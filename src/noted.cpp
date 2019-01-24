#include <argp.h>
#include <iostream>
#include <libnotify/notify.h>
#include "../include/note.hpp"
#include <stdio.h>
#include <chrono>
#include <thread>
#include <ctime>
const char* NOTE_DUE = "One of your notes just reached its due time!";

char monthNames[][4] =
    {
     "jan",
     "feb",
     "mar",
     "apr",
     "may",
     "jun",
     "jul",
     "aug",
     "sep",
     "oct",
     "nov",
     "dec"
    };

char weekDays[][4] =
    {
     "mon",
     "tue",
     "wed",
     "thu",
     "fri",
     "sat",
     "sun"
    };


std::unique_ptr<Note> note = std::make_unique<Note>();

bool validTime(int hour, int min) {
    return hour >= 0 && hour < 24 && min >= 0 && min < 60;
}

struct date {
    int year = -1;
    int month = -1;
    int day = -1;
    int weekday = -1;
};

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
            std::vector<std::pair<int, int>> parsedTimeSpecs;
            std::vector<struct date> parsedDateSpecs;
            while (i < n.size() - 4) {
                int hour = -1, min = -1;
                int year = -1, month = -1, day = -1;
                // Parse time
                auto buf = n.substr(i, std::string::npos).c_str();
                if (sscanf(buf, "%2d:%2d", &hour, &min) == 2 && validTime(hour, min)) {
                    parsedTimeSpecs.push_back({hour, min});
                    i += 5;
                }
                else if (sscanf(buf, "%dAM", &hour) == 1 && validTime(hour, 0)) {
                    parsedTimeSpecs.push_back({hour, 0});
                    i += 3;
                }
                else if (sscanf(buf, "%dPM", &hour) == 1 && validTime(hour + 12, 0)) {
                    parsedTimeSpecs.push_back({hour + 12, 0});
                    i += 3;
                }
                
                // Parse date
                
                
                // Parse full date (DD.MM.YYYY)
                if (sscanf(buf, "%2d.%2d.%4d", &day, &month, &year) == 3) {
                    parsedDateSpecs.push_back({year, month, day, -1});
                    i += 10;
                }
                // Parse DD.MM
                else if (sscanf(buf, "%2d.%2d", &day, &month) == 2) {
                    parsedDateSpecs.push_back({-1, month, day, -1});
                    i += 5;
                }
                // Parse worded date definitions
                else {
                    std::vector<int> months, weekdays;
                    std::string s = n.substr(i, 4);
                    while (s[0] == ' ') {
                        auto name = n.substr(i + 1, 3);
                        i += 4;
                        for (int i = 0; i < 12; i++)
                            if (monthNames[i] == name) {
                                months.push_back(i + 1);
                                break;
                            }
                        for (int i = 0; i < 7; i++)
                            if (weekDays[i] == name) {
                                weekdays.push_back(i + 1);
                                break;
                            }
                        if (i + 5 >= n.size()) break;
                        s = n.substr(i + 1, 3);
                    }
                    if (months.size() == 0)
                        for (auto & w: weekdays)
                            parsedDateSpecs.push_back({-1, -1, -1, w});
                    if (weekdays.size() == 0)
                        for (auto & m: months)
                            parsedDateSpecs.push_back({-1, m, -1, -1});
                    for (auto & m: months)
                        for (auto & w: weekdays)
                            parsedDateSpecs.push_back({-1, m, -1, w});
                }
                
                i++;
            };
            if ((n[0] == 'x' && n[1] == ' ') || (parsedDateSpecs.size() == 0 && parsedTimeSpecs.size() == 0)) continue;
            auto t_now = time(0);
            tm *now = localtime(&t_now);
            bool dateMatches = false, timeMatches = false;
            if (parsedDateSpecs.size() == 0) dateMatches = true;
            else 
                for (auto & date: parsedDateSpecs) {
                    if (verbose) std::cout << "Date spec: y" << date.year << " m" << date.month << " d" << date.day << " w" << date.weekday << std::endl;
                    if ((date.year == -1 || date.year == now->tm_year + 1900)
                        && (date.month == -1 || date.month == now->tm_mon + 1)
                        && (date.day == -1 || date.day == now->tm_mday + 1)
                        && (date.weekday == -1 || date.weekday % 7 == now->tm_wday))
                        {
                            dateMatches = true;
                            if (verbose) std::cout << "Date matches" << std::endl;
                            break;
                        }
                }
            if (parsedTimeSpecs.size() == 0) parsedTimeSpecs.push_back({00, 00});
            for (auto & time: parsedTimeSpecs) {
                if (verbose) std::cout << "Time spec: " << time.first << ":" << time.second << std::endl;
                if (std::abs(time.first * 3600 + time.second * 60 -
                             (now->tm_hour * 3600 + now->tm_min * 60))
                    <= 60)
                    {
                        timeMatches = true;
                        if (verbose) std::cout << "Time matches" << std::endl;
                        break;
                    }
            }
            if (verbose) printf("This note has %d definitions total\n", parsedTimeSpecs.size() * parsedDateSpecs.size());
            if (timeMatches && dateMatches) {
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
