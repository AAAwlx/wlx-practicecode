#include"strbuf.h"
//A
void strbuf_init(struct strbuf* sb, size_t alloc) {
    sb->len = 0;
    sb->alloc = alloc;
    if (alloc)
        sb->buf = (char*)malloc(sizeof(char) * alloc);
}
void strbuf_attach(struct strbuf *sb,  void *str, size_t len, size_t alloc)
{
    sb->alloc=alloc;
    sb->len=len;
    sb->buf=(char*)str;
    sb->buf[sb->len]='\0';
}
void strbuf_release(struct strbuf *sb)
{
    if(sb->alloc==0||sb==NULL)return;
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
char *strbuf_detach(struct strbuf *sb, size_t *sz)
{
    char *d;
    d=sb->buf;
    *sz=sb->alloc;
    return d;
}
int strbuf_cmp(const struct strbuf *first, const struct strbuf *second)
{ 
       if(first->len>second->len)
        return 1;
    else if(first->len<second->len)
        return -1;
    else
        return 0;
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
    if(sb->alloc-sb->len-1 > extra)
    return ;
    else 
    {
        sb->buf=(char *)realloc(sb->buf,(sb->alloc+extra)*sizeof(char));
        sb->alloc=(sb->alloc+extra);
    }
    return ;
}

void strbuf_add(struct strbuf *sb, const void *data, size_t len)
{
    strbuf_grow(sb,len+1);
    memcpy(sb->buf+sb->len,data,len);
    sb->len=sb->len+len;
    sb->buf[sb->len]='\0';
    return ;
}

void strbuf_addch(struct strbuf *sb, int c)
{
   strbuf_grow(sb,2);
    sb->buf[sb->len]=c;
    sb->len++; 
    sb->buf[sb->len]='\0';
    return ;
}

void strbuf_addstr(struct strbuf *sb, const char *s)
{
    int len =strlen(s);
    strbuf_grow(sb,len+1);
    memcpy(sb->buf+sb->len,s,len);
    sb->len=sb->len+len;
    sb->buf[sb->len]='\0';
}

void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2)
{
    strbuf_grow(sb,sb2->len+1);
    memcpy(sb->buf+sb->len,sb2->buf,sb2->len);
    sb->len+=sb2->len;
    sb->buf[sb->len]='\0';
    return ;
}
void strbuf_setlen(struct strbuf *sb, size_t len)
{
	sb->len=len;
	sb->buf[len]='\0';
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
    for(i=sb->len;i>=pos;i--){
        sb->buf[i+len]=sb->buf[i];
    }
    for(i=pos,j=0;i<pos+len;i++,j++){
        sb->buf[i]=((char *)data)[j];
    }
    sb->len+=len;
}
//c
void strbuf_ltrim(struct strbuf *sb)
{
    char *s=sb->buf;
    while(*s==' '||*s=='\t'){
        sb->len--;
        s++;
    }
    memmove(sb->buf,s,sb->len);//第一个参数为需要复制到的地址，第二个参数为开始复制的地址，第三个参数为复制字节的长度
    sb->buf[sb->len]='\0';//令结尾处为'\0'结束
}
void strbuf_rtrim(struct strbuf *sb)	
{
    while(sb->buf[sb->len-1]==' '||sb->buf[sb->len-1]=='\t'){
        sb->len--;
    }
    
}
void strbuf_remove(struct strbuf *sb, size_t pos, size_t len)
{
    memmove(sb->buf+pos,sb->buf+pos+len,sb->len-pos-len);
    sb->len=sb->len-len;
    sb->buf[sb->len]='\0';
}	
//d
ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint)
{
    FILE *fp;
    char a;
    if(((fp=fdopen(fd,"r"))==NULL)||(a=fgetc(fp))==EOF){//如果没有待读入的文件或该文件中没有内容，就直接返回当前len的大小
        return sb->len;     
    }else{
        sb->alloc+=(hint?hint:8192);
        sb->buf=(char*)realloc(sb->buf,sizeof(char)*(sb->alloc));//将字符串扩容至所需大小
        sb->buf[sb->len++]=a;
        while((a=fgetc(fp))!=EOF){//当未到文件结尾时将文件中的字符逐一读入并赋值给buf
            sb->buf[sb->len]=a;
            sb->len++;
        }
        sb->buf[sb->len]='\0';
        return sb->len;
    }
}
int strbuf_getline(struct strbuf *sb, FILE *fp)
{
    int cnt=0,i;
    while(1){
        if(((i=fgetc(fp))=='\n'||i==EOF)){
            break;
        }
        if(strbuf_avail(sb)>0){       
            strbuf_addch(sb,i); 
            cnt++;
        }else{
            strbuf_addch(sb,i);
            cnt++;
        }
    }
    sb->len=cnt;
    return 1;
}
struct strbuf **strbuf_split_buf(const char *str, size_t len, int terminator, int max)
{
    char q=(char)terminator;
    int count=0;
    struct strbuf** p=(struct strbuf**)malloc(sizeof(struct strbuf*));
    struct strbuf* j;
    char s[len+1];
    memcpy(s,str,len+1);
    for(int i=0;i<len;i++)
    {
        if(s[i]=='\0')
        {
            s[i]='@';
        }
    }
    char* r=strtok(s,&q);
    while(r!=NULL&&count<max)
    {
        int r_len=strlen(r);
        for(int i=0;i<r_len;i++)
        {
            if(r[i]=='@')
            {
                r[i]='\0';
            }
        }
        j=(struct strbuf*)malloc(sizeof(struct strbuf));
        strbuf_init(j,r_len+1);
        strbuf_add(j,r,r_len);
        p[count++]=j;
        p=(struct strbuf**)realloc(p,sizeof(struct strbuf*)*(count+1));
        r=strtok(NULL,&q);
    }
    p[count]=NULL;
    return p;
}

bool strbuf_begin_judge(char* target_str, const char* str, int strlen)
{
    int i;
    for(i=0;i<strlen;i++){
        if(str[i]=='\0'){
            break;
        }
        if(target_str[i]!=str[i]){
            return false;
        }
    }
    return true;

}
char* strbuf_get_mid_buf(char* target_buf, int begin, int end, int len)
{
    if(end<begin||target_buf==NULL){
        return NULL;
    }
    char *str;
    str=(char *)malloc(sizeof(char)*(end-begin+1));
    str=(char *)memcpy(str,target_buf+begin,end-begin);
    str[end-begin]='\0';
    return str;
}