#ifndef FILTERODD_H
#define FILTERODD_H

#include "FilterGeneric.h"

class FilterOdd: public FilterGeneric{
	private:
	  bool g(int);
	public:
		FilterOdd();
};
#endif