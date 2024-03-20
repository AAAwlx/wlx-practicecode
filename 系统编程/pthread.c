#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

int nums[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int sum = 0,mutex = 1;
int i = 0;
void* tfn(void* arg) {
    while (mutex == 0){};
    mutex = 0;
    while (i < 10) {
        sum += nums[i];
        printf("nums[%d]=%d\n", i, nums[i]);
        i++;
    }
    mutex = 1;
    return NULL;
}
int main(int argc, char *argv[]) {
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, tfn, NULL);
    pthread_create(&tid2, NULL, tfn, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("sum:%d\n", sum);
    return 0;
}
