#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <map>
#include <vector>
#include "dist/json/json.h"
#include <fakeDos.h>
#include <userManagement.h>
using namespace std;

string current_user;
string current_path;

string command;

string fakeDosFolderPath;

vector<string> operation_list{
    "exit",
    "create_user",
    "log_in",
    "delete_user"
};

map<string, string> operation_syntax{
    {"create_user", "create_user (user name) (password)"},
    {"log_in", "log_in (user_name) (password)"}
};

map<string, string> operation_description{
    {"create_user", "Create a new user."},
    {"log_in", "Log in with the identity of a user."}
};

vector<string> user_name;

map<string, string> user_password;

map<string, string> user_route;

bool exitable = false;

bool is_logged_in = false;

vector<string> command_split(string command) {

    vector<string> command_splited;
    size_t next_space_pos = command.find(' ');
    while (next_space_pos != string::npos) {
        command_splited.push_back(command.substr(0, next_space_pos));
        command.erase(0, next_space_pos + 1);
        next_space_pos = command.find(' ');
    }

    command_splited.push_back(command);

    return command_splited;
}

void fakeDosPre() {

    char *buffer;
    buffer = getcwd(NULL, 0);
    string route(buffer);

    system("mkdir fakeDos");
    system("mkdir fakeDos\\system");
    system("mkdir fakeDos\\users");
    system("mkdir fakeDos\\files");

    fakeDosFolderPath = route;

}

void fakeDos() {
    cout << "fakeDos Prototype" << endl;
    cout << "System boosting..." << endl;

    fakeDosPre();

    cout << "Welcome to fakeDos! Type help for more information." << endl;

    while (exitable == false) {

        if (is_logged_in == false) {
            cout << "Please log in!" << endl;

            if (user_name.size() == 0) {
                cout << "No valid user is found. Please create a user with the following command: " << endl;
                cout << "create_user (user name) (password)" << endl;
            }
        } else {
            cout << current_user << "@" << current_path << " $";
        }

        getline(cin, command);

        /*
        //Debug
//        cout << command << endl;
        */

        vector<string> command_splited = command_split(command);
        string operation = command_splited[0];

        vector<string>::iterator it = find(operation_list.begin(), operation_list.end(), operation);

        /*
        //Debug
//        for (int i = 0; i < int(command_splited.size()); i++) {
//            cout << command_splited[i] << endl;
//        }
        */

        if (it != operation_list.end()) {

            if (operation == "create_user") {
                create_user(command_splited, user_name, user_password);
            }

            if (operation == "log_in") {
                log_in(command_splited, user_name, user_password, is_logged_in, current_user, current_path);
            }

            if (operation == "exit") {
                cout << "System shutting down..." << endl;
                exitable = true;
                break;
            }

        } else {
            cout << "Invalid command: " << operation << endl;
        }

    }

}
