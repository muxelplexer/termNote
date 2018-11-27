#include "../include/note.hpp"

Note::Note() {;
	std::ifstream fileTest(this->path);
	if (!fileTest.good()) {
		std::ofstream file(this->path);
		file.close();
	}	
	fileTest.close();
}	

Note::~Note() {
	
}
void Note::add(char* note) {
	this->noteFile.open(this->path, std::ios::app);
	noteFile << note << std::endl;
}

void Note::del(int delLine) {
	this->noteFile.open(this->path, std::ios::in);
	this->tempFile.open(this->tempPath, std::ios::out);
	int i = 0;
	while(std::getline(noteFile, line)) {
		if(i != delLine) {
			tempFile << line << "\n";
		}
		i++;
	}
	noteFile.close();
	tempFile.close();
	remove(this->path.c_str());
	rename(this->tempPath.c_str(),this->path.c_str());
}
void Note::list() {
	noteFile.open(path, std::ios::in);
	int i = 0;
	while(std::getline(noteFile, line)) {
		std::string newLine;
		newLine = line + "\n";
		std::cout <<"[" << i << "]"<< " " << newLine;
		i++;
	}
	noteFile.close();
}
