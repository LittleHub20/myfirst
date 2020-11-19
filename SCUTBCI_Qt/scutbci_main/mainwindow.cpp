#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->addPermanentWidget(&m_labelStatus);

    m_nNumBtns = 0;

    m_nMode = MODE_ONLINE;
    m_bUserStop = true;
    m_bWaitForNextTrial = true;
    m_nTrainRounds = 10;
    m_nMaxTrial = 80;
    m_nStimIndex = 0;
    m_nRoundIndex = 0;
    m_nCurrentTrial = 0;
    m_nRecvIndex = 0;
    m_seqReceive.clear();

    m_pNetReader = new NetReader(this);
    m_pNetMarker = new NetMarker(this);
    m_pNetActuator = new NetActuator(this);
    m_pNetPresenter = new NetPresenter(this);
    m_Algorithm.setSubject("noise");
    m_Algorithm.setModelPath("../models/trained_bayes.xml");
    enableControls(!m_bUserStop);

    connect(&m_timerFSM, SIGNAL(timeout()), this, SLOT(onTimerFSM()));
    connect(&m_timerData, SIGNAL(timeout()), this, SLOT(onTimerData()));
    connect(&m_timerConnection, SIGNAL(timeout()), this, SLOT(onTimerConnection()));

    startTimerConnection(5000);
}

MainWindow::~MainWindow()
{
    stopTimerConnection();
    delete ui;
}

void MainWindow::enableControls(bool bStarted)
{
    ui->actionStart->setEnabled(!bStarted);
    ui->actionStop->setEnabled(bStarted);
}

void MainWindow::on_actionNetReader_triggered()
{
    m_pNetReader->show();
}

void MainWindow::on_actionNetMarker_triggered()
{
    m_pNetMarker->show();
}

void MainWindow::on_actionNetActuator_triggered()
{
    m_pNetActuator->show();
}

void MainWindow::on_actionNetPresenter_triggered()
{
    m_pNetPresenter->show();
}

void MainWindow::on_actionStimSeq_triggered()
{
    generateSeq(m_seqStim, m_seqStimOld, m_nNumBtns, m_nNumBtns/2);
    displaySeq(m_seqStim);
}

void MainWindow::on_actionStart_triggered()
{
    // if (!initSystem()) return;

    m_bUserStop = false;
    m_nCurrentTrial = 0;
    startTimerFSM(STATE_START, 10);
    startTimerData(10);
    enableControls(!m_bUserStop);
}

void MainWindow::on_actionStop_triggered()
{
    m_bUserStop = true;
    stopTimerFSM();
    stopTimerData();
    enableControls(!m_bUserStop);
}

void MainWindow::paintEvent(QPaintEvent*)
{

}

void MainWindow::startTimerFSM(int state, int interval)
{
    m_nState = state;
    m_timerFSM.stop();
    m_timerFSM.setInterval(interval);
    m_timerFSM.start();
}

void MainWindow::stopTimerFSM()
{
    m_timerFSM.stop();
}

void MainWindow::onTimerFSM()
{
    FSM(m_nState);
}

