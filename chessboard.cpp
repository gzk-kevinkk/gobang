#include "chessboard.h"
#include <iostream>

ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent)
{
    cnt = 0;
    int i, j;
    for (i = 0; i < 15;i++)
    {
        for (j = 0; j < 15;j++)
        {
            board[i][j] = 0;
        }
    }
    board[7][7]=1;
    board[6][9]=2;

    over = true;
    dropEnable = false;
    dropFlag = false;
    //important 为了不消耗资源，此项默认为false
    setMouseTracking(true);
    cur_chess_x = -100;
    cur_chess_y = -100;


};

void ChessBoard::generate_board()
{
    QFont font("宋体",15,QFont::Black,false);
    font.setCapitalization(QFont::SmallCaps);
    font.setLetterSpacing(QFont::AbsoluteSpacing,25);
    paint->setFont(font);
    paint->setRenderHint(QPainter::Antialiasing);
    paint->setPen(QPen(Qt::black,2,Qt::SolidLine));//钢笔工具：颜色，线号，实线
    //画SIZE+1条横线
    for(int i=0;i<SIZE;i++)
    {
        paint->drawLine(x,y+WIDTH*i,x+WIDTH*(SIZE-1),y+WIDTH*i);//画线函数：x1,y1,x2,y2:画从(x1,y1)到(x2,y2)的线
    }
    //画SIZE+1条竖线
    for(int i=0;i<SIZE;i++)
    {
        paint->drawLine(x+WIDTH*i,y,x+WIDTH*i,y+WIDTH*(SIZE-1));
    }

    //在棋盘正中做一个黑棋子
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            if(board[i][j] == 1)
            {
                paint->setPen(QPen(Qt::black,2,Qt::SolidLine));//钢笔工具：颜色，线号，实线
                paint->setBrush(QBrush(Qt::black,Qt::SolidPattern));//毛刷：颜色，实图案
                //paint->drawEllipse((2.0*i+0.2)*WIDTH/2,(2.0*j+0.2)*WIDTH/2+5.0,WIDTH/1.25,WIDTH/1.25);//画椭圆：中心点X,Y,宽度，高度
                paint->drawEllipse(1.0*x+i*WIDTH-0.4*WIDTH,j*WIDTH+1.0*y-0.4*WIDTH,WIDTH*0.8,WIDTH*0.8);//画椭圆：中心点X,Y,宽度，高度
                //paint->drawEllipse((SIZE)*WIDTH/2,(SIZE)*WIDTH/2,WIDTH*2,WIDTH*2);//画椭圆：中心点X,Y,宽度，高度
                paint->setPen(QPen(Qt::white,1,Qt::SolidLine));//钢笔工具：颜色，线号，实线

            }
            else if(board[i][j] == 2)
            {
                paint->setPen(QPen(Qt::black,2,Qt::SolidLine));//钢笔工具：颜色，线号，实线
                paint->setBrush(QBrush(Qt::white,Qt::SolidPattern));//毛刷：颜色，实图案
                //paint->drawEllipse((2.0*i+0.2)*WIDTH/2,(2.0*j+0.2)*WIDTH/2+5.0,WIDTH/1.25,WIDTH/1.25);//画椭圆：中心点X,Y,宽度，高度
                paint->drawEllipse(1.0*x+i*WIDTH-0.4*WIDTH,j*WIDTH+1.0*y-0.4*WIDTH,WIDTH*0.8,WIDTH*0.8);//画椭圆：中心点X,Y,宽度，高度
                //paint->drawEllipse((SIZE)*WIDTH/2,(SIZE)*WIDTH/2,WIDTH*2,WIDTH*2);//画椭圆：中心点X,Y,宽度，高度
                paint->setPen(QPen(Qt::black,1,Qt::SolidLine));//钢笔工具：颜色，线号，实线
            }
            if(cur_chess_x==i && cur_chess_y==j)
            {
                paint->drawLine(1.0*x+i*WIDTH,j*WIDTH+1.0*y-0.2*WIDTH,1.0*x+i*WIDTH-0.2*WIDTH,j*WIDTH+1.0*y+0.14*WIDTH);
                paint->drawLine(1.0*x+i*WIDTH-0.2*WIDTH,j*WIDTH+1.0*y+0.14*WIDTH,1.0*x+i*WIDTH+0.2*WIDTH,j*WIDTH+1.0*y+0.14*WIDTH);
                paint->drawLine(1.0*x+i*WIDTH+0.2*WIDTH,j*WIDTH+1.0*y+0.14*WIDTH,1.0*x+i*WIDTH,j*WIDTH+1.0*y-0.2*WIDTH);
            }
        }
    }

}

