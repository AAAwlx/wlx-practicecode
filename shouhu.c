/*************************************************************************
	> File Name: hello.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2023年04月09日 星期日 21时30分08秒
 ************************************************************************/

#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h >
#include<unistd.h>
#include<errno.h >
#include<pthread.h>
#include<string.h>
#include<sys/stat.h>
int main()
{
	pid_t pid;
	int ret;
	pid=fork();
	if(pid>0){//父进程退出
		exit(0);
	} 
	pid=setsid();//创建会话
	if(pid<0){
		perro("setsid errno");
		exit(1);
	}
	ret=chdir("/home/wlx");//切换工作目录
	if(ret==-1){
		perro("chdir ");
		exit(1);
	}
	umask(0022);//修改文件权限码
	close(STDIN_FIEND);
	int fd=open("/dev/null",O_RDWR);//将文件描述符关闭
	if(fd==-1){
		perro("open");
		exit(1);
	}
	dup2(fd,1);
	dup2(fd,2);
	while(1);//模拟守护进程业务
	return 0;
}
