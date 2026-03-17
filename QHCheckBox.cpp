
#include "QHCheckBox.h"

#include <QStyle>
#include <QMouseEvent>
#include <QApplication>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>

QHCheckBox::QHCheckBox(QWidget *parent)
    : QCheckBox (parent)
{
    m_indicator = new QLabel(this);

    setMinimumHeight(40);
    setContentsMargins(2, 2, 2, 2);
    setAttribute(Qt::WA_StyledBackground, true);
    setProperty("class", "MyCheckBox");
    m_indicator->setProperty("class", "MyCheckBoxIndicator");

    // 添加阴影.
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(10);
    effect->setOffset(0, 1);
    m_indicator->setGraphicsEffect(effect);
    // 设置样式.
    qApp->setStyleSheet(R"(
                        .MyCheckBox[checked=true ] { background: rgb(17,119,181) }
                        .MyCheckBox[checked=false] { background: rgb(200,200,200)}
                        .MyCheckBoxIndicator { background: white }
    )");

    // 动态调整indicator的位置.
    QPropertyAnimation *animation = new QPropertyAnimation(m_indicator, "pos", this);
    connect(this, &QCheckBox::toggled, [=] {
        int leftMargin = contentsMargins().left();
        int x = isChecked() ? width() - m_indicator->width() - leftMargin : leftMargin;
        int y = leftMargin;

        animation->stop();
        animation->setDuration(200);
        animation->setEndValue(QPoint(x, y));
        animation->setEasingCurve(QEasingCurve::InOutCubic);
        animation->start();
        // 更新样式.
        style()->polish(this);
    });
}

void QHCheckBox::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    // 这里啥都不用做，用来清除QCheckBox的默认样式.
}

void QHCheckBox::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)

    int leftMargin = contentsMargins().left();
    int x = isChecked() ? width() - m_indicator->width() - leftMargin : leftMargin;
    int y = leftMargin;
    int w = height() - leftMargin *2;
    int h = w;
    m_indicator->setGeometry(x, y, w, h);

    setMinimumWidth(height() * 2);

    // 更新checkbox和indicator的圆.
    setStyleSheet(QString(".MyCheckBox { border-radius: %1px } .MyCheckBoxIndicator { border-radius: %2px }")
                      .arg(height() / 2)
                      .arg(m_indicator->height() / 2));
}

void QHCheckBox::mousePressEvent(QMouseEvent *e)
{
    e->accept();
    setChecked(!isChecked());
}
