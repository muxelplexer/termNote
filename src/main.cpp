#include <argp.h>#include <exception>#include <iostream>#include "termNote/NoteManager.hpp"static termnote::NoteManager note_manager;static int parseOptions(int key, char *arg,                        struct argp_state *state) {    std::vector<std::size_t> rem_inputs;    std::size_t input_size;    try {    switch (key)    {        case 'a':            note_manager.add_note(arg);            break;        case 'd':            rem_inputs = note_manager.parse_rem_input(arg);            input_size = rem_inputs.size();            if (input_size == 1)                note_manager.rem_note(rem_inputs[0]);            else if (input_size > 1)                note_manager.rem_notes(rem_inputs);            break;        case 'l':            note_manager.write_notes(std::cout);            break;        case 's':            note_manager.write_note(std::cout, std::stoi(arg));            break;        }    }    catch (const std::exception& ex)    {        std::cout << "Error: " << ex.what() << "\n";    }    return 0;}int main(int argc, char **argv) {    if (argc == 1)    {        note_manager.write_notes(std::cout);    }    else    {        constexpr struct argp_option options[] = {            {"add", 'a', "string", 0, "Add an entry"},            {"delete", 'd', "int", 0, "Delete [n]th entry"},            {"delete", 'd', "list", 0, "Delete [n]th entries"},            {"list", 'l', 0, 0, "List all entries"},            {"show", 's', "int", 0, "Show [n]th entry"},            { 0 }        };        struct argp argp = { options, parseOptions };        return argp_parse(&argp, argc, argv, 0, 0, 0);    }}