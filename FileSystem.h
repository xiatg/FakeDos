#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <iostream>
#include <string>
#include "editorBuffer.h"

using namespace std;

struct FS{   //定义结构体: FS (File System), 包含文件类型及文件夹（目录）类型
    string name;   //名称
    int type;  //类型：0表示文件夹，1表示文件

    EditorBuffer *editor; // File editor
    //EditorBuffer editor;
    FS *start;  // specifically for 文件夹：指向当前文件夹内的第一个FS
    FS *next;   //指向在同一目录下的下一个FS
    FS *upper; // 指向上一级文件夹  注：不等于“next”的相反操作
};

FS *deepCopy(FS *old); // 对FS的deep copy

void init();  //初始化文件系统: 创建根目录

FS* File(string name);
FS* Dir(string name);

/* create/delete  file/dir */
void createFile();

void createDir();

void delFile();

void delDir();

void copyHelp();
void copy(); //拷贝文件夹

void cutHelp();
void cut(); //剪切：将一个文件/文件夹从当前目录移动到另一目录

void readFile();
void writeFile(); //对文件的读写操作

void read(FS &file);
void write(FS &file);

void showContent();  // 展示文件夹内所有内容

void changeDir();

void upperDir(); // 进入上一级目录

void showPath(); //展示当前路径

void help(); //展示所有指令符

void FileManagement();

#endif // FILESYSTEM_H
