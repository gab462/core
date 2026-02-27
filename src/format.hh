#pragma once

#include "linear_allocator.hh"
#include "string.hh"
#include "bits.hh"
#include "nolibc.hh"

namespace core {
    
    inline auto format(linear_allocator *arena, char c) -> void {
        *arena->end++ = c;
    }

    inline auto format(linear_allocator *arena, string s) -> void {
        for (usize i = 0; i < s.len; ++i)
            format(arena, s.ptr[i]);
    }

    inline auto format(linear_allocator *arena, const char* s) -> void {
        format(arena, string{s});
    }

    inline auto format(linear_allocator *arena, u64 n) -> void {
        if (n == 0) {
            format(arena, '0');
            return;
        }

        // find highest power of 10 <= n
        u64 p = 1;
        while (p <= n / 10) p *= 10;

        while (p > 0) {
            int digit = n / p;
            format(arena, static_cast<char>('0' + digit));
            n %= p;
            p /= 10;
        }
    }

    inline auto format(linear_allocator *arena, s64 n) -> void {
        if (n < 0) {
            format(arena, '-');
            n *= -1;
        }

        format(arena, static_cast<u64>(n));
    }

    inline auto format(linear_allocator *arena, s32 n) -> void {
        format(arena, static_cast<s64>(n));
    }

    inline auto format(linear_allocator *arena, s16 n) -> void {
        format(arena, static_cast<s64>(n));
    }

    inline auto format(linear_allocator *arena, s8 n) -> void {
        format(arena, static_cast<s64>(n));
    }

    inline auto format(linear_allocator *arena, ssize n) -> void {
        format(arena, static_cast<s64>(n));
    }

    inline auto format(linear_allocator *arena, u32 n) -> void {
        format(arena, static_cast<u64>(n));
    }

    inline auto format(linear_allocator *arena, u16 n) -> void {
        format(arena, static_cast<u64>(n));
    }

    inline auto format(linear_allocator *arena, u8 n) -> void {
        format(arena, static_cast<u64>(n));
    }

    inline auto format(linear_allocator *arena, usize n) -> void {
        format(arena, static_cast<u64>(n));
    }

    template <typename ...A>
    auto fmt(linear_allocator *arena, A... args) -> string {
        const u8 *start = arena->end;

        ((format(arena, args), format(arena, ' ')), ...);

        --arena->end;            // remove extra space

        return {reinterpret_cast<const char *>(start), static_cast<usize>(arena->end - start)};
    }

    template <typename ...A>
    auto println(A... args) -> void {
        u8 *checkpoint = temp::allocator.end;

        string s = fmt(&temp::allocator, args...);
        *temp::allocator.end++ = '\n';
        s.len++;

        write(STDOUT_FILENO, s.ptr, s.len);

        temp::allocator.end = checkpoint;
    }

}
