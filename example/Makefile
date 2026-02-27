CC := cc
NOSTDFLAGS := -nostdlib -fno-unwind-tables -fno-asynchronous-unwind-tables -Wa,--noexecstack -fno-builtin -fno-stack-protector # -fdata-sections + -Wl,-dead_strip / -Wl,--gc-sections
CXXFLAGS := -Wall -Wextra -Wshadow -std=c++20 -pedantic -fno-exceptions -fno-rtti $(NOSTDFLAGS) -I../src

.PHONY: all
all: client server core core.wasm

client: client.cc
	$(CC) $(CXXFLAGS) -o $@ $< -e _start -static -ggdb

server: server.cc
	$(CC) $(CXXFLAGS) -o $@ $< -e _start -static -ggdb

core: core.cc
	$(CC) $(CXXFLAGS) -o $@ $< -e _start -static -ggdb

core.wasm: core.cc
	$(CC) $(CXXFLAGS) -fuse-ld=lld --target=wasm32 -Wl,--export=__heap_base -Wl,--export=_start -Wl,--allow-undefined -o $@ $<
