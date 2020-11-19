#ifndef NETMARKER_H
#define NETMARKER_H

#include <QDialog>
#include <QThread>
#include <qtconcurrentrun.h>
#include <QLinkedList>
#include "udpclient.h"
#include "tcpclientmt.h"

namespace Ui {
class NetMarker;
}

class NetMarker : public QDialog
{
    Q_OBJECT

    class Worker : public QThread
    {
    public:
        Worker(NetMarker *parent = 0) { this->parent = parent; }
    protected:
        NetMarker* parent;
        void run() { parent->worker(); }
    };

    static const int MODE_LOCAL = 1;
    static const int MODE_REMOTE = 2;

public:
    int m_nMode;
    int m_nPort;
    QString m_strServer;
    UDPClient* m_pSocket;
    // TCPClientMT* m_pSocket;

    int m_nEvent;
    bool m_bRunning;
    QMutex m_mutexEvent;
    QLinkedList<int> m_queueEvent;
    QFuture<void> m_WorkThread;

public:
    explicit NetMarker(QWidget *parent = 0);
    ~NetMarker();

    bool isConnected();
    void setMode(int mode);
    void outputEvent(int event);

protected:
    void enableControls(bool bConnected);

    void worker();
    void sendEvent(int event);
    void setEvent(int event);
    int getEvent(bool bRemove = true);
    void clearEvents();

signals:

private slots:
    void on_btnConnect_clicked();
    void on_btnHide_clicked();
    void on_btnSend_clicked();

    void onConnected();
    void onDisconnected();

private:
    Ui::NetMarker *ui;
};

#endif // NETMARKER_H
