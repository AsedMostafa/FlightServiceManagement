#include "ticket.hpp"

Ticket::Ticket(Flight* f, string _flightType, int passCount, string _flightClass, int _id){
    flight = f;
    flightType = _flightType;
    passengerCount = passCount;
    flightClass = _flightClass;
    id = _id;
    cost = passengerCount * flight->getFlightPrice(flightClass);
}

string Ticket::printInfo(){
    ostringstream print;
    print
    << id << " "
    << flight->printFlightInfo(false)
    << flightClass << " "
    << flightType << " "
    << cost << endl;
    return print.str();
}

float Ticket::getTicketCost(){
    cost = passengerCount * flight->getFlightPrice(flightClass); 
    return cost;
}