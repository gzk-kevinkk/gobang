#include "player.h"

Player::Player(int color, ChessBoard* chessboard)
{
    chess_color = color;
    this->chessboard = chessboard;
    chess_cnt = 0;
};

HumanPlayer::HumanPlayer(int color, ChessBoard* chessboard)
    : Player(color, chessboard)
{

}

void HumanPlayer::next()
{
    return;
}

void HumanPlayer::start()
{
    chessboard->dropFlag = true;
}

