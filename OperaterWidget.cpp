#include "OperaterWidget.h"
#include "LoginWidget.h"
#include "UserMgr.h"
#include "qdir.h"
#include "qevent.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "ui_OperaterWidget.h"
#include <QDebug>
#include <QTimer>
#include <QTime>
#include "TcpMgr.h"
#include <QString>
#include <QScreen>
#include <QMessageBox>
#include "clampwidget.h"
#include "lockwidget.h"
#include "downloadwidget.h"
#include <QDesktopServices>
#include <QFile>
#include <TipLabel.h>
#include "camwidget.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget),currentState("")
{
    ui->setupUi(this);
    // resize(1280,800);
    setWindowFlag(Qt::FramelessWindowHint);
    showFullScreen();


    // 初始化定时器
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::checkFolder);

    // 启动定时器，每秒检查一次文件夹
    // timer->start(100);


    CurrentTimer = new QTimer(this);
    connect(CurrentTimer, &QTimer::timeout, this, &Widget::UpDateTime);
    CurrentTimer->start(1000);

    InitObject();
    InitUserInfo();
    InitStyleSheet();
    //绑定关节角控制按钮
    InitJointBtn();
    //绑定方向按钮
    InitDirectionBtn();
    InitSpeed();
    connect(this, &Widget::sig_connect_tcp, TcpMgr::GetInstance().get(), &TcpMgr::slot_tcp_connect);
    connect(TcpMgr::GetInstance().get(),&TcpMgr::sig_clamp_ok,[=](){
        // qDebug()<<"emit";
        QTimer::singleShot(0, this, [=]() {
            // qDebug() << "ok";
            RecoverFunctionBtn();
            Globals::clampisOK = true;
            Globals::clamp_motionisok = true;
        });
        });
    connect(TcpMgr::GetInstance().get(),&TcpMgr::statusReceived,this,&Widget::UpdateAllData);
    //当前版本限制
    BANSCONTROL();

    auto si = std::make_shared<ServerInfo>();
    GetServer(si,this);

    receiverThread = new ResultReceiver();
    receiverThread->host = si->zmqhost;
    receiverThread->port = si->zmqport;

    // qDebug()<<"zmqhost:"<<si->zmqhost;
    // qDebug()<<"zmqport:"<<si->zmqport;

    connect(receiverThread, &ResultReceiver::resultReceived, this, &Widget::onResultImage);
    receiverThread->start();

    QString status_code = QCoreApplication::applicationDirPath() + "/status_code.json";
    statusMap = readStatusCodesFromJson(status_code);

    on_clampdzBtn_clicked();
}

Widget::~Widget()
{
    delete cw;
    delete cw2;
    delete lw;
    delete dw;
    delete ui;
    delete cmw;
}

void Widget::DisableFunctionBtn()
{
    for(auto item : directionBtns) {
        item->setDisabled(true);
    }
    for(auto item : JointBtns) {
        item->setDisabled(true);
    }
     qDebug()<<"disa";
}

void Widget::RecoverFunctionBtn()
{
    // qDebug() << "Before recovering buttons";
    for(auto item : directionBtns) {
        if(item) {  // 检查指针是否有效
            item->setDisabled(false);
        }
    }
    for(auto item : JointBtns) {
        if(item) {  // 检查指针是否有效
            item->setDisabled(false);
        }
    }
    qDebug() << "recov";
}

void Widget::BANSCONTROL()
{
    auto btns = {ui->RX_Up_Btn, ui->RY_Up_Btn, ui->RZ_Up_Btn,
            ui->RX_Down_Btn, ui->RY_Down_Btn, ui->RZ_Down_Btn};
    for(auto btn : btns){
        btn->setDefault(true);
        btn->hide();
    }
    ui->SpeedSlider_2->hide();
    ui->SpeedlineEdit_2->hide();

    auto  lbs = {ui->label_rx,ui->label_ry,ui->label_rz};
    for(auto lb : lbs){
        lb->hide();
    }

    auto lines = {ui->RXlineEdit,ui->RYlineEdit,ui->RZlineEdit};
    for(auto line : lines){
        line->hide();

    }

    ui->label_64->hide();
    ui->label_clamp2->hide();
    ui->WiFiBtn->setCheckable(false);
    ui->WiFiBtn->setDefault(true);

    ui->OperaterBtn->hide();
}


void Widget::InitStyleSheet()
{
    ui->WiFiBtn->setStyleSheet("border-image: url(:/image/wifiOpen.png);");
}

void Widget::connectButton(QPushButton *button, const QString &pressedImage, const QString &releasedImage, QLabel *label)
{
    connect(button, &QPushButton::pressed, [=]() {
        button->setStyleSheet(QString("border-image: url(%1);").arg(pressedImage));
        label->setStyleSheet(QString("border-image: url(%1);").arg(pressedImage));
    });

    connect(button, &QPushButton::released, [=]() {
        button->setStyleSheet(QString("border-image: url(%1);").arg(releasedImage));
        label->setStyleSheet("");
    });
}

void Widget::getTip()
{
    TipLabel * lb = new TipLabel(this->geometry());
}

