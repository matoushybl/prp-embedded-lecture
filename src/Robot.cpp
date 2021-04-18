//
// Created by matous on 18.04.21.
//

#include "Robot.h"

Robot::Robot(std::unique_ptr<Socket> socket): socket(std::move(socket)) {

}

bool Robot::moveForward() {
    const auto writeResult = socket->writeBytes({1, 2, 3}, SocketAddress {"127.0.0.1", 3432});
    if (!writeResult.has_value()) {
        return false;
    }
    const auto readResult = socket->readBytes();
    return readResult.has_value() && readResult.value() == std::vector<uint8_t>{1, 2};
}
