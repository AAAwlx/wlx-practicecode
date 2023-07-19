#include<stdio.h>
#include<string.h>
int lengthOfLongestSubstring(char * s){
    int max=0,l=0,r=0,flag,j,i;
    for(i=0;i<strlen(s);i++){
            flag=0;
            for(j=l;j<i;j++){
                if(s[i]==s[j]){
                    flag=1;
                    break;
                }
            }
            if (flag==1){
                l=j+1;
            }
        if(max<i-l+1){
            max=i-l+1;
        }    
        
    }
    return max;
}
int main()
{
    int a=lengthOfLongestSubstring( "abcabcbb");
    int b=lengthOfLongestSubstring( "bbbbb");
    int c=lengthOfLongestSubstring( "abbcccb");
    printf("%d %d %d",a,b,c);
}