#include <stdio.h>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include "parser.h"
#include<boost/tokenizer.hpp>

using namespace std;

Parser::Parser() : tokenizer(string()){
	tokIterator = tokenizer.begin();
	docsIt = docs.begin();
}

int Parser::openFile(string filename) {
    string ch;
    string doc;
    string text;
    int add;
    ifstream fichier(filename, ios::in); // on ouvre le fichier en lecture

    if (fichier) // si l'ouverture a réussi
    {
        // on vide le vecteur de docs à chaque fichier 
        docs.clear();
        Doc newDocStruct{-1, ""};
        string ligne;
        while (getline(fichier, ligne)) 
        {
            ch = ligne.substr(0,1);
            doc = ligne.substr(0,7);
            if (doc=="<DOCID>"){
				// ajouter le doc dans docs
                // remplir doc.docid dans la struct du doc
				// créer une nouvelle structure doc
				
				
				if(newDocStruct.docId != -1){
					//we were reading a previous doc, save it 
					docs.push_back(newDocStruct);  // make a copy of it, we can reuse this variable now
				}
				newDocStruct = {std::stoi(ligne.substr(7, ligne.length() - 15)), ""};  // TODO get docId from text
                add=0;
            }
            else if (ch == "<") {
                add = 0;
            } 
            else {
                add = 1;
            }

            if (add==1){
				newDocStruct.text += ligne;
            }
        }
		docs.push_back(newDocStruct); //add the last doc
        fichier.close(); // on ferme le fichier
		
		if(!docs.empty()){
			docsIt = docs.begin();
			tokenizer = boost::tokenizer<>((*docsIt).text);
			tokIterator = tokenizer.begin();
		}else{
			// the file is not correct
			return 2;
		}
        
        return 0;
    } else {
        return 1;
    }
}

Parser::Token Parser::getNextToken(){
    if(docs.empty()) {
		throw -1;
	}
	Parser::Token tok;
	if(tokIterator != tokenizer.end()){
		tok.word = *tokIterator;
		++tokIterator;
	}else{
		//the current doc is fully read
		if(++docsIt != docs.end()){
			//there is still docs to read, go to next one and parse its text
			tokenizer = boost::tokenizer<>(docsIt->text);
			tokIterator= tokenizer.begin();
			tok.word = *tokIterator;
			++tokIterator;
		}else{
			//the file is fully read
			return Parser::Token{-1, ""};
		}
	}
	tok.docId = docsIt->docId;
	return tok;
}