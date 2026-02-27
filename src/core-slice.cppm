export module core:slice;

import :bits;

export namespace core {

    template <typename T>
    struct slice {
        T *ptr = nullptr;
        usize len = 0;

        slice() {}

        slice(T *data, usize size): ptr{data}, len{size} {}

        auto operator[](usize idx) -> T& {
            return ptr[idx];
        }

        auto begin() -> T* {
            return ptr;
        }

        auto end() -> T* {
            return ptr + len;
        }
    };

    template <typename T>
    auto subslice(slice<T> s, usize begin, usize end) -> slice<T> {
        return { s.ptr + begin, end - begin };
    }

}
