###   make clean - Delete all o files and the executable


# define makefile variables
CC = g++
CFLAGS  = -g -Wall -Weffc++ -std=c++11
LFLAGS  = -L/usr/lib


cTrace: bin/main.o bin/Graph.o bin/Session.o bin/Agent.o bin/Tree.o 
	$(CC) -o bin/cTrace bin/main.o bin/Graph.o bin/Session.o bin/Agent.o bin/Tree.o $(LFLAGS) 
bin/main.o: src/main.cpp  
	$(CC) $(CFLAGS) -c -Iinclude -o bin/main.o src/main.cpp

bin/Graph.o: src/Graph.cpp  include/Graph.h
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Graph.o src/Graph.cpp
	
bin/Session.o: src/Session.cpp  include/Session.h
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Session.o src/Session.cpp

bin/Agent.o: src/Agent.cpp  include/Agent.h
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Agent.o src/Agent.cpp

bin/Tree.o: src/Tree.cpp  include/Tree.h
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Tree.o src/Tree.cpp
	

#Clean the build directory
clean: 
	rm -f bin/*
