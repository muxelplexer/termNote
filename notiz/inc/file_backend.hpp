#pragma once

#include <cstdlib>
#include <string>
#include <string_view>

#include "backend.hpp"
#include "note.hpp"

namespace termnote
{
    class file_backend : public backend
    {
    public:
        file_backend(const std::string alt_config_path = "");

        virtual std::vector<termnote::note> read_notes() override;
        virtual void write_notes(const std::vector<termnote::note>& notes) override;

        inline const std::string& get_config_path() const
        {
            return this->m_ConfigPath;
        }


    private:
        std::string m_ConfigPath;
        static constexpr std::string_view NOTE_FILE{"notes"};
    };
}
