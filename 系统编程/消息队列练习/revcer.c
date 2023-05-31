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
    struct proto rcvbuf;
    if ((key=ftok(KEYPATH,KEYPROJ))<0)
    {
        perror("ftok()");
        exit(1);
    }
    if((gid=msgget(key,IPC_CREAT|0666))==-1){
        perror("msgget()");
        exit(1);
    }
    while (1)
    {
        if (msgrcv(gid,&rcvbuf,sizeof(rcvbuf),0,0))
        {
            perror("msgrcv");
            exit(1);
            printf("name %s\n",rcvbuf.name);
            printf("chinese=%d\n",rcvbuf.chinese);
            printf("math=%d'\n",rcvbuf.math);
        }
        
    }
    msgctl(gid,IPC_RMID,NULL);
}