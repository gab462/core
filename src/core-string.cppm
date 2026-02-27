export module core:string;

import :slice;
import :bits;

export namespace core {

    template <>
    struct slice<const char> {
        const char *ptr = nullptr;
        usize len = 0;

        slice() {};

        slice(const char *s): ptr{s} {
            if (s == nullptr)
                return;

            while (*s != '\0') {
                len++;
                s++;
            }

        }

        slice(const char *data, usize size): ptr{data}, len{size} {}

        auto operator==(slice<const char> other) -> bool {
            if (len != other.len)
                return false;

            for (usize i = 0; i < len; i++) {
                if (ptr[i] != other.ptr[i])
                    return false;
            }

            return true;
        }
    };

    using string = slice<const char>;

}
