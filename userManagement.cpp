#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <map>
#include <vector>
#include <io.h>
#include <direct.h>
#include <userManagement.h>
using namespace std;

void create_user(vector<string> command_splited, vector<string> & user_name, map<string, string> & user_password, string fakeDosFolderPath) {
    if (command_splited.size() < 3) {
        cout << "Error: Please enter valid user name and password." << endl;
        cout << "\tcreate_user (user name) (password)" << endl;
    } else {
        string username = command_splited[1];
        string password = command_splited[2];

        vector<string>::iterator it = find(user_name.begin(), user_name.end(), username);

        if (it == user_name.end()) {

            user_name.push_back(username);
            user_password[username] = password;
            _mkdir((fakeDosFolderPath + "\\users\\" + username).c_str());

            // Debug
//            cout << (fakeDosFolderPath + "\\users\\" + username).c_str() << endl;

            system(("cd " + fakeDosFolderPath + "\\users\\" + username + " && " + "mklink /j files " + fakeDosFolderPath + "\\files > nul").c_str());
            system(("cd " + fakeDosFolderPath + "\\users\\" + username + " && " + "mklink /j system " + fakeDosFolderPath + "\\system > nul").c_str());

            cout << "Successfully created the user: " << username << endl;
            cout << "\tUser information:" << endl;
            cout << "\tUser name: " << username << endl;
            cout << "\tPassword: " << password << endl;

        } else {
            cout << "Error: user name " << username << " already exists. Try another one." << endl;
        }

    }
}

void log_in(vector<string> command_splited, vector<string> user_name, map<string, string> user_password, bool & is_logged_in, string & current_user, string & current_path) {

    if (is_logged_in) {
        cout << "Error: you have already logged in!" << endl;
    } else {
        if (command_splited.size() < 3) {
            cout << "Error: please enter valid user name and password." << endl;
            cout << "log_in (user name) (password)" << endl;
        } else {

            string username = command_splited[1];
            string password = command_splited[2];

            vector<string>::iterator it_u = find(user_name.begin(), user_name.end(), username);

            if (it_u != user_name.end()) {
                if (user_password[username] == password) {
                    cout << "Welcome back, " << username << "!" << endl;
                    is_logged_in = true;
                    current_user = username;
                    current_path = "users\\" + username;
                } else {
                    cout << "Error: incorrent password." << endl;
                }
            } else {
                cout << "Error: incorrent user name." << endl;
            }
        }
    }

}

void log_out(bool & is_logged_in) {
    is_logged_in = false;
    cout << "You have logged out." << endl;
}
