#include <iostream>
#include <ranges>

#include "file_backend.hpp"
#include "notebook.hpp"
#include "version.hpp"

#include <argparse/argparse.hpp>
#include <stdexcept>

namespace argp = argparse;

int main(int argc, const char** argv)
{
    argp::ArgumentParser program("termNote", std::string(termnote::version::string));
    argp::ArgumentParser add_cmd("add");
    add_cmd.add_description("Adds note to the Database.");
    add_cmd.add_argument("note")
        .default_value(std::string(""))
        .required()
        .remaining();


    argp::ArgumentParser list_cmd("list");
    list_cmd.add_description("Lists notes in Database.");

    argp::ArgumentParser del_cmd("delete");
    del_cmd.add_description("Deletes notes in Database.");
    del_cmd.add_argument("note_id")
        .scan<'i', size_t>()
        .required();


    program.add_subparser(add_cmd);
    program.add_subparser(list_cmd);
    program.add_subparser(del_cmd);

    program.add_epilog("Bug Reports or Issues can be reported at https://github.com/muxelplexer/termnote.");

    try 
    {
        program.parse_args(argc, argv);
        termnote::file_backend back;
        termnote::notebook book{&back};

        auto list_notes = [&book] () {
            for (const auto& [idx, note] : book.get_notes() | std::views::enumerate)
            {
                std::cout << "[" << idx << "] " << note << "\n";
            }
        };

        if (program.is_subcommand_used("list"))
        {
            list_notes();
        } else if (program.is_subcommand_used("add"))
        {
            book.add_note(add_cmd.get("note"));
            book.write();
        } else if (program.is_subcommand_used("delete"))
        {
            auto& note_id = del_cmd.get<size_t>("note_id");

            book.delete_note(note_id);
            book.write();
        } else 
        {
            list_notes();
        }
    } catch (const std::runtime_error& err)
    {
        std::cerr << err.what() << "\n";
        std::cerr << program;
        return 1;
    }

    return 0;
}
