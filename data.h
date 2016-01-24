#ifndef DATA_H
#define DATA_H
typedef struct head
{
    int versions;
    int cmd;
    int number;
    int len;
}HEAD;

//登陆认证指令消息结构体
typedef struct login
{
    char name[20];//ID
    char password[10];//密码
}LOGIN_T;
//2登陆应答指令
enum ERROR
{
    YES,//没有错误
    NAME_E,//ID不存在
    PASSW_E,//密码错误
    CONNECT_MAX,//最大连接数
};




#endif // DATA_H
