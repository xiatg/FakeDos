#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <applications.h>
#include <taskManagement.h>
#include <mem.h>
#include <ctime>

using namespace std;

#define UNDO 0
#define DONE 1

struct event
{
   string remark;
   int state; /* 0 for undo,1 for done*/
   string name;
};

void TODO_List(int taskid,
               bool first_exe,
               string username,
               vector<string> user_name,
               string &jsonmem,
               PCB_type (&mem)[100],
               vector<PCB_type> &runningQueue,
               vector<PCB_type> &blockQueue,
               vector<PCB_type> &readyQueue)
{
   event thing;
   /*data field*/
   vector<event> list_for_all;

   /*retrieve data*/
   if (!first_exe)
   {
      // retrieve the data with the given taskid
       for(int i=0;i<list_for_all.size();i++){
      list_for_all[i].name = task_data_read(taskid, "name"+to_string(i), jsonmem);
      list_for_all[i].remark = task_data_read(taskid, "remark"+to_string(i), jsonmem);
      list_for_all[i].state = stoi(task_data_read(taskid, "state"+to_string(i), jsonmem));

       }

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
      bool flag = true;
      for(int i=0;i<list_for_all.size();i++)
      {
          bool f0 = task_data_write(taskid, "name"+to_string(i), list_for_all[i].name, user_name, username, jsonmem);
          bool f1 = task_data_write(taskid, "remark"+to_string(i), list_for_all[i].remark, user_name, username, jsonmem);
          bool f2 = task_data_write(taskid, "state"+to_string(i),to_string(list_for_all[i].state),user_name,username,jsonmem);
          if(f0||f1||f2==false){
              flag = false;
          }
      }

        if(flag==false)
        {
         cout << "Error: memory overflow. App is terminating." << endl;
         kill(username, taskid, jsonmem, mem, runningQueue, blockQueue, readyQueue);
         return;
         }
   }

   /*main process*/
   bool killable = false;
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
            killable = true;
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
               cout<<"Successfully created!"<<endl;
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
               cout<<s<<"is ticked."<<endl;
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
   if (killable)
   {
      kill(username, taskid, jsonmem, mem, runningQueue, blockQueue, readyQueue);
   }
   else
   {
      // save the useful data to memory with the given taskid
       bool flag = true;
       for(int i=0;i<list_for_all.size();i++)
       {
           bool f0 = task_data_write(taskid, "name"+to_string(i), list_for_all[i].name, user_name, username, jsonmem);
           bool f1 = task_data_write(taskid, "remark"+to_string(i), list_for_all[i].remark, user_name, username, jsonmem);
           bool f2 = task_data_write(taskid, "state"+to_string(i),to_string(list_for_all[i].state),user_name,username,jsonmem);

           if((f0 == false)||(f1 == false)||(f2==false)){
               flag = false;
               break;
           }
       }

      if (flag==false)
      {
         cout << "Error: memory overflow. App is terminating." << endl;
         kill(username, taskid, jsonmem, mem, runningQueue, blockQueue, readyQueue);
      } else {
          block(username, taskid, mem, runningQueue, blockQueue, readyQueue);
      }
   }
}
