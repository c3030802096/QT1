#include "LoginWidget.h"
#include "ui_LoginWidget.h"
#include "TcpMgr.h"
#include "OperaterWidget.h"
#include "DateBaseMgr.h"
#include <QMessageBox>
#include <QInputDialog>
#include "qtBCrypt.h"
#include "UserMgr.h"

bool LoginWidget::LoginSuccess  = false;

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWidget)
{
    ui->setupUi(this);


    ui->stackedWidget->setCurrentIndex(0);
    connect(this, &LoginWidget::sig_connect_tcp, TcpMgr::GetInstance().get(), &TcpMgr::slot_tcp_connect);
    connect(TcpMgr::GetInstance().get(),&TcpMgr::sig_swich_operaterwidget,this,&LoginWidget::slot_switch_OperaterWidget);

    connect(ui->checkBox_admin, &QCheckBox::toggled, [=](bool checked) {
        if (checked) {
            ui->checkBox_user->setChecked(false);
        }
    });

    connect(ui->checkBox_user, &QCheckBox::toggled, [=](bool checked) {
        if (checked) {
            ui->checkBox_admin->setChecked(false);
        }
    });
/**/

}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_LoginBtn_clicked()
{
    // 获取用户输入的ID和密码
    auto id = ui->LoginIdlineEdit->text().trimmed();  // 去除前后空白
    auto pwd = ui->LoginPwdlineEdit->text().trimmed();

    // 检查输入是否为空
    if (id.isEmpty() || pwd.isEmpty()) {
        QMessageBox::warning(this, "登录失败", "账号和密码不能为空！");
        return;
    }

    // 打开UserData.txt文件并读取内容
    QString jsonFilePath = QCoreApplication::applicationDirPath() + "/UserData.txt";
    QFile file(jsonFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法打开用户数据文件！");
        return;
    }

    // 读取文件内容
    QByteArray fileData = file.readAll();
    file.close();

    // 解析JSON数据
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    if (jsonDoc.isNull() || !jsonDoc.isArray()) {
        QMessageBox::warning(this, "错误", "用户数据文件格式错误！");
        return;
    }

    QJsonArray userArray = jsonDoc.array();
    QString userPermission;
    // 检查用户ID是否存在
    bool userFound = false;
    QString storedPwd;  // 保存加密的密码
    for (const QJsonValue &value : userArray) {
        QJsonObject obj = value.toObject();
        if (obj["id"].toString() == id) {
            userFound = true;
            storedPwd = obj["pwd"].toString();  // 获取存储的加密密码
            userPermission = obj["permission"].toString();
            // 验证密码
            if (QtBCrypt::validatePassword(pwd, storedPwd)) {  // 使用bcrypt验证密码
                // 登录成功
                auto si = std::make_shared<ServerInfo>();
                GetServer(si,this);
                emit sig_connect_tcp(si);
                LoginSuccess = true;
                UserMgr::GetInstance()->user_id = id;
                UserMgr::GetInstance()->user_permission = userPermission;
            } else {
                QMessageBox::warning(this, "登录失败", "密码不正确！");
                return;
            }
        }
    }

    if (!userFound) {
        QMessageBox::warning(this, "登录失败", "该用户不存在！");
        return;
    }

}

void LoginWidget::slot_switch_OperaterWidget()
{
    // 检查当前的父窗口是否是 Widget
    if (qobject_cast<Widget*>(this->parentWidget())) {
        return;  // 如果是，则不执行任何操作
    }

    // Widget* w = new Widget();
    Widget::GetInstance()->show();
    // this->deleteLater();
    this->hide();
}


