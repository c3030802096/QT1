#include "OperaterWidget.h"
#include <QOpenGLContext>
#include <QApplication>
#include "LoginWidget.h"
#include <memory>
#include <QSqlDatabase>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include "clampwidget.h"
#include <Global.h>
// 自定义消息处理函数
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QFile logFile("debug_log.txt");
    if (!logFile.isOpen()) {
        logFile.open(QIODevice::WriteOnly | QIODevice::Append);
    }

    QTextStream out(&logFile);
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");

    switch (type) {
    case QtDebugMsg:
        out << "Debug: " << msg << "\n";
        break;
    case QtInfoMsg:
        out << "Info: " << msg << "\n";
        break;
    case QtWarningMsg:
        out << "Warning: " << msg << "\n";
        break;
    case QtCriticalMsg:
        out << "Critical: " << msg << "\n";
        break;
    case QtFatalMsg:
        out << "Fatal: " << msg << "\n";
        break;
    }

    out.flush();
}


const int loginstate = 1;
int main(int argc, char *argv[])
{
    // qInstallMessageHandler(messageHandler);
    QApplication a(argc, argv);
    if(loginstate == 0){
        Widget *w = new Widget();
        w->show();
    } else if(loginstate == 1){
        LoginWidget* w = new LoginWidget();
        w->show();
    }else{
        ClampWidget* w = new ClampWidget();
        w->show();
    }

    return a.exec();
}
