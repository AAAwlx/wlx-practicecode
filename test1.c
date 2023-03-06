#include <unistd.h>    // 提供execvp()函数的原型
#include <sys/types.h> // 提供pid_t类型定义
#include <sys/wait.h>  // 提供waitpid()函数的原型
#include <stdio.h>
int main()
{
    char *arg[3];
    arg[0]="ls";
    arg[1]=".";
    arg[2]=0;
    printf("A to ls -l\n");
    if(execvp("ls",arg)){
        perror("execvp"); 
    }    
    printf("ls is done\n");
}