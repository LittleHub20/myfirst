#include "flashbutton.h"

FlashButton::FlashButton(QWidget *parent) : QPushButton(parent)
{
    init();
}

FlashButton::FlashButton(const QString &text, QWidget *parent) : QPushButton(text, parent)
{
    init();
}

void FlashButton::init()
{
    m_nType = 0;
    m_nState = 0;
    m_nInterval = 100;
    m_nTextSize = 0;
    m_bFlashOnce = false;
    m_clrText[0] = QColor::fromRgbF(1,1,1);
    m_clrText[1] = QColor::fromRgbF(0,0,0);
    m_clrBack[0] = QColor::fromRgbF(0,0,0);
    m_clrBack[1] = QColor::fromRgbF(1,1,1);

    setContentsMargins(0, 0, 0, 0);
    connect(&m_timerFlash, SIGNAL(timeout()), this, SLOT(onTimer()));
}

void FlashButton::setType(int type)
{
    m_nType = type;
}

void FlashButton::setState(int state)
{
    m_nState = state;
}

void FlashButton::setInterval(int interval)
{
    m_nInterval = interval;
}

void FlashButton::setTextColor(QColor color[])
{
    m_clrText[0] = color[0];
    m_clrText[1] = color[1];
}

void FlashButton::setBackColor(QColor color[])
{
    m_clrBack[0] = color[0];
    m_clrBack[1] = color[1];
}

void FlashButton::setImage(QPixmap pixmap[])
{
    m_Pixmap[0] = pixmap[0];
    m_Pixmap[1] = pixmap[1];
}

void FlashButton::flash(bool start)
{
    if (start) {
        m_bFlashOnce = false;
        m_timerFlash.setInterval(m_nInterval/2);
        m_timerFlash.start();
    } else {
        m_timerFlash.stop();
    }
}

void FlashButton::flashOnce(int onset)
{
    m_nState = 1;
    update();
    m_bFlashOnce = true;
    m_timerFlash.setInterval(onset);
    m_timerFlash.start();
}

void FlashButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    int w = rect().width();
    int h = rect().height();
    m_nTextSize = w > h ? h : w;

    if (m_nType == 0) {

        painter.fillRect(rect(), QBrush(m_clrBack[m_nState]));
        m_fontText = font();
        m_fontText.setBold(true);
        m_fontText.setPointSize(0.8*m_nTextSize);
        painter.setFont(m_fontText);
        painter.setPen(QPen(m_clrText[m_nState]));
        painter.drawText(rect(), Qt::AlignCenter, text());

    } else if (m_nType == 1) {

        setIcon(m_Pixmap[m_nState]);
        setIconSize(QSize(w, h));

    }
}

void FlashButton::onTimer()
{
    if (m_bFlashOnce) { m_timerFlash.stop(); }
    m_nState = 1 - m_nState;
    update();
}
