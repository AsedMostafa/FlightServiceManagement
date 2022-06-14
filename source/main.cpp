#include <iostream>
#include <fstream>
#include <string>
#include "manager.hpp"
#include "webHandler.hpp"
#include "flightService.hpp"

using namespace std;

const vector<string> columnNames = {"airline", "origin", "destination", 
    "departure_date", "departure_time", "arrival_date", "arrival_time", "seats", "cost"
};

/*void getInputFromUser(Manager* mgr){
    while(true){
        string temp;
        getline(cin, temp);
        vector<string> cmd = stringToVector(temp);
        mgr->handler(cmd);
    }
}*/


int main(int argc, char *argv[]){
    /*Manager *reservation = new Manager(argv[1]); uncomment this for CLI
    getInputFromUser(reservation);
    delete reservation;*/
    ReadFile reader(argv[1]);
    FlightService* mainService = new FlightService;
    mainService->addFlights(reader.getInfo());
    Server mainServer(5000);
    mainServer.setNotFoundErrPage("htmlFiles/404.html");
    mainServer.post("/login", new LoginHandler(mainService));
    mainServer.get("/login", new LoginHandler(mainService));
    mainServer.post("/signup", new SignupHanlder(mainService));
    mainServer.get("/signup", new SignupHanlder(mainService));
    mainServer.get("/user", new handleUser("htmlFiles/user.html",mainService));
    mainServer.post("/user",  new handleUser("htmlFiles/user.html",mainService));
    mainServer.get("/permissionDenied", new PermissionDeniedHandler(mainService));
    mainServer.get("/flight", new HandleFlight("htmlFiles/flight.html", mainService));
    mainServer.post("/flight", new HandleFlight("htmlFiles/flight.html", mainService));
    mainServer.run();
}