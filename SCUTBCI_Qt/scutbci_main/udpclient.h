#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QThread>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include "sockethandler.h"

class UDPClient : public SocketHandler
{
    Q_OBJECT
protected:
    QString m_strType = "UDP";
    long m_nPort;
    QString m_strHost;
    bool m_bConnected;
    IOBuffer m_Buffer;
    QUdpSocket* m_pSocket;

public:
    explicit UDPClient();
    bool isConnected() { return m_bConnected; }

    void onConnect(const QString host, const long port);
    void onDisconnect();
    void onSend(const char *data, long len);
    void onSend(const char *data);
    void onSend(QByteArray data);
    void onSend(QString data);

public slots:
    void onReceived();
    void onError(QAbstractSocket::SocketError);
};

#endif // UDPCLIENT_H
