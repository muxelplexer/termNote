#include "notebook.hpp"
#include "note.hpp"
#include <algorithm>
#include <iostream>
#include <ranges>

#include "command.hpp"

namespace termnote
{
    void notebook::add_note(const std::string& view)
    {
        this->m_Notes.emplace_back(std::move(view));
    }

    void notebook::delete_note(const size_t n)
    {
        if (n > this->m_Notes.size() - 1)
        {
            std::cerr << "Index too big.\n";
            return;
        }

        this->m_Notes.erase(this->m_Notes.begin() + n);
    }

    std::vector<std::string_view> notebook::get_notes() const
    {
        auto test = m_Notes | std::views::transform(&termnote::note::body);
        return {test.begin(), test.end()};
    }

    void notebook::run_command(std::unique_ptr<termnote::command>& cmd)
    {
        cmd->execute(*this);
    }
}
