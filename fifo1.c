#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include <stdlib.h>
#define SIZE 1024
int main()
{
	int fd;
	char buffer[SIZE];
	mkfifo("/tmp/my_fifo",0666);
	fd=open("/tmp/my_fifo", O_WRONLY);
	if(fd<0){
		perror("open");
		exit(1);
	}
	int i=0;
	while(1){
		sprintf(buffer,"嘿嘿！我是%d号\n",i++);
		write(fd,buffer,strlen(buffer));
		sleep(1);
	}
	close(fd);
	return 0;
}