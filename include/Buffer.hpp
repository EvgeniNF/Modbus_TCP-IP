#pragma once

#include <boost/asio/buffer.hpp>
#include <iostream>

namespace modbus {

using namespace boost::asio;


class Buffer {
   public:
    Buffer(size_t size);
    virtual ~Buffer();

   public:
    [[nodiscard]] const_buffer getConstBuffer() const noexcept;
    [[nodiscard]] mutable_buffer getMutableBuffer() const noexcept;
    bool hasError(Buffer const& responseBuffer) const noexcept;
    std::string getError() const noexcept;
    virtual Buffer createResponseBuffer() const noexcept { return Buffer(); }
    std::vector<bool> getBools(size_t numOfRegisters) const noexcept;
    std::vector<uint16_t> getUInts() const noexcept;

   public:
    friend std::ostream& operator<<(std::ostream& outSream, Buffer const& buffer) noexcept;

   protected:
    void setTransactionId(uint16_t id) noexcept;
    void setProtocolId(uint16_t id) noexcept;
    void setMessageLength(uint16_t length) noexcept;
    void setAddress(uint16_t address) noexcept;
    void setDeviceAddress(uint8_t address) noexcept;
    void setFunctionCode(uint8_t function) noexcept;
    void setNumberOfRegisters(uint16_t numberOfRegisters) noexcept;

   protected:
    void setValueToBuffer(uint16_t value, size_t id) noexcept;
    void setValueToBuffer(bool value, size_t id) noexcept;
    uint16_t getRegister(size_t id) const noexcept;

   protected:
    Buffer() = default;

   protected:
    uint8_t* m_data{nullptr};
    size_t m_size{0};
};

}// namespace modbus
