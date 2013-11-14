CC=g++ -std=c++0x -c -g

all: assn04

assn04: main.o element.o auxFunctionsXML.o attribute.o Doolittle.xml
	g++ main.o element.o attribute.o auxFunctionsXML.o -o assn04

main.o: main.cpp element.h auxFunctionsXML.h attribute.h
	$(CC) main.cpp

element.o: element.cpp element.h
	$(CC) element.cpp

attribute.o: attribute.cpp attribute.h
	$(CC) attribute.cpp
	
auxFunctionsXML.o: auxFunctionsXML.cpp auxFunctionsXML.h element.h
	$(CC) auxFunctionsXML.cpp

clean:
	rm -rf *.o
	rm -rf *.~
	rm -rf assn04
