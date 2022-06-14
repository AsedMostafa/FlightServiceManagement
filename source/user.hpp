#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "ticket.hpp"
#include "utils.hpp"
#include "filters.hpp"

using namespace std;

class User{
public:
    User(string, string);
    void chargeWallet(float);
    void addTicket(Ticket*);
    string printTickets();
    string getUserName(){return userName;};
    double getWalletAmount(){return walletAmount;};
    bool isThisU(string, string);
    void getTicketById(int);
    void cancleTicketById(int);
private:
    string userName;
    string password;
    float walletAmount = 0;
    vector<Ticket*> tickets;
};

#endif