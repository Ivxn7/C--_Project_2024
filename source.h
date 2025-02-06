#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <limits>
#include <ctime>
using namespace std;
#ifndef SOURCE_H_
#define SOURCE_H_

struct schedule{
    string uid;
    string pid;
    string pname;
    string reason;
    string date;
    string time;
};

struct pet{
    string uid;
    string pid;
    string pname;
    string ptype;
    int age;
};

enum class UserRole { VET, OWNER, ADMIN, INVALID };
// const string User::USER_FILE = "users.txt";
// const string showSchedule::SCHEDULE_FILE = "schedule.txt";
// const string Pets::PET_FILE = "pets.txt";


#endif