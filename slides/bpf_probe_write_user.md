--- 

<!-- class: lead -->

# bpf_probe_write_user

---

<!-- class: content -->

##### bpf_probe_write_user

<br>

```c {14-16}
long bpf_probe_write_user(void *dst, const void *src, u32 len)

      Description
              Attempt in a safe way to write len bytes from the
              buffer src to dst in memory. It only works for
              threads that are in user context, and dst must be a
              valid user space address.

              This helper should not be used to implement any
              kind of security mechanism because of TOC-TOU
              attacks, but rather to debug, divert, and
              manipulate execution of semi-cooperative processes.

              Keep in mind that this feature is meant for
              experiments, and it has a risk of crashing the
              system and running programs.  Therefore, when an
              eBPF program using this helper is attached, a
              warning including PID and process name is printed
              to kernel logs.
```

<br><see>See: https://man7.org/linux/man-pages/man7/bpf-helpers.7.html</see>

<style>
pre, pre[class*="language-"] {
  font-size: 0.6em;
}
</style>

---

##### The "buggy" func

<text-cool-blue>*(you can imagine the arg be out of your control)*</text-cool-blue>

```go {0}
func processRecord(record string) {
    // TODO: due to our upstream processing only the last character isn't allowed to be a space
    if record[len(record)-1:] == " " {
        fmt.Println("Error: Bad value encountered!")
        os.Exit(1)
    }
    // fmt.Println("Processing record...") // for debug
}
```

---

##### The "buggy" func

<text-cool-blue>*(you can imagine the arg be out of your control)*</text-cool-blue>

```go {3}
func processRecord(record string) {
    // TODO: due to our upstream processing only the last character isn't allowed to be a space
    if record[len(record)-1:] == " " {
        fmt.Println("Error: Bad value encountered!")
        os.Exit(1)
    }
    // fmt.Println("Processing record...") // for debug
}
```

---

##### Overriding the function arg

<text-cool-blue>*(using the uprobe we try to override the original arg value)*</text-cool-blue>

```c {0}
SEC("uprobe/process_record")
int BPF_UPROBE(process_record_probe, char *record)
{
    ...
    for (int i = 1; i < 32; i++) {
        if (kbuf[32 - i] == ' ') {
            kbuf[32 - i] = '\0';
            bpf_printk("This one ends with a space! Fixing record!");
            bpf_probe_write_user(record, kbuf, sizeof(kbuf));
            return 0;
        }
    }
    ...
```

---

##### Overriding the function arg

<text-cool-blue>*(using the uprobe we try to override the original arg value)*</text-cool-blue>

```c {6-9}
SEC("uprobe/process_record")
int BPF_UPROBE(process_record_probe, char *record)
{
    ...
    for (int i = 1; i < 32; i++) {
        if (kbuf[32 - i] == ' ') {
            kbuf[32 - i] = '\0';
            bpf_printk("This one ends with a space! Fixing record!");
            bpf_probe_write_user(record, kbuf, sizeof(kbuf));
            return 0;
        }
    }
    ...
```