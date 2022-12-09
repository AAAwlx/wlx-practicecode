#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int main( )
{
    int i,a[1000],b[11],j;
    for(i=0;i<11;i++){
        b[i]=0;
    }
    srand((unsigned)time( NULL ) );
    for(i = 0; i < 1000;i++){
        a[i]=rand()%10+1;
    }
   for(i=0;i<1000;i++){
        j=a[i];
        b[j]+=1;
    }
    for(i=0;i<10;i++){
        printf("%d ",b[i]);
    }
}
