export module core:nolibc;

import :bits;

#if defined(__linux__) and defined(__x86_64__)
#define SYS_LINUX
#elif defined(__wasm32__)
#define SYS_WASM
#else
#error "OS not implemented"
#endif

export namespace core {

#if defined(SYS_LINUX)

    auto syscall0(ssize sys) -> ssize {
        register ssize ret asm("rax") = sys;

        __asm__ volatile(
            "syscall"
            : "+r"(ret)
            :
            : "rcx", "r11", "memory");

        return ret;
    }

    auto syscall1(ssize sys, ssize a0) -> ssize {
        register ssize ret asm("rax") = sys;
        register ssize r0 asm("rdi") = a0;

        __asm__ volatile(
            "syscall"
            : "+r"(ret)
            : "r"(r0)
            : "rcx", "r11", "memory");

        return ret;
    }

    auto syscall2(ssize sys, ssize a0, ssize a1) -> ssize {
        register ssize ret asm("rax") = sys;
        register ssize r0 asm("rdi") = a0;
        register ssize r1 asm("rsi") = a1;

        __asm__ volatile(
            "syscall"
            : "+r"(ret)
            : "r"(r0), "r"(r1)
            : "rcx", "r11", "memory");

        return ret;
    }

    auto syscall3(ssize sys, ssize a0, ssize a1, ssize a2) -> ssize {
        register ssize ret asm("rax") = sys;
        register ssize r0 asm("rdi") = a0;
        register ssize r1 asm("rsi") = a1;
        register ssize r2 asm("rdx") = a2;

        __asm__ volatile(
            "syscall"
            : "+r"(ret)
            : "r"(r0), "r"(r1), "r"(r2)
            : "rcx", "r11", "memory");

        return ret;
    }

    auto syscall4(ssize sys, ssize a0, ssize a1, ssize a2, ssize a3) -> ssize {
        register ssize ret asm("rax") = sys;
        register ssize r0 asm("rdi") = a0;
        register ssize r1 asm("rsi") = a1;
        register ssize r2 asm("rdx") = a2;
        register ssize r3 asm("r10") = a3;

        __asm__ volatile(
            "syscall"
            : "+r"(ret)
            : "r"(r0), "r"(r1), "r"(r2), "r"(r3)
            : "rcx", "r11", "memory");

        return ret;
    }

    auto syscall5(ssize sys, ssize a0, ssize a1, ssize a2, ssize a3, ssize a4) -> ssize {
        register ssize ret asm("rax") = sys;
        register ssize r0 asm("rdi") = a0;
        register ssize r1 asm("rsi") = a1;
        register ssize r2 asm("rdx") = a2;
        register ssize r3 asm("r10") = a3;
        register ssize r4 asm("r8") = a4;

        __asm__ volatile(
            "syscall"
            : "+r"(ret)
            : "r"(r0), "r"(r1), "r"(r2), "r"(r3), "r"(r4)
            : "rcx", "r11", "memory");

        return ret;
    }

    auto syscall6(ssize sys, ssize a0, ssize a1, ssize a2, ssize a3, ssize a4, ssize a5) -> ssize {
        register ssize ret asm("rax") = sys;
        register ssize r0 asm("rdi") = a0;
        register ssize r1 asm("rsi") = a1;
        register ssize r2 asm("rdx") = a2;
        register ssize r3 asm("r10") = a3;
        register ssize r4 asm("r8") = a4;
        register ssize r5 asm("r9") = a5;

        __asm__ volatile(
            "syscall"
            : "+r"(ret)
            : "r"(r0), "r"(r1), "r"(r2), "r"(r3), "r"(r4), "r"(r5)
            : "rcx", "r11", "memory");

        return ret;
    }

#elif defined(SYS_WASM)

    extern "C"  {

        auto syscall0(ssize sys) -> ssize;
        auto syscall1(ssize sys, ssize arg0) -> ssize;
        auto syscall2(ssize sys, ssize arg0, ssize arg1) -> ssize;
        auto syscall3(ssize sys, ssize arg0, ssize arg1, ssize arg2) -> ssize;
        auto syscall4(ssize sys, ssize arg0, ssize arg1, ssize arg2, ssize arg3) -> ssize;
        auto syscall5(ssize sys, ssize arg0, ssize arg1, ssize arg2, ssize arg3, ssize arg4) -> ssize;
        auto syscall6(ssize sys, ssize arg0, ssize arg1, ssize arg2, ssize arg3, ssize arg4, ssize arg5) -> ssize;

    }

#endif