void Widget::InitJointBtn()
{
    for (int i = 1; i <= 7; ++i) {
        QPushButton* DownBtn = findChild<QPushButton*>(QString("J%1_Down_Btn").arg(i));
        if (DownBtn) {
            DownBtn->setStyleSheet(BTNCLICKED_STY);
            QString firstPart = DownBtn->objectName().section('_', 0, 0); // 第一个部分 名字
            QString secondPart = DownBtn->objectName().section('_', 1, 1); // 第二个部分 增减
            connect(DownBtn,&QPushButton::pressed,[=](){
                if(Globals::clampisOK){
                    JointPointPress(firstPart,secondPart);
                }else{
                    // getTip();
                }
            });
            connect(DownBtn,&QPushButton::released,[=](){
                if(Globals::clampisOK){
                    JointPointRelease(firstPart,secondPart);
                }else{
                    // getTip();
                }
            });
            JointBtns.append(DownBtn);
        }

        QPushButton* UpBtn = findChild<QPushButton*>(QString("J%1_Up_Btn").arg(i));
        if (UpBtn) {
            UpBtn->setStyleSheet(BTNCLICKED_STY);
            QString firstPart = UpBtn->objectName().section('_', 0, 0); // 第一个部分 名字
            QString secondPart = UpBtn->objectName().section('_', 1, 1); // 第二个部分 增减
            connect(UpBtn,&QPushButton::pressed,[=](){
                if(Globals::clampisOK){
                    JointPointPress(firstPart,secondPart);
                }else{
                    // getTip();
                }
            });
            connect(UpBtn,&QPushButton::released,[=](){
                if(Globals::clampisOK){
                    JointPointRelease(firstPart,secondPart);
                }else{
                    // getTip();
                }
            });
            JointBtns.append(UpBtn);
        }
        QLineEdit * le = findChild<QLineEdit*>(QString("J%1lineEdit").arg(i));
        if(le) {
            lineEdits.append(le);
        }
    }
}

void Widget::InitDirectionBtn()
{
    for(QPushButton* btn : directionBtns) {
        btn->setStyleSheet(BTNCLICKED_STY);
        QString firstPart = btn->objectName().section('_', 0, 0); // 第一个部分 方向
        QString secondPart = btn->objectName().section('_', 1, 1); // 第二个部分 增减

        connect(btn,&QPushButton::pressed,[=](){
            if(Globals::clampisOK == true ){
                dir = firstPart + ":" + secondPart;
                updatePosition();
            }else{
                // getTip();
            }
        });

        connect(btn,&QPushButton::released,[=](){
            if(Globals::clampisOK == true ){
                Globals::clampisOK = false;
                auto msg = firstPart + "&s";
                QByteArray msgbody = msg.toUtf8();
                emit TcpMgr::GetInstance()->sig_send_data("mpot", msgbody);
                DisableFunctionBtn();
            }else{
                // getTip();
            }
        });
    }
}

void Widget::InitObject()
{
    directionBtns = {ui->X_Up_Btn, ui->Y_Up_Btn, ui->Z_Up_Btn,
                     // ui->RX_Up_Btn, ui->RY_Up_Btn, ui->RZ_Up_Btn,
                     ui->X_Down_Btn, ui->Y_Down_Btn, ui->Z_Down_Btn,
                     // ui->RX_Down_Btn, ui->RY_Down_Btn, ui->RZ_Down_Btn
                    };

    lineEdits = {ui->XlineEdit, ui->YlineEdit, ui->ZlineEdit,
                 ui->RXlineEdit, ui->RYlineEdit, ui->RZlineEdit};

    // ui->tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    // ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->MenuStackWidget->   setCurrentIndex(0);
    ui->stackedWidget_msg-> setCurrentIndex(0);
    ui->stackedWidget->     setCurrentIndex(0);

    ui->OperaterBtn->       setCheckable(true);
    ui->SettingBtn->        setCheckable(true);
    ui->InfoBtn->           setCheckable(true);
    ui->HelpBtn->           setCheckable(true);
    ui->clampdzBtn->        setCheckable(true);
    ui->clampwbBtn->        setCheckable(true);

    ui->OperaterBtn->       setAutoExclusive(true);
    ui->SettingBtn->        setAutoExclusive(true);
    ui->InfoBtn->           setAutoExclusive(true);
    ui->HelpBtn->           setAutoExclusive(true);
    ui->clampdzBtn->           setAutoExclusive(true);
    ui->clampwbBtn->           setAutoExclusive(true);

    cw =                    new ClampWidget;
    cw2=                    new ClampWidget;
    lw =                    new LockWidget;
    dw =                    new DownLoadWidget;
    cmw =                   new CamWidget;
    this->                  installEventFilter(this);
    ui->clampdzBtn->       setChecked(true);
    ui->J1_Down_Btn->       setStyleSheet(BTNCLICKED_STY);
    ui->VerticalHoldBtn->   setStyleSheet(OFF);
    ui->HorizenHoldBtn->    setStyleSheet(OFF);
    // QVBoxLayout *layout =   new QVBoxLayout(ui->widget_7);
    // layout->                setContentsMargins(10, 10, 10, 10); // 设置布局边距
    // QLabel *btnlabel =      new QLabel(ui->widget_7);
    // btnlabel->              setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // btnlabel->              setScaledContents(true); // 启用缩放
    // layout->                addWidget(btnlabel);
    ui->ModelcheckBox->     setMinimumHeight(20);
    WiFiState =             true;

}

