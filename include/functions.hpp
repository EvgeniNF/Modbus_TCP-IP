#pragma once

#include <cstdint>

namespace modbus {

namespace functions {

    namespace write {
        static constexpr uint8_t coil  = 0x05u;
        static constexpr uint8_t coils = 0xFu;
        static constexpr uint8_t reg   = 0x06u;
        static constexpr uint8_t regs  = 0x10u;
    }

    namespace read {
        static constexpr uint8_t output    = 0x01u;
        static constexpr uint8_t input     = 0x02u;
        static constexpr uint8_t regs      = 0x03u;
        static constexpr uint8_t inputRegs = 0x04u;
    }
}

}
