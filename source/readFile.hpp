#ifndef READFILE_H
#define READFILE_H

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "utils.hpp"

using namespace std;

class ReadFile{
public:
    ReadFile(string);
    vector<vector<string>> getInfo(){ return information;};
private:
    vector<string> readFlightInfo(string);
    vector<string> readColumnName(string);
    vector<vector<string>> flightInfoMatrix(vector<string>, vector<string>);
    vector<vector<string>> information;
};

#endif