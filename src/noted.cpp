#include <argp.h>
#include <iostream>
#include <libnotify/notify.h>
#include "../include/note.hpp"
#include <stdio.h>
#include <chrono>
#include <thread>
#include <ctime>
#include <iomanip>
const char* NOTE_DUE = "One of your notes just reached its due time!";


std::unique_ptr<Note> note = std::make_unique<Note>();

bool validTime(int hour, int min) {
    return hour >= 0 && hour < 24 && min >= 0 && min < 60;
}

int notifyOnDue(bool verbose) {
    notify_init("termNote");
    
    while(1) {
        auto notes = note->getList();
        for (auto n: notes) {
            if (verbose) std::cout << n << std::endl;
            int i = 0;
            std::vector<std::vector<struct tm>> specs;
            std::istringstream ss(n), buf;
            std::string s;

            
#define READ_DATE_TO(tovec, fmt)                       \
            buf = std::istringstream(s);\
            unit = {-1, -1, -1, -1, -1, -1, -1, -1, -1};\
            buf >> std::get_time(&unit, fmt);\
            if (!buf.fail()) {\
                tovec.push_back(unit);\
                continue;\
            }
#define READ_DATE(fmt) READ_DATE_TO(spec, fmt)

            while (ss) {
                std::vector<tm> spec;
                ss >> s;
                do {
                    tm unit;
                    READ_DATE("%d.%m.%y");
                    READ_DATE("%d.%m");
                    READ_DATE("%R");
                    READ_DATE("%b");
                    READ_DATE("%a");
                } while (ss.peek() == ' ' && ss >> s);
                ss.ignore();
                if (spec.size() > 0) specs.push_back(spec);
            }
            if ((n[0] == 'x' && n[1] == ' ') || specs.size() == 0) continue;
            auto t_now = time(0);
            tm *now = localtime(&t_now);
            bool doNotify = false;
            if (verbose) std::cout << "  This note has " << specs.size() << " specs total" << std::endl;
            for (auto & spec: specs) {
                bool anyTimeMatch = false, allDatesMatch = true;
                for (auto & unit: spec) {
                    if (verbose) std::cout << std::put_time(&unit, "    %Y.%m.%d %R (%A, %B) ");
                    if (unit.tm_min == -1) {
                        unit.tm_min = 0;
                    }
                    bool timeMatches = (
                                        ((unit.tm_hour == -1) ||
                                         unit.tm_hour == now->tm_hour) &&
                                        unit.tm_min == now->tm_min
                                        );
                    
                    bool dateMatches = (
                                        (
                                         (unit.tm_year == -1 || unit.tm_year == now->tm_year) &&
                                         (unit.tm_mon == -1 || unit.tm_mon == now->tm_mon)
                                         ) &&
                                        (
                                         (unit.tm_mday == -1 || unit.tm_mday == now->tm_mday) ||
                                         (unit.tm_wday == -1 || unit.tm_wday == now->tm_wday)
                                        )
                                        );
                    
                    std::cout << "Match: T" << timeMatches << "D" << dateMatches << std::endl;
                    if (!dateMatches) {
                        allDatesMatch = false;
                        break;
                    }
                    if (timeMatches) anyTimeMatch = true;
                }
                if (verbose) std::cout << "  Match: T" << anyTimeMatch << "D" << allDatesMatch << std::endl;
                if (allDatesMatch && anyTimeMatch) {
                    doNotify = true;
                    break;
                }
            }
            if (doNotify) {
                NotifyNotification* notif = notify_notification_new (NOTE_DUE, n.c_str(), 0);
                notify_notification_set_timeout(notif, 10000); // 10 seconds
                if (!notify_notification_show(notif, 0)) {
                    std::cerr << "show has failed" << std::endl;
                    return -1;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(60));
    }
}

static int parseOptions(int key, char *arg,
        struct argp_state *state) {
    bool verbose = false;
    switch(key) {
        case 'v':
            verbose = true;
        case 'f':
            return notifyOnDue(verbose);
            break;
    }
    return 0;
}

int main(int argc, char **argv) {
    if(argc == 1) {
        if (fork() == 0)
            return notifyOnDue(false);
    }
    else {
        struct argp_option options[] = {
        {"verbose", 'v', 0, 0, "Be verbose (implies -f)"},
        {"foreground", 'f', 0, 0, "Stay in the foreground"},
        { 0 }
        };
        struct argp argp = { options, parseOptions };
        return argp_parse(&argp, argc, argv, 0, 0, 0);
    }
}
