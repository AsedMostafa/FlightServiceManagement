#ifndef FLIGHTSERVICE_H
#define FLIGHTSERVICE_H

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <bits/stdc++.h>
#include <algorithm>
#include "flight.hpp"
#include "user.hpp"

using namespace std;

typedef pair<pair<Flight*,Flight*>, float> twoFlightCost;

class FlightService
{
public:
    FlightService(){
        flightId = 1;
        ticketId = 1;
    }
    void addFlights(vector<vector<string>>);
    bool addUser(string, string);
    string printFlights();
    string printFlightById(int);
    void printUsers();
    bool loginUser(string);
    string loggedUserName();
    bool isUserLogged();
    void logoutUser();
    bool validateAndLoginUser(string, string);
    void wallet(string);
    void printLoggedUserAmount();
    void buyingticket(string, string, string, string);
    void addTicket(Flight*, string, int, string, int);
    string printAllUserTickets();
    void printTicketById(int);
    void cancleTicket(int);
    void addDestinationFilter(string, string);
    void nonStraightFlights(string, string);
    void checkForCheapestFlight(string, string, string);
    double printUserWalletAmount(){return loggedUser->getWalletAmount();};
    User* getLoggedUser(){return loggedUser;};
    void report();
private:
    bool isUserValid(string);
    bool isValidAmount(string);
    bool canUserBuyTicket(Flight*, string, int);
    void getConnectingFlight(string, string);
    vector<Flight*> getFlights(string, bool);
    void printConnectingFlights(vector<twoFlightCost>);
    bool isStopTimeEnough(Flight*, Flight*);
    void checkAvailableConnectingFlight(vector<Flight*>, vector<Flight*>);
    vector<twoFlightCost> sortAMap(map<pair<Flight*,Flight*>, float>&);
    vector<pair<string, int>> sortAMap(map<string, int>);
    static bool cmp(const twoFlightCost&,const twoFlightCost&);
    static bool cmpStr(const pair<string, int>&, const pair<string, int>&);
    static bool cmpFl(const pair<Flight*, float>&, const pair<Flight*, float>&);
    float getAverageFlightCost();
    vector<float> getMinAndMaxFlightCost();
    string getMostPopularDestination();
    vector<pair<string, int>> getTopAirlines();
    void flightPrintTemplate(twoFlightCost, bool);
    void flightPrintTemplate(pair<Flight*, float>);
    map<pair<Flight*,Flight*>, float> connectingFlights;
    vector<twoFlightCost> getNonstraightFlightWithDate(int);
    void decideWhichIsCheapest(vector<twoFlightCost>, vector<pair<Flight*, float>>);
    vector<Flight*> flights;
    vector<Ticket*> tickets;
    vector<User*> users;
    User* loggedUser = NULL;
    int flightId;
    int ticketId;
};

#endif