void Widget::InitSpeed()
{
    QString iniFilePath = QCoreApplication::applicationDirPath() + "/config.ini";
    // 创建 QSettings 对象
    QSettings settings(iniFilePath, QSettings::IniFormat);
    settings.beginGroup("speed");  // 进入 [exe] 部分
    auto s1 = settings.value("DirSpeed").toString();
    auto s2 = settings.value("JointSpeed").toString();
    auto s3 = settings.value("MAXSpeed").toString();
    settings.endGroup();  // 进入 [exe] 部分

    Speed = s1.toDouble();
    JointSpeed = s2.toDouble();
    MAXSPEED = s3.toDouble();

    ui->SpeedSlider->setValue(Speed*100/MAXSPEED);
    ui->SpeedSlider_3->setValue(JointSpeed*100/MAXSPEED);
}

QMap<QString, QString> Widget::readStatusCodesFromJson(const QString &filePath)
{
    QMap<QString, QString> statusMap;

    // 打开文件
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "无法打开文件:" << filePath;
        return statusMap;
    }

    // 读取文件内容
    QByteArray jsonData = file.readAll();
    file.close();

    // 解析JSON
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON解析错误:" << parseError.errorString();
        return statusMap;
    }

    if (!jsonDoc.isObject()) {
        qWarning() << "JSON不是对象格式";
        return statusMap;
    }

    // 获取JSON对象
    QJsonObject jsonObj = jsonDoc.object();

    // 遍历所有键值对
    for (auto it = jsonObj.begin(); it != jsonObj.end(); ++it) {
        if (it.value().isString()) {
            statusMap.insert(it.key(), it.value().toString());
            qDebug()<<"key:"<<it.key()<<"value:"<<it.value().toString();
        }
    }
    return statusMap;
}

//姿态速度
void Widget::on_SpeedSlider_valueChanged(int value)
{
    int minValue = ui->SpeedSlider->minimum(); // 获取滑块的最小值
    int maxValue = ui->SpeedSlider->maximum(); // 获取滑块的最大值
    // 计算百分比进度
    double percentage = static_cast<int>((static_cast<double>(value - minValue) / (maxValue - minValue)) * 100);
    Speed = (percentage/100.00) * MAXSPEED;
    // 将百分比转换为字符串并显示在 SpeedlineEdit 上
    ui->SpeedlineEdit->setText(QString::number(percentage) + "%");
    ui->ArmSpeedLabel->setText(QString::number(Speed, 'f', 3).rightJustified(7, '0'));

}
//姿态角速度
void Widget::on_SpeedSlider_2_valueChanged(int value)
{
    int minValue = ui->SpeedSlider_2->minimum(); // 获取滑块的最小值
    int maxValue = ui->SpeedSlider_2->maximum(); // 获取滑块的最大值
    // 计算百分比进度
    double percentage = static_cast<int>((static_cast<double>(value - minValue) / (maxValue - minValue)) * 100);
    StatusJointSpeed = (percentage/100.00) * MAXSPEED;
    // 将百分比转换为字符串并显示在 SpeedlineEdit 上
    ui->SpeedlineEdit_2->setText(QString::number(percentage) + "%");
    ui->StatusJointSpeedLabel->setText(QString::number(StatusJointSpeed, 'f', 3).rightJustified(7, '0'));
}
//关节角速度
void Widget::on_SpeedSlider_3_valueChanged(int value)
{
    int minValue = ui->SpeedSlider_3->minimum(); // 获取滑块的最小值
    int maxValue = ui->SpeedSlider_3->maximum(); // 获取滑块的最大值
    // 计算百分比进度
    double percentage = static_cast<int>((static_cast<double>(value - minValue) / (maxValue - minValue)) * 100);
    JointSpeed = (percentage / 100.00) * MAXSPEED;
    // 将百分比转换为字符串并显示在 SpeedlineEdit 上
    ui->SpeedlineEdit_3->setText(QString::number(percentage) + "%");
    // 格式化 JointSpeed 为 00.00
    ui->ArmJointLabel->setText(QString::number(JointSpeed, 'f', 3).rightJustified(7, '0'));
}


void Widget::on_WiFiBtn_clicked()
{
    // if(!WiFiState) {
    //     WiFiState = true;
    //     ui->WiFiBtn->setStyleSheet("border-image: url(:/image/wifiOpen.png);");
    //     auto si = std::make_shared<ServerInfo>();
    //     GetServer(si,this);
    //     emit sig_connect_tcp(si);
    // } else {
    //     WiFiState = false;
    //     ui->WiFiBtn->setStyleSheet("border-image: url(:/image/wifiClose.png);");
    //     TcpMgr::GetInstance()->Disconnect();
    // }
}

//
void Widget::on_SpeedlineEdit_editingFinished()
{
    bool ok;
    auto txt = ui->SpeedlineEdit->text();
    double value = ui->SpeedlineEdit->text().toDouble(&ok);
    // 检查转换是否成功
    if (!ok) {
        return;  // 如果转换失败，直接返回
    }
    // 限制值范围
    if (value > 100) {
        value = 100;
    }
    if (value < 0) {
        value = 0;
    }
    Speed = (value / 100.00) * MAXSPEED;
    ui->SpeedSlider->setValue(static_cast<int>(value));
    ui->SpeedlineEdit->setText(QString::number(value) + "%");

}

