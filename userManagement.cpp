#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <userManagement.h>
using namespace std;

void create_user(vector<string> command_splited, vector<string> & user_name, map<string, string> & user_password) {
    if (command_splited.size() < 3) {
        cout << "Error: Please enter valid user name and password." << endl;
        cout << "create_user (user name) (password)" << endl;
    } else {
        string username = command_splited[1];
        string password = command_splited[2];

        vector<string>::iterator it = find(user_name.begin(), user_name.end(), username);

        if (it == user_name.end()) {

            user_name.push_back(username);
            user_password[username] = password;

            cout << "Successfully created the user: " << username << endl;
            cout << "User information:" << endl;
            cout << "User name: " << username << endl;
            cout << "Password: " << password << endl;

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
