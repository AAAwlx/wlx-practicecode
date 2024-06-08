#include <linux/bpf.h>

static int (*bpf_trace_printk)(const char *fmt, int fmt_size, ...) = (void *) BPF_FUNC_trace_printk;

unsigned long prog(void){
    char fmt[]="Get";
    bpf_trace_printk(fmt, sizeof(fmt));
    return 0;
}