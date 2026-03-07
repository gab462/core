export module core:array;

import :bits;
import :slice;

export namespace core {

template <typename T, usize N>
struct array {
    T data[N];

    array() = default;

    template <typename... A>
    array(A... args)
        : data { args... } { }

    auto operator[](usize idx) -> T& {
        return data[idx];
    }

    auto begin() -> T* {
        return data;
    }

    auto end() -> T* {
        return data + N;
    }

    operator slice<T>() {
        return slice<T> { data, N };
    }
};

template <typename T, typename... A>
array(T arg, A... args) -> array<T, 1 + sizeof...(A)>;

}
