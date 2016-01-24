#include "network.h"
#include<QDataStream>
#include<QDebug>
#include<stdio.h>
#include"widget.h"
#define D qDebug()
QString network::host_ip = "0";
int network::messageNumber = 1;
int network::versions = 0x10000000;
network::network(QObject *parent) :
    QObject(parent)
{
    socket = new QTcpSocket(this);
    message_size = 0;
    ifConnect = false;
    connect(socket,SIGNAL(connected()),this,SLOT(connected_slot()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SIGNAL(connect_failed()));

}

network::~network()
{
    if(socket){
        delete socket;
    }

}
//接收消息
void network::receive_slot()
{

    int ret = socket->bytesAvailable();
     QDataStream in(socket);
     char buf[1024];
     int pool;
     while (ret = socket->bytesAvailable()) {
         if(message_size==0){
             in.readRawData((char*)&pool,4);
             in.readRawData((char*)&CMD,4);
             in.readRawData((char*)&pool,4);
             in.readRawData((char*)&message_size,4);
             D<<"cmd = "<<CMD<<" message_size = "<<message_size;
         }else if(socket->bytesAvailable()<message_size){
             return;
         }else{
             tmp = new char[message_size+1];
             int ret32 = in.readRawData(tmp,message_size);         
             DB(tmp);
             message_size = 0;
            emit receiveSig(CMD,tmp,ret32);
         }
     }

}
//连接成功
void network::connected_slot()
{
    emit connect_success();
    ifConnect = true;
    connect(socket,SIGNAL(readyRead()),this,SLOT(receive_slot()));//有消息可读
}
void network::connectHost(const char*ip,int port)
{

    socket->connectToHost(ip,port);
    connect(socket,SIGNAL(readyRead()),this,SLOT(receive_slot()));

}
void network::sendSlot(int cmd, QString xml_data)
{
    QByteArray send_data; //用于暂存我们要发送的数据
    QDataStream out(&send_data,QIODevice::WriteOnly);     //使用数据流写入数据
    out<<(quint32)versions;
    out<<(quint32) cmd;//指令号
    out<<(quint32) messageNumber;//序号
    out<<xml_data.toLocal8Bit();
    qint64 ret=socket->write(send_data);
    messageNumber++;

}
