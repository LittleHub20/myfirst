#include "eeggraph.h"
#include <QStyleOption>
#include <QPainter>

EEGGraph::EEGGraph(QWidget *parent) : QWidget(parent)
{
    m_nChannels = 0;
    m_nTotalPoints = 0;
    m_fScale = 1;

    m_timerUpdate = 0;
}

void EEGGraph::paintEvent(QPaintEvent*)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    p.setClipping(true);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    drawWaves();
}

void EEGGraph::timerEvent(QTimerEvent *e)
{
    if (e->timerId() == m_timerUpdate) {
        update();
    }
}

void EEGGraph::init(int channels, int points, float scale)
{
    m_nChannels = channels;
    m_nTotalPoints = points;
    m_fScale = scale;
}

void EEGGraph::setScale(float scale)
{
    m_fScale = scale;
}

void EEGGraph::setPoints(int points)
{
    m_nTotalPoints = points;
}

void EEGGraph::setDataSource(int* pData)
{
    m_pData = pData;
}

void EEGGraph::drawWaves()
{
    if (m_pData == 0) return;
    if (m_nChannels > 0 && m_nTotalPoints > 0) {

        QRect rc = rect();
        QPainter p(this);
        QPixmap pixmem(rc.width(), rc.height());
        QPainter pmem(&pixmem);

        pmem.fillRect(rc, QBrush(QColor::fromRgbF(1,1,1)));
        pmem.setPen(QColor(Qt::black));

        for (int i=0; i<m_nChannels; i++)
        {
            int baseline = rc.top() + (i+0.5)*rc.height()/m_nChannels;
            for (int j=1; j<m_nTotalPoints; j++)
            {
                int x1 = (j-1)*rc.width()/(m_nTotalPoints-1);
                int x2 = j*rc.width()/(m_nTotalPoints-1);
                int y1 = baseline + (int)(m_pData[(j-1)*m_nChannels+i]*m_fScale+0.5f);
                int y2 = baseline + (int)(m_pData[(j)*m_nChannels+i]*m_fScale+0.5f);
                QPoint pt1(x1, y1);
                QPoint pt2(x2, y2);
                pmem.drawLine(pt1, pt2);
            }
        }

        p.drawPixmap(0, 0, pixmem);
    }
}

void EEGGraph::startUpdate(bool bStart)
{
    if (bStart) {
        m_timerUpdate = startTimer(50);
    } else {
        killTimer(m_timerUpdate);
    }
}
