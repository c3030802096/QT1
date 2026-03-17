#ifndef CAMWIDGET_H
#define CAMWIDGET_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class CamWidget;
}

class CamWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CamWidget(QWidget *parent = nullptr);
    ~CamWidget();

    QLabel * imglabel;

    void dz();
    void wb();
private slots:
    void on_camera_2D_Btn_clicked();

    void on_camera_3D_Btn_clicked();

    void on_ModelcheckBox_control_stateChanged(int arg1);

private:
    Ui::CamWidget *ui;
};

#endif // CAMWIDGET_H
