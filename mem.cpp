

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <mem.h>
#include "dist/json/json.h"
#include <iostream>
#include <sstream>
using namespace std;

string current_user;
int apcount;
int mem_capacity = 0xFFFF;
string jsonmem;

void init_mem(){
    Json::StyledStreamWriter writer;
    Json::Value root, user, taskid;

    root["loginuser"] = user;
    root["taskid"] = taskid;

    jsonmem = root.toStyledString(); 
}

void user_mem_alloc(string & current_user){
    Json::Reader reader;
    Json::Value root, user, taskid;
    
    if (reader.parse(jsonmem, root)){
        if (!root["loginuser"].isMember(current_user)){
            user[(char*)current_user.c_str()] = 0x1000;
            root["loginuser"].append(user);
        }
        else{
            root["loginuser"][current_user] = 0x1000;  //  0x1000 represent OS memory usage
        }
        
        int index;
        for (int i = 0; i < user.size(); i++){
            if (root["loginuser"][i].isMember(current_user)){
                index = i;
            }
        }
        //  define taskid for loginuser
        string id = to_string(index);
        Json::Value task;
        task["ap1"] = id + "1";
        task["ap2"] = id + "2";
        task["ap3"] = id + "3";
        root["taskid"] = task;
    }
    jsonmem = root.toStyledString(); 
}

void task_mem(int taskid, int taskmem){
    Json::Reader reader;
    Json::Value root;

    string id = to_string(taskid);

    if (reader.parse(jsonmem, root)){
        if (!root.isMember(id)){
            Json::Value task, mem;
            mem["memusage"] = taskmem;
            task.append(mem);
            root[id] = task;
        }
        else
        {
            root[id][0]["memusage"] = root[id][0]["memusage"].asInt() + taskmem;
        }
        root["loginuser"][current_user] = root["loginuser"][current_user].asInt() + taskmem;
    }
    jsonmem = root.toStyledString(); 
}

template <typename ValueType>
bool task_data_write(int taskid, string key, ValueType value){
    Json::Reader reader;
    Json::Value root;

    string id = to_string(taskid);
    int datamem = sizeof(value);
    if (limit_check(current_user, datamem)) return false;
    if (reader.parse(jsonmem, root)){
        root[id][0][key] = value;
        task_mem(taskid, datamem);
    }
    jsonmem = root.toStyledString(); 
    return true;
}

template <typename ValueType>
ValueType task_data_read(int taskid, string key){
    Json::Reader reader;
    Json::Value root;

    string id = to_string(taskid);

    if (reader.parse(jsonmem, root)){
        return root[id][0][key];
    }
}



void user_mem_free(string & current_user){
    Json::Reader reader;
    Json::Value root, user;
    
    if (reader.parse(jsonmem, root)){
        int index;
        for (int i = 0; i < root["loginuser"].size(); i++){
            if (root["loginuser"][i].isMember(current_user)){
                index = i;
                root["loginuser"][i][current_user] = 0;
            }
        }

        string id = to_string(index);
        for (int i = 1; i < apcount; i++)
            if (root.isMember(id + to_string(i))){
                root.removeMember(id + to_string(i));
            }
    }
    jsonmem = root.toStyledString();
}

void task_mem_free(int taskid){
    Json::Reader reader;
    Json::Value root;
    string id = to_string(taskid);

    if (reader.parse(jsonmem, root)){
        int mem = root[id][0]["memusage"].asInt();
        root[id][0]["memusage"] = 0;
        int userid = stoi(id.substr(0, 1));
        root["loginuser"][userid][current_user] = root["loginuser"][userid][current_user].asInt() - mem;
        root.removeMember(id);
    }
    jsonmem = root.toStyledString();
}

bool limit_check(vector<string> user_name, int mem){
    Json::Reader reader;
    Json::Value root;

    int usage = 0;
    if (reader.parse(jsonmem, root)){
        for (int i = 0; i<user_name.size(); i++){
            usage += root["loginuser"][i][user_name[i]].asInt();
        }
    }
    if ((usage + mem) >= mem_capacity){
        return false;
    }else return true;
}



