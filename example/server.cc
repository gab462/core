#include <nolibc.hh>
#include <bits.hh>
#include <format.hh>

auto htons(core::u16 n) -> core::u16 {
    return (n << 8) | (n >> 8);
}

extern "C" auto _start() -> void {
    int server_fd = core::socket(core::AF_INET, core::SOCK_STREAM, 0);

    if (server_fd == 0) {
        core::println("socket() error\n");
        core::exit(1);
    }

    core::sockaddr_in addr = {
        .sin_family = core::AF_INET,
        .sin_port = htons(8080),
        .sin_addr = {
            .s_addr = 0,
        },
    };

    core::u32 addr_len = sizeof(addr);

    int ret = core::bind(server_fd, &addr, addr_len);

    if (ret < 0) {
        core::println("bind() error");
        core::exit(1);
    }

    ret = core::listen(server_fd, 128);

    if (ret < 0) {
        core::println("listen() error");
        core::exit(1);
    }

    core::println("Server listening...");

    int client_fd = core::accept(server_fd, &addr, &addr_len);

    if (client_fd < 0) {
        core::println("accept() failed");
        core::exit(1);
    }

    core::println("Client connected");

    char buf[4096];
    for (core::usize received = core::read(client_fd, buf, sizeof(buf));
            received > 0;
            received = core::read(client_fd, buf, sizeof(buf))) {
        core::println("Received:", core::string{buf, received});

        core::write(client_fd, buf, received);
    }

    core::close(client_fd);
    core::close(server_fd);

    core::exit(0);
}
