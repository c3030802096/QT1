/********************************************************************************
** Form generated from reading UI file 'lockwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCKWIDGET_H
#define UI_LOCKWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LockWidget
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QSlider *slider;
    QLabel *label;

    void setupUi(QWidget *LockWidget)
    {
        if (LockWidget->objectName().isEmpty())
            LockWidget->setObjectName("LockWidget");
        LockWidget->resize(535, 314);
        LockWidget->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(LockWidget);
        gridLayout->setObjectName("gridLayout");
        widget = new QWidget(LockWidget);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8(""));
        slider = new QSlider(widget);
        slider->setObjectName("slider");
        slider->setGeometry(QRect(110, 110, 281, 61));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(slider->sizePolicy().hasHeightForWidth());
        slider->setSizePolicy(sizePolicy);
        slider->setCursor(QCursor(Qt::OpenHandCursor));
        slider->setStyleSheet(QString::fromUtf8("QSlider::handle:horizontal {\n"
"    width: 40px;\n"
"    height: 40px;\n"
"    margin-top: -5px; /* \346\240\271\346\215\256\346\273\221\346\247\275\351\253\230\345\272\246\350\260\203\346\225\264\350\277\231\344\270\252\345\200\274 */\n"
"    margin-left: -10px;\n"
"    margin-bottom: -5px; /* \346\240\271\346\215\256\346\273\221\346\247\275\351\253\230\345\272\246\350\260\203\346\225\264\350\277\231\344\270\252\345\200\274 */\n"
"    margin-right: 0px;\n"
"    background: white; /* \347\231\275\350\211\262\346\273\221\345\235\227 */\n"
"    border: 2px solid lightgray; /* \350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    border-radius: 20px; /* \350\256\276\347\275\256\345\234\206\345\275\242 */\n"
"}\n"
"\n"
"QSlider::groove:horizontal {\n"
"    height: 35px;\n"
"    left: 0px;\n"
"    right: 0px;\n"
"    border: 0px;\n"
"    border-radius: 17px; /* \347\241\256\344\277\235\345\234\206\350\247\222 */\n"
"    background: rgba(0, 0, 0, 50); /* \346\273\221\346\247\275\350\203\214\346\231\257 */\n"
""
                        "}\n"
"\n"
"QSlider::sub-page:horizontal {\n"
"    border-radius: 17px; /* \347\241\256\344\277\235\344\270\216 groove \344\277\235\346\214\201\344\270\200\350\207\264 */\n"
"    background: rgb(64, 191, 191); /* \345\267\262\347\273\217\350\277\207\347\232\204\351\203\250\345\210\206\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"QSlider::add-page:horizontal {\n"
"    border-radius: 17px; /* \344\271\237\345\257\271\346\234\252\347\273\217\350\277\207\347\232\204\351\203\250\345\210\206\350\256\276\347\275\256\345\234\206\350\247\222 */\n"
"    background: transparent; /* \350\256\276\347\275\256\344\270\272\351\200\217\346\230\216\346\210\226\345\205\266\344\273\226\351\242\234\350\211\262 */\n"
"}\n"
""));
        slider->setOrientation(Qt::Horizontal);
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 40, 351, 51));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(LockWidget);

        QMetaObject::connectSlotsByName(LockWidget);
    } // setupUi

    void retranslateUi(QWidget *LockWidget)
    {
        LockWidget->setWindowTitle(QCoreApplication::translate("LockWidget", "Form", nullptr));
        label->setText(QCoreApplication::translate("LockWidget", "\345\275\223\345\211\215\347\252\227\345\217\243\345\267\262\351\224\201\345\256\232\357\274\214\350\257\267\346\273\221\345\212\250\350\247\243\351\224\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LockWidget: public Ui_LockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCKWIDGET_H
