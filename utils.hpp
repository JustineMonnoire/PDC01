#include "avlTreePosting.hpp"
#include <vector>

#ifndef __UTILS_H_INCLUDED__
#define __UTILS_H_INCLUDED__

class Utils{

	public:
	
		static std::vector<avlTreePosting::posting> merge(const std::vector<avlTreePosting::posting> vect1, const std::vector<avlTreePosting::posting> vect2);

};

#endif