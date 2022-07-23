#include "Buffer.hpp"

#include <iostream>

namespace modbus {

namespace {

    inline uint8_t highByte(uint16_t value) noexcept {
        return *(reinterpret_cast<uint8_t*>(&value) + 1u);
    }

    inline uint8_t lowByte(uint16_t value) noexcept {
        return *(reinterpret_cast<uint8_t*>(&value));
    }

    inline void setValueToBuffer(uint16_t const value, uint8_t* buffer, size_t const id) noexcept {
        buffer[id] = highByte(value);
        buffer[id + 1u] = lowByte(value);
    }

    inline void setValueToBuffer(bool const value, uint8_t* buffer, size_t const id) noexcept {
        buffer[id] = value ? 0xFF : 0x00;
    }
}

void Buffer::setTransactionId(uint16_t id) noexcept {
    setValueToBuffer(id, m_buffer, 0u);
}

void Buffer::setProtocolId(uint16_t id) noexcept {
    setValueToBuffer(id, m_buffer, 2u);
}

inline void Buffer::setDeviceAddress(uint8_t address) noexcept {
    m_buffer[6u] = address;
}

inline void Buffer::setFunctionCode(uint8_t function) noexcept {
    m_buffer[7u] = function;
}

void Buffer::setAddress(uint16_t address) noexcept {
    setValueToBuffer(address, m_buffer, 8u);
}

void Buffer::setMessageLength(uint16_t length) noexcept {
    setValueToBuffer(length, m_buffer, 4u);
}

inline void Buffer::setNumberOfRegisters(uint16_t numberOfRegisters) noexcept {
    setValueToBuffer(numberOfRegisters, m_buffer, 10);
}

Buffer::~Buffer() {
    delete [] m_buffer;
}

Buffer::Buffer(coil value, uint8_t functionCode,
               uint8_t deviceId, uint16_t address, uint16_t transactionId,
               uint16_t protocolId) :
    Buffer(static_cast<reg>(value ? 0xFF00u : 0x00u), functionCode, deviceId,
           address, transactionId, protocolId) {}

Buffer::Buffer(reg value, uint8_t functionCode,
               uint8_t deviceId, uint16_t address, uint16_t transactionId,
               uint16_t protocolId) {
    constexpr uint16_t messageLength = 0x06u;
    constexpr size_t startValueId = 10u;
    m_bufferSize = 12u;
    m_buffer = new uint8_t[m_bufferSize];

    setTransactionId(transactionId);
    setProtocolId(protocolId);
    setDeviceAddress(deviceId);
    setFunctionCode(functionCode);
    setMessageLength(messageLength);
    setAddress(address);

    setValueToBuffer(value, m_buffer, startValueId);
}

Buffer::Buffer(coils const& value, uint8_t functionCode, uint8_t deviceId,
               uint16_t address, uint16_t transactionId, uint16_t protocolId) {
    constexpr size_t numOfStandardRegisters = 12;
    m_bufferSize = numOfStandardRegisters + 1 + value.size();
    m_buffer = new uint8_t[m_bufferSize];

    setTransactionId(transactionId);
    setProtocolId(protocolId);
    setDeviceAddress(deviceId);
    setFunctionCode(functionCode);
    setAddress(address);
    setMessageLength(value.size() + 7);
    setNumberOfRegisters(value.size());
    setNumOfBytes<typename coils::value_type>(value.size());

    for (size_t i = numOfStandardRegisters + 1; i < value.size() + numOfStandardRegisters + 1; ++i) {
        setValueToBuffer(value[i - numOfStandardRegisters - 1], m_buffer, i);
    }
}

Buffer::Buffer(regs const& value, uint8_t functionCode, uint8_t deviceId,
               uint16_t address, uint16_t transactionId, uint16_t protocolId) {
    constexpr size_t numOfStandardRegisters = 12;
    m_bufferSize = numOfStandardRegisters + 1 + value.size() * 2;
    m_buffer = new uint8_t[m_bufferSize];

    setTransactionId(transactionId);
    setProtocolId(protocolId);
    setDeviceAddress(deviceId);
    setFunctionCode(functionCode);
    setAddress(address);
    setMessageLength(value.size() * 2 + 7);
    setNumberOfRegisters(value.size());
    setNumOfBytes<typename regs::value_type>(value.size());

    size_t sizeInBytes = value.size() * 2;
    size_t startAddress = numOfStandardRegisters + 1;
    for (size_t i = startAddress; i < sizeInBytes + startAddress; i += 2) {
        setValueToBuffer(value[(i - startAddress) / 2 ], m_buffer, i);
    }
}

std::ostream& operator<<(std::ostream& outStream, Buffer const& buffer) noexcept {
    for (size_t i = 0; i < buffer.m_bufferSize; ++i) {
        outStream << "0x" << std::hex << (uint16_t) buffer.m_buffer[i] << " ";
    }

    return outStream;
}

const_buffer Buffer::getConstBuffer() const noexcept {
    return {m_buffer, m_bufferSize};
}
mutable_buffer Buffer::getMutableBuffer() const noexcept {
    return {m_buffer, m_bufferSize};
}

}

