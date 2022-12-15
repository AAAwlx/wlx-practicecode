#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct strbuf {
  int len;     //当前缓冲区（字符串）长度
  int alloc;   //当前缓冲区（字符串）容量
  char *buf;   //缓冲区（字符串）
};
void strbuf_init(struct strbuf *sb,size_t alloc)//初始化字符串
{
    sb->len=0;//此时没有字符串输入长度为0
    sb->alloc=alloc;
    sb->buf=(char *)malloc(alloc*sizeof(char *));
}
void strbuf_attach(struct strbuf *sb,char *str, size_t len, size_t alloc)//将字符串添加到结构体中	
{
    sb->len=len;
    sb->alloc=alloc;
    sb->buf=(char *)str;
}
void strbuf_release(struct strbuf *sb)
{
        free(sb->buf);
}
void strbuf_swap(struct strbuf *a, struct strbuf *b)
{
    int t;
    char *p;
    t=a->len;
    a->len=b->len;
    b->len=t;
    t=a->alloc;
    a->alloc=b->alloc;
    b->alloc=t;
    p=a->buf;
    a->buf=b->buf;
    b->buf=p;
}
char *strbuf_detach(struct strbuf *sb, size_t sz)
{
    char *d;
    d=(char *)malloc(sizeof(char *));
    d=sb->buf;
    sb->alloc=sz;
    return d;
}
int strbuf_cmp(const struct strbuf *f, const struct strbuf *s)
{ 
    if(f->alloc==s->alloc){
        return 1;
    }else{
        return 0;
    }
}
void strbuf_reset(struct strbuf *sb)
{
    int i;
    for(i=0;i<=sb->len;i++){
        sb->buf[i]='0';
    }
    sb->len=0;
}
int main()
{   
    struct strbuf sb;
    strbuf_init,(&sb,10);
    strbuf_attach(&sb,"xiyou",5, 10);
    struct strbuf a;
    struct strbuf b;  
    strbuf_release(&sb);
    strbuf_attach(&a,"hhh",3, 10);
    strbuf_attach(&b,"wwww",4, 10);
    strbuf_swap(&a,&b);
    char *d;
    d=strbuf_detach(&sb,9);
    printf("%s",d);
    const struct strbuf f;
    const struct strbuf s;
    int i;
    i=strbuf_cmp(&f,&s);
    strbuf_reset(&sb);
} 