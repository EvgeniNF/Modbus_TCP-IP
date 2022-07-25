#pragma once

#include <cstdint>

namespace modbus {

namespace error_code {

    static constexpr uint8_t illegalFunction    = 0x01;
    static constexpr uint8_t illegalDataAddress = 0x02;
    static constexpr uint8_t illegalDataValue   = 0x03;
    static constexpr uint8_t slaveDeviceFailure = 0x04;
    static constexpr uint8_t success            = 0x00;
    static constexpr uint8_t invalidSlaveID     = 0xE0;
    static constexpr uint8_t invalidFunction    = 0xE1;
    static constexpr uint8_t responseTimedOut   = 0xE2;
    static constexpr uint8_t invalidCRC         = 0xE3;

}// namespace error_code

}// namespace modbus
