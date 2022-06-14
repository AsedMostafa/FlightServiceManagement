#include "readFile.hpp"

ReadFile::ReadFile(string str){
    vector<string> columnNames = readColumnName(str);
    vector<string> flightInfo = readFlightInfo(str);
    information = flightInfoMatrix(flightInfo, columnNames);
}

vector<string> ReadFile::readFlightInfo(string input){
    fstream inputFile(input);
    vector<string> readFile;
    string lineHolder;
    getline(inputFile, lineHolder); // skip the first line
    while(getline(inputFile, lineHolder)){
        readFile.push_back(lineHolder);
    }
    return readFile;
}


vector<string> ReadFile::readColumnName(string input){
    fstream inputFile(input);
    vector<string> columnNames;
    string temp;
    getline(inputFile, temp);
    columnNames = stringToVector(temp, ',');
    return columnNames;
}

vector<vector<string>> ReadFile::flightInfoMatrix(vector<string> flInfo, vector<string> colNames){
    vector<vector<string>> Holder(flInfo.size(), vector<string>(colNames.size()));
    for(int i = 0; i < flInfo.size(); i++){
        vector<string> someVector = stringToVector(flInfo[i], ',');
        for(int j = 0; j < colNames.size(); j++){
            Holder[i][j] = someVector[j];
        }
    }
    return Holder;
}
