#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "Result.hpp"

namespace modbus {

class WriteBuffer;
class ReadBuffer;
class Buffer;

class Master {
   public:
    explicit Master(std::string const& ip, uint16_t deviceId=0x01u, uint16_t port=502);

   public:
    Result writeValue(bool value, uint16_t address) noexcept;
    Result writeValue(uint16_t value, uint16_t address) noexcept;
    Result writeValue(std::vector<bool> const& value, uint16_t address) noexcept;
    Result writeValue(std::vector<uint16_t> const& value, uint16_t address) noexcept;

    Result readValueInputs(uint16_t address, std::vector<bool>& value, size_t num) noexcept;
    Result readValueOutputs(uint16_t address, std::vector<bool>& value, size_t num) noexcept;
    Result readValueRegs(uint16_t address, std::vector<uint16_t>& value, size_t num) noexcept;
    Result readValueInputRegs(uint16_t address, std::vector<uint16_t>& value, size_t num) noexcept;

   private:
    Result write(WriteBuffer const& buffer) noexcept;
    Result read(ReadBuffer const& requestBuffer, Buffer& responseBuffer);

   private:
    uint16_t m_deviceId;
    uint16_t m_transactionId;
    uint16_t m_port;
    boost::asio::ip::tcp::endpoint m_endPoint;
    boost::asio::io_service m_service;
    boost::asio::ip::tcp::socket m_socket;
};

}
