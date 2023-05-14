#include<stdio.h>
#include<stdlib.h>
#define NUM 5
struct node
{
    int num;
    char *data;
};
struct node *hashinit()
{
    struct node *h=(struct node *)malloc(sizeof(struct node *));
    h->data=(char*)malloc(sizeof(char)*NUM); 
    h->num=0;
    for(int i=0;i<NUM;i++){
        h->data[i]=0;
    }
    return h;
}
int hash(char data)
{
    return data%NUM;
}
void hashput(char data,struct node *h)
{
    int index=hash(data);
    if(h->data[index]==0){
        h->data[index]=data;
    }else{
        int count=1;
        while(h->data[index]!=0){
            index=hash(hash(data)+count);
            count++;
        }
        h->data[index]=data;
    }
}
int main()
{
    struct node *h=hashinit();
    hashput('A',h);
    hashput('F',h);
    printf("%c %c",h->data[0],h->data[1]);
}