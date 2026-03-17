#include "clampwidget.h"
#include "ui_clampwidget.h"
#include <QDebug>
#include <QTimer>
#include <QTime>
#include "TcpMgr.h"
#include <QString>
#include <QScreen>
#include <QMessageBox>
#include "Global.h"

ClampWidget::ClampWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClampWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint );
    setWindowModality(Qt::ApplicationModal);
    // setMinimumSize(800,600);
    clampBtns = {ui->Clamp_x_Down_Btn, ui->Clamp_x_Up_Btn,
                 ui->Clamp_y_Down_Btn, ui->Clamp_y_Up_Btn,
                 ui->Clamp_z_Down_Btn, ui->Clamp_z_Up_Btn};

    gripBtns = {ui->C1C2grip_Btn,ui->C1C2release_Btn,
                ui->C3grip_Btn  ,ui->C3release_Btn};

    clampBtns2 = {ui->C3Down_Btn,ui->C3Down_Btn_2,
                ui->C3Up_Btn,ui->C3Up_Btn_2};

    ui->pushButton_recov->setStyleSheet(BTNCLICKED_STY);
    ui->pushButton_speed->setStyleSheet(BTNCLICKED_STY);
    ui->pushButton_recov_2->setStyleSheet(BTNCLICKED_STY);

    for(QPushButton* btn : gripBtns) {
        btn->setStyleSheet(BTNCLICKED_STY);

    }
    for(QPushButton* btn : clampBtns2) {
        btn->setStyleSheet(BTNCLICKED_STY);
    }
    for(QPushButton* btn : clampBtns) {
        QString firstPart = btn->objectName().section('_', 1, 1); // 第一个部分 方向
        QString secondPart = btn->objectName().section('_', 2, 2); // 第二个部分 增减
        btn->setStyleSheet(BTNCLICKED_STY);
        connect(btn,&QPushButton::pressed,[=](){
            Globals::clamp_motionisok = false;
            updateClamp(firstPart,secondPart);});
        connect(btn,&QPushButton::released,[=](){
            QString msg = firstPart + "&coarse&s";
            QByteArray msgbody = msg.toUtf8();
            if(Globals::clampisOK){
                Globals::clampisOK = false;
                dis();
                TcpMgr::GetInstance()->sig_send_data("mclp",msgbody);
            }
        });
    }
    connect(TcpMgr::GetInstance().get(),&TcpMgr::sig_clamp_ok,[=](){
        recov();
        Globals::clampisOK = true;Globals::clamp_motionisok = true;});

    // ui->label_clamp2->hide();
    // ui->label_64->hide();
}

ClampWidget::~ClampWidget()
{
    delete ui;
}

void ClampWidget::recov()
{
    for(auto btn : clampBtns){
        btn->setDisabled(false);
    }
    for(auto btn : clampBtns2){
        btn->setDisabled(false);
    }
    for(auto btn : gripBtns){
        if(!is_hz_cp){//wb
            btn->setDisabled(false);
        }else{//dz
            btn->setDisabled(false);
            if(!c2_is_on){
                ui->C1C2grip_Btn->setDisabled(true);
            }
            if(!c1_is_on){
                ui->C3release_Btn->setDisabled(true);
            }
        }

    }



}

void ClampWidget::set_sw(bool p)
{
    if(p){
        is_hz_cp = true;
        this->setWindowTitle("吊柱夹具窗口");
        ui->label_pz->setText("平夹");
        ui->label_bz->setText("抱夹");
        ui->label_2->hide();
        ui->C3Down_Btn->hide();
        ui->C3Down_Btn_2->hide();
        ui->C3Up_Btn->hide();
        ui->C3Up_Btn_2->hide();
        ui->label_51->hide();
        ui->label_57->hide();
        // ui->widget_8->hide();
        ui->horizontalSlider->hide();

        ui->lineEdit->hide();
        ui->pushButton_speed->hide();
        ui->C1C2grip_Btn->setDisabled(true);
        ui->C3release_Btn->setDisabled(true);
        ui->C1C2grip_Btn->setStyleSheet(BTNON_F);
        ui->C3release_Btn->setStyleSheet(BTNON_F);

    }else{
        is_hz_cp = false;
        this->setWindowTitle("腕臂夹具窗口");
        ui->label_pz->setText("斜腕");
        ui->label_bz->setText("平腕");
        ui->label_2->show();
        ui->C3Down_Btn->show();
        ui->C3Down_Btn_2->show();
        ui->C3Up_Btn->show();
        ui->C3Up_Btn_2->show();
        ui->label_51->show();
        ui->label_57->show();
        // ui->widget_8->hide();
    }
}

void ClampWidget::updateClamp(QString str1, QString str2)
{
    if(Globals::clampisOK == true){
        QString dir;
        if(str2 == "Up" || str2 == "Down")
            dir = str2 == "Up"?"+":"-";

        QString msg = str1 + "&coarse&" + dir;
        QByteArray msgbody = msg.toUtf8();
        emit TcpMgr::GetInstance()->sig_send_data("mclp", msgbody);

        qDebug()<<"msg:"<<msg;
    }else{

    }
}

