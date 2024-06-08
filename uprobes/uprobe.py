from bcc import BPF

# Load eBPF program
b = BPF(text="""
#include <uapi/linux/ptrace.h>

int process_record_probe(struct pt_regs *ctx)
{
    char *record = (char *)PT_REGS_PARM1(ctx);
    char kbuf[32] = {};
    bpf_probe_read_user(&kbuf, sizeof(kbuf), record);

    bpf_trace_printk("Original record: %s", kbuf);

    for (int i = 1; i < 32; i++) {
        if (kbuf[32 - i] == ' ') {
            kbuf[32 - i] = '\\0';
            bpf_trace_printk("This one ends with a space! Fixing record!");
            bpf_probe_write_user(record, kbuf, sizeof(kbuf));
            return 0;
        }
    }
    return 0;
}
""")

# Attach eBPF to a uprobe
binary_path = "/home/ubuntu/all-the-probes/uprobes/output/stripped"
#b.attach_uprobe(name=binary_path, sym="main.processRecord", fn_name="process_record_probe")
b.attach_uprobe(name=binary_path, addr=0x000000000009ed00, fn_name='process_record_probe')

print("eBPF program loaded and attached. Press Ctrl+C to exit.")
try:
    while True:
        pass
except KeyboardInterrupt:
    print("Detaching...")
