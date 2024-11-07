package main

import (
	"fmt"
	"os"
	"time"
	bpf "github.com/iovisor/gobpf/bcc"
)

import "C"

const source string = `
int kprobe__do_sys_open(void *ctx) 
{ 
	bpf_trace_printk("Hello, World!\\n"); 
	return 0; 
}
`

func main() {
	m := bpf.NewModule(source, []string{})
	if m == nil {
		fmt.Println("Failed to create BPF module")
		os.Exit(1)
	}
	defer m.Close()

	kp, err := m.LoadKprobe("kprobe__do_sys_open")
	if err != nil {
		fmt.Printf("Failed to load kprobe: %s\n", err)
		os.Exit(1)
	}

	err = m.AttachKprobe("do_sys_open", kp, -1)
	if err != nil {
		fmt.Printf("Failed to attach kprobe to do_sys_open: %s\n", err)
		os.Exit(1)
	}
  
	for {
		fmt.Println("waiting...")
		time.Sleep(time.Second * 10)
	}
}
