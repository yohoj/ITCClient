#ifndef PROTOCOL_H
#define PROTOCOL_H
#include<QString>
#define HEAD_SIZE 16
#define AUTH_REQ 0x000001
#define AUTH_RSP 0x900001
#define VIDEO_REQ 0x000002
#define VIDEO_RSP 0x900002
#define VIDEO_STM 0x000003
#define VIDEO_END_REQ 0x000004
#define VIDEO_END_RSP 0x900004
#define QUIT_REQ 0x000005
#define QUIT_RSP 0x900005


struct ReqHead {
    unsigned int version;
    unsigned int cmdNo;
    unsigned int seqNo;
    unsigned int bodyLen;
    char body[4096];
};

enum ERROR
{
    YES,//没有错误
    PASSW_E,//密码错误
    CONNECT_MAX,//最大连接数
};

#endif // PROTOCOL_H
