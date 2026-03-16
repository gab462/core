export module core:bounded_array;

import :bits;
import :array;
import :slice;

export namespace core {

template <typename T, core::usize N>
struct bounded_array {
    core::array<T, N> store;
    core::usize len = 0;

    auto push(T item) -> void {
        store[len++] = item;
    }

    auto pop() -> T {
        return store[--len];
    }

    auto swap_delete(core::usize idx) -> void {
        store[idx] = store[--len];
    }

    auto empty() -> bool {
        return len == 0;
    }

    auto full() -> bool {
        return len >= N;
    }

    auto operator[](usize idx) -> T& {
        return store[idx];
    }

    auto begin() -> T* {
        return store.data;
    }

    auto end() -> T* {
        return store.data + len;
    }

    operator slice<T>() {
        return slice<T> { store.data, len };
    }
};

};
