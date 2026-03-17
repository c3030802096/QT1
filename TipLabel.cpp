#include "TipLabel.h"
#include "qapplication.h"
#include "qboxlayout.h"
#include "qguiapplication.h"
#include "qscreen.h"

TipLabel::TipLabel(const QRect &geometry, QWidget *parent)
: QFrame(parent)
{
    setWindowFlags(Qt::FramelessWindowHint| Qt::WindowStaysOnTopHint); // 无边框窗口
    this->show();
    // 设置固定大小为 200x100
    this->setFixedSize(300, 80);
    // 添加一个 QLabel 用于显示文本
    QLabel* label = new QLabel("运动进行中，请等待", this);
    label->setAlignment(Qt::AlignCenter);
    // 设置样式（包括圆角）
    this->setStyleSheet(
        "   background-color: yellow;"
        "   color: black;"
        "   font-size: 20px;"
        "   border-radius: 20px;" // 设置圆角
        );

    // 使用布局将 QLabel 居中
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(label);
    this->setLayout(layout);


    // 根据传入的 geometry 设置位置
    int x = geometry.x() + (geometry.width() - this->width()) / 2; // 水平居中
    int y = geometry.y() + (geometry.height() - this->height()) / 2; // 垂直居中
    this->move(x, y);

    // 设置动画
    setupAnimation();
    // qDebug()<<"label:"<<this->geometry();
}

void TipLabel::setupAnimation()

{
    // 创建属性动画，控制 y 坐标和透明度
    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry", this);
    animation->setDuration(1500);
    animation->setStartValue(this->geometry());

    // 向上移动 100 像素
    QRect endValue = this->geometry();
    endValue.moveTop(endValue.y() - 200);
    animation->setEndValue(endValue);

    // 创建透明度动画
    QPropertyAnimation* opacityAnimation = new QPropertyAnimation(this, "windowOpacity", this);
    opacityAnimation->setDuration(1500);
    opacityAnimation->setStartValue(1.0);
    opacityAnimation->setEndValue(0.0);

    // 启动动画
    animation->start();
    opacityAnimation->start();

    // 动画结束后销毁 Label
    connect(animation, &QPropertyAnimation::finished, this, &TipLabel::deleteLater);
}