void LoginWidget::on_CancleRegisterBTn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void LoginWidget::on_RegisterBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void LoginWidget::on_UserRegisterBtn_clicked()
{
    // // 获取用户输入的ID和密码
    // auto id = ui->IdlineEdit->text();
    // auto pwd = ui->PwdlineEdit->text();
    // auto pwd2 = ui->SurePwdlineEdit->text();

    // // 检查输入是否为空
    // if (id.isEmpty() || pwd.isEmpty() || pwd2.isEmpty()) {
    //     QMessageBox::warning(this, "注册失败", "所有字段均不能为空！");
    //     return;
    // }

    // // 检查密码是否一致
    // if (pwd != pwd2) {
    //     QMessageBox::warning(this, "注册失败", "两次输入的密码不一致！");
    //     return;
    // }

    // // 打开UserData.txt文件并读取内容
    // // 打开UserData.txt文件并读取内容
    // QString jsonFilePath = QCoreApplication::applicationDirPath() + "/UserData.txt";
    // QFile file(jsonFilePath);
    // if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
    //     QMessageBox::warning(this, "错误", "无法打开文件！");
    //     return;
    // }

    // // 读取现有数据
    // QByteArray fileData = file.readAll();
    // QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    // QJsonArray userArray;
    // if (!jsonDoc.isNull() && jsonDoc.isArray()) {
    //     userArray = jsonDoc.array();  // 如果已有数据，则读取为数组
    // }

    // // 检查ID是否已注册
    // for (const QJsonValue &value : userArray) {
    //     QJsonObject obj = value.toObject();
    //     if (obj["id"].toString() == id) {
    //         QMessageBox::warning(this, "注册失败", "该ID已被注册！");
    //         return;
    //     }
    // }

    // // 加密密码
    // QString salt = QtBCrypt::generateSalt();  // 生成盐
    // QString hashedPwd = QtBCrypt::hashPassword(pwd, salt);  // 使用bcrypt加密

    // // 创建用户对象
    // QJsonObject newUser;
    // newUser["id"] = id;
    // newUser["pwd"] = hashedPwd;
    // newUser["permission"] = "user";

    // // 将新用户加入到用户数组中
    // userArray.append(newUser);

    // // 保存新数据到文件
    // jsonDoc.setArray(userArray);
    // file.resize(0);  // 清空文件
    // file.write(jsonDoc.toJson());  // 写入新数据
    // file.close();

    // QMessageBox::information(this, "注册成功", "用户注册成功！");


}


void LoginWidget::on_AdminRegisterBtn_clicked()
{
    // // 获取用户输入的ID和密码
    // auto id = ui->IdlineEdit->text();
    // auto pwd = ui->PwdlineEdit->text();
    // auto pwd2 = ui->SurePwdlineEdit->text();

    // // 检查输入是否为空
    // if (id.isEmpty() || pwd.isEmpty() || pwd2.isEmpty()) {
    //     QMessageBox::warning(this, "注册失败", "所有字段均不能为空！");
    //     return;
    // }

    // // 检查密码是否一致
    // if (pwd != pwd2) {
    //     QMessageBox::warning(this, "注册失败", "两次输入的密码不一致！");
    //     return;
    // }

    // // 弹出输入框，获取确认信息
    // QString confirmationCode = QInputDialog::getText(this, "确认管理员权限", "请输入管理员确认代码:");

    // // 从外部配置文件读取正确的确认信息
    // QString correctCode;

    // QString configFilePath = QCoreApplication::applicationDirPath() + "/config.ini";
    // QFile cfg_file(configFilePath);

    // bool readingPermissions = false; // 标志是否在读取 [permission] 段

    // if (cfg_file.open(QIODevice::ReadOnly)) {
    //     QTextStream in(&cfg_file);
    //     QString line;
    //     while (in.readLineInto(&line)) {
    //         line = line.trimmed(); // 去除前后空白
    //         if (line == "[permission]") {
    //             readingPermissions = true; // 开始读取权限段
    //             continue;
    //         }
    //         if (readingPermissions) {
    //             // 检查是否是 admin 的配置
    //             if (line.startsWith("admin =")) {
    //                 // 使用正则表达式匹配 "admin = "123456""
    //                 QRegularExpression regex(R"(admin\s*=\s*\"(.*?)\".*)");
    //                 QRegularExpressionMatch match = regex.match(line);
    //                 if (match.hasMatch()) {
    //                     correctCode = match.captured(1); // 获取"123456"
    //                 }
    //                 break; // 找到后退出循环
    //             }
    //         }
    //     }
    //     cfg_file.close();
    // } else {
    //     QMessageBox::critical(this, "错误", "无法打开配置文件！");
    //     return;
    // }

    // // 比较用户输入的确认信息与配置文件中的数据
    // if (confirmationCode != correctCode) {
    //     QMessageBox::warning(this, "注册失败", "确认代码不正确！");
    //     return;
    // }

    // // 打开UserData.txt文件并读取内容
    // QString jsonFilePath = QCoreApplication::applicationDirPath() + "/UserData.txt";
    // QFile json_file(configFilePath);
    // if (!json_file.open(QIODevice::ReadWrite | QIODevice::Text)) {
    //     QMessageBox::warning(this, "错误", "无法打开文件！");
    //     return;
    // }

    // // 读取现有数据
    // QByteArray fileData = json_file.readAll();
    // QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    // QJsonArray userArray;
    // if (!jsonDoc.isNull() && jsonDoc.isArray()) {
    //     userArray = jsonDoc.array();  // 如果已有数据，则读取为数组
    // }

    // // 检查ID是否已注册
    // for (const QJsonValue &value : userArray) {
    //     QJsonObject obj = value.toObject();
    //     if (obj["id"].toString() == id) {
    //         QMessageBox::warning(this, "注册失败", "该ID已被注册！");
    //         return;
    //     }
    // }

    // // 加密密码
    // QString salt = QtBCrypt::generateSalt();  // 生成盐
    // QString hashedPwd = QtBCrypt::hashPassword(pwd, salt);  // 使用bcrypt加密

    // // 创建用户对象
    // QJsonObject newUser;
    // newUser["id"] = id;
    // newUser["pwd"] = hashedPwd;
    // newUser["permission"] = "user";

    // // 将新用户加入到用户数组中
    // userArray.append(newUser);

    // // 保存新数据到文件
    // jsonDoc.setArray(userArray);
    // json_file.resize(0);  // 清空文件
    // json_file.write(jsonDoc.toJson());  // 写入新数据
    // json_file.close();

    // QMessageBox::information(this, "注册成功", "用户注册成功！");


}

