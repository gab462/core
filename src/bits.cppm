export module bits;

export namespace core {

    using s8 = signed char;
    using s16 = signed short;
    using s32 = signed int;
    using s64 = signed long long;

    using u8 = unsigned char;
    using u16 = unsigned short;
    using u32 = unsigned int;
    using u64 = unsigned long long;

    using usize = decltype(sizeof(int));
    using ssize = decltype((char *) 0 - (char *) 1);

    static_assert(sizeof(u8) == 1
                  && sizeof(u16) == 2
                  && sizeof(u32) == 4
                  && sizeof(u64) == 8);

    using f32 = float;
    using f64 = double;

    static_assert(sizeof(f32) == 4 && sizeof(f64) == 8);

}
