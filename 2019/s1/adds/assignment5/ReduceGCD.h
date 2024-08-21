#ifndef REDUCEGCD_H
#define REDUCEGCD_H

#include "ReduceGeneric.h"

class ReduceGCD: public ReduceGeneric{
	private:
	  int binOp(int, int);
	public:
		ReduceGCD(); 
};
#endif