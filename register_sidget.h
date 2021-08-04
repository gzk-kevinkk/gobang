#ifndef REGISTER_SIDGET_H
#define REGISTER_SIDGET_H

#include <QWidget>
#include "widget.h"
class Widget;

namespace Ui {
class Register_sidget;
}

class Register_sidget : public QWidget
{
    Q_OBJECT

public:
    explicit Register_sidget(QWidget *parent = nullptr, Widget* widget = nullptr);
    ~Register_sidget();
    bool eventFilter(QObject* obj,QEvent* );

private slots:
    void on_return_pushButton_clicked();

    void on_register_pushButton_clicked();

    void on_registered_pushButton_clicked();

private:
    Ui::Register_sidget *ui;
    Widget* login_window;
    bool regist_user();
};

#endif // REGISTER_SIDGET_H
