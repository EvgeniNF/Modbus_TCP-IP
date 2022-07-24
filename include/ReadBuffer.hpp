#pragma once

#include <cstdint>
#include <cstddef>

#include <boost/asio/buffer.hpp>

#include "Buffer.hpp"

namespace modbus {

using namespace boost::asio;

class ReadBuffer : public Buffer {
   public:
    ReadBuffer(uint16_t address, uint16_t numbersRegisters, uint8_t function, uint8_t deviceId, uint16_t transactionId,
               uint16_t protocolId=0);

   public:
    Buffer createResponseBuffer() const noexcept final;
};


}
