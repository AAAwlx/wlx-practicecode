#include<stdio.h>
int main()
{
	int i,j,n,t,a[10];//n为读入的数组个数，t为所求的和
	scanf("%d %d",&n,&t);
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	for(i=0;i<n;i++){//遍历数组中的每一个元素
		for(j=i+1;j<n;j++){//使当前元素与后面每一个元素相加作对比
			if(a[i]+a[j]==t){//若相等便返回两数的下标
				printf("%d %d",i,j);
			}
		}
	}
}

