#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();
    if (pid < 0) {
        printf("fork error\n");
        exit(-1);
    } else if (pid == 0) {  // 子进程
        //setpgid(0, 0);  // 设置进程组ID为自己的进程ID
        printf("Child process: pid = %d, pgrp = %d\n", getpid(), getpgrp());
        // 子进程的任务
        exit(0);
    } else {  // 父进程
        printf("Parent process: pid = %d, pgrp = %d, child pid = %d\n", getpid(), getpgrp(), pid);
    }

    return 0;
}
