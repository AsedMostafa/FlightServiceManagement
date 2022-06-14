#include "flightService.hpp"

void FlightService::addFlights(vector<vector<string>> info){
    int i = 0;
    while(i < info.size()){
        string airline = info[i][0];
        string origin = info[i][1];
        string destination= info[i][2];
        int departureDate = stoi(info[i][3]);
        string departureTime = info[i][4];
        int arrivalDate = stoi(info[i][5]);
        string arrivalTime = info[i][6];
        int seats = stoi(info[i][7]);
        float price = stof(info[i][8]);
        flights.push_back(new Flight(airline, origin, destination, 
                                departureDate, departureTime, arrivalDate, 
                                arrivalTime, seats, price, flightId));
        flightId++;
        i++;
    }
}


string FlightService::printFlights(){
    if(!isUserLogged()){
        permissionDeniedMsg();
    }
    string print;
    bool thereIsFlight = false;
    for(Flight* f:flights){
        if(f->stillHasCapacity()){
            print += f->printFlightInfo();
            thereIsFlight = true;
        }
    }
    if(!thereIsFlight){
        return "there is no flight";
    }
    return print;
}


string FlightService::printFlightById(int id){
    for(Flight* f:flights){
        if(f->getFlightId() == id){
            return f->printFlightInfo();
        }
    }
    notFoundRequestMsg();
}

string FlightService::loggedUserName(){
    if(isUserLogged()){
        return loggedUser->getUserName();
    }
    return " ";
}

bool FlightService::isUserValid(string username){
    if(users.size() == 0){
        return true;
    }
    for(User* u:users){
        if(username == u->getUserName()){
            return false;
        }
    }
    return true;
}

bool FlightService::addUser(string _user, string _pass){
    if(isUserValid(_user) && !isUserLogged()){
        users.push_back(new User(_user, _pass));
        loggedUser = users.back();
        return true;
    }
    return false;

}

bool FlightService::loginUser(string username){
    for(User* u:users){
        if(u->getUserName() == username){
            loggedUser = u;
            return true;
        }
    }
    return false;
}

bool FlightService::validateAndLoginUser(string _user, string _pass){
    for(User* u:users){
        if(u->isThisU(_user, _pass)){
            loggedUser = u;
            return true;
        }
    }
    return false;
}

void FlightService::logoutUser(){
    loggedUser = NULL;
}

bool FlightService::isUserLogged(){
    if(loggedUser == NULL){
        return false;
    }
    return true;
}

bool FlightService::isValidAmount(string str){
    string::const_iterator it = str.begin();
    while (it != str.end() && isdigit(*it)) ++it;
    return !str.empty() && it == str.end();
}

void FlightService::wallet(string amount){
    if(isValidAmount(amount)){
        double chargeAmount = stod(amount);
        loggedUser->chargeWallet(chargeAmount);
        return;
    }
}

bool FlightService::canUserBuyTicket(Flight* f, string flightClass, int quant){
    float ticketCost = quant * f->getFlightPrice(flightClass);
    if(flightClass == "economy"){
        if(f->stillHasEconomyCapacity(quant) && loggedUser->getWalletAmount() >= ticketCost){
            return true;
        }
    }
    if(flightClass == "business"){
        if(f->stillHasBuisinessCapacity(quant) && loggedUser->getWalletAmount() >= ticketCost){
            return true;
        }
    }
    return false;
}

void FlightService::addTicket(Flight* f, string _type, int passCount, string _flightClass, int id){
    Ticket* buoghtTicket = new Ticket(f, _type, passCount, _flightClass, id);
    loggedUser->addTicket(buoghtTicket);
    f->reduceCapacity(_flightClass, passCount);
    tickets.push_back(buoghtTicket);
    cout << ticketId << endl;
    ticketId++;
}

void FlightService::buyingticket(string _flightId, string _quant, string _flightClass, string _flightType){
    int flightId = stoi(_flightId);
    int quantity = stoi(_quant);
    for(Flight* f:flights){
        if(f->getFlightId() == flightId){
            if(canUserBuyTicket(f, _flightClass, quantity)){
                addTicket(f, _flightType, quantity, _flightClass, ticketId);
                return;
            }
            else{
                badRequestMsg();
                return;
            }
        }
    }
    notFoundRequestMsg();
}

void FlightService::printLoggedUserAmount(){
    loggedUser->getWalletAmount();
}


void FlightService::printUsers(){
    for(User* u:users){
        cout << u->getUserName() << endl;
    }
}

string FlightService::printAllUserTickets(){
    return loggedUser->printTickets();
}

void FlightService::printTicketById(int _id){
    loggedUser->getTicketById(_id);
}

