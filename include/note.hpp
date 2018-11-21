#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>	/* strcat */
#include <cstdlib>	/* getenv */
#include <vector>

class Note {
	private:
		std::fstream noteFile;
		std::string path;
		int delLine;
		std::vector<char> buf;
	public:
		Note();
		~Note();

		void add();
		void del(int delLine);
		void list();
};
