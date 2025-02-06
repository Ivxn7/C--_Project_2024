#include "user.h"



vector<User> User::readUsers(){
    vector<User> users;
    ifstream file(USER_FILE);
    string line;

    while(getline(file, line)){
        stringstream ss(line);
        string userid, pwd, u_role;
        UserRole role;
        char delimiter = ',';
        getline(ss, userid, delimiter);
        getline(ss, pwd, delimiter);
        getline(ss, u_role, delimiter);

        if (u_role == "vet") role = UserRole:: VET;
        else if (u_role == "owner") role = UserRole:: OWNER;
        else if (u_role == "admin") role = UserRole:: ADMIN;
        else continue;

        users.emplace_back(userid, pwd, role);
    }
    file.close();
    return users;
}

void User::user_register(){
        ofstream file(USER_FILE, ios::app);
        nUser newuser;
        char rolechoice;
        bool rep = true;

        while (rep){
            cout << "\n---Registration---\n";
            cout << "User ID: ";
            cin >> newuser.uid;

            vector<User> chkuser = readUsers();
            for (const auto& user: chkuser){
                if (user.userid == newuser.uid){
                    cout << "\nUserID already exists! Please try again!\n";
                    rep = true;
                }
                else rep = false;
            }
        }
        cout << "Enter Password: ";
        cin >> newuser.pwd;

        while (true){
            cout <<"Select role (V/v for VET, O/o for OWNER): ";
            cin >> rolechoice;
            if (tolower(rolechoice) == 'v') {
                newuser.role = UserRole::VET;
                break;
            }
            else if (tolower(rolechoice) == 'o') {
                newuser.role = UserRole::OWNER;
                break;
            }
            else {
                cout << "Invalid role selection! Please try again." << endl;
            }
        }
        file << "\n" << newuser.uid << "," << newuser.pwd << "," << (newuser.role == UserRole::VET ? "vet" : "owner");
    }

  User User::check_credentials(string u_id, string pass){
        vector<User> users = readUsers();
        for (const auto& user: users){
            if (user.userid == u_id && user.pwd == pass){
                return user;
            }
        }
        return {"", "", UserRole::INVALID};
    }