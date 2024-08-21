#ifndef FILTERGENERIC_H
#define FILTERGENERIC_H

#include <vector>

class FilterGeneric{
	private:
		virtual bool g(int) = 0;
	public:
		FilterGeneric();
		std::vector<int> filter(std::vector<int>); //Serve as wrapper for the below function, since recursion is asked by the question
		std::vector<int> inFilter(std::vector<int>, int); //Recursion here
};
#endif