void Widget::on_SpeedlineEdit_2_editingFinished()
{
    bool ok;
    double value = ui->SpeedlineEdit_2->text().toDouble(&ok);
    if (!ok) {
        return;
    }
    if (value > 100) {
        value = 100;
    }
    if (value < 0) {
        value = 0;
    }
    StatusJointSpeed = (value / 100.00) * MAXSPEED;
    ui->SpeedSlider_2->setValue(value);
    ui->SpeedlineEdit_2->setText(QString::number(value) + "%");
}
void Widget::on_SpeedlineEdit_3_editingFinished()
{
    bool ok;
    double value = ui->SpeedlineEdit_3->text().toDouble(&ok);
    if (!ok) {
        return;
    }
    if (value > 100) {
        value = 100;
    }
    if (value < 0) {
        value = 0;
    }
    JointSpeed = (value / 100.00) * MAXSPEED;
    ui->SpeedSlider_3->setValue(value);
    ui->SpeedlineEdit_3->setText(QString::number(value) + "%");
}

void Widget::SetX_Pos(QString pos)
{
    ui->XlineEdit->setText(pos);
}
void Widget::SetY_Pos(QString pos)
{
    ui->YlineEdit->setText(pos);
}
void Widget::SetZ_Pos(QString pos)
{
    ui->ZlineEdit->setText(pos);
}
void Widget::SetRX_Pos(QString deg)
{
    ui->RXlineEdit->setText(deg);
}
void Widget::SetRY_Pos(QString deg)
{
    ui->RYlineEdit->setText(deg);
}
void Widget::SetRZ_Pos(QString deg)
{
    ui->RZlineEdit->setText(deg);
}


//笛卡尔坐标控制
void Widget::updatePosition()
{
    QString part1;
    QString part2;
    QStringList parts = dir.split(':');
    if (parts.size() == 2) {
        part1 = parts[0]; // 方向
        part2 = parts[1]; // 增减
    }
    QString msg = parts[0] + (parts[1] == "Up" ? "&up" : "&down");
    QByteArray msgbody = msg.toUtf8();
    emit TcpMgr::GetInstance()->sig_send_data("mpot", msgbody);
}

void Widget::updateJoint()
{
    if(Globals::clampisOK == true){
        double JointStepValue = JointSpeed;//关节步进速度

        QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
        if (senderButton) {
            QString buttonName = senderButton->objectName(); // 获取按钮的名称
            QString jointIndexStr = buttonName.mid(1, 1); // 截取关节索引部分
            int jointIndex = jointIndexStr.toInt(); // 转换为整数

            double currentValue = JointValue[jointIndex - 1].toDouble();

                if (buttonName.contains("Up")) {
                    // 增加操作
                    currentValue += JointStepValue; // 增加值
                } else if (buttonName.contains("Down")) {
                    // 减少操作
                    currentValue -= JointStepValue; // 减少值
                }

                if (std::abs(currentValue) < 0.00001) {  // 将非常小的值视为0
                    currentValue = 0;
                }
                // 更新 JointValue 数组为新的 QString 值
                JointValue[jointIndex - 1] = QString::number(currentValue);
        }
        QString msg = QString("%1,%2,%3,%4,%5,%6,%7")
                          .arg(JointValue[0])//z1
                          .arg(JointValue[1])//z2
                          .arg(JointValue[2])//z3
                          .arg(JointValue[3])//j1
                          .arg(JointValue[4])//j2
                          .arg(JointValue[5])//j3
                          .arg(JointValue[6]);//z4

        QByteArray msgbody = msg.toUtf8();
        emit TcpMgr::GetInstance()->sig_send_data("gptj", msgbody);
        Globals::clampisOK = false;
    }else{
        // getTip();
    }
}

void Widget::InitUserInfo()
{
    ui->user_nameLB->setText(UserMgr::GetInstance()->user_id);
    ui->permissionLb->setText(UserMgr::GetInstance()->user_permission);
}

QByteArray Widget::getjson()
{
    QJsonObject json;
    QJsonObject range;
    QStringList keys = {"Range_z1", "Range_z2", "Range_z3", "Range_j1", "Range_j2", "Range_j3", "Range_z4"};
    QJsonObject range1;
    range1["min"] = 700;
    range1["max"] = -700;
    json[keys[0]] = range1;

    QJsonObject range2;
    range2["min"] = 180;
    range2["max"] = 136;
    json[keys[1]] = range2;

    QJsonObject range3;
    range3["min"] = 70;
    range3["max"] = 26;
    json[keys[2]] = range3;

    QJsonObject range4;
    range4["min"] = -91.5;
    range4["max"] = 23;
    json[keys[3]] = range4;

    QJsonObject range5;
    range5["min"] = -35;
    range5["max"] = 31;
    json[keys[4]] = range5;

    QJsonObject range6;
    range6["min"] = 42.5;
    range6["max"] = -47.5;
    json[keys[5]] = range6;

    QJsonObject range7;
    range7["min"] = 1100;
    range7["max"] = 8650;
    json[keys[6]] = range7;

    //当前值
    QStringList angles = {"Angle_z1", "Angle_z2", "Angle_z3", "Angle_j1", "Angle_j2", "Angle_j3", "Angle_z4"};
    for(int i = 0; i < 7; i++){
        json[angles[i]] = JointValue[i];
    }

    QJsonObject nowPose, aimPose;
    nowPose["x"] = cartesianCoords[0];
    nowPose["y"] = cartesianCoords[1];
    nowPose["z"] = cartesianCoords[2];
    aimPose["x"] = 0;
    aimPose["y"] = 0;
    aimPose["z"] = 0;
    json["Nowpose"] = nowPose;
    json["Aimpose"] = aimPose;
    json["Angle_roll"] = 0.0;
    json["Angle_pitch"] = 0.0;
    json["Angle_yaw"] = 0.0;
    json["Clamp1"] = (clampState[0] == "1");
    json["Clamp2"] = (clampState[1] == "1");
    json["distance"] = 0.0;

    QJsonDocument doc(json);
    QByteArray data = doc.toJson(QJsonDocument::Compact);

    return data;
}

