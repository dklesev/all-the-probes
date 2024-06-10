#include "vmlinux.h"
#include <bpf/bpf_helpers.h>

SEC("tracepoint/syscalls/sys_enter_openat")
int tracepoint__syscalls__sys_enter_openat(struct trace_event_raw_sys_enter *ctx) {
    
    const char *filename = (const char *)ctx->args[1];
    char target_filename[] = "config.yaml";
    char new_filename[] = "config2.yml";
    char current_filename[32];

    // Read the filename argument from userspace
    bpf_probe_read_str(current_filename, sizeof(current_filename), filename);

    // Prints a lot
    // bpf_printk("Original file: %s\n", filename);

    // Check if the filename is "./config.yaml"
    for (int i = 0; i < sizeof(target_filename); i++) {
        if (current_filename[i] != target_filename[i]) {
            return 0;
        }
    }

    // Override the filename with the new file
    bpf_probe_write_user((char*)ctx->args[1], &new_filename, sizeof(new_filename));

    return 0;
}

char _license[] SEC("license") = "GPL";