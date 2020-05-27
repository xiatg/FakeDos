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

template <typename ValueType>
void task_mem_alloc(int taskid, int memusage, ValueType Args);

void user_mem_free(std::string & current_user);

void task_mem_free(int taskid);

bool limit_check(std::vector<string> user_name, int mem)

#endif 
