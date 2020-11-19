#include "netreader.h"
#include "ui_netreader.h"
#include <QMessageBox>

NetReader::NetReader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetReader)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    m_nPort = 4000;
    m_strServer = "10.10.10.100";
    m_nScale = 10000;
    m_nDuration = 2;
    m_bRunning = false;
    m_pTransport = 0;
    m_pRawData = 0;
    m_nEpochLen = 150;

    m_pEEGGraph = new EEGGraph(this);

    ui->editPort->setText(QString::number(m_nPort));
    ui->editServer->setText(m_strServer);
    ui->spinScale->setMaximum(1000000);
    ui->spinScale->setSingleStep(500);
    ui->spinScale->setValue(m_nScale);
    ui->spinDuration->setValue(m_nDuration);
    ui->editInstruction->setEnabled(false);

    showInstructions();
}

NetReader::~NetReader()
{
    stopAcquisition();
    delete ui;
}

void NetReader::on_btnConnect_clicked()
{
    // qDebug("NetReader::on_btnConnect_clicked: thread 0x%x", (uint)QThread::currentThreadId());
    m_nPort = ui->editPort->text().toInt();
    m_strServer = ui->editServer->text();

    if (m_pTransport == 0) {
        m_pTransport = new AmpTransport(this);
        connect(m_pTransport, SIGNAL(connected()), this, SLOT(onConnected()));
        connect(m_pTransport, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
        connect(m_pTransport, SIGNAL(ctrlpacket(AmpMessage*)), this, SLOT(onCtrlMsg(AmpMessage*)));
        connect(m_pTransport, SIGNAL(datapacket(AmpMessage*)), this, SLOT(onDataMsg(AmpMessage*)));
    }

    if (!m_pTransport->isConnected()) {
        m_pTransport->start(m_strServer, m_nPort);
    } else {
        stopAcquisition();
        showStatus("Client stopped");
    }
    enableControls(isConnected());
}

void NetReader::on_btnHide_clicked()
{
    hide();
}

void NetReader::on_spinDuration_valueChanged(int arg1)
{
    m_nDuration = arg1;
    m_pEEGGraph->setPoints(m_nDuration*m_BasicInfo.nRate);
}

void NetReader::on_spinScale_valueChanged(int arg1)
{
    m_nScale = arg1;
    m_fScaleCoef = (32767*m_BasicInfo.fResolution)/(m_nScale*(m_BasicInfo.nEegChan+2));
    m_pEEGGraph->setScale(m_fScaleCoef);
}

bool NetReader::startAcquisition()
{
    if (m_pTransport == 0) return false;
    if (m_bRunning) return false;

    if (!m_BasicInfo.validate()) {
        qDebug("Basic channel info unavailable. Look at NetReader::startAcquisition() procedure.");
        return false;
    }
    m_nAllChannels = m_BasicInfo.nEegChan + m_BasicInfo.nEvtChan;
    m_nBlockPoints = m_BasicInfo.nBlockPnts;
    m_nTotalPoints = m_BasicInfo.nRate*m_nDuration;
    m_fScaleCoef = (32767*m_BasicInfo.fResolution)/(m_nScale*(m_BasicInfo.nEegChan+2));

    if (!m_BasicInfo.validate() || m_nTotalPoints <= 0) {
        qDebug("Serious error with parameters.Look at NetReader::startAcquisition() procedure.");
        return false;
    }
    m_EpochManager.setChannelInfo(m_BasicInfo.nEegChan, m_BasicInfo.nEvtChan, m_nEpochLen);
    m_EpochManager.clearEpochs();

    m_pRawData = new int[m_nTotalPoints*m_nAllChannels];
    m_pEEGGraph->init(m_nAllChannels, m_nTotalPoints, m_fScaleCoef);
    m_pEEGGraph->setDataSource(m_pRawData);
    m_pEEGGraph->startUpdate();
    m_pEEGGraph->show();
    m_pEEGGraph->setGeometry(ui->editInstruction->geometry());
    ui->editInstruction->hide();

    m_WorkThread = QtConcurrent::run(this, &NetReader::worker);
    m_pTransport->sendCommand(CTRLCODE::ClientControlCode, CTRLREQ::RequestStartData);

    return true;
}

bool NetReader::stopAcquisition()
{
    if (m_pTransport == 0) return false;

    m_pTransport->sendCommand(CTRLCODE::ClientControlCode, CTRLREQ::RequestStopData);
    m_pTransport->stop();

    m_bRunning = false;
    m_WorkThread.waitForFinished();

    m_EpochManager.clearEpochs();

    // m_EEGGraph.stopUpdate();
    delete m_pRawData;
    m_pRawData = 0;

    return true;
}

void NetReader::worker()
{
    qDebug("NetReader::worker: thread started: 0x%x", (uint)QThread::currentThreadId());
    int sample = 0;
    bool b32bit = (m_BasicInfo.nDataSize == sizeof(int));
    int blocksize = m_nAllChannels*m_nBlockPoints*m_BasicInfo.nDataSize;
    char* data = new char[blocksize];

    m_bRunning = true;
    while (m_bRunning) {
        if (!m_pTransport->getData(data, blocksize)) {
            QThread::msleep(10);
        } else {
            m_EpochManager.insertData(data, m_BasicInfo.nBlockPnts, b32bit);

            if (m_pRawData != 0) {
                for (int i=0; i<m_nBlockPoints; i++)
                {
                    for (int j=0; j<m_nAllChannels; j++)
                    {
                        if (b32bit) {
                            int* pData32 = (int*)data;
                            int aa = pData32[i*m_nAllChannels+j];
                            m_pRawData[(i+sample)*m_nAllChannels+j] = aa;
                        } else {
                            short* pData16 = (short*)data;
                            m_pRawData[(i+sample)*m_nAllChannels+j] = pData16[i*m_nAllChannels+j];
                        }
                    }
                }
                sample = (sample+m_nBlockPoints)%m_nTotalPoints;
            }
        }
    }
    qDebug("NetReader::worker: thread stopped: 0x%x", (uint)QThread::currentThreadId());
}

bool NetReader::isConnected()
{
    return (m_pTransport && m_pTransport->isConnected());
}

void NetReader::onConnected()
{
    showStatus("Server: "+m_strServer+":"+QString::number(m_nPort));
    showInstructions();

    enableControls(isConnected());
}

void NetReader::onDisconnected()
{
    enableControls(isConnected());
}

void NetReader::onCtrlMsg(AmpMessage* pMsg)
{
    int code = pMsg->m_nCode;
    int request = pMsg->m_nRequest;
    if (!pMsg->isValidPacket()) return;
    if (code == CTRLCODE::GeneralControlCode) {
        switch (request)
        {
        case CTRLREQ::ClosingUp:
        case CTRLREQ::ServerDisconnected:
                m_EpochManager.clearEpochs();
                showStatus("Server disconnected");
                break;
        }
    }
    else if (code == CTRLCODE::ServerControlCode) {
        QString strStatus;
        switch (request)
        {
            case CTRLREQ::StartAcquisition:
                if (startAcquisition()) {
                    strStatus = "Start Acquisition";
                }
                break;
            case CTRLREQ::StopAcquisition:
                if (stopAcquisition()) {
                    strStatus = "Stop Acquisition";
                }
                break;
            case CTRLREQ::StartImpedance:
                strStatus = "Start Impedance";
                break;
            case CTRLREQ::DCCorrection:
                strStatus = "DC Correction";
                break;
            case CTRLREQ::ChangeSetup:
                strStatus = "Setup was changed";
                break;
        }
        showStatus(strStatus);
    }
    delete pMsg;
    enableControls(isConnected());
}

void NetReader::onDataMsg(AmpMessage* pMsg)
{
    int code = pMsg->m_nCode;
    int request = pMsg->m_nRequest;
    if (!pMsg->isValidPacket()) return;
    if (code == DATACODE::DataType_InfoBlock) {
        if (request == DATAREQ::InfoType_BasicInfo) {
            if ((pMsg->m_pData != 0) && (pMsg->m_nSize > 0)) {
                AmpBasicInfo* pInfo = (AmpBasicInfo*)pMsg->m_pData;
                Q_ASSERT(pInfo->dwSize == sizeof(AmpBasicInfo));
                memcpy((void*)&m_BasicInfo, pMsg->m_pData, sizeof(m_BasicInfo));
                QString strMsg;
                strMsg.sprintf("EEG:%d+%d;Pnts:%d;%dHz;Bits:%d;Res:%.3fuV/LSB",
                    m_BasicInfo.nEegChan, m_BasicInfo.nEvtChan, m_BasicInfo.nBlockPnts,
                    m_BasicInfo.nRate, m_BasicInfo.nDataSize*8, m_BasicInfo.fResolution);
                showStatus(strMsg);
            }
        }
    }
    delete pMsg;
    pMsg = 0;
}

void NetReader::enableControls(bool bConnected)
{
    ui->editPort->setEnabled(!bConnected);
    ui->editServer->setEnabled(!bConnected);
    ui->spinDuration->setEnabled(!bConnected);
    ui->btnConnect->setText(bConnected?"Disconnect":"Connect");
}

void NetReader::showStatus(QString strStatus)
{
    ui->editStatus->setText(strStatus);
}

void NetReader::showInstructions()
{
    QString strInstructions =
        (
        "\r\n"
        "\tDESCRIPTION:\r\n\r\n"
        "\tThis sample application (with source code) is provided to illustrate a client\\server concept under SCAN 4.3\r\n"
        "\tincluding: 1) transfer the basic setup information, EEG data, and impedance values through TCP sockets;\r\n"
        "\t2) display of the incoming EEG data signals and events; 3) storing the raw EEG data/events in binary format.\r\n\r\n"
        "\tINSTRUCTIONS:\r\n\r\n"
        "\t1. \tStart ACQUIRE.EXE as a server on local or remote computer.\r\n"
        "\t2. \tIf you use remote computer, enter it's server name, e.g. '12.34.56.78'.\r\n"
        "\t   \tIf you use local computer, leave default 'localhost' name.\r\n"
        "\t3. \tSpecify port, duration, and initial scale.\r\n"
        "\t4. \tClick on 'Connect' button. This program will connect as a client to ACQUIRE server.\r\n"
        "\t5. \tStart acquisition on server side, the signal will appear on both screens.\r\n"
        "\t   \tStatus box will show total bytes transferred and current transfer rate.\r\n"
        "\t6. \tAdjust vertical scale, if necessary.\r\n"
        "\t7. \tEnter events and perform DC corrections on server side, observe they appear on client side.\r\n"
        "\t8. \tClick on 'Save' button to store incoming data in raw binary format.\r\n"
        "\t   \tFile name is 'DATA.BIN' and it is created in working directory of client program.\r\n"
        "\t9. \tStart impedance measurement on server side and see impedance values on client side.\r\n"
        "\t10.\tClick on 'Disconnect' button to stop client operation.\r\n"
        "\t11.\tExit ACQUIRE and this program.\r\n\r\n"
        "\tDISCLAIMER:\r\n"
        "\tThis sample application is provided for informational purposes only and Neuroscan makes no warranties,\r\n"
        "\teither express or implied, in this application. The entire risk of the use of this sample remains with the user.\r\n"
        "\tTechnical support is not available for this sample application and for the provided source code.\r\n"
        "\r\n\r\n\r\n\r\n\r\n\r\n\t?986-2003 Neuroscan. All rights reserved."
        );
    ui->editInstruction->setText(strInstructions);
    m_pEEGGraph->hide();
    ui->editInstruction->show();
}

void NetReader::setEpochLen(int epochlen)
{
    m_nEpochLen = epochlen;
}

Epoch* NetReader::getEpoch()
{
    return m_EpochManager.getEpoch(true);
}

void NetReader::clearEpochs()
{
    m_EpochManager.clearEpochs();
}
