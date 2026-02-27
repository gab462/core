#pragma once

#include "bits.hh"

#define assert(p) assert_here(p, #p, __FILE__, __LINE__)

namespace core {
    inline auto assert_here(bool pred, const char *msg, const char *file, s32 line) -> void;
}

#include "format.hh"

namespace core {
    
    inline auto assert_here(bool pred, const char *msg, const char *file, s32 line) -> void {
        if (!pred) {
            println(file, ":", line, ": assertion failed (", msg, ")");
            exit(1);
        }
    }

}
