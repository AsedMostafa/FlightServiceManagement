#ifndef MANAGER_H
#define MANAGER_H

#include "flightService.hpp"
#include "readFile.hpp"
#include "utils.hpp"
using namespace std;

const vector<string> commands = {"signup", "login", "logout", "wallet", "flights", 
                                    "filters", "tickets", "connecting_flights", "cheapest_flights",
                                     "overall_report"};
const string GET_COMMAND = "GET";
const string POST_COMMAND = "POST";
const string DELETE_COMMAND = "DELETE";

class Manager{
public:
    Manager(string);
    void handler(vector<string>);
    bool validCommand(vector<string>);
private:
    void initilizeFlights(string);
    void getInputFromUser();
    void serviceHandler(vector<string>);
    void userHandler(vector<string>);
    void signup(vector<string>);
    void signupHandler(vector<string>);
    void login(vector<string>);
    void loginHandler(vector<string>);
    void logout(vector<string>);
    void walletHandler(vector<string>);
    void flightCommand(vector<string>);
    void flightHandler(vector<string>);
    void flightById(int);
    void getAvailableFlights();
    void buyingTicketCommand(vector<string>);
    void getTicketCommand(vector<string>);
    void cancleTicketCommand(vector<string>);
    void nonStraightFlightsCommand(vector<string>);
    void getReportCommand(vector<string>);
    void getCheapestFlight(vector<string>);
    FlightService* mainService;
    ReadFile* reader;
};

#endif