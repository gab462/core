export module core;

export import :bits;
export import :array;
export import :format;
export import :linear_allocator;
export import :memory;
export import :nolibc;
export import :slice;
export import :string;

// https://gcc.gnu.org/onlinedocs/gcc/Standards.html

export extern "C" {
    auto memcpy(core::u8 *dest, const core::u8* src, core::usize n) -> core::u8 * {
        for (core::usize i = 0; i < n; ++i) {
            dest[i] = src[i];
        }

        return dest;
    }

    auto memset(core::u8 *s, core::u8 c, core::usize n) -> core::u8 * {
        for (core::usize i = 0; i < n; ++i) {
            s[i] = c;
        }

        return s;
    }

    auto memmove(core::u8 *dst, const core::u8 *src, core::usize n) -> core::u8 * {
        if (dst < src) {
            for (core::usize i = 0; i < n; ++i) {
                dst[i] = src[i];
            }
        } else if (src < dst) {
            for (core::usize i = 0; i < n; ++i) {
                dst[n - i - 1] = src[n - i - 1];
            }
        }

        return dst;
    }

    auto memcmp(const core::u8* s1, const core::u8* s2, core::usize n) -> core::s32 {
        for (core::usize i = 0; i < n; ++i) {
            if (s1[i] != s2[i]) {
                if (s1[i] < s2[i])
                    return -1;
                else
                    return 1;
            }
        }

        return 0;
    }
}
