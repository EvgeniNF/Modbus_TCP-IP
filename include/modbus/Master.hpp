#pragma once

#include "Result.hpp"

#include <memory>
#include <vector>

namespace modbus {

class WriteBuffer;
class ReadBuffer;
class Buffer;
class Connection;

class Master {
   public:
    explicit Master(std::string const& ip, uint16_t deviceId = 0x01u, uint16_t port = 502);
    Master(Master&) = delete;
    Master(Master&&) = default;
    Master& operator=(Master const&) = delete;
    Master& operator=(Master&&) = default;
    ~Master();

   public:
    Result writeCoil(bool value, uint16_t address) noexcept;
    Result writeCoils(std::vector<bool> const& value, uint16_t address) noexcept;
    Result writeRegister(uint16_t value, uint16_t address) noexcept;
    Result writeRegisters(std::vector<uint16_t> const& value, uint16_t address) noexcept;

    Result readInputs(uint16_t address, size_t numInputs, std::vector<bool>& value) noexcept;
    Result readInputs(uint16_t address, bool& value) noexcept;
    Result readCoils(uint16_t address, size_t numInputs, std::vector<bool>& value) noexcept;
    Result readCoils(uint16_t address, bool& value) noexcept;
    Result readInputRegisters(uint16_t address, size_t numInputs, std::vector<uint16_t>& value) noexcept;
    Result readInputRegisters(uint16_t address, uint16_t& value) noexcept;
    Result readHoldingRegisters(uint16_t address, size_t numInputs, std::vector<uint16_t>& value) noexcept;
    Result readHoldingRegisters(uint16_t address, uint16_t& value) noexcept;

    void setDeviceId(uint16_t deviceId) noexcept;

   private:
    Result sendBuffer(Buffer const& request, Buffer& response) noexcept;

   private:
    uint16_t m_deviceId;
    uint16_t m_transactionId;
    Connection* m_connection {nullptr};
};

}// namespace modbus
