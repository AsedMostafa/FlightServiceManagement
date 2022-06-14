#include <string>

using namespace std;

class Filter{
public:
    virtual void dueFilter() = 0;
};

class destinationFilter: public Filter{
public:
    destinationFilter(string, string);
private:
    string from;
    string to;
};

class priceFilter: public Filter{

};

class airlineFilter: public Filter{

};

class intervalFilter: public Filter{

};