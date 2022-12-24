#include "termNote/Note.hpp"

namespace termnote
{
    Note::Note(const std::string_view description)
        : Note(description, true)
    {

    }

    Note::Note(const std::string_view note, bool completed)
        : m_Description{note}, m_Completed{completed}
    {

    }


    Note::~Note()
    {

    }


    std::string Note::to_string()
    {
        return this->m_Description;
    }

    const std::string Note::to_string() const
    {
        return this->m_Description;
    }
}