#include "ReadBuffer.hpp"

namespace modbus {

ReadBuffer::ReadBuffer(uint16_t address, uint16_t numbersRegisters, uint8_t function, uint8_t deviceId,
                       uint16_t transactionId, uint16_t protocolId) :
Buffer(12) {
    setTransactionId(transactionId);
    setProtocolId(protocolId);
    setMessageLength(0x06u);

    setDeviceAddress(deviceId);
    setFunctionCode(function);

    setDeviceAddress(address);
    setNumberOfRegisters(numbersRegisters);
}

Buffer ReadBuffer::createResponseBuffer() const noexcept {
    return Buffer(12);
}

}
