/********************************************************************************
** Form generated from reading UI file 'downloadwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOADWIDGET_H
#define UI_DOWNLOADWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DownLoadWidget
{
public:
    QPushButton *CancelDownBtn;
    QPushButton *RequestDownBtn;
    QLabel *tiplabel;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLabel *label_4;

    void setupUi(QWidget *DownLoadWidget)
    {
        if (DownLoadWidget->objectName().isEmpty())
            DownLoadWidget->setObjectName("DownLoadWidget");
        DownLoadWidget->resize(460, 452);
        CancelDownBtn = new QPushButton(DownLoadWidget);
        CancelDownBtn->setObjectName("CancelDownBtn");
        CancelDownBtn->setGeometry(QRect(310, 380, 80, 21));
        RequestDownBtn = new QPushButton(DownLoadWidget);
        RequestDownBtn->setObjectName("RequestDownBtn");
        RequestDownBtn->setGeometry(QRect(60, 380, 80, 21));
        tiplabel = new QLabel(DownLoadWidget);
        tiplabel->setObjectName("tiplabel");
        tiplabel->setGeometry(QRect(80, 360, 271, 41));
        QFont font;
        font.setPointSize(12);
        tiplabel->setFont(font);
        widget = new QWidget(DownLoadWidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 40, 411, 251));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(widget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 0);"));

        verticalLayout->addWidget(label_3);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 5);

        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        label_4 = new QLabel(widget);
        label_4->setObjectName("label_4");
        label_4->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);"));

        verticalLayout_2->addWidget(label_4);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 5);

        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(DownLoadWidget);

        QMetaObject::connectSlotsByName(DownLoadWidget);
    } // setupUi

    void retranslateUi(QWidget *DownLoadWidget)
    {
        DownLoadWidget->setWindowTitle(QCoreApplication::translate("DownLoadWidget", "Form", nullptr));
        CancelDownBtn->setText(QCoreApplication::translate("DownLoadWidget", "\347\241\256\350\256\244\345\256\211\350\243\205\345\256\214\346\210\220", nullptr));
        RequestDownBtn->setText(QCoreApplication::translate("DownLoadWidget", "\350\257\267\346\261\202\345\256\211\350\243\205", nullptr));
        tiplabel->setText(QString());
        label->setText(QCoreApplication::translate("DownLoadWidget", "\350\205\225\350\207\202\345\256\211\350\243\205", nullptr));
        label_3->setText(QCoreApplication::translate("DownLoadWidget", "\345\233\276\347\211\2071", nullptr));
        label_2->setText(QCoreApplication::translate("DownLoadWidget", "\345\220\212\346\237\261\345\256\211\350\243\205", nullptr));
        label_4->setText(QCoreApplication::translate("DownLoadWidget", "\345\233\276\347\211\2072", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DownLoadWidget: public Ui_DownLoadWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADWIDGET_H