void MainWindow::FSM(int state)
{
    stopTimerFSM();
    switch (state)
    {
    case STATE_START:
        m_seqStimOld.clear();
        if (m_nMode == MODE_TRAIN) {
            setParameterTrain();
        } else if (m_nMode == MODE_ONLINE) {
            setParameterOnline();
        }
        startTimerFSM(STATE_PREPARE, m_nTimeStart2Prepare);
        break;
    case STATE_PREPARE:
        m_pNetPresenter->queryStimulusNumber();
        m_nStimIndex = 0;
        m_nRoundIndex = 0;
        m_pNetMarker->outputEvent(EVENT_SYSTEM_START);
        startTimerFSM(STATE_ROUNDINIT, m_nTimePrepare2Round);
        break;
    case STATE_ROUNDINIT:
        m_nNumBtns = m_pNetPresenter->m_nStimulusNumber;
        if (m_nNumBtns <= 1) {
            startTimerFSM(STATE_PREPARE, m_nTimeStart2Prepare);
            break;
        }
        m_bWaitForNextTrial = false;
        generateSeq(m_seqStim, m_seqStimOld, m_nNumBtns, m_nNumBtns/2);
        qDebug("Trial: %d, Round: %d, Seq: ", m_nCurrentTrial, m_nRoundIndex);
        displaySeq(m_seqStim);

        m_nFlashIndex = m_seqStim.takeFirst();
        m_pNetMarker->outputEvent(EVENT_DATA_BEGIN+m_nFlashIndex-1);
        // m_pBtnSpeller[m_nFlashIndex-1]->flashOnce(100);
        m_pNetPresenter->presentStimulus(m_nFlashIndex-1);
        m_nStimIndex ++;

        if (!m_bWaitForNextTrial)
            startTimerFSM(STATE_ROUND, m_nTimeOneStimulus);

        break;
    case STATE_ROUND:
        if (m_bWaitForNextTrial) break;
        m_nFlashIndex = m_seqStim.takeFirst();
        m_pNetMarker->outputEvent(EVENT_DATA_BEGIN+m_nFlashIndex-1);
        // m_pBtnSpeller[m_nFlashIndex-1]->flashOnce(100);
        m_pNetPresenter->presentStimulus(m_nFlashIndex-1);
        m_nStimIndex ++;

        if (m_nStimIndex >= m_nNumBtns) {
            m_nStimIndex = 0;
            m_nRoundIndex ++;
            startTimerFSM(STATE_ROUNDINIT, m_nTimeOneStimulus);
            break;
        }

        startTimerFSM(STATE_ROUND, m_nTimeOneStimulus);
        break;
    case STATE_REST:
        m_nCurrentTrial ++;
        startTimerFSM(STATE_PREPARE, m_nTimeRest2Prepare);
        break;
    }

    if (m_nCurrentTrial > m_nMaxTrial) on_actionStop_triggered();
    QString strStatus;
    strStatus.sprintf("Trial: %d, Round: %d [P300_result = %d]",
        m_nCurrentTrial, m_nRoundIndex, m_Algorithm.getResult());
    m_labelStatus.setText(strStatus);
}

void MainWindow::startTimerData(int interval)
{
    m_timerData.stop();
    m_timerData.setInterval(interval);
    m_timerData.start();
}

void MainWindow::stopTimerData()
{
    m_timerData.stop();
}

void MainWindow::onTimerData()
{
    checkDataReady();
}

void MainWindow::checkDataReady()
{
    Epoch* epoch = m_pNetReader->getEpoch();
    if (epoch != 0) {
        int event = epoch->event;
        if (event >= EVENT_DATA_BEGIN && event <= EVENT_DATA_END) {
            // qDebug("Received event: %d", event);
            if (m_bWaitForNextTrial) {
                if (epoch) delete epoch;
                return;
            }

            /*
            m_nRecvIndex ++;
            m_seqReceive.append(event);
            if (m_nRecvIndex % m_nNumBtns == 0) {
                displaySeq(m_seqReceive);
                m_nRecvIndex = 0;
                m_seqReceive.clear();
            }
            */

            m_Algorithm.recvEpoch(epoch->event, epoch->data, epoch->channels, epoch->epochlen);
            m_Algorithm.call(EEGAlgoEng::JOB_ROUND, 5000);
            feedback(m_Algorithm.getResult());
            m_Algorithm.resetResult();

            delete epoch;
        }
    }
}

void MainWindow::startTimerConnection(int interval)
{
    m_timerConnection.stop();
    m_timerConnection.setInterval(interval);
    m_timerConnection.start();
}

void MainWindow::stopTimerConnection()
{
    m_timerConnection.stop();
}

void MainWindow::onTimerConnection()
{
    checkConnection();
}

void MainWindow::checkConnection()
{
    m_pNetPresenter->onConnect();
}

