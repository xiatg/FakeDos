#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <vector>

using namespace std;

/* Judges whether a string is a path:
 * in here, we requires a path to content "\\",
 * such as "users\xxx\xxx"
 */
bool isPath(string &str);

/* Create txt file with a specified name.
 * The file will be created under current route.
 */
void make_file(string name,string fakeDosFolderPath, string &current_user,map<string, string> &user_route);

/* Create a directory by name under current route. */
void make_dir(string name, string fakeDosFolderPath, string &current_user,map<string, string> &user_route);


/* Delete a directory or a text file under current route */
void del_dir(string name,string fakeDosFolderPath,string current_user, map<string, string> &user_route);
void del_file(string name,string fakeDosFolderPath,string current_user, map<string, string> &user_route);


/* Copy or move a text file or a directory to a target directory.
 * If the target directory is under current route, then the user can simply specify its name;
 * Otherwise, the user have to specify the "complete" (fake) route of target directory,
 * such as "users\xxx\xxx".
 */
void copy(string this_name, string target_name, string fakeDosFolderPath,
              string current_user, map<string, string> &user_route);

void move(string this_name, string target_name, string fakeDosFolderPath,
              string current_user, map<string, string> &user_route);


/* Using filestream to read and write in text files.
 */
void read(string name, string fakeDosFolderPath,
          string current_user, map<string, string> &user_route);
void write(string name, string fakeDosFolderPath,
          string current_user, map<string, string> &user_route);


/* Print out all the files and dirs' names under current directory */
void show_content(string fakeDosFolderPath, string current_user, map<string, string> &user_route );

/* Get all the names under current directory, and store them in a vector */
vector<string> getFiles(string current_route);

/* Print out the content in vector "getFiles" */
void printNames(string true_current_route, string fake_current_route);


/* create the upper route of input route.
 * For example: "users\A\B" -> "users\A";
 * If the upper route is root (fakeDos): "users" -> "(root)"
 */
string upper_route(string &current_route);

/* Change current path of a specific user to a target path.
 * If the target directory is under current route, then the user can simply specify its name;
 * Otherwise, the user have to specify the "complete" (fake) route of target directory,
 * such as "users\xxx\xxx".
 */
void change_path(string name, string fakeDosFolderPath, string current_user, map<string, string> &user_route );

#endif // FILEMANAGEMENT_H