    struct pollfd {
        int fd;
        short events;
        short revents;
    };

    struct in_addr {
        unsigned int s_addr;
    };

    struct sockaddr_un {
        unsigned short sun_family;
        char sun_path[108];
    };

    struct sockaddr_in {
        unsigned short sin_family;
        unsigned short sin_port;
        struct in_addr sin_addr;
        char sin_zero[8];
    };

    // TODO: enum class
    constexpr ssize SYS_READ = 0;
    constexpr ssize SYS_WRITE = 1;
    constexpr ssize SYS_OPEN = 2;
    constexpr ssize SYS_CLOSE = 3;
    constexpr ssize SYS_POLL = 7;
    constexpr ssize SYS_LSEEK = 8;
    constexpr ssize SYS_MMAP = 9;
    constexpr ssize SYS_MUNMAP = 11;
    constexpr ssize SYS_PIPE = 22;
    constexpr ssize SYS_GETPID = 39;
    constexpr ssize SYS_SOCKET = 41;
    constexpr ssize SYS_CONNECT = 42;
    constexpr ssize SYS_ACCEPT = 43;
    constexpr ssize SYS_SENDTO = 44;
    constexpr ssize SYS_RECVFROM = 45;
    constexpr ssize SYS_SHUTDOWN = 48;
    constexpr ssize SYS_BIND = 49;
    constexpr ssize SYS_LISTEN = 50;
    constexpr ssize SYS_FORK = 57;
    constexpr ssize SYS_EXIT = 60;
    constexpr ssize SYS_WAIT4 = 61;
    constexpr ssize SYS_KILL = 62;
    constexpr ssize SYS_UMASK = 95;

    constexpr ssize STDIN_FILENO = 0;
    constexpr ssize STDOUT_FILENO = 1;
    constexpr ssize STDERR_FILENO = 2;

    constexpr ssize O_RDONLY = 0;
    constexpr ssize O_WRONLY = 1;
    constexpr ssize O_RDWR = 2;

    constexpr ssize SEEK_SET = 0;
    constexpr ssize SEEK_CUR = 1;
    constexpr ssize SEEK_END = 2;

    constexpr ssize PROT_NONE = 0;
    constexpr ssize PROT_READ = 1;
    constexpr ssize PROT_WRITE = 2;
    constexpr ssize PROT_EXEC = 4;

    constexpr ssize MAP_SHARED = 1;
    constexpr ssize MAP_PRIVATE = 2;
    constexpr ssize MAP_FIXED = 16;

    constexpr ssize AF_UNIX = 1;
    constexpr ssize AF_INET = 2;

    constexpr ssize SOCK_STREAM = 1;
    constexpr ssize SOCK_DGRAM = 2;
    constexpr ssize SOCK_RAW = 3;

    constexpr ssize MSG_OOB = 0x01;
    constexpr ssize MSG_PEEK = 0x02;
    constexpr ssize MSG_DONTROUTE = 0x04;

    constexpr ssize SHUT_RD = 0;
    constexpr ssize SHUT_WR = 1;
    constexpr ssize SHUT_RDWR = 2;

    constexpr ssize WNOHANG = 1;
    constexpr ssize WUNTRACED = 2;

    constexpr ssize O_APPEND = 00002000;
    constexpr ssize O_CLOEXEC = 02000000;
    constexpr ssize O_CREAT = 00000100;
    constexpr ssize O_DIRECTORY = 00200000;
    constexpr ssize O_EXCL = 00000200;
    constexpr ssize O_NOFOLLOW = 00400000;
    constexpr ssize O_NONBLOCK = 00004000;
    constexpr ssize O_TRUNC = 00001000;

    constexpr ssize SEEK_HOLE = 4;
    constexpr ssize SEEK_DATA = 3;

    constexpr ssize MAP_ANONYMOUS = 32;
    constexpr ssize MAP_NORESERVE = 16384;

    constexpr ssize MSG_WAITALL = 0x100;

    auto WTERMSIG(int status) -> int {
        return status & 0177;
    }

    auto WSTOPSIG(int status) -> int {
        return status >> 8;
    }

    auto WIFEXITED(int status) -> int {
        return WTERMSIG(status) == 0;
    }

