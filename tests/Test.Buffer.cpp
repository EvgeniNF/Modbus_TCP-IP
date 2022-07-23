#include <gtest/gtest.h>
#include "Buffer.hpp"

inline uint8_t highByte(uint16_t value) noexcept {
    return *(reinterpret_cast<uint8_t*>(&value) + 1u);
}

inline uint8_t lowByte(uint16_t value) noexcept {
    return *(reinterpret_cast<uint8_t*>(&value));
}

TEST(TEST_BUFFER, COIL_BUFFER) {
    bool value = true;
    uint8_t slaveId = 0x01u;
    uint8_t address = 0x01u;
    uint16_t messageId = 0x01u;

    modbus::Buffer bufferTrue(value, 0x05u, slaveId, address, messageId);
    std::cout << bufferTrue << std::endl;

    auto data = reinterpret_cast<uint8_t const*>(bufferTrue.getMutableBuffer().data());

    ASSERT_TRUE(data[0] == highByte(messageId));
    ASSERT_TRUE(data[1] == lowByte(messageId));
    ASSERT_TRUE(data[2] == 0x00u);
    ASSERT_TRUE(data[3] == 0x00u);
    ASSERT_TRUE(data[4] == 0x00u);
    ASSERT_TRUE(data[5] == 0x06u);
    ASSERT_TRUE(data[6] == slaveId);
    ASSERT_TRUE(data[7] == 0x05u);

    ASSERT_TRUE(data[8] == highByte(messageId));
    ASSERT_TRUE(data[9] == lowByte(messageId));

    ASSERT_TRUE(data[10] == 0xFFu);
    ASSERT_TRUE(data[11] == 0x00u);

    value = false;
    modbus::Buffer bufferFalse(value, 0x05u, slaveId, address, messageId);
    std::cout << bufferFalse << std::endl;

    data = reinterpret_cast<uint8_t const*>(bufferFalse.getConstBuffer().data());

    ASSERT_TRUE(data[0] == highByte(messageId));
    ASSERT_TRUE(data[1] == lowByte(messageId));
    ASSERT_TRUE(data[2] == 0x00u);
    ASSERT_TRUE(data[3] == 0x00u);
    ASSERT_TRUE(data[4] == 0x00u);
    ASSERT_TRUE(data[5] == 0x06u);
    ASSERT_TRUE(data[6] == slaveId);
    ASSERT_TRUE(data[7] == 0x05u);

    ASSERT_TRUE(data[8] == highByte(messageId));
    ASSERT_TRUE(data[9] == lowByte(messageId));

    ASSERT_TRUE(data[10] == 0x00u);
    ASSERT_TRUE(data[11] == 0x00u);
}

TEST(TEST_BUFFER, REG_BUFFER) {
    uint16_t value = 0x0055u;
    uint8_t slaveId = 0x01u;
    uint8_t address = 0x01u;
    uint16_t messageId = 0x01u;

    modbus::Buffer buffer(value, 0x05u, slaveId, address, messageId);
    std::cout << buffer << std::endl;
}

TEST(TEST_BUFFER, COILS_BUFFER) {
    std::vector<bool> value = {true, false};
    uint8_t slaveId = 0x01u;
    uint8_t address = 0x01u;
    uint16_t messageId = 0x01u;

    modbus::Buffer buffer(value, 0xFu, slaveId, address, messageId);
    std::cout << buffer << std::endl;
}

TEST(TEST_BUFFER, REGS_BUFFER) {
    std::vector<uint16_t> value = {0x22, 0x2418};
    uint8_t slaveId = 0x01u;
    uint8_t address = 0x01u;
    uint16_t messageId = 0x01u;

    modbus::Buffer buffer(value, 0x10u, slaveId, address, messageId);
    std::cout << buffer << std::endl;
}
