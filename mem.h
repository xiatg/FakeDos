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

void user_mem_alloc(std::string username, std::string jsonmem);

void task_mem(int taskid, int taskmem, std::string username, std::string jsonmem);

template <typename ValueType>
bool task_data_write(int taskid, std::string key, ValueType value, std::string jsonmem);

template <typename ValueType>
ValueType task_data_read(int taskid, std::string key, std::string jsonmem);

void user_mem_free(std::string username, std::string jsonmem);

void task_mem_free(int taskid, std::string jsonmem);

bool limit_check(std::vector<string> user_name, int mem, std::string jsonmem);

int get_task_mem(int taskid, std::string jsonmem);

int get_user_mem(std::string username, std::string jsonmem);


#endif
