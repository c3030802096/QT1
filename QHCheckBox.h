
#ifndef QHCHECKBOX_H
#define QHCHECKBOX_H

#include <QCheckBox>
#include <QLabel>

class QHCheckBox : public QCheckBox {
public:
    QHCheckBox(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;

private:
    // 指示器.
    // checked为false时indicator在最左边，为true时indicator在最右边.
    QLabel *m_indicator;
};

#endif // QHCHECKBOX_H
