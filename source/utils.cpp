#include"utils.hpp"


timePoint parseTimeFromString(string str){
    tm time = {};
    stringstream timeString(str);
    timeString >> get_time(&time, "%T");
    auto extractedTime = chrono::system_clock::from_time_t(mktime(&time));
    return extractedTime;
}

void successfulRequestMsg(){
    cout << "OK" << endl;
}

void emptyRequestMsg(){
    cout << "EMPTY" << endl;
}

void notFoundRequestMsg(){
    cout << "Not Found" << endl;
}

void badRequestMsg(){
    cout << "Bad Request" << endl;
}

void permissionDeniedMsg(){
    cout << "Permission Denied" << endl;
}

vector<string> stringToVector(string toBeConverted, char delimeter){
    stringstream ss(toBeConverted);
    string word;
    vector<string> stringVector;
    while (getline(ss, word, delimeter)) {
        stringVector.push_back(word);
    }
    return stringVector;
}

int whichCommand(string str, vector<string> cmds){
    int i = 0;
    for(string s:cmds){
        if(str == s){
            return i;
        }
        i++;
    }
    return -1;
}

int differnceOfDays(int firstDay, int secondDay){
    if(secondDay == 1 && firstDay != 30){
        return -1;
    }
    if(secondDay == 1 && firstDay == 30){
        return 1;
    }
    if(secondDay < firstDay){
        return -1;
    }
    return secondDay - firstDay;
}