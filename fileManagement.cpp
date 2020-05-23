#include "fileManagement.h"
#include <unistd.h>
#include <io.h>
#include <map>
#include <vector>
#include <fstream>

// 用于记录某个用户的当前路径，应作为的一部分，这样每个用户重新登陆时都会回到其登出时的状态
//map<string, string> user_route;

bool isPath(string &str){
    for (int i = 0; i<int(str.length()); i++){
        if (str[i]=='\\') return true;
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



//暂时只允许用户在当前目录下specify 名称以创建文件夹
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


// 暂时只允许change path by name
void change_path(string name, string fakeDosFolderPath,
                 string current_user, map<string, string> &user_route){
    string target_path;

    if (name == "u"){
        user_route[current_user] = upper_route(user_route[current_user]);
    }else{
        if (user_route[current_user] == "(root)"){
            target_path = fakeDosFolderPath+ "\\" + name;

            if (_access(target_path.c_str(),0)== -1){
                cout << "Error: Directory doesn't exist."<<endl;
                return;
            }else{
                user_route[current_user] = name;
            }

        }else{
            target_path = fakeDosFolderPath+ "\\" + user_route[current_user] + "\\"+ name;
            if (_access(target_path.c_str(),0)== -1){
                cout << "Error: Directory doesn't exist."<<endl;
                return;
            }else{
                user_route[current_user] = user_route[current_user] + "\\"+ name;
            }
        }
    }
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

    string command1 = "cd "+ current_route;
    string command2 = "move "+ this_name + " "+ target_name;
    system((command1 + " && "+ command2).c_str());
}


