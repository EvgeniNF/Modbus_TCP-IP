#pragma once

#include <cstdint>

namespace modbus {

namespace functions {

    namespace write {

        static constexpr uint8_t singleCoil        = 0x05u;
        static constexpr uint8_t multipleCoils     = 0xFu;
        static constexpr uint8_t singleRegister    = 0x06u;
        static constexpr uint8_t multipleRegisters = 0x10u;

    }// namespace write

    namespace read {

        static constexpr uint8_t coil             = 0x01u;
        static constexpr uint8_t input            = 0x02u;
        static constexpr uint8_t holdingRegisters = 0x03u;
        static constexpr uint8_t inputRegisters   = 0x04u;

    }// namespace read

}// namespace functions

}// namespace modbus
