
#include "pet.h"

vector<pet> Pets::readpets(){
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


void Pets::display_pets(string userid){
    vector<pet> pets = readpets();
    int idx = 0;
    cout << "\n===Your Pets===\n";
    for (const auto& i : pets){
        if (i.uid == userid){
            cout << ++idx << "Pet ID: " << i.pid;
            cout << " | Name: " << i.pname;
            cout << " | Type: " << i.ptype;
            cout << " | age: " << i.age << endl;
        }
    }
}

void Pets::display_all_pets(){
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

void Pets::add_pets(string userid){
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

string Pets::generate_pid(){
        vector<pet> pets = readpets();
        int number_part, j = 0;
        int vsize = pets.size();
        size_t numStart = 0;
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

void Pets::display_one_pet(string const& id){
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

void Pets::search_func(string const& id){
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
                cout << i.pid << "\n";
                if (i.pid == id){
                    display_one_pet(id);
                    break;
                }
            }
            cout << "ID does not exist in database. Try again..."<<endl;
            return;
        }
        return;   
    }