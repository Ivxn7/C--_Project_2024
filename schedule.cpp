#include "schedule.h"

vector<schedule> showSchedule::readSchedule(){
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

void showSchedule::show_all(){
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

void showSchedule::show_owner_schedule(string const& userid){
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

void showSchedule::make_appointment(string const& userid){
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