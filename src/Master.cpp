#include "Master.hpp"

#include <iostream>

#include "WriteBuffer.hpp"
#include "ReadBuffer.hpp"
#include "functions.hpp"

namespace modbus {

Master::Master(std::string const& ip, uint16_t deviceId, uint16_t port) :
    m_deviceId(deviceId), m_transactionId(1u), m_port(port),
    m_endPoint(boost::asio::ip::address::from_string(ip), m_port),
    m_service(),
    m_socket(m_service) {
    boost::system::error_code errorCode;
    m_socket.connect(m_endPoint, errorCode);

    if (errorCode.failed()) {
        throw std::runtime_error(errorCode.message());
    }
}

Result Master::writeValue(bool value, uint16_t address) noexcept {
    WriteBuffer writeBuffer(value, functions::write::coil, m_deviceId, address, m_transactionId);
    ++m_transactionId;
    return write(writeBuffer);
}

Result Master::writeValue(uint16_t value, uint16_t address) noexcept {
    WriteBuffer writeBuffer(value, functions::write::reg, m_deviceId, address, m_transactionId);
    ++m_transactionId;
    return write(writeBuffer);
}

Result Master::writeValue(std::vector<bool> const& value, uint16_t address) noexcept {
    WriteBuffer writeBuffer(value, functions::write::coils, m_deviceId, address, m_transactionId);
    ++m_transactionId;
    return write(writeBuffer);
}

Result Master::writeValue(std::vector<uint16_t> const& value, uint16_t address) noexcept {
    WriteBuffer writeBuffer(value, functions::write::regs, m_deviceId, address, m_transactionId);
    ++m_transactionId;
    return write(writeBuffer);
}

Result Master::write(WriteBuffer const& buffer) noexcept {
    if (not m_socket.is_open()) {
        return {false, "Socket was not opened"};
    }

    boost::system::error_code errorCode;
    m_socket.write_some(buffer.getConstBuffer(), errorCode);
    if (errorCode.failed()) {
        return {false, errorCode.message()};
    }
    errorCode.clear();
    auto responseBuffer = buffer.createResponseBuffer();

    m_socket.read_some(responseBuffer.getMutableBuffer(), errorCode);
    if (errorCode.failed()) {
        return {false, errorCode.message()};
    }

    if (responseBuffer.hasError(buffer)) {
        return {false, responseBuffer.getError()};
    }

    return {true, "Success"};
}

Result Master::read(ReadBuffer const& requestBuffer, Buffer& responseBuffer) {
    if (not m_socket.is_open()) {
        return {false, "Socket was not opened"};
    }

    boost::system::error_code errorCode;
    m_socket.write_some(requestBuffer.getConstBuffer(), errorCode);
    if (errorCode.failed()) {
        return {false, errorCode.message()};
    }
    errorCode.clear();

    m_socket.read_some(responseBuffer.getMutableBuffer(), errorCode);
    if (errorCode.failed()) {
        return {false, errorCode.message()};
    }

    if (responseBuffer.hasError(requestBuffer)) {
        return {false, responseBuffer.getError()};
    }

    return {true, "Success"};
}

Result Master::readValueInputs(uint16_t address, std::vector<bool>& value, size_t num) noexcept {
    ReadBuffer request(address, num, functions::read::input, m_deviceId, m_transactionId);
    Buffer response = request.createResponseBuffer();
    auto result = read(request, response);
    if (not result) {
        return result;
    }

    value = response.getBools();
    return {true, "Success"};
}

Result Master::readValueOutputs(uint16_t address, std::vector<bool>& value, size_t num) noexcept {
    ReadBuffer request(address, num, functions::read::output, m_deviceId, m_transactionId);
    Buffer response = request.createResponseBuffer();
    auto result = read(request, response);
    if (not result) {
        return result;
    }

    value = response.getBools();
    return {true, "Success"};
}

Result Master::readValueRegs(uint16_t address, std::vector<uint16_t>& value, size_t num) noexcept {
    ReadBuffer request(address, num, functions::read::regs, m_deviceId, m_transactionId);
    Buffer response = request.createResponseBuffer();
    auto result = read(request, response);
    if (not result) {
        return result;
    }

    value = response.getUInts();
    return {true, "Success"};
}

Result Master::readValueInputRegs(uint16_t address, std::vector<uint16_t>& value, size_t num) noexcept {
    ReadBuffer request(address, num, functions::read::inputRegs, m_deviceId, m_transactionId);
    Buffer response = request.createResponseBuffer();
    auto result = read(request, response);
    if (not result) {
        return result;
    }

    value = response.getUInts();
    return {true, "Success"};
}

}
