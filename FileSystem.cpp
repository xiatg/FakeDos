#include "FileSystem.h"
#include <iostream>
#include "stringOperators.h"
#include "editorBuffer.h"
#include <iomanip>
#include <stack>
using namespace std;

FS *current = new FS; //当前dir
FS root; //根目录


int main(){
    //cout << "Main"<<endl;
    FileManagement();
    return 0;
}


void init(){
    // 初始化根目录
    root.name="root";
    root.next = NULL;
    root.type = 0;
    root.start = NULL;
    root.upper = NULL;
    // 初始化当前dir: 设为根目录(root)
    current = &root;
}

FS* deepCopy(FS *old){
    cout <<endl<<endl;
    FS *neww = new FS;
    FS *aid;
    EditorBuffer *newEditor = new EditorBuffer;
    newEditor->copyInternalData(*old->editor);


    neww->editor = newEditor;
    neww->name = old->name;
    neww->next = old->next;
    neww->type = old->type;
    neww->start = old->start;
    neww->upper = old->upper;
    aid = neww->start;
    while (aid){
        aid->upper = neww;
        aid=aid->next;
    }

    //
    neww->editor->showContents();


    return neww;
}

void create(){
    string command;
    cout << "Input 't' to terminate."<< endl;
    while(true){
        getline(cin,command);
        if (command == "t")break;
        createFile();
        createDir();
    }
    showContent();
}

void showContent(){
    FS *aid;
    int type;
    aid = current->start;
/*
    cout << "Enter showContent()"<< endl;
    cout << endl;
    */

    if (aid == NULL){
        cout << " The current folder is empty."<< endl;
    }
    else{
        while(true){
            if (aid==NULL) break;
            type = aid->type;
            if(!type){  //type==0: aid为文件夹
                cout << aid->name<< "(Folder)"<< endl;
            }
            else cout << aid->name<< "(File)"<< endl;
            aid = aid->next;
        }
    }
}

void createFile(){
    FS *newfile = new FS;   // 新建的文件
    FS *aid;
    string name;

    cout << "Please enter a file name: ";
    getline(cin,name);
    if (name != ""){
        newfile->editor = new EditorBuffer;
        newfile->name = name;
        newfile->next = NULL;
        newfile->type = 1;
        newfile->start = NULL;
        newfile->upper = current; //在当前目录下

        aid = current->start;
        if (aid == NULL){  // 若该文件为当前目录下的第一个文件
            current->start = newfile;
        }
        else{
            while (true){
                if (aid->type && aid->name == name){ //若存在同名文件
                    cout << "File existed!"<< endl;
                    break;
                }
                if (aid->next == NULL){
                    aid->next = newfile;
                    break;
                }
                aid = aid->next;
            }
        }
    }
}

void createDir(){
    FS *newDir = new FS;   // 新建的文件夹
    FS *aid;
    string name;

    cout << "Please enter a folder name: ";
    getline(cin,name);
    if (name != ""){
        newDir->name = name;
        newDir->next = NULL;
        newDir->type = 0;
        newDir->start = NULL;
        newDir->upper = current; //在当前目录下

        aid = current->start;
        if (aid == NULL){  // 若该文件为当前目录下的第一个文件夹
            current->start = newDir;
        }
        else{
            while (true){
                if (!(aid->type) && aid->name == name){ //若存在同名文件夹
                    cout << "Folder existed!"<< endl;
                    break;
                }
                if (aid->next == NULL){
                    aid->next = newDir;
                    break;
                }
                aid = aid->next;
            }
        }
    }
}

void changeDir(){
    string name;
    FS *aid;

    cout << "Change directory to (enter folder name): ";
    getline(cin,name);
    aid = current->start;
    while (true){
        if (aid == NULL){
            cout << "Cannot find target directory!"<< endl;
            break;
        }

        if (!(aid->type) && (aid->name==name)){ //若找到目标文件夹
            current = aid;   //切换当前目录至目标文件夹
            break;
        }
        aid = aid->next;
    }

    showPath();
    showContent();
}

void upperDir(){
    if(current->upper == NULL){
        cout << "Upper class directory doesn't exist!"<<endl;
    }
    else{
        current = current->upper;
        showPath();
        showContent();
    }
}

void cutHelp(){
    cout << endl;
    cout << "Commands for cut operation:"<< endl;
    cout << "'U': go to upper directory"<< endl;
    cout << "CD: change to the specific dirctory under current working space "<< endl;
    cout << "'OK': cut the file to current directory"<< endl;
    cout << "'Q': Cancel cut operation" << endl;
    cout << endl;
}

