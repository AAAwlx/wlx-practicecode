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
int command_a=0, command_l=0, command_r=0, command_i=0, command_s=0, command_T=0, command_R=0;
struct file
{
    char filename[256];
    struct stat STA;
};//存储文件的名字与其属性
int getcolor( char *filename )
{
    struct stat info;    //通过设置可以获取文件属性
    int foreground=0;
   lstat( filename,&info );//将文件输入获得赋值给info
    switch ( (info.st_mode & S_IFMT) ){
        case S_IFREG:               /*regular 普通文件 , 色*/
            {
                foreground = 37;
                    if((info.st_mode&S_IXOTH)||(info.st_mode&S_IXGRP)||(info.st_mode&S_IXUSR))
      {
            foreground = 32;
        }
            break;
            }
        case S_IFLNK:               /*symbolic link 链接文件 , 青蓝色*/
            foreground = 36;
            break;
        case S_IFSOCK:              /*紫红色*/
            foreground = 35;
            break;
        case S_IFDIR:               /*directory 目录文件 , 蓝色*/
        foreground = 34;
            break;
        case S_IFBLK:               /*block special 块设备文件 , 黄色*/
            foreground = 33;
            break;
        case S_IFCHR:               /*character special 字符设备文件 , 黄色*/
            foreground = 33;
            break;
    }
    return foreground;
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
//通过uid和gid找到用户名字和用户组名字    
char* UID(uid_t uid)
{  
    struct passwd* getpwuid(),* pw_ptr;  
    static char numstr[10];  
      
    if((pw_ptr = getpwuid(uid)) == NULL)  
    {  
        sprintf(numstr,"%d",uid);
        return numstr;
    }  
    else  
    {  
        return pw_ptr->pw_name;
    }  
}       
char* GID(gid_t gid)
{  
    struct group* getgrgid(),* grp_ptr;  
    static char numstr[10];  
      
    if(( grp_ptr = getgrgid(gid)) == NULL)  
    {  
        sprintf(numstr,"%d",gid);  
        return numstr;  
    }  
    else  
    {  
        return grp_ptr->gr_name;  
    }  
}  
void show_file(struct stat* STA)  
{
    char modestr[11];  //存放权限
    //权限
    MODE((int)STA->st_mode, modestr);
    //连到该文件的硬连接数目，刚建立的文件值为1
    printf(" %5d", (int) STA->st_nlink);
    //用户
    printf(" %5s", UID(STA->st_uid));
    //用户组
    printf(" %5s", GID(STA->st_gid));
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
void LS_r(struct file *FILE,int len)
{
    int i,j;
    for(i=0,j=len-1;i<j;i++,j--){
        struct file n = FILE[i];
		FILE[i] = FILE[j];
		FILE[j] = n;
    }
}

void list(char *pathname)
{
	DIR *dir=NULL;
	struct dirent *ptr;
    dir=opendir(pathname);  //返回目录流
    chdir(pathname);
	if(dir == NULL) //如果路径为空，返回错误
    {
        printf("error!cannot open the file\n");
        exit(-1);
    }
	struct stat statbuf;
	int i=0,j=0;
	struct file* f = malloc(sizeof(struct file)*100);
	struct file* temp = f;//记录初始位置
	while((ptr=readdir(dir))!=NULL){
		if(command_a==0){
			if(ptr->d_name[0]=='.'){
				continue;
			}
		}
		stat(ptr->d_name, &(f->STA));
		strcpy(f->filename,ptr->d_name);
		f++;
		j++;
	}
	f = temp;  //指向开始
    if(command_T== 1)
    {
        LS_T(f, j);
    }
    if(command_r== 1)
    {
        LS_r(f, j);
    }
	for(i=0;i<j;i++){
        if(command_i==1){
			LS_I(&(f+i)->STA);
		}
	    if(command_s==1){
			LS_S(&(f+i)->STA);
		}
		if(command_l==1){
            show_file(&(f+i)->STA);
            printf("\n");
		}
        int foreground=getcolor((f+i)->filename);
        printf("\033[%dm%-15s\033[0m",foreground,(f+i)->filename);
        if(i%5==0&&command_l==0){
            printf("\n");
        }
	}
    printf("\n");
    if(command_R == 1)  //-R递归
    {
        for(int i=0;i<j;i++)
        {
            if((f+i)->filename[0]=='.'&&(strlen((f+i)->filename)==1||strlen((f+i)->filename)==2)){
                continue ;
            }
            char name[256];
            strcpy(name,pathname);
            //printf("%d\n",strcmp((f+i)->filename,"."));
            if(S_ISDIR((f+i)->STA.st_mode)){
                if(name[strlen(name)]!='/'){
                strcat(name,"/");
                }
                strcat(name,(f+i)->filename);
                printf("%s:\n",name);
                list(name); 
            }
        }
        free(f);
    }
	closedir(dir);
}

int main(int argc,char** argv)
{
    int count=0;
    char pathname[256];
    if(argc>1){
        int j=0;
        while(count<argc){
            if(argv[count][0]=='-'){
                int len=strlen(argv[count]);
                int i;
                for(i=0;i<len;i++){
		            if(argv[count][i]=='a')
                    {
                        command_a=1;
                    }else if(argv[count][i]=='l')
                    {
                        command_l=1;
                    }else if(argv[count][i]=='R')
                    {
                        command_R=1;
                    }else if(argv[count][i]=='i')
                    {
                        command_i=1;
                    }else if(argv[count][i]=='s')
                    {
                        command_s=1;
                    }else if(argv[count][i]=='t')
                    {
                        command_T=1;
                    }else if(argv[count][i]=='r')
                    {
                        command_r=1;
                    }else if(argv[count][i]=='-')
                    {
                        continue;
                    }else{
                        printf("错误！\n");
                        return -1;
                    }
                }
                count++;
            }else{
                count++;
                continue ;
            }     
        }
        while(j<argc){
            if(argv[j][0]=='-'){
                j++;
                continue ;
            }else{
                if(argv[j][0]=='.'){
                    realpath(argv[j], pathname);
                }else{
                    strcpy(pathname,argv[j]);
                }
                if(chdir(pathname)==0){
                    printf("%s:\n",pathname);
                    list(pathname);
                }else{
                    j++;
                    continue;
                }
                j++;
            }
        }
        if(count==0){
            getcwd(pathname,sizeof(pathname));
            chdir(pathname);
            list(pathname);
        }
    }else{
       
            getcwd(pathname,sizeof(pathname));
            chdir(pathname);
            list(pathname);
        
    }
    return 0;    
}