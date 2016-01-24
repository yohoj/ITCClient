#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QDebug>
#include"acceptthread.h"
#include"videothread.h"
#include<QTextBrowser>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <xpath_static.h>
#include <string.h>
#include<QString>


#include <stdio.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private slots:
    void on_config_clicked();
    void on_login_clicked();
    void on_open_clicked();
    void recv_image_slot(uchar *,int);

       void video_thread_quit();
       void on_zhuapai_clicked();
       void on_stop_clicked();

public:
       QString ip;
       QString port;
       QString poss;
       QString id;
       QString vport;
private:
    Ui::Widget *ui;
    QString num;
     int s;//作为私有成员变量，可以在类里面的任何一个函数使用
     VideoThread *vidthread;
     AcceptThread *athread;
     int sock;
     uchar image[320*240*3];
     int size;
     TiXmlDocument *document;
     TiXmlElement *root;


};

#endif // WIDGET_H
