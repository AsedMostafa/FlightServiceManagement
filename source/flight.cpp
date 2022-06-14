#include "flight.hpp"

Flight::Flight(string _airline, string _org, string _dest, int dpDate, string dpTime,
                int arDate, string arTime, int _seats, float _cost, int _id){
    airline = _airline;
    origin = _org;
    destination = _dest;
    departureDate = dpDate;
    departureTime = parseTimeFromString(dpTime);
    arrivalDate = arDate;
    arrivalTime = parseTimeFromString(arTime);
    seats = _seats;
    availableSeats = _seats;
    price = _cost;
    id = _id;
    businessCapacity = seats * 0.25;
    economyCapacity = seats * 0.75;
}

string Flight::printFlightInfo(bool printPrice){
    time_t dpT = chrono::system_clock::to_time_t(departureTime);
    time_t arT = chrono::system_clock::to_time_t(arrivalTime); 
    ostringstream print;
    print
    << "<tr>"
    
    << "<td> " << airline << "</td> " << "<td> " << origin << "</td> " << "<td> "<< destination << " "
    << "<td> " << departureDate <<"</td> " <<"<td> " <<put_time(localtime(&dpT), "%H:%M") << "</td> "
    <<"<td> " << arrivalDate <<"</td> " << "<td> "<<put_time(localtime(&arT), "%H:%M") << "</td> ";
    if(printPrice){
        print
        << "<td> "<<availableSeats << "</td> "<< " " << fixed << setprecision(2) <<"<td> "<< price << "</td> "
        << "</td>"
        << "<td><a href='flight?id=" << id << "'><button>"<< "Buy" <<"</button></a></td>"
        << "</tr>";
    }
    return print.str();
}

bool Flight::stillHasCapacity(){
    if(availableSeats > 0){
        return true;
    }
    return false;
}

bool Flight::stillHasBuisinessCapacity(int quant){
    if(businessCapacity >= quant){
        return true;
    }
    return false;
}

bool Flight::stillHasEconomyCapacity(int quant){
    if(economyCapacity >= quant){
        return true;
    }
    return false;
}

void Flight::reduceCapacity(string _type, int count){
    availableSeats -= count;
    if(_type == "economy"){
        economyCapacity -= count;
    }
    if(_type == "business"){
        businessCapacity -= count;
    }
}

float Flight::getFlightPrice(string _type){
    if(_type == "economy"){
        return price;
    }
    if(_type == "business"){
        return 2.5 * price;
    }
}

bool Flight::isThisYourOrigin(string _from){
    if(origin == _from){
        return true;
    }
    return false;
}

bool Flight::isThisYourDestination(string _to){
    if(destination == _to){
        return true;
    }
    return false;
}