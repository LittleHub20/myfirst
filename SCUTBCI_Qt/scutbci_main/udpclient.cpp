#include "udpclient.h"

UDPClient::UDPClient()
{
    m_pSocket = 0;
    m_bConnected = false;
}

void UDPClient::onConnect(const QString host, const long port)
{
    // qDebug("onConnect in thread: 0x%x", (uint)QThread::currentThreadId());
    if (m_pSocket == 0)  {
        m_pSocket = new QUdpSocket(this);
        connect(m_pSocket, SIGNAL(readyRead()), this, SLOT(onReceived()));
        connect(m_pSocket, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(onError(QAbstractSocket::SocketError)));
    }

    try {
        m_Buffer.clear();
        m_nPort = port;
        m_strHost = host;
        m_pSocket->bind(QHostAddress::AnyIPv4, 5678);
        m_bConnected = true;
        emit connected();
    } catch (QAbstractSocket::SocketError) {
        emit error(m_pSocket->error(), m_pSocket->errorString());
    }
}

void UDPClient::onDisconnect()
{
    // qDebug("onDisconnect in thread: 0x%x", (uint)QThread::currentThreadId());
    m_pSocket->abort();
    m_pSocket->close();
    m_bConnected = false;
    emit disconnected();
}

void UDPClient::onSend(const char *data, long len)
{
    QByteArray buff;
    buff.append(data, len);
    onSend(buff);
}

void UDPClient::onSend(const char *data)
{
    QByteArray buff;
    buff.append(data);
    onSend(buff);
}

void UDPClient::onSend(QByteArray data)
{
    // qDebug("onSend in thread: 0x%x", (uint)QThread::currentThreadId());
    m_pSocket->writeDatagram(data.data(), data.size(), QHostAddress(m_strHost), m_nPort);
    // m_pSocket->flush();
}

void UDPClient::onSend(QString data)
{
    onSend(data.toLocal8Bit());
}

void UDPClient::onReceived()
{
    // qDebug("onReceived in thread: 0x%x", (uint)QThread::currentThreadId());
    QHostAddress sender;
    quint16 senderPort;
    QByteArray buffer;
    buffer.resize(m_pSocket->pendingDatagramSize());
    m_pSocket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
    m_Buffer.write(buffer.data(), buffer.size());
    emit received(&m_Buffer);
}

void UDPClient::onError(QAbstractSocket::SocketError)
{
    // qDebug("error %d : %s", m_pSocket->error(), m_pSocket->errorString().data());
    emit error(m_pSocket->error(), m_pSocket->errorString());
}
