#include "netmarker.h"
#include "ui_netmarker.h"
#include <QtEndian>
#include <QMessageBox>

NetMarker::NetMarker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetMarker)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    m_nMode = MODE_LOCAL;
    m_nPort = 5000;
    m_strServer = "192.168.0.104";
    m_pSocket = 0;
    m_nEvent = 1;
    m_bRunning = false;

    ui->editPort->setText(QString::number(m_nPort));
    ui->editServer->setText(m_strServer);
    ui->editEvent->setText(QString::number(m_nEvent));
}

NetMarker::~NetMarker()
{
    m_bRunning = false;
    m_WorkThread.waitForFinished();
    delete ui;
}

void NetMarker::on_btnConnect_clicked()
{
    m_nPort = ui->editPort->text().toInt();
    m_strServer = ui->editServer->text();

    if (m_pSocket == 0)  {
        m_pSocket = new UDPClient();
        connect(m_pSocket, SIGNAL(connected()), this, SLOT(onConnected()));
        connect(m_pSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
        // connect(m_pSocket, SIGNAL(received(IOBuffer*)), this, SLOT(onReceived(IOBuffer*)));
        // connect(m_pSocket, SIGNAL(error(int, QString)), this, SLOT(onError(int, QString)));
    }

    if (!m_pSocket->isConnected()) {
        m_pSocket->onConnect(m_strServer, m_nPort);
    } else {
        m_pSocket->onDisconnect();
    }
}

void NetMarker::on_btnHide_clicked()
{
    hide();
}

void NetMarker::on_btnSend_clicked()
{
    m_nEvent = ui->editEvent->text().toInt();
    outputEvent(m_nEvent);
}

void NetMarker::onConnected()
{
    clearEvents();
    m_bRunning = true;
    // m_WorkThread = QtConcurrent::run(this, &NetMarker::worker);

    enableControls(isConnected());
}

void NetMarker::onDisconnected()
{
    m_bRunning = false;
    m_WorkThread.waitForFinished();

    enableControls(isConnected());
}

void NetMarker::setMode(int mode)
{
    m_nMode = mode;
}

void NetMarker::outputEvent(int event)
{
    // setEvent(event);
    sendEvent(event);
}

void NetMarker::sendEvent(int event)
{
    // event = qToBigEndian(event);
    if (isConnected())
        m_pSocket->onSend((char*)&event, sizeof(int));
}

bool NetMarker::isConnected()
{
    return (m_pSocket && m_pSocket->isConnected());
}

void NetMarker::enableControls(bool bConnected)
{
    ui->editPort->setEnabled(!bConnected);
    ui->editServer->setEnabled(!bConnected);
    ui->btnConnect->setText(bConnected?"Disconnect":"Connect");
}

void NetMarker::worker()
{
    qDebug("NetMarker::worker: thread started: 0x%x", (uint)QThread::currentThreadId());
    int event = -1;
    while (m_bRunning) {
        event = getEvent();
        if (event > 0) {
            sendEvent(event);
        } else {
            QThread::msleep(1);
        }
    }
    qDebug("NetMarker::worker: thread stopped: 0x%x", (uint)QThread::currentThreadId());
}

void NetMarker::setEvent(int event)
{
    m_mutexEvent.lock();
    m_queueEvent.append(event);
    m_mutexEvent.unlock();
}

int NetMarker::getEvent(bool bRemove)
{
    int event = -1;
    m_mutexEvent.lock();
    if (m_queueEvent.size() > 0) {
        if (bRemove) {
            event = m_queueEvent.takeFirst();
        } else {
            event = m_queueEvent.first();
        }
    }
    m_mutexEvent.unlock();
    return event;
}

void NetMarker::clearEvents()
{
    m_mutexEvent.lock();
    m_queueEvent.clear();
    m_mutexEvent.unlock();
}
