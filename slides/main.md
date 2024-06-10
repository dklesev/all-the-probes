---
marp: true
theme: ebpf
footer: <p>04.06.2024</p><p>eBPF Vienna</p><p></p>
paginate: true

---

<!-- class: cover -->
# eBPF pls fix my bugs!

<text-gray>using *probes* and *bpf_probe_write_user*</text-gray>

![logo](https://ebpf.foundation/wp-content/uploads/sites/9/2023/03/ebpf_logo_color_on_white-2-300x108.png)
<font-vienna>VIENNA</font-vienna>

!!!include(ebpf.md)!!!

<!-- include(syscalls.md)!!! -->

!!!include(probes.md)!!!
!!!include(examples.md)!!!
!!!include(bpf_probe_write_user.md)!!!

---

<!-- class: lead -->

# DEMO

---

<!-- class: lead -->

# Thank You!

---

<!-- class: content -->

##### References

- https://eunomia.dev
- https://www.brendangregg.com
- https://embracethered.com/blog/posts/2021/offensive-bpf-libbpf-bpf_probe_write_user/
- https://de.slideshare.net/vh21/linux-kernel-tracing
- https://docs.kernel.org/trace/tracepoints.html
- https://chrisarges.net/posts/2018-10-04-tracing-in-linux/
- https://elixir.bootlin.com/linux/latest/source/fs/open.c#L1430
- https://elixir.bootlin.com/linux/latest/source/include/linux/syscalls.h#L144