#include "Master.hpp"

#include "Buffer.hpp"
#include "functions.hpp"

namespace modbus {

Master::Master(std::string const& ip, uint16_t deviceId, uint16_t port) :
    m_deviceId(deviceId), m_transactionId(0), m_port(port),
    m_endPoint(boost::asio::ip::make_address(ip), m_port),
    m_service(),
    m_socket(m_service, m_endPoint) {
    boost::system::error_code errorCode;
    m_socket.open(m_endPoint.protocol(), errorCode);

    if (errorCode.failed()) {
        throw std::runtime_error(errorCode.message());
    }
}

bool Master::writeValue(bool value, uint16_t address) noexcept {
    if (m_socket.is_open()) {
        return false;
    }

    boost::system::error_code errorCode;
    Buffer writeBuffer(value, functions::write::coil, m_deviceId, address, m_transactionId);
    m_socket.write_some(writeBuffer.getConstBuffer(), errorCode);
    if (errorCode.failed()) {
        return false;
    }
    errorCode.clear();

    m_socket.read_some(writeBuffer.getMutableBuffer(), errorCode);
    if (errorCode.failed()) {
        return false;
    }

    return true;
}

}
