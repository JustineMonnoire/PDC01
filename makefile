all: 
	g++ -std=c++11 -Ilibs/boost_1.59.0/ main.cpp parser.cpp  -o mainApp
	
clean: 
	rm *.o mainApp