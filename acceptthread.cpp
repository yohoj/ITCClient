#include "acceptthread.h"
#include<QDebug>
#include <unistd.h>
AcceptThread::AcceptThread(QObject *parent) :
    QThread(parent)
{
    stopped = false;
}

bool AcceptThread::CreateTcpServer(int port)
{
    struct sockaddr_in addr;
    int reuse = 1;

    servSock = socket(PF_INET,SOCK_STREAM,0);
    if(servSock < 0)
    {
      qDebug()<<"Socket create failed\n";
      return false;
    }

    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    setsockopt(servSock,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
    if(0 != bind(servSock,(struct sockaddr *)&addr,sizeof(addr)))
    {
        qDebug()<<"Bind to port 777 failed\n";
        close(servSock);
        return false;
    }

    listen(servSock,5);
    return true;
}
void AcceptThread::run()
{
    int client;
    struct sockaddr_in caddr;
    socklen_t len;
    if(!CreateTcpServer(7777))
    {
        return;
    }
    while(!stopped)
    {
       len = sizeof(caddr);
       qDebug()<<"Start accept\n";
       client = accept(servSock,(struct sockaddr *)&caddr,&len);
       if(client < 0){
           qDebug()<<"Accept failed\n";
           break;
       }
       qDebug()<<"Accept a new connection\n";
       DoClient(client);
       ::close(client);
    }
    ::close(servSock);
}

int AcceptThread::DoClient(int sock)
{
    struct ReqHead head;
    char buf[1024];
    int size;
    size = recv(sock,&head,sizeof(head),0);
    if(size <= 0){
        return -1;
    }
    if(head.bodyLen > 0){
        size = recv(sock,buf,head.bodyLen,0);
        if(size <= 0)
           return -1;
    }
    switch(head.cmdId){
        case REQUEST_OPEN_DOOR:
            qDebug()<<"Request open door\n";
            emit request_open();
            break;
        default:
            qDebug()<<"Unknow command:"<<head.cmdId;
            return -1;
    }
    return 0;
}
