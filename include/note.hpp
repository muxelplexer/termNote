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
		std::fstream noteFile;
		std::fstream tempFile;
		std::string noteDir = std::string(std::getenv("HOME")) + "/.termNote/";
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
