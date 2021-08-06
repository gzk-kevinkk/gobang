#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "widget.h"
#include <QWidget>
#include "chessboard.h"
#include <QLabel>
#include "player.h"
class Player;
class Widget;
class ChessBoard;

#include "shapedclock.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr, Widget *last = nullptr);
    ~GameWindow();
    bool eventFilter(QObject* obj, QEvent* e);

    ChessBoard * chessboard;

private slots:
    void on_ReturnButton_clicked();

    void on_StartButton_clicked();

    void on_RestartButton_clicked();

    void on_ExitButton_clicked();

    void on_hh_action_triggered();

    void on_h_black_triggered();

    void on_h_white_triggered();

private:
    Ui::GameWindow *ui;
    Widget* widget;
    int mode; // 人机（玩家黑）0  人机（玩家白）1  人人 2
    //ActionGroup
    QActionGroup* action_group;
    QLabel label;
    //Player
    Player* player_black;
    Player* player_white;
    //ShapedCLock
    ShapedClock* clock;
};

#endif // GAMEWINDOW_H
