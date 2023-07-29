#pragma once
#include <string>
#include <vector>

namespace termnote
{
    struct backend
    {
        virtual std::vector<std::string> read_notes() = 0;
        virtual void write_notes(const std::vector<std::string> notes) = 0;
    };
}
