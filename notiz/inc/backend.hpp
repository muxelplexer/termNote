#pragma once
#include <string>
#include <vector>

#include "note.hpp"

namespace termnote
{
    struct backend
    {
        virtual std::vector<termnote::note> read_notes() = 0;
        virtual void write_notes(const std::vector<termnote::note>& notes) = 0;
    };
}
