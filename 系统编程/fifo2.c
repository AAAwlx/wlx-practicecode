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
    char buffer[SIZE];
    int fd;
    fd=open("/tmp/my_fifo",O_RDONLY);
    if(fd<0){
		perror("open");
		exit(1);
	}
    while(1){
        int len=read(fd,buffer,sizeof(buffer));
        write(STDOUT_FILENO,buffer,len);
        sleep(3);
    }
    close(fd);
    return 0;
}