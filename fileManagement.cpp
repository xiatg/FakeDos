#include "fileManagement.h"
#include "fakeDos.h"
#include <unistd.h>
#include <io.h>
#include <map>
#include <vector>
#include <fstream>

bool isPath(string &str){
    for (int i = 0; i<int(str.length()); i++){
        if (str[i]=='\\') return true;
    }
    return false;
}

bool find(vector<string> &fileNames, string name){
    for (int i = 0; i < int(fileNames.size()); i++){
        if (fileNames[i] == name) return true;
    }
    return false;
}

vector<string> getFiles(string current_route){
    vector<string> files;
    _finddata_t file;
    long lf;
    if ( (lf = _findfirst(current_route.c_str(), &file))== -1){
        cout << current_route<<"not found."<<endl;
    } else{
        while(_findnext(lf, &file)==0){
            if (strcmp(file.name, ".") == 0
                    || strcmp(file.name, "..") == 0) continue;
            files.push_back(file.name);
        }
    }
    _findclose(lf);
    return files;
}

void printNames(string true_current_route, string fake_current_route){
    cout << endl<<"Files and dirs under '"<<fake_current_route<<"': "<<endl;
    true_current_route = true_current_route + "\\*";
    vector<string> files = getFiles(true_current_route);
    if (files.size()==0){
        cout << "(Empty)"<<endl;
    }else{
        for (int i = 0; i< int(files.size());i++){
            cout << files[i]<<endl;
        }
    }
    cout << endl;
}

void show_content(string fakeDosFolderPath, string current_user, map<string, string> &user_route){
    //system()
    string true_current_route;
    string fake_current_route = user_route[current_user];

    if (user_route[current_user] == "(root)"){
        true_current_route = fakeDosFolderPath;
    }else {
        true_current_route = fakeDosFolderPath+"\\"+user_route[current_user];
    }
    //system(("dir "+ current_route).c_str());
    printNames(true_current_route, fake_current_route);
}



void make_dir(string name, string fakeDosFolderPath, string &current_user,map<string, string> &user_route){

    string current_route;
    if (user_route[current_user] == "(root)"){
        current_route = fakeDosFolderPath;
    }else {
        current_route = fakeDosFolderPath+"\\"+user_route[current_user];
    }

    string command1 = "cd "+ current_route;
    string command2 = "mkdir "+name;
    system((command1 + "&&" + command2).c_str());
}

// 在当前目录下依据名称创建txt文件
void make_file(string name,string fakeDosFolderPath, string &current_user,map<string, string> &user_route){
    ifstream infile;
    ofstream outfile;
    string current_route;
    string target_route;

    if (user_route[current_user] == "(root)"){
        current_route = fakeDosFolderPath;
    }else {
        current_route = fakeDosFolderPath+"\\"+user_route[current_user];
    }
    target_route = current_route + "\\" + name + ".txt";

    infile.open(target_route);
    if (!infile.fail()){
        cout << "Error: File already exists, please change another name."<<endl<<endl;
        infile.close();
    } else{
        infile.close();
        outfile.open(target_route);
        outfile.close();
        cout << "Successfully create text file "<< name
             << " under "<<user_route[current_user]<<"."<<endl<<endl;
    }

}



void change_path(string name, string fakeDosFolderPath,
                 string current_user, map<string, string> &user_route){
    string target_path;

    if (name == "u"){
        user_route[current_user] = upper_route(user_route[current_user]);
    } else if (name == "rt"){
        user_route[current_user] = "(root)";
    }   else{
        if (user_route[current_user] == "(root)"){
            target_path = fakeDosFolderPath+ "\\" + name;

            if (_access(target_path.c_str(),0)== -1){
                cout << "Error: Directory doesn't exist."<<endl;
                return;
            }else{
                user_route[current_user] = name;
            }

        }else{
            vector<string> fileNames = getFiles(fakeDosFolderPath + "\\*");

            if (isPath(name) || (find(fileNames, name))){
                target_path = fakeDosFolderPath + "\\" + name;
            }else {
                target_path = fakeDosFolderPath+ "\\" + user_route[current_user] + "\\"+ name;
            }

            if (_access(target_path.c_str(),0)== -1){
                cout << "Error: Directory doesn't exist."<<endl;
                return;
            }else{
                if (isPath(name) || (find(fileNames, name))){
                    user_route[current_user] = name;
                }else{
                    user_route[current_user] = user_route[current_user] + "\\"+ name;
                }
            }
        }
    }

    write_users();
}


