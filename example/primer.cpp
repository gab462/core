import core;

extern "C" auto _start() -> void {
    auto n = core::temp::create<core::s32>(-777);

    core::println("allocated:", *n);

    auto s = core::temp::alloc<core::s16>(5);

    for (auto& e : s) {
        e = 3;
    }

    for (auto e : s) {
        core::println("slice:", e);
    }

    core::assert(s[0] == 3);
    core::assert(s[2] == 3);

    core::array arr { 'a', 'b', 'c' };

    core::assert(arr[0] == 'a');
    core::assert(arr[2] == 'c');

    for (auto e : arr) {
        core::println("arr:", e);
    }

    core::slice<char> view = arr;

    core::assert(view[1] == 'b');

    for (auto& e : arr) {
        e = 'd';
    }

    core::assert(view[2] == 'd');

    for (auto e : view) {
        core::println("view:", e);
    }

    core::temp::free_all();

    core::exit(0);
}