void cut(){
    string name;
    FS *aid, *aid2;
    string command;
    int state1,state2; //state: 指示能否找到要拷贝的文件
    int flag;

    state1=0;
    state2=0;

    cutHelp();
    cout << "Cut file/folder (enter file/folder name):";
    getline(cin,name);
    aid = current->start;

    int position=1; //用于记录移动的文件位于其所在目录的位置
    while (aid){
        if (aid->name == name){  //若找到目标文件： aid
            state1=1;
            FS *oldDir = current;

            while(true){
                cout << "Please enter your command for cut operation ('U'/'OK'/'Q'/'CD'): ";  //这段话再改准确一点
                getline(cin, command);
                command = toUpperCase(command);

                if (command == "U") flag = 1;
                else if (command == "OK") flag = 2;
                else if (command == "Q") flag = 3;
                else if (command == "CD") flag = 4;
                else flag =5;

                switch (flag) {
                case 1: {     // 切换至上一级目录
                    upperDir();
                    break;
                }
                case 2:  {    // 拷贝至当前目录
                    state2 = 1;

                    if (current->start == NULL){  //若当前目录为空
                        if (position == 1){  //若目标文件位于第一位
                            oldDir->start = aid->next;
                            current->start = aid;
                            aid->upper = current;
                            aid->next = NULL;
                            cout << "Successfully cut "<< aid->name <<
                                    " to directory "<<current->name<<"."<< endl;
                            break;
                        }

                        current->start = aid;
                        aid2->next = aid->next;
                        aid->upper = current;
                        aid->next = NULL;
                        cout << "Successfully cut "<< aid->name <<
                                " to directory "<<current->name<<"."<< endl;
                        break;
                    }

                    //若当前目录不为空：
                    FS *aid3 = current->start;
                    while(true){
                        if ((aid3->name == aid->name)&&(aid3->type == aid->type)){ //若当前目录下存在同名文件
                            if (aid->type){
                                cout << "Cut fail: File with the same name already exists!"<< endl;
                                break;
                            }
                            cout << "Cut fail: Folder with the same name already exists!"<< endl;
                            break;
                    }
                        if (aid3->next == NULL){ //若无同名文件存在
                            if (position == 1){
                                oldDir->start = aid->next;
                                aid3->next = aid;
                                aid->upper = current;
                                aid->next = NULL;
                                cout << "Successfully cut "<< aid->name <<
                                        " to directory "<<current->name<<"."<< endl;
                                break;
                            }
                            aid3->next = aid;   //将文件添加至当前目录末尾
                            aid2->next = aid->next;
                            aid->upper = current;
                            aid->next = NULL;
                            cout << "Successfully copy "<< aid->name <<
                                    " to directory "<<current->name<<"."<< endl;
                            break;
                        }
                        aid3 = aid3->next;
                    }
                    break;
                }

                case 3:{   // 取消拷贝操作
                    state2 = 1;
                    cout << " Cancel cut operation. " << endl;
                    break;
                }
                case 4: {  //切换至指定目录
                    changeDir();
                    break;
                }
                default:{  // 若输入无意义
                    state2 = 1;
                    cout << "Copy fail: invalid command."<< endl;
                    break;
                }

                }

                if (state2) break;  //若state2 = 1(即输入command 不为 U或CD),终止拷贝循环
            }
            break;
        }

        aid2 = aid;  //aid2: 指向目标文件/文件夹(aid)的上一项
        aid = aid->next;
        position+=1;
    }

    if(!state1){
        cout << "Cannot find target file/folder! "<< endl;
        cout << endl;
    }

}

void readFile(){
    FS *aid;
    string name;
    cout << "Read file (enter file name):";
    getline(cin,name);
    aid = current->start;

    while(aid){
        if (aid->name == name) {
            cout << "found "<<endl;
            cout << aid->name<<endl;
            //aid->editor->showContents();
            //aid->editor->debug();

            read(*aid);
            return;
        }
        aid = aid->next;
    }
    cout << "Cannot find target file!"<<endl;
}

void read(FS &file){
    if (file.type){
        cout << "read()"<<endl;

        file.editor->showContents();
    }
    else{
        cout << "Invalid command: target is not a file."<<endl;
    }
}

void writeFile(){
    FS *aid;
    string name;
    cout << "Write file (enter file name):";
    getline(cin,name);
    aid = current->start;

    while(aid){
        if (aid->name == name) {
            write(*aid);
            return;
        }
        aid = aid->next;
    }
    cout << "Cannot find target file!"<<endl;
}

