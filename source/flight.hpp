#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
#include <chrono>
#include "utils.hpp"

using namespace std;

class Flight
{
public:
    Flight(string, string, string, int, string, int, string, int, float, int);
    string printFlightInfo(bool printCost = true);
    bool stillHasCapacity();
    float getFlightPrice(string _type);
    void reduceCapacity(string, int);
    bool stillHasBuisinessCapacity(int);
    bool stillHasEconomyCapacity(int);
    string getAirline(){return airline;};
    int getFlightId(){return id;}
    bool isThisYourOrigin(string);
    bool isThisYourDestination(string);
    string getOrigin(){return origin;};
    string getDestination(){return destination;};
    int getDepartureDate(){return departureDate;};
    int getArrivalDate(){return arrivalDate;};
    timePoint getDepartureTime(){return departureTime;};
    timePoint getArrivalTime(){return arrivalTime;};
private:
    string airline;
    string origin;
    string destination;
    int departureDate;
    timePoint departureTime;
    int arrivalDate;
    timePoint arrivalTime;
    int seats;
    float price;
    int businessCapacity;
    int economyCapacity;
    int availableSeats;
    int id;
};

#endif
