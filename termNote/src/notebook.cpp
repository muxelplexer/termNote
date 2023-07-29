#include "notebook.hpp"

namespace termnote
{
    void notebook::add_note(const std::string& view)
    {
        this->m_Notes.emplace_back(std::move(view));
    }

    void notebook::delete_note(const size_t n)
    {

    }

    std::string& notebook::get_note(const size_t n)
    {

    }

    const std::vector<std::string>& notebook::get_notes() const
    {
        return this->m_Notes;
    }
}
