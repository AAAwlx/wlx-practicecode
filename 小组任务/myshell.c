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
#define BUFFER_SIZE 12
#define EXIT_SHELL -1
void PIP(char **buffer);
int command_7 = 0; // 后台命令默认为无
char arr[1000];
int flag[5] = {0};
void Print_infermation()
{
    char *name1 = "wlx@wlx-ThinkPad-T490";
    printf("\033[1m\033[32m%s\033[0m", name1);
    printf(":");
    getcwd(arr, sizeof(arr));
    printf("\033[1m\033[34m%s\033[0m", arr);
    uid_t euid = geteuid();
    if (euid == 0)
    {
        printf("#");
    }
    else
    {
        printf("$ ");
    }
    fflush(stdout);
}
void func_cd(char *pathname)
{
    if (pathname[0] == '-' && strlen(pathname) == 1)
    {
        strcpy(pathname, arr);
    }
    chdir(pathname);
    strcpy(arr, pathname);
    if (chdir(pathname) == -1)
    {
        printf("cd: 没有那个文件或目录: %s", pathname);
    }
    return;
}
//
void func_help()
{
    printf("hello myshell!");
}
int func_exit()
{
    return EXIT_SHELL;
}
char *readcommand() // 读取命令
{
    char *p = (char *)malloc(BUFFER_SIZE * sizeof(char));
    p = NULL;
    int i = 0, buffer_size = BUFFER_SIZE;
    while (1)
    {
        char c = getchar();
        if (c == EOF || c == '\n')
        {
            p[i] = '\0';
            break;
        }
        else
        {
            p[i] = c;
            i++;
        }
        if (i >= (BUFFER_SIZE))
        {
            buffer_size += BUFFER_SIZE;
            p = realloc(p, buffer_size);
        }
    }
    return p;
}

