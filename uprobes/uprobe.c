#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <bpf/libbpf.h>
#include "uprobe.skel.h"

static int libbpf_print_fn(enum libbpf_print_level level, const char *format, va_list args)
{
	return vfprintf(stderr, format, args);
}

int main(int argc, char **argv) {
    struct uprobe_bpf *skel;
    int err;

    libbpf_set_print(libbpf_print_fn);

    skel = uprobe_bpf__open_and_load();
    if (!skel) {
        fprintf(stderr, "Failed to open and load BPF skeleton\n");
        return 1;
    }

    LIBBPF_OPTS(bpf_uprobe_opts, uprobe_opts, .func_name = "main.processRecord");

    skel->links.process_record_probe = bpf_program__attach_uprobe_opts(
        skel->progs.process_record_probe, -1, "/home/ubuntu/all-the-probes/uprobes/output/main", 0, &uprobe_opts
    );

    if (!skel->links.process_record_probe) {
        err = -errno;
        fprintf(stderr, "Failed to attach uprobe: %d\n", err);
        goto cleanup;
    }

    printf("Successfully started! Please run `sudo cat /sys/kernel/debug/tracing/trace_pipe` "
           "to see output of the BPF programs.\n");


    for (;;) {
	fprintf(stderr, ".");
        sleep(1);
    }

cleanup:
    uprobe_bpf__destroy(skel);
    return -err;
}