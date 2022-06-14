#ifndef WEBHANDLER_H
#define WEBHANDLER_H

#include "../server/server.hpp"
#include "flightService.hpp"


class CallbackHandler: public RequestHandler{
public:
    CallbackHandler(FlightService*);
    Response *callback(Request *);
    virtual Response *getHandler(Request *) = 0;
    virtual Response *postHandler(Request *) = 0;
protected:
    FlightService* main;
};

class SignupHanlder: public CallbackHandler{
public:
    SignupHanlder(FlightService*);
    Response *getHandler(Request *);
    Response *postHandler(Request *);
private:
    FlightService* main;
};


class LoginHandler: public CallbackHandler{
public:
    LoginHandler(FlightService*);
    Response *getHandler(Request *);
    Response *postHandler(Request *);
private:
    FlightService* main;
};

class UserHandler: public CallbackHandler{
public:
    UserHandler(FlightService*);
    Response *getHandler(Request *);
    Response *postHandler(Request *);
private:
    FlightService* main;

};

class HandleCppHtml: public TemplateHandler{
public:
    HandleCppHtml(string, FlightService*);
    virtual map<string, string> handle(Request *req) = 0;
protected:
    FlightService* main;
};

class handleUser: public HandleCppHtml{
public:
    handleUser(string, FlightService*);
    map<string, string> handle(Request *req);
    Response *callback(Request *req);
private:
    UserHandler* user;
};

class FlightHandler: public CallbackHandler{
public:
    FlightHandler(FlightService*);
    Response *getHandler(Request *);
    Response *postHandler(Request *);
private:
    FlightService* main;

};

class HandleFlight: public HandleCppHtml{
public:
    HandleFlight(string, FlightService*);
    map<string, string> handle(Request *req);
    Response *callback(Request *req);
private:
    FlightHandler* flight;
};

class PermissionDeniedHandler: public CallbackHandler{
public:
    PermissionDeniedHandler(FlightService*);
    Response *getHandler(Request *);
    Response *postHandler(Request *);
private:
    FlightService* main;
};




#endif