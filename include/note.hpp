#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>	/* getenv */
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

class Note {
	private:
		std::fstream noteStream;
		std::fstream tempStream;
		std::string noteDir = std::string(std::getenv("HOME")) + "/.termNote/";
		std::string tempFile = noteDir + "tempNotes";
		std::string file = noteDir + "notes";
		int delLine;
		std::string line;
		
	public:
		Note();
		~Note();

		void add(char* note);
		void del(int delLine);
		void list();
};
