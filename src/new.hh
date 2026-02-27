#pragma once

#include "bits.hh"

inline auto operator new(core::usize, void *ptr) -> void * {
    return ptr;
}

inline auto operator new[](core::usize, void *ptr) -> void * {
    return ptr;
}
