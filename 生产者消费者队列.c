#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
int count=0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_full = PTHREAD_COND_INITIALIZER;
struct SPSCQueue {
    int x;
    int capacity;
    struct SPSCQueue *next;
} typedef SPSCQueue;
SPSCQueue *queueFornt;
SPSCQueue *queueRear;
void SPSCQueueInit(int capacity)
{
    queueFornt=(SPSCQueue*)malloc(sizeof(SPSCQueue));
    queueRear=queueFornt;
    queueFornt->capacity=capacity;
    queueFornt->x=0;
    queueFornt->next=NULL;
}
void SPSCQueuePush(int x)
{
    SPSCQueue *node=(SPSCQueue*)malloc(sizeof(SPSCQueue));
    node->capacity=queueFornt->capacity;
    node->x=x;
    node->next=NULL;
    if(queueFornt->next==NULL){
        queueFornt->next=node;
    }
    queueRear->next=node;
    queueRear=node;
}
void *SPSCQueuePop()
{
    SPSCQueue *node=queueFornt->next;
    queueFornt->next=node->next;
    if(queueFornt->next==NULL){
       queueRear =queueFornt;
    }
    return node; 
}
void *producer(void *arg)
{
	int i=0;
	while(1){
		sleep(3);
		pthread_mutex_lock(&mutex);
		while(count==queueFornt->capacity){
			pthread_cond_wait(&cond_empty,&mutex);
		}
        i++;
        count++;
        SPSCQueuePush(i);
        printf("生产者生产了%d\n",i);
		pthread_cond_signal(&cond_full);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}
void *consumer(void *arg)
{
	while(1){
		sleep(1);
		pthread_mutex_lock(&mutex);
		while(count==0){//防止虚假唤醒
			pthread_cond_wait(&cond_full,&mutex);
		}
        SPSCQueue *node=SPSCQueuePop();
        printf("消费者消费了%d\n",node->x);
        free(node);
        count--;
		pthread_cond_signal(&cond_empty);
		pthread_mutex_unlock(&mutex);
	}
}
int main()
{
	pthread_t tid1;
	pthread_t tid2;
    SPSCQueueInit(5);
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