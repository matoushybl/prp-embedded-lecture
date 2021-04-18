//
// Created by matous on 18.04.21.
//

#ifndef PRP_LECTURE_EMBEDDED_SOCKET_H
#define PRP_LECTURE_EMBEDDED_SOCKET_H

#include <cstdint>
#include <vector>
#include <string>
#include <optional>

struct SocketAddress {
    std::string address;
    uint16_t port;
};

class Socket {
public:
    virtual std::optional<std::vector<uint8_t>> readBytes() = 0;
    virtual std::optional<size_t> writeBytes(const std::vector<uint8_t> &data, SocketAddress targetAddress) = 0;
};

#endif //PRP_LECTURE_EMBEDDED_SOCKET_H