char **split_line(char *buffer) // 将命令与重定向的文件名分开后存入buffer，从管道命令数的后的一位开始为文件名，检查“>”与“>>“合并，在执行前只要检查文件名中是否有>即可
{
    char **p = (char **)malloc(12 * sizeof(char **)); // 0为>，1为<,2为管道,3为普通命令
    if (strstr(buffer, "|"))
    {
        int size = 12, i = 0;
        flag[2]++;                    // 需要创建管道符号的数量
        p[i++] = strtok(buffer, "|"); // buffer中依次存储了管道的命令，读入重定向的文件名和输出重定向的文件名
        while ((p[i] = strtok(NULL, "|")) != NULL)
        {
            flag[2]++;
            i++;
            if (i > size)
            {
                size += BUFFER_SIZE;
                p = realloc(p, size);
            }
        }
    }
    else if (strstr(buffer, ">"))
    {
        int size = 12, i = 0;
        flag[0]++; // 记录文件名重定向写入的数量
        p[i++] = strtok(buffer, ">");
        while ((p[i] = strtok(NULL, ">")) != NULL)
        {
            flag[0]++;
            i++;
            if (i > size)
            {
                size += BUFFER_SIZE;
                p = realloc(p, size);
            }
        }
    }
    else if (strstr(buffer, "<"))
    {

        int size = 12, i = 0;
        flag[1]++; // 记录文件名读入的数量
        p[i++] = strtok(buffer, "<");
        while ((p[i] = strtok(NULL, "<")) != NULL)
        {
            flag[0]++;
            i++;
            if (i > size)
            {
                size += BUFFER_SIZE;
                p = realloc(p, size);
            }
        }
    }
    else
    {
        flag[3] = 1;
    }
}
// 按空格分解命令与参数
char **Strtok(char *buffer)
{
    char **arg = (char **)malloc(12 * sizeof(char **));
    int i, size = 12;
    arg[i] = strtok(buffer, " ");
    while ((arg[i] = strtok(NULL, " ")) != NULL)
    {
        i++;
        if (i > size)
        {
            size += BUFFER_SIZE;
            arg = realloc(arg, size);
        }
    }
    return arg;
}
void DUP1(char **buffer)
{
    int i, n;
    n = flag[0] + flag[2];
    for (i = flag[2]; i < n; i++)
    {
        int fd;
        if (strstr(buffer[i], ">"))
        {
            fd = open(buffer[i], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        }
        else
        {
            fd = open(buffer[i], O_WRONLY | O_CREAT | O_APPEND, 0666); // 只写模式|表示如果指定文件不存在，则创建这个文件|表示追加，如果原来文件里面有内容，则这次写入会写在文件的最末尾。
        }
        dup2(fd, 1);
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            if (flag[2] > 0)
            {
                PIP(buffer); // 如果有管道命令跳到管道函数执行
            }
            else
            {
                char **arg = Strtok(buffer[0]); // 如果没有直接替换,先将命令切割为，命令与选项参数
                execvp(arg[0], arg);
            }
        }
        else
        {
            if (command_7 == 1)
            { // 如果后台运行就直接打印进程号并返回
                command_7 = 0;
                printf("%d\n", pid);
                return;
            }
            waitpid(pid, NULL, 0);
        }
    }
}
void DUP2(char **buffer)
{
    int i, n;
    n = flag[0] + flag[1] + flag[2];
    for (i = flag[2] + flag[0]; i < n; i++)
    {
        int fd;
        fd = open(buffer[i], O_RDONLY, 0666); // 只读
        dup2(fd, 0);
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            if (flag[2] > 0)
            {
                PIP(buffer); // 如果有管道命令跳到管道函数执行
            }
            else
            {
                char **arg = Strtok(buffer[0]); // 如果没有直接替换
                execvp(arg[0], arg);
            }
        }
        else
        {
            if (command_7 == 1)
            {
                command_7 = 0;
                printf("%d\n", pid);
                return;
            }
            waitpid(pid, NULL, 0);
        }
    }
}
void PIP(char **buffer) // 管道命令
{
    int n = flag[2] - 1, i;
    int fd[n][2]; // 存放管道描述符
    pid_t pid;
    for (i = 0; i < n; i++)
    {
        pipe(fd[i]);
    }
    for (i = 0; i < n + 1; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            break;
        }
    }
    if (pid == 0)
    {
        if (n)
        {
            if (i == 0)
            {                      // 如果是第一个子进程就将写端打开其余的全部关闭
                dup2(fd[0][1], 1); // 打开写
                close(fd[0][0]);   // 关闭读
                for (int j = 1; j < n; j++)
                {
                    close(fd[i][0]);
                    close(fd[i][1]);
                }
            }
            else if (i == n)
            {
                dup2(fd[i - 1][0], 0); // 打开读端
                close(fd[i - 1][1]);   // 关闭写端
                for (int j = 0; j < n - 1; j++)
                { // 其他进程读写端全部关闭
                    close(fd[j][1]);
                    close(fd[j][0]);
                }
            }
            else
            {
                dup2(fd[i - 1][0], 0); //
                close(fd[i - 1][1]);
                dup2(fd[i][1], 1);
                close(fd[i][0]);
                for (int j = 0; j < n; j++)
                {
                    if (j != i && j != (i - 1))
                    {
                        close(fd[j][0]);
                        close(fd[j][1]);
                    }
                }
            }
        }
        char **arg = Strtok(buffer[i]);
        execvp(arg[0], arg);
        perror("execvp");
        exit(1);
    }
    for (i = 0; i < n; i++)
    {
        close(fd[i][0]);
        close(fd[i][1]);
    }
    if (command_7 = 1)
    {
        command_7 = 0;
        printf("%d\n", pid);
        return;
    }
    for (int j = 0; j < n; j++)
        wait(NULL);
}
int do_command(char **buffer)
{
    if (flag[1])
    {
        DUP2(buffer);
    }
    else if (flag[0])
    {
        DUP1(buffer);
    }
    else if (flag[2])
    {
        PIP(buffer);
    }
    else if (flag[3])
    {
        char **arg = Strtok(buffer[0]);
        if (strcmp(arg[0], "cd"))
        {

            func_cd(arg[1]);
        }
        else if (strcmp(arg[0], "exit"))
        {
            return func_exit();
        }
        else if (strcmp(arg[0], "help"))
        {
            func_help();
        }
        else
        {
            if (strcmp(arg[0], "ll"))
            {
                strcpy(arg[0], "ls");
                strcat(arg[1], "l");
            } // 如果是ll就将他替换为ls -l
            pid_t pid = fork();
            if (pid < 0)
            {
                perror("fork");
                exit(1);
            }
            else if (pid == 0)
            {
                execvp(arg[0], arg);
                perror("commod");
                exit(1);
            }
            else
            {
                if (command_7 == 1)
                {
                    command_7 = 0;
                    printf("%d\n", pid);
                    return 0;
                }
                waitpid(pid, NULL, 0);
            }
        }
    }
}
int main(int argc, char **argv)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
    while (1)
    {
        Print_infermation();
        char *buffer = readcommand(); // 读入命令
        if (buffer == NULL)
        {
            printf("\n");
            continue;
        }
        char **p = split_line(buffer); // 解析命令,将文件名与命令分开
        int ret = do_command(p);
        if (ret == -1)
        {
            break;
        }
        free(buffer);
        free(p);
    }
}