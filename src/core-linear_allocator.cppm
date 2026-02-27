export module core:linear_allocator;

import :bits;
import :nolibc;
import :memory;
import :slice;

export namespace core {
        
    struct linear_allocator {
        static constexpr usize overcommit = 16ul * 1024 * 1024 * 1024;

        u8 *start;
        u8 *end;
        usize total_size;

        linear_allocator() = default;

        linear_allocator(usize size): total_size{size} {
            start = static_cast<u8*>(mmap(nullptr, overcommit,
                                          PROT_READ | PROT_WRITE,
                                          MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE,
                                          -1, 0));
            end = start;
        }

        template <typename T>
        auto align() -> void {
            usize pos = end - start;

            if (pos % alignof(T) != 0)
                end += alignof(T) - (pos % alignof(T));
        }

        template <typename T, typename ...A>
        auto create(A... args) -> T * {
            align<T>();
            auto addr = new(end) T{args...};
            end += sizeof(T);

            return static_cast<T *>(addr);
        }

        template <typename T, typename ...A>
        auto alloc(usize count) -> slice<T> {
            align<T>();
            auto addr = new(end) T[count];
            end += sizeof(T) * count;

            return slice<T>{addr, count};
        }

        auto reset() -> void {
            end = start;
        }

        auto free_all() -> void {
            munmap(start, total_size);
        }
    };

    struct temp {
        static inline linear_allocator allocator = {};

        template <typename T, typename ...A>
        static auto create(A... args) -> T * {
            if (allocator.start == nullptr)
                allocator = linear_allocator(linear_allocator::overcommit);

            return allocator.create<T>(args...);
        }

        template <typename T, typename ...A>
        static auto alloc(usize count) -> slice<T> {
            if (allocator.start == nullptr)
                allocator = linear_allocator(linear_allocator::overcommit);

            return allocator.alloc<T>(count);
        }

        static auto reset() -> void {
            allocator.reset();
        }

        static auto free_all() -> void {
            if (allocator.start != nullptr)
                allocator.free_all();
        }
    };

}
