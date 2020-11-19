#ifndef HRTIMER_H
#define HRTIMER_H

#include <QTimer>

class HRTimer : public QObject
{
    Q_OBJECT
protected:
    int m_nInterval; // milliseconds
    int m_nCounter;
    int m_nMaxInterval;
    QTimer m_timerMS;

public:
    explicit HRTimer(QObject *parent = 0);
    ~HRTimer();

    void setInterval(long interval);
    void start();
    void stop();

signals:
    void timeout();

public slots:
    void onTimer();
};

#endif // HRTIMER_H
