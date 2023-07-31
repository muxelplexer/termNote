#include <algorithm>
#include <filesystem>
#include <fstream>
#include <ranges>

#include <catch2/catch.hpp>

#include "file_backend.hpp"

TEST_CASE("file_backend functions", "[backend]") 
{
    const std::vector<std::string> test_notes { "Hello World!" , "This is a Test Note"};
    std::filesystem::remove("./notes");
    SECTION("successfully creates empty notes file")
    {
        termnote::file_backend back("./");
        REQUIRE(std::filesystem::exists("./notes"));
    }

    SECTION("writes notes to filesystem")
    {
        termnote::file_backend back("./");
        std::vector<termnote::note> notes{};
        for (const auto& note : test_notes)
        {
            notes.emplace_back(note);
        }
        back.write_notes(notes);
        std::ifstream fstream ("./notes");
        std::vector<std::string> lines;
        for (std::string line; std::getline(fstream, line);)
        {
            lines.push_back(line);
        }
        REQUIRE(std::ranges::equal(test_notes, lines));
   }
}
