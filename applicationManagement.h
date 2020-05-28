#ifndef APPLICATIONMANAGEMENT_H
#define APPLICATIONMANAGEMENT_H

#include <string>
#include <vector>
#include <map>

using namespace std;

void install(string appname,
             vector<string> app_list,
             string fakeDosFolderPath,
             string & current_user,
             map<string, string> & user_route
             );

void show_apps(vector<string> app_list,
               map<string, string> app_description);

#endif // APPLICATIONMANAGEMENT_H
