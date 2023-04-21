#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
typedef struct Task
{
    void (*function)(void *arg);
    void *arg;
    struct Task *next;
} Task;
typedef struct Threadpool
{
    Task *queueFornt;      // 队列头
    Task *queueRear;       // 队列尾
    int num;               // 池中线程数量
    pthread_t *tid;        // 线程号
    pthread_mutex_t mutex; // 互斥锁
    pthread_cond_t cond;
    int flag; // 线程是否关闭的函数
} Threadpool;
void *worker(void *arg)
{
    Threadpool *pool = (Threadpool *)arg;
    while (1)
    {
        pthread_mutex_lock(&pool->mutex);
        // 当任务队列为空时阻塞等待任务
        while (pool->queueRear == pool->queueFornt && pool->flag == 0)
        {
            pthread_cond_wait(&pool->cond, &pool->mutex);
        }
        if (pool->flag == 1)
        {
            pthread_mutex_unlock(&pool->mutex);
            printf("线程池被关闭，线程%ld已退出\n", pthread_self());
            pthread_exit((void *)0);
        }
        // 获取任务
        Task task;
        Task *t = pool->queueFornt->next;
        task.function = t->function;
        task.arg = t->arg;
        pool->queueFornt->next = t->next;
        free(t);
        // 当任务
        if (pool->queueFornt->next == NULL)
        {
            pool->queueRear = pool->queueFornt;
        }
        pthread_mutex_unlock(&pool->mutex);
        printf("线程%ld正在工作", pthread_self());
        task.function(task.arg);
    }
}
Threadpool *creat_thread_init(int num)
{
    Threadpool *pool = (Threadpool *)malloc(sizeof(Threadpool)); // 为线程池结构体创建空间
    if (pool == NULL)
    {
        fprintf(stderr, "malloc Threadpool faliue");
    }
    pool->queueFornt = (Task *)malloc(sizeof(Task));
    if (pool->queueFornt == NULL)
    {
        fprintf(stderr, "malloc Task faliue\n");
        free(pool);
        return NULL;
    }
    pool->queueRear = pool->queueFornt; // 此时队列为空，让队头指向队尾
    pool->queueFornt->next = NULL;
    pool->tid = (pthread_t *)malloc(num * sizeof(pthread_t));
    if (pool->tid == NULL)
    {
        fprintf(stderr, "malloc pthread_t faliue\n");
        free(pool->queueFornt);
        free(pool);
        return NULL;
    }
    pool->num = num;
   // 循环创建线程池中的变量 
    int i; 
    for (i = 0; i < num; i++)
    {
        if (pthread_create(&pool->tid[i], NULL, worker, pool) != 0)
        {
            free(pool->queueFornt);
            free(pool->tid);
            free(pool);
            fprintf(stderr, "pthread_create faliue\n");
            return NULL;
        }
        pthread_detach(pool->tid[i]); // 线程结束后自动释放
    }
    pthread_mutex_init(&pool->mutex, NULL); // 初始化条件变量与互斥锁
    pthread_cond_init(&pool->cond, NULL);
    pool->flag = 0; // 设置线程池为运行状态
    return pool;
}

void task_function(void *arg)
{

    int n = *(int *)arg;
    printf("线程%ld正在工作 i=%d", pthread_self(), n);
    free(arg);
    sleep(1);
}
void task_add(Threadpool *pool, void (*function)(void *arg), void *arg)
{

    pthread_mutex_lock(&pool->mutex);
    Task *t = (Task *)malloc(sizeof(Task));
    if (t == NULL)
    {
        fprintf(stderr, "malloc Task faliue\n");
        return;
    }
    t->arg = arg;
    t->function = function;
    t->next = NULL;
    if (pool->queueRear == NULL)
    {
        pool->queueFornt = t;
        pool->queueRear = t;
    }
    else
    {
        pool->queueRear->next = t;
        pool->queueRear = t;
    }
    pthread_mutex_unlock(&pool->mutex);
    pthread_cond_signal(&pool->cond);
}
void destroy_thread(Threadpool *pool)
{
    pool->flag = 1;
    int i;
    for (i = 0; i < pool->num; i++)
    {
        pthread_cond_signal(&pool->cond);
    }
    free(pool->tid);
    while (pool->queueFornt->next != NULL)
    {
        Task *t = pool->queueFornt->next;
        pool->queueFornt->next = t->next;
        free(t);
    }
    free(pool->queueFornt);
    pthread_mutex_destroy(&pool->mutex);
    pthread_cond_destroy(&pool->cond);
    free(pool);
}
int main()
{
    Threadpool *pool = creat_thread_init(10);
    if (pool == NULL)
    {
        return -1;
    }
    printf("线程创建完成\n");
    sleep(1);
    int i = 0;
    // 将任务入队
    while (i < 50)
    {
        int *arg = (int *)malloc(sizeof(int));
        *arg = i;
        task_add(pool, task_function, arg);
        i++;
    }
    // destroy_thread(pool);
    sleep(5);
    return 0;
}