//
// Created by matous on 18.04.21.
//

#ifndef PRP_LECTURE_EMBEDDED_UDPSOCKET_H
#define PRP_LECTURE_EMBEDDED_UDPSOCKET_H

#include "Socket.h"

class UDPSocket: public Socket {
public:
    explicit UDPSocket(uint16_t receivingPort);

    //region
//    UDPSocket(const UDPSocket &source) = delete;
//    UDPSocket& operator= (const UDPSocket& source) = delete;

    UDPSocket(UDPSocket &&moved) noexcept;
    UDPSocket& operator= (UDPSocket&& moved) noexcept;

    //endregion
    std::optional<std::vector<uint8_t>> readBytes() override;

    std::optional<size_t> writeBytes(const std::vector<uint8_t> &data, SocketAddress targetAddress) override;

    virtual ~UDPSocket();

private:
    int fileDescriptor;
};


#endif //PRP_LECTURE_EMBEDDED_UDPSOCKET_H
