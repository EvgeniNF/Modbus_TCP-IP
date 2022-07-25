#include "Connection.hpp"

namespace modbus {

Connection::Connection(std::string const& ip, uint16_t port) :
    m_endPoint(boost::asio::ip::address::from_string(ip), port),
    m_service(),
    m_socket(m_service) {}

Result Connection::send(boost::asio::const_buffer requestBuffer,
                        boost::asio::mutable_buffer responseBuffer) noexcept {
    boost::system::error_code error;
    if (not m_socket.is_open()) {
        m_socket.connect(m_endPoint, error);
    }

    if (error.failed()) {
        return {false, error.message()};
    }
    error.clear();

    m_socket.write_some(requestBuffer, error);
    if (error.failed()) {
        return {false, error.message()};
    }
    error.clear();


    m_socket.read_some(responseBuffer, error);
    if (error.failed()) {
        return {false, error.message()};
    }

    return {true, "Success"};
}

}