void del_dir(string name,string fakeDosFolderPath,string current_user, map<string, string> &user_route){
    string current_route;

    if (user_route[current_user] == "(root)"){
        current_route = fakeDosFolderPath;
    }else {
        current_route = fakeDosFolderPath+"\\"+user_route[current_user];
    }

    string command = "rd /s /q "+ current_route + "\\" + name;
    system(command.c_str());
}

void del_file(string name, string fakeDosFolderPath,string current_user, map<string, string> &user_route){
    string current_route;

    if (user_route[current_user] == "(root)"){
        current_route = fakeDosFolderPath;
    }else {
        current_route = fakeDosFolderPath+"\\"+user_route[current_user];
    }

    string command = "del "+ current_route + "\\" + name +".txt";
    system(command.c_str());
}

string upper_route(string &current_route){
    int len = current_route.length();
    for (int i = len-1; i>=0 ; i--){
        char ch = current_route[i];
        if (ch == '\\'){
            return current_route.substr(0,i);
        }
    }
    return "(root)";
}


// Copy "this" to "target"
void copy(string this_name, string target_name, string fakeDosFolderPath,
              string current_user, map<string, string> &user_route){
    string current_route;

    if (user_route[current_user] == "(root)"){
        current_route = fakeDosFolderPath;
    }else {
        current_route = fakeDosFolderPath+"\\"+user_route[current_user];
    }

     vector<string> fileNames = getFiles(fakeDosFolderPath + "\\*");

    if (isPath(target_name) || (find(fileNames, target_name))){
        target_name = fakeDosFolderPath+"\\"+target_name;
    }

    string command1 = "cd "+ current_route;
    string command2 = "xcopy "+ this_name + " "+ target_name +" /s /e";
    system((command1 + " && "+ command2).c_str());
}

void move(string this_name, string target_name, string fakeDosFolderPath,
              string current_user, map<string, string> &user_route){
    string current_route;

    if (user_route[current_user] == "(root)"){
        current_route = fakeDosFolderPath;
    }else {
        current_route = fakeDosFolderPath+"\\"+user_route[current_user];
    }

    vector<string> fileNames = getFiles(fakeDosFolderPath + "\\*");

    if (isPath(target_name) || (find(fileNames, target_name))){
        target_name = fakeDosFolderPath+"\\"+target_name;
    }
    string command1 = "cd "+ current_route;
    string command2 = "move "+ this_name + " "+ target_name;
    system((command1 + " && "+ command2).c_str());
}


void read(string name, string fakeDosFolderPath,
          string current_user, map<string, string> &user_route){

    ifstream infile;
    ofstream outfile;
    string current_route;

    if (user_route[current_user] == "(root)"){
        current_route = fakeDosFolderPath;
    }else {
        current_route = fakeDosFolderPath+"\\"+user_route[current_user];
    }
    current_route = current_route + "\\"+ name +".txt";

    infile.open(current_route.c_str());
    if (infile.fail()){
        cout << "Error: file doesn't exist."<<endl;
        infile.close();
        return;
    }else{
        cout << "Read text file '"<<name<<"': "<<endl;
        while(true){
            string line;
            getline(infile, line);
            if(infile.fail()) break;
            cout << line << endl;
        }
        cout <<endl;
    }
}

void write(string name, string fakeDosFolderPath,
           string current_user, map<string, string> &user_route){

    ifstream infile;
    ofstream outfile;
    string current_route;

    if (user_route[current_user] == "(root)"){
        current_route = fakeDosFolderPath;
    }else {
        current_route = fakeDosFolderPath+"\\"+user_route[current_user];
    }
    current_route = current_route + "\\"+ name +".txt";

    infile.open(current_route.c_str());
    if (infile.fail()){
        cout << "Error: file doesn't exist."<<endl;
        infile.close();
        return;
    }else{
        infile.close();
        cout << "Write in text file '"<< name << "' (enter 'eee' to terminate): "<<endl;
        outfile.open(current_route.c_str(), ios::app);
        while(true){
            string line;
            getline(cin, line);
            if (line == "eee") break;
            outfile << line<<endl;

        }
    }
}
