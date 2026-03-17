#include "TcpMgr.h"
#include "qjsonobject.h"
#include <QJsonDocument>
#include <QDataStream>
#include <QMutex>
#include <QMessageBox>
#include <QTextCodec>
TcpMgr::TcpMgr():_host(""),_port(0),_b_recv_pending(false),_message_id(),_message_len(),_b_recv_pending2(false)
{

    //监听连接请求
    QObject::connect(&controlSocket, &QTcpSocket::connected, [&]() {
        // qDebug() << "Connected to server!";
        addconnectedCount(); // 检查连接状态
    });

    //监听连接请求
    QObject::connect(&statusSocket, &QTcpSocket::connected, [&]() {
        // qDebug() << "Connected to server!";
        addconnectedCount(); // 检查连接状态
    });


    // 监听消息发送
    //读取状态消息
    QObject::connect(&statusSocket, &QTcpSocket::readyRead, [&]() {
        // 当有数据可读时，读取所有数据
        // 读取所有数据并追加到缓冲区
        _buffer.append(statusSocket.readAll());

        QDataStream stream(&_buffer, QIODevice::ReadOnly);
        stream.setVersion(QDataStream::Qt_5_0);
        qDebug() << "Received data:" << _buffer;

        forever {
            // 先解析头部
            if (!_b_recv_pending) {
                // 检查缓冲区中的数据是否足够解析出两个 QString（共 8 字节）
                if (_buffer.size() < 10) {
                    return; // 数据不够，等待更多数据
                }

                QByteArray data = _buffer.mid(0, 10);
                // 提取两个 4 字节的部分
                QByteArray firstStringData = data.mid(0, 4);
                QByteArray secondStringData = data.mid(5, 4);

                // 转换为 QString
                QString firstString = QString::fromUtf8(firstStringData);
                QString secondString = QString::fromUtf8(secondStringData);

                qDebug() << "First String:" << firstString;
                qDebug() << "Second String:" << secondString;

                // 从缓冲区中移除已处理的数据
                _buffer.remove(0, 10);

                bool ok;
                int messageLength = secondString.toInt(&ok);

                if (ok) {
                    qDebug() << "Message Length as int:" << messageLength;
                } else {
                    qWarning() << "Failed to convert secondString to int:" << secondString;
                }

                qDebug() << "Buffer size:" << _buffer.size();

                // 检查缓冲区是否足够读取消息体
                if (_buffer.size() < messageLength) {
                    _b_recv_pending = true; // 标记为等待状态
                    return; // 数据不够，等待更多数据
                }

                // 如果有足够的数据，读取消息体
                QByteArray messageBody = _buffer.mid(0, messageLength);
                qDebug() << "Received body msg is" << messageBody;

                // 从缓冲区中移除消息体
                _buffer.remove(0, messageLength);
                // 处理消息体
                handleMsg(firstString, messageLength, messageBody);
            }
        }
    });

    //读取动作消息回包
    QObject::connect(&controlSocket, &QTcpSocket::readyRead, [&]() {
        // 当有数据可读时，读取所有数据
        // 读取所有数据并追加到缓冲区
        _buffer2.append(controlSocket.readAll());

        QDataStream stream(&_buffer2, QIODevice::ReadOnly);
        stream.setVersion(QDataStream::Qt_5_0);
        qDebug() << "Received data:" << _buffer2;

        forever {
            // 先解析头部
            if (!_b_recv_pending2) {
                if (_buffer2.size() < 10) {
                    return; // 数据不够，等待更多数据
                }

                QByteArray data = _buffer2.mid(0, 10);
                // 提取两个 4 字节的部分
                QByteArray firstStringData = data.mid(0, 4);
                QByteArray secondStringData = data.mid(5, 4);

                // 转换为 QString
                QString firstString = QString::fromUtf8(firstStringData);
                QString secondString = QString::fromUtf8(secondStringData);

                qDebug() << "First String:" << firstString;
                qDebug() << "Second String:" << secondString;

                // 从缓冲区中移除已处理的数据
                _buffer2.remove(0, 10);

                // 假设 secondString 是从缓冲区中提取的第二个 4 字节字符串
                bool ok;
                int messageLength = secondString.toInt(&ok);

                if (ok) {
                    qDebug() << "Message Length as int:" << messageLength;
                } else {
                    qWarning() << "Failed to convert secondString to int:" << secondString;
                }

                qDebug() << "Buffer size:" << _buffer2.size();

                // 检查缓冲区是否足够读取消息体
                if (_buffer2.size() < messageLength) {
                    _b_recv_pending2 = true; // 标记为等待状态
                    return; // 数据不够，等待更多数据
                }

                // 如果有足够的数据，读取消息体
                QByteArray messageBody = _buffer2.mid(0, messageLength);
                qDebug() << "Received body msg is" << messageBody;

                // 从缓冲区中移除消息体
                _buffer2.remove(0, messageLength);
                // 处理消息体
                handleMsg2(firstString, messageLength, messageBody);
            }
        }
    });


    // 读取消息回包
    QObject::connect(&Socket1, &QTcpSocket::readyRead, [&]() {
        QByteArray data = Socket1.readAll();
        qDebug() << "Received (raw):" << data;

        // **假设服务器返回的是 GBK 编码**
        QTextCodec *codec = QTextCodec::codecForName("GBK");
        QString jsonString = codec->toUnicode(data);
        // qDebug() << "Received (converted from GBK):" << jsonString;

        // 解析 JSON 响应
        QJsonDocument jsonResponse = QJsonDocument::fromJson(jsonString.toUtf8());
        if (!jsonResponse.isNull() && jsonResponse.isObject()) {
            QJsonObject jsonObj = jsonResponse.object();
            // qDebug() << "Parsed JSON Response:" << jsonObj;

            // 提取 "Category" 字段
            if (jsonObj.contains("Category") && jsonObj["Category"].isString()) {
                QString category = jsonObj["Category"].toString();
                qDebug() << "Category (UTF-8):" << category; // 应该正确显示中文
                //发送响应请求
                emit sig_download(category);
            } else {
                qDebug() << "Category field not found or invalid";
            }
        } else {
            qDebug() << "Invalid JSON response";
        }
    });


    //5.15 之后版本
    QObject::connect(&statusSocket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred), [&](QAbstractSocket::SocketError socketError) {
        Q_UNUSED(socketError)
        qDebug() << "Error:" << statusSocket.errorString();
        // 显示警告框
        QMessageBox::critical(nullptr, "网络错误", "状态连接异常，请重新连接");
    });
    QObject::connect(&controlSocket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred), [&](QAbstractSocket::SocketError socketError) {
        Q_UNUSED(socketError)
        qDebug() << "Error:" << controlSocket.errorString();
        // 显示警告框
        QMessageBox::critical(nullptr, "网络错误", "控制连接异常，请重新连接 ");
    });

    // 处理错误（适用于Qt 5.15之前的版本）
    // QObject::connect(&_socket, static_cast<void (QTcpSocket::*)(QTcpSocket::SocketError)>(&QTcpSocket::error),
    //                  [&](QTcpSocket::SocketError socketError) {
    //                      qDebug() << "Error:" << _socket.errorString() ;
    //                      switch (socketError) {
    //                      case QTcpSocket::ConnectionRefusedError:
    //                          qDebug() << "Connection Refused!";
    //                          break;
    //                      case QTcpSocket::RemoteHostClosedError:
    //                          qDebug() << "Remote Host Closed Connection!";
    //                          break;
    //                      case QTcpSocket::HostNotFoundError:
    //                          qDebug() << "Host Not Found!";
    //                          break;
    //                      case QTcpSocket::SocketTimeoutError:
    //                          qDebug() << "Connection Timeout!";
    //                          break;
    //                      case QTcpSocket::NetworkError:
    //                          qDebug() << "Network Error!";
    //                          break;
    //                      default:
    //                          qDebug() << "Other Error!";
    //                          break;
    //                      }
    //                  });

    // 处理连接断开
    QObject::connect(&statusSocket, &QTcpSocket::disconnected, [&]() {
        qDebug() << "statusSocket Disconnected from server.";
        if (connectedCount > 0) {
            subconnectedCount();
        }
    });
    QObject::connect(&controlSocket, &QTcpSocket::disconnected, [&]() {
        qDebug() << "controlSocket Disconnected from server.";
        if (connectedCount > 0) {
            subconnectedCount();
        }
    });
    //数据发送
    QObject::connect(this, &TcpMgr::sig_send_data, this, &TcpMgr::slot_send_data);

    //注册消息
    initHandlers();//状态回包接收
    initHandlers2();//动作完成回包接收
}

