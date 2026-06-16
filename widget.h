#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDateTime>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QTcpServer *mServer;
    QTcpSocket *mSocket;
    QString ipAddress;
    QString port;
private slots:
    void new_client(); //新用户发起连接函数
    void read_client_data();//读取客户端数据
    void client_dis();//客户端掉线
    void on_btnTcpConnect_clicked();

    void on_clear_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
