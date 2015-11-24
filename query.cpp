#include<iostream>
#include<fstream>
#include<string>
#include <set>
#include <sstream>
#include <map>
#include <algorithm> 

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
		if(results.empty()){
			cout<<"no docs founds";
		}else{
			for(int result : results){
				cout<<result<<" - ";
			}
		}
		cout<<endl;
		}
}


/*
 * search the docs including all the words given
 * return docIds
 */
set<int> search(set<string> words, map<string, int> vocab, string postingListFile){
	set<int> offsets;
	for(string word: words){ 
		map<string, int>::iterator it = vocab.find(word);
		if(it != vocab.end()){
			
			offsets.insert(it->second);
		}else{
			cout<<word<<" not found"<<endl;
		}		
	}
	set<int> results;
	
	ifstream plFile;
	int numberOfLineRead = 0;
	plFile.open(postingListFile);
	if (plFile.is_open())
	{
		
		for(int offset : offsets){
			//get postinglist
			string sPostingList;
			for(int i = numberOfLineRead ; i < offset; i++){
				getline (plFile,sPostingList);
				++numberOfLineRead;
			}
			//parse postinglist
			string sdocId;
			std::stringstream ss(sPostingList);
			set<int> docIdset;
			while (getline(ss,sdocId, ';'))
			{
				if(!sdocId.empty()) docIdset.insert(stoi(sdocId));
			}		
			if(results.empty()){
				results = docIdset;
			}else{
				set<int> intersection;
				set_intersection(results.begin(),results.end(),docIdset.begin(),docIdset.end(),
					  std::inserter(intersection,intersection.begin()));
				results = intersection;
			}
		}
		plFile.close();
	}
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