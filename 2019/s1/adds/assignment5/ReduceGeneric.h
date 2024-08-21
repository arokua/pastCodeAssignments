#ifndef REDUCEGENERIC_H
#define REDUCEGENERIC_H

#include <vector>

class ReduceGeneric{
	private:
		virtual int binOp(int, int) = 0;
	public:
		ReduceGeneric();
		int reduce(std::vector<int>); //Serve as wrapper for the below function, since recursion is asked by the question
		int inReduce(std::vector<int>, int, int); //Recursion here
};
#endif