void write(FS &file){
    if (file.type){
        editText(*file.editor);
    }
    else{
        cout << "Invalid command: target is not a file."<<endl;
    }

}

void delFile(){
    string name;
    FS *aid;

    cout << "Delete file (enter file name): ";
    getline(cin,name);
    aid = current->start;

    while(true){
        if (aid == NULL){
            cout << "Cannot find target file!"<< endl;
            break;
        }

        if (aid ->type && aid->name == name){
            current->start = aid->next;
            delete aid->editor;
            delete aid;
            break;
        }

        if (aid->next!=NULL){
            if (aid->next->type && (aid->next->name==name)){  //若找到目标文件: aid->next
                if (aid->next->next != NULL){
                    FS *p = aid->next->next;

                    delete aid->next->editor;
                    delete aid->next;
                    aid->next = p;
                    break;
                }
                delete aid->next->editor;
                delete aid->next;
                aid->next = NULL;
                break;
            }
        }
        aid = aid->next;
    }
}

void delDir(){
    string name;
    FS *aid;

    cout << "Delete folder (enter folder name): ";
    getline(cin,name);
    aid = current->start;

    while(true){
        if (aid == NULL){
            cout << "Cannot find target folder!"<< endl;
            break;
        }

        if (!(aid ->type) && aid->name == name){
            current->start = aid->next;
            delete aid;
            break;
        }

        if (aid->next!=NULL){
            if (!(aid->next->type) && (aid->next->name==name)){  //若找到目标文件: aid->next
                if (aid->next->next != NULL){
                    FS *p = aid->next->next;
                    delete aid->next;
                    aid->next = p;
                    break;
                }
                delete aid->next;
                aid->next = NULL;
                break;
            }
        }
        aid = aid->next;
    }

}

void copyHelp(){
    cout << endl;
    cout << "Commands for copy operation:"<< endl;
    cout << "'U': go to upper directory"<< endl;
    cout << "CD: change to the specific dirctory under current working space "<< endl;
    cout << "'OK': copy the file to current directory"<< endl;
    cout << "'Q': Cancel copy operation" << endl;
    cout << endl;
}

void copy(){
    string name;
    FS *aid,*aid_new;
    string command;
    int state1,state2; //state: 指示能否找到要拷贝的文件
    int flag;

    state1=0;
    state2=0;

    copyHelp();
    cout << "Copy file/folder (enter file/folder name):";
    getline(cin,name);
    aid = current->start;

    while (aid){
        if (aid->name == name){  //若找到目标文件： aid
            state1=1;
            aid_new = deepCopy(aid);   // 新建文件/文件夹指针

            cout << "name: "<<aid_new->name<<endl;
            cout << aid_new->upper->name<<endl;

            aid->editor->showContents();

            cout <<"tst"<<endl;
            aid_new->editor->showContents();


            while(true){
                cout << "Please enter your command for copy operation ('U'/'OK'/'Q'/'CD'): ";  //这段话再改准确一点
                getline(cin, command);
                command = toUpperCase(command);

                if (command == "U") flag = 1;
                else if (command == "OK") flag = 2;
                else if (command == "Q") flag = 3;
                else if (command == "CD") flag = 4;
                else flag =5;

                switch (flag) {
                case 1: {     // 切换至上一级目录
                    upperDir();
                    break;
                }
                case 2:  {    // 拷贝至当前目录
                    state2 = 1;

                    if (current->start == NULL){  //若当前目录为空
                        current->start = aid_new;
                        aid_new->upper = current;
                        aid_new->next = NULL;
                        cout << "Successfully copy "<< aid_new->name <<
                                " to directory "<<current->name<<"."<< endl;



                        cout << "content: ";
                        aid_new->editor->showContents();


                        break;
                    }

                    //若当前目录不为空：
                    aid = current->start;
                    while(true){
                        if ((aid->name == aid_new->name)&&(aid->type == aid_new->type)){ //若当前目录下存在同名文件
                            if (aid->type){
                                cout << "Copy fail: File with the same name already exists!"<< endl;
                                break;
                            }
                            cout << "Copy fail: Folder with the same name already exists!"<< endl;
                            break;
                    }
                        if (aid->next == NULL){ //若无同名文件存在
                            aid->next = aid_new;   //将文件添加至当前目录末尾
                            aid_new->upper = current;
                            aid_new->next = NULL;
                            cout << "Successfully copy "<< aid_new->name <<
                                    " to directory "<<current->name<<"."<< endl;
                            break;
                        }
                        aid = aid->next;
                    }
                    break;
                }

                case 3:{   // 取消拷贝操作
                    state2 = 1;
                    cout << " Cancel copy operation. " << endl;
                    delete aid_new;
                    break;
                }
                case 4: {  //切换至指定目录
                    changeDir();
                    break;
                }
                default:{  // 若输入无意义
                    state2 = 1;
                    cout << "Copy fail: invalid command."<< endl;
                    delete aid_new;
                    break;
                }

                }

                if (state2) break;  //若state2 = 1(即输入command 不为 U或CD),终止拷贝循环
            }
            break;
        }

        aid = aid->next;
    }

    if(!state1){
        cout << "Cannot find target file/folder! "<< endl;
        cout << endl;
    }
}

