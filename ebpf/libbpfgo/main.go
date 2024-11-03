package main

import (
    "log"
    "os"
    "os/signal"
    "syscall"

    "github.com/cilium/ebpf/link"    // 导入 Cilium eBPF 链接库
    "github.com/cilium/ebpf/rlimit"  // 导入 Cilium eBPF 限制库
)

func main() {
    // 创建一个用于接收操作系统信号的通道
    stopper := make(chan os.Signal, 1)
    // 监听中断信号和终止信号，并将其发送到 stopper 通道
    signal.Notify(stopper, os.Interrupt, syscall.SIGTERM)

    // 允许当前进程锁定内存，以便为 eBPF 资源分配足够的内存
    if err := rlimit.RemoveMemlock(); err != nil {
        log.Fatal(err)  // 如果移除内存限制失败，记录错误并退出
    }

    // 加载预编译的 eBPF 程序和映射到内核中
    objs := bpfObjects{}
    if err := loadBpfObjects(&objs, nil); err != nil {
        log.Fatalf("loading objects: %s", err)  // 如果加载失败，记录错误并退出
    }
    defer objs.Close()  // 确保在程序结束时释放资源

    // 连接到名为 "sys_enter_execve" 的 tracepoint，进行系统调用的跟踪
    kp, err := link.Tracepoint("syscalls", "sys_enter_execve", objs.BpfProg, nil)
    if err != nil {
        log.Fatalf("opening tracepoint: %s", err)  // 如果连接失败，记录错误并退出
    }
    defer kp.Close()  // 确保在程序结束时关闭 tracepoint

    // 输出成功消息，提示用户使用命令查看 BPF 程序的输出
    log.Printf("Successfully started! Please run \"sudo cat /sys/kernel/debug/tracing/trace_pipe\" to see output of the BPF programs\n")

    // 等待操作系统信号，并在收到信号时关闭 perf reader，
    // 这将中断 rd.Read()，使程序退出
    <-stopper
    log.Println("Received signal, exiting program..")  // 打印退出消息
}
