#include <stdio.h>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <string.h>
#include "parser.h"
#include "avlTreePosting.hpp"
#include "utils.hpp"
#include <boost/tokenizer.hpp>
#include <map>
#include <cstddef>
#include <algorithm>

#define MAX_TO_CREATE_FILE 10000

using namespace std;

void writeFileWithMap(std::map<string, vector<int>> map);
int iFiles = 0;

int main( int argc, const char* argv[] )
{
	std::map<string, vector<int> > wordPostingListMap;
	string filenamePrefix = "avldump";
	int nbDump = 0;
	//avlTreePosting avl;
    Parser parser;
	DIR *rep;
	string dossier="Fichiers";
	rep = opendir(dossier.c_str());
	struct dirent *lecture;
				vector<int> docIdVector;
				std::map<string, vector<int> >::iterator it;
	while ((lecture = readdir(rep))) {
        int codeErreur =parser.openFile(dossier+"/"+lecture->d_name);
        if(strcmp(lecture->d_name,".")!=0 and strcmp(lecture->d_name,"..")!=0){
			if(codeErreur == 0){
				// file successfully read
				cout << "reading "<< lecture->d_name <<endl;
				Parser::Token tok = parser.getNextToken();
				int i = 0;
				while(true)
				{
					if(tok.docId == -1)
					{
						writeFileWithMap(wordPostingListMap);
						break;
					}

					if(i == MAX_TO_CREATE_FILE)
					{
						writeFileWithMap(wordPostingListMap);
						wordPostingListMap.clear();
						i=0;
					}

					it = wordPostingListMap.find(tok.word);
					if(it != wordPostingListMap.end()) //If the word exist
					{
						//cout << "Mot existe deja : " << tok.word << " | fichier associe : " << tok.docId << endl;//Test block
						docIdVector = wordPostingListMap[tok.word];
						if(std::find(docIdVector.begin(), docIdVector.end(), tok.docId) == docIdVector.end()) //If the docId is not found
						{
							wordPostingListMap[tok.word].push_back(tok.docId);
						}
						//Get the vector
						//Add docId to the vector
						//Replace data in the map for the defined word
					}
					else
					{
						//cout << "Ajout du mot : " << tok.word << " | fichier associe : " << tok.docId << endl; //Test block
						docIdVector.push_back(tok.docId); //Create the vector
						wordPostingListMap.insert( std::pair<string,vector<int>>(tok.word,docIdVector) ); //Insert data in the map
					}
					docIdVector.clear();

					/*try{
						avl.root = avl.insert(avl.root, &tok.word,  &tok.docId);
					} catch (std::bad_alloc&) {	
						cout << "avl to file " << filenamePrefix + std::to_string(nbDump) + ".txt" <<endl;
						avl.inorder(avl.root, filenamePrefix + std::to_string(nbDump) + ".txt");
						++nbDump;
					}*/					
					i++;
					tok = parser.getNextToken();
				}
				
			} else {
				cerr<<codeErreur;
			}
        }
	}
	//Test block to show the wordPostingListMap
	/*it = wordPostingListMap.begin();
				while(it != wordPostingListMap.end())
				{
					cout << "\nMot : " << it->first << endl;
					std::vector<int>::iterator itDoc;
					itDoc = it->second.begin();
					while(itDoc != it->second.end())
					{
						cout << "Fichier : " << *itDoc << "	";
						++itDoc;
					}

					++it;
				}*/
	//cout << "avl to file " << filenamePrefix + std::to_string(nbDump) + ".txt" <<endl;
	//avl.inorder(avl.root, filenamePrefix + std::to_string(nbDump) + ".txt");
	return 0;
}

void writeFileWithMap(std::map<string, vector<int>> map)
{

	ofstream myfile;
	string fileName = std::string("invertedFile") + std::to_string(iFiles) + std::string(".txt");
	myfile.open(fileName, ios::trunc);

	std::map<string, vector<int> >::iterator it;
	it = map.begin();
	while(it != map.end())
	{
		myfile << it->first << endl;
		std::vector<int>::iterator itDoc;
		itDoc = it->second.begin();
		while(itDoc != it->second.end())
		{
			myfile << *itDoc << ";";
			++itDoc;
		}
		myfile << endl;

		++it;
	}
	myfile.close();

	iFiles++;
}
