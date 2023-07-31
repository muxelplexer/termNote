#pragma once
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <span>

#include "backend.hpp"
#include "note.hpp"

namespace termnote
{
    class command;
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

        void set_backend(backend* back)
        {
            this->back = back;
        }

        void run_command(std::unique_ptr<termnote::command>& cmd);

        void add_note(const std::string& view);
        void delete_note(const size_t n);
        std::vector<std::string_view> get_notes() const;
        inline void write()
        {
            this->back->write_notes(this->m_Notes);
        }
    private:
        backend* back;
        std::vector<termnote::note> m_Notes;
    };
}
