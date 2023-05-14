#include<stdio.h>
double tiaohe(double a,double b)
{
    double c,d;
    c=1/a+1/b;
    d=2/c;
    return d;
}
int main()
{
    double a,b,d;
    scanf("%lf %lf",&a,&b);
    d=tiaohe(a,b);
    printf("%f",d);
}