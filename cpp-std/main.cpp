#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

namespace {
constexpr int kPort = 8080;

bool send_all(int socket, const std::string& message) {
    std::size_t sent = 0;
    while (sent < message.size()) {
        const ssize_t count = send(socket, message.data() + sent,
                                   message.size() - sent, 0);
        if (count < 0) {
            if (errno == EINTR) {
                continue;
            }
            return false;
        }
        if (count == 0) {
            return false;
        }
        sent += static_cast<std::size_t>(count);
    }
    return true;
}
}  // namespace

int main() {
    const int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "socket failed: " << std::strerror(errno) << '\n';
        return 1;
    }

    int reuse_address = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse_address,
                   sizeof(reuse_address)) < 0) {
        std::cerr << "setsockopt failed: " << std::strerror(errno) << '\n';
        close(server_socket);
        return 1;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(kPort);

    if (bind(server_socket, reinterpret_cast<sockaddr*>(&address),
             sizeof(address)) < 0) {
        std::cerr << "bind failed: " << std::strerror(errno) << '\n';
        close(server_socket);
        return 1;
    }

    if (listen(server_socket, 16) < 0) {
        std::cerr << "listen failed: " << std::strerror(errno) << '\n';
        close(server_socket);
        return 1;
    }

    std::cout << "Server running on http://localhost:" << kPort << '\n';

    while (true) {
        sockaddr_in client_address{};
        socklen_t client_address_length = sizeof(client_address);
        const int client_socket = accept(
            server_socket, reinterpret_cast<sockaddr*>(&client_address),
            &client_address_length);

        if (client_socket < 0) {
            if (errno == EINTR) {
                continue;
            }
            std::cerr << "accept failed: " << std::strerror(errno) << '\n';
            break;
        }

        char request[4096]{};
        const ssize_t received = recv(client_socket, request, sizeof(request) - 1, 0);
        if (received < 0 && errno != EINTR) {
            std::cerr << "recv failed: " << std::strerror(errno) << '\n';
        }

        const std::string body = "Hello, C++!\n";
        const std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain; charset=utf-8\r\n"
            "Content-Length: " + std::to_string(body.size()) + "\r\n"
            "Connection: close\r\n"
            "\r\n" + body;

        if (!send_all(client_socket, response)) {
            std::cerr << "send failed: " << std::strerror(errno) << '\n';
        }
        close(client_socket);
    }

    close(server_socket);
    return 0;
}
