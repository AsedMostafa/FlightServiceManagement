#include "user.hpp"

User::User(string _name, string _pass){
    userName = _name;
    password = _pass;
}

void User::chargeWallet(float chargeAmount){
    walletAmount += chargeAmount;
}

void User::addTicket(Ticket* t){
    walletAmount -= t->getTicketCost();
    tickets.push_back(t);
}

string User::printTickets(){
    if(tickets.size()==0){
        return "There is no ticket";
    }
    for(Ticket* t:tickets){
        return t->printInfo();
    }
}

bool User::isThisU(string user, string pass){
    if(user == userName && pass == password){
        return true;
    }
    return false;
}

void User::getTicketById(int _id){
    for(Ticket* t:tickets){
        if(_id == t->getTicketId()){
            t->printInfo();
            return;
        }
    }
    notFoundRequestMsg();

}

void User::cancleTicketById(int _id){
    int k = 0;
    for(Ticket* t:tickets){
        if(t->getTicketType() == "nonrefundable"){
            badRequestMsg();
            return;
        }
        if(t->getTicketId() == _id){
            walletAmount += 0.5 * t->getTicketCost();
            tickets.erase(tickets.begin() + k);
            successfulRequestMsg();
            return;
        }
        k++;
    }
    notFoundRequestMsg();
}