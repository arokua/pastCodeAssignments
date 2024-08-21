#ifndef REDUCEMINIMUM_H
#define REDUCEMINIMUM_H

#include "ReduceGeneric.h"

class ReduceMinimum: public ReduceGeneric{
	private:
	  int binOp(int, int);
	public:
		ReduceMinimum(); 
};
#endif