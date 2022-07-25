#pragma once

#include <boost/asio.hpp>
#include "Result.hpp"

namespace modbus {

class Connection {
   public:
    Connection(std::string const& ip, uint16_t port);
    Connection(Connection&) = delete;
    Connection(Connection&&) noexcept = delete;
    Connection& operator=(Connection const&) = delete;
    Connection& operator=(Connection&&) = delete;
    ~Connection() = default;

   public:
    Result send(boost::asio::const_buffer requestBuffer,
                boost::asio::mutable_buffer responseBuffer) noexcept;

   private:
    boost::asio::ip::tcp::endpoint m_endPoint;
    boost::asio::io_service m_service;
    boost::asio::ip::tcp::socket m_socket;
};

}
