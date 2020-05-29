#include <iostream>
#include <string>
#include <random>
#include <vector>
#include "mem.h"
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
    int state; /* 0 for not in memory, 1 for running, 2 for hang up */
};

vector<PCB_type> runningQueue;
vector<PCB_type> blockQueue;
vector<PCB_type> readyQueue;

struct PCB_type mem[100]; //a list stands for memory


void task_management()
{
    if (readyQueue.size() == 0)
    {
        return;
    }

    else if (runningQueue.size() < 1)
    {
        while (runningQueue.size() < 1 && readyQueue.empty() == 0)
        {
            readyQueue.front().state = RUNNING;
            runningQueue.push_back(readyQueue.front());
            readyQueue.erase(readyQueue.begin());
        }
    }
}

int create_task(string userName, string appName)
{
    int i, j, random_num;
    default_random_engine random;
    vector<string> usernames;

    random_num = random();
    for (j = 0; j < 100; j++)
        while (mem[j].id == random_num)
        {
            random_num = random();
        }

    for (i = 0; i < 100; i++)
        if (mem[i].state != NULL)
        {
            usernames.push_back(mem[i].user_name);
        }
    for (i = 0; i < 100; i++)
        if (mem[i].state == NULL)
            break;
    mem[i].id = random_num;
    mem[i].state = READY;
    readyQueue.push_back(mem[i]);
    mem[i].app_name = appName;
    mem[i].user_name = userName;

    cout << "The task is created successfully, task id:" << mem[i].id << endl;
    //print the task id
    task_management();

    return mem[i].id;
}

void display()
{
    int i;
    cout << "Number of tasks in memory: " << runningQueue.size() + readyQueue.size() + blockQueue.size() << endl;
    for (i = 0; i < 100; i++)
    {
        if (mem[i].state == RUNNING)
        {
            cout << "Task id =" << mem[i].id << " is running." << endl;
            cout << "User name:" << mem[i].user_name << endl;
            cout << "App name:" << mem[i].app_name << endl;
        }

        if (mem[i].state == READY)
        {
            cout << "Task id =" << mem[i].id << " is ready." << endl;
            cout << "User name:" << mem[i].user_name << endl;
            cout << "App name:" << mem[i].app_name << endl;
        }

        if (mem[i].state == BLOCK)
        {
            cout << "Task id =" << mem[i].id << " is blocked." << endl;
            cout << "User name:" << mem[i].user_name << endl;
            cout << "App name:" << mem[i].app_name << endl;
        }
    }
}

void block(int id)
{
    int i;

    if (runningQueue.empty() && readyQueue.empty() && blockQueue.empty())
    {
        cout << "No task in the memory." << endl;
        return;
    }

    else if (runningQueue.empty() && readyQueue.empty())
    {
        cout << "Every task is blocked." << endl;
        return;
    }

    bool find = 0; //stands for whether task exists in memory

    for (i = 0; i < 100; i++)
    {
        if (id == mem[i].id)
        {
            find = 1;

            if (mem[i].state == NULL) //The task is already killed.
                cout << "The task does not exist." << endl;

            else if (mem[i].state == BLOCK) //The task has been already blocked.
                cout << "The task has been already blocked." << endl;

            else if (mem[i].state == RUNNING)
            {
                mem[i].state = BLOCK; //The task is blocked.
                cout << "The task is blocked." << endl;
                blockQueue.push_back(mem[i]);

                vector<PCB_type>::iterator iter;
                for (iter = runningQueue.begin(); iter != runningQueue.end(); iter++)
                {
                    if (iter->id == mem[i].id)
                        runningQueue.erase(iter);
                }
            }

            else if (mem[i].state == READY)
            {
                mem[i].state = BLOCK; //The task is blocked.
                cout << "The task is blocked." << endl;
                blockQueue.push_back(mem[i]);

                vector<PCB_type>::iterator iter;
                for (iter = readyQueue.begin(); iter != readyQueue.end(); iter++)
                {
                    if (iter->id == mem[i].id)
                        readyQueue.erase(iter);
                }
            }
        }
    }

    if (find == 0) //No such tasks in the memory
    {
        cout << "You entered a wrong id!" << endl;
    }

    task_management();
}

void wake_up(int id)
{
    int i;

    if (runningQueue.empty() && readyQueue.empty() && blockQueue.empty())
    {
        cout << "No task in the memory." << endl;
        return;
    }

    else if (blockQueue.empty())
    {
        cout << "Every task is either running or ready, no task need to wake up." << endl;
        return;
    }

    bool find = 0; //stands for whether task exists in memory

    for (i = 0; i < 100; i++)
    {
        if (id == mem[i].id)
        {
            find = 1;

            if (mem[i].state == NULL) //The task is already killed.
                cout << "The task does not exist." << endl;

            else if (mem[i].state != BLOCK) //The task is not blocked.
                cout << "The task is either running or ready. "
                        "No need to wake it up."
                     << endl;

            else //the task is blocked.
            {
                mem[i].state = READY; //The task is waken up.
                cout << "The task is waken up to ready state." << endl;
                readyQueue.push_back(mem[i]);
                vector<PCB_type>::iterator iter;
                for (iter = blockQueue.begin(); iter != blockQueue.end(); iter++)
                {
                    if (iter->id == mem[i].id)
                        blockQueue.erase(iter);
                }
            }
        }
    }
    if (find == 0) //No such tasks in the memory
    {
        cout << "You entered a wrong id!" << endl;
    }
    task_management();
}

void kill(int id)
{
    int i;

    if (runningQueue.empty() && readyQueue.empty() && blockQueue.empty())
    {
        cout << "No task in the memory." << endl;
        return;
    }

    bool find = 0; //stands for whether task exists in memory

    for (i = 0; i < 100; i++)
    {
        if (id == mem[i].id)
        {
            find = 1;

            if (mem[i].state == NULL) //The task is already killed.
                cout << "The task does not exist." << endl;

            else if (mem[i].state == RUNNING)
            {
                mem[i].state = NULL; //The task is killed.
                cout << "The task is killed." << endl;
                vector<PCB_type>::iterator iter;
                for (iter = runningQueue.begin(); iter != runningQueue.end(); iter++)
                {
                    if (iter->id == mem[i].id)
                        runningQueue.erase(iter);
                }
            }

            else if (mem[i].state == BLOCK)
            {
                mem[i].state = NULL; //The task is killed.
                cout << "The task is killed." << endl;
                vector<PCB_type>::iterator iter;
                for (iter = blockQueue.begin(); iter != blockQueue.end(); iter++)
                {
                    if (iter->id == mem[i].id)
                        blockQueue.erase(iter);
                }
                task_mem_free(id);
            }

            else if (mem[i].state == READY)
            {
                mem[i].state = NULL; //The task is killed.
                cout << "The task is killed." << endl;
                vector<PCB_type>::iterator iter;
                for (iter = readyQueue.begin(); iter != readyQueue.end(); iter++)
                {
                    if (iter->id == mem[i].id)
                        readyQueue.erase(iter);
                }
                task_mem_free(id);
            }

            break;
        }
    }
    if (find == 0) //No such tasks in the memory
    {
        cout << "You entered a wrong id!" << endl;
    }
    task_management();
}


