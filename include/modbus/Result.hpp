#pragma once

#include <string>

namespace modbus {

class Result {
   public:
    Result(bool success, std::string message) :
    m_isSuccess(success), m_message(std::move(message)){}

    [[nodiscard]] std::string what() const noexcept {
        return m_message;
    }

    operator bool() const noexcept {
        return m_isSuccess;
    }

   private:
    bool m_isSuccess;
    std::string m_message;
};

}
