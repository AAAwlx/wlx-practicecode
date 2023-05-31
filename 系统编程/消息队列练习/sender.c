#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"proto.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main()
{
    int gid;
    key_t key;
    struct proto sendbuf;
    //获取key
    if ((key=ftok(KEYPATH,KEYPROJ))<0)
    {
        perror("ftok()");
        exit(1);
    }
    //创建消息队列
    sendbuf.chinese=60;
    sendbuf.math=60;
    strcpy(sendbuf.name,"xiaomin");
    if((gid=msgget(key,0))==-1){
        perror("msgget()");
        exit(1);
    }
    //发送消息
    if (msgsnd(gid,&sendbuf,sizeof(sendbuf),0)<0)
    {
        perror("msgsnd()");
        exit(1);
    }
    puts("ok!");
}