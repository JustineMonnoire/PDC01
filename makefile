all: parser merge query

parser: 
	test -d memoryDumps || mkdir memoryDumps
	g++ -std=c++11 -Ilibs/boost_1.59.0/ main.cpp parser.cpp avlTreePosting.cpp utils.cpp  -o parser

merge:
	test -d merged || mkdir merged
	g++ -std=c++11 merge.cpp -o merge
	
query:
	g++ -std=c++11 query.cpp -o query	
	
clean: 
	rm *.o mainApp memoryDumps/*