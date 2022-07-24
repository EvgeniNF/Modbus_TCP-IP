#include "WriteBuffer.hpp"

namespace modbus {

WriteBuffer::WriteBuffer(reg value, uint8_t functionCode,
                         uint8_t deviceId, uint16_t address, uint16_t transactionId,
                         uint16_t protocolId) : Buffer(12u) {
    constexpr uint16_t messageLength = 0x06u;
    constexpr size_t startValueId = 10u;

    setTransactionId(transactionId);
    setProtocolId(protocolId);
    setDeviceAddress(deviceId);
    setFunctionCode(functionCode);
    setMessageLength(messageLength);
    setAddress(address);

    setValueToBuffer(value, startValueId);
}

WriteBuffer::WriteBuffer(coil value, uint8_t functionCode,
               uint8_t deviceId, uint16_t address, uint16_t transactionId,
               uint16_t protocolId) :
    WriteBuffer(static_cast<reg>(value ? 0xFF00u : 0x00u), functionCode, deviceId,
           address, transactionId, protocolId) {}


WriteBuffer::WriteBuffer(coils const& value, uint8_t functionCode, uint8_t deviceId,
                         uint16_t address, uint16_t transactionId, uint16_t protocolId) :
    Buffer(14 + (value.size() - 1) / 8) {

    setTransactionId(transactionId);
    setProtocolId(protocolId);
    setDeviceAddress(deviceId);
    setFunctionCode(functionCode);
    setAddress(address);
    setMessageLength(7 + (value.size() + 7) / 8);
    setNumberOfRegisters(value.size());
    setNumOfBytes<typename coils::value_type>(value.size());

    for (size_t i = 0; i < value.size(); ++i) {
        m_data[(14 - 1) + i / 8u] += value[i] << (i % 8u);
    }
}

WriteBuffer::WriteBuffer(regs const& value, uint8_t functionCode, uint8_t deviceId,
                         uint16_t address, uint16_t transactionId, uint16_t protocolId) :
    Buffer(12 + 1 + value.size() * 2) {

    setTransactionId(transactionId);
    setProtocolId(protocolId);
    setDeviceAddress(deviceId);
    setFunctionCode(functionCode);
    setAddress(address);
    setMessageLength(value.size() * 2 + 7);
    setNumberOfRegisters(value.size());
    setNumOfBytes<typename regs::value_type>(value.size());

    size_t sizeInBytes = value.size() * 2;
    size_t startAddress = 12 + 1;
    for (size_t i = startAddress; i < sizeInBytes + startAddress; i += 2) {
        setValueToBuffer(value[(i - startAddress) / 2 ], i);
    }
}

Buffer WriteBuffer::createResponseBuffer() const noexcept {
    return Buffer(12);
}

}
