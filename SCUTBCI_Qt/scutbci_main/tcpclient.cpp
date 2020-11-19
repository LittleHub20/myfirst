#include "tcpclient.h"

TCPClient::TCPClient()
{
    m_pSocket = 0;
}

void TCPClient::onConnect(const QString host, const long port)
{
    // qDebug("onConnect in thread: 0x%x", (uint)QThread::currentThreadId());
    if (m_pSocket == 0)  {
        m_pSocket = new QTcpSocket();
        connect(m_pSocket, SIGNAL(connected()), this, SLOT(onConnected()));
        connect(m_pSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
        connect(m_pSocket, SIGNAL(readyRead()), this, SLOT(onReceived()));
        connect(m_pSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(onSent(qint64)));
        connect(m_pSocket, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(onError(QAbstractSocket::SocketError)));
    }

    try {
        m_Buffer.clear();
        m_pSocket->connectToHost(host, port);
    } catch (QAbstractSocket::SocketError) {
        emit error(m_pSocket->error(), m_pSocket->errorString());
    }
}

void TCPClient::onDisconnect()
{
    // qDebug("onDisconnect in thread: 0x%x", (uint)QThread::currentThreadId());
    if (isConnected()) {
        m_pSocket->abort();
        m_pSocket->disconnectFromHost();
        m_pSocket->close();
    }
}

void TCPClient::onSend(const char *data, long len)
{
    QByteArray buff;
    buff.append(data, len);
    onSend(buff);
}

void TCPClient::onSend(const char *data)
{
    QByteArray buff;
    buff.append(data);
    onSend(buff);
}

void TCPClient::onSend(QByteArray data)
{
    // qDebug("onSend in thread: 0x%x", (uint)QThread::currentThreadId());
    m_pSocket->write(data.data(), data.size());
    // m_pSocket->flush();
}

void TCPClient::onSend(QString data)
{
    onSend(data.toLocal8Bit());
}

void TCPClient::onConnected()
{
    m_pSocket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
    emit connected();
}

void TCPClient::onDisconnected()
{
    emit disconnected();
}

void TCPClient::onReceived()
{
    // qDebug("onReceived in thread: 0x%x", (uint)QThread::currentThreadId());
    QByteArray buff;
    buff = m_pSocket->readAll();
    m_Buffer.write(buff.data(), buff.size());
    emit received(&m_Buffer);
}

void TCPClient::onSent(qint64 bytes)
{
    // qDebug("%lld bytes have been sent", bytes);
    emit sent(bytes);
}

void TCPClient::onError(QAbstractSocket::SocketError)
{
    // qDebug("error %d : %s", m_pSocket->error(), m_pSocket->errorString().data());
    emit error(m_pSocket->error(), m_pSocket->errorString());
}
