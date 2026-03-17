/********************************************************************************
** Form generated from reading UI file 'camwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMWIDGET_H
#define UI_CAMWIDGET_H

#include <QHCheckBox.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CamWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_img;
    QHBoxLayout *horizontalLayout_43;
    QPushButton *camera_2D_Btn;
    QPushButton *camera_3D_Btn;
    QHBoxLayout *horizontalLayout_26;
    QLabel *ModelLabel;
    QHBoxLayout *horizontalLayout_53;
    QLabel *label_57;
    QHCheckBox *ModelcheckBox_control;
    QLabel *label_60;

    void setupUi(QWidget *CamWidget)
    {
        if (CamWidget->objectName().isEmpty())
            CamWidget->setObjectName("CamWidget");
        CamWidget->resize(422, 441);
        verticalLayout = new QVBoxLayout(CamWidget);
        verticalLayout->setObjectName("verticalLayout");
        label_img = new QLabel(CamWidget);
        label_img->setObjectName("label_img");

        verticalLayout->addWidget(label_img);

        horizontalLayout_43 = new QHBoxLayout();
        horizontalLayout_43->setSpacing(80);
        horizontalLayout_43->setObjectName("horizontalLayout_43");
        horizontalLayout_43->setContentsMargins(-1, 20, -1, 20);
        camera_2D_Btn = new QPushButton(CamWidget);
        camera_2D_Btn->setObjectName("camera_2D_Btn");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(camera_2D_Btn->sizePolicy().hasHeightForWidth());
        camera_2D_Btn->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(9);
        font.setBold(true);
        camera_2D_Btn->setFont(font);
        camera_2D_Btn->setCursor(QCursor(Qt::PointingHandCursor));
        camera_2D_Btn->setStyleSheet(QString::fromUtf8("QPushButton  {\n"
"	border: 1px solid;\n"
"	border-color: rgb(0, 200, 200);\n"
"	border-radius:5px;\n"
"}\n"
"\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(0, 255, 255); \n"
"\n"
"}"));

        horizontalLayout_43->addWidget(camera_2D_Btn);

        camera_3D_Btn = new QPushButton(CamWidget);
        camera_3D_Btn->setObjectName("camera_3D_Btn");
        sizePolicy.setHeightForWidth(camera_3D_Btn->sizePolicy().hasHeightForWidth());
        camera_3D_Btn->setSizePolicy(sizePolicy);
        camera_3D_Btn->setFont(font);
        camera_3D_Btn->setCursor(QCursor(Qt::PointingHandCursor));
        camera_3D_Btn->setStyleSheet(QString::fromUtf8("QPushButton  {\n"
"	border: 1px solid;\n"
"	border-color: rgb(0, 200, 200);\n"
"	border-radius:5px;\n"
"}\n"
"\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(0, 255, 255); \n"
"\n"
"}"));

        horizontalLayout_43->addWidget(camera_3D_Btn);


        verticalLayout->addLayout(horizontalLayout_43);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setObjectName("horizontalLayout_26");
        ModelLabel = new QLabel(CamWidget);
        ModelLabel->setObjectName("ModelLabel");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ModelLabel->sizePolicy().hasHeightForWidth());
        ModelLabel->setSizePolicy(sizePolicy1);
        ModelLabel->setFont(font);

        horizontalLayout_26->addWidget(ModelLabel);

        horizontalLayout_53 = new QHBoxLayout();
        horizontalLayout_53->setObjectName("horizontalLayout_53");
        label_57 = new QLabel(CamWidget);
        label_57->setObjectName("label_57");
        sizePolicy1.setHeightForWidth(label_57->sizePolicy().hasHeightForWidth());
        label_57->setSizePolicy(sizePolicy1);
        label_57->setFont(font);
        label_57->setAlignment(Qt::AlignCenter);

        horizontalLayout_53->addWidget(label_57);

        ModelcheckBox_control = new QHCheckBox(CamWidget);
        ModelcheckBox_control->setObjectName("ModelcheckBox_control");
        sizePolicy1.setHeightForWidth(ModelcheckBox_control->sizePolicy().hasHeightForWidth());
        ModelcheckBox_control->setSizePolicy(sizePolicy1);

        horizontalLayout_53->addWidget(ModelcheckBox_control);

        label_60 = new QLabel(CamWidget);
        label_60->setObjectName("label_60");
        sizePolicy1.setHeightForWidth(label_60->sizePolicy().hasHeightForWidth());
        label_60->setSizePolicy(sizePolicy1);
        label_60->setFont(font);
        label_60->setAlignment(Qt::AlignCenter);

        horizontalLayout_53->addWidget(label_60);

        horizontalLayout_53->setStretch(0, 2);
        horizontalLayout_53->setStretch(1, 1);
        horizontalLayout_53->setStretch(2, 2);

        horizontalLayout_26->addLayout(horizontalLayout_53);


        verticalLayout->addLayout(horizontalLayout_26);

        verticalLayout->setStretch(0, 4);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);

        retranslateUi(CamWidget);

        QMetaObject::connectSlotsByName(CamWidget);
    } // setupUi

    void retranslateUi(QWidget *CamWidget)
    {
        CamWidget->setWindowTitle(QCoreApplication::translate("CamWidget", "Form", nullptr));
        label_img->setText(QCoreApplication::translate("CamWidget", "TextLabel", nullptr));
        camera_2D_Btn->setText(QCoreApplication::translate("CamWidget", "2D\347\233\270\346\234\272", nullptr));
        camera_3D_Btn->setText(QCoreApplication::translate("CamWidget", "3D\347\233\270\346\234\272", nullptr));
        ModelLabel->setText(QCoreApplication::translate("CamWidget", "<html><head/><body><p><span style=\" font-size:10pt;\">\345\267\245\344\275\234\346\250\241\345\274\217\357\274\232</span></p></body></html>", nullptr));
        label_57->setText(QCoreApplication::translate("CamWidget", "\346\211\213\345\212\250\346\223\215\346\216\247", nullptr));
        ModelcheckBox_control->setText(QCoreApplication::translate("CamWidget", "CheckBox", nullptr));
        label_60->setText(QCoreApplication::translate("CamWidget", "\350\247\206\350\247\211\345\274\225\345\257\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CamWidget: public Ui_CamWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMWIDGET_H
