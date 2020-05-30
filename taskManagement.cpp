#include <iostream>
#include <string>
#include <random>
#include <vector>
#include "mem.h"
#include <taskManagement.h>
using namespace std;

#define TRUE 1
#define FALSE 0

void task_management(vector<PCB_type> & runningQueue, vector<PCB_type> & readyQueue)
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

int create_task(string userName, string appName, string & jsonmem, PCB_type (&mem)[100], vector<PCB_type> & readyQueue, vector<PCB_type> & runningQueue)
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
        if (mem[i].state != EMPTY)
        {
            usernames.push_back(mem[i].user_name);
        }

    if (limit_check(0, usernames, jsonmem))
    {

        for (i = 0; i < 100; i++)
            if (mem[i].state == EMPTY)
                break;
        mem[i].id = random_num;
        mem[i].state = READY;
        readyQueue.push_back(mem[i]);
        mem[i].app_name = appName;
        mem[i].user_name = userName;

        cout << "The task is created successfully, task id:" << mem[i].id << endl;
        //print the task id
        task_management(runningQueue, readyQueue);

        return mem[i].id;
    }

    else
    {
        cout << "Task creation failed." << endl;
        return false;
    }
}

void display(vector<string> user_name, string jsonmem, PCB_type (&mem)[100], vector<PCB_type> & runningQueue, vector<PCB_type> & blockQueue, vector<PCB_type> & readyQueue)
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
            cout << "Memory Use:" << get_task_mem(mem[i].id, jsonmem) << endl;
        }

        if (mem[i].state == READY)
        {
            cout << "Task id =" << mem[i].id << " is ready." << endl;
            cout << "User name:" << mem[i].user_name << endl;
            cout << "App name:" << mem[i].app_name << endl;
            cout << "Memory Use:" << get_task_mem(mem[i].id, jsonmem) << endl;
        }

        if (mem[i].state == BLOCK)
        {
            cout << "Task id =" << mem[i].id << " is blocked." << endl;
            cout << "User name:" << mem[i].user_name << endl;
            cout << "App name:" << mem[i].app_name << endl;
            cout << "Memory Use:" << get_task_mem(mem[i].id, jsonmem) << endl;
        }
    }

    cout << endl;

    if (user_name.size() > 0) {

        int used = 0;
        int total = 0xFFFF;

        cout << "User Memory Usage" << endl;
        for (i = 0; i < int(user_name.size()); i++)
        {
            cout << "User name:" << user_name[i] << endl;
            cout << "Memory Usage:" << get_user_mem(user_name[i], jsonmem) << endl;

            used += get_user_mem(user_name[i], jsonmem);
        }

        cout << endl;

        cout << "Used/Total: " << used << "/" << total << endl;

    } else {

        cout << "No user is using memory." << endl;
    }
}

bool block(string userName, int id, PCB_type (&mem)[100], vector<PCB_type> & runningQueue, vector<PCB_type> & blockQueue, vector<PCB_type> & readyQueue)
{
    int i;

    if (runningQueue.empty() && readyQueue.empty() && blockQueue.empty())
    {
        cout << "No task in the memory." << endl;
        return false;
    }

    else if (runningQueue.empty() && readyQueue.empty())
    {
        cout << "Every task is blocked." << endl;
        return false;
    }

    bool find = 0; //stands for whether task exists in memory

    for (i = 0; i < 100; i++)
    {
        if (id == mem[i].id)
        {
            find = 1;

            if (mem[i].user_name != userName)
            {
                cout << "You can only block your task." << endl;
                return false;
            }

            if (mem[i].state == EMPTY) //The task is already killed.
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

    task_management(runningQueue, readyQueue);
    return TRUE;
}

bool wake_up(string userName, int id, PCB_type (&mem)[100], vector<PCB_type> & runningQueue, vector<PCB_type> & blockQueue, vector<PCB_type> & readyQueue)
{
    int i;

    if (runningQueue.empty() && readyQueue.empty() && blockQueue.empty())
    {
        cout << "No task in the memory." << endl;
        return false;
    }

    else if (blockQueue.empty())
    {
        cout << "Every task is either running or ready, no task need to wake up." << endl;
        return false;
    }

    bool find = 0; //stands for whether task exists in memory

    for (i = 0; i < 100; i++)
    {
        if (id == mem[i].id)
        {
            find = 1;
            if (mem[i].user_name != userName)
            {
                cout << "You can only wake up your task." << endl;
                return false;

                if (mem[i].state == EMPTY) //The task is already killed.
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
    }
    task_management(runningQueue, readyQueue);
    return TRUE;
}

bool kill(string userName,
          int id,
          string & jsonmem,
          PCB_type (&mem)[100],
          vector<PCB_type> & runningQueue, vector<PCB_type> & blockQueue, vector<PCB_type> & readyQueue)
{
    int i;

    if (runningQueue.empty() && readyQueue.empty() && blockQueue.empty())
    {
        cout << "No task in the memory." << endl;
        return false;
    }

    bool find = 0; //stands for whether task exists in memory

    for (i = 0; i < 100; i++)
    {
        if (id == mem[i].id)
        {
            find = 1;

            if (mem[i].user_name != userName)
            {
                cout << "You can only kill your task." << endl;
                return false;
            }

            if (mem[i].state == EMPTY)
            { //The task is already killed.
                cout << "The task does not exist." << endl;
                return false;
            }

            else if (mem[i].state == RUNNING)
            {
                mem[i].state = EMPTY; //The task is killed.
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
                mem[i].state = EMPTY; //The task is killed.
                cout << "The task is killed." << endl;
                vector<PCB_type>::iterator iter;
                for (iter = blockQueue.begin(); iter != blockQueue.end(); iter++)
                {
                    if (iter->id == mem[i].id)
                        blockQueue.erase(iter);
                }
                //task_mem_free(id);
            }

            else if (mem[i].state == READY)
            {
                mem[i].state = EMPTY; //The task is killed.
                cout << "The task is killed." << endl;
                vector<PCB_type>::iterator iter;
                for (iter = readyQueue.begin(); iter != readyQueue.end(); iter++)
                {
                    if (iter->id == mem[i].id)
                        readyQueue.erase(iter);
                }
                task_mem_free(id, mem[i].user_name, jsonmem);
            }

            break;
        }
    }
    if (find == 0) //No such tasks in the memory
    {
        cout << "You entered a wrong id!" << endl;
    }
    task_management(runningQueue, readyQueue);
    return TRUE;
}
