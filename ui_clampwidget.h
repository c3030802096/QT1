/********************************************************************************
** Form generated from reading UI file 'clampwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLAMPWIDGET_H
#define UI_CLAMPWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClampWidget
{
public:
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_23;
    QHBoxLayout *horizontalLayout_43;
    QPushButton *C3Down_Btn;
    QLabel *label_51;
    QPushButton *C3Up_Btn;
    QHBoxLayout *horizontalLayout_53;
    QPushButton *C3Down_Btn_2;
    QLabel *label_57;
    QPushButton *C3Up_Btn_2;
    QHBoxLayout *horizontalLayout_4;
    QSlider *horizontalSlider;
    QLineEdit *lineEdit;
    QPushButton *pushButton_speed;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *C1C2grip_Btn;
    QLabel *label_pz;
    QPushButton *C1C2release_Btn;
    QHBoxLayout *horizontalLayout_44;
    QPushButton *C3grip_Btn;
    QLabel *label_bz;
    QPushButton *C3release_Btn;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_50;
    QPushButton *Clamp_z_Down_Btn;
    QLabel *label_54;
    QPushButton *Clamp_z_Up_Btn;
    QHBoxLayout *horizontalLayout_48;
    QPushButton *Clamp_x_Down_Btn;
    QLabel *label_52;
    QPushButton *Clamp_x_Up_Btn;
    QHBoxLayout *horizontalLayout_49;
    QPushButton *Clamp_y_Down_Btn;
    QLabel *label_53;
    QPushButton *Clamp_y_Up_Btn;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_recov_2;
    QPushButton *pushButton_recov;

    void setupUi(QWidget *ClampWidget)
    {
        if (ClampWidget->objectName().isEmpty())
            ClampWidget->setObjectName("ClampWidget");
        ClampWidget->resize(517, 513);
        horizontalLayout_5 = new QHBoxLayout(ClampWidget);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_2 = new QLabel(ClampWidget);
        label_2->setObjectName("label_2");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        label_2->setFont(font);

        verticalLayout_5->addWidget(label_2);

        verticalLayout_23 = new QVBoxLayout();
        verticalLayout_23->setSpacing(4);
        verticalLayout_23->setObjectName("verticalLayout_23");
        horizontalLayout_43 = new QHBoxLayout();
        horizontalLayout_43->setSpacing(0);
        horizontalLayout_43->setObjectName("horizontalLayout_43");
        horizontalLayout_43->setContentsMargins(0, -1, 0, -1);
        C3Down_Btn = new QPushButton(ClampWidget);
        C3Down_Btn->setObjectName("C3Down_Btn");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(C3Down_Btn->sizePolicy().hasHeightForWidth());
        C3Down_Btn->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(35);
        font1.setBold(true);
        C3Down_Btn->setFont(font1);
        C3Down_Btn->setCursor(QCursor(Qt::PointingHandCursor));
        C3Down_Btn->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_43->addWidget(C3Down_Btn);

        label_51 = new QLabel(ClampWidget);
        label_51->setObjectName("label_51");
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        label_51->setFont(font2);
        label_51->setAlignment(Qt::AlignCenter);

        horizontalLayout_43->addWidget(label_51);

        C3Up_Btn = new QPushButton(ClampWidget);
        C3Up_Btn->setObjectName("C3Up_Btn");
        sizePolicy.setHeightForWidth(C3Up_Btn->sizePolicy().hasHeightForWidth());
        C3Up_Btn->setSizePolicy(sizePolicy);
        C3Up_Btn->setFont(font1);
        C3Up_Btn->setCursor(QCursor(Qt::PointingHandCursor));
        C3Up_Btn->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_43->addWidget(C3Up_Btn);

        horizontalLayout_43->setStretch(0, 2);
        horizontalLayout_43->setStretch(1, 1);
        horizontalLayout_43->setStretch(2, 2);

        verticalLayout_23->addLayout(horizontalLayout_43);

        horizontalLayout_53 = new QHBoxLayout();
        horizontalLayout_53->setSpacing(0);
        horizontalLayout_53->setObjectName("horizontalLayout_53");
        horizontalLayout_53->setContentsMargins(0, -1, 0, -1);
        C3Down_Btn_2 = new QPushButton(ClampWidget);
        C3Down_Btn_2->setObjectName("C3Down_Btn_2");
        sizePolicy.setHeightForWidth(C3Down_Btn_2->sizePolicy().hasHeightForWidth());
        C3Down_Btn_2->setSizePolicy(sizePolicy);
        C3Down_Btn_2->setFont(font1);
        C3Down_Btn_2->setCursor(QCursor(Qt::PointingHandCursor));
        C3Down_Btn_2->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_53->addWidget(C3Down_Btn_2);

        label_57 = new QLabel(ClampWidget);
        label_57->setObjectName("label_57");
        label_57->setFont(font2);
        label_57->setAlignment(Qt::AlignCenter);

        horizontalLayout_53->addWidget(label_57);

        C3Up_Btn_2 = new QPushButton(ClampWidget);
        C3Up_Btn_2->setObjectName("C3Up_Btn_2");
        sizePolicy.setHeightForWidth(C3Up_Btn_2->sizePolicy().hasHeightForWidth());
        C3Up_Btn_2->setSizePolicy(sizePolicy);
        C3Up_Btn_2->setFont(font1);
        C3Up_Btn_2->setCursor(QCursor(Qt::PointingHandCursor));
        C3Up_Btn_2->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_53->addWidget(C3Up_Btn_2);

        horizontalLayout_53->setStretch(0, 2);
        horizontalLayout_53->setStretch(1, 1);
        horizontalLayout_53->setStretch(2, 2);

        verticalLayout_23->addLayout(horizontalLayout_53);

        verticalLayout_23->setStretch(0, 1);
        verticalLayout_23->setStretch(1, 1);

        verticalLayout_5->addLayout(verticalLayout_23);


        verticalLayout_6->addLayout(verticalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(-1, 0, -1, -1);
        horizontalSlider = new QSlider(ClampWidget);
        horizontalSlider->setObjectName("horizontalSlider");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(horizontalSlider->sizePolicy().hasHeightForWidth());
        horizontalSlider->setSizePolicy(sizePolicy1);
        horizontalSlider->setStyleSheet(QString::fromUtf8("QSlider::handle:horizontal {\n"
"    width: 35px;\n"
"    height: 35px;\n"
"    margin-top: -5px; /* \346\240\271\346\215\256\346\273\221\346\247\275\351\253\230\345\272\246\350\260\203\346\225\264\350\277\231\344\270\252\345\200\274 */\n"
"    margin-left: 0px;\n"
"    margin-bottom: -5px; /* \346\240\271\346\215\256\346\273\221\346\247\275\351\253\230\345\272\246\350\260\203\346\225\264\350\277\231\344\270\252\345\200\274 */\n"
"    margin-right: 0px;\n"
"    background: white; /* \347\231\275\350\211\262\346\273\221\345\235\227 */\n"
"    border: 2px solid lightgray; /* \350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    border-radius: 17px; /* \350\256\276\347\275\256\345\234\206\345\275\242 */\n"
"}\n"
"\n"
"QSlider::groove:horizontal {\n"
"    height: 30px;\n"
"    left: 0px;\n"
"    right: 0px;\n"
"    border: 0px;\n"
"    border-radius: 10px;\n"
"    background: rgba(0, 0, 0, 50); /* \346\273\221\346\247\275\350\203\214\346\231\257 */\n"
"}\n"
"QSlider::sub-page:horizontal {\n"
"    border-radi"
                        "us: 10px; /* \347\241\256\344\277\235\344\270\216 groove \344\277\235\346\214\201\344\270\200\350\207\264 */\n"
