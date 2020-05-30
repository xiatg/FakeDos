#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <Task_management.h>

using namespace std;

#define UNDO 0
#define DONE 1

struct event
{
    string remark;
    int state; /* 0 for undo,1 for done*/
    string name;
};

void TODO_List(int taskid, bool first_exe)
{
    /*data field*/
    vector<event> list_for_all;
    event thing;

    /*retrieve data*/
    if (!first_exe)
    {
        // retrieve the data with the given taskid
    }
    else
    {
        cout << "Welcome to your todo list!" << endl;
        cout << "You can add events to your todo list and tick when you done it." << endl;
        cout << "You can see your todo list at any time!" << endl;
        cout << "Enter 'add' to add the event,enter 'tick' to tick your event, "
                "enter 'display' to look your todo list."
             << endl;
        cout << "Type 'hangon' to save your changes, you can later open it." << endl;
        cout << "Type 'exit' to exit the todo list." << endl;
    }

    /*main process*/
    bool killed = false;
    string command;
    while (true)
    {

        getline(cin, command);
        if (command == "hangon")
            break;
        else
        {
            if (command == "exit")
            {
                killed = true;
                break;
            }
            else
            {
                if (command == "add")
                {
                    cout << "Please enter the event name:" << endl;
                    getline(cin, thing.name);
                    cout << "Please enter the remark of the event:" << endl;
                    getline(cin, thing.remark);
                    thing.state = 0;
                    list_for_all.push_back(thing);
                }
                else if (command == "tick")
                {
                    cout << "Please enter the event you have done:" << endl;
                    string s;
                    getline(cin, s);
                    vector<event>::iterator iter;
                    for (iter = list_for_all.begin(); iter != list_for_all.end(); iter++)
                    {
                        if (iter->name == s)
                            iter->state = 1;
                    }
                }
                else if (command == "display")
                {
                    vector<event>::iterator iter;
                    int find = 0;
                    for (iter = list_for_all.begin(); iter != list_for_all.end(); iter++)
                    {
                        if (iter->state == 1)
                        {
                            cout << iter->name << " is done." << endl;
                        }
                        else if (iter->state == 0)
                        {
                            cout << iter->name << " is undone." << endl;
                            cout << "Remark:" << iter->remark << endl;
                            find++;
                        }
                    }
                    if (find == 0)
                    {
                        cout << "Congratulations! You have done all the things!" << endl;
                    }
                    else
                    {
                        cout << "You still have " << find << " thing(s) to do." << endl;
                    }
                }
            }
        }
    }

    /*exit part*/
    if (killed)
    {
        //kill(userName,taskid,jsonmem);
    }
    else
    {
        // save the useful data to memory with the given taskid
    }
}
