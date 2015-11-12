all: 
	g++ -std=c++11 -Ilibs/boost_1.59.0/ main.cpp parser.cpp avlTreePosting.cpp utils.cpp  -o mainApp
	
clean: 
	rm *.o mainApp