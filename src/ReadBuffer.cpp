#include "ReadBuffer.hpp"

#include "functions.hpp"

namespace modbus {

namespace {}

ReadBuffer::ReadBuffer(uint16_t address, uint16_t numbersRegisters,
                       uint8_t function, uint8_t deviceId,
                       uint16_t transactionId, uint16_t protocolId) :
    Buffer(numOfReadBufferRegisters) {
    setTransactionId(transactionId);
    setProtocolId(protocolId);
    setMessageLength(0x06u);

    setDeviceAddress(deviceId);
    setFunctionCode(function);

    setAddress(address);
    setNumberOfRegisters(numbersRegisters);
}

Buffer ReadBuffer::createResponseBuffer() const noexcept {
    if (m_data[7] == functions::read::coil || m_data[7] == functions::read::input) {
        return Buffer(numOfStandardRegisters + (getRegister(10)));
    } else if (m_data[7] == functions::read::holdingRegisters || m_data[7] == functions::read::inputRegisters) {
        return Buffer(numOfStandardRegisters + (getRegister(10) * 2));
    }

    return Buffer(0);
}

}// namespace modbus