void FlightService::cancleTicket(int _id){
    loggedUser->cancleTicketById(_id);
}

void FlightService::nonStraightFlights(string from, string to){
    if(!isUserLogged()){
        permissionDeniedMsg();
        return;
    }
    getConnectingFlight(from, to);
    printConnectingFlights(sortAMap(connectingFlights));
}

vector<Flight*> FlightService::getFlights(string where, bool from){
    vector<Flight*> tempFlightsHolder;
    for(Flight* f:flights){
        if(f->isThisYourOrigin(where) && from){
            tempFlightsHolder.push_back(f);
        }
        else if(f->isThisYourDestination(where)){
            tempFlightsHolder.push_back(f);
        }
    }
    return tempFlightsHolder;

}

bool FlightService::isStopTimeEnough(Flight* firstFlight, Flight* secondFlight){
    auto stayingTime = secondFlight->getDepartureTime() - firstFlight->getArrivalTime(); 
    auto maxStaying = chrono::hours(15);
    auto diffTime = (stayingTime - maxStaying);
    if(diffTime > chrono::minutes(0)){
        return false;
    }
    return true;
}

void FlightService::getConnectingFlight(string _from, string _to){
    vector<Flight*> fromWhere = getFlights(_from, true);
    vector<Flight*> toWhere = getFlights(_to, false);
    if(fromWhere.size() == 0 || toWhere.size() == 0){
        notFoundRequestMsg();
        return;
    }
    
    checkAvailableConnectingFlight(fromWhere, toWhere);
}

void FlightService::checkAvailableConnectingFlight(vector<Flight*> fromWhere, vector<Flight*> toWhere){
    if(connectingFlights.size() != 0){
        connectingFlights.erase(connectingFlights.begin(), connectingFlights.end());
    }
    for(Flight* from:fromWhere){
        for(Flight* to:toWhere){
            if(from->getDestination() == to->getOrigin()){
                auto twoFlights = pair<Flight*,Flight*>(from, to);
                float price = from->getFlightPrice("economy") + to->getFlightPrice("economy");
                connectingFlights.insert(twoFlightCost(twoFlights, price));
            }
            int dayDifference = differnceOfDays(from->getArrivalDate(), to->getDepartureDate());
            if(dayDifference == -1 || dayDifference > 1 || !isStopTimeEnough(from, to)){
                connectingFlights.erase(pair<Flight*, Flight*>(from, to));
            }
        }
    }
}


void FlightService::printConnectingFlights(vector<twoFlightCost> connecting){
    if(connecting.size() == 0){
        notFoundRequestMsg();
        return;
    }
    for (auto itr: connecting) {
        flightPrintTemplate(itr, true);
    }
}

void FlightService::flightPrintTemplate(twoFlightCost itr, bool withTime){
        cout << "Flight 1: ";
        itr.first.first->printFlightInfo();
        cout << "Flight 2: ";
        itr.first.second->printFlightInfo();
        if(withTime){
            cout << "* Connection duration: ";
            time_t arrival = chrono::system_clock::to_time_t(itr.first.first->getArrivalTime());
            time_t leave = chrono::system_clock::to_time_t(itr.first.second->getDepartureTime());
            time_t diff = leave - arrival;
            cout << put_time(gmtime(&(diff)), "%Hh %Mm");
            cout << ", ";
        }
        cout << "Total cost: ";
        cout << fixed << setprecision(2) << itr.second << endl;
        if(withTime){
            cout << "----------" << endl;
        }
}

bool FlightService::cmp(const twoFlightCost& a,const twoFlightCost& b){
    return a.second < b.second;
}

bool FlightService::cmpStr(const pair<string, int>& a, const pair<string, int>& b){
    return a.second > b.second;
}

bool FlightService::cmpFl(const pair<Flight*, float>& a, const pair<Flight*, float>& b){
    return a.second < b.second;
}

vector<twoFlightCost> FlightService::sortAMap(map<pair<Flight*,Flight*>, float>& vorodi){
    vector<twoFlightCost> A;
    for (auto& it : vorodi) {
        A.push_back(it);
    }
    sort(A.begin(), A.end(), cmp);
    return A;
}

vector<pair<string, int>> FlightService::sortAMap(map<string, int> toSort){
    vector<pair<string, int>> A;
        for (auto& it : toSort) {
        A.push_back(it);
    }
    sort(A.begin(), A.end(), cmpStr);
    return A;
}

float FlightService::getAverageFlightCost(){
    float sum = 0;
    int howManyFlight = 0;
    for(Flight* f:flights){
        sum += f->getFlightPrice("economy");
        howManyFlight++;
    }
    return sum/howManyFlight;
}

