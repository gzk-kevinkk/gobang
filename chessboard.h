#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QActionGroup>
#include "player.h"
class Player;

class ChessBoard : public QWidget
{
    Q_OBJECT
public:
    friend class GameWindow;
    friend class HumanPlayer;

    explicit ChessBoard(QWidget *parent = nullptr);
    void get_dis(int dis);
    void get_player(Player*,Player*);
    void judge(); //判断胜负
    void clear_board();

signals:
    void game_over();

public slots:
    void timelose();

private:
    int board[15][15]; //棋局
    int cnt; //步数
    QPainter* paint; //棋盘画图工具
    //棋盘大小及画棋盘参数
    const int SIZE=15;
    int WIDTH;
    int x,y;
    const int tol = 10;
    //形势判断和是否能落子
    bool over;
    bool dropEnable;
    bool dropFlag;

    //鼠标坐标
    int cur_x;
    int cur_y;
    int cur_x_i;
    int cur_y_i;
    //当前棋子坐标
    int cur_chess_x;
    int cur_chess_y;
    //Player
    Player* player_black;
    Player* player_white;

    void paintEvent(QPaintEvent *);//绘图函数声明
    void generate_board();
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);

    int find_chess(int x,int y,int dir);
};

#endif // CHESSBOARD_H
