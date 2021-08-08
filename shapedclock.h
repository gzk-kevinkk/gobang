#ifndef SHAPEDCLOCK_H
#define SHAPEDCLOCK_H

#include <QWidget>

#include <QWidget>

class ShapedClock : public QWidget
{
    Q_OBJECT
public:
    ShapedClock(QWidget *parent = nullptr);
    QSize sizeHint() const override;
protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
private:
    QPoint dragPosition;
    bool move_button;
};

#endif // SHAPEDCLOCK_H
