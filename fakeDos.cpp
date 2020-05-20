#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <map>
#include <vector>
#include <io.h>
#include <direct.h>
#include <fakeDos.h>
#include <userManagement.h>
using namespace std;

string current_user;
string current_path;

string command;

string fakeDosFolderPath;
//string fileFolderPath;
//string systemFolderPath;
string usersFilePath;

vector<string> operation_list{
    "exit",
    "create_user",
    "log_in",
//    "delete_user",
    "log_out",
    "help"
};

map<string, string> operation_syntax{
    {"help", "help"},
    {"create_user", "create_user (user name) (password)"},
    {"log_in", "log_in (user_name) (password)"},
    {"log_out", "log_out"},
    {"exit", "exit"}
};

map<string, string> operation_description{
    {"help", "See description and syntax for all operations."},
    {"create_user", "Create a new user."},
    {"log_in", "Log in with the identity of a user."},
    {"log_out", "Log out from the current user."},
    {"exit", "Shutdown FakeDos."}
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

void read_users() {
    ifstream ifs;
    ifs.open((usersFilePath).c_str());
    string line;
    string username;
    bool is_username = true;
    while (getline(ifs, line)) {
        if (is_username) {
            user_name.push_back(line);
            username = line;
            is_username = false;
        } else {
            user_password[username] = line;
            is_username = true;
        }
    }
    ifs.close();
}

void write_users() {
    ofstream ofs;
    ofs.open((usersFilePath).c_str());
    for (int i = 0; i < int(user_name.size()); i++) {
        string username = user_name[i];
        string password = user_password[username];

        for (int j = 0; j < int(username.size()); j++) {
            ofs.put(username[j]);
        }
        ofs.put('\n');
        for (int j = 0; j < int(password.size()); j++) {
            ofs.put(password[j]);
        }
        ofs.put('\n');
    }
    ofs.close();
}

void fakeDosPre() {
    char *buffer;
    buffer = getcwd(NULL, 0);
    string route(buffer);

    if ((_access("fakeDos", 0)) == -1) {
        system("mkdir fakeDos");
        system("mkdir fakeDos\\system");
        system("mkdir fakeDos\\users");
        system("mkdir fakeDos\\files");
    }

    fakeDosFolderPath = route + "\\fakeDos";
    usersFilePath = fakeDosFolderPath + "\\system\\users.txt";

    if ((_access(usersFilePath.c_str(), 0) == -1)) {
        system(("type nul>" + usersFilePath).c_str());
    } else {
        read_users();
    }
}

void help() {
    for (int i = 0; i < int(operation_list.size()); i++) {
        string op = operation_list[i];
        cout << op << ": " << operation_syntax[op] << endl;
        cout << "\t" << operation_description[op] << endl;
    }
}

void exit() {
    cout << "System shutting down..." << endl << "See you next time!" << endl;
    write_users();
}

void fakeDos() {
    cout << "fakeDos Prototype" << endl;
    cout << "System boosting..." << endl;

    fakeDosPre();

    cout << "Welcome to fakeDos! Type help for more information." << endl;

    while (exitable == false) {

        if (is_logged_in == false) {
            cout << "Please log in with the following command: " << endl;
            cout << "\tlog_in (username) (password)" << endl;

            if (user_name.size() == 0) {
                cout << "No valid user is found. Please create a user with the following command: " << endl;
                cout << "\tcreate_user (user name) (password)" << endl;
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

            if (operation == "help") {
                help();
            }

            if (operation == "create_user") {
                create_user(command_splited, user_name, user_password, fakeDosFolderPath);
            }

            if (operation == "log_out") {
                log_out(is_logged_in);
            }

            if (operation == "log_in") {
                log_in(command_splited, user_name, user_password, is_logged_in, current_user, current_path);
            }

            if (operation == "exit") {
                exit();
                exitable = true;
                break;
            }

        } else {
            cout << "Invalid command: " << operation << endl;
        }

    }

}
