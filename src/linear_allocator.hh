#pragma once

#include "bits.hh"
#include "nolibc.hh"
#include "new.hh"
#include "slice.hh"

namespace core {
        
    struct linear_allocator {
        static constexpr usize overcommit = 16ul * 1024 * 1024 * 1024;

        u8 *start;
        u8 *end;

        linear_allocator() {
            start = static_cast<u8*>(mmap(nullptr, overcommit,
                                          PROT_READ | PROT_WRITE,
                                          MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE,
                                          -1, 0));
            end = start;
        }

        template <typename T>
        auto align() -> void {
            usize pos = end - start;

            if (pos % alignof(T) != 0)
                end += alignof(T) - (pos % alignof(T));
        }

        template <typename T, typename ...A>
        auto create(A... args) -> T * {
            align<T>();
            auto addr = new(end) T{args...};
            end += sizeof(T);

            return static_cast<T *>(addr);
        }

        template <typename T, typename ...A>
        auto alloc(usize count) -> slice<T> {
            align<T>();
            auto addr = new(end) T[count];
            end += sizeof(T) * count;

            return slice<T>{addr, count};
        }

        auto reset() -> void {
            end = start;
        }

        auto free_all() -> void {
            munmap(start, overcommit);
        }
    };

    struct temp {
        static inline linear_allocator allocator = {};


        template <typename T, typename ...A>
        static auto create(A... args) -> T * {
            return allocator.create<T>(args...);
        }

        template <typename T, typename ...A>
        static auto alloc(usize count) -> slice<T> {
            return allocator.alloc<T>(count);
        }

        static auto reset() -> void {
            allocator.reset();
        }

        static auto free_all() -> void {
            allocator.free_all();
        }
    };

}
