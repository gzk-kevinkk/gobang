#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QGuiApplication>
#include <QRect>
#include <QScreen>
#include <iostream>
#include <QLayout>
#include <QPoint>
#include <QDir>
#include <QCoreApplication>


GameWindow::GameWindow(QWidget *parent, Widget *last) :
    QMainWindow(parent),
    ui(new Ui::GameWindow), widget(last), clock(new ShapedClock())
{
    ui->setupUi(this);
    ui->ReturnButton->installEventFilter(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1);

    //自适应窗口大小设置，可适应多分辨率
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect rect = screen->availableGeometry();
    int screen_width = rect.width();
    int screen_height = rect.height();
    int widget_width = 7*screen_width/8;
    int widget_height = 7*screen_height/8;
    setGeometry((screen_width-widget_width)/2,(screen_height-widget_height)/2,
                widget_width,widget_height);

    QVBoxLayout* layout = new QVBoxLayout();

    //棋盘
    chessboard = new ChessBoard();
    int board_width = width()/2;
    int board_height = height();
    int chessboard_width = (board_width-10);
    int chessboard_height = (board_height-10);
    ui->board_widget->setGeometry((width()-chessboard_width)/2,(height()-chessboard_height)/2,
                                  chessboard_width,chessboard_height);
    ui->board_widget->setLayout(layout);
    int line_dis = chessboard_width/17;
    chessboard->get_dis(line_dis);
    chessboard->installEventFilter(this);

    //模式提示label
    label.setText(tr("模式：人机模式，玩家执黑"));
    rect = chessboard->geometry();
    QPoint point = rect.topLeft();
    int temp_width = label.width();
    int temp_height = label.height();
    label.setGeometry(point.x(),point.y(),temp_width,temp_height);

    //设置layout
    layout->addWidget(&label);
    layout->addWidget(chessboard);
    layout->setStretch(0,1);
    label.setMaximumHeight(30);
    layout->setStretch(1,10);

    //默认模式
    mode = 2;
    player_black = new HumanPlayer(1, chessboard);
    player_white = new HumanPlayer(2, chessboard);
    chessboard->get_player(player_black, player_white);

    //ActionGroup
    action_group = new QActionGroup(this);
    action_group->addAction(ui->hh_action);
    action_group->addAction(ui->h_black);
    action_group->addAction(ui->h_white);
    ui->hh_action->trigger();

//    std::cout << QCoreApplication::applicationDirPath().toStdString() << std::endl;
//    std::cout << QDir::currentPath().toStdString() << std::endl;

    //ShapedClock
    QVBoxLayout* clocklayout = new QVBoxLayout();
    ui->clock_widget -> setLayout(clocklayout);
    clocklayout->addWidget(clock);

    //计时器
    timer_black = new Utimer();
    timer_white = new Utimer();
    timer_black->arrange(ui->widget_2);
    timer_white->arrange(ui->widget_4);

    connect(timer_black, SIGNAL(timeout()), chessboard, SLOT(timelose()));
    connect(timer_white, SIGNAL(timeout()), chessboard, SLOT(timelose()));
    connect(player_black, SIGNAL(player_turn()), timer_black, SLOT(start()));
    connect(player_black, SIGNAL(player_turn()), timer_white, SLOT(end()));
    connect(player_white, SIGNAL(player_turn()), timer_white, SLOT(start()));
    connect(player_white, SIGNAL(player_turn()), timer_black, SLOT(end()));
    connect(chessboard, SIGNAL(game_over()), timer_black, SLOT(end()));
    connect(chessboard, SIGNAL(game_over()), timer_white, SLOT(end()));
}

GameWindow::~GameWindow()
{
    delete ui;
}

bool GameWindow::eventFilter(QObject *obj, QEvent *e)
{
    if(obj==ui->ReturnButton && e->type()==QEvent::KeyPress)
    {
        QKeyEvent* keyevent = static_cast<QKeyEvent*>(e);
        if(keyevent->key()==Qt::Key_Enter || keyevent->key()==Qt::Key_Return)
            on_ReturnButton_clicked();
    }
    return QWidget::eventFilter(obj, e);
}

void GameWindow::on_ReturnButton_clicked()
{
    close();
    widget->reshow();
}


void GameWindow::on_StartButton_clicked()
{
    if(chessboard->over == true)
    {
        chessboard->clear_board();
        std::cout << chessboard->dropEnable << std::endl;
        player_black->start();
        chessboard->over = false;
        chessboard->repaint();
    }
}

void GameWindow::on_RestartButton_clicked()
{
    chessboard->clear_board();
    player_black->start();
    chessboard->over = false;
    chessboard->repaint();
}

void GameWindow::on_ExitButton_clicked()
{
    widget->close();
    close();
}


void GameWindow::on_hh_action_triggered()
{
    label.setText(tr("模式：人人对战"));
}


void GameWindow::on_h_black_triggered()
{
    label.setText(tr("模式：人机模式，玩家执黑"));
}


void GameWindow::on_h_white_triggered()
{
    label.setText(tr("模式：人机模式，玩家执白"));
}