//登录密码可见
void LoginWidget::on_pwdcheckable_btn_clicked()
{
    if(ui->LoginPwdlineEdit->echoMode() == QLineEdit::Password) {
        ui->LoginPwdlineEdit->setEchoMode(QLineEdit::Normal);
        ui->pwdcheckable_btn->setStyleSheet("border-image: url(:/image/eyes_disable.png);");
    } else if(ui->LoginPwdlineEdit->echoMode() == QLineEdit::Normal) {
        ui->LoginPwdlineEdit->setEchoMode(QLineEdit::Password);
        ui->pwdcheckable_btn->setStyleSheet("border-image: url(:/image/eyes_enable.png);");
    }
}
void LoginWidget::on_pwdcheckable_btn_2_clicked()
{
    if(ui->PwdlineEdit->echoMode() == QLineEdit::Password) {
        ui->PwdlineEdit->setEchoMode(QLineEdit::Normal);
        ui->pwdcheckable_btn_2->setStyleSheet("border-image: url(:/image/eyes_disable.png);");
    } else if(ui->PwdlineEdit->echoMode() == QLineEdit::Normal) {
        ui->PwdlineEdit->setEchoMode(QLineEdit::Password);
        ui->pwdcheckable_btn_2->setStyleSheet("border-image: url(:/image/eyes_enable.png);");
    }
}
void LoginWidget::on_pwdcheckable_btn_3_clicked()
{
    if(ui->SurePwdlineEdit->echoMode() == QLineEdit::Password) {
        ui->SurePwdlineEdit->setEchoMode(QLineEdit::Normal);
        ui->pwdcheckable_btn_3->setStyleSheet("border-image: url(:/image/eyes_disable.png);");
    } else if(ui->SurePwdlineEdit->echoMode() == QLineEdit::Normal) {
        ui->SurePwdlineEdit->setEchoMode(QLineEdit::Password);
        ui->pwdcheckable_btn_3->setStyleSheet("border-image: url(:/image/eyes_enable.png);");
    }
}


