#include "downloadwidget.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "qtimer.h"
#include "ui_downloadwidget.h"
#include <QRandomGenerator>
#include "TcpMgr.h"
DownLoadWidget::DownLoadWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DownLoadWidget)
{
    ui->setupUi(this);

    // ui->tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    // ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(this,&DownLoadWidget::sig_download,TcpMgr::GetInstance().get(),&TcpMgr::slot_sendDownload);
    connect(TcpMgr::GetInstance().get(),&TcpMgr::sig_download,this,&DownLoadWidget::slot_download);
}

DownLoadWidget::~DownLoadWidget()
{
    delete ui;
}

//安装请求
void DownLoadWidget::on_RequestDownBtn_clicked()
{
    // 示例数据
    QByteArray requestData1 = R"({"Category":"请求腕臂安装数据","SN":"null","ItemType":"null"})";
    QByteArray requestData2 = R"({"Category":"请求吊柱安装数据","SN":"null","ItemType":"null"})";

    emit sig_download(requestData1);
    emit sig_download(requestData2);
}

void DownLoadWidget::on_CancelDownBtn_clicked()
{
    // 示例数据
    QByteArray requestData1 =R"({"Category":"腕臂加工完成","SN":"SD01","ItemType":"横梁"})";
    QByteArray requestData2 =R"({"Category":"吊柱加工完成","SN":"SD01","ItemType":"横梁"})";

    emit sig_download(requestData1);
    emit sig_download(requestData2);
}

void DownLoadWidget::slot_download(QString str)
{
    if(str == "响应请求数据") {
        ui->tiplabel->setText("服务器相响应请求数据");
    }
    if(str == "未找到待加工数据") {
        ui->tiplabel->setText("服务器未找到待加工数据");
    }
    if(str == "响应加工完成") {
        ui->tiplabel->setText("服务器响应加工完成");
    }
}

