#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<dirent.h>
#include<glob.h>
#include<stdlib.h>
#include<stdbool.h>
#define BULE 34
#define GREEN 32//控制字符颜色
struct file
{
    char filename[256];
    struct stat STA;
};//存储文件的名字与其属性
void COLOR(int color)
{
    printf("\033[%dm",color);
}
void LS_I(struct stat *STA)
{
    printf("%ld ", STA->st_ino);
}
void LS_S(struct stat *STA)
{
    printf("%ld ",( long )STA->st_size);
}

void MODE(int mode, char str[])
{  
    strcpy(str, "----------");  //初始化全为---------- 
      
    if(S_ISDIR(mode))   //是否为目录
    {  
        str[0] = 'd';  
    }  
      
    if(S_ISCHR(mode))  //是否为字符设置
    {  
        str[0] = 'c';  
    }  
      
    if(S_ISBLK(mode))  //是否为块设备
    {  
        str[0] = 'b';  
    }
    if((mode & S_IRUSR))  
    {  
        str[1] = 'r';  
    }  
    if((mode & S_IWUSR))  
    {  
        str[2] = 'w';  
    }
    if((mode & S_IXUSR))  
    {  
        str[3] = 'x';  
    }  
    if((mode & S_IRGRP))  
    {  
        str[4] = 'r';  
    }  
    if((mode & S_IWGRP))  
    {  
        str[5] = 'w';  
    }
    if((mode & S_IXGRP))  
    {  
        str[6] = 'x';  
    }  
    if((mode & S_IROTH))  
    {  
        str[7] = 'r';  
    }  
    if((mode & S_IWOTH))  
    {  
        str[8] = 'w';  
    }  
    if((mode & S_IXOTH))  
    {  
        str[9] = 'x';  
    }
 
    printf("%s ",str);
} 
void show_file(struct stat* STA)  
{
    char modestr[11];  //存放权限
    //权限
    MODE((int)STA->st_mode, modestr);
    //连到该文件的硬连接数目，刚建立的文件值为1
    printf(" %5d", (int) STA->st_nlink);
    //用户
    printf(" %5d", UID(STA->st_uid));
    //用户组
    printf(" %5d", GID(STA->st_gid));
    //文件大小
    printf(" %5ld", (long) STA->st_size);
    //ctime:最后一次改变文件内容或目录内容的时间
    char buf_time[32];
    strcpy(buf_time, ctime(&(STA->st_mtime)));
    buf_time[strlen(buf_time) - 1] = '\0';
    printf(" %5s",buf_time);
    //文件名字
    //printf(" %20s\n", filename);
}
void LS_T(struct file *FILE,int len)
{
    for(int i=1;i<=len-1;i++)
    {
 
        for(int j=1;j<len-i;j++)
        {
 
            if(FILE[i].STA.st_mtime<FILE[j].STA.st_mtime)//char* a; a-> = (*a)
            {
				struct file n = FILE[i];
				FILE[i] = FILE[j];
				FILE[j] = n;
            }
        }
    }
}
void list(int *command,int size)
{
	DIR *dir=NULL;
	struct dirent *ptr;
	char pathname[256];
	getcwd(pathname,sizeof(pathname));  //获取当前路径
    dir=opendir(pathname);  //返回目录流
	if(dir == NULL) //如果路径为空，返回错误
    {
        printf("error!cannot open the file\n");
        exit(-1);
    }
	struct stat statbuf;
	int s_buf;
	int i=0,j=0;
	struct file* f = malloc(sizeof(struct file)*100);
	struct file* temp = f;//记录初始位置
	while(ptr=readdir(dir)!=NULL){
		if(command[0]==0){
			if(ptr->d_name[0]=='.'){
				continue;
			}
		}
		s_buf=stat(ptr->d_name, &(f->STA));
		strcpy(f->filename,ptr->d_name);
		f++;
		j++;
	}
	f = temp;  //指向开始
    if(command[5] == true)
    {
        LS_T(f, j);
    }
	for(i=0;i<j;i++){
		if(command[4]==1){
			LS_S(&(f+i)->STA);
		}
		if(command[3]==1){
			LS_I(&(f+i)->STA);
		}
		if(command[1]==1){
			printf("\n");
            show_file(&(f+i)->STA);
		}
		//打印名称
		if(S_ISDIR(f->STA.st_mode))
        {
            //目录
            COLOR(BULE);
            printf("%5s",f->filename);
        }else if(f->STA.st_mode & S_IXGRP)
        {
            //可执行文件（位运算？）
            printf("....");
            COLOR(GREEN);
            printf("%5s",(f+i)->filename);
        }else if(S_ISREG(f->STA.st_mode))//普通文件
        {
            printf("......................");
            printf("   %5s",(f+i)->filename);
        }
        if(i % 5 ==0 && command[1] != true)
        {
            printf("\n");
        }
	}
    if(command[2] == true)  //-R递归
    {
        printf("\n");
        for(int i=0;i<j;i++)
        {
            printf("%s:\n",(f+i)->filename);
            list(&(command[1]),3);
        }
    }
	closedir(dir);
}

int main(int argc,char* argv[])
{
	int i;
	int len=strlen(argv[1]);//得到命令的长度
	int command[10]={0};
	//从0～5分别为a l r i s t
	for(i=0;i<len;i++){
		if(argv[1][i]=='a')
        {
            command[0]++;
        }else if(argv[1][i]=='l')
        {
             command[1]++;
        }else if(argv[1][i]=='R')
        {
            command[2]++;
        }else if(argv[1][i]=='i')
        {
            command[3]++;
        }else if(argv[1][i]=='s')
        {
            command[4]++;
        }else if(argv[1][i]=='t')
        {
            command[5]++;
        }else{
            printf("错误！\n");
            return -1;
        }
	}
	for(i=0;i<6;i++){
		if(command[i]!=0){
			command[i]=1;
		}
	}
	list(command,6);
	return 0;
}
