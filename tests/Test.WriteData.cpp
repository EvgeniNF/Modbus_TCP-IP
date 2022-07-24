#include <gtest/gtest.h>
#include <Master.hpp>

TEST(TEST_WRITE_DATA, REGISTER) {
    modbus::Master master("127.0.0.1");
    uint16_t value = 0x2544;
    auto result = master.writeValue(value, 0x50);

    std::cout << result.what() << std::endl;
    ASSERT_TRUE(result);

    std::vector<uint16_t> readData;
    size_t const readDataSize = 1;
    result = master.readValueRegs(0x50, readData, readDataSize);

    std::cout << result.what() << std::endl;
    ASSERT_TRUE(result);

    std::cout << "Write data: " << std::hex << value << std::endl;

    std::cout << "Read data: " << std::hex << readData.at(0) << std::endl;

    ASSERT_TRUE(value == readData.at(0));
}

TEST(TEST_WRITE_DATA, REGISTERS) {
    modbus::Master master("127.0.0.1");
    std::vector<uint16_t> value = {0x2544, 0x0012, 0x3378, 0x8753};
    auto result = master.writeValue(value, 0x50);

    std::cout << result.what() << std::endl;
    ASSERT_TRUE(result);

    std::vector<uint16_t> readData;
    size_t const readDataSize = 4;
    result = master.readValueRegs(0x50, readData, readDataSize);

    std::cout << result.what() << std::endl;
    ASSERT_TRUE(result);


    for (size_t i =0; i < readDataSize; ++i) {
        std::cout << "Write data: " << std::hex << value.at(i) << std::endl;
        std::cout << "Read data: " << std::hex << readData.at(i) << std::endl;
        ASSERT_TRUE(value.at(i) == readData.at(i));
    }
}

TEST(TEST_WRITE_DATA, COIL) {
    modbus::Master master("127.0.0.1");
    bool value = true;
    auto result = master.writeValue(value, 0x50);

    std::cout << result.what() << std::endl;
    ASSERT_TRUE(result);

    std::vector<bool> readData;
    size_t const readDataSize = 1;
    result = master.readValueOutputs(0x50, readData, readDataSize);

    std::cout << result.what() << std::endl;
    ASSERT_TRUE(result);

    std::cout << "Write data: " << std::boolalpha << value << std::endl;
    std::cout << "Read data: " << std::boolalpha << readData.at(0) << std::endl;
    ASSERT_TRUE(value == readData.at(0));
}

TEST(TEST_WRITE_DATA, COILS) {
    modbus::Master master("127.0.0.1");
    std::vector<bool> value = {true, false, true, true, false, false, true};
    auto result = master.writeValue(value, 0x50);

    std::cout << result.what() << std::endl;
    ASSERT_TRUE(result);

    std::vector<bool> readData;
    size_t const readDataSize = value.size();
    result = master.readValueOutputs(0x50, readData, readDataSize);

    std::cout << result.what() << std::endl;
    ASSERT_TRUE(result);

    for (size_t i =0; i < readDataSize; ++i) {
        std::cout << "Write data: " << std::boolalpha << value.at(i) << std::endl;
        std::cout << "Read data: " << std::boolalpha << readData.at(i) << std::endl;
        std::cout << std::endl;
        ASSERT_TRUE(value.at(i) == readData.at(i));
    }

    ASSERT_TRUE(value.size() == readData.size());
}


TEST(TEST_WRITE_DATA, INPUTS) {
    modbus::Master master("127.0.0.1");
    std::vector<bool> value = {false, true, true, true, false, false, true, true, false, false, true};
    auto result = master.writeValue(value, 0x50);

    std::cout << result.what() << std::endl;
    ASSERT_TRUE(result);

    std::vector<bool> readData;
    size_t const readDataSize = value.size();
    result = master.readValueInputs(0x50, readData, readDataSize);

    std::cout << result.what() << std::endl;
    ASSERT_TRUE(result);

    ASSERT_TRUE(value.size() == readData.size());

    for (size_t i =0; i < readDataSize; ++i) {
        std::cout << "Write data: " << std::boolalpha << value.at(i) << std::endl;
        std::cout << "Read data: " << std::boolalpha << readData.at(i) << std::endl;
        std::cout << std::endl;
        ASSERT_TRUE(value.at(i) == readData.at(i));
    }
}
