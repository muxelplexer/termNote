#include <argp.h>
#include "../include/note.hpp"

std::unique_ptr<Note> note = std::make_unique<Note>();

static int parseOptions(int key, char *arg,
                        struct argp_state *state) {
    switch(key) {
        case 'l':
            note->list();
            break;
        case 'a':
            note->add(arg);
            break;
        case 's':
            note->show(std::strtol(arg, nullptr, 0));
            break;
        case 'd':
            std::vector<int> numbers;
            std::stringstream ss(arg);
            int i;
            while (ss >> i)
            {
                numbers.push_back(i);
                if (ss.peek() == ',')
                    ss.ignore();
            }
            note->del(numbers);
            break;
    }
    return 0;
}

int main(int argc, char **argv) {
    if(argc == 1) {
        note->list();
    }
    else {
        struct argp_option options[] = {
        {"add", 'a', "string", 0, "Add an entry"},
        {"delete", 'd', "int", 0, "Delete [n]th entry"},
        {"delete", 'd', "list", 0, "Delete [n]th entries"},
        {"list", 'l', 0, 0, "List all entries"},
        {"show", 's', "int", 0, "Show [n]th entry"},
        { 0 }
        };
        struct argp argp = { options, parseOptions };
        return argp_parse(&argp, argc, argv, 0, 0, 0);
    }
}
