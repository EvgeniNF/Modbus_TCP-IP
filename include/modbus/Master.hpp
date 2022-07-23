#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace modbus {

class Master {
   public:
    explicit Master(std::string const& ip, uint16_t deviceId=1, uint16_t port=512);

   public:
    bool writeValue(bool value, uint16_t address) noexcept;

   private:
    uint16_t m_deviceId;
    uint16_t m_transactionId;
    uint16_t m_port;
    boost::asio::ip::tcp::endpoint m_endPoint;
    boost::asio::io_service m_service;
    boost::asio::ip::tcp::socket m_socket;
};

}
