/*#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

int nums[5000];
int sum = 0,mutex = 1;
int i = 0;
void* tfn(void* arg) {
    while (mutex == 0){};
    mutex = 0;
    while (i < 5000) {
        sum += nums[i];
        printf("nums[%d]=%d\n", i, nums[i]);
        i++;
    }
    mutex = 1;
    return NULL;
}
int main(int argc, char *argv[]) {
    pthread_t tid1, tid2;
    for (int i = 0; i < 5000;i++ )
    {
        nums[i] = i;

    }

    pthread_create(&tid1, NULL, tfn, NULL);
    pthread_create(&tid2, NULL, tfn, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("sum:%d\n", sum);
    return 0;
}*/
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
void* tfn(void* arg) {
    int i;
    for (int i = 0; i < 500; i++)
    {
       printf("%d\n",i);
    }
    return NULL;
}
int main()
{
    pthread_t th;
    pthread_create(&th, NULL, tfn, NULL);
    pthread_join(th, NULL);
    return 0;
}