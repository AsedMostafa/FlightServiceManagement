CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all:$(BUILD_DIR) utravel.out

utravel.out: $(BUILD_DIR)/main.o $(BUILD_DIR)/manager.o $(BUILD_DIR)/webHandler.o $(BUILD_DIR)/readFile.o $(BUILD_DIR)/flightService.o $(BUILD_DIR)/flight.o $(BUILD_DIR)/user.o $(BUILD_DIR)/utils.o $(BUILD_DIR)/ticket.o $(BUILD_DIR)/my_server.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/webHandler.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/manager.o $(BUILD_DIR)/readFile.o $(BUILD_DIR)/flightService.o $(BUILD_DIR)/flight.o $(BUILD_DIR)/user.o $(BUILD_DIR)/utils.o $(BUILD_DIR)/ticket.o -o utravel.out
$(BUILD_DIR)/main.o: source/main.cpp $(BUILD_DIR)/manager.o $(BUILD_DIR)/webHandler.o
	$(CC) -c source/main.cpp -o $(BUILD_DIR)/main.o
$(BUILD_DIR)/webHandler.o:source/webHandler.cpp source/webHandler.hpp  $(BUILD_DIR)/server.o
	$(CC) -c source/webHandler.cpp -o $(BUILD_DIR)/webHandler.o
$(BUILD_DIR)/manager.o: source/manager.cpp source/manager.hpp $(BUILD_DIR)/flightService.o $(BUILD_DIR)/readFile.o
	$(CC) -c source/manager.cpp -o $(BUILD_DIR)/manager.o
$(BUILD_DIR)/readFile.o: source/readFile.cpp source/readFile.hpp
	$(CC) -c source/readFile.cpp -o $(BUILD_DIR)/readFile.o
$(BUILD_DIR)/flightService.o:source/flightService.cpp source/flightService.hpp $(BUILD_DIR)/flight.o $(BUILD_DIR)/user.o
	$(CC) -c source/flightService.cpp -o$(BUILD_DIR)/flightService.o
$(BUILD_DIR)/ticket.o: source/ticket.cpp source/ticket.hpp $(BUILD_DIR)/flight.o
	$(CC) -c source/ticket.cpp -o $(BUILD_DIR)/ticket.o
$(BUILD_DIR)/flight.o: source/flight.cpp source/flight.hpp $(BUILD_DIR)/utils.o
	$(CC) -c source/flight.cpp -o $(BUILD_DIR)/flight.o
$(BUILD_DIR)/user.o: source/user.cpp source/user.hpp $(BUILD_DIR)/ticket.o
	$(CC) -c source/user.cpp -o $(BUILD_DIR)/user.o
$(BUILD_DIR)/utils.o: source/utils.cpp source/utils.hpp
	$(CC) -c source/utils.cpp -o $(BUILD_DIR)/utils.o
$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o
$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o
$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o
$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o
$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o
$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o
$(BUILD_DIR)/handlers.o: examples/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c examples/handlers.cpp -o $(BUILD_DIR)/handlers.o
$(BUILD_DIR)/my_server.o: examples/my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c examples/my_server.cpp -o $(BUILD_DIR)/my_server.o
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
