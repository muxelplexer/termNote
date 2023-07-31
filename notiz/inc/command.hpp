#pragma once
#include "notebook.hpp"
#include <string>
#include <iostream>
#include <ranges>

namespace termnote
{
    class command
    {
    public:
        virtual ~command()
        {

        }
        virtual void execute(notebook& book) = 0;
    };

    class add_command : public command
    {
    public:
        add_command(const std::string& body)
            : m_Body{body}
        {

        }

        inline virtual void execute(notebook& book) override
        {
            book.add_note(std::move(this->m_Body));
        }

    private:
        std::string m_Body;
    };

    class delete_command : public command
    {
    public:
        delete_command(const std::size_t idx)
            : m_IDX{idx}
        {

        }

        inline virtual void execute(notebook& book) override
        {
            book.delete_note(m_IDX);
        }

    private:
        std::size_t m_IDX;
    };

    class list_command : public command
    {
    public:
        inline virtual void execute(notebook& book) override
        {
            for (const auto& [idx, note] : book.get_notes() | std::views::enumerate)
            {
                std::cout << "[" << idx << "] " << note << "\n";
            }
        }

    private:
    };

}
