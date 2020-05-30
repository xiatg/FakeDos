#ifndef TASK_MANAGEMENT_H
#define TASK_MANAGEMENT_H

#include <iostream>
#include <string>
#include <random>
using namespace std;

#define EMPTY 0
#define RUNNING 1
#define BLOCK 2
#define READY 3

struct PCB_type
{
    int id;
    string user_name;
    string app_name;
    int state; /* 0 for not in memory, 1 for running, 2 for hang up */
};

int create_task(string, string,string &, PCB_type (&mem)[100], vector<PCB_type> & readyQueue, vector<PCB_type> &);
void display(vector<string>, string, PCB_type (&mem)[100], vector<PCB_type> & runningQueue, vector<PCB_type> & blockQueue, vector<PCB_type> & readyQueue);
bool block(string,int, PCB_type (&mem)[100], vector<PCB_type> & runningQueue, vector<PCB_type> & blockQueue, vector<PCB_type> & readyQueue);
bool wake_up(string,int, PCB_type (&mem)[100], vector<PCB_type> & runningQueue, vector<PCB_type> & blockQueue, vector<PCB_type> & readyQueue);
bool kill(string,int,string &, PCB_type (&mem)[100], vector<PCB_type> & runningQueue, vector<PCB_type> & blockQueue, vector<PCB_type> & readyQueue);
void task_management(PCB_type (&mem)[100], vector<PCB_type> &, vector<PCB_type> &);


#endif // TASK_MANAGEMENT_H

