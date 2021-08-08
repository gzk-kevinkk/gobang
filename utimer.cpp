#include "utimer.h"
#include <QString>
#include <QHBoxLayout>
#include <QLayout>

Utimer::Utimer()
{
    //初始化QLCDNumber
    lcd1.setDigitCount(1);
    lcd2.setDigitCount(1);
    lcd_m.setDigitCount(1);
    lcd3.setDigitCount(1);
    lcd4.setDigitCount(1);

    lcd1.display(0);
    lcd2.display(0);
    lcd_m.display(QString(":"));
    lcd3.display(0);
    lcd4.display(0);

    m_time = 0;
    m_timer = new QTimer(this);

    connect(m_timer,SIGNAL(timeout()),this,SLOT(subTime()));
}

void Utimer::set_lcd_color(QLCDNumber* lcd_m,const QColor&acolor)
{
    lcd_m->setSegmentStyle(QLCDNumber::Flat);
    //调色板
    QPalette lcdpat1 = lcd_m->palette();
    /*设置颜色，整体背景颜色 颜色蓝色,此函数的第一个参数可以设置多种。如文本、按钮按钮文字、多种*/
    lcdpat1.setColor(QPalette::Normal,QPalette::WindowText,acolor);
    //设置当前窗口的调色板
    lcd_m->setPalette(lcdpat1);
}

void Utimer::arrange(QWidget *widget)
{
    if(widget==nullptr)
        return;
    QLayout* layout;
    if(widget->layout()==nullptr)
    {
        layout = new QHBoxLayout();
        widget->setLayout(layout);
    }
    else
        layout = widget->layout();
    layout->addWidget(&lcd1);
    layout->addWidget(&lcd2);
    layout->addWidget(&lcd_m);
    layout->addWidget(&lcd3);
    layout->addWidget(&lcd4);
}

void Utimer::setTime(const unsigned int timee)
{
    m_time = timee;
}

void Utimer::showTime(const unsigned int time_in_s)
{
    int m = time_in_s/60;
    int s = time_in_s%60;

    lcd1.display(m/10);
    lcd2.display(m%10);
    lcd3.display(s/10);
    lcd4.display(s%10);
}

void Utimer::start()
{
    set_lcd_color(&lcd1,Qt::red);
    set_lcd_color(&lcd2,Qt::red);
    //set_lcd_color(&lcd_m,Qt::red);
    set_lcd_color(&lcd3,Qt::red);
    set_lcd_color(&lcd4,Qt::red);

    const int time_interval = 15;
    setTime(time_interval);
    showTime(time_interval);
    if(m_time && !m_timer->isActive())
        m_timer->start(1000);
    return;
}

void Utimer::subTime()
{
    m_time--;
    showTime(m_time);
    if(m_time==0)
        emit timeout();
}

void Utimer::end()
{
    m_timer->stop();
    set_lcd_color(&lcd1,Qt::black);
    set_lcd_color(&lcd2,Qt::black);
    //set_lcd_color(&lcd_m,Qt::black);
    set_lcd_color(&lcd3,Qt::black);
    set_lcd_color(&lcd4,Qt::black);
    lcd1.display(0);
    lcd2.display(0);
    lcd3.display(0);
    lcd4.display(0);
}
