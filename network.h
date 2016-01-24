#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include<QTcpServer>
#include<QTcpSocket>
#include<QString>
#include"data.h"
class network : public QObject
{
    Q_OBJECT
public:
    explicit network(QObject *parent = 0);
    ~network();
    enum CMD{
        AUTH_REQ =	0x000001,//	登陆认证指令
        AUTH_RSP =	0x900001,//	登陆应答指令
        VIDEO_REQ =	0x000006,//	视频连接指令
        VIDEO_RSP =	0x900006,//	视频连接指令应答
        VIDEO_STM =	0x000007,//	视频流指令
        VIDEO_END_REQ =	0x000008,//	结束视频连接指令
        VIDEO_END_RSP =	0x900008,//	结束视频连接指令应
        QUIT_REQ =	0x0000FF,//	退出登陆请求
        QUIT_RSP =	0x9000FF,//	退出登陆应答


    };
public:
     static QString host_ip;//服务器IP
     QString host_port;//服务器端口
     static int versions;
     static int messageNumber;
     int CMD;
     int message_size;
     char*tmp;
     bool ifConnect;

public:

     void connectHost(const char *ip, int port);
private:
    QTcpSocket *socket;
    HEAD *head;

signals:
    void receiveSig(int cmd,char*data,int len);
    void connect_success();
    void connect_failed();

public slots:
    void receive_slot();
    void connected_slot();
    void sendSlot(int cmd, QString xml_data);

};

#endif // NETWORK_H
