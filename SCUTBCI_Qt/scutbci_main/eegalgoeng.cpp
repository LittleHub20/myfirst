#include "eegalgoeng.h"

EEGAlgoEng::EEGAlgoEng()
{
    m_nEvent = -1;
    m_nChannels = 0;
    m_nDataPoints = 0;
    m_pEpochData = 0;
    m_nResult = -1;
    setup();
}

EEGAlgoEng::~EEGAlgoEng()
{
    shutdown();
}

void EEGAlgoEng::setup()
{
    m_bUserStop = false;
    m_mutexCall.lock();
    m_mutexFinish.lock();
    start();
}

void EEGAlgoEng::shutdown()
{
    m_bUserStop = true;
    m_eventCall.wakeAll();
    m_eventFinish.wakeAll();
    wait();
    m_mutexCall.unlock();
    m_mutexFinish.unlock();
}

bool EEGAlgoEng::call(int type, int timeout)
{
    m_nJobType = type;
    m_eventCall.wakeOne();
    if (m_eventFinish.wait(&m_mutexFinish, timeout)) {
        return true;
    }
    return false;
}

void EEGAlgoEng::run()
{
    qDebug("EEGAlgoEng::run: thread started: 0x%x", (uint)QThread::currentThreadId());
    while (1) {
        m_eventCall.wait(&m_mutexCall);

        if (m_bUserStop) break;

        m_mutexLock.lock();
        doJob(m_nJobType);
        m_mutexLock.unlock();

        m_eventFinish.wakeOne();
    }
    qDebug("EEGAlgoEng::run: thread stopped: 0x%x", (uint)QThread::currentThreadId());
}

void EEGAlgoEng::doJob(int type)
{
    switch (type)
    {
    case JOB_INIT:
        init();
        break;
    case JOB_RESET:
        reset();
        break;
    case JOB_ROUND:
        round();
        break;
    case JOB_EVALUATE:
        evaluate();
        break;
    }
}

void EEGAlgoEng::setSubject(QString subject)
{
    m_strSubject = subject;
}

void EEGAlgoEng::setModelPath(QString modelpath)
{
    m_strModelPath = modelpath;
}

void EEGAlgoEng::recvEpoch(int event, float* epoch, int channels, int points)
{
    m_mutexLock.lock();
    m_nEvent = event;
    if ((m_nChannels != channels) || (m_nDataPoints != points)) {
        m_nChannels = channels;
        m_nDataPoints = points;
        if (m_pEpochData) {
            delete m_pEpochData;
            m_pEpochData = 0;
        }
    }
    if (!m_pEpochData) m_pEpochData = new double[channels*points];

    for (int i=0; i<channels; i++)
    {
        for (int j=0; j<points; j++)
        {
            m_pEpochData[j*channels+i] = epoch[j*channels+i];
        }
    }
    m_mutexLock.unlock();
}

int EEGAlgoEng::getResult()
{
    int result = -1;
    m_mutexLock.lock();
    result = m_nResult;
    m_mutexLock.unlock();
    return result;
}

void EEGAlgoEng::resetResult()
{
    m_mutexLock.lock();
    m_nResult = -1;
    m_mutexLock.unlock();
}
