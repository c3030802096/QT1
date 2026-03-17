#include "DateBaseMgr.h"

DateBaseMgr::DateBaseMgr()
{
    db = QSqlDatabase::addDatabase("QMYSQL");

    // 读取配置文件
    QString configFilePath = QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings settings(configFilePath, QSettings::IniFormat);

    if (!QFile::exists(configFilePath)) {
        qDebug() << "Config file does not exist!";
        return;
    }

    // 获取 MySQL 配置信息
    QString dbName = settings.value("MYSQL/DatabaseName").toString();
    QString hostName = settings.value("MYSQL/HostName").toString();
    QString userName = settings.value("MYSQL/UserName").toString();
    QString password = settings.value("MYSQL/Password").toString();

    db.setDatabaseName(dbName);
    db.setHostName(hostName);
    db.setUserName(userName);
    db.setPassword(password);

    // db.setDatabaseName("Arm");
    // db.setHostName("localhost");
    // db.setUserName("root");
    // db.setPassword("123456");

    if(db.open())
    {
        qDebug()<<"successed";
    }else{
        qDebug()<<"failed";
    }
}
