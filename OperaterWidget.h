#ifndef OPERATERWIDGET_H
#define OPERATERWIDGET_H

#include "qlabel.h"
#include <QWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QEvent>
#include <QSlider>
#include "qlineedit.h"
#include "singleton.h"
#include <Global.h>
#include <QLineEdit>
#include <QSettings>
#include <QProcess>
#include <QMessageBox>
#include "zmqreceiverthread.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class DownLoadWidget;
class ClampWidget;
class LockWidget;
class CamWidget;
class Widget : public QWidget, public Singleton<Widget>
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void DisableFunctionBtn();
    void RecoverFunctionBtn();
    void BANSCONTROL();

    bool isstat = false;
    QLabel* tiplb;
    ClampWidget * cw = nullptr;
    ClampWidget * cw2 = nullptr;
    LockWidget * lw = nullptr;
    DownLoadWidget * dw = nullptr;
    CamWidget* cmw = nullptr;

    QString getEdgeBrowserPath() {
        // 定位Edge的注册表路径
        QSettings settings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\msedge.exe", QSettings::NativeFormat);
        QString edgePath = settings.value(".").toString();

        // 检查路径是否有效
        if (edgePath.isEmpty()) {
            QMessageBox::warning(nullptr, "Edge路径未找到", "无法找到Microsoft Edge的安装路径！");
        }

        return edgePath;
    }

    void openDoxFileWithEdge(const QString &filePath) {
        QString edgePath = getEdgeBrowserPath();

        // 使用startDetached启动进程
        if (!QProcess::startDetached(edgePath, QStringList() << filePath)) {
            QMessageBox::critical(nullptr, "错误", "无法启动Edge浏览器！");
        }
    }


signals:
    void sig_switch_to_login();
    void sig_connect_tcp(std::shared_ptr<ServerInfo>);
    void sig_sendmsg(const QByteArray &jsonData);

private slots:
    void on_WiFiBtn_clicked();
    void on_SpeedlineEdit_editingFinished();
    void on_SpeedSlider_valueChanged(int value);
    void on_ModelcheckBox_toggled(bool checked);
    void on_SpeedSlider_2_valueChanged(int value);
    void on_LoginoutBtn_clicked();
    void on_camera_2D_Btn_clicked();
    void on_CloseBtn_clicked();
    void on_ZeroStatusBtn_clicked();
    void on_BeginStatusBtn_clicked();
    void on_SpeedSlider_3_valueChanged(int value);
    void on_OperaterBtn_clicked();
    void on_SettingBtn_clicked();
    void on_InfoBtn_clicked();
    void on_HelpBtn_clicked();
    void on_ModelcheckBox_allmsg_toggled(bool checked);
    void on_SpeedlineEdit_2_editingFinished();
    void on_SpeedlineEdit_3_editingFinished();
    void on_SpeedlineEdit_textEdited(const QString &arg1);
    void on_SpeedlineEdit_2_textEdited(const QString &arg1);
    void on_SpeedlineEdit_3_textEdited(const QString &arg1);
    void JointPointPress(QString str1, QString str2);
    void JointPointRelease(QString str1, QString str2);
    void on_ClampWidgetBtn_clicked();
    void on_LockBtn_clicked();
    void on_DownloadBeginBtn_clicked();
    void on_openfile_clicked();
    void on_max10Btn_clicked();
    void on_max100Btn_clicked();
    void on_lineEdit_speed_editingFinished();
    void on_SpeedBtn_clicked();
    void on_HorizenHoldBtn_clicked();
    void on_VerticalHoldBtn_clicked();
    void on_SVBtn_clicked();
    void on_ModelcheckBox_control_stateChanged(int arg1);
    void checkFolder(); // 定时检查文件夹
    void onResultImage(const QImage &img);
    void on_ClampWidgetBtn_2_clicked();

    void on_clampdzBtn_clicked();

    void on_clampwbBtn_clicked();

    void on_CamWidgetBtn_clicked();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;
    void closeEvent(QCloseEvent * event) override;


private:
    Ui::Widget *ui;

    ResultReceiver* receiverThread;

    int JNum = 7;
    double Speed = 0;
    double JointSpeed = 0;
    double StatusJointSpeed = 0;
    double MAXSPEED = 100;
    double X_Pos = 0;
    double Y_Pos = 0;
    double Z_Pos = 0;
    double X_Deg = 0;
    double Y_Deg = 0;
    double Z_Deg = 0;
    bool clamp = false;
    QString JointValue[7];
    QString cartesianCoords[6];
    QString clampState[2];
    QString Aimpos[6];
    QString ZeroStatus[13];
    QString BeginStatus[13];
    QString dir;
    QList<QPushButton*>directionBtns;
    QList<QSlider*> Jsliders;
    QList<QPushButton*>JointBtns;
    QList<QLineEdit*> lineEdits;
    QList<QPushButton*> clampBtns;
    QList<QPushButton*> gripBtns;
    QString currentState;
    bool WiFiState = false;
    bool Carmera_Is_On = false;
    QTimer* CurrentTimer;
    int ChangeTime =  500;
    QTimer *cp_timer;
    QTimer *timer300;
    bool isClicked = false;
    void SetCurrentToggled(QString j,bool isChecked);
    void InitStyleSheet();
    void SetX_Pos(QString pos);
    void SetY_Pos(QString pos);
    void SetZ_Pos(QString pos);
    void SetRX_Pos(QString deg);
    void SetRY_Pos(QString deg);
    void SetRZ_Pos(QString deg);
    void updatePosition();
    void updateClampStatus(QString str);
    void updateJoint();
    void InitUserInfo();
    QByteArray getjson();
    void UpDateJointValue(int value);
    void UpDateTime();
    // void UpdateAllData(QString str1, QString str2, QString str3, QString str4);
    void UpdateAllData(QStringList messageparts);
    void connectButton(QPushButton *button, const QString &pressedImage, const QString &releasedImage, QLabel *label);
    void loadAndShowNextImage(QString str);
    void getTip();
    void InitJointBtn();
    void InitDirectionBtn();
    void InitObject();
    void InitSpeed();

    QMap<QString, QString> statusMap;

    QMap<QString, QString> readStatusCodesFromJson(const QString& filePath);

    QString BTNCLICKED_STY = "QPushButton {"
                             "    background-color: rgb(50, 170, 255);"  // 正常状态
                             "    border: 2px solid rgb(30, 150, 240);"  // 可选：边框
                             "    border-radius: 5px;"                  // 可选：圆角
                             "    color: white;"                        // 可选：文字颜色
                             "}"
                             "QPushButton:pressed {"
                             "    background-color: rgb(30, 50, 255);"  // 按下状态
                             "}";
    QString ON = "border: 1px solid;"
                 "background-color: rgb(255, 255, 127);"
                 "border-radius:5px;";

    QString OFF = "border: 1px solid;"
                  "background-color: rgb(178, 178, 89);"
                  "border-radius:5px;";
};
#endif // OPERATERWIDGET_H
