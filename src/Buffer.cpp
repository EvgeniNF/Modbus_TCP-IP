#include "Buffer.hpp"

#include <iostream>
#include "error_codes.hpp"

namespace modbus {

namespace {

    inline uint8_t highByte(uint16_t value) noexcept {
        return *(reinterpret_cast<uint8_t*>(&value) + 1u);
    }

    inline uint8_t lowByte(uint16_t value) noexcept {
        return *(reinterpret_cast<uint8_t*>(&value));
    }
}

Buffer::Buffer(size_t size) {
    m_size = size;
    m_data = new uint8_t[m_size];
}

Buffer::~Buffer() {
    delete [] m_data;
}

const_buffer Buffer::getConstBuffer() const noexcept {
    return {m_data, m_size};
}

mutable_buffer Buffer::getMutableBuffer() const noexcept {
    return {m_data, m_size};
}

void Buffer::setTransactionId(uint16_t id) noexcept {
    setValueToBuffer(id, 0u);
}

void Buffer::setProtocolId(uint16_t id) noexcept {
    setValueToBuffer(id, 2u);
}

void Buffer::setDeviceAddress(uint8_t address) noexcept {
    m_data[6u] = address;
}

void Buffer::setFunctionCode(uint8_t function) noexcept {
    m_data[7u] = function;
}

void Buffer::setAddress(uint16_t address) noexcept {
    setValueToBuffer(address, 8u);
}

void Buffer::setMessageLength(uint16_t length) noexcept {
    setValueToBuffer(length, 4u);
}

void Buffer::setNumberOfRegisters(uint16_t numberOfRegisters) noexcept {
    setValueToBuffer(numberOfRegisters, 10u);
}

bool Buffer::hasError(Buffer const& responseBuffer) const noexcept {
    return m_data[7] != responseBuffer.m_data[7];
}

std::string Buffer::getError() const noexcept {
    switch (m_data[8]) {
        case error_code::illegalFunction:
            return "Illegal function";
        case error_code::illegalDataAddress:
            return "Illegal data address";
        case error_code::illegalDataValue:
            return "Illegal data value";
        case error_code::slaveDeviceFailure:
            return "Slave device failure";
        case error_code::invalidSlaveID:
            return "Invalid slave id";
        case error_code::invalidFunction:
            return "Invalid function";
        case error_code::responseTimedOut:
            return "Response timeout";
        case error_code::invalidCRC:
            return "Invalid CRC";
        case error_code::success:
            return "Success";
        default:
            return "Unknown error";
    }
}

void Buffer::setValueToBuffer(uint16_t value, size_t id) noexcept {
    m_data[id] = highByte(value);
    m_data[id + 1u] = lowByte(value);
}

void Buffer::setValueToBuffer(bool value, size_t id) noexcept {
    m_data[id] = value;
}

std::ostream& operator<<(std::ostream& outStream, Buffer const& buffer) noexcept {
    for (size_t i = 0; i < buffer.m_size; ++i) {
        outStream << "0x" << std::hex << (uint16_t) buffer.m_data[i] << " ";
    }

    return outStream;
}

}