//x微调
void ClampWidget::on_C3Down_Btn_pressed()
{
    if(Globals::clampisOK == true){
        QString msg = "x&fine&-";
        QByteArray msgbody = msg.toUtf8();
        TcpMgr::GetInstance()->sig_send_data("mclp",msgbody);
    }
}
void ClampWidget::on_C3Down_Btn_released()
{
    if(Globals::clampisOK == true){
        QString msg = "x&fine&s";
        QByteArray msgbody = msg.toUtf8();
        Globals::clampisOK = false;
        dis();
        TcpMgr::GetInstance()->sig_send_data("mclp",msgbody);
    }
}
void ClampWidget::on_C3Up_Btn_pressed()
{
    if(Globals::clampisOK){
        QString msg = "x&fine&+";
        QByteArray msgbody = msg.toUtf8();
        TcpMgr::GetInstance()->sig_send_data("mclp",msgbody);
    }

}
void ClampWidget::on_C3Up_Btn_released()
{
    if(Globals::clampisOK){
        QString msg = "x&fine&s";
        QByteArray msgbody = msg.toUtf8();
        Globals::clampisOK = false;
        dis();
        TcpMgr::GetInstance()->sig_send_data("mclp",msgbody);
    }
}
//y微调
void ClampWidget::on_C3Down_Btn_2_pressed()
{
    if(Globals::clampisOK){
        QString msg = "y&fine&-";
        QByteArray msgbody = msg.toUtf8();
        TcpMgr::GetInstance()->sig_send_data("mclp",msgbody);
    }

}
void ClampWidget::on_C3Down_Btn_2_released()
{
    if(Globals::clampisOK){
        QString msg = "y&fine&s";
        QByteArray msgbody = msg.toUtf8();
        Globals::clampisOK = false;
        dis();
        TcpMgr::GetInstance()->sig_send_data("mclp",msgbody);
    }
}
void ClampWidget::on_C3Up_Btn_2_pressed()
{
    if(Globals::clampisOK){
        QString msg = "y&fine&+";
        QByteArray msgbody = msg.toUtf8();
        TcpMgr::GetInstance()->sig_send_data("mclp",msgbody);
    }
}
void ClampWidget::on_C3Up_Btn_2_released()
{
    if(Globals::clampisOK){
        QString msg = "y&fine&s";
        QByteArray msgbody = msg.toUtf8();
        Globals::clampisOK = false;
        dis();
        TcpMgr::GetInstance()->sig_send_data("mclp",msgbody);
    }
}

//clamp1,clamp2松紧
void ClampWidget::on_C1C2grip_Btn_pressed()
{
    if(is_hz_cp){
        c1_is_on = false;
        ui->C3release_Btn->setDisabled(true);
        ui->C3release_Btn->setStyleSheet(BTNON_F);
    }


    ui->C1C2grip_Btn->setStyleSheet(BTNON_STY);
    ui->C1C2release_Btn->setStyleSheet(BTNCLICKED_STY);

    if(is_hz_cp){
        if(Globals::clampisOK == true){
            QString msg = "clamp1&grip";
            QByteArray msgbody = msg.toUtf8();
            emit TcpMgr::GetInstance()->sig_send_data("aclp", msgbody);
            Globals::clamp_motionisok = false;
        }
    }else{
        if(Globals::clampisOK == true){
            QString msg = "clamp1&release";
            QByteArray msgbody = msg.toUtf8();
            emit TcpMgr::GetInstance()->sig_send_data("aclp", msgbody);
            Globals::clamp_motionisok = false;
        }
    }



}
void ClampWidget::on_C1C2grip_Btn_released()
{
    if(Globals::clampisOK == true){
        QString msg = "clamp1&stop";
        QByteArray msgbody = msg.toUtf8();
        Globals::clampisOK = false;
        dis();
        emit TcpMgr::GetInstance()->sig_send_data("aclp", msgbody);
    }

}
void ClampWidget::on_C1C2release_Btn_pressed()
{

    if(is_hz_cp){
        c1_is_on = true;
        ui->C3release_Btn->setDisabled(false);
        ui->C3release_Btn->setStyleSheet(BTNCLICKED_STY);

        if(c2_is_on){
            ui->C1C2grip_Btn->setStyleSheet(BTNCLICKED_STY);
        }
    }else{
        ui->C1C2grip_Btn->setStyleSheet(BTNCLICKED_STY);
    }

    ui->C1C2release_Btn->setStyleSheet(BTNON_STY);

    if(is_hz_cp){
        if(Globals::clampisOK == true){
            QString msg = "clamp1&release";
            QByteArray msgbody = msg.toUtf8();
            emit TcpMgr::GetInstance()->sig_send_data("aclp", msgbody);
            Globals::clamp_motionisok = false;
        }
    }else{
        if(Globals::clampisOK == true){
            QString msg = "clamp1&grip";
            QByteArray msgbody = msg.toUtf8();
            emit TcpMgr::GetInstance()->sig_send_data("aclp", msgbody);
            Globals::clamp_motionisok = false;
        }
    }
}
void ClampWidget::on_C1C2release_Btn_released()
{

    if(Globals::clampisOK == true){
        QString msg = "clamp1&stop";
        QByteArray msgbody = msg.toUtf8();
        Globals::clampisOK = false;
        dis();
        emit TcpMgr::GetInstance()->sig_send_data("aclp", msgbody);
    }
}


