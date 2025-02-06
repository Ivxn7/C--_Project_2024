#pragma once
#include "source.h"
#include "pet.h"

class showSchedule : public Pets{
private:
    static const string SCHEDULE_FILE;
    static vector<schedule> readSchedule();

public:
    static void show_all();
    static void show_owner_schedule(string const& userid);
    static void make_appointment(string const& userid);
};

// const string showSchedule::SCHEDULE_FILE = "schedule.txt";