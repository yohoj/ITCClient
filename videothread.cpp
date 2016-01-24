#include "videothread.h"
#include"protocol.h"
#include <arpa/inet.h>
#include"widget.h"
#include <unistd.h>
VideoThread::VideoThread(QObject *parent) :
    QThread(parent)
{
    stopped = false;
}
void VideoThread::run()
{
    int size;
//    struct sockaddr_in addr;
    struct ReqHead head;
    uchar frame[320*240*3];

    int count=0;
    //创建TCP套接字
//    sock=socket(PF_INET,SOCK_STREAM,0);
//    addr.sin_family = AF_INET;
//    addr.sin_port = htons(6666);

//    char*  ch;

//    QByteArray ba = ip.toLatin1();

//    ch=ba.data();
//    inet_pton(AF_INET,ch,&addr.sin_addr);
//    //连接服务器
//    if(::connect(sock,(struct sockaddr*)&addr,sizeof(addr)) != 0){
//        ::close(sock);
//        return;
//    }
    //发送视频监控请求
    head.cmdNo = VIDEO_REQ;
    head.bodyLen = HEAD_SIZE;
    send(sock,&head,sizeof(head),0);
    while(!stopped) {
        //接收消息头
            if(recv(sock,&head,HEAD_SIZE,0)<=0) {
                ::close(sock);
                break;
            }
            count = 0;
            while(count < head.bodyLen){
               if((size = recv(sock,frame+count,head.bodyLen-count,0))<=0 ){
                    ::close(sock);
                    return;
                }
                count += size;
            }
            emit recv_image(frame,count);

    }
    qDebug()<<"stop";
    sleep(1);
//    ::close(sock);
    stopped = true;
}

void VideoThread::SetStop()
{
//     struct ReqHead head;
//    head.cmdNo = VIDEO_END_REQ;
//    head.bodyLen = 16;
//    send(sock,&head,sizeof(head),0);
//    recv(sock,&head,sizeof(head),0);
//    if(head.cmdNo == VIDEO_END_RSP)
//    {
//        qDebug()<<"fjdk"<<head.cmdNo;
//
//    }
    stopped = true;

}
