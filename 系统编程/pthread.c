#include<string.h>
#include <stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<pthread.h>
#include<stdio.h>
typedef struct{
	int var;
	char str[256];
}thrd;
void *tfn(void *arg)
{
	thrd *p=(thrd*)malloc(sizeof(thrd));
	p->var=0;
	strcpy(p->str,"hello thread");
	//return thrd *retval;
	pthread_exit(p);
}
int main(int argc, char *argv[])
{
	pthread_t tid;
	int ret =pthread_create(&tid,NULL,tfn,NULL);
	if(ret!=0){
		perror("pthread_create");
		exit(1);
	}
	thrd  *retval;
	pthread_join(tid,(void**)&retval);
	printf("%s",retval->str);
	free(retval);
	return 0;
}
