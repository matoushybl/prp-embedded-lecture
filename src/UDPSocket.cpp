//
// Created by matous on 18.04.21.
//

#include <UDPSocket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>
#include <arpa/inet.h>
#include <unistd.h>

UDPSocket::UDPSocket(uint16_t receivingPort) {
    fileDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fileDescriptor == -1) {
        throw std::runtime_error("Failed to create socket.");
    }

    sockaddr_in bindAddress = {};
    bindAddress.sin_family = AF_INET;
    bindAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    bindAddress.sin_port = htons(receivingPort);

    if (bind(fileDescriptor, reinterpret_cast<sockaddr *>(&bindAddress), sizeof(sockaddr_in)) == -1) {
        throw std::runtime_error("Failed to bind socket.");
    }
}

//region
UDPSocket::UDPSocket(UDPSocket &&moved) noexcept : fileDescriptor(moved.fileDescriptor) {
    moved.fileDescriptor = -1;
}

UDPSocket &UDPSocket::operator=(UDPSocket &&moved) noexcept {
    fileDescriptor = moved.fileDescriptor;
    moved.fileDescriptor = -1;
    return *this;
}
//endregion

std::optional<std::vector<uint8_t>> UDPSocket::readBytes() {
    std::vector<uint8_t> readBuffer(1500, 0);
    const auto receivedBytes = ::recv(fileDescriptor, readBuffer.data(), readBuffer.size(), 0);
    if (receivedBytes == -1) {
        return std::nullopt;
    }
    return std::make_optional(std::vector(readBuffer.begin(), readBuffer.begin() + receivedBytes));
}

std::optional<size_t> UDPSocket::writeBytes(const std::vector<uint8_t> &data, SocketAddress targetAddress) {
    sockaddr_in rawTargetAddress = {};
    rawTargetAddress.sin_family = AF_INET;
    rawTargetAddress.sin_addr.s_addr = inet_addr(targetAddress.address.c_str());
    rawTargetAddress.sin_port = htons(targetAddress.port);

    const auto writeResult = ::sendto(fileDescriptor, data.data(), data.size(), 0, reinterpret_cast<sockaddr *>(&rawTargetAddress),
                                      sizeof(sockaddr_in));
    if (writeResult == -1) {
        return std::nullopt;
    }
    return std::make_optional(static_cast<size_t>(writeResult));
}

UDPSocket::~UDPSocket() {
    if (fileDescriptor != -1) {
        ::close(fileDescriptor);
    }
}
