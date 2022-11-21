#include<stdio.h>
int main()
{
    int a[100] ,i,j,t,n;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }//输入
    for(i=1;i<n-1;i++){//计算完成排序所需的最大轮数
        if(a[i]<a[i-1]){//若无序数列的第一个值小于有序数列的最后一个值，则遍历有序数列直至找到大于该值的数
            t=a[i];
            for(j=i-1;j>=0&&a[j];j--){
                a[j+1]=a[j];//将有序数列的值依次向后挪一个位置留下待插入的空位
            }
            a[j+1]=t;//将该值插入到空位中
        }
    }
    for(i=0;i<n;i++){
    printf("%d ",a[i]);
    }//输出
    return 0;
}
