#include <stdio.h>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include<string>
#include "parser.h"
#include "avlTreePosting.hpp"
#include "utils.hpp"
#include<boost/tokenizer.hpp>

using namespace std;

int main( int argc, const char* argv[] )
{
	string filenamePrefix = "avldump";
	int nbDump = 0;
	avlTreePosting avl;
    Parser parser;
	DIR *rep;
	string dossier="Fichiers";
	rep = opendir(dossier.c_str());
	struct dirent *lecture;
	while ((lecture = readdir(rep))) {
        int codeErreur =parser.openFile(dossier+"/"+lecture->d_name);
        if(strcmp(lecture->d_name,".")!=0 and strcmp(lecture->d_name,"..")!=0){
			if(codeErreur == 0){
				// file successfully read
				cout << "reading "<< lecture->d_name <<endl;
				Parser::Token tok = parser.getNextToken();
				while(tok.docId != -1)
				{					
					try{
						avl.root = avl.insert(avl.root, &tok.word,  &tok.docId);
					} catch (std::bad_alloc&) {	
						cout << "avl to file " << filenamePrefix + std::to_string(nbDump) + ".txt" <<endl;
						avl.inorder(avl.root, filenamePrefix + std::to_string(nbDump) + ".txt");
						++nbDump;
					}					
					tok = parser.getNextToken();
				}
				
			} else {
				cerr<<codeErreur;
			}
        }
	}
	cout << "avl to file " << filenamePrefix + std::to_string(nbDump) + ".txt" <<endl;
	avl.inorder(avl.root, filenamePrefix + std::to_string(nbDump) + ".txt");
	return 0;
}