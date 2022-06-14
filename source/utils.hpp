#ifndef UTILS_H
#define UTILS_H

#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>

using namespace std;

typedef chrono::system_clock::time_point timePoint;

timePoint parseTimeFromString(string);
void successfulRequestMsg();
void emptyRequestMsg();
void notFoundRequestMsg();
void badRequestMsg();
void permissionDeniedMsg();
vector<string> stringToVector(string, char = ' ');
int whichCommand(string, vector<string>);
int differnceOfDays(int, int);

#endif

