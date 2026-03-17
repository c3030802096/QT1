#ifndef LOCKWIDGET_H
#define LOCKWIDGET_H

#include "qpropertyanimation.h"
#include <QWidget>

namespace Ui {
class LockWidget;
}

class LockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LockWidget(QWidget *parent = nullptr);
    ~LockWidget();

    void onSliderReleased();

    void onSliderFull();
    void onValueChanged(int value);
    void onSliderClicked(int value);

protected:
    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent *event) override;
private:
    Ui::LockWidget *ui;
};

#endif // LOCKWIDGET_H
