

//#include <iostream>
//#include <cstdlib>
//#include <string>
//#include <vector>
//#include <mem.h>
//#include "dist/json/json.h"
//#include <iostream>
//#include <sstream>
//using namespace std;

//string current_user;
//int apcount;
//int mem_capacity = 1024;
//string jsonmem;

//void init_mem(){
//    Json::StyledStreamWriter writer;
//    Json::Value root, user, taskid;

//    root["loginuser"] = user;
//    root["taskid"] = taskid;

//    jsonmem = root.toStyledString();
//}

//void user_mem_alloc(string & current_user){
//    Json::Reader reader;
//    Json::Value root, user, taskid;
    
//    if (reader.parse(jsonmem, root)){
//        if (!root["loginuser"].isMember(current_user)){
//            user[(char*)current_user.c_str()] = 64;
//            root["loginuser"].append(user);
//        }
//        else{
//            root["loginuser"][current_user] = 64;  //  64KB represent OS memory usage
//        }
        
//        int index;
//        for (int i = 0; i < user.size(); i++){
//            if (root["loginuser"][i].isMember(current_user)){
//                index = i;
//            }
//        }
//        //  define taskid for loginuser
//        string id = to_string(index);
//        Json::Value task;
//        task["ap1"] = id + "01";
//        task["ap2"] = id + "02";
//        task["ap3"] = id + "03";
//        root["taskid"] = task;
//    }
//    jsonmem = root.toStyledString();
//}

//template <typename ValueType>
//void task_mem_alloc(int taskid, int memusage, ValueType Args){
//    Json::Reader reader;
//    Json::Value root, task, mem, var;

//    string id = to_string(taskid);

//    if (reader.parse(jsonmem, root)){
//        if (!root.isMember(id)){
//            root[to_string(id)] = task;
//            mem["memusage"] = memusage;
//            task.append(mem);
//        root["loginuser"][current_user] = root["loginuser"][current_user].asInt() + 16;
//    //////////////////////////////
//    // write variable into memory
//    //////////////////////////////



//        }
//    }
//    jsonmem = root.toStyledString();
//}



//void user_mem_free(string & current_user){
//    Json::Reader reader;
//    Json::Value root, user, taskid;
    
//    if (reader.parse(jsonmem, root)){
//        int index;
//        for (int i = 0; i < user.size(); i++){
//            if (root["loginuser"][i].isMember(current_user)){
//                index = i;
//                root["loginuser"][i][current_user] = 0;
//            }
//        }

//        string id = to_string(index);
//        for (int i = 1; i < apcount; i++)
//            if (root.isMember(id + to_string(i))){
//                root.removeMember(id + to_string(i));
//            }
//    }
//    jsonmem = root.toStyledString();
//}

//void task_mem_free(int taskid){
//    Json::Reader reader;
//    Json::Value root, task;
//    string id = to_string(taskid);

//    if (reader.parse(jsonmem, root)){
//        string mem = root[id][0]["memusage"].asString();
//        root[id][0]["memusage"] = 0;
//        int userid = stoi(id.substr(0, 1));
//        root["loginuser"][userid][current_user] = root["loginuser"][userid][current_user].asInt() - stoi(mem);
//        root.removeMember(id);
//    }
//    jsonmem = root.toStyledString();
//}

//bool limit_check(vector<string> user_name, int mem){
//    Json::Reader reader;
//    Json::Value root, task;

//    int usage = 0;
//    if (reader.parse(jsonmem, root)){
//        for (int i = 0; i<user_name.size(); i++){
//            usage += root["loginuser"][i][user_name[i]].asInt();
//        }
//    }
//    if ((usage + mem) >= mem_capacity){
//        return false;
//    }else return true;
//}