//关节角控制消息发送
void Widget::UpDateJointValue(int value)
{
    QString str = QString::number(value);
    // 获取发出信号的滑块
    QSlider* slider = qobject_cast<QSlider*>(sender());
    if (slider) {
        QString name = slider->objectName().left(2); // 获取对象名称
        str = name + "&" + str;
    }
    QByteArray byteValue = str.toUtf8();
    TcpMgr::GetInstance()->sig_send_data("gjot",byteValue);
}
//当前时间更新
void Widget::UpDateTime()
{
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();
    auto t = date.toString("yyyy-MM-dd") + " " + time.toString("hh:mm:ss");
    ui->TimeLabel->setText(t);
}
// //更新所有运动状态
// void Widget::UpdateAllData(QString str1, QString str2, QString str3, QString str4)
// {
//     isstat = true;
//     auto str1list = str1.split(",");//笛卡尔
//     auto str2list = str2.split(",");//关节
//     // 确保 str1list 的大小不超过 6，以防止越界
//     for (int i = 0; i < qMin(str1list.size(), 6); ++i) {
//         cartesianCoords[i] = str1list[i]; // 按顺序存入数组
//     }

//     for(int i = 0; i < qMin(str2list.size(),  7); ++i) {
//         JointValue[i] = str2list[i];
//     }
//     //更新关节角
//     ui->J1lineEdit->setText(JointValue[0]);
//     ui->J2lineEdit->setText(JointValue[1]);
//     ui->J3lineEdit->setText(JointValue[2]);
//     ui->J4lineEdit->setText(JointValue[3]);
//     ui->J5lineEdit->setText(JointValue[4]);
//     ui->J6lineEdit->setText(JointValue[5]);
//     ui->J7lineEdit->setText(JointValue[6]);
//     //更新笛卡尔坐标系
//     SetX_Pos(cartesianCoords[0]);
//     SetY_Pos(cartesianCoords[1]);
//     SetZ_Pos(cartesianCoords[2]);
//     SetRX_Pos(cartesianCoords[3]);
//     SetRY_Pos(cartesianCoords[4]);
//     SetRZ_Pos(cartesianCoords[5]);
//     //更新夹爪状态
//     updateClampStatus(str4);
//     //更新运动状态
//     ui->movestatlabel->setText(QString("%1").arg(str3 == "0" ? "当前运动状态：停止" : "当前运动状态：运动中"));
// }

void Widget::UpdateAllData(QStringList messageparts)
{
    auto str1 = messageparts[0];//dke
    auto str2 = messageparts[1];//gjj
    auto str3 = messageparts[2];//status
    auto str4 = messageparts[3];//clamp
    auto str5 = messageparts[4];//distance
    auto str6 = messageparts[5];//stauts
    auto str7 = messageparts[6];//jdw

    isstat = true;
    auto str1list = str1.split(",");//笛卡尔
    auto str2list = str2.split(",");//关节
    auto str5list = str5.split(",");//运动进度
    auto str7list = str7.split(",");//xyz
    for (int i = 0; i < qMin(str1list.size(), 6); ++i) {
        cartesianCoords[i] = str1list[i]; // 按顺序存入数组
    }

    for(int i = 0; i < qMin(str2list.size(),  7); ++i) {
        JointValue[i] = str2list[i];
    }
    //更新关节角
    ui->J1lineEdit->setText(JointValue[0]);
    ui->J2lineEdit->setText(JointValue[1]);
    ui->J3lineEdit->setText(JointValue[2]);
    ui->J4lineEdit->setText(JointValue[3]);
    ui->J5lineEdit->setText(JointValue[4]);
    ui->J6lineEdit->setText(JointValue[5]);
    ui->J7lineEdit->setText(JointValue[6]);

    QString jointText;
    for (int i = 0; i < 7; i++) {
        jointText += QString("J%1:%2").arg(i + 1).arg(JointValue[i]);
        if (i < 6) jointText += ", ";  // 最后一个不加逗号
    }

    // 设置字体大小
    QFont font = ui->label_Joint->font(); // 获取当前字体
    font.setPointSize(12); // 设置字号（例如12pt）
    ui->label_Joint->setFont(font); // 应用新字体

    // 设置文本
    ui->label_Joint->setText(jointText);

    //更新笛卡尔坐标系
    SetX_Pos(str7list[0]);
    SetY_Pos(str7list[1]);
    SetZ_Pos(str7list[2]);
    // SetRX_Pos(cartesianCoords[3]);
    // SetRY_Pos(cartesianCoords[4]);
    // SetRZ_Pos(cartesianCoords[5]);
    //更新夹爪状态
    updateClampStatus(str4);
    //更新运动状态
    ui->movestatlabel->setText(QString("%1").arg(str3 == "0" ? "当前运动状态：停止" : "当前运动状态：运动中"));
    if(str3 == "1"){
        ui->movesteplabel->setText(QString("%1方向正在运动:%2个单位").arg(str5list[0])
                                       .arg(str5list[1]));
    }else{
        ui->movesteplabel->setText(QString("%1方向运动已完成").arg(str5list[0]));
        QTimer::singleShot(500, this, [this]() {
            ui->movesteplabel->setText("当前无任务");
        });
    }

    // 遍历所有状态码
    for (auto it = statusMap.begin(); it != statusMap.end(); ++it) {
        qDebug() << "状态码:" << it.key() << "-> 信息:" << it.value();
    }

    // 查询特定状态码
    if (statusMap.contains(str6)) {
        qDebug() << str6 << "的信息是:" << statusMap.value(str6);
        ui->statuslabel->setText(statusMap.value(str6));

    } else {
        ui->statuslabel->setText("未找到状态码");
    }
}