void showPath(){
    stack<string> dirList;
    string dir, path;
    //ostringstream path;
    FS *aid = current;

    while(aid){
        dirList.push(aid->name);
        aid=aid->upper;
    }

    if (dirList.size()==1){
        dir = dirList.top();
        dirList.pop();
        path = dir;
    }
    else{
        dir = dirList.top();
        dirList.pop();
        path = dir + ":";
    }

    while(!dirList.empty()){
        dir = dirList.top();
        dirList.pop();
        path += ("\\"+dir);
    }

    cout << "Current path: "<<endl;
    cout << path<< endl;
    cout << endl;
}

void help(){
    cout << "+-------------------------------------------+"<<endl;
    cout << "|               Command List                |"<< endl;
    cout << "+-------------------------------------------+"<<endl;
    cout << "|"<< right << setw(4)<<"E:"<< left<<
            setw(39)<< " Exit file management system"<<"|"<<endl;
    cout << "|"<< right<< setw(4)<<"H:"<< left<<
            setw(39)<< " Show command lists"<<"|"<<endl;
    cout << "|"<< right<< setw(4)<<"F:"<< left<<
            setw(39)<< " Create new file"<<"|"<<endl;
    cout << "|"<< right<< setw(4)<<"D:"<< left<<
            setw(39)<< " Create new directory(folder)"<<"|"<<endl;

    cout << "|"<< right<< setw(4)<<"R:"<< left<<
            setw(39)<< " Read a file"<<"|"<<endl;
    cout << "|"<< right<< setw(4)<<"W:"<< left<<
            setw(39)<< " Write a file"<<"|"<<endl;

    cout << "|"<< right<< setw(4)<<"DF:"<< left<<
            setw(39)<< " Delete file"<<"|"<<endl;
    cout << "|"<< right<< setw(4)<<"DD:"<< left<<
            setw(39)<< " Delete directory(folder)"<<"|"<<endl;
    cout << "|"<< right<< setw(4)<<"CP:"<< left<<
            setw(39)<< " Copy a file or a directory(folder)"<<"|"<<endl;
    cout << "|"<< right<< setw(4)<<"CT:"<< left<<
            setw(39)<< " Cut a file or a directory(folder)"<<"|"<<endl;
    cout << "|"<< right<< setw(4)<<"UD:"<< left<<
            setw(39)<< " Go to upper class directory"<<"|"<<endl;
    cout << "|"<< right<< setw(4)<<"CD:"<< left<<
            setw(39)<< " Change current directory"<<"|"<<endl;
    cout << "|"<< right<< setw(4)<<"SD:"<< left<<
            setw(39)<< " Show the content of current directory"<<"|"<<endl;
    cout << "|"<< right<< setw(4)<<"SP:"<< left<<
            setw(39)<< " Show current path"<<"|"<<endl;
    cout << "+-------------------------------------------+"<<endl;

}

void FileManagement(){
    string command;

    init();

    cout << "---------------------------------------------------"<<endl;
    cout << "  Welcome to the File Management System!"<< endl;
    cout << endl;

    help();

    while (true){
        cout << "Please enter your command: ";
        getline(cin, command);
        command = toUpperCase(command);

        if (command == "E"){
            cout << "Exit file management system, thank you for using."<< endl;
            cout << endl;
            break;
        }

        else if (command == "H" ) help();
        else if (command == "F") createFile();
        else if (command == "D") createDir();
        else if (command == "R") readFile();
        else if (command == "W") writeFile();
        else if (command == "DF") delFile();
        else if (command == "DD") delDir();
        else if (command == "CP") copy();
        else if (command == "CT") cut();
        else if (command == "UD") upperDir();
        else if (command == "CD") changeDir();
        else if (command == "SD") showContent();
        else if (command == "SP") showPath();

        else {
            cout << "Invalid command!"<< endl;
            cout << "(Enter 'H' for command help)"<< endl;
            cout << endl;
        }

    }
}



