#include "shapedclock.h"
#include <QtWidgets>

ShapedClock::ShapedClock(QWidget* parent)
    :QWidget(parent,Qt::FramelessWindowHint | Qt::WindowSystemMenuHint)
{
    move_button = false;
    QTimer* timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(1000);

    QAction* quitAction = new QAction(tr("E&xit"),this);
    quitAction->setShortcut(tr("Ctrl+Q"));
    connect(quitAction,SIGNAL(triggered()),qApp,SLOT(quit()));
    addAction(quitAction);

    setContextMenuPolicy(Qt::ActionsContextMenu);
    setToolTip(tr("Drag the clock with the left mouse button.\n"
                  "Use the right mouse button to open a context menu."));
    setWindowTitle(tr("ShapedClock"));
}

QSize ShapedClock::sizeHint() const
{
    return QSize(200,200);
}

void ShapedClock::paintEvent(QPaintEvent*)
{
    static const QPoint hourHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -40)
    };
    static const QPoint minuteHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -70)
    };

    QColor hourColor(127, 0, 127);
    QColor minuteColor(0, 127, 127, 191);


    int side = qMin(width(), height());
    QTime time = QTime::currentTime();

    QPainter painter(this);
    //painter.fillRect(0, 0, width(), height(), QGradient::NightFade);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);

    painter.save();
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();

    painter.setPen(hourColor);

    for (int i = 0; i < 12; ++i) {
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);

    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();

    painter.setPen(minuteColor);

    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter.drawLine(92, 0, 96, 0);
        painter.rotate(6.0);
    }
    return;
}

void ShapedClock::resizeEvent(QResizeEvent*)
{
    int side = qMin(width(),height());
    QRegion region(width()/2-side/2,height()/2-side/2,side,side,QRegion::Ellipse);
    setMask(region);
    return;
}

void ShapedClock::mousePressEvent(QMouseEvent* event)
{
    if(!move_button)
        return;
    if(event->button()==Qt::LeftButton)
    {
        dragPosition = event->globalPos()-frameGeometry().topLeft();
        event->accept();
    }
    return;
}

void ShapedClock::mouseMoveEvent(QMouseEvent* event)
{
    if(!move_button)
        return;
    if(event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos()-dragPosition);
        event->accept();
    }
    return;
}

