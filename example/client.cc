#include <nolibc.hh>
#include <bits.hh>
#include <format.hh>

auto htons(core::u16 n) -> core::u16 {
    return (n << 8) | (n >> 8);
}

extern "C" auto _start() -> void {
    int fd = core::socket(core::AF_INET, core::SOCK_STREAM, 0);

    if (fd < 0) {
        core::println("socket() error");
        core::exit(1);
    }

    core::sockaddr_in addr = {
        .sin_family = core::AF_INET,
        .sin_port = htons(8080),
        .sin_addr = {
            .s_addr = (127 << 0) + (0 << 8) + (0 << 16) + (1 << 24),
        },
    };

    int ret = core::connect(fd, &addr, sizeof(addr));

    if (ret < 0) {
        core::println("connect() error");
        core::exit(1);
    }

    core::println("Connected successfully\n");

    core::string msg = "hello";

    ret = core::write(fd, msg.ptr, msg.len);

    if (ret <= 0) {
        core::println("write() error");
        core::exit(1);
    }

    char buf[4096];
    core::usize received = core::read(fd, buf, sizeof(buf));

    if (received <= 0) {
        core::println("read() error\n");
        core::exit(1);
    }

    core::println("Message:", core::string{buf, received});

    core::close(fd);

    core::exit(0);
}
