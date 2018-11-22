#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>	/* strcat */
#include <cstdlib>	/* getenv */
#include <vector>
#include <iterator>

class Note {
	private:
		std::fstream noteFile;
		std::string path = std::strcat(getenv("HOME"), "/.termNote/notes");
		int delLine;
		std::string line;
		std::vector<std::string> buf;
	public:
		Note();
		~Note();

		void add(char* note);
		void del(int delLine);
		void list();
};
