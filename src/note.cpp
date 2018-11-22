#include "../include/note.hpp"

Note::Note() {
	std::ifstream fileTest(this->path);
	if (!fileTest.good()) {
		std::ofstream file(this->path);
		file.close();
	}	
}	

Note::~Note() {
	
}
void Note::add(char* note) {
	this->noteFile.open(this->path, std::ios::app);
	noteFile << note << std::endl;
}

void Note::del(int delLine) {

}

void Note::list() {
	this->noteFile.open(this->path, std::ios::in);
	int i = 0;
	while(std::getline(noteFile, line)) {
		std::string newLine;
		newLine = line + "\n";
		std::cout <<"[" << i << "]"<< " " << newLine;
		buf.push_back(newLine);
		i++;
	}
	this->noteFile.close();
}
