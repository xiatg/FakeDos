#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <applications.h>

using namespace std;

bool is_number(string s) {
    string::iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void addition(int taskid, bool first_exe) {
    /*data field*/
    int a, b;
    bool ae = false, be = false;

    /*retrieve data*/
    if (!first_exe) {
        // retrieve the data with the given taskid
    }

    /*main process*/
    bool kill = false;
    string command;
    while (true) {

        if (!ae) {
            cout << "a = ";
            cin >> command;

            if (command == "exit") {
                kill = true;
                break;
            }
            else
            {
                if (command == "hangon") {
                    break;
                }
                else
                {
                    a = stoi(command);
                    ae = true;
                }
            }
        }

        if (!be) {
            cout << "b = ";
            cin >> command;

            if (command == "exit") {
                kill = true;
                break;
            } else {
                if (command == "hangon") {
                    break;
                } else {
                    b = stoi(command);
                    be = true;
                }
            }
        }

        cout << "c = " << a+b << endl;
        ae = false;
        be = false;
    }

    /*exit part*/
    if (kill) {
        // kill the task with the given taskid
    } else {
        // save the useful data to memory with the given taskid
    }
}

void guessGame(int taskid, bool first_exe) {
    /*data field*/
    int guess, goal, round;
    bool regenerate = true;

    /*retrieve data*/
    if (!first_exe) {
        // retrieve the data with the given taskid
    } else {
        cout << "Welcome to number guessing game!" << endl;
        cout << "I've radnomly generated a number, every round you can take a guess and I will tell you if the number is bigger or smaller than the value that you guess." << endl;
        cout << "Try to get the correct value within as less rounds as you can!" << endl;
        cout << "Type hangon to save the game for later." << endl;
        cout << "Type exit to exit the game." << endl;
    }

    /*main process*/
    bool kill = false;
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
                kill = true;
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
                        }
                    }
                    round++;
                }
            }
        }
    }

    /*exit part*/
    if (kill) {
        // kill the task with the given taskid
    } else {
        // save the useful data to memory with the given taskid
    }
}
