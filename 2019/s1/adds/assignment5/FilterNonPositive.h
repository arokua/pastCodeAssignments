#ifndef FILTERNONPOSITIVE_H
#define FILTERNONPOSITIVE_H

#include "FilterGeneric.h"

class FilterNonPositive: public FilterGeneric{
	private:
	  bool g(int);
	public:
		FilterNonPositive();
};
#endif