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
		std::fstream tempFile;
		
		std::string tempPath = std::string(std::getenv("HOME")) + "/.termNote/tempNotes";
		std::string path = std::string(std::getenv("HOME")) + "/.termNote/notes";
		int delLine;
		std::string line;
		
	public:
		Note();
		~Note();

		void add(char* note);
		void del(int delLine);
		void list();
};
