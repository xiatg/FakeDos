/*
 * File: mem.h
 * -------------
 * This interface 
 */

#ifndef MEM_H
#define MEM_H

#include <string>
#include <vector>
#include <map>



void init_mem();

void user_mem_alloc(std::string & current_user);

void task_mem(int taskid, int taskmem);

template <typename ValueType>
bool task_data_write(int taskid, int taskmem);

template <typename ValueType>
ValueType task_data_read(int taskid, std::string key);


void user_mem_free(std::string & current_user);

void task_mem_free(int taskid);

bool limit_check(std::vector<std::string> user_name, int mem);

#endif 
