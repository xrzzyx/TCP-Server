#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("TCP服务器");
    //TCP服务器对象
    mServer=new QTcpServer(this);
    //关联客户端连接信号
    connect(mServer,&QTcpServer::newConnection,this,&Widget::new_client);
    ui->pushButton_3->setDisabled(true);
    ui->btnTcpConnect->setShortcut(QKeySequence(Qt::ALT+Qt::Key_L));
}

Widget::~Widget()
{
    delete ui;
}

//新用户发起连接函数
void Widget::new_client()
{
     //与客户端连接的端点
    mSocket =mServer->nextPendingConnection();
     //接收客户端发来的数据信号
    connect(mSocket,&QTcpSocket::readyRead,this,&Widget::read_client_data);
    //检测到掉线信号
    connect(mSocket,&QTcpSocket::disconnected,this,&Widget::client_dis);
    //ip、端口、时间
    QString ip=mSocket->peerAddress().toString();
    int port=mSocket->peerPort();
    QString time=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->textEdit->append(time+QString("有新连接登录！！！IP地址是[%1],端口号是[%2]").arg(ip).arg(port));
}

void Widget::read_client_data()//读取客户端数据
{
     //来一个接收或者发送信息的QTcpscoket对象
    QTcpSocket *obj=(QTcpSocket*)sender();
     //读取数据
    QString msg=obj->readAll();
    //ip,端口,时间
    QString ip=mSocket->peerAddress().toString();
    int port=mSocket->peerPort();
    QString time=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->textEdit->append(time+QString("[%1:%2]：%3").arg(ip).arg(port).arg(msg));
}
void Widget::client_dis()//客户端掉线
{
    if(mServer->isListening())
    {
        QMessageBox::information(this,"提示","客户已经断开");
    }
}

void Widget::on_btnTcpConnect_clicked()
{
    if(ui->btnTcpConnect->text()=="服务器已经打开")
    {
        mServer->close();
        ui->btnTcpConnect->setText("打开服务器");
        ui->pushButton_3->setDisabled(true);
        ui->btnTcpConnect->setStyleSheet("background:white;color:black");
    }
    else
    {
        //ip、端口号
        ipAddress =ui->lineEditIpAddress->text();
        port=ui->lineEditPort->text();
        if(ipAddress.length()<7||port.length()==0)
        {
            QMessageBox::critical(this,"错误","请输入正确的ip、端口号");
            return;
        }
        //启动QSTcpServer服务器监听，监听任意地址、端口地址为8080
        mServer->listen(QHostAddress::Any,8080);
        ui->pushButton_3->setDisabled(false);
        ui->btnTcpConnect->setText("服务器已经打开");
        ui->btnTcpConnect->setStyleSheet("background:green;color:yellow;");
    }


}


void Widget::on_clear_clicked()
{
    ui->textEdit->setText("");
}


void Widget::on_pushButton_3_clicked()
{
    if(mServer->isListening())
    {
        mSocket->write(ui->sendData->text().toUtf8());
    }
}

