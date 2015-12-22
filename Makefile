
CC:= g++ 
OPTS:= -Wall -g 
LIBS:= -pthread -lboost_system -std=c++11
HEADERS:= alias_for_boost.h command.h monitor.h server.h session.h users.h
SOURCES:= monitor.cc server.cc session.cc 

ftpd : main.cc $(HEADERS) $(SOURCES)
	$(CC) $(OPTS) $^ -o $@ $(LIBS)

clean:
	rm -rf ftpd *.o 
