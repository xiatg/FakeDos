#ifndef TODO_LIST_H
#define TODO_LIST_H
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <applications.h>
#include <taskManagement.h>
#include <mem.h>
#include <ctime>

void TODO_List(int taskid,
               bool first_exe,
               string username,
               vector<string> user_name,
               string &jsonmem,
               PCB_type (&mem)[100],
               vector<PCB_type> &runningQueue,
               vector<PCB_type> &blockQueue,
               vector<PCB_type> &readyQueue);

#endif // TODO_LIST_H
