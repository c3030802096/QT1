#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "Global.h"
#include "singleton.h"
namespace Ui {
class LoginWidget;
}

class Widget;
class LoginWidget : public QWidget, public Singleton<LoginWidget>
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

    static bool LoginSuccess;

signals:
    void sig_connect_tcp(std::shared_ptr<ServerInfo> si);
    void sig_switch_to_widget();
private slots:
    void on_LoginBtn_clicked();
    void slot_switch_OperaterWidget();
    void on_CancleRegisterBTn_clicked();
    void on_RegisterBtn_clicked();
    void on_UserRegisterBtn_clicked();
    void on_AdminRegisterBtn_clicked();
    void on_pwdcheckable_btn_clicked();
    void on_RegisterOKBtn_clicked();
    void on_pwdcheckable_btn_2_clicked();
    void on_pwdcheckable_btn_3_clicked();

private:
    Ui::LoginWidget *ui;

};

#endif // LOGINWIDGET_H
