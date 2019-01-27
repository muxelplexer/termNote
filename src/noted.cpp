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

int notifyOnDue(bool verbose) {
    notify_init("termNote");
    while(1) {
        auto notes = note->getList();
        for (auto n: notes) {
            if (n.completed) continue;
            auto t_now = time(0);
            tm *now = localtime(&t_now);
            bool doNotify = false;
            if (verbose) std::cout << n.description << std::endl;
            for (auto & spec: n.getNotificationSpecs()) {
                bool anyTimeMatch = false, allDatesMatch = true;
                if (verbose) std::cout << "    Spec of size " << spec.size() << std::endl;
                for (auto & unit: spec) {
                    if (verbose) std::cout << std::put_time(&unit, "      %Y.%m.%d %R (%A, %B) ");
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
                                         (unit.tm_mday == -1 || unit.tm_mday == now->tm_mday) &&
                                         (unit.tm_wday == -1 || unit.tm_wday == now->tm_wday)
                                        )
                                        );
                    
                    if (verbose) std::cout << "Match: T" << timeMatches << "D" << dateMatches << std::endl;
                    if (!dateMatches) {
                        allDatesMatch = false;
                        break;
                    }
                    if (timeMatches) anyTimeMatch = true;
                }
                if (verbose) std::cout << "    Match: T" << anyTimeMatch << "D" << allDatesMatch << std::endl;
                if (allDatesMatch && anyTimeMatch) {
                    doNotify = true;
                    break;
                }
            }
            if (doNotify) {
                NotifyNotification* notif = notify_notification_new (NOTE_DUE, n.description.c_str(), 0);
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