void TcpMgr::Disconnect()
{
    statusSocket.disconnectFromHost();
    controlSocket.disconnectFromHost();
}

bool TcpMgr::IsConnected()
{
    return _IsConnected ? true : false;
}

void TcpMgr::RECOVR()
{
    emit sig_clamp_ok();
    clampstop_index = 0;
}

void TcpMgr::addconnectedCount()
{
    std::lock_guard<std::mutex> lock(mtx);  // 自动加锁和解锁
    connectedCount++;
    if (connectedCount == 2) {
        emit sig_swich_operaterwidget(); // 两个socket都连接后发送信号
        _IsConnected = true;
    }
}

void TcpMgr::subconnectedCount()
{
    std::lock_guard<std::mutex> lock(mtx);  // 自动加锁和解锁
    connectedCount--;
}

//服务器状态消息
void TcpMgr::initHandlers()
{
    //状态消息回包
    _handlers.insert("stat", [this](QString id, int len, QByteArray data) {
        // 解析消息内容
        QString message = QString::fromUtf8(data);
        QStringList messageParts = message.split('&');

        if (messageParts.size() != 7) {
            qDebug() << "Invalid status data format.";
            return; // 处理格式错误
        }

        // 获取笛卡尔坐标和关节角,夹爪
        QString cartesianCoords = messageParts[0]; // "0,0,0,0,0,0"
        QString jointAngles = messageParts[1];      // "0,0,0,0,0,0,0"
        QString motionStatus = messageParts[2];      // "0"
        QString clampStatus = messageParts[3];      //"0,0"
        QString movedistance = messageParts[4];     //x,0
        QString statuscode = messageParts[5];     //状态码
        QString jdw = messageParts[6];
        // 输出解析的数据
        qDebug() << "Cartesian Coords:" << cartesianCoords;
        qDebug() << "Joint Angles:" << jointAngles;
        qDebug() << "Motion Status:" << motionStatus;
        qDebug() << "Clamp Status:" << clampStatus;
        qDebug() << "movedistance:" << movedistance;
        qDebug() << "statuscode:" << statuscode;
        qDebug() << "jdw:" << jdw;
        // emit statusReceived(cartesianCoords, jointAngles, motionStatus, clampStatus);//设置机械臂状态
        emit statusReceived(messageParts);
        // 如果运动状态是 0，发送回包
        if (motionStatus == "0") {
            slot_send_data("stat","0");
        }
        else {
            slot_send_data("stat","0");
        }
    });
}

