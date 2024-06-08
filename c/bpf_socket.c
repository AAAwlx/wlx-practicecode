#include <stdio.h>
#include <stdlib.h>  //为了exit()函数
#include <stdint.h>    //为了uint64_t等标准类型的定义
#include <string.h>
#include <errno.h>    //为了错误处理
#include <linux/bpf.h>    //位于/usr/include/linux/bpf.h, 包含BPF系统调用的一些常量, 以及一些结构体的定义
#include <sys/syscall.h>    //为了syscall()
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

//类型转换, 减少warning, 也可以不要
#define ptr_to_u64(x) ((uint64_t)x)

//对于系统调用的包装, __NR_bpf就是bpf对应的系统调用号, 一切BPF相关操作都通过这个系统调用与内核交互
int bpf(enum bpf_cmd cmd, union bpf_attr *attr, unsigned int size)
{
    return syscall(__NR_bpf, cmd, attr, size);
}

//用于保存BPF验证器的输出日志
#define LOG_BUF_SIZE 0x1000
char bpf_log_buf[LOG_BUF_SIZE];

//通过系统调用, 向内核加载一段BPF指令
int bpf_prog_load(enum bpf_prog_type type, const struct bpf_insn* insns, int insn_cnt, const char* license)
{
    union bpf_attr attr = {
        .prog_type = type,        //程序类型
        .insns = ptr_to_u64(insns),    //指向指令数组的指针
        .insn_cnt = insn_cnt,    //有多少条指令
        .license = ptr_to_u64(license),    //指向整数字符串的指针
        .log_buf = ptr_to_u64(bpf_log_buf),    //log输出缓冲区
        .log_size = LOG_BUF_SIZE,    //log缓冲区大小
        .log_level = 2,    //log等级
    };

    return bpf(BPF_PROG_LOAD, &attr, sizeof(attr));
}

//开启一个socket
int get_listen_socket(char *ip, int port){
    //获取一个TCP类型的socket
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 

    //设置地址对象, 采用IPv4
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(port);

    //把socket绑定的指定地址
    bind(sock, (struct sockaddr *)(&serv_addr), sizeof(serv_addr));

    //socket进入监听模式
    listen(sock, 20);
    return sock;
}

//保存BPF程序
struct bpf_insn bpf_prog[0x100];

int main(int argc, char **argv){
    //先从文件中读入BPF指令
    int text_len = atoi(argv[2]);
    int file = open(argv[1], O_RDONLY);
    if(read(file, (void *)bpf_prog, text_len)<0){
        perror("read prog fail");
        exit(-1);
    }
    close(file);

    //把BPF程序加载进入内核, 注意这里程序类型一定要是BPF_PROG_TYPE_SOCKET_FILTER, 表示BPF程序用于socket
    int prog_fd = bpf_prog_load(BPF_PROG_TYPE_SOCKET_FILTER, bpf_prog, text_len/sizeof(bpf_prog[0]), "GPL");
    printf("%s\n", bpf_log_buf);
    if(prog_fd<0){
        perror("BPF load prog");
        exit(-1);
    }
    printf("prog_fd: %d\n", prog_fd);

    //打开一个socket进入监听状态
    int sock = get_listen_socket("0.0.0.0", 9527);
    printf("socket: %d\n", sock);

    //把已经加载的BPF程序附加到socket上, 这样当数据到来时这个BPF程序就会被调用
    if(setsockopt(sock, SOL_SOCKET, SO_ATTACH_BPF, &prog_fd, sizeof(prog_fd))<0){
        perror("set socket error");
        exit(-1);
    }

    //调用accept()等待链接到来
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(sock, (struct sockaddr *)(&clnt_addr), &clnt_addr_size);
}