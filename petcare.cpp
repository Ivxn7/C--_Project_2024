#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <limits>
#include <ctime>
using namespace std;

enum class UserRole { VET, OWNER, ADMIN, INVALID };


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
    static vector<User> readUsers(){
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
    static void user_register(){
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
    
    static User check_credentials(string u_id, string pass){
        vector<User> users = readUsers();
        for (const auto& user: users){
            if (user.userid == u_id && user.pwd == pass){
                return user;
            }
        }
        return {"", "", UserRole::INVALID};
    }
};

class Pets: public User{
public:
    static const string PET_FILE;
    static vector<pet> readpets(){
        vector<pet> pets;
        ifstream file(PET_FILE);
        string line;

        while (getline(file, line)){
            stringstream ss(line);
            string uid, pid, pname, ptype;
            int age;
            char deli = ',';

            getline(ss, uid, deli);
            getline(ss, pid, deli);
            getline(ss, pname, deli);
            getline(ss, ptype, deli);
            ss >> age;
            ss.ignore();

            pets.push_back({uid, pid, pname, ptype, age});
            // pets.emplace_back(uid, pid, pname, ptype, age);
        }
        file.close();
        return pets;
    }

    static void display_pets(string userid){
        vector<pet> pets = readpets();
        int idx = 0;
        cout << "\n===Your Pets===\n";
        for (const auto& i : pets){
            if (i.uid == userid){
                cout << ++idx << "Pet ID: " << i.pid;
                cout << " | Name: " << i.pname;
                cout << " | age: " << i.age << endl;
            }
        }
    }
    static void display_all_pets(){
        vector<pet> pets = readpets();
        cout << "\n===All Pets===\n";
        for (const auto& i : pets){
            cout << "Owner: " << i.uid;
            cout << " | Pet ID: " << i.pid;
            cout << " | Name: " << i.pname;
            cout << " | Type: " << i.ptype;
            cout << " | age: " << i.age << endl;
        }
    }
    static void add_pets(string userid){
        ofstream file(PET_FILE, ios::app);
        pet newpet;
        
        while (true){
            cout << "\n===Register your new pet===\n";
            cout << "Pet Name: ";
            cin >> newpet.pname;
            cin.ignore(numeric_limits <streamsize>::max(), '\n');
            cout << "Pet Type: ";
            getline(cin, newpet.ptype);
            cout << "Pet Age: ";
            while(!(cin >> newpet.age)){
                cout << "Invalid Input! Please try again: ";
                cin.clear();
                cin.ignore(numeric_limits <streamsize>::max(), '\n');
            }
            break;
        }
        newpet.pid = generate_pid();
        file << "\n" << userid << "," << newpet.pid<< "," << newpet.pname << "," << newpet.ptype << "," << newpet.age;
        return;
    }

    static string generate_pid(){
        vector<pet> pets = readpets();
        int number_part, j = 0;
        int vsize = pets.size();
        int numStart = 0;
        string prefix, numeric, new_num;
        for (const auto& i : pets){
            j++;
            if (j == vsize){
                while(numStart < i.pid.size() && !isdigit(i.pid[numStart])){
                    numStart++;
                }
                prefix = i.pid.substr(0, numStart);
                numeric = i.pid.substr(1);

                number_part = stoi(numeric);
                number_part++;

                new_num = to_string(number_part);
                
            }
        }
        return prefix + new_num;
    }

    static void display_one_pet(string const& id){
        vector<pet> pets = readpets();
        cout << "\n==="<<"Pet: "<< id <<"===\n";
        for (const auto& i : pets){
            if (i.pid == id){
                cout << " | Name: " << i.pname;
                cout << " | Type: " << i.ptype;
                cout << " | age: " << i.age << endl;
                break;
            }
        }
    }

    static void search_func(string const& id){
        vector<User> users = readUsers();
        vector<pet> pets = readpets();
        string nested;
        char cont;
        
        if (id == "q"){
            cout << "Stop searching...";
            return;
        }
        else{
            for (const auto& i : users){
                if (i.userid == id && i.role == UserRole::OWNER){
                    cout << "===============\n";
                    cout << "Owner: "<<i.userid<<endl;
                    // cout << "---------------";
                    for (const auto& j : pets){
                        if (j.uid == id ){
                            cout << "---------------";
                            cout <<"\nPet ID: "<<j.pid;
                            cout <<"\nPet Name: "<<j.pname<<endl;
                        }
                    }
                    do{
                        cout << "===============";
                        cout << "\nEnter Pet ID to check for more information: ";
                        cin >> nested;
                        if (nested == "q") {
                            cout <<"Stop searching..."; 
                            break;
                        }
                        search_func(nested);
                        cout << "\nDo you want to search again? (y/n): ";
                        cin >> cont;

                    }while (toupper(cont) == 'Y');
                    return;
                }
            }
            for (const auto& i : pets){
                if (i.pid == id){
                    display_one_pet(id);
                    break;
                }
                else{
                    cout << "ID does not exist in database. Try again..."<<endl;
                    return;
                }
            }
        }
        return;   
    }
};

class showSchedule : public Pets{
private:
    static const string SCHEDULE_FILE;
    static vector<schedule> readSchedule(){
        vector<schedule> schdl;
        ifstream file(SCHEDULE_FILE); 
        string line;

        while(getline(file, line)){
            stringstream ss(line);
            string uid, pid, pname, reason, date, time;
            char delimiter = ',';

            getline(ss, uid, delimiter);
            getline(ss, pid, delimiter);
            getline(ss, pname, delimiter);
            getline(ss, reason, delimiter);
            getline(ss, date, delimiter);
            getline(ss, time, delimiter);
            schdl.push_back({uid, pid, pname, reason, date, time});
        }
        file.close();
        return schdl;
    }

public:
    static void show_all(){
        vector<schedule> schdl = readSchedule();
        cout << "\n===All Schedule===\n";
        for (const auto& i : schdl){
            cout << "Owner: " << i.uid
                 << " | Pet ID: " << i.pid 
                 << " | Pet Name: " << i.pname
                 << " | Reason: " << i.reason
                 << " | Date: " << i.date
                 << " | Time: " << i.time << endl;
        }
    }

    static void show_owner_schedule(string const& userid){
        vector<schedule> schdl = readSchedule();
        cout << "\n===Your Schedule===\n";
        for (const auto& i : schdl){
            if (i.uid == userid){
                cout << "Owner: " << i.uid
                    << " | Pet ID: " << i.pid 
                    << " | Pet Name: " << i.pname
                    << " | Reason: " << i.reason
                    << " | Date: " << i.date
                    << " | Time: " << i.time << endl;
            }
        }
    }
    static void make_appointment(string const& userid){
        ofstream file(SCHEDULE_FILE, ios::app);
        vector<pet> pets = readpets();
        display_pets(userid);
        string selected, areason;
        int dd;
        
        cout <<"\nDisclaimer: You can only make an appointment for maximum 3 days in the future.";
        cout <<"\nWhich pet do you wish to make an appointment for? (Enter Pet ID): ";
        cin >> selected;
        for (const auto& i : pets){
            if (i.uid == userid && i.pid == selected){
                cout << "Pick a day: ";
                time_t t = time(0);   // get time now
                tm* now = localtime(&t);
                string year = to_string(now->tm_year + 1900);
                string month = to_string(now->tm_mon + 1);
                string day = to_string(now->tm_mday);
                cout << "\n1. "<<year<<"-"<<month<<"-"<<stoi(day)+1;
                cout << "\n2. "<<year<<"-"<<month<<"-"<<stoi(day)+2;
                cout << "\n3. "<<year<<"-"<<month<<"-"<<stoi(day)+3;

                while (true){
                    cout << "\nChoice: ";
                    cin >> dd;
                    if (dd >= 4 || cin.fail()){
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cout <<"Invalid input! Please select 1, 2 or 3.";
            
                    }
                    else{
                        cout <<"You are going to make an appointment on: "<<year<<"-"<<month<<"-"<<stoi(day)+dd;
                        cin.ignore(numeric_limits <streamsize>::max(), '\n');
                        cout << "\nPlease state your reason: ";
                        getline(cin, areason);
                        cout <<"\nConfirm? (y/n): ";
                        char choice;
                        cin >> choice;
                        if (tolower(choice)== 'y'){
                            string sday;
                            schedule nschdl;
                            sday = to_string(stoi(day)+dd);
                            nschdl.uid = userid;
                            nschdl.pid = i.pid;
                            nschdl.pname = i.pname;
                            nschdl.reason = areason;
                            nschdl.date = year+'-'+month+'-'+sday;
                            nschdl.time= "10:00AM";
                            file << "\n"<< nschdl.uid << ','<<nschdl.pid<<','<<nschdl.pname<<','<<nschdl.reason<<','<<nschdl.date<<','<<nschdl.time;
                            file.close();
                            return;
                        }
                        else if(tolower(choice) == 'n'){
                            cout <<"\nExiting...";
                            return;
                        } 
                    }      
                    }
                }
            }
            cout <<"\nPet ID does not exist in our database. Exiting...\n";
            return;    
    }

};

const string User::USER_FILE = "users.txt";
const string showSchedule::SCHEDULE_FILE = "schedule.txt";
const string Pets::PET_FILE = "pets.txt";

void vetMenu(string userid) {

    while (true){
        cout << "\n--- Vet Menu ---" << endl;
        cout << "1. View all pets\n"
            << "2. View all appointments\n"
            << "3. Search\n"
            << "4. Logout\n"
            << "Choice: ";
            int choice;
            cin >> choice;
            string id;

            switch (choice){
                case 1:
                    Pets::display_all_pets();
                    break;
                case 2:
                    showSchedule::show_all();
                    break;
                case 3:
                    cout << "\nSearch info by ID (q to exit): ";
                    cin >> id;
                    Pets::search_func(id);
                    break;
                case 4:
                    cout << "Logging out..."<< endl;
                    return; 
            }

    }
}

void ownerMenu(string userid) {
    while (true){
        cout << "\n--- Owner Menu ---" << endl;
        cout << "1. View my pets\n"
            << "2. View appointment\n"
            << "3. Add new pet\n"
            << "4. Make appointment\n"
            << "5. Logout\n"
            << "Choice: ";
            int choice;
            cin >> choice;

            switch (choice){
                case 1:
                    Pets::display_pets(userid);
                    break;
                case 2:
                    showSchedule::show_owner_schedule(userid);
                    break;
                case 3:
                    Pets::add_pets(userid);
                    break;
                case 4:
                    showSchedule::make_appointment(userid);
                    break;
                case 5:
                    cout << "Logging out..."<<endl;
                    return ;
                default:
                    break;
            }
    }
}

int main(){
    string u_id;
    string pass;
    int choice;

    while (true){
        cout << "\nWelcome to Pet Care Pro\n"
             << "1. Register\n"
             << "2. Login\n"
             << "3. Exit\n"
             << "Choice: ";
        while (!(cin >> choice)){
            cout << "\nInvalid input: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice){
            case 1:
                User::user_register();
                break;
            case 2: {
                cout <<"----Login----"<<endl;
                cout <<"UserID: ";
                cin >> u_id;
                cout <<"Password: ";
                cin >> pass;

                User users = User::check_credentials(u_id, pass);
                if (users.role != UserRole::INVALID){
                    if (users.role == UserRole::VET){
                        cout<< "\nHELLO VET: "<<users.userid<<endl;
                        vetMenu(users.userid);
                        break;
                    }
                    else if (users.role == UserRole::OWNER){
                        cout<< "\nHELLO OWNER: "<<users.userid<<endl;
                        ownerMenu(users.userid);
                        break;

                    }
                }
                else {
                    cout <<"UserID or Password does not match our database!"<<endl;
                }
                break;
            }
            case 3:
                cout << "Exiting system..."<<endl;
                return 0;
            default:
                cout <<"Invalid Choice!"<<endl;
        }
    }
}