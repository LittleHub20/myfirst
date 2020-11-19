#include "tcpclientmt.h"

TCPWorker::TCPWorker(QObject *parent) : QObject(parent)
{
    m_pSocket = 0;
}

void TCPWorker::onConnect(QString host, long port)
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
    } catch (...) {
        emit error(m_pSocket->error(), m_pSocket->errorString());
    }
}

void TCPWorker::onDisconnect()
{
    // qDebug("onDisconnect in thread: 0x%x", QThread::currentThreadId());
    if (isConnected()) {
        m_pSocket->abort();
        m_pSocket->disconnectFromHost();
        m_pSocket->close();
    }
}

void TCPWorker::onSend(QByteArray data)
{
    // qDebug("onSend in thread: 0x%x", (uint)QThread::currentThreadId());
    m_pSocket->write(data.data(), data.size());
    // m_pSocket->flush();
}

void TCPWorker::onConnected()
{
    m_pSocket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
    emit connected();
}

void TCPWorker::onDisconnected()
{
    emit disconnected();
}

void TCPWorker::onReceived()
{
    // qDebug("onReceived in thread: 0x%x", (uint)QThread::currentThreadId());
    QByteArray buff;
    buff = m_pSocket->readAll();
    m_Buffer.write(buff.data(), buff.size());
    emit received(&m_Buffer);
}

void TCPWorker::onSent(qint64 bytes)
{
    // qDebug("%lld bytes have been sent", bytes);
    emit sent(bytes);
}

void TCPWorker::onError(QAbstractSocket::SocketError)
{
    emit error(m_pSocket->error(), m_pSocket->errorString().toLocal8Bit().data());
}

TCPClientMT::TCPClientMT()
{
    m_pWorker = 0;
    m_pSocket = 0;
    m_pThread = new QThread(this);
    m_pThread->start();

    qRegisterMetaType<IOBuffer*>("IOBuffer");
    qRegisterMetaType<IOBuffer*>("IOBuffer&");
    qRegisterMetaType<IOBuffer*>("IOBuffer*");
}

TCPClientMT::~TCPClientMT()
{
    m_pThread->exit();
    m_pThread->wait();
}

void TCPClientMT::onConnect(const QString host, const long port)
{
    if (m_pWorker == 0)  {
        m_pWorker = new TCPWorker();
        m_pWorker->setParent(0);
        m_pWorker->moveToThread(m_pThread);
        connect(this, SIGNAL(doConnect(QString,long)), m_pWorker, SLOT(onConnect(QString,long)));
        connect(this, SIGNAL(doDisconnect()), m_pWorker, SLOT(onDisconnect()));
        connect(this, SIGNAL(doSend(QByteArray)), m_pWorker, SLOT(onSend(QByteArray)));
        connect(m_pWorker, SIGNAL(connected()), this, SLOT(onConnected()));
        connect(m_pWorker, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
        connect(m_pWorker, SIGNAL(received(IOBuffer*)), this, SLOT(onReceived(IOBuffer*)));
        connect(m_pWorker, SIGNAL(sent(long)), this, SLOT(onSent(long)));
        connect(m_pWorker, SIGNAL(error(int, QString)), this, SLOT(onError(int, QString)));
    }
    emit doConnect(host, port);
}

void TCPClientMT::onDisconnect()
{
    emit doDisconnect();
}

void TCPClientMT::onSend(const char *data, long len)
{
    QByteArray buff;
    buff.append(data, len);
    onSend(buff);
}

void TCPClientMT::onSend(const char *data)
{
    QByteArray buff;
    buff.append(data);
    onSend(buff);
}

void TCPClientMT::onSend(QByteArray data)
{
    emit doSend(data);
}

void TCPClientMT::onSend(QString data)
{
    onSend(data.toLocal8Bit());
}

void TCPClientMT::onConnected()
{
    emit connected();
}

void TCPClientMT::onDisconnected()
{
    emit disconnected();
}

void TCPClientMT::onReceived(IOBuffer* data)
{
    emit received(data);
}

void TCPClientMT::onSent(long bytes)
{
    // qDebug("%lld bytes have been sent", bytes);
    emit sent(bytes);
}

void TCPClientMT::onError(int errorno, QString errorstr)
{
    emit error(errorno, errorstr);
}
