#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include<fileManagement.h>
#include<applicationManagement.h>

using namespace std;

void install(string appname,
             vector<string> app_list,
             string fakeDosFolderPath,
             string & current_user,
             map<string, string> & user_route
             ) {

    vector<string>::iterator it = find(app_list.begin(), app_list.end(), appname);

    if (it == app_list.end()) {
        cout << "Error: app name " << appname << " is not available in the App Store." << endl;
    } else {
        make_file(appname, fakeDosFolderPath, current_user, user_route);

//        cout << fakeDosFolderPath << endl << user_route[current_user] << endl;

        cout << "Successfully installed " << appname << " ." << endl;
    }
}

void show_apps(vector<string> app_list,
               map<string, string> app_description) {
    for (int i = 0; i < int(app_list.size()); i++) {
        string appname = app_list[i];
        cout << appname << endl;
        cout << "\t" << app_description[appname] << endl;
    }
}
