#include "notebook.hpp"
#include <iostream>

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

    const std::vector<std::string>& notebook::get_notes() const
    {
        return this->m_Notes;
    }
}
