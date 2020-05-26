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
#include <fileManagement.h>
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
    "help",

/* The following are file management commands */
    "make_dir",
    "make_file",
    "del_dir",
    "del_file",

    "read",
    "write",

    "copy",
    "move",

    "show_content",
    "change_path"


};

map<string, string> operation_syntax{
    {"help", "help"},
    {"create_user", "create_user (user name) (password)"},
    {"log_in", "log_in (user_name) (password)"},
    {"log_out", "log_out"},
    {"exit", "exit"},

    {"make_dir", "make_dir (name)"},
    {"make_file", "make_file (name)"},
    {"del_dir", "del_dir (name)"},
    {"del_file", "del_file (name)"},
    {"read", "read (name)"},
    {"write", "write (name)"},
    {"copy","copy (name/path1) to (name/path2) "},
    {"move","move (name/path1) to (name/path2) "},
    {"show_content", "show_content"},
    {"change_path", "change_path (name)"}

};

map<string, string> operation_description{
    {"help", "See description and syntax for all operations."},
    {"create_user", "Create a new user."},
    {"log_in", "Log in with the identity of a user."},
    {"log_out", "Log out from the current user."},
    {"exit", "Shutdown FakeDos."},

    {"make_dir", "Create a new directory under current route."},
    {"make_file", "Create a new text file under current route."},
    {"del_dir", "Delete a directory under current route."},
    {"del_file", "Delete a txt file under current route."},
    {"read","Read a text file."},
    {"write", "Write in a text file."},
    {"copy","Copy file/dir 1 to dir 2. When copying txt file, you need to add (.txt) after its name."},
    {"move","Move file/dir 1 to dir 2. When moving txt file, you need to add (.txt) after its name."},
    {"show_content", "Show the content of current directory."},
    {"change_path", "Change current path to a specific directory. "
        "You can go to upper class directory by entering 'u', "
        "and go to root directory by entering 'rt'."}

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
    bool is_password = false;
    bool is_route = false;

    while (getline(ifs, line)) {
        if (is_username) {
            user_name.push_back(line);
            username = line;
            is_username = false;
            is_password = true;

        } else if (is_password){
            user_password[username] = line;
            is_password = false;
            is_route = true;
        } else if (is_route){
            user_route[username] = line;
            is_route = false;
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


        string userRoute = user_route[username];


        for (int j = 0; j < int(username.size()); j++) {
            ofs.put(username[j]);
        }
        ofs.put('\n');

        for (int j = 0; j < int(password.size()); j++) {
            ofs.put(password[j]);
        }
        ofs.put('\n');

        for (int j = 0; j < int(userRoute.size()); j++) {
            ofs.put(userRoute[j]);
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

void fakeDos() { // fakeDos main process
    cout << "fakeDos Prototype" << endl;
    cout << "System boosting..." << endl;

    fakeDosPre();

    cout << "Welcome to fakeDos! Type help for more information." << endl;


    //cout << fakeDosFolderPath<<endl;
    //cout << usersFilePath<<endl;


    while (exitable == false) {

        if (is_logged_in == false) {
            cout << "Please log in with the following command: " << endl;
            cout << "\tlog_in (username) (password)" << endl;

            if (user_name.size() == 0) {
                cout << "No valid user is found. Please create a user with the following command: " << endl;
                cout << "\tcreate_user (user name) (password)" << endl;
            }
        } else {

            current_path = user_route[current_user];
            cout << current_user << "@" << current_path << " $";
        }

        getline(cin, command); // read the command as a whole line

        /*
        //Debug
//        cout << command << endl;
        */

        vector<string> command_splited = command_split(command); // split the command by blank space
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
                create_user(command_splited, user_name, user_password, user_route, fakeDosFolderPath);
            }

            if (operation == "log_out") {
                log_out(is_logged_in);
            }

            if (operation == "log_in") {
                log_in(command_splited, user_name, user_password, user_route, is_logged_in, current_user, current_path);
            }

            if (operation == "exit") {
                exit();
                exitable = true;
                break;
            }


            if (operation == "make_dir"){
                string name = command_splited[1];
                make_dir(name, fakeDosFolderPath, current_user, user_route);
            }

            if (operation == "make_file"){
                string name = command_splited[1];
                make_file(name,fakeDosFolderPath,current_user,user_route);
            }

            if (operation == "del_dir"){
                string name = command_splited[1];
                del_dir(name,fakeDosFolderPath, current_user,user_route);
            }

            if (operation == "del_file"){
                string name = command_splited[1];
                del_file(name,fakeDosFolderPath,current_user,user_route);
            }

            if (operation == "read"){
                string name = command_splited[1];
                read(name,fakeDosFolderPath,current_user,user_route);
            }

            if (operation == "write"){
                string name = command_splited[1];
                write(name,fakeDosFolderPath,current_user,user_route);
            }

            if (operation == "copy"){
                string this_name = command_splited[1];
                string taregt_name = command_splited[2];
                copy(this_name,taregt_name,fakeDosFolderPath,current_user,user_route);
            }

            if (operation == "move"){
                string this_name = command_splited[1];
                string taregt_name = command_splited[2];
                move(this_name,taregt_name,fakeDosFolderPath,current_user,user_route);
            }

            if (operation == "show_content"){
                show_content(fakeDosFolderPath,current_user,user_route);
            }

            if (operation == "change_path"){
                string name = command_splited[1];
                change_path(name,fakeDosFolderPath,current_user,user_route);
            }


        } else {
            cout << "Invalid command: " << operation << endl;
        }

    }

}
