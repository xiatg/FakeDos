#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <string>
#include <vector>
#include <map>
#include <taskManagement.h>

using namespace std;
/*
 * Create a user.
 */
void create_user(vector<string> command_splited, vector<string> & user_name,
                 map<string, string> & user_password, map<string, string> & user_route,
                 string fakeDosFolderPath);

void log_in(vector<string> command_splited, vector<string> user_name,
            map<string, string> user_password, map<string, string> user_route,
            bool & is_logged_in, string & current_user,
            string & current_path, std::vector<std::string> & logged_in_users,
            string & jsonmem);

void delete_user(std::vector<std::string> command_splited,
                 std::vector<std::string> & user_name,
                 std::map<std::string, std::string> & user_password,
                 map<string, string> & user_route,
                 std::string fakeDosFolderPath,
                 std::vector<std::string> & logged_in_users,
                 std::string current_user,
                 string & jsonmem,
                 PCB_type (&mem)[100],
                 vector<PCB_type> & runningQueue,
                 vector<PCB_type> & blockQueue,
                 vector<PCB_type> & readyQueue);

void change_user(bool & is_logged_in, string & current_user);

void log_out(bool & is_logged_in,
             std::string & current_user,
             std::vector<std::string> & logged_in_users,
             string & jsonmem,
             PCB_type (&mem)[100],
             vector<PCB_type> & runningQueue,
             vector<PCB_type> & blockQueue,
             vector<PCB_type> & readyQueue);

void ls_u(std::vector<std::string> user_name);

void ls_lu(std::vector<std::string> logged_in_users);


#endif // USERMANAGEMENT_H
