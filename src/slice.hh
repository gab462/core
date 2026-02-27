#pragma once

#include "bits.hh"
#include "assert.hh"

namespace core {
    
    template <typename T>
    struct slice {
        T *ptr = nullptr;
        usize len = 0;

        slice() {}

        slice(T *data, usize size): ptr{data}, len{size} {}

        auto operator[](usize idx) -> T& {
            assert(ptr != nullptr && idx < len);
            return ptr[idx];
        }

        auto begin() -> T* {
            assert(ptr != nullptr);
            return ptr;
        }

        auto end() -> T* {
            assert(ptr != nullptr);
            return ptr + len;
        }
    };

    template <typename T>
    auto subslice(slice<T> s, usize begin, usize end) -> slice<T> {
        assert(end >= begin && end <= s.len);
        return { s.ptr + begin, end - begin };
    }

}
