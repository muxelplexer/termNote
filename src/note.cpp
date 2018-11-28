#include "../include/note.hpp"

Note::Note() {
	if(fs::exists(this->noteDir) != 1) {
		fs::create_directory(this->noteDir);
	}

	std::ifstream iFileTest(this->file);
	if (!iFileTest.good()) {
		std::ofstream oFileTest(this->file);
		oFileTest.close();
	}	
	iFileTest.close();
}	

Note::~Note() {
	
}

void Note::add(char* note) {
	this->noteStream.open(this->file, std::ios::app);
	noteStream << note << std::endl;
}

void Note::del(int delLine) {

	this->noteStream.open(this->file, std::ios::in);
	this->tempStream.open(this->tempFile, std::ios::out);
	
	int i = 0;
	while(std::getline(noteStream, line)) {
		if(i != delLine) {
			tempStream << line << "\n";
		}
		i++;
	}
	
	noteStream.close();
	tempStream.close();
	remove(this->file.c_str());
	rename(this->tempFile.c_str(),this->file.c_str());
}
void Note::list() {
	noteStream.open(file, std::ios::in);
	int i = 0;
	while(std::getline(noteStream, line)) {
		std::string newLine;
		newLine = line + "\n";
		std::cout <<"[" << i << "]"<< " " << newLine;
		i++;
	}
	std::cout << std::endl;
	noteStream.close();
}