//clamp状态松紧更新
void Widget::updateClampStatus(QString str)
{
    auto str1list = str.split(",");//笛卡尔

    ui->label_clamp1->setText(QString("%1").arg(str1list[0] == "0" ? "松开" : "夹紧"));
    // ui->label_clamp2->setText(QString("%1").arg(str1list[0] == "0" ? "松开" : "夹紧"));
    ui->label_clamp3->setText(QString("%1").arg(str1list[1] == "0" ? "松开" : "夹紧"));

    clampState[0] = str1list[0];
    clampState[1] = str1list[1];
}

bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        // 点击其他控件或空白区域时触发editingFinished
        if (ui->SpeedlineEdit->hasFocus()) {
            ui->SpeedlineEdit->clearFocus();  // 失去焦点
            on_SpeedlineEdit_editingFinished();  // 触发editingFinished
            return true;  // 事件已处理
        }
    }
    return QWidget::eventFilter(obj, event);  // 继续处理其他事件
}

void Widget::resizeEvent(QResizeEvent *event)
{

}

void Widget::closeEvent(QCloseEvent *event)
{
    TcpMgr::GetInstance()->Disconnect();
}

//切换操作模式
void Widget::on_ModelcheckBox_toggled(bool checked)
{
    ui->stackedWidget->setCurrentIndex(checked ? 1 : 0);
}

//信息窗口切换
void Widget::on_ModelcheckBox_allmsg_toggled(bool checked)
{
    if(checked) {
        ui->stackedWidget_msg->setCurrentIndex(1);
    }else {
        ui->stackedWidget_msg->setCurrentIndex(0);
    }
}

//登出/切换用户
void Widget::on_LoginoutBtn_clicked()
{
    if(TcpMgr::GetInstance()->IsConnected()){
        TcpMgr::GetInstance()->Disconnect();
    }
    TcpMgr::GetInstance()->RECOVR();
    // LoginWidget * lg = new LoginWidget();
    LoginWidget::LoginSuccess = false;
    LoginWidget::GetInstance()->show();
    // this->deleteLater();
    this->hide();
}

//2D相机
void Widget::on_camera_2D_Btn_clicked()
{
    // if(!Carmera_Is_On){
    //     ui->camera_2D_Btn->setText("Carmera_Is_On");
    //     DisableFunctionBtn();
    //     Carmera_Is_On = true;
    // } else {
    //     ui->camera_2D_Btn->setText("Carmera_Is_Off");
    //     RecoverFunctionBtn();
    //     Carmera_Is_On = false;
    // }

}

void Widget::on_CloseBtn_clicked()
{
    this->close();
    // exit(0);
}

//零位
void Widget::on_ZeroStatusBtn_clicked()
{
    // TipLabel * lb = new TipLabel(this->geometry());
    // TcpMgr::GetInstance()->RECOVR();
    DisableFunctionBtn();
}

//初始
void Widget::on_BeginStatusBtn_clicked()
{
    RecoverFunctionBtn();
}

//主界面切换
void Widget::on_OperaterBtn_clicked()
{
    ui->MenuStackWidget->setCurrentIndex(0);
    ui->OperaterBtn->setChecked(true);
}
void Widget::on_SettingBtn_clicked()
{
    ui->MenuStackWidget->setCurrentIndex(1);
    ui->SettingBtn->setChecked(true);
}
void Widget::on_InfoBtn_clicked()
{
    ui->MenuStackWidget->setCurrentIndex(2);
    ui->InfoBtn->setChecked(true);
}
void Widget::on_HelpBtn_clicked()
{
    ui->MenuStackWidget->setCurrentIndex(3);
    ui->HelpBtn->setChecked(true);
}


void Widget::on_SpeedlineEdit_textEdited(const QString &arg1)
{
    QString txt = ui->SpeedlineEdit->text();
    // 如果文本中包含 '%', 移除它
    if (txt.contains("%")) {
        txt.remove("%");
        ui->SpeedlineEdit->setText(txt);  // 更新文本
    }
}
void Widget::on_SpeedlineEdit_2_textEdited(const QString &arg1)
{
    QString txt = ui->SpeedlineEdit_2->text();
    // 如果文本中包含 '%', 移除它
    if (txt.contains("%")) {
        txt.remove("%");
        ui->SpeedlineEdit_2->setText(txt);  // 更新文本
    }
}
void Widget::on_SpeedlineEdit_3_textEdited(const QString &arg1)
{
    QString txt = ui->SpeedlineEdit_3->text();
    // 如果文本中包含 '%', 移除它
    if (txt.contains("%")) {
        txt.remove("%");
        ui->SpeedlineEdit_3->setText(txt);  // 更新文本
    }
}

