#ifndef TICKET_H
#define TICKET_H

#include "flight.hpp"

class Ticket{
public:
    Ticket(Flight*, string, int, string, int);
    string printInfo();
    float getTicketCost();
    int getTicketId(){return id;}
    string getTicketType(){return flightType;}
    string getDestination(){return flight->getDestination();}
    int getQuantity(){return passengerCount;};
    string getAirline(){return flight->getAirline();};
private:
    Flight* flight;
    string flightType;
    int passengerCount;
    string flightClass;
    int id;
    float cost;
};

#endif