//动作完成回包(server发起
void TcpMgr::initHandlers2()
{
    //机器人某个关节持续运动|停止（点动效果）
    _handlers2.insert("mpot", [this](QString id, int len, QByteArray data){
        QString message = QString::fromUtf8(data);
        // QStringList msglist = message.split("|");
        // if(msglist.size() != 1) {
        //     qWarning() << "invalid msg";
        //     return;
        // }
        //可以继续下一个操作
        clampstop_index++;
        // clampstop_index++;
        if(clampstop_index == 2) {
            emit sig_clamp_ok();
            clampstop_index = 0;
        }
    });
//让机器人运动到点(关节角Z1,Z2,Z3,J1,J2,J3,Z4)
    _handlers2.insert("gptj", [this](QString id, int len, QByteArray data){
        // 解析消息内容
        QString message = QString::fromUtf8(data);//
        clampstop_index++;
        clampstop_index++;
        if(clampstop_index == 2) {
            emit sig_clamp_ok();
            clampstop_index = 0;
        }
    });

    _handlers2.insert("gjot", [this](QString id, int len, QByteArray data){
        // 解析消息内容
        QString message = QString::fromUtf8(data);//
        clampstop_index++;
        if(clampstop_index == 2) {
            emit sig_clamp_ok();
            clampstop_index = 0;
        }
    });

    _handlers2.insert("mjot", [this](QString id, int len, QByteArray data){
        // 解析消息内容
        QString message = QString::fromUtf8(data);//
        clampstop_index++;
        if(clampstop_index == 2) {
            emit sig_clamp_ok();
            clampstop_index = 0;
        }
    });
//机器人某个夹爪夹紧|松开（开关）
    _handlers2.insert("aclp", [this](QString id, int len, QByteArray data){
        QString message = QString::fromUtf8(data);//
        clampstop_index++;
        if(clampstop_index == 2) {
            emit sig_clamp_ok();
            clampstop_index = 0;
        }


    });
//机器人夹爪位置调整（点动效果）
    _handlers2.insert("mclp", [this](QString id, int len, QByteArray data){
        QString message = QString::fromUtf8(data);//
        clampstop_index++;
        if(clampstop_index == 2) {
            emit sig_clamp_ok();
            clampstop_index = 0;
        }
    });
}

