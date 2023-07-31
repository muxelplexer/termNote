#include <iostream>
#include <memory>
#include <ranges>

#include "file_backend.hpp"
#include "notebook.hpp"
#include "version.hpp"

#include <argparse/argparse.hpp>
#include <stdexcept>

namespace argp = argparse;

#include "command.hpp"

std::unique_ptr<termnote::command> parse_commandline(termnote::notebook& book, const int argc, const char** argv)
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
        if (program.is_subcommand_used("list"))
        {
            return std::make_unique<termnote::list_command>();
        } else if (program.is_subcommand_used("add"))
        {
            return std::make_unique<termnote::add_command>(add_cmd.get("note"));
        } else if (program.is_subcommand_used("delete"))
        {
            return std::make_unique<termnote::delete_command>(del_cmd.get<size_t>("note_id"));
        }

        return std::make_unique<termnote::list_command>();
    } catch (const std::runtime_error& err)
    {
        std::cerr << err.what() << "\n";
        std::cerr << program;
        return nullptr;
    }

}

int main(int argc, const char** argv)
{
    termnote::file_backend back;
    termnote::notebook book{&back};

    auto cmd = parse_commandline(book, argc, argv);

    if (cmd == nullptr) return 1;

    cmd->execute(book);

    return 0;
}
