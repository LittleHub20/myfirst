#include "netpresenter.h"
#include "ui_netpresenter.h"

NetPresenter::NetPresenter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetPresenter)
{
    ui->setupUi(this);

    m_nMode = MODE_LOCAL;
    m_nPort = UI_SOCKET_PORT;
    m_strServer = "127.0.0.1";
    m_strContent = "1";
    m_pSocket = 0;
    m_nTarget = 1;
    m_nStimulusNumber = -1;
    m_bRunning = false;

    ui->editPort->setText(QString::number(m_nPort));
    ui->editServer->setText(m_strServer);
    ui->editContent->setText(m_strContent);
}

NetPresenter::~NetPresenter()
{
    m_bRunning = false;
    delete ui;
}

void NetPresenter::on_btnConnect_clicked()
{
    m_nPort = ui->editPort->text().toInt();
    m_strServer = ui->editServer->text();
    onConnect();
}

void NetPresenter::on_btnHide_clicked()
{
    hide();
}

void NetPresenter::on_btnSend_clicked()
{
    m_nTarget = ui->editContent->text().toInt();
    presentStimulus(m_nTarget);
}

void NetPresenter::onConnect()
{
    if (m_pSocket == 0)  {
        m_pSocket = new TCPClientMT();
        connect(m_pSocket, SIGNAL(connected()), this, SLOT(onConnected()));
        connect(m_pSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
        connect(m_pSocket, SIGNAL(received(IOBuffer*)), this, SLOT(onReceived(IOBuffer*)));
        connect(m_pSocket, SIGNAL(error(int, QString)), this, SLOT(onError(int, QString)));
    }

    if (!m_pSocket->isConnected()) {
        m_pSocket->onConnect(m_strServer, m_nPort);
    }
}

void NetPresenter::onDisconnect()
{
    if (m_pSocket)
        m_pSocket->onDisconnect();
}

void NetPresenter::onConnected()
{
    // m_WorkThread = QtConcurrent::run(this, &NetPresenter::worker);
    enableControls(isConnected());
}

void NetPresenter::onDisconnected()
{
    m_bRunning = false;
    enableControls(isConnected());
}

void NetPresenter::setMode(int mode)
{
    m_nMode = mode;
}

void NetPresenter::queryStimulusNumber()
{
    m_nStimulusNumber = -1;
    queryStimulus();
}

void NetPresenter::worker()
{
    qDebug("NetPresenter::worker: thread started: 0x%x", (uint)QThread::currentThreadId());
    m_bRunning = true;
    while (m_bRunning) {

    }
    qDebug("NetPresenter::worker: thread stopped: 0x%x", (uint)QThread::currentThreadId());
}

void NetPresenter::presentStimulus(int target)
{
    sendStimulus(target);
}

void NetPresenter::presentFeedback(int result)
{
    sendStimulus(result);
}

void NetPresenter::queryStimulus()
{
    UICommand cmd = {CMDTYPE::CMDTYPE_QUERY, 0};
    if (isConnected())
        m_pSocket->onSend((char*)&cmd, sizeof(UICommand));
}

void NetPresenter::onStimulusNumber(int num)
{
    if (num > 0) {
        m_nStimulusNumber = num;
        emit stimulusnumber(num);
    }
}

void NetPresenter::sendStimulus(int target)
{
    UICommand cmd = {CMDTYPE::CMDTYPE_STIMULUS, target};
    if (isConnected())
        m_pSocket->onSend((char*)&cmd, sizeof(UICommand));
}

void NetPresenter::sendFeedback(int result)
{
    UICommand cmd = {CMDTYPE::CMDTYPE_RESULT, result};
    if (isConnected())
        m_pSocket->onSend((char*)&cmd, sizeof(UICommand));
}

bool NetPresenter::isConnected()
{
    return (m_pSocket && m_pSocket->isConnected());
}

void NetPresenter::onError(int errorno, QString errorstr)
{
    emit error(errorno, errorstr);
}

void NetPresenter::onReceived(IOBuffer* buff)
{
    UICommand cmd;
    if (buff->length() >= sizeof(UICommand)) {
        buff->read((char*)&cmd, sizeof(UICommand));
        if (cmd.type == CMDTYPE::CMDTYPE_RESULT) {
            qDebug("CMDTYPE_RESULT received and number of stimulus is %d", cmd.content);
            onStimulusNumber(cmd.content);
        }
    }
}

void NetPresenter::enableControls(bool bConnected)
{
    ui->editPort->setEnabled(!bConnected);
    ui->editServer->setEnabled(!bConnected);
    ui->btnConnect->setText(bConnected?"Disconnect":"Connect");
}