void ChessBoard::paintEvent(QPaintEvent *)
{
    paint=new QPainter;
    paint->begin(this);//主窗口

    generate_board();


    paint->end();
    //delete paint;
    paint = nullptr;

}

void ChessBoard::get_dis(int dis)
{
    std::cout<<dis<<std::endl;
    WIDTH = dis;
    x = dis;
    y = dis;
}

void ChessBoard::mouseMoveEvent(QMouseEvent* e)
{
    if(over || !dropFlag)
    {
        return;
    }

#if 1
    cur_x = e->x();
    cur_y = e->y();
    //std::cout<<cur_x<<std::endl;
    int res = (cur_x+100*WIDTH-x)%WIDTH;
    if(res>tol && res<WIDTH-tol)
    {
        dropEnable = false;
        //std::cout<<1<<std::endl;
        setCursor(Qt::ArrowCursor);
        return;
    }
    cur_x_i = (cur_x+tol-x)/WIDTH;
    if(cur_x_i<0 || cur_x_i>=SIZE)
    {
        dropEnable = false;
        //std::cout<<2<<std::endl;
        setCursor(Qt::ArrowCursor);
        return;
    }
    res = (cur_y+100*WIDTH-y)%WIDTH;
    if(res>tol && res<WIDTH-tol)
    {
        dropEnable = false;
        //std::cout<<3<<std::endl;
        setCursor(Qt::ArrowCursor);
        return;
    }
    cur_y_i = (cur_y+tol-y)/WIDTH;
    if(cur_y_i<0 || cur_y_i>=SIZE)
    {
        dropEnable = false;
        //std::cout<<4<<std::endl;
        setCursor(Qt::ArrowCursor);
        return;
    }
    if(board[cur_x_i][cur_y_i]!=0)
    {
        dropEnable = false;
        //std::cout<<5<<std::endl;
        setCursor(Qt::ArrowCursor);
        return;
    }
    dropEnable = true;
    setCursor(Qt::PointingHandCursor);
    //std::cout<<"here"<<std::endl;
#endif
    return;
}

void ChessBoard::mousePressEvent(QMouseEvent* )
{
    //std::cout << dropEnable << std::endl;
    if(!over && dropFlag && dropEnable)
    {
        if(cnt%2==0)
        {
            player_black->next();
            cur_chess_x = cur_x_i;
            cur_chess_y = cur_y_i;
            board[cur_x_i][cur_y_i]=1;
            judge();
            if(!over)
                player_white->start();
        }
        else
        {
            player_white->next();
            cur_chess_x = cur_x_i;
            cur_chess_y = cur_y_i;
            board[cur_x_i][cur_y_i]=2;
            judge();
            if(!over)
                player_black->start();
        }
        cnt++;
        update();
    }
#if 0
    cur_x = e->x();
    cur_y = e->y();
    std::cout<<cur_x<<std::endl;
#endif
}

void ChessBoard::clear_board()
{
    cnt = 0;
    int i, j;
    for (i = 0; i < 15;i++)
    {
        for (j = 0; j < 15;j++)
        {
            board[i][j] = 0;
        }
    }
    over = true;
    dropEnable = false;
    dropFlag = false;
}

void ChessBoard::get_player(Player* black, Player* white)
{
    player_black = black;
    player_white = white;
}

int ChessBoard::find_chess(int x,int y,int dir)
{
    int dir_x = 0;
    int dir_y = 0;
    switch(dir){
    case 0:
        dir_x = 1;
        dir_y = 0;
        break;
    case 1:
        dir_x = 0;
        dir_y = 1;
        break;
    case 2:
        dir_x = 1;
        dir_y = 1;
        break;
    case 3:
        dir_x = 1;
        dir_y = -1;
        break;
    }
    int color = board[cur_x_i][cur_y_i];
    int head_x = cur_x_i;
    int head_y = cur_y_i;
    while(head_x>0 && head_y>0 && head_y<SIZE-1)
    {
        if(color == board[head_x-dir_x][head_y-dir_y])
        {
            head_x -= dir_x;
            head_y -= dir_y;
        }
        else
            break;
    }
    int length = 0;
    while(head_x<SIZE && head_y>=0 && head_y<SIZE)
    {
        if(board[head_x][head_y]!=color)
            break;
        length++;
        head_x += dir_x;
        head_y += dir_y;
    }
    return length;
}

void ChessBoard::judge()
{
    for(int i=0;i<4;i++)
    {
        int temp_tot = find_chess(cur_x_i,cur_y_i,i);
        if(temp_tot>=5)
        {
            over = true;
            setMouseTracking(false);
            setCursor(Qt::ArrowCursor);
            emit game_over();
            return;
        }
    }
}

//void ChessBoard::game_over()
//{
//    over = true;
//    dropEnable = false;
//    dropFlag = false;
//}

void ChessBoard::timelose()
{

}