void MainWindow::feedback(int result)
{
    if (result > 0 && result <= m_nNumBtns) {
        m_bWaitForNextTrial = true;

        m_nCurrentTrial ++;
        stopTimerFSM();
        outputResult(result);

        m_nState = STATE_PREPARE;
        startTimerFSM(STATE_PREPARE, m_nTimeRest2Prepare);
    }
}

void MainWindow::outputResult(int result)
{
    qDebug("Evaluate result: %d", result);
}

bool MainWindow::initSystem()
{
    if (!m_pNetMarker->isConnected()) {
        m_pNetMarker->show();
        QMessageBox::information(this, "NetMarker",
            "Please connect to the StimGenerator, then press OK");
        return false;
    }

    if (!m_pNetReader->isConnected()) {
        m_pNetReader->show();
        QMessageBox::information(this, "NetReader",
            "Please start the Scan server, then press OK");
        return false;
    }

    m_Algorithm.call(EEGAlgoEng::JOB_INIT);

    return true;
}

void MainWindow::setParameterTrain()
{
    m_nTimeStart2Prepare = 2000;
    m_nTimePrepare2Round = 2000;
    m_nTimeOneStimulus	= 30;
    m_nTimeRest2Prepare	= 2000;
}

void MainWindow::setParameterOnline()
{
    m_nTimeStart2Prepare = 2000;
    m_nTimePrepare2Round = 2000;
    m_nTimeOneStimulus	= 30;
    m_nTimeRest2Prepare	= 2000;
}

void MainWindow::randperm(int* seq, int n)
{
    int i,k;
    int	*tmp = NULL;

    tmp = new int[n];

    for(i=0; i<n; i++)
    {
        tmp[i] = i+1;
    }

    for(i=0; i<n; i++)
    {
        k = rand()%(n-i);
        seq[i] = tmp[k];
        tmp[k] = tmp[n-i-1];
    }

    delete tmp;
}

void MainWindow::generateSeq(QList<int> &newSeq, QList<int> &oldSeq, int len, int interval)
{
    if(interval >= len - 1)
    {
        qDebug("interval is too large.");
        return;
    }

    if(newSeq.size() > 0)
    {
        newSeq.clear();
    }

    int i, j;
    if(oldSeq.size() > 0)
    {
        // 生成一个1-len的固定序列
        QList<int> fixSeq;
        for(i=0; i<len; i++)
        {
            fixSeq.append(i+1);
        }

        // 生成新的序列并保证新序列首部inteval长度范围内的值与就序列不同
        for(i=0; i<interval; i++)
        {
            bool valid = false; // 新生成值是否存在与就序列尾部相同的

            int new_temp;
            int index_temp;
            do
            {
                valid = true;
                index_temp = rand()%fixSeq.size();
                new_temp = fixSeq.at(index_temp);
                fixSeq.removeAt(index_temp);
                // 比较旧序列的尾部interval-i长度内是否存在相同的值
                for(j=0; j<interval-i; j++)
                {
                    int old_temp = oldSeq.at(len-j-1);
                    if(old_temp == new_temp)
                    {
                        fixSeq.insert(index_temp, new_temp);
                        valid = false;
                        break;
                    }
                }
            }while(!valid);

            newSeq.append(new_temp);
        }

        for(i=i; i<len; i++)
        {
            int temp = rand()%fixSeq.size();
            newSeq.append(fixSeq.at(temp));
            fixSeq.removeAt(temp);
        }
    }
    // 不存在旧序列则直接随机生成一个序列返回
    else {
        // 生成一个1-len的固定序列
        QList<int> fixSeq;
        for(i=0; i<len; i++)
        {
            fixSeq.append(i+1);
        }

        for(i=0; i<len; i++)
        {
            int temp = rand()%fixSeq.size();
            newSeq.append(fixSeq.at(temp));
            fixSeq.removeAt(temp);
        }
    }

    oldSeq = newSeq;
}

void MainWindow::displaySeq(QList<int> &seq)
{
    QString strSeq;
    for (int index=0; index< seq.size(); index++)
    {
        strSeq += QString::number(seq.at(index)) + " ";
    }
    qDebug(strSeq.toLocal8Bit());
}