    auto WCOREDUMP(int status) -> int {
        return status & 0200;
    }

    auto WIFSIGNALED(int status) -> int {
        return (WTERMSIG(status) + 1) >> 1 > 0;
    }

    auto WIFSTOPPED(int status) -> int {
        return (status & 0xff) == 0177;
    }

    auto WEXITSTATUS(int status) -> int {
        return status & 0xff00 >> 8;
    }

    auto read(int fd, void *buf, usize count) -> ssize {
        return syscall3(SYS_READ, fd, reinterpret_cast<ssize>(buf), count);
    }

    auto write(int fd, const void *buf, usize count) -> ssize {
        return syscall3(SYS_WRITE, fd, reinterpret_cast<ssize>(buf), count);
    }

    auto open(const char *filename, int flags, unsigned short mode) -> int {
        return syscall3(SYS_OPEN, reinterpret_cast<ssize>(filename), flags, mode);
    }

    auto close(int fd) -> int {
        return syscall1(SYS_CLOSE, fd);
    }

    auto poll(struct pollfd ufds[], unsigned int nfds, int timeout) -> int {
        return syscall3(SYS_POLL, reinterpret_cast<ssize>(ufds), nfds, timeout);
    }

    auto lseek(int fd, ssize offset, int whence) -> ssize {
        return syscall3(SYS_LSEEK, fd, offset, whence);
    }

    auto mmap(void *addr, usize len, int prot, int flags, int fd, ssize offset) -> void * {
        return reinterpret_cast<void *>(syscall6(SYS_MMAP, reinterpret_cast<ssize>(addr), len,
                                                 prot, flags, fd, offset));
    }

    auto munmap(void *addr, usize len) -> int {
        return syscall2(SYS_MUNMAP, reinterpret_cast<ssize>(addr), len);
    }

    auto pipe(int fds[2]) -> int {
        return syscall1(SYS_PIPE, reinterpret_cast<ssize>(fds));
    }

    auto getpid(void) -> int {
        return syscall0(SYS_GETPID);
    }

    auto socket(int domain, int type, int protocol) -> int {
        return syscall3(SYS_SOCKET, domain, type, protocol);
    }

    auto connect(int sockfd, const void *addr, unsigned len) -> int {
        return syscall3(SYS_CONNECT, sockfd, reinterpret_cast<ssize>(addr), len);
    }

    auto accept(int sockfd, void *addr, unsigned *len) -> int {
        return syscall3(SYS_ACCEPT, sockfd, reinterpret_cast<ssize>(addr),
                        reinterpret_cast<ssize>(len));
    }

    auto sendto(int sockfd, const void *buf, usize buf_len, int flags,
                const void *addr, unsigned addr_len) -> ssize {
        return syscall6(SYS_SENDTO, sockfd, reinterpret_cast<ssize>(buf), buf_len, flags,
                        reinterpret_cast<ssize>(addr), addr_len);
    }

    auto recvfrom(int sockfd, const void *buf, usize buf_len,
                  int flags, const void *addr, unsigned *addr_len) -> ssize {
        return syscall6(SYS_RECVFROM, sockfd, reinterpret_cast<ssize>(buf), buf_len, flags,
                        reinterpret_cast<ssize>(addr), reinterpret_cast<ssize>(addr_len));
    }

    auto shutdown(int sockfd, int how) -> int {
        return syscall2(SYS_SHUTDOWN, sockfd, how);
    }

    auto bind(int sockfd, const void *addr, unsigned len) -> int {
        return syscall3(SYS_BIND, sockfd, reinterpret_cast<ssize>(addr), len);
    }

    auto listen(int sockfd, int backlog) -> int {
        return syscall2(SYS_LISTEN, sockfd, backlog);
    }

    auto fork(void) -> int {
        return syscall0(SYS_FORK);
    }

    auto exit(int code) -> void {
        syscall1(SYS_EXIT, code);
    }

    auto waitpid(int pid, int *status, int options) -> int {
        return syscall4(SYS_WAIT4, pid, reinterpret_cast<ssize>(status), options, 0);
    }

    auto kill(int pid, int sig) -> int {
        return syscall2(SYS_KILL, pid, sig);
    }

    auto umask(unsigned short cmask) -> core::s16 {
        return syscall1(SYS_UMASK, cmask);
    }

}
