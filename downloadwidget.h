#ifndef DOWNLOADWIDGET_H
#define DOWNLOADWIDGET_H

#include <QWidget>

namespace Ui {
class DownLoadWidget;
}

class DownLoadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DownLoadWidget(QWidget *parent = nullptr);
    ~DownLoadWidget();



private slots:
    void on_RequestDownBtn_clicked();
    void on_CancelDownBtn_clicked();
    void slot_download(QString str);

signals:
    void sig_download(const QByteArray &jsonData);

private:
    Ui::DownLoadWidget *ui;
    QTimer *timer;

};

#endif // DOWNLOADWIDGET_H
