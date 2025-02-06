#include "source.h"
#include "user.h"
#include "pet.h"
#include "schedule.h"

void vetMenu(string userid) {

    while (true){
        cout << "\n--- Vet Menu ---" << endl;
        cout << "1. View all pets\n"
            << "2. View all appointments\n"
            << "3. Search\n"
            << "4. Logout\n"
            << "Choice: ";
            int choice;
            while (!(cin >> choice)){
                cout << "\nInvalid input! Please try again: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
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
            while (!(cin >> choice)){
                cout << "\nInvalid input! Please try again: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

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

const string User::USER_FILE = "./data/users.txt";
const string showSchedule::SCHEDULE_FILE = "./data/schedule.txt";
const string Pets::PET_FILE = "./data/pets.txt";

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
            cout << "\nInvalid input! Please try again: ";
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