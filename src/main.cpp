#include <argp.h>
#include "../include/note.hpp"

Note *note = new Note();
static int parseOptions(int key, char *arg,
		struct argp_state *state) {
	switch(key) {
		case 'a':
			note->add(arg);
			break;
		case 'd':
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
		{"list", 'l', 0, "List the Notes"},
		{ 0 }
		};
		struct argp argp = { options, parseOptions };
		return argp_parse(&argp, argc, argv, 0, 0, 0);
	}
}
