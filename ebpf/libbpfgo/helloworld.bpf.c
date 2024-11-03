#include "/home/ylx/ebpf/examples/headers/common.h"
SEC("tracepoint/syscalls/sys_enter_execve")

int bpf_prog(void *ctx) {
  char msg[] = "Hello, World!";
  // 输出一行内核调试日志
  // 可以通过 / sys/kernel/debug/tracing/trace_pipe 查看到相关日志输出
  bpf_printk("invoke bpf_prog: %s\n", msg);
  return 0;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";