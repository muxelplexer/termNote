#include "./include/note.hpp"

Note::Note() {
	path = std::strcat(getenv("$HOME"), "./termNote/");
}	

Note::~Note() {

}
void Note::add() {

}

void Note::del(int delLine) {

}

void Note::list() {
	this->noteFile.open(std::string(path + "notes"), std::ios::in);
	noteFile >> buf;
	for(auto i = buf.begin(); i != buf.end(); ++i) {
		std::cout << *i;
	}
	this->noteFile.close();
}
