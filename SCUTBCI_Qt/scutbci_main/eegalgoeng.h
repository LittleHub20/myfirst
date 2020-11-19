#ifndef EEGALGOENG_H
#define EEGALGOENG_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class EEGAlgoEng : public QThread
{
    Q_OBJECT
public:
    static const int JOB_INIT = 1;
    static const int JOB_RESET = 2;
    static const int JOB_ROUND = 3;
    static const int JOB_EVALUATE = 4;

protected:
    int m_nJobType;
    bool m_bUserStop;
    QMutex m_mutexLock;
    QMutex m_mutexCall;
    QMutex m_mutexFinish;
    QWaitCondition m_eventCall;
    QWaitCondition m_eventFinish;

    int m_nEvent;
    int m_nChannels;
    int m_nDataPoints;
    double* m_pEpochData;
    int m_nResult;
    QString m_strSubject;
    QString m_strModelPath;

public:
    EEGAlgoEng();
    ~EEGAlgoEng();

    bool call(int type, int timeout = 5000);
    void setSubject(QString subject);
    void setModelPath(QString modelpath);
    void recvEpoch(int event, float* epoch, int channels, int points);
    int getResult();
    void resetResult();

protected:
    void setup();
    void shutdown();
    void doJob(int type);
    void run();

    virtual void init() = 0;
    virtual void reset() = 0;
    virtual void round() = 0;
    virtual void evaluate() = 0;
};

#endif // EEGALGOENG_H
