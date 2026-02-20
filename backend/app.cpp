#include <iostream>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    char hostname[256];
    gethostname(hostname, sizeof(hostname));

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 10);

    while (true) {
        int client = accept(server_fd, nullptr, nullptr);

        std::string body = "Served by backend: ";
        body += hostname;
        body += "\n";

        std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: " + std::to_string(body.size()) + "\r\n"
            "Connection: close\r\n"
            "\r\n" +
            body;

        send(client, response.c_str(), response.size(), 0);
        close(client);
    }
}
