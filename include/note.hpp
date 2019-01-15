#pragma once
#define GCC_VERSION (__GNUC__ * 10000 \
                     + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__)
#if GCC_VERSION < 80000
	#include <experimental/filesystem>
	namespace fs = std::experimental::filesystem;
#else
	#include <filesystem>
	namespace fs = std::filesystem;
#endif
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>	/* getenv */
#include <vector>

class Note {
	private:
		// Filestreams
		std::fstream noteStream;
		std::fstream tempStream;
		
		// Files and Directories
		std::string configDir = std::string(std::getenv("HOME")) + "/.config/termNote/";
		std::string noteDir = std::string(std::getenv("HOME")) + "/.termNote/";
		std::string tempFile = noteDir + "tempNotes";
		std::string file = noteDir + "notes";
		std::string configFile = configDir + "config";
			
		int delLine;
		std::string line;
	public:
		Note();
		~Note();

		void add(char* note);
		void del(int delLine);
		void list();
};
