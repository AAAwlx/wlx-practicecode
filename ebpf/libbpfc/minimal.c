#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h> // rlimit使用
#include <bpf/libbpf.h>
#include "minimal.skel.h" // 这就是上一步生成的skeleton，minimal的“框架” 

int main(int argc, char **argv)
{
        struct minimal_bpf *skel; // bpftool生成到skel文件中，格式都是xxx_bpf。
        int err;

		struct rlimit rlim = {
        	.rlim_cur = 512UL << 20,
        	.rlim_max = 512UL << 20,
    	};
		// bpf程序需要加载到lock memory中，因此需要将本进程的lock mem配大些
    	if (setrlimit(RLIMIT_MEMLOCK, &rlim)) {
        	fprintf(stderr, "set rlimit error!\n");
        	return 1;
    	}
        // 第一步，打开bpf文件，返回指向xxx_bpf的指针（在.skel中定义）
        skel = minimal_bpf__open();
        if (!skel) {
                fprintf(stderr, "Failed to open BPF skeleton\n");
                return 1;
        }

       // 第二步，加载及校验bpf程序
        err = minimal_bpf__load(skel);
        if (err) {
                fprintf(stderr, "Failed to load and verify BPF skeleton\n");
                goto cleanup;
        }

        // 第三步，附加到指定的hook点
        err = minimal_bpf__attach(skel);
        if (err) {
                fprintf(stderr, "Failed to attach BPF skeleton\n");
                goto cleanup;
        }

        printf("Successfully started! Please run `sudo cat /sys/kernel/debug/tracing/trace_pipe` "
               "to see output of the BPF programs.\n");

        for (;;) {
                /* trigger our BPF program */
                fprintf(stderr, ".");
                sleep(1);
        }
cleanup:
        minimal_bpf__destroy(skel);
        return -err;
}
