#include<stdio.h>
#include<pthread.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
pthread_mutex_t lock;
void *tfn(void *arg)
{
	while(1){
		pthread_mutex_lock(&lock);//加锁
		printf("hello ");
		sleep(1);
		printf("world!\n");
		pthread_mutex_unlock(&lock);
		sleep(1);
	}

}
int main()
{
	pthread_t tid;
	int ret=pthread_mutex_init(&lock,NULL);
	if(ret!=0){
		fprintf(stderr,"mutex init error:%d\n",strerror(ret));
		exit(1);
	}
	pthread_create(&tid,NULL,tfn,NULL);
	sleep(3);
	while(1){
		pthread_mutex_lock(&lock);
		printf("HELLO ");
		sleep(1);
		printf("WORLD!\n");
		pthread_mutex_unlock(&lock);
		sleep(1);
		//pthread_mutex_unlock(&lock);
	}
	pthread_join(tid,NULL);
	pthread_mutex_destroy(&lock);
	return 0;
}