void TcpMgr::slot_send_data(QString reqId, QByteArray dataBytes)
{
    // 计算 dataBytes 的长度
    quint16 length = static_cast<quint16>(dataBytes.length());

    // 转换长度为字符串
    QString lengthStr = QString::number(length).rightJustified(4, '0'); // 右对齐，不足时在前面补零
    QByteArray lengthBytes = lengthStr.toUtf8(); // 转换为 QByteArray

    // 创建一个 QByteArray 用于存储要发送的所有数据
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    // 设置数据流使用网络字节序
    out.setByteOrder(QDataStream::BigEndian);

    // 将 reqId 转换为 4 字节
    QByteArray reqIdBytes = reqId.toUtf8();
    reqIdBytes.resize(4); // 确保 reqIdBytes 的长度为 4，不足时填充
    reqIdBytes.append('|'); // 在 reqIdBytes 后添加符号 '|'

    // 将 dataBytes 前添加符号 '|'
    QByteArray modifiedDataBytes = '|' + dataBytes;

    // 写入 reqId 和长度
    block.append(reqIdBytes); // 添加 reqId
    block.append(lengthBytes); // 添加长度
    block.append(modifiedDataBytes); // 添加修改后的消息体

    if(reqId == "stat") {
        statusSocket.write(block);
    }else{
        // 发送数据
        controlSocket.write(block);
    }

    qDebug() << "tcp mgr send byte data is " << block;
}


//连接tcp服务器
void TcpMgr::slot_tcp_connect(std::shared_ptr<ServerInfo> si)
{

    _host = si->Host1;
    c_port = static_cast<uint16_t>(si->controlPort);
    s_port = static_cast<uint16_t>(si->statusPort);
    // port0 = static_cast<uint16_t>(si->Port0);
    port1 = static_cast<uint16_t>(si->Port1);

    controlSocket.connectToHost(si->Host1, c_port);
    statusSocket.connectToHost(si->Host1, s_port);
    // Socket0.connectToHost(si->Host2, port0);
    Socket1.connectToHost(si->Host2, port1);
}

//消息解析
void TcpMgr::handleMsg(QString id, int len, QByteArray data)
{
    auto find_iter =  _handlers.find(id);
    if(find_iter == _handlers.end()){
        qDebug()<< "not found id ["<< id << "] to handle";
        return ;
    }

    find_iter.value()(id,len,data);
}

//消息解析2
void TcpMgr::handleMsg2(QString id, int len, QByteArray data)
{
    auto find_iter =  _handlers2.find(id);
    if(find_iter == _handlers2.end()){
        qDebug()<< "not found id ["<< id << "] to handle";
        return ;
    }

    find_iter.value()(id,len,data);
}


//300ms定时响应
void TcpMgr::slot_sendData(const QByteArray &jsonData)
{
    // QByteArray data = jsonData + "\x0D\x0A";
    // // qDebug()<<"9090"<<data;
    // Socket0.write(data);
    // Socket0.flush();
}

//安装请求
void TcpMgr::slot_sendDownload(const QByteArray &jsonData)
{
    // QByteArray utf8Data = QString::fromUtf8(jsonData).toUtf8() + "\x0D\x0A";
    QByteArray data = jsonData + "\x0D\x0A";
    Socket1.write(data);
    Socket1.flush();
}


