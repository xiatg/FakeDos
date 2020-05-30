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
#include <taskManagement.h>
#include <mem.h>
#include "fakeDos.h"
using namespace std;

void create_user(vector<string> command_splited, vector<string> & user_name, map<string, string> & user_password, map<string, string> & user_route, string fakeDosFolderPath) {
    if (command_splited.size() < 3) {
        cout << "Error: Please enter a valid user name and password." << endl;
        cout << "\tcreate_user (user name) (password)" << endl;
    } else {
        string username = command_splited[1];
        string password = command_splited[2];

        vector<string>::iterator it = find(user_name.begin(), user_name.end(), username);

        if (it == user_name.end()) {


            if (username == "NULL") {
                cout << "Error: you can not use NULL as user name. Try another one." << endl;
            } else {
                user_name.push_back(username);
                user_password[username] = password;
              
                string userRoute = "root\\users\\"+username;
                user_route[username] = userRoute;

                _mkdir((fakeDosFolderPath + "\\users\\" + username).c_str());

                system(("cd " + fakeDosFolderPath + "\\users\\" + username + " && " + "mklink /j files " + fakeDosFolderPath + "\\files > nul").c_str());
                system(("cd " + fakeDosFolderPath + "\\users\\" + username + " && " + "mklink /j system " + fakeDosFolderPath + "\\system > nul").c_str());

                cout << "Successfully created the user: " << username << endl;
                cout << "\tUser information:" << endl;
                cout << "\tUser name: " << username << endl;
                cout << "\tPassword: " << password << endl;

                write_users();
            }
        } else {
            cout << "Error: user name " << username << " already exists. Try another one." << endl;
        }

    }
}

void delete_user(vector<string> command_splited,
                 vector<string> & user_name,
                 map<string, string> & user_password,
                 map<string, string> & user_route,
                 string fakeDosFolderPath,
                 vector<string> & logged_in_users,
                 string current_user,
                 string & jsonmem,
                 PCB_type (&mem)[100],
                 vector<PCB_type> & runningQueue,
                 vector<PCB_type> & blockQueue,
                 vector<PCB_type> & readyQueue
                 ) {
    if (command_splited.size() < 2) {
        cout << "Error: Please enter a valid user name." << endl;
        cout << "\tdelete_user (user name)" << endl;
    } else {
        string username = command_splited[1];

        if (username == current_user) {
            cout << "Error: you can not delete yourself while logging in." << endl;
        } else {
            vector<string>::iterator it = find(user_name.begin(), user_name.end(), username);

            if (it != user_name.end()) {

                cout << "Are you sure you want to delete " << username << " ? Enter password to continue:" << endl;

                string password;

                getline(cin, password);

                if (password == user_password[username]) {
                    user_name.erase(it);
                    user_password.erase(username);
                    user_route.erase(username);
                    system(("rmdir /s /Q " + fakeDosFolderPath + "\\users\\" + username).c_str());

                    vector<string>::iterator it2 = find(logged_in_users.begin(), logged_in_users.end(), username);

                    if (it2 != logged_in_users.end()) {
                        logged_in_users.erase(it2);

                        user_mem_free(username, jsonmem);

                        for (int i = 0; i < 100; i++) {
                            if ((mem[i].state == RUNNING) || (mem[i].state == BLOCK)) {
                                if (mem[i].user_name == username) {
                                    kill(username, mem[i].id, jsonmem, mem,
                                         runningQueue, blockQueue, readyQueue);
                                }
                            }
                        }
                    }

                    cout << "Successfully deleted the user: " << username << endl;

                }
                else {
                    cout << "Error: incorrent password." << endl;
                }
            } else {
                cout << "Error: user name " << username << " does not exist." << endl;
            }
        }
    }
}

void change_user(bool & is_logged_in, string & current_user) {
    if (!is_logged_in) {
        cout << "Error: you are already in the user select panel." << endl;
    } else {
        is_logged_in = false;
        current_user = "NULL";
    }
}

void log_in(vector<string> command_splited,
            vector<string> user_name,
            map<string, string> user_password,
            map<string, string> user_route,
            bool & is_logged_in,
            string & current_user,
            string & current_path,
            vector<string> & logged_in_users,
            string & jsonmem) {
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

                    if (limit_check(0x1000, logged_in_users, jsonmem)) {

                        user_mem_alloc(username, jsonmem);

                        //Debug
//                        cout << jsonmem << endl;

                        cout << "Welcome back, " << username << "!" << endl;
                        is_logged_in = true;

                        vector<string>::iterator it_liu = find(logged_in_users.begin(), logged_in_users.end(), username);
                        if (it_liu == logged_in_users.end()) {
                            logged_in_users.push_back(username);
                        }

                        current_user = username;
                        current_path = user_route[username];

                    } else {
                        cout << "Error: insufficient memory to log in a new user." << endl;
                    }
                } else {
                    cout << "Error: incorrent password." << endl;
                }
            } else {
                cout << "Error: username " << username << " does not exist." << endl;
            }
        }
    }

}

void log_out(bool & is_logged_in,
             string & current_user,
             vector<string> & logged_in_users,
             string & jsonmem,
             PCB_type (&mem)[100],
             vector<PCB_type> & runningQueue,
             vector<PCB_type> & blockQueue,
             vector<PCB_type> & readyQueue
             ) {
    if (!is_logged_in) {
        cout << "Error: you have not logged in yet." << endl;
    } else {
        is_logged_in = false;

        vector<string>::iterator it_liu = find(logged_in_users.begin(), logged_in_users.end(), current_user);
        logged_in_users.erase(it_liu);

        user_mem_free(current_user, jsonmem);

        for (int i = 0; i < 100; i++) {
            if ((mem[i].state == RUNNING) || (mem[i].state == BLOCK)) {
                if (mem[i].user_name == current_user) {
                    kill(current_user, mem[i].id, jsonmem, mem,
                         runningQueue, blockQueue, readyQueue);
                }
            }
        }

        current_user = "NULL";

        //Debug
        cout << jsonmem << endl;

        cout << "You have logged out." << endl;
    }
}

void ls_u(vector<string> user_name) {
    cout << user_name.size() << " users exist." << endl;
    for (int i = 0; i < int(user_name.size()); i++) {
        cout << user_name[i] << endl;
    }
}

void ls_lu(vector<string> logged_in_users) {
    cout << logged_in_users.size() << " users have currently logged in." << endl;
    for (int i = 0; i < int(logged_in_users.size()); i++) {
        cout << logged_in_users[i] << endl;
    }
}
