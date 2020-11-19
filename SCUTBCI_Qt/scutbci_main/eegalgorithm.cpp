#include "eegalgorithm.h"

EEGAlgorithm::EEGAlgorithm()
{
    m_nEpochLen = 0;
    m_pEpochData = 0;
    init();
}

EEGAlgorithm::~EEGAlgorithm()
{
    shutdown();
}

void EEGAlgorithm::init()
{
    m_bUserStop = false;
    m_mutexCall.lock();
    m_mutexFinish.lock();
    start();
}

void EEGAlgorithm::shutdown()
{
    m_bUserStop = true;
    m_eventCall.wakeAll();
    m_eventFinish.wakeAll();
}

bool EEGAlgorithm::call(int type, int timeout)
{
    m_nJobType = type;
    m_eventCall.wakeOne();
    if (m_eventFinish.wait(&m_mutexFinish, timeout)) {
        return true;
    }
    return false;
}

void EEGAlgorithm::run()
{
    while (1) {
        m_eventCall.wait(&m_mutexCall);

        if (m_bUserStop) break;

        m_mutexLock.lock();
        doJob(m_nJobType);
        m_mutexLock.unlock();

        m_eventFinish.wakeOne();
    }
}

void EEGAlgorithm::doJob(int type)
{
    switch (type)
    {
    case JOB_INIT:
        qDebug("JOB_INIT called");
        break;
    case JOB_RESET:
        qDebug("JOB_RESET called");
        break;
    case JOB_ROUND:
        qDebug("JOB_ROUND called");
        break;
    case JOB_EVALUATE:
        qDebug("JOB_EVALUATE called");
        break;
    }
}

void EEGAlgorithm::setInput(Epoch* epoch)
{
    m_mutexLock.lock();
    m_nEpochLen = epoch->epochlen;
    m_nEvent = epoch->event;
    m_pEpochData = epoch->data;
    m_mutexLock.unlock();
}

int EEGAlgorithm::getResult()
{
    m_mutexLock.lock();
    return m_nResult;
    m_mutexLock.unlock();
}

void EEGAlgorithm::resetResult()
{
    m_mutexLock.lock();
    m_nResult = -1;
    m_mutexLock.unlock();
}
