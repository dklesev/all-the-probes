---
<!-- class: lead -->

# syscalls

---
<!-- class: content -->

##### How syscalls work

![](https://www.researchgate.net/profile/Wai-Kyi/publication/334531571/figure/fig1/AS:781892970352640@1563429219162/Basic-architecture-of-system-call-interface.ppm)

<see>See: https://www.researchgate.net/figure/Basic-architecture-of-system-call-interface_fig1_334531571</see>

---
<!-- class: content -->

##### Opening a file

<text-cool-blue>*(opening a file in go)*</text-cool-blue>

```go {0}
func readConfig(path string) (Config, error) {
	var config Config
	yamlFile, err := os.ReadFile(path)
	...
}

func main() {
	config, err := readConfig("config.yaml")
	...
}
```

---
<!-- class: content -->

##### Opening a file

<text-cool-blue>*(opening a file in go)*</text-cool-blue>

```go {3,8}
func readConfig(path string) (Config, error) {
	var config Config
	yamlFile, err := os.ReadFile(path)
	...
}

func main() {
	config, err := readConfig("config.yaml")
	...
}
```

---
<!-- class: content -->

##### Opening a file

<text-cool-blue>*(view invoked syscalls using strace)*</text-cool-blue>

```bash {0}
$ go build main.go && strace ./main
...
futex(0x4000053148, FUTEX_WAKE_PRIVATE, 1) = 1
mmap(NULL, 262144, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xfc6c4fdc0000
fcntl(1, F_GETFL)                       = 0x2 (flags O_RDWR)
fcntl(2, F_GETFL)                       = 0x2 (flags O_RDWR)
openat(AT_FDCWD, "config.yaml", O_RDONLY|O_CLOEXEC) = 3
futex(0x15afa0, FUTEX_WAKE_PRIVATE, 1)  = 1
futex(0x15aeb8, FUTEX_WAKE_PRIVATE, 1)  = 1
fcntl(3, F_GETFL)                       = 0x20000 (flags O_RDONLY|O_LARGEFILE)
```

<see>See: https://strace.io/</see>

---
<!-- class: content -->

##### Opening a file

<text-cool-blue>*(view invoked syscalls using strace)*</text-cool-blue>

```bash {7}
$ go build main.go && strace ./main
...
futex(0x4000053148, FUTEX_WAKE_PRIVATE, 1) = 1
mmap(NULL, 262144, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xfc6c4fdc0000
fcntl(1, F_GETFL)                       = 0x2 (flags O_RDWR)
fcntl(2, F_GETFL)                       = 0x2 (flags O_RDWR)
openat(AT_FDCWD, "config.yaml", O_RDONLY|O_CLOEXEC) = 3
futex(0x15afa0, FUTEX_WAKE_PRIVATE, 1)  = 1
futex(0x15aeb8, FUTEX_WAKE_PRIVATE, 1)  = 1
fcntl(3, F_GETFL)                       = 0x20000 (flags O_RDONLY|O_LARGEFILE)
```

<see>See: https://strace.io/</see>

