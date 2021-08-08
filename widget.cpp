#include "widget.h"
#include "ui_widget.h"
#include <QScreen>
#include <QDebug>
#include <QGuiApplication>
#include <QSizePolicy>
#include <QMovie>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <QMessageBox>
#include <QIcon>
using std::ifstream;
using std::ofstream;
using std::string;


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget), game_window(nullptr), register_window(nullptr)
{
    ui->setupUi(this);
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect mm = screen->availableGeometry();
    int screen_width = mm.width();
    int screen_height = mm.height();
    int widget_width = screen_width/7;
    int widget_height = screen_height/6;
    setFixedSize(widget_width,widget_height);

    setGeometry(screen_width/2,(screen_height-widget_height)/2,
                widget_width,widget_height);
    setWindowTitle(tr("五子棋"));


    //EventFilter
    ui->LoginButton->installEventFilter(this);
    ui->VisibileButton->installEventFilter(this);
    ui->ExitButton->installEventFilter(this);
    ui->TouristButton->installEventFilter(this);
    ui->RegisterButton->installEventFilter(this);

    setWindowIcon(QIcon(":/myimage/image/2.ico"));
    ui->VisibileButton->setIcon(QIcon(":/myimage/image/111.ico"));
    ui->PasswdEdit->setEchoMode(QLineEdit::Password);
    //ui->VisibileButton->setDisabled(true);
    //QMovie* movie=new QMovie("myimage/image/pic1.gif");
}

Widget::~Widget()
{
    delete ui;
}

bool
Widget::eventFilter(QObject* target, QEvent* event)
{
    if(target==ui->ExitButton && event->type()==QEvent::KeyPress)
    {
        QKeyEvent* keyevent = static_cast<QKeyEvent*>(event);
        if(keyevent->key()==Qt::Key_Enter || keyevent->key()==Qt::Key_Return)
            on_ExitButton_clicked();
    }
    else if(target==ui->LoginButton && event->type()==QEvent::KeyPress)
    {
        QKeyEvent* keyevent = static_cast<QKeyEvent*>(event);
        if(keyevent->key()==Qt::Key_Enter || keyevent->key()==Qt::Key_Return)
            on_LoginButton_clicked();
    }
    else if(target==ui->TouristButton && event->type()==QEvent::KeyPress)
    {
        QKeyEvent* keyevent = static_cast<QKeyEvent*>(event);
        if(keyevent->key()==Qt::Key_Enter || keyevent->key()==Qt::Key_Return)
            on_TouristButton_clicked();
    }
    else if(target==ui->RegisterButton && event->type()==QEvent::KeyPress)
    {
        QKeyEvent* keyevent = static_cast<QKeyEvent*>(event);
        if(keyevent->key()==Qt::Key_Enter || keyevent->key()==Qt::Key_Return)
            on_RegisterButton_clicked();
    }
    else if(target==ui->VisibileButton && event->type()==QEvent::Enter)
    {
        ui->PasswdEdit->setEchoMode(QLineEdit::Normal);
    }
    else if(target==ui->VisibileButton && event->type()==QEvent::Leave)
    {
        ui->PasswdEdit->setEchoMode(QLineEdit::Password);
    }
    return QWidget::eventFilter(target,event);
}

bool
Widget::judge_login()
{
    std::string s_path = QCoreApplication::applicationDirPath().toStdString();
    s_path += "/../gobang/data/number.txt";
#if 1
    std::cout << s_path << std::endl;
    ifstream fi(s_path);
    ofstream fo(s_path, ofstream::app);
#else
    ifstream fi("/home/kevinkk/Desktop/self/../self/qt_project/gobang/data/number.txt");
    ofstream fo("/home/kevinkk/Desktop/self/qt_project/gobang/data/number.txt", ofstream::app);
#endif
    string temp;
    string::iterator it;
    string target;
    string::iterator it2;
    string passwd;
    //std::cout << "Please enter the username." << std::endl;
    target = ui->NameEdit->text().toStdString();
    bool cond1 = false;
    bool cond2 = false;
    // if (target == "huyukuan")
    //     std::cout << 111 << std::endl;
    while (getline(fi, temp))
    {
        it = temp.begin();
        it2 = target.begin();
        while (it2 != target.end() && it != temp.end())
        {
            if(*it++!=*it2++)
                break;
        }
        if(it!=temp.end() && *it==' ')
        {
            cond1 = true;
            //std::cout << "Please enter the passwd." << std::endl;
            passwd = ui->PasswdEdit->text().toStdString();
            it++;
            it2 = passwd.begin();
            while (it2 != passwd.end() && it != temp.end())
            {
                if (*it++ != *it2++)
                    break;
            }
            if (it == temp.end() && it2 == passwd.end())
                cond2 = true;
            break;
        }
    }
#if 1
    if(!cond1)
        std::cout << "Username isn't registered!" << std::endl;
    else if(!cond2)
        std::cout << "Password isn't right!" << std::endl;
    else
        std::cout << "Register successfully!" << std::endl;
#endif
    if(cond1 && cond2)
        return true;
    return false;
}

void
Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/myimage/image/pic1.gif"));
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/myimage/bg.png"));
    //    QMovie* movie=new QMovie(":/myimage/image/pic1.gif");
    //    ui->Namelabel->setMovie(movie);
    //    movie->start();
    return;
}

void
Widget::game_window_open()
{
    if(game_window==nullptr)
        game_window = new GameWindow(nullptr,this);
    game_window->show();
    game_window->chessboard->clear_board();
    game_window->chessboard->repaint();
    close();
}

void
Widget::reshow()
{
    ui->NameEdit->clear();
    ui->PasswdEdit->clear();
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect mm = screen->availableGeometry();
    int screen_width = mm.width();
    int screen_height = mm.height();
    int widget_width = screen_width/7;
    int widget_height = screen_height/6;
    setFixedSize(widget_width,widget_height);

    setGeometry(screen_width/2,(screen_height-widget_height)/2,
                widget_width,widget_height);
    if(register_window)
        delete(register_window);
    register_window = nullptr;
//    if(game_window)
//        delete(game_window);
//    game_window = nullptr;
    show();
#if 0
    //game_window = nullptr;
    std::cout<<"delete game_window"<<std::endl;
#endif

}

void
Widget::on_ExitButton_clicked()
{
    close();
}

void
Widget::on_LoginButton_clicked()
{
    if(judge_login())
    {
        game_window_open();
    }
    else
    {
        QMessageBox::warning(NULL, tr("警告"), tr("用户名不存在或者密码错误"), \
                                 QMessageBox::Yes, QMessageBox::Yes);
    }
}

void Widget::on_RegisterButton_clicked()
{
    register_window = new Register_sidget(nullptr, this);
    register_window->show();
    close();
}

void Widget::del()
{
    if(game_window)
    {
        delete game_window;
        game_window = nullptr;
    }
}


void Widget::on_TouristButton_clicked()
{
    game_window_open();
}

