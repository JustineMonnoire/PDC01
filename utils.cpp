#include <vector>
#include <stdio.h>
#include <iostream>
#include "utils.hpp"

using namespace std;

vector<avlTreePosting::posting> Utils::merge(const vector<avlTreePosting::posting> vect1, const vector<avlTreePosting::posting> vect2){
	vector<avlTreePosting::posting> result;
	if(vect1.back().doCID == vect2.front().doCID)
	{
		result.reserve(vect1.size()+vect2.size()-1); //prevent reallocation
		result.insert(result.end(), vect1.begin(), vect1.end());
		result.back().frequency += vect2.front().frequency;
		result.insert(result.end(), vect2.begin()+1, vect2.end());
	}else
	{
		result.reserve(vect1.size()+vect2.size()); //prevent reallocation
		result.insert(result.end(), vect1.begin(), vect1.end());
		result.insert(result.end(), vect2.begin(), vect2.end());
	}
	return result;
};


