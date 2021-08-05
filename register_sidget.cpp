#include "register_sidget.h"
#include "ui_register_sidget.h"
#include <QScreen>
#include <QRect>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <QDir>
#include <QMessageBox>
#include <QCoreApplication>
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::string;

Register_sidget::Register_sidget(QWidget *parent, Widget* w) :
    QWidget(parent),
    ui(new Ui::Register_sidget), login_window(w)
{
    ui->setupUi(this);
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect mm = screen->availableGeometry();
    int width = mm.width();
    int height = mm.height();
    int widget_width = width/4;
    int widget_height = height/4;
    setFixedSize(widget_width,widget_height);
    setWindowTitle(tr("注册"));

    setGeometry(3*width/8,3*height/8,
                width,height);
    width = this->width();
    height = this->height();
    widget_width = 9*width/10;
    widget_height = 9*height/10;
    ui->container_widget->setGeometry(width/20,height/20,widget_width,widget_height);

    ui->passwd_lineEdit->setEchoMode(QLineEdit::Password);
    ui->passwd_lineEdit2->setEchoMode(QLineEdit::Password);
    ui->registered_pushButton->setIcon(QIcon(":/myimage/image/111.ico"));
    ui->visible_pushButton->setIcon(QIcon(":/myimage/image/111.ico"));
    ui->visible_pushButton2->setIcon(QIcon(":/myimage/image/111.ico"));
    ui->visible_pushButton->installEventFilter(this);
    ui->visible_pushButton2->installEventFilter(this);
    ui->register_pushButton->installEventFilter(this);
    ui->caution_label->setText(QString(""));


    setAttribute(Qt::WA_DeleteOnClose,1);

}

Register_sidget::~Register_sidget()
{
    delete ui;
}

bool Register_sidget::eventFilter(QObject *obj, QEvent *e)
{
    if(obj==ui->visible_pushButton && e->type()==QEvent::Enter)
    {
        ui->passwd_lineEdit->setEchoMode(QLineEdit::Normal);
    }
    else if(obj==ui->visible_pushButton && e->type()==QEvent::Leave)
    {
        ui->passwd_lineEdit->setEchoMode(QLineEdit::Password);
    }
    else if(obj==ui->visible_pushButton2 && e->type()==QEvent::Enter)
    {
        ui->passwd_lineEdit2->setEchoMode(QLineEdit::Normal);
    }
    else if(obj==ui->visible_pushButton2 && e->type()==QEvent::Leave)
    {
        ui->passwd_lineEdit2->setEchoMode(QLineEdit::Password);
    }
    return QWidget::eventFilter(obj, e);
}

bool Register_sidget::regist_user()
{
    ui->caution_label->setStyleSheet("color:black;");
    ui->caution_label->setText(QString(""));
    ui->caution_label2->setStyleSheet("color:black;");
    ui->caution_label2->setText(QString(""));
    string s_path = QCoreApplication::applicationDirPath().toStdString();
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
    string target;
    string passwd;
    //std::cout << "Please enter the username." << std::endl;
    target = ui->name_lineEdit->text().toStdString();
    if(target.length()<5)
    {
        ui->caution_label->setStyleSheet("color:red;");
        ui->caution_label->setText(QString("名称必须大于等于5个字符!"));
    }
    passwd = ui->passwd_lineEdit->text().toStdString();
    if(passwd != ui->passwd_lineEdit2->text().toStdString())
    {
        ui->caution_label2->setStyleSheet("color:red;");
        ui->caution_label2->setText(QString("两次输入的密码不一致!"));
        return false;
    }
    if(passwd.length() < 8)
    {
        ui->caution_label2->setStyleSheet("color:red;");
        ui->caution_label2->setText(QString("密码的长度必须大于或等于8!"));
        return false;
    }
    while (getline(fi, temp))
    {
        stringstream sst_temp(temp);
        string name;
        sst_temp >> name;
        if(temp == target)
        {
            ui->caution_label->setStyleSheet("color:red;");
            ui->caution_label->setText(QString("该名称已存在!"));
            return false;
        }
    }
    fo << target << " " << passwd << std::endl;
    fo.close();
    fi.close();
    return true;
}

void Register_sidget::on_return_pushButton_clicked()
{
    login_window->reshow();
    close();
}


void Register_sidget::on_register_pushButton_clicked()
{
    if(regist_user())
        QMessageBox::information(NULL, tr("注册成功"), tr("注册成功"), \
                                 QMessageBox::Yes, QMessageBox::Yes);
}


void Register_sidget::on_registered_pushButton_clicked()
{
    ui->caution_label->setStyleSheet("color:black;");
    ui->caution_label->setText(QString(""));
    std::ifstream fi("/home/kevinkk/Desktop/self/qt_project/gobang/data/number.txt");
    std::ofstream fo("/home/kevinkk/Desktop/self/qt_project/gobang/data/number.txt", std::ofstream::app);
    string temp;
    string target;
    string passwd;
    //std::cout << "Please enter the username." << std::endl;
    target = ui->name_lineEdit->text().toStdString();

    //std::cout << QDir::currentPath().toStdString() << std::endl;
    while (getline(fi, temp))
    {
        stringstream sst_temp(temp);
        string name;
        sst_temp >> temp;
        if(temp == target)
        {
            ui->caution_label->setStyleSheet("color:red;");
            ui->caution_label->setText(QString("该名称已存在!"));
            return;
        }
    }
    {
        ui->caution_label->setStyleSheet("color:black;");
        ui->caution_label->setText(QString("该名称可以使用!"));
        return;
    }
}

