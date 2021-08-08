#ifndef UTIMER_H
#define UTIMER_H

#include <QObject>
#include <QLCDNumber>
#include <QWidget>
#include <QTimer>

class Utimer : public QWidget
{
    Q_OBJECT
public:
    QLCDNumber lcd1;
    QLCDNumber lcd2;
    QLCDNumber lcd_m;
    QLCDNumber lcd3;
    QLCDNumber lcd4;

    Utimer();
    void arrange(QWidget* widget);
    void set_lcd_color(QLCDNumber*,const QColor&);
    void setTime(const unsigned int timee);

protected:
    int m_time;
    QTimer* m_timer;
    bool m_pause;

public slots:
    void start();
//    void pause();
    void end();
    void subTime();
    void showTime(const unsigned int time_in_s);
signals:
    void timeout();
};

#endif // UTIMER_H