void LoginWidget::on_RegisterOKBtn_clicked()
{
    // 获取用户输入的ID和密码
    auto id = ui->IdlineEdit->text();
    auto pwd = ui->PwdlineEdit->text();
    auto pwd2 = ui->SurePwdlineEdit->text();

    QString userpermission;
    QString configFilePath = QCoreApplication::applicationDirPath() + "/config.ini";
    // 检查输入是否为空
    if (id.isEmpty() || pwd.isEmpty() || pwd2.isEmpty()) {
        QMessageBox::warning(this, "注册失败", "所有字段均不能为空！");
        return;
    }

    // 检查密码是否一致
    if (pwd != pwd2) {
        QMessageBox::warning(this, "注册失败", "两次输入的密码不一致！");
        return;
    }

    if(ui->checkBox_admin->isChecked()) {
        userpermission = "admin";
        // 弹出输入框，获取确认信息
        QString confirmationCode = QInputDialog::getText(this, "确认管理员权限", "请输入管理员确认代码:");
        // 从外部配置文件读取正确的确认信息
        QString correctCode;
        QFile cfg_file(configFilePath);
        qDebug()<<cfg_file.fileName();
        bool readingPermissions = false; // 标志是否在读取 [permission] 段
        if (cfg_file.open(QIODevice::ReadOnly)) {
            QTextStream in(&cfg_file);
            QString line;
            while (in.readLineInto(&line)) {
                line = line.trimmed(); // 去除前后空白
                if (line == "[permission]") {
                    readingPermissions = true; // 开始读取权限段
                    continue;
                }
                if (readingPermissions) {
                    // 检查是否是 admin 的配置
                    if (line.startsWith("admin =")) {
                        // 使用正则表达式匹配 "admin = "123456""
                        QRegularExpression regex(R"(admin\s*=\s*\"(.*?)\".*)");
                        QRegularExpressionMatch match = regex.match(line);
                        qDebug()<<match.captured(1);
                        if (match.hasMatch()) {
                            correctCode = match.captured(1); // 获取"123456"
                        }
                        break; // 找到后退出循环
                    }
                }
            }
            cfg_file.close();
        } else {
            QMessageBox::critical(this, "错误", "无法打开配置文件！");
            return;
        }

        // 比较用户输入的确认信息与配置文件中的数据
        if (confirmationCode != correctCode) {
            QMessageBox::warning(this, "注册失败", "确认代码不正确！");
            return;
        }
    }

    if(ui->checkBox_user->isChecked()) {
        userpermission = "user";
    }

    if(userpermission == "") {
        QMessageBox::warning(this, "注册失败", "请选择权限注册");
        return;
    }
    // 打开UserData.txt文件并读取内容
    QString jsonFilePath = QCoreApplication::applicationDirPath() + "/UserData.txt";
    QFile json_file(jsonFilePath);
    qDebug()<<json_file.fileName();
    if (!json_file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法打开文件！");
        return;
    }

    // 读取现有数据
    QByteArray fileData = json_file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonArray userArray;
    if (!jsonDoc.isNull() && jsonDoc.isArray()) {
        userArray = jsonDoc.array();  // 如果已有数据，则读取为数组
    }

    // 检查ID是否已注册
    for (const QJsonValue &value : userArray) {
        QJsonObject obj = value.toObject();
        if (obj["id"].toString() == id) {
            QMessageBox::warning(this, "注册失败", "该ID已被注册！");
            return;
        }
    }

    // 加密密码
    QString salt = QtBCrypt::generateSalt();  // 生成盐
    QString hashedPwd = QtBCrypt::hashPassword(pwd, salt);  // 使用bcrypt加密

    // 创建用户对象
    QJsonObject newUser;
    newUser["id"] = id;
    newUser["pwd"] = hashedPwd;
    newUser["permission"] = userpermission;
    // 将新用户加入到用户数组中
    userArray.append(newUser);
    // 保存新数据到文件
    jsonDoc.setArray(userArray);
    json_file.resize(0);  // 清空文件
    json_file.write(jsonDoc.toJson());  // 写入新数据
    json_file.close();
    QMessageBox::information(this, "注册成功", "用户注册成功！");
}




