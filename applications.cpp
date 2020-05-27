#include<iostream>
#include<string>
#include<vector>

using namespace std;

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
