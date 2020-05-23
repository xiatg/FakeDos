#include "fileManagement.h"
#include <unistd.h>
#include <map>
#include <fstream>

// 用于记录某个用户的当前路径，应作为的一部分，这样每个用户重新登陆时都会回到其登出时的状态
//map<string, string> user_route;

bool isPath(string &str){
    if (str.find("~")==0) return true;
    return false;
}

void show_content(string fakeDosFolderPath, string current_user, map<string, string> &user_route){
    //system()
    string current_route = fakeDosFolderPath+"\\"+user_route[current_user];
    system(("dir "+ current_route).c_str());
}



//暂时只允许用户在当前目录下specify 名称以创建文件夹
void make_dir(string name, string fakeDosFolderPath, string &current_user,map<string, string> &user_route){
    string current_route = fakeDosFolderPath+"\\"+user_route[current_user];
    string command1 = "cd "+ current_route;
    string command2 = "mkdir "+name;
    system((command1 + "&&" + command2).c_str());
}

// 在当前目录下依据名称创建txt文件
void make_file(string name,string fakeDosFolderPath, string &current_user,map<string, string> &user_route){
    ifstream infile;
    ofstream outfile;
    string current_route = fakeDosFolderPath+"\\"+user_route[current_user];
    string target_route = current_route + "\\" + name + ".txt";

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


// 暂时只允许change path by name; 未考虑错误输入的情况
void change_path(string name, string fakeDosFolderPath,
                 string current_user, map<string, string> &user_route){
    if (name == "u"){
        cout << "Now: "<< user_route[current_user]<<endl;
        user_route[current_user] = upper_route(user_route[current_user]);
        cout << "Now: "<< user_route[current_user]<<endl;
    }else{
        user_route[current_user] = user_route[current_user] + "\\"+ name;
        cout << "Now: "<< user_route[current_user]<<endl;
    }
}


void del_dir(string name,string fakeDosFolderPath,string current_user, map<string, string> &user_route){
    string current_route = fakeDosFolderPath+"\\"+user_route[current_user];
    string command = "rd /s /q "+ current_route + "\\" + name;
    system(command.c_str());
}

void del_file(string name, string fakeDosFolderPath,string current_user, map<string, string> &user_route){
    string current_route = fakeDosFolderPath+"\\"+user_route[current_user];
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
    string current_route = fakeDosFolderPath+"\\"+user_route[current_user];
    string command1 = "cd "+ current_route;
    string command2 = "xcopy "+ this_name + " "+ target_name +" /s /e";
    system((command1 + " && "+ command2).c_str());
}

void move(string this_name, string target_name, string fakeDosFolderPath,
              string current_user, map<string, string> &user_route){
    string current_route = fakeDosFolderPath+"\\"+user_route[current_user];
    string command1 = "cd "+ current_route;
    string command2 = "move "+ this_name + " "+ target_name;
    system((command1 + " && "+ command2).c_str());
}




