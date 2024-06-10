---
<!-- class: lead -->

# examples

---
<!-- class: content -->

##### Some example code

```go {0}
func processRecord(record string) {
    // TODO: due to our upstream processing only the last character isn't allowed to be a space
    if record[len(record)-1:] == " " {
        fmt.Println("Error: Bad value encountered!")
        os.Exit(1)
    }
    // fmt.Println("Processing record...") // for debug
}

func main() {
    data := flag.String("data", "good", "what data to process")
    ...
    file, err := os.Open(*data + ".csv")
    ...
    for {
        record, err := csvReader.Read()
        ...
        processRecord(record[1])
    }
    fmt.Println("Data successfully processed!")
}
```

---
<!-- class: content -->

##### Some example code

```go {2-5,7,18,20}
func processRecord(record string) {
    // TODO: due to our upstream processing only the last character isn't allowed to be a space
    if record[len(record)-1:] == " " {
        fmt.Println("Error: Bad value encountered!")
        os.Exit(1)
    }
    // fmt.Println("Processing record...") // for debug
}

func main() {
    data := flag.String("data", "good", "what data to process")
    ...
    file, err := os.Open(*data + ".csv")
    ...
    for {
        record, err := csvReader.Read()
        ...
        processRecord(record[1])
    }
    fmt.Println("Data successfully processed!")
}
```

---
<!-- class: content -->

##### Simple `uprobe` example

<text-cool-blue>*(just print the value passed to the function)*</text-cool-blue>

```c {0}
SEC("uprobe/process_record")
int BPF_UPROBE(process_record_probe, char *record)
{
    char kbuf[32] = {};
    bpf_probe_read_user(&kbuf, sizeof(kbuf), record);

    bpf_printk("Original record: %s\n", kbuf);
    return 0;
}
```

---
<!-- class: content -->

##### Simple `uprobe` example

<text-cool-blue>*(just print the value passed to the function)*</text-cool-blue>

```c {1-2,5,7}
SEC("uprobe/process_record")
int BPF_UPROBE(process_record_probe, char *record)
{
    char kbuf[32] = {};
    bpf_probe_read_user(&kbuf, sizeof(kbuf), record);

    bpf_printk("Original record: %s\n", kbuf);
    return 0;
}
```

<style>
pre, pre[class*="language-"] {
  color: white;
}
.highlighted-line {
  background-color: #FFE100;
  display: block;
}
</style>

---
<!-- class: content -->

##### Alternative `bpftrace` example

<text-cool-blue>*(for go there are **s**args)*</text-cool-blue>

```c {0}
uprobe:/home/ubuntu/ebpf/main:"main.processRecord"
{
    printf("Processing record: %s\n", str(sarg1, 8));
}
```
---
<!-- class: content -->

##### opensnoop

```c {0}
...
tracepoint:syscalls:sys_enter_open,
tracepoint:syscalls:sys_enter_openat
{
	@filename[tid] = args.filename;
}

tracepoint:syscalls:sys_exit_open,
tracepoint:syscalls:sys_exit_openat
/@filename[tid]/
{
	$ret = args.ret;
	$fd = $ret >= 0 ? $ret : -1;
	$errno = $ret >= 0 ? 0 : - $ret;

	printf("%-6d %-16s %4d %3d %s\n", pid, comm, $fd, $errno,
	    str(@filename[tid]));
	delete(@filename[tid]);
}
...
```

<see>See: https://github.com/bpftrace/bpftrace/blob/master/tools/opensnoop.bt</see>

---
<!-- class: content -->

##### opensnoop

```c {2-3,5,8-10}
...
tracepoint:syscalls:sys_enter_open,
tracepoint:syscalls:sys_enter_openat
{
	@filename[tid] = args.filename;
}

tracepoint:syscalls:sys_exit_open,
tracepoint:syscalls:sys_exit_openat
/@filename[tid]/
{
	$ret = args.ret;
	$fd = $ret >= 0 ? $ret : -1;
	$errno = $ret >= 0 ? 0 : - $ret;

	printf("%-6d %-16s %4d %3d %s\n", pid, comm, $fd, $errno,
	    str(@filename[tid]));
	delete(@filename[tid]);
}
...
```

<see>See: https://github.com/bpftrace/bpftrace/blob/master/tools/opensnoop.bt</see>

---
<!-- class: content -->

##### opensnoop

<text-cool-blue>*(using cat opensnoop.bt in another terminal)*</text-cool-blue>

```bash {0}
$ sudo bpftrace opensnoop.bt
Attaching 4 probes...
Tracing open syscalls... Hit Ctrl-C to end.
PID    COMM               FD ERR PATH
9284   bash                3   0 /dev/null
9284   bash                3   0 /dev/null
25540  bash                3   0 .
9284   bash                3   0 /dev/null
25541  cat                 3   0 /etc/ld.so.cache
25541  cat                 3   0 /lib/aarch64-linux-gnu/libc.so.6
...
25541  cat                 3   0 /usr/lib/locale/C.utf8/LC_CTYPE
25541  cat                 3   0 opensnoop.bt
```

---
<!-- class: content -->

##### opensnoop

<text-cool-blue>*(using cat opensnoop.bt in another terminal)*</text-cool-blue>

```bash {13}
$ sudo bpftrace opensnoop.bt
Attaching 4 probes...
Tracing open syscalls... Hit Ctrl-C to end.
PID    COMM               FD ERR PATH
9284   bash                3   0 /dev/null
9284   bash                3   0 /dev/null
25540  bash                3   0 .
9284   bash                3   0 /dev/null
25541  cat                 3   0 /etc/ld.so.cache
25541  cat                 3   0 /lib/aarch64-linux-gnu/libc.so.6
...
25541  cat                 3   0 /usr/lib/locale/C.utf8/LC_CTYPE
25541  cat                 3   0 opensnoop.bt
```

