export module core:array;

import :bits;
import :slice;

export namespace core {

    template <typename T, usize N>
    struct array {
        T data[N];

        auto operator[](usize idx) -> T& {
            return data[idx];
        }

        auto begin() -> T * {
            return data;
        }

        auto end() -> T * {
            return data + N;
        }

        operator slice<T>() {
            return slice<T> { data, N };
        }
    };

    template <typename T, typename ...A>
    auto make_array(T arg, A... args) {
        return array<T, 1 + sizeof...(args)>{arg, args...};
    }

}