//Clamp3松紧
void ClampWidget::on_C3grip_Btn_pressed()
{
    if(is_hz_cp){
        c2_is_on = true;
        ui->C1C2grip_Btn->setDisabled(false);
        ui->C1C2grip_Btn->setStyleSheet(BTNCLICKED_STY);
        if(c1_is_on){
            ui->C3release_Btn->setStyleSheet(BTNCLICKED_STY);
        }
    }else{
        ui->C3release_Btn->setStyleSheet(BTNCLICKED_STY);
    }


    ui->C3grip_Btn->setStyleSheet(BTNON_STY);


    if(Globals::clampisOK == true){
        QString msg = "clamp2&grip";
        QByteArray msgbody = msg.toUtf8();
        emit TcpMgr::GetInstance()->sig_send_data("aclp", msgbody);
        Globals::clamp_motionisok = false;
    }
}
void ClampWidget::on_C3grip_Btn_released()
{
    if(Globals::clampisOK == true){
        QString msg = "clamp2&stop";
        QByteArray msgbody = msg.toUtf8();
        Globals::clampisOK = false;
        dis();
        emit TcpMgr::GetInstance()->sig_send_data("aclp", msgbody);
    }
}

void ClampWidget::on_C3release_Btn_pressed()
{
    if(is_hz_cp){
        c2_is_on = false;
        ui->C1C2grip_Btn->setDisabled(true);
        ui->C1C2grip_Btn->setStyleSheet(BTNON_F);
    }


    ui->C3release_Btn->setStyleSheet(BTNON_STY);
    ui->C3grip_Btn->setStyleSheet(BTNCLICKED_STY);
    if(Globals::clampisOK == true){
        QString msg = "clamp2&release";
        QByteArray msgbody = msg.toUtf8();
        emit TcpMgr::GetInstance()->sig_send_data("aclp", msgbody);
        Globals::clamp_motionisok = false;
    }
}
void ClampWidget::on_C3release_Btn_released()
{
    if(Globals::clampisOK == true){
        QString msg = "clamp2&stop";
        QByteArray msgbody = msg.toUtf8();
        Globals::clampisOK = false;
        dis();
        emit TcpMgr::GetInstance()->sig_send_data("aclp", msgbody);
    }
}


void ClampWidget::on_pushButton_recov_clicked()
{
    QString msg = "1";
    QByteArray msgbody = msg.toUtf8();
    emit TcpMgr::GetInstance()->sig_send_data("cprc", msgbody);
}


void ClampWidget::on_C1C2grip_Btn_clicked()
{

}


void ClampWidget::on_pushButton_speed_clicked()
{
    QString msg = ui->lineEdit->text();
    QByteArray msgbody = msg.toUtf8();
    emit TcpMgr::GetInstance()->sig_send_data("clsp", msgbody);
}

int maxspeed = 10;
void ClampWidget::on_horizontalSlider_valueChanged(int value)
{
    int minValue = ui->horizontalSlider->minimum(); // 获取滑块的最小值
    int maxValue = ui->horizontalSlider->maximum(); // 获取滑块的最大值
    // 计算百分比进度
    double percentage = static_cast<int>((static_cast<double>(value - minValue) / (maxValue - minValue)) * 100);
    auto Speed = (percentage/100.00) * maxspeed;
    // 将百分比转换为字符串并显示在 SpeedlineEdit 上
    ui->lineEdit->setText(QString::number(Speed));
}


void ClampWidget::on_lineEdit_editingFinished()
{
    bool ok;
    auto txt = ui->lineEdit->text();
    double value = ui->lineEdit->text().toDouble(&ok);
    // 检查转换是否成功
    if (!ok) {
        return;  // 如果转换失败，直接返回
    }
    // 限制值范围
    if (value > 10) {
        value = 10;
    }
    if (value < 0) {
        value = 0;
    }
    auto Speed = (value / 10.00) * maxspeed;
    ui->horizontalSlider->setValue(static_cast<int>(value)*10);
    ui->lineEdit->setText(QString::number(Speed));
}


void ClampWidget::on_pushButton_recov_2_clicked()
{
    QString msg = "1";
    QByteArray msgbody = msg.toUtf8();
    emit TcpMgr::GetInstance()->sig_send_data("clzc", msgbody);
}

