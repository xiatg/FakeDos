#ifndef FAKEDOS_H
#define FAKEDOS_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

/*
 * Split the command by blank space.
 */
std::vector<std::string> command_split(std::string command);

/*
 * System preparation.
 */
void fakeDosPre();


/*
 * System main process.
 */
void fakeDos();

#endif // FAKEDOS_H
