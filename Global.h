#ifndef GLOBAL_H
#define GLOBAL_H
#include "qregularexpression.h"
#include <QString>
#include <QCoreApplication>
#include <QFile>
#include <QMessageBox>
#include <QSettings>
#include <memory>
#include <QDir>

namespace Globals {
extern bool clampisOK;
extern bool clamp_motionisok;
}


struct ServerInfo{
    // QString Host = "192.168.2.110";
    // QString Port = "15001";
    QString Host1 = "127.0.0.1";
    QString Host2 = "127.0.0.1";
    const int controlPort = 15000;
    const int statusPort = 15001;
    const int Port1 = 15002;

    QString zmqhost = "127.0.0.1";
    QString zmqport = "5555";
};


void GetServer(std::shared_ptr<ServerInfo> si ,QWidget* w);

void ADebug(QString str1, bool iswrite = false);


#endif // GLOBAL_H
