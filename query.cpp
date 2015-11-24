#include<iostream>
#include<fstream>
#include<string>
#include <set>
#include <sstream>
#include <map>

using namespace std;


set<int> search(set<string> words, map<string, int> vocab, string postingListFile = "merged/postingLists.txt");
void interactiveMode(map<string, int> vocab);
map<string, int> loadVocab(string = "merged/vocab.txt");

int main(int argc, char* argv[]){
	map<string, int> vocab = loadVocab();
	if(argc>1){
		set<string> words(argv+1, argv + argc);
		set<int> results = search(words, vocab);
		for(int result: results){
			cout<<result<<";";
		}
		cout<<endl;
	}else{
		interactiveMode(vocab);	
	}
	
}

void interactiveMode(map<string, int> vocab){
	cout<<"interactive mode"<<endl;
	cout<<"type words separated by a comma, empty list to stop"<<endl;
	while(true){
		cout<<">";
		string wordReads;
		string wordRead;
		set<string> words;
		std::getline( cin, wordReads );
		std::stringstream ss(wordReads);

		while (getline(ss,wordRead, ','))
		{
			words.insert(wordRead);
		}
		if(words.empty()) return;
		
		set<int> results = search(words, vocab);
		for(int result : results){
			cout<<result<<";";
		}
		cout<<endl;
		}
}


/*
 * search the docs including all the words given
 * return docIds
 */
set<int> search(set<string> words, map<string, int> vocab, string postingListFile){
	cout<<" -- trace - words searched :"<< endl;
	for(string word: words){ 
		map<string, int>::iterator it = vocab.find(word);
		if(it != vocab.end()){
			cout<<word<<" - offset : "<<it->second<<endl;
		}else{
			cout<<word<<" not found"<<endl;
		}
		
		
	}
	set<int> results;
	results.insert(1);
	results.insert(5);
	return results;
}

map<string, int> loadVocab(string fileUrl ){
	map<string, int>  vocab;
	ifstream vocabFile;
	vocabFile.open(fileUrl);
	if (vocabFile.is_open())
	{
		string line;
		while ( getline (vocabFile,line) )
		{
			string word;
			string soffset;
			stringstream ss(line);
			getline (ss,word, ';');
			getline (ss,soffset);
			vocab.insert(make_pair(word, stoi(soffset)));
		}
	vocabFile.close();
	}else{
		cerr<< "couldn't open vocab file"<<endl;
	}

	return vocab;
}