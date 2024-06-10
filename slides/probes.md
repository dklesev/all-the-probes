---

<!-- class: lead -->

# probes

---

<!-- class: content -->

##### probes

![](https://www.grant.pizza/weaver/uprobe-ebpf.png)

<see>See: https://www.grant.pizza/blog/tracing-go-functions-with-ebpf-part-1/</see>

---

<!-- class: lead -->

# tracepoints

---

<!-- class: content -->

##### tracepoint definition

```c {0}
#undef TRACE_SYSTEM
#define TRACE_SYSTEM subsys

#if !defined(_TRACE_SUBSYS_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_SUBSYS_H

#include <linux/tracepoint.h>

DECLARE_TRACE(subsys_eventname,
        TP_PROTO(int firstarg, struct task_struct *p),
        TP_ARGS(firstarg, p));

#endif /* _TRACE_SUBSYS_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
```

<see>See: https://docs.kernel.org/trace/tracepoints.html</see>

---

<!-- class: content -->

##### tracepoint usage

```c {0}
#include <trace/events/subsys.h>

#define CREATE_TRACE_POINTS
DEFINE_TRACE(subsys_eventname);

void somefct(void)
{
        ...
        trace_subsys_eventname(arg, task);
        ...
}
```

<see>See: https://docs.kernel.org/trace/tracepoints.html</see>

