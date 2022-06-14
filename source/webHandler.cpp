#include "webHandler.hpp"

SignupHanlder::SignupHanlder(FlightService* service): CallbackHandler(service){
    main = service;
}

LoginHandler::LoginHandler(FlightService* service): CallbackHandler(service){
    main = service;
}

CallbackHandler::CallbackHandler(FlightService* service){
    main = service;
}

UserHandler::UserHandler(FlightService* fl): CallbackHandler(fl){
    main = fl;
}

HandleCppHtml::HandleCppHtml(string _filePath, FlightService* fl): TemplateHandler(_filePath){
    main = fl;
}

Response *CallbackHandler::callback(Request* req){
    Response* res = new Response;
    if(req->getMethod() == GET){
        res = getHandler(req);
    }
    if(req->getMethod() == POST){
        res = postHandler(req);
    }
    return res;
}

Response *LoginHandler::getHandler(Request* req){
    string filePath = "htmlFiles/login.html";
    string fileType = "text/" + getExtension(filePath);
    string session = req->getSessionId();
    Response* res = new Response;
    res->setHeader("Content-Type", fileType);
    res->setBody(readFile(filePath.c_str()));
    if(main->loginUser(session)){
        return res->redirect("/user");
    }
    else{
        return res;
    }

}

Response *LoginHandler::postHandler(Request* req){
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    bool validate = main->validateAndLoginUser(username, password);
    Response *res = new Response;
    if(validate){
        return res->redirect("/user");
    }
    else{
        return res->redirect("/permissonDenied");
    }
}


Response *SignupHanlder::getHandler(Request* req){
    string filePath = "htmlFiles/signup.html";
    string fileType = "text/" + getExtension(filePath);
    string session = req->getSessionId();
    Response* res = new Response;
    res->setHeader("Content-Type", fileType);
    res->setBody(readFile(filePath.c_str()));
    if(main->loginUser(session)){
        return res->redirect("/user");
    }
    else{
        return res;
    }
}

Response *SignupHanlder::postHandler(Request* req){
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    bool a = main->addUser(username, password);
    Response *res = new Response;
    if(!a){
        return res->redirect("/badRequest");
    }
    if(main->isUserLogged()){
        res->setSessionId(username);
        return res->redirect("/user");
    }
}

Response *FlightHandler::postHandler(Request* req){
    Response *res = new Response;
    return res;
}

Response *FlightHandler::getHandler(Request* req){
    Response *res = new Response;
    return res;
}

Response *UserHandler::getHandler(Request* req){
    Response *res = new Response;
    if(!main->isUserLogged()){
        return res->redirect("/permissionDenied");
    }
    string charge = req->getQueryParam("chargeAmount");
    main->wallet(charge);

    return res;
}

Response *UserHandler::postHandler(Request* req){
    Response *res = new Response;
    string emptySession = "";
    res->setSessionId(emptySession);
    main->logoutUser();
    return res->redirect("/login");
}


handleUser::handleUser(string filePath, FlightService* fl): HandleCppHtml(filePath, fl){
    user = new UserHandler(main);
}

HandleFlight::HandleFlight(string filePath, FlightService* fl): HandleCppHtml(filePath, fl){
    flight = new FlightHandler(main);
}

FlightHandler::FlightHandler(FlightService* fl):CallbackHandler(fl){
    main = fl;
}

map<string, string> HandleFlight::handle(Request *req){
    map<string, string> context;
    int id = stoi(req->getQueryParam("id"));
    context["flight"] = main->printFlightById(id);
    return context;
}

map<string, string> handleUser::handle(Request *req) {
    map<string, string> context;
    string walletAmount = to_string(main->printUserWalletAmount());
    context["walletAmount"] = walletAmount;
    string flights = main->printFlights();
    context["printFlights"] = flights;
    string tickets = main->printAllUserTickets();
    context["tickets"]= tickets;
    /*string newName = "I am " + req->getQueryParam("name");
    context["name"] = newName;
    context["color"] = req->getQueryParam("color");*/
    return context;
}

Response *HandleFlight::callback(Request* req){
    map<string, string> context;
    Response *res = new Response;
    res = this->flight->callback(req);
    context = this->handle(req);
    res->setHeader("Content-Type", "text/html");
    res->setBody(parser->getHtml(context));
    return res;
}

Response *handleUser::callback(Request* req){
    map<string, string> context;
    Response *res = new Response;
    res = this->user->callback(req);
    if(!main->isUserLogged()){
        res->redirect("/login");
        return res;
    }
    context = this->handle(req);
    res->setHeader("Content-Type", "text/html");
    res->setBody(parser->getHtml(context));
    return res;
}

PermissionDeniedHandler::PermissionDeniedHandler(FlightService* fl):CallbackHandler(fl){
    main = fl;
}

Response *PermissionDeniedHandler::getHandler(Request* req){
    Response *res = new Response;
    string filePath = "htmlFiles/permissionDenied.html";
    string fileType = "text/" + getExtension(filePath);
    res->setHeader("Content-Type", fileType);
    res->setBody(readFile(filePath.c_str()));
    return res;
}

Response *PermissionDeniedHandler::postHandler(Request* req){
    //to do
}






