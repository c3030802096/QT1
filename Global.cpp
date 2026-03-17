#include "Global.h"

namespace Globals {
bool clampisOK = true;
bool clamp_motionisok = true;
}

void GetServer(std::shared_ptr<ServerInfo> si, QWidget *w){
    // QString ipAddress;
    // QString configFilePath = QCoreApplication::applicationDirPath() + "/config.ini";
    // QFile cfg_file(configFilePath);

    QString iniFilePath = QCoreApplication::applicationDirPath() + "/config.ini";
    // 创建 QSettings 对象
    QSettings settings(iniFilePath, QSettings::IniFormat);
    // 检查 QSettings 的状态
    if (settings.status() != QSettings::NoError) {
        QMessageBox::critical(w, "错误", "无法打开配置文件！");
    }

    settings.beginGroup("tcp");  // 进入 [exe] 部分
    si->Host1 = settings.value("ip1").toString();
    si->Host2 = settings.value("ip2").toString();
    si->zmqhost = settings.value("zmqhost").toString();
    si->zmqport = settings.value("zmqport").toString();
    settings.endGroup();  // 进入 [exe] 部分

    // qDebug()<<"1:"<<si.Host1<<"2:"<<si.Host2;
    // bool readingTcpSection = false;

    // if (cfg_file.open(QIODevice::ReadOnly)) {
    //     QTextStream in(&cfg_file);
    //     QString line;
    //     while (in.readLineInto(&line)) {
    //         line = line.trimmed();
    //         if (line == "[tcp]") {
    //             readingTcpSection = true;
    //             continue;
    //         }
    //         if (readingTcpSection) {
    //             if (line.startsWith("ip1 =")) {
    //                 // 解析 IP 地址
    //                 QRegularExpression regex(R"(ip\s*=\s*(\S+))");
    //                 QRegularExpressionMatch match = regex.match(line);
    //                 if (match.hasMatch()) {
    //                     ipAddress = match.captured(1); // 获取 IP 地址
    //                     qDebug() << "Read IP address: " << ipAddress; // 输出调试信息
    //                     si.Host1 = ipAddress;
    //                 }
    //                 break;
    //             }
    //         }
    //     }
    //     cfg_file.close();
    // } else {

    // }
}

void ADebug(QString str1, bool iswrite)
{
    qDebug()<<"ADebug:"+str1;
    if(iswrite){
        // 获取exe所在目录
        QString exeDir = QCoreApplication::applicationDirPath();

        // 构造文件路径
        QString filePath = QDir(exeDir).filePath("ADebug.txt");

        // 获取当前时间并格式化为"年月日"
        QTime time = QTime::currentTime();
        QDate date = QDate::currentDate();
        auto currentTime = date.toString("yyyy-MM-dd") + " " + time.toString("hh:mm:ss");

        // 创建并写入文件
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << currentTime + "\n" + str1 << "\n";  // 添加换行
            file.close();
        } else {
            qWarning() << "无法创建或写入文件:" << filePath;
        }
    }
}
