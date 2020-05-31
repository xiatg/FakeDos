
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <mem.h>
#include "dist/json/json.h"
#include <iostream>
#include <sstream>
using namespace std;

void init_mem(string & jsonmem){
    Json::Value root, user, taskmem;

    root["user"] = user;
    root["taskmem"] = taskmem;

    jsonmem = root.toStyledString();
}

void user_mem_alloc(string username, string & jsonmem){
    Json::Reader reader;
    Json::Value root;

    if (reader.parse(jsonmem, root)){
        root["user"][username] = 0xFF;  //  0x1000 represent OS memory usage
    }
    jsonmem = root.toStyledString();
}

void task_mem(int taskid, int taskmem, string username, string & jsonmem){
    Json::Reader reader;
    Json::Value root;

    string id = to_string(taskid);

    //Debug
//    cout << taskmem << endl;

    if (reader.parse(jsonmem, root)){
        if (!root["taskmem"].isMember(id)){
            root["taskmem"][id] = taskmem;

            //Debug
//            cout << "GERE" << endl;
        }
        else {
            root["taskmem"][id] = root["taskmem"][id].asInt() + taskmem;
        }
        root["user"][username] = root["user"][username].asInt() + taskmem;
    }

    //Debug
//    cout << root.toStyledString() << endl;

    jsonmem = (root.toStyledString());
}



string task_data_read(int taskid, string key, string & jsonmem){
    Json::Reader reader;
    Json::Value root;

    string id = to_string(taskid);

    if (reader.parse(jsonmem, root)){
        return root[id][key].asString();
    }
}


void user_mem_free(string username, string & jsonmem){
    Json::Reader reader;
    Json::Value root, user;

    if (reader.parse(jsonmem, root)){
        root["user"][username] = 0;
    }
    jsonmem = root.toStyledString();
}

void task_mem_free(int taskid, string username, string & jsonmem){
    Json::Reader reader;
    Json::Value root;
    string id = to_string(taskid);

    if (reader.parse(jsonmem, root)){
        root.removeMember(id);
        int mem = root["taskmem"][id].asInt();
        root["taskmem"][id] = 0;
        root["user"][username] = root["user"][username].asInt() - mem;
    }
    jsonmem = root.toStyledString();
}

bool limit_check(int mem, vector <string> l_u, string & jsonmem){
    Json::Reader reader;
    Json::Value root;

    int usage = 0;
    if (reader.parse(jsonmem, root)){
        for (int i = 0; i < int(l_u.size()); i++){
            usage += root["user"][l_u[i]].asInt();
        }
    }

    if ((usage + mem) >= 0x7FF){
        return false;
    }else return true;
}

int get_task_mem(int taskid, string & jsonmem){
    Json::Reader reader;
    Json::Value root;

    //Debug
//    cout << jsonmem;

    if (reader.parse(jsonmem, root)){
        return root["taskmem"][to_string(taskid)].asInt();
    } else return 0;
}

int get_user_mem(string username, string & jsonmem){
    Json::Reader reader;
    Json::Value root;
    // cout << jsonmem;

    if (reader.parse(jsonmem, root)){
        return root["user"][username].asInt();
    } else return 0;
}

bool task_data_write(int taskid, string key, string value, vector <string> user_name, string username, string & jsonmem){
    Json::Reader reader;
    Json::Value root;

    string id = to_string(taskid);
    int datamem = sizeof(value);

    if (limit_check(datamem, user_name, jsonmem)){
        if (reader.parse(jsonmem, root)){
            if (!root[id].isMember(key)) {
                task_mem(taskid, datamem, username, jsonmem);
            }
        }

        if (reader.parse(jsonmem, root)){
            root[id][key] = value;
            jsonmem = root.toStyledString();
        }
    }
    else return false;

    //Debug
//    cout << jsonmem << endl;

    return true;
}
