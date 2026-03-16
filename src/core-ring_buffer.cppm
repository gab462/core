export module core:ring_buffer;

import :bits;
import :array;

export namespace core {

template <typename T, core::usize N>
struct ring_buffer {
    core::array<T, N> store;
    core::usize head = 0;
    core::usize tail = 0;

    auto put(T item) -> void {
        store[tail] = item;
        tail = (tail + 1) % N;
    }

    auto get() -> T {
        T ret = store[head];
        head = (head + 1) % N;

        return ret;
    }

    auto empty() -> bool {
        return head == tail;
    }

    auto full() -> bool {
        return (head + 1) % N == tail;
    }
};

};
