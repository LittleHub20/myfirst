#include "hrtimer.h"

HRTimer::HRTimer(QObject *parent) :
    QObject(parent)
{
    m_nInterval = 1;
    // Qt use multimedia timer automatically
    // when the interval is less than 20ms
    m_nMaxInterval = 19;
    connect(&m_timerMS, SIGNAL(timeout()), this, SLOT(onTimer()));
}

HRTimer::~HRTimer()
{
    stop();
}

void HRTimer::setInterval(long interval)
{
    m_nInterval = interval;
}

void HRTimer::start()
{
    // Qt use multimedia timer automatically
    // when the interval is less than 20ms
    if (m_nInterval <= m_nMaxInterval) {
        m_timerMS.setInterval(m_nInterval);
    } else {
        m_nCounter = m_nMaxInterval;
        m_timerMS.setInterval(m_nMaxInterval);
    }
    m_timerMS.start();
}

void HRTimer::stop()
{
    m_timerMS.stop();
}

void HRTimer::onTimer()
{
    // Qt use multimedia timer automatically
    // when the interval is less than 20ms
    if (m_nInterval <= m_nMaxInterval) {
        emit timeout();
    } else {
        if (m_nCounter + m_nMaxInterval <= m_nInterval) {
            m_nCounter += m_nMaxInterval;
        } else {
            m_timerMS.start(m_nInterval - m_nCounter);
            m_nCounter = m_nInterval - m_nMaxInterval;
        }

        if (m_nCounter >= m_nInterval) {
            emit timeout();
            m_timerMS.start(m_nMaxInterval);
            m_nCounter = m_nMaxInterval;
        }
    }
}

