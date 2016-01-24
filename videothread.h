#ifndef VIDEOTHREAD_H
#define VIDEOTHREAD_H

#include <QThread>
#include<sys/types.h>
#include<sys/socket.h>
#include"protocol.h"
#include <arpa/inet.h>

class VideoThread : public QThread
{
    Q_OBJECT
public:
    explicit VideoThread(QObject *parent = 0);
    int sock;
    void SetStop();
    
signals:
    void recv_image(uchar *,int);
public slots:

protected:
    void run();//线程执行函数
 private:

    bool stopped;    
};

#endif // VIDEOTHREAD_H
