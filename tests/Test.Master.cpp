#include <gtest/gtest.h>
#include <Master.hpp>

TEST(TEST_MASTER, WRITE_COIL) {
    modbus::Master modbusMaster("127.0.0.1");
    bool coil = true;

    auto result = modbusMaster.writeCoil(coil, 0x00);
    std::cout << result.what() << std::endl;
    ASSERT_TRUE(result);
    coil = false;
    result = modbusMaster.writeCoil(coil, 0x00);
    std::cout << result.what() << std::endl;
    ASSERT_TRUE(result);
}

TEST(TEST_MASTER, WRITE_REG) {
    modbus::Master modbusMaster("127.0.0.1");
    uint16_t reg = 0x2344;

    auto result = modbusMaster.writeRegister(reg, 0x00);
    std::cout << result.what() << std::endl;
    ASSERT_TRUE(result);
    reg = 0x0000u;
    result = modbusMaster.writeRegister(reg, 0x00);
    std::cout << result.what() << std::endl;
    ASSERT_TRUE(result);
}

TEST(TEST_MASTER, WRITE_REGS) {
    modbus::Master modbusMaster("127.0.0.1");
    std::vector<uint16_t> regs = {0xFFu, 0xA, 0x24FF};

    auto result = modbusMaster.writeRegisters(regs, 0x00u);
    std::cout << result.what() << std::endl;
    ASSERT_TRUE(result);
    regs = {0, 0, 0};
    result = modbusMaster.writeRegisters(regs, 0x00u);
    std::cout << result.what() << std::endl;
    ASSERT_TRUE(result);
}

TEST(TEST_MASTER, WRITE_COILS) {
    modbus::Master modbusMaster("127.0.0.1");
    std::vector<bool> coils = {true, false, true, false, false, true};


    auto result = modbusMaster.writeCoils(coils, 0x00u);
    std::cout << result.what() << std::endl;
    ASSERT_TRUE(result);
    coils = {false, false, false, false, false, false};
    result = modbusMaster.writeCoils(coils, 0x00u);
    std::cout << result.what() << std::endl;
    ASSERT_TRUE(result);
}

TEST(TEST_MASTER, READ_COILS) {
    modbus::Master modbusMaster("127.0.0.1");
    std::vector<bool> coils;

    auto result = modbusMaster.readCoils(0x01u, 2, coils);
    std::cout << result.what() << std::endl;
    ASSERT_TRUE(result);
}

TEST(TEST_MASTER, READ_INPUTS) {
    modbus::Master modbusMaster("127.0.0.1");
    std::vector<bool> inputs;

    auto result = modbusMaster.readInputs(0x01u, 2, inputs);
    std::cout << result.what() << std::endl;
    ASSERT_TRUE(result);
}

TEST(TEST_MASTER, READ_REGS) {
    modbus::Master modbusMaster("127.0.0.1");
    std::vector<uint16_t> regs;

    auto result = modbusMaster.readHoldingRegisters(0x01u, 2, regs);
    std::cout << result.what() << std::endl;
    ASSERT_TRUE(result);
}

TEST(TEST_MASTER, READ_INPUT_REGS) {
    modbus::Master modbusMaster("127.0.0.1");
    std::vector<uint16_t> inputRegs;

    auto result = modbusMaster.readInputRegisters(0x01u, 2, inputRegs);
    std::cout << result.what() << std::endl;
    ASSERT_TRUE(result);
}
