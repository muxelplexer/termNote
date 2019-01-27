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
#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>	/* getenv */
#include <vector>

#define HOME std::getenv("HOME")
#define XDG_CONFIG_HOME std::getenv("XDG_CONFIG_HOME")
#define XDG_DATA_HOME std::getenv("XDG_DATA_HOME")

class todoTxtNote {
private:
    static tm * parseTime(std::string s, const char* format);
    std::vector<std::string> words;
public:
    bool completed = false;
    char priority = 'z';
    tm * createdAt = nullptr;
    tm * completedAt = nullptr;
    std::string description;
    
    std::string toString();
    
    std::vector<std::vector<tm>> getNotificationSpecs();
    std::vector<std::string> getProjects(), getContexts();
    
    todoTxtNote(std::string raw);
    ~todoTxtNote();
};

class Note {
private:
    // Filestreams
    std::fstream noteStream;
    std::fstream tempStream;
        
    // Files and Directories
    std::string configDir = XDG_CONFIG_HOME ? std::string(XDG_CONFIG_HOME) + "/termNote/" : std::string(HOME) + "/.config/termNote/";
    std::string noteDir = XDG_DATA_HOME ? std::string(XDG_DATA_HOME) + "/termNote/" : std::string(HOME) + "/.termNote/";
    std::string tempFile = noteDir + "tempNotes";
    std::string file = noteDir + "notes";
    std::string configFile = configDir + "config";
    
    std::string line;
public:
    Note();
    ~Note();
    
    void add(char* note);
    void del(std::vector<int> numbers);
    void list(bool show_completed);
    void show(int n);
    void complete(int n);
    
    std::vector<todoTxtNote> getList();
};
