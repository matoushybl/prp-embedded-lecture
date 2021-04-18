#include <spdlog/spdlog.h>
#include <UDPSocket.h>
#include <Robot.h>

int main() {
    spdlog::info("Hello world!");
    std::unique_ptr<Socket> socket = std::make_unique<UDPSocket>(3432);
    Robot robot(std::move(socket));
    robot.moveForward();
    return 0;
}
