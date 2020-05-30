
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif defined(_MSC_VER)
#pragma warning(disable : 4996)
#endif

#ifndef MEM_H
#define MEM_H

#include <string>
#include <vector>
#include <map>



void init_mem();

void user_mem_alloc(std::string username, std::string & jsonmem);

void task_mem(int taskid, int taskmem, std::string username, std::string & jsonmem);

template <typename ValueType>
bool task_data_write(int taskid, std::string key, ValueType value, std::vector<std::string> user_name, std::string username, std::string & jsonmem);

template <typename ValueType>
ValueType task_data_read(int taskid, std::string key, std::string & jsonmem);

void user_mem_free(std::string username, std::string & jsonmem);

void task_mem_free(int taskid, std::string & jsonmem);

bool limit_check(int mem, std::vector<std::string> user_name, std::string & jsonmem);

int get_task_mem(int taskid, std::string & jsonmem);

int get_user_mem(std::string username, std::string & jsonmem);


#endif
