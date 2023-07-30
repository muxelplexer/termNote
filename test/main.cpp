#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "file_backend.hpp"
#include <filesystem>

TEST_CASE("file_backend initializes correctly", "test") 
{
    SECTION("Note File Exists")
    {
        std::filesystem::remove("./notes");
        termnote::file_backend back("./");
        REQUIRE(std::filesystem::exists("./notes"));
    }
}
