#include<stdio.h>
int main()
{
    double a[10];
    int i;
    for(i=0;i<10;i++){
        scanf("%lf",&a[i]);
    }
    double max=0,min=a[0];
    for(i=0;i<10;i++){
        if(a[i]>max){
            max=a[i];
        }
        if(a[i]<min){
            min=a[i];
        }
    }
    printf("%f",max-min);
}