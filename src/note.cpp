#include <algorithm>
#include "../include/note.hpp"

Note::Note() {
    // Look if termNote directories and files exist, if not then create them
    if(fs::exists(this->noteDir) != 1) {
        fs::create_directory(this->noteDir);
    }
    std::ifstream iFileTest(this->file);
    if (!iFileTest.good()) {
        std::ofstream oFileTest(this->file);
        oFileTest << "This is a sample note. You can run `termNote --help` to get help. ";
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

void Note::del(std::vector<int> numbers) {
    std::sort(numbers.begin(), numbers.end());
    this->noteStream.open(this->file, std::ios::in);
    this->tempStream.open(this->tempFile, std::ios::out);
    int i = 0;
    int j = 0;
    while(std::getline(noteStream, line)) {
        if(i != numbers[j]) {
            tempStream << line << "\n";
        } else j++;
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
    noteStream.close();
}

std::vector<std::string> Note::getList() {
    noteStream.open(file, std::ios::in);
    std::vector<std::string> result;
    while(std::getline(noteStream, line))
        result.push_back(line);
    noteStream.close();
    return result;
}
