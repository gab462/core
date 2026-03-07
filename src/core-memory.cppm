export module core:memory;

import :bits;

export auto operator new(core::usize, void* ptr) -> void* {
    return ptr;
}

export auto operator new[](core::usize, void* ptr) -> void* {
    return ptr;
}
