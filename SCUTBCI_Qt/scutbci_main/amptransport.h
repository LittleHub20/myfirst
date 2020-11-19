#ifndef AMPTRANSPORT_H
#define AMPTRANSPORT_H

#include <string.h>
#include <QtEndian>
#include <QMutex>
#include <QLinkedList>
#include "tcpclientmt.h"

// "CTRL" packet control codes
class CTRLCODE {
public:
    static const short GeneralControlCode  = 1;
    static const short ServerControlCode   = 2;
    static const short ClientControlCode   = 3;
};

// "CTRL" packet requests
class CTRLREQ {
public:
    static const short RequestForVersion   = 1;
    static const short ClosingUp           = 2;
    static const short ServerDisconnected  = 3;

    static const short StartAcquisition    = 1;
    static const short StopAcquisition     = 2;
    static const short StartImpedance      = 3;
    static const short ChangeSetup         = 4;
    static const short DCCorrection        = 5;

    static const short RequestEdfHeader    = 1;
    static const short RequestAstFile      = 2;
    static const short RequestStartData    = 3;
    static const short RequestStopData     = 4;
    static const short RequestBasicInfo    = 5;
};

// "DATA" packet codes and requests
class DATACODE {
public:
    static const short DataType_InfoBlock  = 1;
    static const short DataType_EegData    = 2;
};

class DATAREQ {
public:
    static const short InfoType_Version    = 1;
    static const short InfoType_EdfHeader  = 2;
    static const short InfoType_BasicInfo  = 3;

    static const short DataTypeRaw16bit    = 1;
    static const short DataTypeRaw32bit    = 2;
};

class AmpMessage
{
public:
    char	m_szId[4];		// ID string, no trailing '\0'
    short	m_nCode;		// Code
    short	m_nRequest;		// Request
    int 	m_nSize;		// Body size (in bytes)
    char*	m_pData;		// Ptr to body data

    bool    m_bHeaderReady;
    bool    m_bRecvComplete;

    // Construction
public:
    AmpMessage()
    {
        memset(m_szId, 0, 4);
        m_nCode = 0;
        m_nRequest = 0;
        m_nSize = 0;
        m_pData = 0;
        m_bHeaderReady = false;
        m_bRecvComplete = false;
    }

    AmpMessage(const char* id, short code, short request, int size)
    {
        memcpy(m_szId, id, 4);
        m_nCode = code;
        m_nRequest = request;
        m_nSize = size;
        m_pData = 0;
        m_bHeaderReady = true;
        m_bRecvComplete = false;
    }

    ~AmpMessage()
    {
        if (isValidPacket() && m_pData) delete m_pData;
        m_pData = 0;
    }

    // Header portion includes m_szId,m_nCode,m_nRequest,m_nSize
    int	getHeaderSize() { return 12; }
    bool isCtrlPacket() { return (!memcmp(m_szId, "CTRL", 4)); }
    bool isDataPacket() { return (!memcmp(m_szId, "DATA", 4)); }
    bool isValidPacket() { return m_nSize >= 0 && (isCtrlPacket() || isDataPacket()); }

    void convert(bool bSending)
    {
        if (bSending)
        {
            // Convert from host byte order to network  byte order (Little-Endian to Big-Endian)
            m_nCode = qToBigEndian(m_nCode);
            m_nRequest = qToBigEndian(m_nRequest);
            m_nSize = qToBigEndian(m_nSize);
        }
        else
        {
            // Convert from network byte order to host byte order (Big-Endian to Little-Endian)
            m_nCode = qFromBigEndian(m_nCode);
            m_nRequest = qFromBigEndian(m_nRequest);
            m_nSize = qFromBigEndian(m_nSize);
        }
    }
};

class AmpTransport : public QObject
{
    Q_OBJECT
protected:
    QString m_strStatus;
    TCPClientMT* m_pSocket;

    AmpMessage* m_pMsg;
    QMutex m_mutexMsg;
    QLinkedList<AmpMessage*> m_queueMsg;
    static const int m_nMaxMsg = 1000;

public:
    AmpTransport(QObject* parent = 0);

    void start(QString server, int port);
    void stop();
    bool isConnected();
    bool sendCommand(short command, short subtype);
    bool getData(char* data, int size);

protected:
    bool send(AmpMessage msg, char* buff);

    void onMessage(AmpMessage* pMsg);
    void addMessage(AmpMessage* pMsg);
    AmpMessage* removeMessage();
    void clearMessages();

signals:
    void connected();
    void disconnected();
    void error(int errorno, const QString errorstr);
    void ctrlpacket(AmpMessage* pMsg);
    void datapacket(AmpMessage* pMsg);

public slots:
    void onConnected();
    void onDisconnected();
    void onError(int errorno, QString errorstr);
    void onReceived(IOBuffer* buff);
};

#endif // AMPTRANSPORT_H
