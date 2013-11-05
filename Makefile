CC=g++ -std=c++0x -c -g

all: assn04

assn04: main.o element.o auxFunctionsXML.o Doolittle.xml
	g++ main.o element.o auxFunctionsXML.o -o assn04

main.o: main.cpp element.h auxFunctionsXML.h
	$(CC) main.cpp

element.o: element.cpp element.h
	$(CC) element.cpp
	
auxFunctionsXML.o: auxFunctionsXML.cpp auxFunctionsXML.h element.h
	$(CC) auxFunctionsXML.cpp

clean:
	rm -rf *.o
	rm -rf *.~
	rm -rf assn04
