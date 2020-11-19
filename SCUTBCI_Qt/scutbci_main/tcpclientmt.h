#ifndef TCPCLIENTMT_H
#define TCPCLIENTMT_H

#include <QThread>
#include <QMetaType>
#include <QTcpSocket>
#include "sockethandler.h"

class TCPWorker : public QObject
{
    Q_OBJECT
protected:
    IOBuffer m_Buffer;
    QTcpSocket* m_pSocket;
public:
    explicit TCPWorker(QObject *parent = 0);
    QTcpSocket* getSocket() { return m_pSocket; }
    bool isConnected() {
        return (m_pSocket && (m_pSocket->state() == QAbstractSocket::ConnectedState));
    }

signals:
    void connected();
    void disconnected();
    void received(IOBuffer* buff);
    void sent(long bytes);
    void error(int errorno, const QString errorstr);

public slots:
    // handling signals from its owner
    void onConnect(const QString host, const long port);
    void onDisconnect();
    void onSend(QByteArray data);
    // handling signals from QTcpSocket
    void onConnected();
    void onDisconnected();
    void onReceived();
    void onSent(qint64);
    void onError(QAbstractSocket::SocketError);
};

class TCPClientMT : public SocketHandler
{
    Q_OBJECT
protected:
    QString m_strType = "TCP";
    QThread* m_pThread;
    TCPWorker* m_pWorker;
    QTcpSocket* m_pSocket;

public:
    explicit TCPClientMT();
    ~TCPClientMT();
    bool isConnected() { return (m_pWorker && m_pWorker->isConnected()); }

    void onConnect(const QString host, const long port);
    void onDisconnect();
    void onSend(const char *data, long len);
    void onSend(const char *data);
    void onSend(QByteArray data);
    void onSend(QString data);

signals:
    // signals for TCPWorker
    void doConnect(QString, long);
    void doDisconnect();
    void doSend(const char*, long);
    void doSend(QByteArray);

public slots:
    void onConnected();
    void onDisconnected();
    void onReceived(IOBuffer* data);
    void onSent(long);
    void onError(int errorno, QString errorstr);
};

#endif // TCPCLIENTMT_H
