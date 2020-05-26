#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <string>
#include <vector>
#include <map>

/*
 * Create a user.
 */
void create_user(std::vector<std::string> command_splited, std::vector<std::string> & user_name, std::map<std::string, std::string> & user_password, std::string fakeDosFolderPath);

void delete_user(std::vector<std::string> command_splited, std::vector<std::string> & user_name, std::map<std::string, std::string> & user_password, std::string fakeDosFolderPath, std::vector<std::string> & logged_in_users);

void change_user(bool & is_logged_in);

void log_in(std::vector<std::string> command_splited, std::vector<std::string> user_name, std::map<std::string, std::string> user_password, bool & is_logged_in, std::string & current_user, std::string & current_path, std::vector<std::string> & logged_in_users);

void log_out(bool & is_logged_in, std::string current_user, std::vector<std::string> & logged_in_users);

void ls_u(std::vector<std::string> user_name);

void ls_lu(std::vector<std::string> logged_in_users);

#endif // USERMANAGEMENT_H
