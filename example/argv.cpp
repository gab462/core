import core;

extern "C" { core::slice<char*> argv = {}; }

extern "C" [[gnu::naked]] auto _start() -> void {
    __asm__ volatile(
        "pop %rax\n"
        "mov %rax, argv+8(%rip)\n"
        "mov %rsp, %rax\n"
        "mov %rax, argv(%rip)\n"
        "xor %rax, %rax\n"
        "xor %rbp, %rbp\n"
        "call start\n"
        "mov %rax, %rdi\n"
        "mov $60, %rax\n"
        "syscall\n"
    );
}

extern "C" auto start() -> int {
    core::println("arg count:", argv.len);

    for (auto arg : argv) {
        core::println("arg:", arg);
    }

    return 0;
}
