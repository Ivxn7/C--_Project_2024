#pragma once
#include "source.h"
#include "user.h"

class Pets: public User{
public:
    static const string PET_FILE;
    static vector<pet> readpets();
    static void display_pets(string userid);
    static void display_all_pets();
    static void add_pets(string userid);
    static string generate_pid();
    static void display_one_pet(string const& id);
    static void search_func(string const& id);
};

// const string Pets::PET_FILE = "pets.txt";