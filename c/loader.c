#include <linux/bpf.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <linux/perf_event.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>        // 包含 read 和 close 的声明
#include <sys/ioctl.h>     // 包含 ioctl 的声明
//类型转换, 减少warning, 也可以不要
#define ptr_to_u64(x) ((uint64_t)x)

//对于系统调用的包装, __NR_bpf就是bpf对应的系统调用号, 一切BPF相关操作都通过这个系统调用与内核交互
int bpf(enum bpf_cmd cmd, union bpf_attr *attr, unsigned int size)
{
    return syscall(__NR_bpf, cmd, attr, size);
}

//对于perf_event_open系统调用的包装, libc里面不提供, 要自己定义
static int perf_event_open(struct perf_event_attr *evt_attr, pid_t pid, int cpu, int group_fd, unsigned long flags)
{
    int ret;
    ret = syscall(__NR_perf_event_open, evt_attr, pid, cpu, group_fd, flags);
    return ret;
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
        .license = ptr_to_u64(license),    //被加载程序的许可证
        .log_buf = ptr_to_u64(bpf_log_buf),    //log输出缓冲区
        .log_size = LOG_BUF_SIZE,    //log缓冲区大小
        .log_level = 2,    //log等级
    };

    return bpf(BPF_PROG_LOAD, &attr, sizeof(attr));
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

    //把BPF程序加载进入内核, 注意这里程序类型一定要是BPF_PROG_TYPE_TRACEPOINT, 表示BPF程序用于内核中预定义的追踪点
    int prog_fd = bpf_prog_load(BPF_PROG_TYPE_TRACEPOINT, bpf_prog, text_len/sizeof(bpf_prog[0]), "GPL");
    printf("%s\n", bpf_log_buf);
    if(prog_fd<0){
        perror("BPF load prog");
        exit(-1);
    }
    printf("prog_fd: %d\n", prog_fd);

    //设置一个perf事件属性的对象
    struct perf_event_attr attr = {};
    attr.type = PERF_TYPE_TRACEPOINT;    //跟踪点类型
    attr.sample_type = PERF_SAMPLE_RAW;    //记录其他数据, 通常由跟踪点事件返回
    attr.sample_period = 1;    //每次事件发送都进行取样
    attr.wakeup_events = 1;    //每次取样都唤醒
    attr.config = 806;  // 观测进入execve的事件, 来自于: /sys/kernel/debug/tracing/events/syscalls/sys_enter_execve/id

    //开启一个事件观测, 跟踪所有进程, group_fd为-1表示不启用事件组
    int efd = perf_event_open(&attr, -1/*pid*/, 0/*cpu*/, -1/*group_fd*/, 0);
    if(efd<0){
        perror("perf event open error");
        exit(-1);
    }
    printf("efd: %d\n", efd);

    ioctl(efd, PERF_EVENT_IOC_RESET, 0);        //重置事件观测
    ioctl(efd, PERF_EVENT_IOC_ENABLE, 0);        //启动事件观测
    if(ioctl(efd, PERF_EVENT_IOC_SET_BPF, prog_fd)<0){    //把BPF程序附着到此事件上 
        perror("ioctl event set bpf error");
        exit(-1);
    }

    //程序不能立即退出, 不然BPF程序会被卸载
    getchar();

}