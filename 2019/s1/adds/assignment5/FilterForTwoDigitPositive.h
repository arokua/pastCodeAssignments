#ifndef FILTERFORTWODIGITPOSITIVE_H
#define FILTERFORTWODIGITPOSITIVE_H

#include "FilterGeneric.h"

class FilterForTwoDigitPositive: public FilterGeneric{
	private:
	  bool g(int);
	public:
		FilterForTwoDigitPositive();
};
#endif