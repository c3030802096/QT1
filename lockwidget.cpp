#include "lockwidget.h"
#include "ui_lockwidget.h"
#include "customslider.h"

LockWidget::LockWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LockWidget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint );
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::FramelessWindowHint);
    ui->slider->setRange(0, 100);  // 设置范围为 0 到 100

    // 连接信号槽
    connect(ui->slider, &CustomSlider::sliderReleased, this, &LockWidget::onSliderReleased);
    connect(ui->slider, &CustomSlider::valueChanged, this, &LockWidget::onValueChanged);
    // 连接自定义信号到槽
    //connect(ui->slider, &CustomSlider::sliderClicked, this, &LockWidget::onSliderClicked);
}

LockWidget::~LockWidget()
{
    delete ui;
}

void LockWidget::onSliderReleased()
{
    int value = ui->slider->value();  // 获取当前滑块值
    int targetValue = (value >= 70) ? 100 : 0;  // 确定目标值

    QPropertyAnimation *animation = new QPropertyAnimation(ui->slider, "value", this);
    animation->setDuration(500);
    animation->setStartValue(value);
    animation->setEndValue(targetValue);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void LockWidget::onSliderFull()
{
    this->close();
}

void LockWidget::onValueChanged(int value)
{
    if (value == 100) {
        this->close();  // 关闭窗口
    }
}

void LockWidget::onSliderClicked(int value)
{

    //ui->slider->setValue(0);
    // qDebug() << "当前滑动条值:" << value;

    // //int targetValue = (value >= 70) ? 100 : 0;

    // // 使用动画自动归位
    // QPropertyAnimation *animation = new QPropertyAnimation(ui->slider, "value", this);
    // animation->setDuration(300); // 动画持续时间
    // animation->setStartValue(value);
    // animation->setEndValue(0);
    // animation->setEasingCurve(QEasingCurve::OutQuad);
    // animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void LockWidget::closeEvent(QCloseEvent *event)
{
    ui->slider->setValue(0);  // 重置滑动条进度
    QWidget::closeEvent(event);  // 保持父类的关闭行为
}

void LockWidget::showEvent(QShowEvent *event)
{
    ui->slider->setValue(0);  // 重置滑动条进度
    QWidget::showEvent(event);
}
