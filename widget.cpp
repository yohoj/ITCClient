#include "widget.h"
#include "ui_widget.h"
#include "config.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include<qpixmap.h>
#include<QProcess>
#include<QDebug>
#include<QStringList>
#include <unistd.h>
#include<QMessageBox>
#include"md5.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
       vidthread = NULL;
}

Widget::~Widget()
{
    delete ui;
}

//系统设置
void Widget::on_config_clicked()
{
   config tmp(this);
}

void Widget::on_login_clicked()
{


    ReqHead *msg = new ReqHead;
    msg->version = 1.0;
    msg->cmdNo = AUTH_REQ;
    msg->seqNo = 1;
    struct sockaddr_in addr;
    char buf[1024];
    char passwad[33];
    MD5Encode((void *)this->poss.toStdString().data(),(this->poss.length()),passwad);
    qDebug()<<passwad<<""<<this->poss<<"length"<<this->poss.length();
    sprintf(msg->body,"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
            "<REQUEST>"
            "<USER>%s</USER>"
            "<PASS>%s </PASS>"
            "</REQUEST>",this->id.toStdString().data(),passwad);
    msg->bodyLen = strlen((char *)msg->body);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(this->port.toInt());
    qDebug()<<ip;
    inet_pton(AF_INET,this->ip.toStdString().data(),&addr.sin_addr);
    sock = socket(AF_INET,SOCK_STREAM,0);
    if(::connect(sock,(struct sockaddr*)&addr,sizeof(struct sockaddr)) != 0)
    {
        perror("connect");
        ui->debug->setText("连接超时");
       return;
    }
    if(send(sock,msg,16,0) <= 0)
    {
        ui->debug->setText("登入失败，连接不上主机，请检查网络");
        return;
    }
    send(sock,msg->body,msg->bodyLen,0);
    int len;
   if(recv(sock,msg,16,0)  <= 0)
   {
        return;
   }
   len = recv(sock,buf,msg->bodyLen,0);
   buf[len] = '\0';
   qDebug()<<buf;
   document = new  TiXmlDocument;
   if(len > 0)
   {
   document->Parse((char *)buf);
   root = document->RootElement();
   }
   TiXmlString code;
   TiXmlString codeStr;
   if(!TinyXPath::o_xpath_string(root,"/RESPONSE/CODE/text()",code) || !TinyXPath::o_xpath_string(root,"/RESPONSE/DESC/text()",codeStr))
   {
       ui->debug->setText("解析错误");
            return ;
   }
    qDebug()<<"codeStr"<<codeStr.c_str();
   if(code.c_str()[0]-48 == 0)
    {
         ui->label_6->setText("已连接");
   }
    qDebug()<<code.c_str()<<"dfk"<<code.c_str()[0];
    ui->debug->setText(codeStr.c_str());

}


void Widget::on_open_clicked()
{
    if(vidthread == NULL)
       {
           //没在播放则启动播放
           vidthread = new VideoThread();
           vidthread->sock = this->sock;
           connect(vidthread,SIGNAL(recv_image(uchar*,int)),this,SLOT(recv_image_slot(uchar*,int)));
           connect(vidthread,SIGNAL(finished()),this,SLOT(video_thread_quit()));
           vidthread->start();
    }
}

void Widget::recv_image_slot(uchar *image,int size)
{
    memcpy(this->image,image,size);
    this->size = size;
    QPixmap pix;
    if(!pix.loadFromData(image,size)){

    }
    else{
        ui->imgaShow->setPixmap(pix);
    }
}

void Widget::video_thread_quit()
{
    disconnect(this,SLOT(recv_image_slot(uchar*,int)));
    disconnect(this,SLOT(video_thread_quit()));
    delete vidthread;
    vidthread = NULL;
    ui->imgaShow->setStyleSheet("background-color: rgb(0, 0, 0)");

}


void Widget::on_zhuapai_clicked()
{
    FILE *fp = fopen("./a.jpg","w");
    fwrite(image,size,1,fp);
    fclose(fp);
}

void Widget::on_stop_clicked()
{
   vidthread->SetStop();
}
