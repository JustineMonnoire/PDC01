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

void printvector(vector<avlTreePosting::posting> vect )
{
	for(vector<avlTreePosting::posting>::iterator it = vect.begin(); it != vect.end(); ++it) {
		cout<<it->doCID<< "  -  "<<it->frequency<<endl;
	}
}

int main( int argc, const char* argv[] )
{
	vector<avlTreePosting::posting> vect1;
	
	vector<avlTreePosting::posting>vect2;
	
	vector<avlTreePosting::posting> vect3;
	
	for(int i = 1; i<5; ++i ){
		vect1.push_back({i,i});
	};
	for(int i = 4; i<8; ++i ){
		vect2.push_back({i,i});
	};
	for(int i = 7; i<10; ++i ){
		vect3.push_back({i,i});
	};
	
	
	cout<<" vect1 : "<<endl;
	printvector(vect1);
	cout<<" vect2 : "<<endl;
	printvector(vect2);
	cout<<" vect3 : "<<endl;
	printvector(vect3);
	cout<<" result : "<<endl;
	vector<avlTreePosting::posting> result = Utils::merge(Utils::merge(vect1,vect2), vect3);
	
	printvector(result);
 
	cout << "press enter" <<endl;
	getchar();

	avlTreePosting avl;
    Parser parser;
	DIR *rep;
	string dossier="Fichiers";
	rep = opendir(dossier.c_str());
	struct dirent *lecture;
	while ((lecture = readdir(rep))) {
		int previousDocId = -1;
        int codeErreur =parser.openFile(dossier+"/"+lecture->d_name);
        if(strcmp(lecture->d_name,".")!=0 and strcmp(lecture->d_name,"..")!=0){
			if(codeErreur == 0){
				// file successfully read
				Parser::Token tok = parser.getNextToken();
				while(tok.docId != -1)
				{					
					if(previousDocId != tok.docId){
						previousDocId = tok.docId;
						cout << "parsing doc " << tok.docId << endl;
					}
					avl.root = avl.insert(avl.root, &tok.word,  &tok.docId);
					tok = parser.getNextToken();
				}
			} else {
				cerr<<codeErreur;
			}
        }
	}
	cout << "press enter" <<endl;
	getchar();
	cout << "avl to file ..." <<endl;
	avl.inorder(avl.root);
	
	return 0;
}