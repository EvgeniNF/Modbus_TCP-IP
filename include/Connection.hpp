#pragma once

#include <boost/asio.hpp>

namespace modbus {

struct Connection {
    boost::asio::io_service service;
    std::string ip;
    uint16_t port;
};

}