//关节角点动操作
void Widget::JointPointPress(QString str1, QString str2)
{
    if(Globals::clampisOK){
        if(str1 == "J1"){str1 = "Z1";};
        if(str1 == "J2"){str1 = "Z2";};
        if(str1 == "J3"){str1 = "Z3";};
        if(str1 == "J4"){str1 = "J1";};
        if(str1 == "J5"){str1 = "J2";};
        if(str1 == "J6"){str1 = "J3";};
        if(str1 == "J7"){str1 = "Z4";};
        QString msg;
        msg = str1 + (str2 == "Up" ? "&c" : "&cc");
        QByteArray msgbody = msg.toUtf8();
        emit TcpMgr::GetInstance()->sig_send_data("mjot", msgbody);
    }
}
void Widget::JointPointRelease(QString str1, QString str2)
{
    if(Globals::clampisOK) {
        if(str1 == "J1"){str1 = "Z1";};
        if(str1 == "J2"){str1 = "Z2";};
        if(str1 == "J3"){str1 = "Z3";};
        if(str1 == "J4"){str1 = "J1";};
        if(str1 == "J5"){str1 = "J2";};
        if(str1 == "J6"){str1 = "J3";};
        if(str1 == "J7"){str1 = "Z4";};
        QString msg = str1 + "&s";
        QByteArray msgbody = msg.toUtf8();
        Globals::clampisOK = false;
        DisableFunctionBtn();
        emit TcpMgr::GetInstance()->sig_send_data("mjot", msgbody);
    }
}


void Widget::on_ClampWidgetBtn_clicked()
{
    QString msg = "0";
    QByteArray msgbody = msg.toUtf8();
    emit TcpMgr::GetInstance()->sig_send_data("swcl", msgbody);
    cw->set_sw(true);
    cw->show();
}

void Widget::on_ClampWidgetBtn_2_clicked()
{
    QString msg = "1";
    QByteArray msgbody = msg.toUtf8();
    emit TcpMgr::GetInstance()->sig_send_data("swcl", msgbody);
    cw2->set_sw(false);
    cw2->show();
}

void Widget::on_LockBtn_clicked()
{
    lw->show();
}

void Widget::on_DownloadBeginBtn_clicked()
{
    dw->show();
}


void Widget::on_openfile_clicked()
{
    QString filepath = "C:\\Users\\futur\\Desktop\\0068操作说明.docx";
    QUrl url = QUrl::fromLocalFile(filepath);
    QDesktopServices::openUrl(url);
}


void Widget::on_max10Btn_clicked()
{
    MAXSPEED = 10;
}
void Widget::on_max100Btn_clicked()
{
    MAXSPEED = 100;
}

void Widget::on_lineEdit_speed_editingFinished()
{
    MAXSPEED = ui->lineEdit_speed->text().toInt();
}

void Widget::on_SpeedBtn_clicked()
{

    QString iniFilePath = QCoreApplication::applicationDirPath() + "/config.ini";
    // 创建 QSettings 对象
    QSettings settings(iniFilePath, QSettings::IniFormat);

    // 写入值到 [speed] 部分
    settings.beginGroup("speed");  // 进入 [speed] 部分

    // 写入各个值
    settings.setValue("DirSpeed", Speed);     // 写入 DirSpeed
    settings.setValue("JointSpeed", JointSpeed);   // 写入 JointSpeed
    settings.setValue("MAXSpeed", MAXSPEED);     // 写入 MAXSpeed

    settings.endGroup();  // 结束 [speed] 部分

    // 确保立即写入文件而不是等到 QSettings 对象销毁
    settings.sync();

    // 检查是否写入成功
    if (settings.status() != QSettings::NoError) {
        qDebug() << "写入配置文件时出错!";
    }

    QString msg = QString::number(Speed) + "&" + QString::number(JointSpeed);
    QByteArray msgbody = msg.toUtf8();
    emit TcpMgr::GetInstance()->sig_send_data("sped", msgbody);
}

bool ish = false;
void Widget::on_HorizenHoldBtn_clicked()
{
    QString msg;
    if(!ish){
        ish = true;
        ui->HorizenHoldBtn->setText("水平保持开启");
        msg = "Horizen&On";
        ui->HorizenHoldBtn->setStyleSheet(ON);
        ui->VerticalHoldBtn->setDisabled(true);
    }else{
        ish = false;
        ui->HorizenHoldBtn->setText("水平保持关闭");
        msg = "Horizen&Off";
       ui->HorizenHoldBtn->setStyleSheet(OFF);
        ui->VerticalHoldBtn->setDisabled(false);
    }
    QByteArray msgbody = msg.toUtf8();
    emit TcpMgr::GetInstance()->sig_send_data("clap", msgbody);
}

bool isv = false;
void Widget::on_VerticalHoldBtn_clicked()
{
    QString msg;
    if(!isv){
        isv = true;
        ui->VerticalHoldBtn->setText("垂直保持开启");
        msg = "Vertical&On";
        ui->VerticalHoldBtn->setStyleSheet(ON);
        ui->HorizenHoldBtn->setDisabled(true);
    }else{
        isv = false;
        ui->VerticalHoldBtn->setText("垂直保持关闭");
        msg = "Vertical&Off";
        ui->VerticalHoldBtn->setStyleSheet(OFF);
        ui->HorizenHoldBtn->setDisabled(false);
    }
    QByteArray msgbody = msg.toUtf8();
    emit TcpMgr::GetInstance()->sig_send_data("clap", msgbody);
}


