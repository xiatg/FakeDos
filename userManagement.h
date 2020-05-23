#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <string>
#include <vector>
#include <map>

using namespace std;
/*
 * Create a user.
 */
void create_user(vector<string> command_splited, vector<string> & user_name,
                 map<string, string> & user_password, map<string, string> & user_route,
                 string fakeDosFolderPath);

void log_in(vector<string> command_splited, vector<string> user_name,
            map<string, string> user_password, map<string, string> user_route,
            bool & is_logged_in, string & current_user, string & current_path);


void log_out(bool & is_logged_in);


#endif // USERMANAGEMENT_H
