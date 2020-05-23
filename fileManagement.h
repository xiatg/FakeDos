#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <map>

using namespace std;

/* Judges whether a string is a path:
 * in here, we requires a path to start with ~,
 * such as ~/users
 */
bool isPath(string &str);

//_access()

/* Create txt file with a specified name.
 * User can also specifies the path of the file,
 * but by default, the file will be created under current directory
 */
void make_file(string name,string fakeDosFolderPath, string &current_user,map<string, string> &user_route);

/* Create a directory. User can create directory by either entering a name or a path*/
void make_dir(string name, string fakeDosFolderPath, string &current_user,map<string, string> &user_route);

void del_dir(string name,string fakeDosFolderPath,string current_user, map<string, string> &user_route);
void del_file(string name,string fakeDosFolderPath,string current_user, map<string, string> &user_route);


void copy(string this_name, string target_name, string fakeDosFolderPath,
              string current_user, map<string, string> &user_route);

void move(string this_name, string target_name, string fakeDosFolderPath,
              string current_user, map<string, string> &user_route);

// show the content of current directory
void show_content(string fakeDosFolderPath, string current_user, map<string, string> &user_route );


string upper_route(string &current_route);

void change_path(string name, string fakeDosFolderPath, string current_user, map<string, string> &user_route );

#endif // FILEMANAGEMENT_H
