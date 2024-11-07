package main

import (
        "fmt"
        "time"

        bpf "github.com/aquasecurity/libbpfgo"
)

func main() {
    fmt.Println("aaa...")
        bpfModule, err := bpf.NewModuleFromFile("execve_bpf.o")
        if err != nil {
                panic(err)
        }
        defer bpfModule.Close()
        if err := bpfModule.BPFLoadObject(); err != nil {
                panic(err)
        }
        prog, err := bpfModule.GetProgram("kprobe__do_sys_openat2")
        if err != nil {
                panic(err)
        }
        if _, err := prog.AttachKprobe("do_sys_openat2"); err != nil {
                panic(err)
        }
        
        for {
                fmt.Println("Waiting...")
                time.Sleep(10 * time.Second)
        }
}