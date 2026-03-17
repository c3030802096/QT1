#include <QThread>
#include <QImage>
#include <QByteArray>
#include <zmq.hpp>

class ResultReceiver : public QThread {
    Q_OBJECT
public:
    void run() override {
        zmq::context_t context(1);
        zmq::socket_t subscriber(context, zmq::socket_type::sub);
        QString connectionString = QString("tcp://%1:%2").arg(host).arg(port);
        subscriber.connect(connectionString.toStdString().c_str());
        subscriber.set(zmq::sockopt::subscribe, "");

        while (true) {
            zmq::message_t msg;
            subscriber.recv(msg, zmq::recv_flags::none);
            QByteArray data((char*)msg.data(), msg.size());

            QImage image;
            image.loadFromData(data, "JPG");

            if (!image.isNull()) {
                emit resultReceived(image);
            }
        }
    }

    QString host;
    QString port;
signals:
    void resultReceived(const QImage &image);
};
