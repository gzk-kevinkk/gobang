#ifndef PLAYER_H
#define PLAYER_H
#include "chessboard.h"
class ChessBoard;
#include <QObject>

class Player : public QObject
{
public:
    Player(int color, ChessBoard* chessboard);
    virtual void next() = 0;
    virtual void start() = 0;
    void increase_cnt(){
        chess_cnt++;
    }

protected:
    int chess_color; // 黑 1 白 2
    ChessBoard* chessboard;
    int chess_cnt; //步数
};

class HumanPlayer : public Player
{
    Q_OBJECT
public:
    HumanPlayer(int color, ChessBoard* chessboard);
    void next();
    void start();
signals:
    void player_turn();
};

#endif // PLAYER_H
