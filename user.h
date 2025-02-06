#pragma once
#include "source.h"

class User {
public:
    string userid;
    string pwd;
    UserRole role;
    struct nUser{
        string uid;
        string pwd;
        UserRole role;
    };
    User(string userid, string pwd, UserRole role) : userid(userid), pwd(pwd), role(role) {}
    static const string USER_FILE;
    static vector<User> readUsers();
    static void user_register(); 
    static User check_credentials(string u_id, string pass);
};
// const string User::USER_FILE = "users.txt";