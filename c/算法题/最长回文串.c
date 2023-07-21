#include<stdio.h>
#include<string.h>
int is(int l,int r)
{

}
char * longestPalindrome(char * s){
    int max=0,i,j;
    int n=strlen(s);
    int b[100];
    for ( i = 0; i < n; i++)
    {
        for(j=i;j<n;j++){
            if (is(i,j))
            {
                b[i]=b[i]>b[j]+1?b[i]:b[j]+1;
            }
        }
    }
    
}
int main()
{
    longestPalindrome
}