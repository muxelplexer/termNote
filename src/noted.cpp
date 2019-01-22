#include <argp.h>
#include <iostream>
#include <libnotify/notify.h>
#include "../include/note.hpp"
#include <stdio.h>
#include <chrono>
#include <thread>
#include <ctime>
const char* NOTE_DUE = "One of your notes just reached its due time!";


std::unique_ptr<Note> note = std::make_unique<Note>();

int notifyOnDue(bool verbose) {
    notify_init("termNote");
    if (verbose) {
        std::cout << "List of notes:" << std::endl;
        note->list();
    }
    while(1) {
        auto notes = note->getList();
        for (auto n: notes) {
            int i = 0;
            int hour = -1, min = -1, sec = -1;
            while ((sscanf(n.substr(i, std::string::npos).c_str(), "%2d:%2d", &hour, &min) != 2 ) &&
                         i < n.size() - 1
                         ) i++;
            if (sec == -1) sec = 0;
            if (hour == -1 || min == -1) continue;
            if (verbose) printf("This note is scheduled on %2d:%2d:%2d\n", hour, min, sec);
            auto t_now = time(0);
            tm *now = localtime(&t_now);
            bool doNotify = false;
            if (std::abs(hour * 3600 + min * 60 + sec -
                            (now->tm_hour * 3600 + now->tm_min * 60 + now->tm_sec))
                    <= 60) doNotify = true;
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
