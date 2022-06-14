#include "manager.hpp"

Manager::Manager(string str){
    mainService = new FlightService;
    initilizeFlights(str);

}

void Manager::initilizeFlights(string str){
    reader = new ReadFile(str);
    mainService->addFlights(reader->getInfo());
    delete reader;
}

bool Manager::validCommand(vector<string> userCommnad){
    if(userCommnad.size() < 2){
        return false;
    }
    if(whichCommand(userCommnad[1], commands) != -1){
        return true;
    }
    return false;
}

void Manager::signupHandler(vector<string> usercommand){
    int user = whichCommand("username", usercommand);
    int pass = whichCommand("password", usercommand);
    if(user == -1 || pass == -1){
        badRequestMsg();
        return;
    }
    mainService->addUser(usercommand[user+1], usercommand[pass+1]);
}

void Manager::signup(vector<string> userCommand){
    if(mainService->isUserLogged()){
        badRequestMsg();
        return;
    }
    signupHandler(userCommand);
}


void Manager::login(vector<string> usercommand){
    int user = whichCommand("username", usercommand);
    int pass = whichCommand("password", usercommand);
    if(user == -1 || pass == -1){
        badRequestMsg();
        return;
    }
    if(mainService->validateAndLoginUser(usercommand[user+1], usercommand[pass+1])){
        successfulRequestMsg();
        return;
    }
    badRequestMsg();
}

void Manager::logout(vector<string> userCommand){
    if(mainService->isUserLogged()){
        mainService->logoutUser();
        successfulRequestMsg();
        return;
    }
    permissionDeniedMsg();
}

void Manager::serviceHandler(vector<string> userCommand){
    if(userCommand[0] == POST_COMMAND){
        int cmd = whichCommand(userCommand[1], commands);
        switch (cmd)
        {
        case 0:
            signup(userCommand);
            break;
        case 1:
            login(userCommand);
            break;
        case 2:
            logout(userCommand);
            break;
        }
        return;
    }
    badRequestMsg();
}

void Manager::walletHandler(vector<string> usercommand){
    int h = whichCommand("amount", usercommand);
    if(h == -1){
        badRequestMsg();
        return;
    }
    if(mainService->isUserLogged()){
        mainService->wallet(usercommand[h+1]);
        return;
    }
    else{
        permissionDeniedMsg();
    }
}

void Manager::flightById(int id){
    mainService->printFlightById(id);
}

void Manager::getAvailableFlights(){
    mainService->printFlights();
}

void Manager::buyingTicketCommand(vector<string> userCommand){
    if(userCommand.size() < 10){
        badRequestMsg();
        return;
    }
    int flight = whichCommand("flight", userCommand);
    int quant = whichCommand("quantity", userCommand);
    int flightClass = whichCommand("class", userCommand);
    int type = whichCommand("type", userCommand);
    if(flight == -1 || quant == -1 || flightClass == -1 || type == -1){
        badRequestMsg();
        return;
    }
    mainService->buyingticket(userCommand[flight+1], userCommand[quant+1], userCommand[flightClass+1],
                                userCommand[type+1]);
}

void Manager::flightHandler(vector<string> userCommand){
    int h = whichCommand("id", userCommand);
    if(h != -1){
        int id = stoi(userCommand[h+1]);
        flightById(id);
        return;
    }
    if((h == -1) && (userCommand.size() > 2)){
        badRequestMsg();
        return;
    }
    getAvailableFlights();
}

void Manager::flightCommand(vector<string> userCommand){
    if(mainService->isUserLogged()){
        flightHandler(userCommand);
        return;
    }
    else{
        permissionDeniedMsg();
    }
}

void Manager::getTicketCommand(vector<string> userCommand){
    if(!mainService->isUserLogged()){
        permissionDeniedMsg();
        return;
    }
    int h = whichCommand("id", userCommand);
    if(userCommand.size() > 2){
        if(h != -1){
            mainService->printTicketById(h);
        }
        else{
            badRequestMsg();
            return;
        }
    }
    else{
        mainService->printAllUserTickets();
    }
}

void Manager::cancleTicketCommand(vector<string> userCommand){
    if(userCommand.size() != 5){
        badRequestMsg();
        return;
    }
    int h = whichCommand("id", userCommand);
    if(h != -1){
        mainService->cancleTicket(stoi(userCommand[h+1]));
        return;
    }
    badRequestMsg();
}

void Manager::nonStraightFlightsCommand(vector<string> userCommand){
    if(userCommand.size() != 7){
        badRequestMsg();
        return;
    }
    int from = whichCommand("from", userCommand);
    int to = whichCommand("to", userCommand);
    if(from == -1 || to == -1){
        badRequestMsg();
        return;
    }
    mainService->nonStraightFlights(userCommand[from+1], userCommand[to+1]);
}

void Manager::getCheapestFlight(vector<string> userCommand){
    if(userCommand.size() != 9){
        badRequestMsg();
        return;
    }
    int from = whichCommand("from", userCommand);
    int to = whichCommand("to", userCommand);
    int depDate = whichCommand("departure_date", userCommand);
    if(from == -1 || to == -1 || depDate == -1){
        badRequestMsg();
        return;
    }
    mainService->checkForCheapestFlight(userCommand[from+1], userCommand[to+1], userCommand[depDate+1]);
}

void Manager::getReportCommand(vector<string> userCommnad){
    if(userCommnad.size() != 2){
        badRequestMsg();
        return;
    }
    mainService->report();
}

void Manager::userHandler(vector<string> userCommand){
    int h = whichCommand(userCommand[1], commands);
    if((userCommand[0] == POST_COMMAND) && (h == 3)){
        walletHandler(userCommand);
        return;
    }
    if((userCommand[0] == GET_COMMAND) && (h == 4)){
        flightCommand(userCommand);
        return;
    }
    if((userCommand[0] == POST_COMMAND) && (h == 6)){
        buyingTicketCommand(userCommand);
        return;
    }
    if((userCommand[0] == GET_COMMAND) && (h == 6)){
        getTicketCommand(userCommand);
        return;
    }
    if((userCommand[0] == DELETE_COMMAND) && (h == 6)){
        cancleTicketCommand(userCommand);
        return;
    }
    if((userCommand[0] == GET_COMMAND) && (h == 7)){
        nonStraightFlightsCommand(userCommand);
        return;
    }
    if((userCommand[0] == GET_COMMAND && (h == 8))){
        getCheapestFlight(userCommand);
        return;
    }
    if((userCommand[0] == GET_COMMAND) && (h == 9)){
        getReportCommand(userCommand);
        return;
    }
    badRequestMsg();
}

void Manager::handler(vector<string> userCommnad){
    if(validCommand(userCommnad)){
        int h = whichCommand(userCommnad[1], commands);
        if(h < 3){
            serviceHandler(userCommnad);
            return;
        }
        else{
            userHandler(userCommnad);
            return;
        }
       badRequestMsg();
    }
    else{
        badRequestMsg();
    }
}


