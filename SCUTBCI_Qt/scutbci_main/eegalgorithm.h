#ifndef EEGALGORITHM_H
#define EEGALGORITHM_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "epochmanager.h"

class EEGAlgorithm : public QThread
{
    Q_OBJECT
public:
    static const int JOB_INIT = 1;
    static const int JOB_RESET = 2;
    static const int JOB_ROUND = 3;
    static const int JOB_EVALUATE = 4;

protected:
    int m_nEvent;
    int m_nEpochLen;
    float* m_pEpochData;

    int m_nJobType;
    bool m_bUserStop;
    QMutex m_mutexLock;
    QMutex m_mutexCall;
    QMutex m_mutexFinish;
    QWaitCondition m_eventCall;
    QWaitCondition m_eventFinish;

    int m_nResult;
    // AlgoParam mParam;
    // AlgoState mState;
    QString m_strModelPath;

public:
    EEGAlgorithm();
    ~EEGAlgorithm();

    bool call(int type, int timeout = 5000);
    void setInput(Epoch* epoch);
    int getResult();
    void resetResult();

protected:
    void init();
    void shutdown();
    void doJob(int type);
    void run();

public:

};

#endif // EEGALGORITHM_H
