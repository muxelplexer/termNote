#pragma once
#include <chrono>
#include <string>
#include <string_view>

namespace termnote
{
    using time_point = std::chrono::time_point<std::chrono::system_clock>;
    class note
    {
    public:
        note(const std::string& body)
            : m_Body(std::move(body)), m_DueDate(std::chrono::system_clock::now())
        {

        }


        [[nodiscard]] inline const time_point& due_date() const
        {
            return this->m_DueDate;
        }

        [[nodiscard]] inline std::string_view body() const
        {
            return this->m_Body;
        }

    private:
        time_point m_DueDate;
        std::string m_Body;
    };
}
