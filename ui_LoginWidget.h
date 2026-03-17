/********************************************************************************
** Form generated from reading UI file 'LoginWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIDGET_H
#define UI_LOGINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWidget
{
public:
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *LoginIdlineEdit;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *LoginPwdlineEdit;
    QPushButton *pwdcheckable_btn;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *LoginBtn;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *RegisterBtn;
    QLabel *label_6;
    QWidget *page_2;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *IdlineEdit;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *PwdlineEdit;
    QPushButton *pwdcheckable_btn_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLineEdit *SurePwdlineEdit;
    QPushButton *pwdcheckable_btn_3;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *checkBox_user;
    QCheckBox *checkBox_admin;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *RegisterOKBtn;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *CancleRegisterBTn;
    QPushButton *UserRegisterBtn;
    QPushButton *AdminRegisterBtn;

    void setupUi(QWidget *LoginWidget)
    {
        if (LoginWidget->objectName().isEmpty())
            LoginWidget->setObjectName("LoginWidget");
        LoginWidget->resize(600, 400);
        gridLayout = new QGridLayout(LoginWidget);
        gridLayout->setObjectName("gridLayout");
        stackedWidget = new QStackedWidget(LoginWidget);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        layoutWidget = new QWidget(page);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(160, 100, 271, 101));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        LoginIdlineEdit = new QLineEdit(layoutWidget);
        LoginIdlineEdit->setObjectName("LoginIdlineEdit");
        LoginIdlineEdit->setEchoMode(QLineEdit::Normal);

        horizontalLayout_2->addWidget(LoginIdlineEdit);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(1, 7);
        horizontalLayout_2->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        horizontalLayout->addWidget(label_2);

        LoginPwdlineEdit = new QLineEdit(layoutWidget);
        LoginPwdlineEdit->setObjectName("LoginPwdlineEdit");
        LoginPwdlineEdit->setEchoMode(QLineEdit::Password);

        horizontalLayout->addWidget(LoginPwdlineEdit);

        pwdcheckable_btn = new QPushButton(layoutWidget);
        pwdcheckable_btn->setObjectName("pwdcheckable_btn");
        pwdcheckable_btn->setMinimumSize(QSize(0, 23));
        pwdcheckable_btn->setStyleSheet(QString::fromUtf8("border-image: url(:/image/eyes_enable.png);"));

        horizontalLayout->addWidget(pwdcheckable_btn);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 7);
        horizontalLayout->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout);

        layoutWidget1 = new QWidget(page);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(170, 260, 261, 41));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        LoginBtn = new QPushButton(layoutWidget1);
        LoginBtn->setObjectName("LoginBtn");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoginBtn->sizePolicy().hasHeightForWidth());
        LoginBtn->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(20);
        font1.setBold(true);
        LoginBtn->setFont(font1);
        LoginBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	border-radius:19px;\n"
"	background-color: rgb(0, 170, 255);\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: rgb(0, 97, 145);\n"
"}"));

        horizontalLayout_8->addWidget(LoginBtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);

        RegisterBtn = new QPushButton(layoutWidget1);
        RegisterBtn->setObjectName("RegisterBtn");
        sizePolicy.setHeightForWidth(RegisterBtn->sizePolicy().hasHeightForWidth());
        RegisterBtn->setSizePolicy(sizePolicy);
        RegisterBtn->setFont(font1);
        RegisterBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"border-radius:19px;\n"
"background-color: rgb(170, 255, 255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color: rgb(63, 95, 95);\n"
"}"));

        horizontalLayout_8->addWidget(RegisterBtn);

        horizontalLayout_8->setStretch(0, 2);
        horizontalLayout_8->setStretch(2, 2);
        label_6 = new QLabel(page);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(240, 10, 121, 61));
        label_6->setFont(font1);
        label_6->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        layoutWidget2 = new QWidget(page_2);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(170, 30, 251, 181));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName("label_3");
        QFont font2;
        font2.setPointSize(9);
        font2.setBold(true);
        label_3->setFont(font2);

        horizontalLayout_3->addWidget(label_3);

        IdlineEdit = new QLineEdit(layoutWidget2);
        IdlineEdit->setObjectName("IdlineEdit");

        horizontalLayout_3->addWidget(IdlineEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        horizontalLayout_3->setStretch(0, 2);
        horizontalLayout_3->setStretch(1, 7);
        horizontalLayout_3->setStretch(2, 1);

        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_4 = new QLabel(layoutWidget2);
        label_4->setObjectName("label_4");
        label_4->setFont(font2);

        horizontalLayout_4->addWidget(label_4);

        PwdlineEdit = new QLineEdit(layoutWidget2);
        PwdlineEdit->setObjectName("PwdlineEdit");
        PwdlineEdit->setEchoMode(QLineEdit::Password);

        horizontalLayout_4->addWidget(PwdlineEdit);

        pwdcheckable_btn_2 = new QPushButton(layoutWidget2);
        pwdcheckable_btn_2->setObjectName("pwdcheckable_btn_2");
        pwdcheckable_btn_2->setMinimumSize(QSize(0, 22));
        pwdcheckable_btn_2->setStyleSheet(QString::fromUtf8("border-image: url(:/image/eyes_enable.png);"));

        horizontalLayout_4->addWidget(pwdcheckable_btn_2);

        horizontalLayout_4->setStretch(0, 2);
        horizontalLayout_4->setStretch(1, 7);
        horizontalLayout_4->setStretch(2, 1);

        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_5 = new QLabel(layoutWidget2);
        label_5->setObjectName("label_5");
        label_5->setFont(font2);

        horizontalLayout_5->addWidget(label_5);

        SurePwdlineEdit = new QLineEdit(layoutWidget2);
        SurePwdlineEdit->setObjectName("SurePwdlineEdit");
        SurePwdlineEdit->setEchoMode(QLineEdit::Password);

        horizontalLayout_5->addWidget(SurePwdlineEdit);

        pwdcheckable_btn_3 = new QPushButton(layoutWidget2);
        pwdcheckable_btn_3->setObjectName("pwdcheckable_btn_3");
        pwdcheckable_btn_3->setMinimumSize(QSize(0, 22));
        pwdcheckable_btn_3->setStyleSheet(QString::fromUtf8("border-image: url(:/image/eyes_enable.png);"));

        horizontalLayout_5->addWidget(pwdcheckable_btn_3);

        horizontalLayout_5->setStretch(0, 2);
        horizontalLayout_5->setStretch(1, 7);
        horizontalLayout_5->setStretch(2, 1);

        verticalLayout_2->addLayout(horizontalLayout_5);

        layoutWidget3 = new QWidget(page_2);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(170, 230, 252, 91));
        verticalLayout_3 = new QVBoxLayout(layoutWidget3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        checkBox_user = new QCheckBox(layoutWidget3);
        checkBox_user->setObjectName("checkBox_user");
        sizePolicy.setHeightForWidth(checkBox_user->sizePolicy().hasHeightForWidth());
        checkBox_user->setSizePolicy(sizePolicy);
        QFont font3;
        font3.setPointSize(13);
        font3.setBold(true);
        checkBox_user->setFont(font3);

        horizontalLayout_7->addWidget(checkBox_user);

        checkBox_admin = new QCheckBox(layoutWidget3);
        checkBox_admin->setObjectName("checkBox_admin");
        sizePolicy.setHeightForWidth(checkBox_admin->sizePolicy().hasHeightForWidth());
        checkBox_admin->setSizePolicy(sizePolicy);
        checkBox_admin->setFont(font3);

        horizontalLayout_7->addWidget(checkBox_admin);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        RegisterOKBtn = new QPushButton(layoutWidget3);
        RegisterOKBtn->setObjectName("RegisterOKBtn");
        sizePolicy.setHeightForWidth(RegisterOKBtn->sizePolicy().hasHeightForWidth());
        RegisterOKBtn->setSizePolicy(sizePolicy);
        QFont font4;
        font4.setPointSize(17);
        font4.setBold(true);
        RegisterOKBtn->setFont(font4);
        RegisterOKBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"border-radius:19px;\n"
"background-color: rgb(201, 201, 201);\n"
"}\n"
"QPushButton:pressed{\n"
"	background-color: rgb(108, 108, 108);\n"
"}"));

        horizontalLayout_6->addWidget(RegisterOKBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);

        CancleRegisterBTn = new QPushButton(layoutWidget3);
        CancleRegisterBTn->setObjectName("CancleRegisterBTn");
        sizePolicy.setHeightForWidth(CancleRegisterBTn->sizePolicy().hasHeightForWidth());
        CancleRegisterBTn->setSizePolicy(sizePolicy);
        CancleRegisterBTn->setFont(font4);
        CancleRegisterBTn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"border-radius:19px;\n"
"background-color: rgb(201, 201, 201);\n"
"}\n"
"QPushButton:pressed{\n"
"	background-color: rgb(108, 108, 108);\n"
"}"));

        horizontalLayout_6->addWidget(CancleRegisterBTn);

        horizontalLayout_6->setStretch(0, 2);
        horizontalLayout_6->setStretch(2, 2);

        verticalLayout_3->addLayout(horizontalLayout_6);

        UserRegisterBtn = new QPushButton(page_2);
        UserRegisterBtn->setObjectName("UserRegisterBtn");
        UserRegisterBtn->setGeometry(QRect(460, 70, 80, 18));
        UserRegisterBtn->setFlat(true);
        AdminRegisterBtn = new QPushButton(page_2);
        AdminRegisterBtn->setObjectName("AdminRegisterBtn");
        AdminRegisterBtn->setGeometry(QRect(461, 110, 81, 20));
        AdminRegisterBtn->setFlat(true);
        stackedWidget->addWidget(page_2);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);


        retranslateUi(LoginWidget);

        stackedWidget->setCurrentIndex(0);
        UserRegisterBtn->setDefault(false);


        QMetaObject::connectSlotsByName(LoginWidget);
    } // setupUi

    void retranslateUi(QWidget *LoginWidget)
    {
        LoginWidget->setWindowTitle(QCoreApplication::translate("LoginWidget", "Form", nullptr));
        label->setText(QCoreApplication::translate("LoginWidget", "\350\264\246\345\217\267\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("LoginWidget", "\345\257\206\347\240\201\357\274\232", nullptr));
        pwdcheckable_btn->setText(QString());
        LoginBtn->setText(QCoreApplication::translate("LoginWidget", "\347\231\273\345\275\225", nullptr));
        RegisterBtn->setText(QCoreApplication::translate("LoginWidget", "\346\263\250\345\206\214", nullptr));
        label_6->setText(QString());
        label_3->setText(QCoreApplication::translate("LoginWidget", "\350\264\246\345\217\267     \357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("LoginWidget", "\345\257\206\347\240\201     \357\274\232", nullptr));
        pwdcheckable_btn_2->setText(QString());
        label_5->setText(QCoreApplication::translate("LoginWidget", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", nullptr));
        pwdcheckable_btn_3->setText(QString());
        checkBox_user->setText(QCoreApplication::translate("LoginWidget", "\346\231\256\351\200\232\347\224\250\346\210\267", nullptr));
        checkBox_admin->setText(QCoreApplication::translate("LoginWidget", "\347\256\241\347\220\206\345\221\230", nullptr));
        RegisterOKBtn->setText(QCoreApplication::translate("LoginWidget", "\345\256\214\346\210\220", nullptr));
        CancleRegisterBTn->setText(QCoreApplication::translate("LoginWidget", "\345\217\226\346\266\210", nullptr));
        UserRegisterBtn->setText(QString());
        AdminRegisterBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginWidget: public Ui_LoginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIDGET_H
