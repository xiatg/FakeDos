#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <applications.h>
#include <taskManagement.h>
#include <mem.h>

using namespace std;

bool is_number(string s) {
    string::iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void guessGame(int taskid,
               bool first_exe,
               string username,
               vector<string> user_name,
               string & jsonmem,
               PCB_type (&mem)[100],
               vector<PCB_type> & runningQueue,
               vector<PCB_type> & blockQueue,
               vector<PCB_type> & readyQueue
               ) {
    /*data field*/
    int guess = 0, goal = 0, round = 0;
    bool regenerate = true;

    /*retrieve data*/
    if (!first_exe) {
        // retrieve the data with the given taskid
        guess = stoi(task_data_read(taskid, "guess", jsonmem));
        goal = stoi(task_data_read(taskid, "goal", jsonmem));
        round = stoi(task_data_read(taskid, "round", jsonmem));
        regenerate = false;
    } else {
        cout << "Welcome to number guessing game!" << endl;
        cout << "I've radnomly generated a number, every round you can take a guess and I will tell you if the number is bigger or smaller than the value that you guess." << endl;
        cout << "Try to get the correct value within as less rounds as you can!" << endl;
        cout << "Type hangon to save the game for later." << endl;
        cout << "Type exit to exit the game." << endl;

        if((!task_data_write(taskid, "guess", to_string(guess), user_name, username, jsonmem))
        || (!task_data_write(taskid, "goal", to_string(goal), user_name, username, jsonmem))
        || (!task_data_write(taskid, "round", to_string(round), user_name, username, jsonmem))) {

            cout << "Error: memory overflow. App is terminating." << endl;
            kill(username, taskid, jsonmem, mem, runningQueue, blockQueue, readyQueue);
            return ;
        }
    }

    /*main process*/
    bool killable = false;
    string command;
    while (true) {

        default_random_engine random;

        if (regenerate) {
            round = 0;
            goal = random();
            regenerate = false;
        }

        cout << "You are currently at round " << round << endl;
        cout << "Take a guess:";

        getline(cin, command);

        if (command == "hangon") break;
        else {
            if (command == "exit") {
                killable = true;
                break;
            } else {
                if (!is_number(command)) {
                    cout << "Error: please input a integer." << endl;
                } else {
                    guess = stoi(command);
                    if (goal < guess) {
                        cout << "The goal number is smaller than " << guess << endl;
                    } else {
                        if (goal > guess) {
                            cout << "The goal number is bigger than " << guess << endl;
                        } else {
                            cout << "Congratulations! The goal number is " << guess << " !" << endl;
                            cout << "It takes " << round << " rounds to get the goal number!" << endl;
                            cout << "Try again? (Y/else)";
                            getline(cin, command);
                            if (command == "Y") regenerate = true;
                            else {
                                killable = true;
                                break;
                            }
                        }
                    }
                    round++;
                }
            }
        }
    }

    /*exit part*/
    if (killable) {
        kill(username, taskid, jsonmem, mem, runningQueue, blockQueue, readyQueue);
    } else {
        // save the useful data to memory with the given taskid
        if((!task_data_write(taskid, "guess", to_string(guess), user_name, username, jsonmem))
        || (!task_data_write(taskid, "goal", to_string(goal), user_name, username, jsonmem))
        || (!task_data_write(taskid, "round", to_string(round), user_name, username, jsonmem))) {
            cout << "Error: memory overflow. App is terminating." << endl;
            kill(username, taskid, jsonmem, mem, runningQueue, blockQueue, readyQueue);
        }

        block(username, taskid, mem, runningQueue, blockQueue, readyQueue);
    }
}
