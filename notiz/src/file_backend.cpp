#include "file_backend.hpp"
#include "note.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <utility>

namespace fs = std::filesystem;
namespace termnote
{
    fs::path get_home_config()
    {
        const char* home = std::getenv("HOME");
        if (home == nullptr) throw "wtf?";

        return fs::path(home) / ".config" / "termNote";
    }

    file_backend::file_backend(const std::string alt_config_path)
        : m_ConfigPath{alt_config_path.empty() ? get_home_config().string() : alt_config_path}
    {
        if (!fs::exists(m_ConfigPath)) fs::create_directory(m_ConfigPath);

        auto file = fs::path(m_ConfigPath) / "notes";
        if (!fs::exists(file))
        {
            std::ofstream ofs{file};
            ofs.close();
        }
    }

    std::vector<termnote::note> file_backend::read_notes()
    {
        std::vector<termnote::note> notes{};
        auto path = fs::path(m_ConfigPath) / NOTE_FILE;
        std::ifstream ifs{path};

        for (std::string line; std::getline(ifs, line); )
        {
            notes.emplace_back(std::move(line));
        }
        return notes;
    }

    void file_backend::write_notes(const std::vector<termnote::note>& notes)
    {
        auto path = fs::path(m_ConfigPath) / NOTE_FILE;
        std::ofstream ofs{path, std::ios::trunc};
        
        for (const auto& note : notes)
        {
            ofs << note.body() << "\n";
        }

        ofs.close();
    }
}
