#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
int buffer[10];
int count=0;
int in=0;
int out=0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_full = PTHREAD_COND_INITIALIZER;
void *producer(void *arg)
{
	int i=0;
	while(1){
		sleep(3);
		pthread_mutex_lock(&mutex);
		if(count==10){
			pthread_cond_wait(&cond_empty,&mutex);
		}
		in=(in+1)%10;
		i++;
		buffer[in]=i;
		printf("生产者生产了%d\n",i);
		count++;
		pthread_cond_signal(&cond_full);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}
void *consumer(void *arg)
{
	int i=0;
	while(1){
		sleep(1);
		pthread_mutex_lock(&mutex);
		if(count==0){
			pthread_cond_wait(&cond_full,&mutex);
		}
		out=(out+1)%10;
		i=buffer[out];
		printf("消费者消费了%d\n",i);
		count--;
		pthread_cond_signal(&cond_empty);
		pthread_mutex_unlock(&mutex);
	}
}
int main()
{
	pthread_t tid1;
	pthread_t tid2;
	int ret1=pthread_create(&tid1,NULL,producer,NULL);
	int ret2=pthread_create(&tid2,NULL,consumer,NULL);
	if(ret1!=0||ret2!=0){
		perror("pthread_create");
		exit(1);
	}
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	return 0;
}
