//
// Created by matous on 18.04.21.
//

#include <gtest/gtest.h>
#include <UDPSocket.h>

TEST(UDPSocketTests, SendTest) {
    UDPSocket receivingSocket(3432);
    UDPSocket sendingSocket(3433);
    const std::vector<uint8_t> toBeSent = {1, 2, 3};
    const auto writeResult = sendingSocket.writeBytes(toBeSent, SocketAddress {"127.0.0.1", 3432});
    ASSERT_TRUE(writeResult.has_value());

    const auto readResult = receivingSocket.readBytes();
    ASSERT_TRUE(readResult.has_value());
    ASSERT_EQ(toBeSent, readResult.value());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}