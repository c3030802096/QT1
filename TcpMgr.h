#ifndef TCPMGR_H
#define TCPMGR_H
#include <QTcpSocket>
#include "singleton.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <Global.h>
class TcpMgr:public QObject, public Singleton<TcpMgr>,
               public std::enable_shared_from_this<TcpMgr>
{
    Q_OBJECT
public:
    TcpMgr();
    QMap<QString, std::function<void(QString, int, QByteArray)>> _handlers;
    QMap<QString, std::function<void(QString, int, QByteArray)>> _handlers2;
    void Disconnect();
    bool IsConnected();
    bool _IsConnected = false;
    void RECOVR();
private:
    int connectedCount = 0; // 连接计数
    std::mutex mtx;  // 互斥锁
    void addconnectedCount();
    void subconnectedCount();

    QTcpSocket _socket;
    QTcpSocket controlSocket;
    QTcpSocket statusSocket;
    QTcpSocket Socket0;
    QTcpSocket Socket1;
    QString _host;
    uint16_t _port;
    uint16_t c_port;
    uint16_t s_port;
    uint16_t port0;
    uint16_t port1;
    QByteArray _buffer;
    QByteArray _buffer2;
    bool _b_recv_pending;
    bool _b_recv_pending2;
    quint32 _message_id;
    quint32 _message_len;
    void initHandlers();
    void initHandlers2();
    int clampstop_index = 0;


public slots:
    void slot_send_data(QString reqId, QByteArray dataBytes);
    void slot_tcp_connect(std::shared_ptr<ServerInfo> si);
    void handleMsg(QString id, int len, QByteArray data);
    void handleMsg2(QString id, int len, QByteArray data);
    void slot_sendData(const QByteArray &jsonData);
    void slot_sendDownload(const QByteArray &jsonData);

signals:
    void sig_send_data(QString reqId, QByteArray data);
    void sig_swich_operaterwidget();
    // void statusReceived(QString str1, QString str2, QString str3, QString str4);
    void statusReceived(QStringList messageParts);
    void sig_set_cartesianCoords(QString message);//设置笛卡尔坐标系数据
    void sig_set_Joint(QString message);//设置关节角数据
    void sig_set_OneJoint(QString message);//设置单个关节角
    void sig_clamp_ok();
    void sig_clamp_motionisok();
    void sig_download(QString message);

};

#endif // TCPMGR_H
