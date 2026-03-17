#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

#include <QSlider>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QDebug>
#include <QStyle>

class CustomSlider : public QSlider {
    Q_OBJECT

public:
    explicit CustomSlider(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (orientation() == Qt::Horizontal) {
            // 获取鼠标点击位置相对于滑动条的值
            int newValue = QStyle::sliderValueFromPosition(
                minimum(), maximum(), event->pos().x(), width());
            setValue(newValue); // 设置滑动条的值
        } else {
            int newValue = QStyle::sliderValueFromPosition(
                minimum(), maximum(), event->pos().y(), height());
            setValue(newValue);
        }
        // 保留父类默认行为
        QSlider::mousePressEvent(event);
        // 不调用基类的 mousePressEvent，从而禁用点击事件
        //event->ignore();
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        // 触发点击后的归位判断逻辑
        emit sliderClicked(value());
    }

signals:
    void sliderClicked(int value); // 自定义信号，传递当前值
};
#endif // CUSTOMSLIDER_H
