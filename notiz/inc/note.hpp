#pragma once
#include <chrono>
#include <string>

namespace termnote
{
    using time_point = std::chrono::time_point<std::chrono::system_clock>;

    class note
    {
    public:
        note();
    private:
        time_point m_Created;
        std::string body;
    };
}
