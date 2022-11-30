#include<stdio.h>
double lifang(double a)
{
    double b=a*a*a;
    return b;
}
int main()
{
    double a,b;
    scanf("%lf",&a);
    b=lifang(a);
    printf("%f",b);
}