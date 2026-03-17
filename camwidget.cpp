#include "camwidget.h"
#include "ui_camwidget.h"
#include <TcpMgr.h>

CamWidget::CamWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CamWidget)
{
    ui->setupUi(this);


    imglabel = ui->label_img;

    ui->ModelcheckBox_control->setMaximumHeight(20);
}

CamWidget::~CamWidget()
{
    delete ui;
}

void CamWidget::dz()
{
    ui->camera_2D_Btn->hide();
    ui->camera_3D_Btn->show();
}

void CamWidget::wb()
{
    ui->camera_2D_Btn->show();
    ui->camera_3D_Btn->hide();
}

void CamWidget::on_camera_2D_Btn_clicked()
{

}


void CamWidget::on_camera_3D_Btn_clicked()
{

}


void CamWidget::on_ModelcheckBox_control_stateChanged(int arg1)
{
    QString msg = "";
    if(arg1 == 0){
        msg = "0";

    }else{
        msg = "1";
    }
    QByteArray msgbody = msg.toUtf8();
    emit TcpMgr::GetInstance()->sig_send_data("ctrl", msgbody);
}

