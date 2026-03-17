#ifndef CLAMPWIDGET_H
#define CLAMPWIDGET_H

#include <QWidget>
#include "qpushbutton.h"
#include "singleton.h"
#include <Global.h>

namespace Ui {
class ClampWidget;
}

class ClampWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClampWidget(QWidget *parent = nullptr);
    ~ClampWidget();
    QList<QPushButton*> clampBtns;
    QList<QPushButton*> clampBtns2;
    QList<QPushButton*> gripBtns;

    bool Carmera_Is_On = false;

    void dis(){
        for(auto btn : clampBtns){
            btn->setDisabled(true);
        }
        for(auto btn : clampBtns2){
            btn->setDisabled(true);
        }
        for(auto btn : gripBtns){
            btn->setDisabled(true);
        }

    }
    void recov();

    bool is_hz_cp = false;
    void set_sw(bool p);

    bool c2_is_on = false;
    bool c1_is_on = false;

private slots:
    void on_C3Down_Btn_pressed();
    void on_C3Up_Btn_released();
    void on_C3Down_Btn_released();
    void on_C3Up_Btn_pressed();
    void on_C3Down_Btn_2_pressed();
    void on_C3Down_Btn_2_released();
    void on_C3Up_Btn_2_pressed();
    void on_C3Up_Btn_2_released();
    void on_C1C2grip_Btn_pressed();
    void on_C1C2grip_Btn_released();
    void on_C1C2release_Btn_pressed();
    void on_C1C2release_Btn_released();
    void on_C3grip_Btn_pressed();
    void on_C3grip_Btn_released();
    void on_C3release_Btn_pressed();
    void on_C3release_Btn_released();
    void on_pushButton_recov_clicked();

    void on_C1C2grip_Btn_clicked();

    void on_pushButton_speed_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_lineEdit_editingFinished();

    void on_pushButton_recov_2_clicked();

private:
    Ui::ClampWidget *ui;

    void updateClamp(QString str1, QString str2);
    QString BTNCLICKED_STY = "QPushButton {"
                             "    background-color: rgb(50, 170, 255);"  // 正常状态
                             "    border: 2px solid rgb(30, 150, 240);"  // 可选：边框
                             "    border-radius: 5px;"                  // 可选：圆角
                             "    color: white;"                        // 可选：文字颜色
                             "}"
                             "QPushButton:pressed {"
                             "    background-color: rgb(30, 50, 255);"  // 按下状态
                             "}";

    QString BTNON_STY = "QPushButton {"
                             "    background-color: rgb(85, 255, 0);"  // 正常状态
                             "    border: 2px solid rgb(40, 200, 0);"  // 可选：边框
                             "    border-radius: 5px;"                  // 可选：圆角
                             "    color: white;"                        // 可选：文字颜色
                             "}"
                             "QPushButton:pressed {"
                             "    background-color: rgb(40, 200, 0);"  // 按下状态
                             "}";

    QString BTNON_F = "QPushButton {"
                        "    background-color: rgb(150, 150, 150);"  // 正常状态
                        "    border: 2px solid rgb(30, 150, 240);"    // 可选：边框
                        "    border-radius: 5px;"                  // 可选：圆角
                        "    color: white;"                        // 可选：文字颜色
                      "}";


};

#endif // CLAMPWIDGET_H
