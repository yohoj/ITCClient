#include"widget.h"
#include"ui_widget.h"
#include<QMessageBox>
#include<QDomDocument>
#include<qdebug.h>
#define D qDebug()
//登陆
void Widget::logInRsp(char*data)
{
    QDomDocument*doc = new QDomDocument;
     doc->setContent(QString(data),false);//装置XML数据
     QDomElement head = doc->documentElement().firstChildElement();
     head = head.nextSiblingElement();
     D<<head.tagName();
     
}

//视频链接VIDEO_RSP
void Widget::videoRsp(char *data)
{

}
//关闭视频
void Widget::videoEndRsp()
{

}
