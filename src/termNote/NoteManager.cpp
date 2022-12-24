#include "termNote/NoteManager.hpp"
#include <exception>
#include <fstream>
#include <iostream>

namespace termnote
{
    NoteManager::NoteManager()
        : m_NotePath(std::move(this->get_note_directory()))
    {
        if (!fs::exists(this->m_NotePath))
            fs::create_directory(this->m_NotePath);

        if (!fs::exists(this->m_NoteFile))
        {
            std::ofstream ofile(this->m_NoteFile);
            ofile << "This is a sample note. you can run `termNote --help` to get help.\n";
            ofile.close();
        }

        this->m_Notes = std::move(this->parse_file(this->m_NoteFile));
    }

    NoteManager::~NoteManager()
    {
        std::ofstream ofstr(this->m_NoteFile);
        for (auto& note : this->m_Notes)
        {
            ofstr << note.get_description() << '\n';
        }
        ofstr.close();
    }

    fs::path NoteManager::get_note_directory()
    {
        fs::path path;
        auto xdg_dir = std::getenv("XDG_DATA_HOME");
        if (xdg_dir) path = fs::path(xdg_dir) / "termNote/";
        else path = fs::path(std::getenv("HOME")) / ".termNote/";

        return path;
    }

    std::vector<termnote::Note> NoteManager::parse_file(const fs::path file)
    {
        std::vector<termnote::Note> notes;
        if (!fs::exists(file)) return notes;
        std::string line;
        std::ifstream fstr(file);

        if (!fstr.is_open()) throw std::runtime_error("Could not open file");

        while (std::getline(fstr, line))
        {  
            notes.emplace_back(line, false);
        }
        return notes;
    }

    void NoteManager::add_note(const termnote::Note& note) noexcept
    {
        this->m_Notes.push_back(std::move(note));
    }

    void NoteManager::add_note(const std::string_view description) noexcept
    {
        this->m_Notes.emplace_back(description, false);
    }

    void NoteManager::rem_note(const std::size_t idx)
    {
        if (idx > this->m_Notes.size()) throw new std::runtime_error("Index out of Range.");
        this->m_Notes.erase(this->m_Notes.begin() + idx);
    }

    void NoteManager::write_notes(std::ostream& ostr) noexcept
    {
        std::size_t i = 0;
        for (auto& note : this->m_Notes)
        {
            ostr << '[' << i << "] " << note.get_description() << '\n';
            i++;
        }
    }

    void NoteManager::write_note(std::ostream& ostr, const std::size_t n)
    {
        if (n >= this->m_Notes.size()) throw new std::runtime_error("N out of Bounds");
        ostr << '[' << n << "] " << this->m_Notes[n].to_string() << "\n";
    }
}
