#ifndef ACCEPTTHREAD_H
#define ACCEPTTHREAD_H
#include <QThread>
#include<sys/socket.h>
#include"protocol.h"
#include<arpa/inet.h>
#include<sys/types.h>

class AcceptThread : public QThread
{
    Q_OBJECT
public:
    explicit AcceptThread(QObject *parent = 0);

    bool CreateTcpServer(int port);

    int DoClient(int s);
    
signals:
    void request_open();
    
public slots:

protected:
    void run();
private:
    bool stopped;
    int servSock;
};

#endif // ACCEPTTHREAD_H
