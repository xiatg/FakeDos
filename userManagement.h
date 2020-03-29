#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <string>
#include <vector>
#include <map>

/*
 * Create a user.
 */
void create_user(std::vector<std::string> command_splited, std::vector<std::string> & user_name, std::map<std::string, std::string> & user_password);

void log_in(std::vector<std::string> command_splited, std::vector<std::string> user_name, std::map<std::string, std::string> user_password, bool & is_logged_in, std::string & current_user, std::string & current_path);

#endif // USERMANAGEMENT_H
