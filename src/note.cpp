#include "../include/note.hpp"

Note::Note() {
	
}	

Note::~Note() {

}
void Note::add() {
	
}

void Note::del(int delLine) {

}

void Note::list() {
	this->noteFile.open(this->path, std::ios::in);
	int i = 0;
	while(std::getline(noteFile, line)) {
		std::string newLine;
		newLine = line + "\n";
		std::cout <<"[" << i << "]" << newLine;
		buf.push_back(newLine);
		i++;
	}
	this->noteFile.close();
}
