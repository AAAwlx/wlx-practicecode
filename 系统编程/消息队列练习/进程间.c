#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MSG_SIZE 1024

// 定义消息结构体
struct msgbuf {
    long mtype;           // 消息类型
    char mtext[MAX_MSG_SIZE];  // 消息内容
};

int main() {
    pid_t pid;
    key_t key;
    int msgid;
    struct msgbuf sendbuf, recvbuf;
    
    // 生成key值
    if ((key = ftok(".", 'a')) == -1) {
        perror("ftok error");
        exit(1);
    }

    // 创建或获取消息队列
    if ((msgid = msgget(key, IPC_CREAT | 0666)) == -1) {
        perror("msgget error");
        exit(1);
    }
    
    // 创建子进程
    pid = fork();
    if (pid == -1) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {  // 子进程
        if (msgrcv(msgid, &recvbuf, MAX_MSG_SIZE, 2, 0) == -1) {
            perror("msgrcv error");
            exit(1);
        }
        printf("[Child] Received message: %s\n", recvbuf.mtext);

        // 发送响应消息
        sendbuf.mtype = 3;
        strcpy(sendbuf.mtext, "Response from child process.");
        if (msgsnd(msgid, &sendbuf, strlen(sendbuf.mtext)+1, 0) == -1) {
            perror("msgsnd error");
            exit(1);
        }
    } else {  // 父进程
        // 发送消息给子进程
        sendbuf.mtype = 2;
        strcpy(sendbuf.mtext, "Message from parent process.");
        if (msgsnd(msgid, &sendbuf, strlen(sendbuf.mtext)+1, 0) == -1) {
            perror("msgsnd error");
            exit(1);
        }

        // 等待子进程的响应
        wait(NULL);
        if (msgrcv(msgid, &recvbuf, MAX_MSG_SIZE, 3, 0) == -1) {
            perror("msgrcv error");
            exit(1);
        }
        printf("[Parent] Received response: %s\n", recvbuf.mtext);

        // 删除消息队列
        if (msgctl(msgid, IPC_RMID, NULL) == -1) {
            perror("msgctl error");
            exit(1);
        }
    }

    return 0;
}