void Widget::on_SVBtn_clicked()
{
    QString msg = "1";
    QByteArray msgbody = msg.toUtf8();
    emit TcpMgr::GetInstance()->sig_send_data("svrs", msgbody);

    // auto str = "on_SVBtn_clicked:"+msgbody;
    // ADebug(str,true);
}

void Widget::on_ModelcheckBox_control_stateChanged(int arg1)
{
    // qDebug()<<"arg1 "<<arg1;
    QString msg = "";
    if(arg1 == 0){
        msg = "0";

    }else{
        msg = "1";
    }
    QByteArray msgbody = msg.toUtf8();
    emit TcpMgr::GetInstance()->sig_send_data("ctrl", msgbody);
}

void Widget::checkFolder()
{
    auto str = "F:/model/L2dMotion/wave/images/train";
    loadAndShowNextImage(str);
}

void Widget::onResultImage(const QImage &img)
{
    cmw->imglabel->setPixmap(QPixmap::fromImage(img).scaled(cmw->imglabel->size(), Qt::KeepAspectRatio));
}

void Widget::loadAndShowNextImage(QString str)
{
    // 获取文件夹中的所有图片文件，并按修改时间排序
    QDir dir(str);
    QStringList filters = {"*.jpg", "*.jpeg", "*.png", "*.bmp", "*.gif", "*.tiff"};
    QStringList imageFiles = dir.entryList(filters, QDir::Files, QDir::Time); // 按修改时间排序

    if (imageFiles.isEmpty()) {
        qDebug() << "No images to show.";
        return;
    }

    // 反转文件列表，使最早的文件排在最前面
    std::reverse(imageFiles.begin(), imageFiles.end());

    // 获取最早的一张图片
    QString imageName = imageFiles.first();
    QString imagePath = dir.filePath(imageName);

    // 显示图片
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull()) {
        // ui->imglabel->setPixmap(pixmap.scaled(ui->imglabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        qDebug() << "Showing image:" << imagePath;

        // 目标文件夹路径
        QString destinationFolder = "F:/model/L2dMotion/wave/images/processed"; // 替换为你的目标文件夹路径
        QDir destDir(destinationFolder);

        // 如果目标文件夹不存在，则创建
        if (!destDir.exists()) {
            destDir.mkpath(".");
        }

        // 移动文件到目标文件夹
        QString destinationPath = destDir.filePath(imageName);
        if (QFile::rename(imagePath, destinationPath)) {
            qDebug() << "Moved image to:" << destinationPath;
        } else {
            qDebug() << "Failed to move image:" << imagePath;
        }
    } else {
        qDebug() << "Failed to load image:" << imagePath;
    }
}




void Widget::on_clampdzBtn_clicked()
{

    ui->MenuStackWidget->setCurrentIndex(0);
    ui->clampdzBtn->setChecked(true);

    // 1. 确保 cw 没有旧的父控件
    cw2->hide();
    QString msg = "0";
    QByteArray msgbody = msg.toUtf8();
    emit TcpMgr::GetInstance()->sig_send_data("swcl", msgbody);
    cw->set_sw(true);

    cw->setParent(nullptr);

    // 2. 设置新的父控件
    cw->setParent(ui->clampWidget);

    // 3. 设置大小策略（允许扩展）
    cw->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 4. 检查 clampWidget 是否已有布局
    if (!ui->clampWidget->layout()) {
        // 如果没有布局，创建一个新的
        QVBoxLayout *layout = new QVBoxLayout(ui->clampWidget);
        layout->addWidget(cw);
        ui->clampWidget->setLayout(layout);
    } else {
        // 如果已有布局，直接添加
        ui->clampWidget->layout()->addWidget(cw);
    }
    cw->show();
    cmw->dz();
    // 6. 强制刷新布局
    ui->clampWidget->update();
}


void Widget::on_clampwbBtn_clicked()
{

    ui->MenuStackWidget->setCurrentIndex(0);
    ui->clampwbBtn->setChecked(true);

    cw->hide();
    QString msg = "1";
    QByteArray msgbody = msg.toUtf8();
    emit TcpMgr::GetInstance()->sig_send_data("swcl", msgbody);
    cw2->set_sw(false);

    cw2->setParent(nullptr);

    // 2. 设置新的父控件
    cw2->setParent(ui->clampWidget);

    // 3. 设置大小策略（允许扩展）
    cw2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 4. 检查 clampWidget 是否已有布局
    if (!ui->clampWidget->layout()) {
        // 如果没有布局，创建一个新的
        QVBoxLayout *layout = new QVBoxLayout(ui->clampWidget);
        layout->addWidget(cw2);
        ui->clampWidget->setLayout(layout);
    } else {
        // 如果已有布局，直接添加
        ui->clampWidget->layout()->addWidget(cw2);
    }
    cw2->show();
    cmw->wb();
    // 6. 强制刷新布局
    ui->clampWidget->update();
}


void Widget::on_CamWidgetBtn_clicked()
{
    cmw->show();
}

