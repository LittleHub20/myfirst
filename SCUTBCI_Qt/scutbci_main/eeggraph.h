#ifndef EEGGRAPH_H
#define EEGGRAPH_H

#include <QWidget>
#include <QTimerEvent>

class EEGGraph : public QWidget
{
    Q_OBJECT
protected:
    int m_nChannels;
    int m_nTotalPoints;
    int* m_pData;
    float m_fScale;

    int m_timerUpdate;

public:
    explicit EEGGraph(QWidget *parent = 0);

public:
    void init(int channels, int points, float scale);
    void setScale(float scale);
    void setPoints(int points);
    void setDataSource(int*);
    void startUpdate(bool bStart=true);

protected:
    void drawWaves();

    void paintEvent(QPaintEvent *e);
    void timerEvent(QTimerEvent *e);

signals:

public slots:
};

#endif // EEGGRAPH_H
