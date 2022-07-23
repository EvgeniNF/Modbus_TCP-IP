#pragma once

#include <boost/asio/buffer.hpp>

namespace modbus {

using namespace boost::asio;

class Buffer {
   using coil = bool;
   using reg = uint16_t;
   using coils = std::vector<coil>;
   using regs = std::vector<reg>;

  public:
    Buffer(reg value, uint8_t functionCode, uint8_t deviceId,
           uint16_t address, uint16_t transactionId, uint16_t protocolId=0);
    Buffer(coil value, uint8_t functionCode, uint8_t deviceId,
           uint16_t address, uint16_t transactionId, uint16_t protocolId=0);
    Buffer(coils const& value, uint8_t functionCode, uint8_t deviceId,
           uint16_t address, uint16_t transactionId, uint16_t protocolId=0);
    Buffer(regs const& value, uint8_t functionCode, uint8_t deviceId,
           uint16_t address, uint16_t transactionId, uint16_t protocolId=0);
    Buffer(Buffer&) = delete;
    Buffer(Buffer&&) = default;
    Buffer& operator=(Buffer const&) = delete;
    ~Buffer();

   public:
    [[nodiscard]] const_buffer getConstBuffer() const noexcept;
    [[nodiscard]] mutable_buffer getMutableBuffer() const noexcept;

   private:
    inline void setTransactionId(uint16_t id) noexcept;
    inline void setProtocolId(uint16_t id) noexcept;
    inline void setMessageLength(uint16_t length) noexcept;
    inline void setAddress(uint16_t address) noexcept;
    inline void setDeviceAddress(uint8_t address) noexcept;
    inline void setFunctionCode(uint8_t function) noexcept;
    inline void setNumberOfRegisters(uint16_t numberOfRegisters) noexcept;

    template <class Type>
    void setNumOfBytes(size_t size) noexcept;

    private:
    uint8_t* m_buffer   {nullptr};
    size_t m_bufferSize {0};

   public:
    friend std::ostream& operator<<(std::ostream& outStream, Buffer const& buffer) noexcept;

};

template <class Type>
void Buffer::setNumOfBytes(size_t size) noexcept {
    m_buffer[12] = static_cast<uint8_t>(sizeof(Type)) * size;
}

}// namespace modbus
