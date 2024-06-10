---

<!-- class: lead-->

![](https://ebpf.foundation/wp-content/uploads/sites/9/2023/03/ebpf_logo_color_on_white-2-300x108.png)
*(recap)*

---

<!-- class: content -->

##### eBPF 

![height:15em](https://www.brendangregg.com/eBPF/linux_ebpf_support.png)

<br>

<see>See: https://www.brendangregg.com/ebpf.html</see>

---


<!-- class: content -->

##### What's Tracing

<text-cool-blue>*(proven method for tracing)*</text-cool-blue>

```c {0}
void myfunc(int type) 
{
	if (type > 20) {
		/* do some things */
		printf ("I like it goes here!\n"); 
	
	} else if (type < 100) { 
		/* do other things */
		printf ("But it goes here!\n");
	} else {
		/* error handling */
		printf ("Oh! I hate it's here! Wrong type is %d\n", type);
	｝
｝
```

<see>See: https://de.slideshare.net/vh21/linux-kernel-tracing</see>

