#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct strbuf {
  int len;     //当前缓冲区（字符串）长度
  int alloc;   //当前缓冲区（字符串）容量
  char *buf;   //缓冲区（字符串）
};
//A
void strbuf_init(struct strbuf *sb,size_t alloc)//初始化字符串
{
    sb->buf=(char *)malloc(alloc*sizeof(char *));
    sb->len=0;//此时没有字符串输入长度为0
    sb->alloc=alloc;
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
    sb->buf=NULL;//避免sb->buf被释放后变为野指针
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
    for(i=0;i<sb->len;i++){
        sb->buf[i]='\0';
    }
    sb->len=0;
}
//B
void strbuf_grow(struct strbuf *sb, size_t extra)
{
    sb->buf=(char*)realloc(sb->buf,extra);
    sb->alloc=sb->len+extra;
}
void strbuf_add(struct strbuf *sb, const void *data, size_t len)
{
    if(len==0){
        return;
    }
    if(sb->len+len>=sb->alloc){
        strbuf_grow(sb,len+1);
    }
    memcpy(sb->buf+sb->len,data,len);
    sb->buf[sb->len+len]='\0';
    sb->len+=len;
}
void strbuf_addch(struct strbuf *sb, int c)
{
    if(sb->len+1>sb->alloc){
        strbuf_grow(sb,1);
    }
    memcpy(sb->buf+sb->len,&c,4);
}
void strbuf_addstr(struct strbuf *sb, const char *s)
{
	strbuf_add(sb,s,strlen(s));
}
void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2)
{
	strbuf_addstr(sb,sb2->buf);
}
void strbuf_setlen(struct strbuf *sb, size_t len)
{

	sb->len=len;
	sb->buf[len+1]='\0';
}
size_t strbuf_avail(const struct strbuf *sb)
{
    int t;
	if(sb->alloc==0){
        t=0;
    }else{
        t=sb->alloc-sb->len-1;
    }
    return t;
}
void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len)
{
    int i,j;
    if(sb->len+pos+len+1>sb->alloc){
        strbuf_grow(sb,pos+sb->len+1);
    }
    for(i=pos,j=pos+len;i<pos+len;i++,j++){
        sb->buf[j]=sb->buf[i];
    }
    for(i=pos,j=0;i<pos+len;i++,j++){
        sb->buf[i]=((char *)data)[j];
    }
}
int main()
{   
    struct strbuf sb;
    strbuf_init(&sb,10);
    strbuf_attach(&sb,"xiyou",5, 10);
    struct strbuf a;
    struct strbuf b;  
    //strbuf_release(&sb);
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
    strbuf_grow(&sb,6);
    strbuf_add(&sb,"welcome",5);
	strbuf_addch(&sb,'c');
	strbuf_addstr(&sb,"you");
	struct strbuf sb2;
	strbuf_attach(&sb2,"xxx",3, 10);
	strbuf_setlen(&sb2,4);
    int t;
    t=strbuf_avail(&sb);
    strbuf_insert(&sb,2,"lll",3);
} 
