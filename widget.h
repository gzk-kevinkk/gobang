#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "gamewindow.h"
class GameWindow;
#include <QPaintEvent>
#include <QPainter>
#include "register_sidget.h"
class Register_sidget;

QT_BEGIN_NAMESPACE
namespace Ui {
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    bool eventFilter(QObject* obj, QEvent* e);
    void paintEvent(QPaintEvent* e);
    void reshow();
    void del();

private slots:
    void on_ExitButton_clicked();

    void on_LoginButton_clicked();

    void on_RegisterButton_clicked();

    void on_TouristButton_clicked();

private:
    Ui::Widget *ui;
    GameWindow* game_window;
    Register_sidget* register_window;
    bool judge_login();
    void game_window_open();
};
#endif // WIDGET_H
