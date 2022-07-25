#include "Master.hpp"

#include <iostream>

#include "Connection.hpp"
#include "WriteBuffer.hpp"
#include "ReadBuffer.hpp"
#include "functions.hpp"

namespace modbus {

Master::Master(std::string const& ip, uint16_t deviceId, uint16_t port) :
m_deviceId(deviceId), m_transactionId(1u) {
    m_connection = new Connection(ip, port);
}

Master::~Master() {
    if (m_connection != nullptr) {
        delete m_connection;
    }
}

Result Master::writeCoil(bool value, uint16_t address) noexcept {
    WriteBuffer request(value, functions::write::singleCoil, m_deviceId, address, m_transactionId);
    Buffer response = request.createResponseBuffer();
    return sendBuffer(request, response);
}

Result Master::writeRegister(uint16_t value, uint16_t address) noexcept {
    WriteBuffer request(value, functions::write::singleRegister, m_deviceId, address, m_transactionId);
    Buffer response = request.createResponseBuffer();
    return sendBuffer(request, response);
}

Result Master::writeCoils(std::vector<bool> const& value, uint16_t address) noexcept {
    WriteBuffer request(value, functions::write::multipleCoils, m_deviceId, address, m_transactionId);
    Buffer response = request.createResponseBuffer();
    return sendBuffer(request, response);
}

Result Master::writeRegisters(std::vector<uint16_t> const& value, uint16_t address) noexcept {
    WriteBuffer request(value, functions::write::multipleRegisters, m_deviceId, address, m_transactionId);
    Buffer response = request.createResponseBuffer();
    return sendBuffer(request, response);
}

Result Master::readInputs(uint16_t address, size_t numInputs, std::vector<bool>& value) noexcept {
    ReadBuffer request(address, numInputs, functions::read::input, m_deviceId, m_transactionId);
    Buffer response = request.createResponseBuffer();
    auto result = sendBuffer(request, response);
    if (not result) {
        return result;
    }

    value = response.getBools(numInputs);
    return {true, "Success"};
}

Result Master::readInputs(uint16_t address, bool& value) noexcept {
    ReadBuffer request(address, 1, functions::read::input, m_deviceId, m_transactionId);
    Buffer response = request.createResponseBuffer();
    auto result = sendBuffer(request, response);
    if (not result) {
        return result;
    }

    value = response.getBools(1).at(0);
    return {true, "Success"};
}

Result Master::readCoils(uint16_t address, size_t numInputs, std::vector<bool>& value) noexcept {
    ReadBuffer request(address, numInputs, functions::read::coil, m_deviceId, m_transactionId);
    Buffer response = request.createResponseBuffer();
    auto result = sendBuffer(request, response);
    if (not result) {
        return result;
    }

    value = response.getBools(numInputs);
    return {true, "Success"};
}

Result Master::readCoils(uint16_t address, bool& value) noexcept {
    ReadBuffer request(address, 1, functions::read::coil, m_deviceId, m_transactionId);
    Buffer response = request.createResponseBuffer();
    auto result = sendBuffer(request, response);
    if (not result) {
        return result;
    }

    value = response.getBools(1).at(0);
    return {true, "Success"};
}

Result Master::readInputRegisters(uint16_t address, size_t numInputs, std::vector<uint16_t>& value) noexcept {
    ReadBuffer request(address, numInputs, functions::read::inputRegisters, m_deviceId, m_transactionId);
    Buffer response = request.createResponseBuffer();
    auto result = sendBuffer(request, response);
    if (not result) {
        return result;
    }

    value = response.getUInts();
    return {true, "Success"};
}

Result Master::readInputRegisters(uint16_t address, uint16_t& value) noexcept {
    ReadBuffer request(address, 1, functions::read::inputRegisters, m_deviceId, m_transactionId);
    Buffer response = request.createResponseBuffer();
    auto result = sendBuffer(request, response);
    if (not result) {
        return result;
    }

    value = response.getUInts().at(0);
    return {true, "Success"};
}

Result Master::readHoldingRegisters(uint16_t address, size_t numInputs, std::vector<uint16_t>& value) noexcept {
    ReadBuffer request(address, numInputs, functions::read::holdingRegisters, m_deviceId, m_transactionId);
    Buffer response = request.createResponseBuffer();
    auto result = sendBuffer(request, response);
    if (not result) {
        return result;
    }

    value = response.getUInts();
    return {true, "Success"};
}

Result Master::readHoldingRegisters(uint16_t address, uint16_t& value) noexcept {
    ReadBuffer request(address, 1, functions::read::holdingRegisters, m_deviceId, m_transactionId);
    Buffer response = request.createResponseBuffer();
    auto result = sendBuffer(request, response);
    if (not result) {
        return result;
    }

    value = response.getUInts().at(0);
    return {true, "Success"};
}

Result Master::sendBuffer(Buffer const& request, Buffer& response) noexcept {
    ++m_transactionId;
    Result result = m_connection->send(request.getConstBuffer(), response.getMutableBuffer());

    if (not result) {
        return result;
    }

    if (response.hasError(request)) {
        return {false, response.getError()};
    }

    return {true, "Success"};
}

void Master::setDeviceId(uint16_t deviceId) noexcept {
    m_deviceId = deviceId;
}

}
