#ifndef FLASHBUTTON_H
#define FLASHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QTimer>

class FlashButton : public QPushButton
{
    Q_OBJECT
protected:
    int	m_nType;
    int	m_nState;
    int	m_nInterval;
    int m_nTextSize;
    bool m_bFlashOnce;
    QFont m_fontText;
    QColor m_clrText[2];
    QColor m_clrBack[2];
    QPixmap m_Pixmap[2];
    QTimer m_timerFlash;

public:
    explicit FlashButton(QWidget *parent = 0);
    explicit FlashButton(const QString &text = "", QWidget *parent = 0);

    void setType(int type);
    void setState(int state);
    void setInterval(int interval);
    void setTextColor(QColor color[]);
    void setBackColor(QColor color[]);
    void setImage(QPixmap pixmap[]);

    void flash(bool start);
    void flashOnce(int onset);

protected:
    void init();

    void paintEvent(QPaintEvent *e);

signals:

public slots:
    void onTimer();

};

#endif // FLASHBUTTON_H
