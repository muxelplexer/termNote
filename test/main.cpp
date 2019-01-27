#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <../include/note.hpp>

TEST_CASE( "todo.txt format is parsed", "[todoTxtNote]" ) {
    SECTION( "Full form is parsed" ) {
        todoTxtNote full("x (A) 2019-01-01 2018-02-02 This is a note!");
        REQUIRE(full.completed == true);
        REQUIRE(full.priority == 'A');
        REQUIRE(full.createdAt->tm_year == 2018 - 1900);
        REQUIRE(full.createdAt->tm_mon == 1);
        REQUIRE(full.createdAt->tm_mday == 2);
        REQUIRE(full.completedAt->tm_year == 2019 - 1900);
        REQUIRE(full.completedAt->tm_mon == 0);
        REQUIRE(full.completedAt->tm_mday == 1);
    }
    SECTION( "Simple case is handled" ) {
        todoTxtNote simple("This is a note!");
        REQUIRE(simple.completed == false);
        REQUIRE(simple.priority == 'z');
        REQUIRE(simple.completedAt == nullptr);
    }
}


TEST_CASE( "Notifications are parsed", "[todoTxtNote]" ) {
    SECTION( "Empty note doesn't generate notifications" ) {
        todoTxtNote mute("This note shouldn't generate any notifications");
        REQUIRE(mute.getNotificationSpecs().size() == 0);
    }
    SECTION( "One exact specification is parsed" ) {
        todoTxtNote one("This note should generate one notification at 02.10.2019 00:00");
        REQUIRE(one.getNotificationSpecs().size() == 1);
        REQUIRE(one.getNotificationSpecs()[0].size() == 2);
    }
    SECTION( "Multiple specifications are parsed" ) {
        todoTxtNote two("This note should generate notifications at Jan Sun 18:00, 15.05.2020 15:00");
        REQUIRE(two.getNotificationSpecs().size() == 2);
        
    }
}
