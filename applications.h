#ifndef APPLICATIONS_H
#define APPLICATIONS_H

#include <string>
#include <taskManagement.h>

void addition(int taskid, bool first_exe, std::string jsonmem);

void guessGame(int taskid,
               bool first_exe,
               string username,
               vector<string> user_name,
               string & jsonmem,
               PCB_type (&mem)[100],
               vector<PCB_type> & runningQueue,
               vector<PCB_type> & blockQueue,
               vector<PCB_type> & readyQueue);

#endif // APPLICATIONS_H
