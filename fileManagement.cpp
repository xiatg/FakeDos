#include "fileManagement.h"
#include "fakeDos.h"
#include <unistd.h>
#include <io.h>
#include <map>
#include <vector>
#include <fstream>



// Change a virtual route (e.g: root:\users\xxx) to a real route
string route_formating(string fakeDosFolderPath, string str){
    if (str == "root") return fakeDosFolderPath;
    return fakeDosFolderPath + "\\" + str.substr(5);
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

    true_current_route = route_formating(fakeDosFolderPath,fake_current_route);

    //system(("dir "+ current_route).c_str());
    printNames(true_current_route, fake_current_route);
}



void make_dir(string name, string fakeDosFolderPath, string &current_user,map<string, string> &user_route){

    string current_route;

    current_route = route_formating(fakeDosFolderPath, user_route[current_user]);

    cout << "current: "<<current_route<<endl;

    string command1 = "cd "+ current_route;
    string command2 = "mkdir "+name;
    system((command1 + "&&" + command2).c_str());
}

bool isTypeSpecified(string name){
    if (name.find('.') == string::npos) return false;
    return true;
}


// name 包含名称及文件类型；e.g: apple.app
void make_file(string name,string fakeDosFolderPath, string &current_user,
               map<string, string> &user_route){

    if (!isTypeSpecified(name)){
        cout << "Error: File type not specified. (e.g: .txt, .app, ...)"<<endl;
        return;
    }

    string current_route;
    current_route = route_formating(fakeDosFolderPath,user_route[current_user]);

    string command1 = "cd "+ current_route;
    string command2 = "cd > "+name;

    system((command1 + " && " + command2).c_str());

    cout << "Successfully create file "<< name
         << " under "<<user_route[current_user]<<"."<<endl<<endl;
}



/*
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
*/

string upper_route(string &current_route){
    int len = current_route.length();
    for (int i = len-1; i>=0 ; i--){
        char ch = current_route[i];
        if (ch == '\\'){
            string sub_route = current_route.substr(0,i);
            if (sub_route != "root:") return sub_route;
            else return "root";
        }
    }
    return "root";
}

// 改成开头为 "root"
bool isPath(string &str){
    if (str.find("root") == 0) return true;
    return false;
}

void change_path(string name, string fakeDosFolderPath,
                 string current_user, map<string, string> &user_route){
    string target_path;

    if (name == "u"){
        user_route[current_user] = upper_route(user_route[current_user]);
    } else if (name == "rt"){
        user_route[current_user] = "root";
    } else {

        if (isPath(name)){  //若输入为虚拟路径
            target_path = route_formating(fakeDosFolderPath, name);
            if (_access(target_path.c_str(),0)== -1){
                cout << "Error: Directory doesn't exist."<<endl;
                return;
            } else {
                user_route[current_user] = name;
            }
        } else if (isTypeSpecified(name)){ // If input is a file, e.g: xxx.txt
            cout << "Error: Input is not a directory."<<endl;
            return;
        } else { // 若输入为名称：判断当前目录下是否存在
            string current_route = route_formating(fakeDosFolderPath, user_route[current_user]);
            vector<string> fileNames = getFiles(current_route + "\\*");
            if (find(fileNames,name)){
                user_route[current_user] = user_route[current_user] + "\\"+name;
            } else {
                cout << "Error: Directory doesn't exist."<<endl;
                return;
            }
        }

    }
    write_users();
}

/*
void change_path(string name, string fakeDosFolderPath,
                 string current_user, map<string, string> &user_route){
    string target_path;

    if (name == "u"){
        user_route[current_user] = upper_route(user_route[current_user]);
    } else if (name == "rt"){
        user_route[current_user] = "root";
    } else {
        if (user_route[current_user] == "root"){
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
*/


// 添加错误input handling
void del_dir(string name,string fakeDosFolderPath,string current_user, map<string, string> &user_route){
    string current_route;

    current_route = route_formating(fakeDosFolderPath, user_route[current_user]);

    string command = "rd /s /q "+ current_route + "\\" + name;
    system(command.c_str());
}

void del_file(string name, string fakeDosFolderPath,string current_user, map<string, string> &user_route){
    string current_route;

    if (!isTypeSpecified(name)){
        cout << "Error: File type not specified. (e.g: .txt, .app...)"<<endl;
        return;
    }
    current_route = route_formating(fakeDosFolderPath, user_route[current_user]);

    string command = "del "+ current_route + "\\" + name;
    system(command.c_str());
}



// Copy "this" to "target"
void copy(string this_name, string target_name, string fakeDosFolderPath,
              string current_user, map<string, string> &user_route){
    string current_route, target_path;
    current_route = route_formating(fakeDosFolderPath, user_route[current_user]);

    vector<string> fileNames = getFiles(current_route + "\\*");

    if (!find(fileNames,this_name)){
        cout << "Error: File/directory not found." << endl;
        return;
    }else{
        if (isPath(target_name)){
            target_path = route_formating(fakeDosFolderPath, target_name);
        } else {
            target_path = user_route[current_user] + "\\" + target_name;
            target_path = route_formating(fakeDosFolderPath,target_path);
        }

        if (_access(target_path.c_str(),0)== -1){
            cout << "Error: Directory doesn't exist."<<endl;
            return;
        } else {
            if (isTypeSpecified(this_name)){
                string command1 = "cd "+ current_route;
                string command2 = "xcopy "+ this_name + " "+ target_name +" /s /e";
                system((command1 + " && "+ command2).c_str());
            } else {//若拷贝文件夹：先切换到目标路径，创建同名文件夹，再执行拷贝
                string command1 = "cd "+ target_path;
                string command2 = "md "+ this_name;
                string command3 = "cd "+ current_route;
                string command4 = "xcopy "+ this_name + " "+ target_path + "\\" + this_name +" /s /e";

                system(  (command1 + "&&"
                        + command2 + "&&"
                        + command3 + "&&"
                        + command4).c_str());
            }
        }

    }
}

void move(string this_name, string target_name, string fakeDosFolderPath,
              string current_user, map<string, string> &user_route){
    string current_route, target_path;

    current_route = route_formating(fakeDosFolderPath, user_route[current_user]);

    vector<string> fileNames = getFiles(current_route + "\\*");

    if (!find(fileNames,this_name)){
        cout << "Error: File/directory not found." << endl;
        return;
    } else {
        if (!isPath(target_name)) target_name = user_route[current_user] + "\\" + target_name;

        target_path = route_formating(fakeDosFolderPath,target_name);


        if (_access(target_path.c_str(),0)== -1){
            cout << "Error: Directory doesn't exist."<<endl;
            return;
        } else {
            string command1 = "cd "+ current_route;
            string command2 = "move "+ this_name + " "+ target_path;
            system((command1 + " && "+ command2).c_str());
        }
    }
}


void read(string name, string fakeDosFolderPath,
          string current_user, map<string, string> &user_route){

    ifstream infile;
    ofstream outfile;
    string current_route;

    current_route = route_formating(fakeDosFolderPath, user_route[current_user]);

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

    current_route = route_formating(fakeDosFolderPath, user_route[current_user]);

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
