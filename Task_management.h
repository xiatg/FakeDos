#ifndef TASK_MANAGEMENT_H
#define TASK_MANAGEMENT_H

#include <iostream>
#include <string>
#include <random>
using namespace std;

#define TRUE 1
#define FALSE 0
#define NULL 0
#define RUNNING 1
#define BLOCK 2
#define READY 3

struct PCB_type
{
    int id;
    string user_name;
    string app_name;
    void *addr;
    int state; /* 0 for not in memory, 1 for running, 2 for hang up */
};

void create_task();
void display();
void block();
void wake_up();
void kill();
void task_management();


#endif // TASK_MANAGEMENT_H