"     /* background: rgba(240, 240, 240, 1); /* \345\267\262\347\273\217\350\277\207\347\232\204\346\273\221\346\247\275\351\203\250\345\210\206\351\242\234\350\211\262 */\n"
"	background: rgb(64, 191, 191);\n"
"}\n"
"\n"
"QSlider::add-page:horizontal {\n"
"    border-radius: 10px; /* \344\271\237\345\257\271\346\234\252\347\273\217\350\277\207\347\232\204\351\203\250\345\210\206\350\256\276\347\275\256\345\234\206\350\247\222 */\n"
"    background: transparent; /* \350\256\276\347\275\256\344\270\272\351\200\217\346\230\216\346\210\226\345\205\266\344\273\226\351\242\234\350\211\262 */\n"
"}"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(horizontalSlider);

        lineEdit = new QLineEdit(ClampWidget);
        lineEdit->setObjectName("lineEdit");
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(lineEdit);

        pushButton_speed = new QPushButton(ClampWidget);
        pushButton_speed->setObjectName("pushButton_speed");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_speed->sizePolicy().hasHeightForWidth());
        pushButton_speed->setSizePolicy(sizePolicy2);
        QFont font3;
        font3.setPointSize(16);
        font3.setBold(true);
        pushButton_speed->setFont(font3);

        horizontalLayout_4->addWidget(pushButton_speed);

        horizontalLayout_4->setStretch(0, 4);
        horizontalLayout_4->setStretch(1, 1);
        horizontalLayout_4->setStretch(2, 1);

        verticalLayout_6->addLayout(horizontalLayout_4);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        C1C2grip_Btn = new QPushButton(ClampWidget);
        C1C2grip_Btn->setObjectName("C1C2grip_Btn");
        sizePolicy2.setHeightForWidth(C1C2grip_Btn->sizePolicy().hasHeightForWidth());
        C1C2grip_Btn->setSizePolicy(sizePolicy2);
        C1C2grip_Btn->setMinimumSize(QSize(100, 0));
        QFont font4;
        font4.setPointSize(26);
        font4.setBold(true);
        font4.setItalic(false);
        C1C2grip_Btn->setFont(font4);
        C1C2grip_Btn->setCursor(QCursor(Qt::PointingHandCursor));
        C1C2grip_Btn->setStyleSheet(QString::fromUtf8("QPushButton:pressed\n"
"{\n"
"	background-color: rgb(160, 160, 160);\n"
"}\n"
"\n"
"QPushButton:released\n"
"{\n"
"	background-color: rgb(255, 255, 255);\n"
"}"));

        horizontalLayout_2->addWidget(C1C2grip_Btn);

        label_pz = new QLabel(ClampWidget);
        label_pz->setObjectName("label_pz");
        label_pz->setMinimumSize(QSize(100, 0));
        label_pz->setFont(font3);
        label_pz->setCursor(QCursor(Qt::ArrowCursor));
        label_pz->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_pz);

        C1C2release_Btn = new QPushButton(ClampWidget);
        C1C2release_Btn->setObjectName("C1C2release_Btn");
        sizePolicy2.setHeightForWidth(C1C2release_Btn->sizePolicy().hasHeightForWidth());
        C1C2release_Btn->setSizePolicy(sizePolicy2);
        C1C2release_Btn->setMinimumSize(QSize(100, 0));
        C1C2release_Btn->setFont(font4);
        C1C2release_Btn->setCursor(QCursor(Qt::PointingHandCursor));
        C1C2release_Btn->setStyleSheet(QString::fromUtf8("QPushButton:pressed\n"
"{\n"
"	background-color: rgb(160, 160, 160);\n"
"}\n"
"\n"
"QPushButton:released\n"
"{\n"
"	background-color: rgb(255, 255, 255);\n"
"}"));

        horizontalLayout_2->addWidget(C1C2release_Btn);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_44 = new QHBoxLayout();
        horizontalLayout_44->setSpacing(4);
        horizontalLayout_44->setObjectName("horizontalLayout_44");
        C3grip_Btn = new QPushButton(ClampWidget);
        C3grip_Btn->setObjectName("C3grip_Btn");
        sizePolicy2.setHeightForWidth(C3grip_Btn->sizePolicy().hasHeightForWidth());
        C3grip_Btn->setSizePolicy(sizePolicy2);
        C3grip_Btn->setMinimumSize(QSize(100, 0));
        C3grip_Btn->setFont(font4);
        C3grip_Btn->setCursor(QCursor(Qt::PointingHandCursor));
        C3grip_Btn->setStyleSheet(QString::fromUtf8("QPushButton:pressed\n"
"{\n"
"	background-color: rgb(160, 160, 160);\n"
"}\n"
"\n"
"QPushButton:released\n"
"{\n"
"	background-color: rgb(255, 255, 255);\n"
"}"));

        horizontalLayout_44->addWidget(C3grip_Btn);

        label_bz = new QLabel(ClampWidget);
        label_bz->setObjectName("label_bz");
        label_bz->setMinimumSize(QSize(100, 0));
        label_bz->setFont(font3);
        label_bz->setCursor(QCursor(Qt::ArrowCursor));
        label_bz->setAlignment(Qt::AlignCenter);

        horizontalLayout_44->addWidget(label_bz);

        C3release_Btn = new QPushButton(ClampWidget);
        C3release_Btn->setObjectName("C3release_Btn");
        sizePolicy2.setHeightForWidth(C3release_Btn->sizePolicy().hasHeightForWidth());
        C3release_Btn->setSizePolicy(sizePolicy2);
        C3release_Btn->setMinimumSize(QSize(100, 0));
        C3release_Btn->setFont(font4);
        C3release_Btn->setCursor(QCursor(Qt::PointingHandCursor));
        C3release_Btn->setStyleSheet(QString::fromUtf8("QPushButton:pressed\n"
"{\n"
"	background-color: rgb(160, 160, 160);\n"
"}\n"
"\n"
"QPushButton:released\n"
"{\n"
"	background-color: rgb(255, 255, 255);\n"
"}"));

        horizontalLayout_44->addWidget(C3release_Btn);


        verticalLayout_2->addLayout(horizontalLayout_44);


        verticalLayout_6->addLayout(verticalLayout_2);

        verticalLayout_6->setStretch(0, 4);
        verticalLayout_6->setStretch(1, 1);
        verticalLayout_6->setStretch(2, 4);

        horizontalLayout_5->addLayout(verticalLayout_6);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label = new QLabel(ClampWidget);
        label->setObjectName("label");
        label->setFont(font);

        verticalLayout_3->addWidget(label);

        verticalLayout_3->setStretch(0, 1);

        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_50 = new QHBoxLayout();
        horizontalLayout_50->setSpacing(0);
        horizontalLayout_50->setObjectName("horizontalLayout_50");
        horizontalLayout_50->setContentsMargins(10, -1, 10, -1);
        Clamp_z_Down_Btn = new QPushButton(ClampWidget);
        Clamp_z_Down_Btn->setObjectName("Clamp_z_Down_Btn");
        sizePolicy.setHeightForWidth(Clamp_z_Down_Btn->sizePolicy().hasHeightForWidth());
        Clamp_z_Down_Btn->setSizePolicy(sizePolicy);
        Clamp_z_Down_Btn->setFont(font1);
        Clamp_z_Down_Btn->setCursor(QCursor(Qt::PointingHandCursor));
        Clamp_z_Down_Btn->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_50->addWidget(Clamp_z_Down_Btn);

        label_54 = new QLabel(ClampWidget);
        label_54->setObjectName("label_54");
        QFont font5;
        font5.setBold(true);
        label_54->setFont(font5);
        label_54->setAlignment(Qt::AlignCenter);

        horizontalLayout_50->addWidget(label_54);

        Clamp_z_Up_Btn = new QPushButton(ClampWidget);
        Clamp_z_Up_Btn->setObjectName("Clamp_z_Up_Btn");
        sizePolicy.setHeightForWidth(Clamp_z_Up_Btn->sizePolicy().hasHeightForWidth());
        Clamp_z_Up_Btn->setSizePolicy(sizePolicy);
        Clamp_z_Up_Btn->setFont(font1);
        Clamp_z_Up_Btn->setCursor(QCursor(Qt::PointingHandCursor));
        Clamp_z_Up_Btn->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_50->addWidget(Clamp_z_Up_Btn);

        horizontalLayout_50->setStretch(0, 2);
        horizontalLayout_50->setStretch(1, 1);
        horizontalLayout_50->setStretch(2, 2);

        verticalLayout->addLayout(horizontalLayout_50);

        horizontalLayout_48 = new QHBoxLayout();
        horizontalLayout_48->setSpacing(0);
        horizontalLayout_48->setObjectName("horizontalLayout_48");
        horizontalLayout_48->setContentsMargins(10, -1, 10, -1);
        Clamp_x_Down_Btn = new QPushButton(ClampWidget);
        Clamp_x_Down_Btn->setObjectName("Clamp_x_Down_Btn");
        sizePolicy.setHeightForWidth(Clamp_x_Down_Btn->sizePolicy().hasHeightForWidth());
        Clamp_x_Down_Btn->setSizePolicy(sizePolicy);
        Clamp_x_Down_Btn->setFont(font1);
        Clamp_x_Down_Btn->setCursor(QCursor(Qt::PointingHandCursor));
        Clamp_x_Down_Btn->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_48->addWidget(Clamp_x_Down_Btn);

        label_52 = new QLabel(ClampWidget);
        label_52->setObjectName("label_52");
        label_52->setFont(font5);
        label_52->setAlignment(Qt::AlignCenter);

        horizontalLayout_48->addWidget(label_52);

        Clamp_x_Up_Btn = new QPushButton(ClampWidget);
        Clamp_x_Up_Btn->setObjectName("Clamp_x_Up_Btn");
        sizePolicy.setHeightForWidth(Clamp_x_Up_Btn->sizePolicy().hasHeightForWidth());
        Clamp_x_Up_Btn->setSizePolicy(sizePolicy);
        Clamp_x_Up_Btn->setFont(font1);
        Clamp_x_Up_Btn->setCursor(QCursor(Qt::PointingHandCursor));
        Clamp_x_Up_Btn->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_48->addWidget(Clamp_x_Up_Btn);

        horizontalLayout_48->setStretch(0, 2);
        horizontalLayout_48->setStretch(1, 1);
        horizontalLayout_48->setStretch(2, 2);

        verticalLayout->addLayout(horizontalLayout_48);

        horizontalLayout_49 = new QHBoxLayout();
        horizontalLayout_49->setSpacing(0);
        horizontalLayout_49->setObjectName("horizontalLayout_49");
        horizontalLayout_49->setContentsMargins(10, -1, 10, -1);
        Clamp_y_Down_Btn = new QPushButton(ClampWidget);
        Clamp_y_Down_Btn->setObjectName("Clamp_y_Down_Btn");
        sizePolicy.setHeightForWidth(Clamp_y_Down_Btn->sizePolicy().hasHeightForWidth());
        Clamp_y_Down_Btn->setSizePolicy(sizePolicy);
        Clamp_y_Down_Btn->setFont(font1);
        Clamp_y_Down_Btn->setCursor(QCursor(Qt::PointingHandCursor));
        Clamp_y_Down_Btn->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_49->addWidget(Clamp_y_Down_Btn);

        label_53 = new QLabel(ClampWidget);
        label_53->setObjectName("label_53");
        label_53->setFont(font5);
        label_53->setAlignment(Qt::AlignCenter);

        horizontalLayout_49->addWidget(label_53);

        Clamp_y_Up_Btn = new QPushButton(ClampWidget);
        Clamp_y_Up_Btn->setObjectName("Clamp_y_Up_Btn");
        sizePolicy.setHeightForWidth(Clamp_y_Up_Btn->sizePolicy().hasHeightForWidth());
        Clamp_y_Up_Btn->setSizePolicy(sizePolicy);
        Clamp_y_Up_Btn->setFont(font1);
        Clamp_y_Up_Btn->setCursor(QCursor(Qt::PointingHandCursor));
        Clamp_y_Up_Btn->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_49->addWidget(Clamp_y_Up_Btn);

        horizontalLayout_49->setStretch(0, 2);
        horizontalLayout_49->setStretch(1, 1);
        horizontalLayout_49->setStretch(2, 2);

        verticalLayout->addLayout(horizontalLayout_49);


        verticalLayout_4->addLayout(verticalLayout);

        widget = new QWidget(ClampWidget);
        widget->setObjectName("widget");
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(-1, 20, -1, 20);
        pushButton_recov_2 = new QPushButton(widget);
        pushButton_recov_2->setObjectName("pushButton_recov_2");
        sizePolicy2.setHeightForWidth(pushButton_recov_2->sizePolicy().hasHeightForWidth());
        pushButton_recov_2->setSizePolicy(sizePolicy2);
        pushButton_recov_2->setFont(font3);

        horizontalLayout_3->addWidget(pushButton_recov_2);

        pushButton_recov = new QPushButton(widget);
        pushButton_recov->setObjectName("pushButton_recov");
        sizePolicy2.setHeightForWidth(pushButton_recov->sizePolicy().hasHeightForWidth());
        pushButton_recov->setSizePolicy(sizePolicy2);
        pushButton_recov->setFont(font3);

        horizontalLayout_3->addWidget(pushButton_recov);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 1);

        verticalLayout_4->addWidget(widget);

        verticalLayout_4->setStretch(1, 3);
        verticalLayout_4->setStretch(2, 1);

        horizontalLayout_5->addLayout(verticalLayout_4);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 1);

        retranslateUi(ClampWidget);

        QMetaObject::connectSlotsByName(ClampWidget);
    } // setupUi

    void retranslateUi(QWidget *ClampWidget)
    {
        ClampWidget->setWindowTitle(QCoreApplication::translate("ClampWidget", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("ClampWidget", "\346\226\234\350\205\225\350\207\202\345\244\271\347\210\252\344\275\215\347\275\256\350\260\203\350\212\202\357\274\232", nullptr));
        C3Down_Btn->setText(QCoreApplication::translate("ClampWidget", "-", nullptr));
        label_51->setText(QCoreApplication::translate("ClampWidget", "X\350\260\203\350\212\202", nullptr));
        C3Up_Btn->setText(QCoreApplication::translate("ClampWidget", "+", nullptr));
        C3Down_Btn_2->setText(QCoreApplication::translate("ClampWidget", "-", nullptr));
        label_57->setText(QCoreApplication::translate("ClampWidget", "Y\350\260\203\350\212\202", nullptr));
        C3Up_Btn_2->setText(QCoreApplication::translate("ClampWidget", "+", nullptr));
        pushButton_speed->setText(QCoreApplication::translate("ClampWidget", "\350\256\276\345\256\232\351\200\237\345\272\246", nullptr));
        C1C2grip_Btn->setText(QCoreApplication::translate("ClampWidget", "\345\244\271\347\264\247", nullptr));
        label_pz->setText(QCoreApplication::translate("ClampWidget", "\345\271\263\345\244\271", nullptr));
        C1C2release_Btn->setText(QCoreApplication::translate("ClampWidget", "\346\235\276\345\274\200", nullptr));
        C3grip_Btn->setText(QCoreApplication::translate("ClampWidget", "\345\244\271\347\264\247", nullptr));
        label_bz->setText(QCoreApplication::translate("ClampWidget", "\346\212\261\345\244\271", nullptr));
        C3release_Btn->setText(QCoreApplication::translate("ClampWidget", "\346\235\276\345\274\200", nullptr));
        label->setText(QCoreApplication::translate("ClampWidget", "\345\256\211\350\243\205\347\262\276\345\257\271\344\275\215\357\274\232", nullptr));
        Clamp_z_Down_Btn->setText(QCoreApplication::translate("ClampWidget", "-", nullptr));
        label_54->setText(QCoreApplication::translate("ClampWidget", "Z\347\262\276\350\260\203", nullptr));
        Clamp_z_Up_Btn->setText(QCoreApplication::translate("ClampWidget", "+", nullptr));
        Clamp_x_Down_Btn->setText(QCoreApplication::translate("ClampWidget", "-", nullptr));
        label_52->setText(QCoreApplication::translate("ClampWidget", "X\347\262\276\350\260\203", nullptr));
        Clamp_x_Up_Btn->setText(QCoreApplication::translate("ClampWidget", "+", nullptr));
        Clamp_y_Down_Btn->setText(QCoreApplication::translate("ClampWidget", "-", nullptr));
        label_53->setText(QCoreApplication::translate("ClampWidget", "Y\347\262\276\350\260\203", nullptr));
        Clamp_y_Up_Btn->setText(QCoreApplication::translate("ClampWidget", "+", nullptr));
        pushButton_recov_2->setText(QCoreApplication::translate("ClampWidget", "Z\347\262\276\350\260\203\351\231\220\344\275\215\345\217\226\346\266\210", nullptr));
        pushButton_recov->setText(QCoreApplication::translate("ClampWidget", "\347\262\276\350\260\203\345\244\215\344\275\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClampWidget: public Ui_ClampWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLAMPWIDGET_H
