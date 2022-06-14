CC := g++ --std=c++11

utravel.out: main.o manager.o readFile.o flightService.o flight.o user.o utils.o ticket.o
	$(CC) main.o manager.o readFile.o flightService.o flight.o user.o utils.o ticket.o -o utravel.out
main.o: main.cpp manager.o
	$(CC) -c main.cpp
manager.o: manager.cpp manager.hpp flightService.o readFile.o
	$(CC) -c manager.cpp
readFile.o: readFile.cpp readFile.hpp
	$(CC) -c readFile.cpp
flightService.o:flightService.cpp flightService.hpp flight.o user.o
	$(CC) -c flightService.cpp
ticket.o: ticket.cpp ticket.hpp flight.o
	$(CC) -c ticket.cpp
flight.o: flight.cpp flight.hpp utils.o
	$(CC) -c flight.cpp
user.o: user.cpp user.hpp ticket.o
	$(CC) -c user.cpp
utils.o: utils.cpp utils.hpp
	$(CC) -c utils.cpp
clean:
	rm -r *.o *.out