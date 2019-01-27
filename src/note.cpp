#include <algorithm>
#include <iterator>

#include <chrono>
#include <ctime>
#include <iomanip>
#include "../include/note.hpp"

tm * todoTxtNote::parseTime(std::string s, const char *format) {
    std::istringstream buf(s);
    struct tm * unit = (struct tm*) malloc(sizeof(struct tm));
    unit->tm_year = -1;
    unit->tm_mon = -1;
    unit->tm_mday = -1;
    unit->tm_wday = -1;
    unit->tm_hour = -1;
    unit->tm_min = -1;
    unit->tm_sec = -1;
    buf >> std::get_time(unit, format);
    if (!buf.fail()) return unit;
    else return nullptr;
}

std::vector< std::vector<tm> > todoTxtNote::getNotificationSpecs() {
    int i = 0;
    std::vector<std::vector<struct tm>> specs;
    std::vector<tm> spec;
    for (auto & w: words) {
        tm * cur;
        if ((cur = parseTime(w, "%R")) ||
            (cur = parseTime(w, "%H%p")) ||
            (cur = parseTime(w, "%d.%m.%y")) ||
            (cur = parseTime(w, "%d.%m")) ||
            (cur = parseTime(w, "%a")) ||
            (cur = parseTime(w, "%b"))) {
            spec.push_back(*cur);
        }
        std::string sep = ",./;!%&";
        if (!cur || sep.find(w[w.size() - 1]) != std::string::npos) {
            if (spec.size() > 0)
                specs.push_back(spec);
            spec.clear();
        }
    }
    if (spec.size() > 0) specs.push_back(spec);
    return specs;
}

todoTxtNote::todoTxtNote(std::string raw) {
    std::istringstream rawstream(raw);
    words = std::vector<std::string>{std::istream_iterator<std::string>{rawstream},
                                     std::istream_iterator<std::string>{}};
    while (words.size() < 5) words.push_back("");
    short i = 0;
    if (words[i] == "x") {
        completed = true;
        i ++;
    }
    if (words[i].size() == 3 && words[i][0] == '(' && words[i][2] == ')') {
        priority = words[i][1];
        i ++;
    }

    tm * time1 = parseTime(words[i], "%Y-%m-%d");
    tm * time2 = parseTime(words[i + 1], "%Y-%m-%d");
    
    if (time1 && time2) {
        completedAt = time1;
        createdAt = time2;
        i += 2;
    } else if (time1) {
        createdAt = time1;
        i ++;
    } else {
        time_t now = std::time(0);
        createdAt = localtime(&now);
    }

    for (i; i < words.size(); i ++)
        description += words[i] + ' ';
}

todoTxtNote::~todoTxtNote() {

}

Note::Note() {
    // Look if termNote directories and files exist, if not then create them
    if(fs::exists(this->noteDir) != 1) {
        fs::create_directory(this->noteDir);
    }
    std::ifstream iFileTest(this->file);
    if (!iFileTest.good()) {
        std::ofstream oFileTest(this->file);
        oFileTest << "This is a sample note. You can run `termNote --help` to get help." << std::endl;
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
    std::cout << "These notes are going to be deleted:" << std::endl;
    while(std::getline(noteStream, line)) {
        if(i != numbers[j]) tempStream << line << "\n";
        else {
            j++;
            std::cout << '[' << i << ']' << ' ' << line << std::endl;
        }
        i++;
    }
    noteStream.close();
    tempStream.close();
    std::cout << "Type 'yes' if you would like to confirm. >>> ";
    std::string answer;
    std::cin >> answer;
    if (answer == "yes") {
        remove(this->file.c_str());
        rename(this->tempFile.c_str(), this->file.c_str());
    } else {
        std::cout << "You didn't type 'yes', no action is done" << std::endl;
        remove(this->tempFile.c_str());
        exit(1);
    }
}
std::vector<todoTxtNote> Note::getList() {
    noteStream.open(file, std::ios::in);
    std::vector<todoTxtNote> result;
    while(std::getline(noteStream, line))
        result.push_back(todoTxtNote(line));
    noteStream.close();
    return result;
}

void Note::list(bool show_completed) {
    short i = 0;
    std::vector<todoTxtNote> notes = getList();
    for (auto note: notes) {
        if (show_completed || !note.completed)
            std::cout << '[' << i << ']' << ' ' << note.description << std::endl;
        i++;
    }
}

void Note::show(int n) {
    std::cout << getList()[n].description << std::endl;
}
