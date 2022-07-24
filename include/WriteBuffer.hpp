#pragma once

#include "Buffer.hpp"

namespace modbus {

class WriteBuffer : public Buffer {
   public:
    using coil = bool;
    using reg = uint16_t;
    using coils = std::vector<coil>;
    using regs = std::vector<reg>;

   public:
    WriteBuffer(reg value, uint8_t functionCode, uint8_t deviceId,
           uint16_t address, uint16_t transactionId, uint16_t protocolId=0);
    WriteBuffer(coil value, uint8_t functionCode, uint8_t deviceId,
           uint16_t address, uint16_t transactionId, uint16_t protocolId=0);
    WriteBuffer(coils const& value, uint8_t functionCode, uint8_t deviceId,
           uint16_t address, uint16_t transactionId, uint16_t protocolId=0);
    WriteBuffer(regs const& value, uint8_t functionCode, uint8_t deviceId,
           uint16_t address, uint16_t transactionId, uint16_t protocolId=0);

   public:
    Buffer createResponseBuffer() const noexcept final;

   private:
    template <class Type>
    std::enable_if_t<std::is_same_v<Type, bool>> setNumOfBytes(size_t size) noexcept;
    template <class Type>
    std::enable_if_t<std::is_same_v<Type, uint16_t>> setNumOfBytes(size_t size) noexcept;

};

template <class Type>
std::enable_if_t<std::is_same_v<Type, uint16_t>> WriteBuffer::setNumOfBytes(size_t size) noexcept {
    m_data[12] = static_cast<uint8_t>(sizeof(uint16_t)) * size;
}

template <class Type>
std::enable_if_t<std::is_same_v<Type, bool>> WriteBuffer::setNumOfBytes(size_t size) noexcept {
    m_data[12] = static_cast<uint8_t>((size + 7) / 8);
}

}
