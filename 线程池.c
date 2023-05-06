#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#define NUMBER 2
typedef struct task
{
    void(*function)(void *arg);
    void *arg;
}task;
typedef struct Pthreadpool
{
    task *taskQ;
    pthread_t *tidwork;//工作线程号
    pthread_t tidmanager;
    pthread_cond_t full;
    pthread_cond_t empty;
    pthread_mutex_t mutexpool;//线程池互斥锁
    pthread_mutex_t mutexbusy;//忙线程互斥锁
    //任务队列
    int queueFornt;//头
    int queueRear;//尾
    int queuesize;//当前任务队列中的任务数
    int queueCapacity;//容量
    int minNum;//最小线程数
    int maxNum;//最大线程数
    int busyNum;//忙线程
    int liveNum;//存活线程数
    int exitNum;//要杀死的线程个数
    int flag;//是否销毁线程池

}Pthreadpool;

void *threadExit(Pthreadpool *pool);

void task_function(void *arg)
{

    int n = *(int *)arg;
    printf("线程%ld正在工作 i=%d\n", pthread_self(), n);
    free(arg);
    sleep(1);
}
void *worker (void* arg)
{
   Pthreadpool*pool=(Pthreadpool*)arg;
   while(1){
         
        pthread_mutex_lock(&pool->mutexpool);
        // 当前任务队列是否为空
        while (pool->queuesize == 0 && !pool->flag)
        {
            // 阻塞工作线程
            pthread_cond_wait(&pool->empty, &pool->mutexpool);

            // 判断是不是要销毁线程
            if (pool->exitNum > 0)
            {
                pool->exitNum--;
                if (pool->liveNum > pool->minNum)
                {
                    pool->liveNum--;
                    pthread_mutex_unlock(&pool->mutexpool);
                    threadExit(pool);
                }
            }
        }

        // 判断线程池是否被关闭了
        if (pool->flag)
        {
            pthread_mutex_unlock(&pool->mutexpool);
            threadExit(pool);
        }

        task t;
        t.function=pool->taskQ[pool->queueFornt].function;
        t.arg=pool->taskQ[pool->queueFornt].arg;
        pool->queueFornt=(pool->queueFornt+1)%pool->queueCapacity;
        pool->queuesize--;
        pthread_cond_signal(&pool->full);//通知任务生产函数生产任务
        pthread_mutex_unlock(&pool->mutexpool);
        printf("thread %ld start working...\n", pthread_self());

        pthread_mutex_lock(&pool->mutexbusy);//忙线程+1
        pool->busyNum++;
        pthread_mutex_unlock(&pool->mutexbusy);
        t.function(t.arg);//执行任务
        t.arg==NULL;

        pthread_mutex_lock(&pool->mutexbusy);//任务完成后忙线程-1
        pool->busyNum--;
        pthread_mutex_unlock(&pool->mutexbusy);
    }   
}
void *threadExit(Pthreadpool *pool)
{
    pthread_t tid=pthread_self();
    int i;
    for(i=0;i<pool->maxNum;i++){
        if(pool->tidwork[i] == tid){
            pool->tidwork[i]=0;
            printf("threadExit() called, %ld exiting\n", tid);
            break;
        }    
    }
    pthread_exit(NULL);
}
void *manarge (void* arg)
{
    Pthreadpool *pool=(Pthreadpool *)arg;
    while (!pool->flag)
    {
        sleep(3);
        pthread_mutex_lock(&pool->mutexpool);
        int queuesize=pool->queuesize;//得到当前队列中任务的数量
        int liveNum=pool->liveNum;//得到当前存活线程数量
        pthread_mutex_unlock(&pool->mutexpool);
        pthread_mutex_lock(&pool->mutexbusy);
        int busyNum=pool->busyNum;
        pthread_mutex_unlock(&pool->mutexbusy);
        if(queuesize>liveNum&&liveNum<pool->maxNum){
            pthread_mutex_lock(&pool->mutexpool);
            int count=0,i;
            for(i=0; i < pool->maxNum && count < NUMBER && pool->liveNum < pool->maxNum; ++i){
                if(pool->tidwork[i]==0){
                    pthread_create(&pool->tidwork[i],NULL,worker,pool);
                    count++;
                    pool->liveNum++;
                }
            }
            pthread_mutex_unlock(&pool->mutexpool);
        }
        if(busyNum*2<liveNum&&liveNum>pool->minNum){
            pthread_mutex_lock(&pool->mutexpool);
            pool->exitNum=NUMBER;
            pthread_mutex_unlock(&pool->mutexpool);
            for(int i = 0; i < NUMBER; i++){
                pthread_cond_signal(&pool->empty);
            }
        }
    }
    
}
void task_push(Pthreadpool* pool,void (*function)(void *arg), void *arg)
{
    pthread_mutex_lock(&pool->mutexpool);
    while(pool->queuesize==pool->queueCapacity&&!pool->flag){
        pthread_cond_wait(&pool->full,&pool->mutexpool);
    }
    if(pool->flag==1){
        pthread_mutex_unlock(&pool->mutexpool);
        return;
    }
    pool->taskQ[pool->queueRear].function=function;
    pool->taskQ[pool->queueRear].arg=arg;
    pool->queueRear=(pool->queueRear+1)%pool->queueCapacity;
    pool->queuesize++;
    pthread_cond_signal(&pool->empty);
    pthread_mutex_unlock(&pool->mutexpool);
}
Pthreadpool * create_pool(int num,int max,int min)
{
    Pthreadpool *pool=(Pthreadpool*)malloc(sizeof(Pthreadpool));

    if(pool==NULL){
        printf("创建线程池失败\n");
        return 0;
    }
    pool->tidwork=(pthread_t*)malloc(sizeof(pthread_t)*max);
    if(pool->tidwork==NULL){
        free(pool);
        printf("线程号数组创建失败\n");
        return 0;
    }
    memset(pool->tidwork,0,sizeof(pthread_t)*max); 
    pool->queueCapacity=num;
    pool->maxNum=max;
    pool->minNum=min;
    pool->busyNum=0;
    pool->liveNum=min;
    pool->exitNum=0;
    pool->taskQ=malloc(sizeof(task)*num);
    if(pool->taskQ==NULL){
        free(pool->tidwork);
        free(pool);
        printf("线程号数组创建失败\n");
        return 0;
    }
    pool->queueCapacity=num;
    pool->queueFornt=0;
    pool->queueRear=0;
    pool->queuesize=0;
    pthread_create(&pool->tidmanager,NULL,manarge,pool);
    if (pthread_mutex_init(&pool->mutexpool, NULL) != 0 ||
            pthread_mutex_init(&pool->mutexbusy, NULL) != 0 ||
            pthread_cond_init(&pool->empty, NULL) != 0 ||
            pthread_cond_init(&pool->full, NULL) != 0)
        {
            free(pool->tidwork);
            free(pool);
            printf("mutex or condition init fail...\n");
        }
    int i;
    pool->flag=0;
    for(i=0;i<min;i++){
        pthread_create(&pool->tidwork[i],NULL,worker,pool);
    }
    return pool;
}
void destroy_pool(Pthreadpool * pool)
{
    int i;
    if(pool==NULL){
        return ;
    }
    pool->flag=1;
    pthread_join(pool->tidmanager,NULL);
    for(i=0;i<pool->liveNum;i++){
        pthread_cond_signal(&pool->empty);
    }
    if(pool->taskQ){
        free(pool->taskQ);
    }
    if(pool->tidwork){
        free(pool->tidwork);
    }
    pthread_mutex_destroy(&pool->mutexpool);
    pthread_mutex_destroy(&pool->mutexbusy);
    pthread_cond_destroy(&pool->empty);
    pthread_cond_destroy(&pool->full);

    free(pool);
    pool = NULL;

    return ;
}
int threadPoolBusyNum(Pthreadpool * pool)
{
    pthread_mutex_lock(&pool->mutexbusy);
    int busyNum = pool->busyNum;
    pthread_mutex_unlock(&pool->mutexbusy);
    return busyNum;
}

int threadPoolAliveNum( Pthreadpool * pool)
{
    pthread_mutex_lock(&pool->mutexpool);
    int aliveNum = pool->liveNum;
    pthread_mutex_unlock(&pool->mutexpool);
    return aliveNum;
}
int main()
{

    Pthreadpool *pool = create_pool(10,10,2);
    if (pool == NULL)
    {
        return -1;
    }
    printf("线程创建完成\n");
    int i = 0;
    // 将任务入队
    while (i < 50)
    {
        int *arg = (int *)malloc(sizeof(int));
        *arg = i;
        task_push(pool, task_function, arg);
        i++;
        
    }
    sleep(6);
    destroy_pool(pool);
    return 0;
}
