CC := cc
NOSTDFLAGS := -nostdlib -fno-builtin -fno-unwind-tables -fno-asynchronous-unwind-tables -Wa,--noexecstack -fno-stack-protector # -fdata-sections + -Wl,-dead_strip / -Wl,--gc-sections
CXXFLAGS := -Wall -Wextra -Wshadow -std=c++20 -pedantic -fno-exceptions -fno-rtti -fmodules $(NOSTDFLAGS) -fprebuilt-module-path=.
MOD := core-bits.pcm core-nolibc.pcm core-slice.pcm core-string.pcm core-array.pcm core-memory.pcm core-linear_allocator.pcm core-format.pcm core.pcm
TARGET := LINUX

ifeq ($(TARGET), WASM)
	CXXFLAGS += --target=wasm32
	LDFLAGS = -fuse-ld=lld -Wl,--export=__heap_base -Wl,--export=_start -Wl,--allow-undefined 
	EXT=.wasm
else
	CXXFLAGS += -ggdb
	LDFLAGS = -static
	EXT=
endif

.PHONY: all
all: client$(EXT) server$(EXT) core$(EXT)

%.pcm: ../src/%.cppm
	$(CC) $(CXXFLAGS) --precompile -o $@ $<

%$(EXT): %.cpp $(MOD)
	$(CC) $(CXXFLAGS) -o $@ $^ -e _start $(LDFLAGS)
