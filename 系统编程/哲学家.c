#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
sem_t cha[5];
pthread_mutex_t mutex;
int philosophers[5] = {0, 1, 2, 3, 4};
void err(char *arg)
{
    perror(arg);
    exit(1);
}
void *philosopher(void *arg)
{
    int i=*(int *)arg;
    int left=i;
    int right=(i+1)%5;
    while (1)
    {
        sleep(3);//哲学家思考
        pthread_mutex_lock(&mutex);
        sem_wait(&cha[left]);
        printf("哲学家%d拿起了%d号筷子,现在只有一支筷子,不能进餐\n", i, left);
        sem_wait(&cha[right]);
        printf("哲学家%d拿起了%d号筷子,开始进餐\n", i, right);
        pthread_mutex_unlock(&mutex);
        sleep(3);//模拟进餐时间
        sem_post(&cha[left]);
        printf("哲学家%d放下了%d号筷子\n", i, left);
        sem_post(&cha[right]);
        printf("哲学家%d放下了%d号筷子\n", i, right);
    }    
}
int main()
{
    int i;
    pthread_t tid[5];
    for(i=0;i<5;i++){
        sem_init(&cha[i],0,1);
    }//初始化信号量
    for(i=0;i<5;i++){
        pthread_create(&tid[i],NULL,philosopher,&philosophers[i]);
    }//创建五个哲学家的进程
    for(i=0;i<5;i++){
        pthread_join(tid[i],NULL);
    }//等待回收
    for(i=0;i<5;i++){
        sem_destroy(&cha[i]);
    }//销毁信号量
    pthread_mutex_destroy(&mutex);
    return 0;
}
