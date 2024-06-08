OUTPUT := ./output
CC := clang
CFLAGS := -O2 -g -target bpf -I$(OUTPUT) -I/usr/include -I/usr/src/linux-headers-$(shell uname -r)/include -D __TARGET_ARCH_arm64 -D__BPF_TRACING__
SRC := ./uprobe.bpf.c
OBJ := $(OUTPUT)/uprobe.bpf.o
SKEL := $(OUTPUT)/uprobe.skel.h
VMLINUX_H := $(OUTPUT)/vmlinux.h

all: build_c build_ebpf build_go

$(VMLINUX_H):
	bpftool btf dump file /sys/kernel/btf/vmlinux format c > $(VMLINUX_H)

$(OBJ): $(SRC) $(VMLINUX_H)
	$(CC) $(CFLAGS) -c $< -o $@ || (echo "Error building eBPF program"; exit 1)

$(SKEL): $(OBJ)
	bpftool gen skeleton $(OBJ) > $(SKEL)

build_go:
	go build -o $(OUTPUT)/main main.go

build_random:
	go build -o $(OUTPUT)/random random.go

build_stripped:
	go build -ldflags "-s -w" -o $(OUTPUT)/stripped main.go

build_ebpf: $(VMLINUX_H) $(OBJ)

build_c: $(SKEL)
	$(CC) -g -Wall -I$(OUTPUT) -c uprobe.c -o $(OUTPUT)/uprobe.o
	$(CC) $(OUTPUT)/uprobe.o -L. -lbpf -lelf -lz -lrt -ldl -lpthread -lm -o $(OUTPUT)/uprobe
	chmod +x $(OUTPUT)/uprobe

clean:
	rm -f $(OBJ) 

.PHONY: all build_ebpf build_go clean