vector<float> FlightService::getMinAndMaxFlightCost(){
    vector<float> cost;
    vector<float> minAndMax;
    for(Flight* f:flights){
        cost.push_back(f->getFlightPrice("economy"));
    }
    minAndMax.push_back(*min_element(cost.begin(), cost.end()));
    minAndMax.push_back(*max_element(cost.begin(), cost.end()));
    return minAndMax;
}

string FlightService::getMostPopularDestination(){
    map<string, int> howManyBuys;
    for(Ticket* t:tickets){
        if(howManyBuys.find(t->getDestination()) == howManyBuys.end()){
            howManyBuys.insert(pair<string, int>(t->getDestination(), t->getQuantity()));
        }
        else{
            howManyBuys[t->getDestination()] += t->getQuantity();
        }
    }
    if(howManyBuys.size() == 0){
        return " ";
    }
    vector<pair<string, int>> sorted = sortAMap(howManyBuys);
    return sorted.front().first;
}

vector<pair<string, int>> FlightService::getTopAirlines(){
    map<string, int> topAirLines;
    for(Ticket* t:tickets){
        if(topAirLines.find(t->getAirline()) == topAirLines.end()){
            topAirLines.insert(pair<string, int>(t->getAirline(), t->getQuantity()));
        }
        else{
            topAirLines[t->getAirline()] += t->getQuantity();
        }
    }
    vector<pair<string, int>> sorted = sortAMap(topAirLines);
    return sorted;
}

vector<twoFlightCost> FlightService::getNonstraightFlightWithDate(int depDate){
    vector<twoFlightCost> tempNonStraightFlight;
    if(connectingFlights.size() != 0){
        vector<twoFlightCost> sortedFlights = sortAMap(connectingFlights);
        for(auto sortedFlight:sortedFlights){
            if(sortedFlight.first.first->getDepartureDate() == depDate){
                tempNonStraightFlight.push_back(sortedFlight);
            }
        }
    }
    return tempNonStraightFlight;
}

void FlightService::decideWhichIsCheapest(vector<twoFlightCost>  nonStraightFlight, vector<pair<Flight*, float>> straightFlights){
    if(nonStraightFlight.size() == 0 && straightFlights.size() == 0){
        notFoundRequestMsg();
        return;
    }
    if(nonStraightFlight.size() != 0 && straightFlights.size() == 0){
        flightPrintTemplate(nonStraightFlight.front(), false);
    }
    if(nonStraightFlight.size() == 0 && straightFlights.size() != 0){
        flightPrintTemplate(straightFlights.front());
    }
    if(nonStraightFlight.size() != 0 && straightFlights.size() != 0){
        if(nonStraightFlight.front().second >= straightFlights.front().second){
            flightPrintTemplate(straightFlights.front());
        }
        else{
            flightPrintTemplate(nonStraightFlight.front(), false);
        }
    }
}

void FlightService::checkForCheapestFlight(string _from, string _to, string _depDate){
    if(!isUserLogged()){
        permissionDeniedMsg();
        return;
    }
    int depDate = stoi(_depDate);
    vector<pair<Flight*, float>> straightFlights;
    for(Flight* f:flights){
        if(f->getDepartureDate() == depDate && f->getOrigin() == _from && f->getDestination() == _to){
            straightFlights.push_back(pair<Flight*, float>(f, f->getFlightPrice("economy")));
        }
    }
    sort(straightFlights.begin(), straightFlights.end(), cmpFl);
    getConnectingFlight(_from, _to);
    vector<twoFlightCost> tempNonStraightFlight = getNonstraightFlightWithDate(depDate);
    decideWhichIsCheapest(tempNonStraightFlight, straightFlights);

}

void FlightService::flightPrintTemplate(pair<Flight*, float> stFls){
    stFls.first->printFlightInfo();
    cout << "Total cost: " << fixed << setprecision(2) << stFls.first->getFlightPrice("economy");
    cout << endl;
}

void FlightService::report(){
    if(!isUserLogged()){
        permissionDeniedMsg();
        return;
    }
    cout << "average_flight_cost: " << getAverageFlightCost() << endl;
    cout << "min_flight_cost: " << getMinAndMaxFlightCost()[0] << endl;
    cout << "max_flight_cost: " << getMinAndMaxFlightCost()[1] << endl;
    cout << "most_popular_destination: " << getMostPopularDestination() << endl;
    vector<pair<string, int>> topAirline = getTopAirlines();
    cout << "top_airlines: ";
    if(topAirline.size() >=3 ){
        for(int i = 0; i > 2; i++){
            cout << topAirline[i].first << " ";
        }
        cout << endl;
    }
    else{
        for(auto top:topAirline){
            cout << top.first << " ";
        }
        cout << endl;
    }
}


