#include <QThread>
#include <QMessageBox>
#include "amptransport.h"

AmpTransport::AmpTransport(QObject* parent) :
    QObject(parent)
{
    m_pSocket = 0;
    m_pMsg = 0;
    clearMessages();
}

void AmpTransport::start(QString server, int port)
{
    if (m_pSocket == 0)  {
        m_pSocket = new TCPClientMT();
        connect(m_pSocket, SIGNAL(connected()), this, SLOT(onConnected()));
        connect(m_pSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
        connect(m_pSocket, SIGNAL(received(IOBuffer*)), this, SLOT(onReceived(IOBuffer*)), Qt::DirectConnection);
        connect(m_pSocket, SIGNAL(error(int, QString)), this, SLOT(onError(int, QString)));
    }

    if (!m_pSocket->isConnected()) {
        m_pSocket->onConnect(server, port);
    }
}

void AmpTransport::stop()
{
    if (m_pSocket && m_pSocket->isConnected())
    {
        sendCommand(CTRLCODE::ClientControlCode, CTRLREQ::RequestStopData);
        sendCommand(CTRLCODE::GeneralControlCode, CTRLREQ::ClosingUp);
        QThread::msleep(100);
        m_pSocket->onDisconnect();
    }
    clearMessages();
}

bool AmpTransport::isConnected()
{
    return (m_pSocket && m_pSocket->isConnected());
}

bool AmpTransport::sendCommand(short command, short subtype)
{
    qDebug("sendCommand: code %d, request %d", command, subtype);
    AmpMessage msg("CTRL", command, subtype, 0);
    return send(msg, 0);
}

bool AmpTransport::send(AmpMessage msg, char* buff)
{
    if (!m_pSocket->isConnected()) return false;

    msg.convert(true);
    m_pSocket->onSend(msg.m_szId, msg.getHeaderSize());

    if (buff && msg.m_nSize > 0)
        m_pSocket->onSend(buff, msg.m_nSize);

    return true;
}

bool AmpTransport::getData(char* data, int size)
{
    if (m_queueMsg.size() == 0) return false;

    AmpMessage* pMsg = removeMessage();
    if (pMsg->isDataPacket()) {
        if (pMsg->m_nSize != size) {
            qDebug("AmpTransport error, wrong size %d, should be %d",
                   pMsg->m_nSize, size);
            return false;
        } else {
            memcpy(data, pMsg->m_pData, size);
            return true;
        }
    }
    return false;
}

void AmpTransport::onConnected()
{
    // Request for basic info
    sendCommand(CTRLCODE::ClientControlCode, CTRLREQ::RequestBasicInfo);

    emit connected();
}

void AmpTransport::onDisconnected()
{
    emit disconnected();
}

void AmpTransport::onError(int errorno, QString errorstr)
{
    emit error(errorno, errorstr);
}

void AmpTransport::onReceived(IOBuffer* buff)
{
    if (!m_pMsg) m_pMsg = new AmpMessage();
    if (!m_pMsg->m_bHeaderReady) { // 收到数据
        int hdrsize = m_pMsg->getHeaderSize();
        if (buff->length() >= hdrsize) {
            buff->read(m_pMsg->m_szId, hdrsize);
            m_pMsg->convert(false);
            m_pMsg->m_bHeaderReady = true;
        }
    }

    if (m_pMsg && m_pMsg->m_bHeaderReady) {
        int datasize = m_pMsg->m_nSize;
        if (datasize == 0) {
            m_pMsg->m_bRecvComplete = true;
        } else if (datasize > 0 && buff->length() >= datasize) {
            m_pMsg->m_pData = new char[datasize];
            buff->read(m_pMsg->m_pData, datasize);
            m_pMsg->m_bRecvComplete = true;
        }
    }

    if (m_pMsg && m_pMsg->m_bRecvComplete) {
        onMessage(m_pMsg);
        m_pMsg = 0;
    }
}

void AmpTransport::onMessage(AmpMessage* pMsg)
{
    if (pMsg->isCtrlPacket()) {
        qDebug("recvCommand: code %d, request %d", pMsg->m_nCode, pMsg->m_nRequest);
        emit ctrlpacket(pMsg);
    }
    else if (pMsg->isDataPacket()) {
        if (pMsg->m_nCode == DATACODE::DataType_EegData) {
            if (pMsg->m_nRequest == DATAREQ::DataTypeRaw16bit
                || pMsg->m_nRequest == DATAREQ::DataTypeRaw32bit) {
                addMessage(pMsg);
            }
        } else {
            // qDebug("AmpTransport::onMessage() in thread: 0x%x", (uint)QThread::currentThreadId());
            qDebug("recvDataCtrl: code %d, request %d", pMsg->m_nCode, pMsg->m_nRequest);
            emit datapacket(pMsg);
        }
    }
}

void AmpTransport::addMessage(AmpMessage* pMsg)
{
    m_mutexMsg.lock();
    m_queueMsg.append(pMsg);
    m_mutexMsg.unlock();
}

AmpMessage* AmpTransport::removeMessage()
{
    m_mutexMsg.lock();
    AmpMessage* pMsg = 0;
    if (m_queueMsg.size() > 0) pMsg = m_queueMsg.takeFirst();
    m_mutexMsg.unlock();
    return pMsg;
}

void AmpTransport::clearMessages()
{
    m_mutexMsg.lock();
    while (m_queueMsg.size() > 0) {
        AmpMessage* pMsg = m_queueMsg.takeFirst();
        delete pMsg;
    }
    m_mutexMsg.unlock();
}
