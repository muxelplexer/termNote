#pragma once
#include "Note.hpp"
#include <filesystem>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>


namespace termnote
{
    namespace fs = std::filesystem;
    class NoteManager
    {
    private:
        fs::path m_NotePath;
        fs::path m_TempFile = m_NotePath / "tempNotes";
        fs::path m_NoteFile = m_NotePath / "notes";
        std::vector<termnote::Note> m_Notes;

        fs::path get_note_directory();

    public:
        NoteManager();
        ~NoteManager();

        void add_note(const termnote::Note& note) noexcept;
        void add_note(const std::string_view description) noexcept;
        void rem_note(std::size_t idx);
        
        void write_notes(std::ostream& ostr) noexcept;
        void write_note(std::ostream& ostr, const std::size_t n);

        std::vector<termnote::Note> parse_file(const fs::path file);

        [[nodiscard]] inline const std::vector<termnote::Note>& get_notes() const noexcept { return this->m_Notes; };
        [[nodiscard]] inline std::vector<termnote::Note> get_notes() noexcept { return this->m_Notes; };
    };
}