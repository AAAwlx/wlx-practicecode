#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
void sys_erro(char *str){
	perror(str);
	exit(1);
}
void *my_function(void *arg)
{
	printf("hello %lu,pid=%d",pthread_self(),getpid());
	return NULL;
}
int main(int argc,char *argv[])
{
	pthread_t tid;
	int ret=pthread_create(&tid,NULL,my_function,NULL);
	if(ret!=0){
		sys_erro("pthread_create");
	}
	printf("pid=%d\n",getpid());
	pthread_join(tid,NULL);
}
