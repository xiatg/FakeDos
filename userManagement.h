#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <string>
#include <vector>
#include <map>

/*
 * Create a user.
 */
void create_user(std::vector<std::string> command_splited,
                 std::vector<std::string> & user_name,
                 std::map<std::string, std::string> & user_password,
                 std::map<std::string, std::string> & user_route,
                 std::string fakeDosFolderPath);

void log_in(std::vector<std::string> command_splited,
            std::vector<std::string> user_name,
            std::map<std::string, std::string> user_password,
            std::map<std::string, std::string> user_route,
            bool & is_logged_in,
            std::string & current_user,
            std::string & current_path);

void log_out(bool & is_logged_in);

#endif // USERMANAGEMENT_H
