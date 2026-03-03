export module core:format;

import :linear_allocator;
import :string;
import :bits;
import :nolibc;

export namespace core {
    
    auto format(linear_allocator *arena, char c) -> void {
        *arena->end++ = c;
    }

    auto format(linear_allocator *arena, string s) -> void {
        for (usize i = 0; i < s.len; ++i)
            format(arena, s.ptr[i]);
    }

    auto format(linear_allocator *arena, const char *s) -> void {
        format(arena, string{s});
    }

    auto format(linear_allocator *arena, u64 n) -> void {
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

    auto format(linear_allocator *arena, s64 n) -> void {
        if (n < 0) {
            format(arena, '-');
            n *= -1;
        }

        format(arena, static_cast<u64>(n));
    }

    auto format(linear_allocator *arena, s32 n) -> void {
        format(arena, static_cast<s64>(n));
    }

    auto format(linear_allocator *arena, s16 n) -> void {
        format(arena, static_cast<s64>(n));
    }

    auto format(linear_allocator *arena, s8 n) -> void {
        format(arena, static_cast<s64>(n));
    }

    auto format(linear_allocator *arena, ssize n) -> void {
        format(arena, static_cast<s64>(n));
    }

    auto format(linear_allocator *arena, u32 n) -> void {
        format(arena, static_cast<u64>(n));
    }

    auto format(linear_allocator *arena, u16 n) -> void {
        format(arena, static_cast<u64>(n));
    }

    auto format(linear_allocator *arena, u8 n) -> void {
        format(arena, static_cast<u64>(n));
    }

    auto format(linear_allocator *arena, usize n) -> void {
        format(arena, static_cast<u64>(n));
    }

    template <typename ...A>
    auto fmt(linear_allocator *arena, A... args) -> string {
        u8 *start = arena->alloc<u8>(0).ptr;

        ((format(arena, args), format(arena, ' ')), ...);

        --arena->end;            // remove extra space

        return {reinterpret_cast<const char *>(start), static_cast<usize>(arena->end - start)};
    }

    template <typename ...A>
    auto println(A... args) -> void {
        u8 *checkpoint = temp::alloc<u8>(0).ptr;

        string s = fmt(&temp::allocator, args...);
        *temp::allocator.end++ = '\n';
        s.len++;

        write(STDOUT_FILENO, s.ptr, s.len);

        temp::allocator.end = checkpoint;
    }

    auto assert(bool pred, const char *file = __builtin_FILE(), s32 line = __builtin_LINE()) -> void {
        if (not pred) {
            u8 *start = temp::alloc<u8>(0).ptr;

            format(&temp::allocator, file);
            format(&temp::allocator, ":");
            format(&temp::allocator, line);
            format(&temp::allocator, ": assertion failed\n");

            string s =  {reinterpret_cast<const char *>(start), static_cast<usize>(temp::allocator.end - start)};
            write(STDOUT_FILENO, s.ptr, s.len);

            exit(1);
        }
    }

}
