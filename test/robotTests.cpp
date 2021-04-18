//
// Created by matous on 18.04.21.
//

#include <gtest/gtest.h>
#include <Socket.h>
#include <Robot.h>

//region
class MockSocket: public Socket {
public:
    std::optional<std::vector<uint8_t>> readBytes() override {
        return std::make_optional(std::vector<uint8_t>{1, 2});
    }

    std::optional<size_t> writeBytes(const std::vector<uint8_t> &data, SocketAddress) override {
        return std::make_optional(data.size());
    }
};
//endregion

TEST(RobotTests, MoveForward) {
    std::unique_ptr<Socket> socket = std::make_unique<MockSocket>();
    Robot robot(std::move(socket));

    ASSERT_TRUE(robot.moveForward());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}