#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid1, pid2;

    // 创建第一个子进程
    pid1 = fork();
    int num2=0;
    int num1=0;
    if (pid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        // 子进程1的代码
        printf("Child process 1 (PID: %d)\n", getpid());
        exit(3);
    } else {
        // 父进程
        printf("Parent process (PID: %d)\n", getpid());
        
        // 创建第二个子进程
        pid2 = fork();

        if (pid2 < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid2 == 0) {
            // 子进程2的代码
            printf("Child process 2 (PID: %d)\n", getpid());
            exit(8);
        }else 
        {
            
            wait(&num2);
        }
        
        wait(&num1);
    }

    // 父进程代码
    printf("Parent process exiting %d %d\n",WEXITSTATUS(num1),WEXITSTATUS(num2));

    return 0;
}


/*int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // 子进程
        printf("Child process\n");
        exit(EXIT_SUCCESS);
    } else {
        // 父进程
        printf("Parent process\n");

        int status;
        // 等待子进程结束
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        }

        printf("Parent process exiting\n");
    }

    return 0;
}*/