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

void user_mem_alloc(std::string username);

void task_mem(int taskid, int taskmem);

template <typename ValueType>
bool task_data_write(int taskid, std::string key, ValueType value);

template <typename ValueType>
ValueType task_data_read(int taskid, std::string key);

void user_mem_free(std::string username);

void task_mem_free(int taskid);

bool limit_check(std::vector<std::string> user_name, int mem);

int get_task_mem(int taskid);

int get_user_mem(std::string username);

#endif
