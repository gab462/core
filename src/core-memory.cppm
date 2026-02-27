export module core:memory;

import :bits;

export inline auto operator new(core::usize, void *ptr) -> void * {
    return ptr;
}

export inline auto operator new[](core::usize, void *ptr) -> void * {
    return ptr;
}
