#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <dirent.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;


struct PLread{
	ifstream* source;
	string sPL;
};
vector<ifstream*> files;
ofstream outputVocab("merged/vocab.txt", ios::in | ios::trunc);
ofstream outputPl("merged/postingLists.txt", ios::in | ios::trunc);
int plOffset = 1;
void writePLandWordToFile(string word, set<int> docIds);
void readOneTokenFromFiles(vector<ifstream*> &filesToRead, multimap<string, PLread> &tokensRead);

int main( int argc, const char* argv[] )
{
	DIR *rep;
	string dossier="memoryDumps";
	rep = opendir(dossier.c_str());
	struct dirent *lecture;

	multimap<string, PLread> tokensRead;
	cout<<"merging..."<<endl;
	//open all the files
	while ((lecture = readdir(rep))) {
		if(strcmp(lecture->d_name,".")!=0 and strcmp(lecture->d_name,"..")!=0){
			ifstream* myfile = new ifstream(dossier+"/"+lecture->d_name, ios::in);
			files.push_back(myfile);
		}
	}
	
	//read first token of files
	readOneTokenFromFiles(files, tokensRead);

	while(!files.empty()){
		//get all PL of the first word
		pair<multimap<string, PLread>::iterator, multimap<string, PLread>::iterator> ret;
		ret = tokensRead.equal_range(tokensRead.begin()->first);
		set<int> docIds;
		vector<ifstream*> filesToRead;
		//merge the docids
		for (multimap<string, PLread>::iterator itret=ret.first; itret!=ret.second; ++itret){
			stringstream ss( (itret->second.sPL) );
			while( ss.good() )
			{
				string sdocId;
				getline( ss, sdocId, ';' );
				if(!sdocId.empty()){
					docIds.insert(stoi(sdocId));
				}
			}
			//save files to read
			filesToRead.push_back(itret->second.source);
		}
		// write to filebuf
		writePLandWordToFile(tokensRead.begin()->first, docIds);
		// remove the word from the map and read the next word of the files
		tokensRead.erase(ret.first, ret.second);
	
		readOneTokenFromFiles(filesToRead, tokensRead);
	}
	outputVocab.close();
	outputPl.close();
	cout<<"merge done"<<endl;
	getchar();
	return 0;
}


void writePLandWordToFile(string word, set<int> docIds){
	outputVocab<< word << ";" << plOffset << endl;
	for(int docId : docIds){
		outputPl << docId << ";";
	}
	outputPl<<endl;
	plOffset++;
}	


 void readOneTokenFromFiles(vector<ifstream*> &filesToRead, multimap<string, PLread> &tokensRead){
	std::vector<ifstream*>::iterator it = filesToRead.begin();
	while ( it != filesToRead.end()){
		string word;
		string postingList;
		getline(**it,word);
		if(!(**it).good()){
			(*it)->close();
			files.erase(find(files.begin(), files.end(), *it));
			it++;
			continue;
		}
		getline(**it,postingList);
		if(!(**it).good()){
			(*it)->close();
			files.erase(find(files.begin(), files.end(), *it));
			it++;
			continue;
		}
		PLread plRead =  {*it, postingList};
		tokensRead.insert(make_pair(word, plRead));
		++it;
	}

}