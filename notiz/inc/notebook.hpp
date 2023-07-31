#pragma once
#include <string>
#include <utility>
#include <vector>

#include "backend.hpp"

namespace termnote
{
    class notebook
    {
    public:
        notebook(backend* back)
            : back{back}, m_Notes(back->read_notes())
        {

        }

        notebook(const notebook&) = delete;
        notebook& operator=(const notebook&) = delete;
        ~notebook() = default;

        notebook(notebook&& book) noexcept
        {

        }

        notebook& operator=(notebook&& book) noexcept
        {
            *this = notebook(std::move(book));
            return *this;
        }

        void add_note(const std::string& view);
        void delete_note(const size_t n);
        const std::vector<std::string>& get_notes() const;
        inline void write()
        {
            this->back->write_notes(this->m_Notes);
        }
    private:
        backend* back;
        std::vector<std::string> m_Notes;
    };
}
