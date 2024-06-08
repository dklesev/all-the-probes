#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

char LICENSE[] SEC("license") = "Dual BSD/GPL";

SEC("uprobe/process_record")
int BPF_UPROBE(process_record_probe, char *record)
{
    //char *record = (char *)PT_REGS_PARM1(ctx);

    char kbuf[32] = {};
    bpf_probe_read_user(&kbuf, sizeof(kbuf), record);

    bpf_printk("Original record: %s", kbuf);

    for (int i = 1; i < 32; i++) {
        if (kbuf[32 - i] == ' ') {
            kbuf[32 - i] = '\0';
            bpf_printk("This one ends with a space! Fixing record!");
            bpf_probe_write_user(record, kbuf, sizeof(kbuf));
            return 0;
        }
    }
    return 0;
}