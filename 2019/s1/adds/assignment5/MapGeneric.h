#ifndef MAPGENERIC_H
#define MAPGENERIC_H

#include <vector>

class MapGeneric{
	private:
		virtual int f(int) = 0;
	public:
		MapGeneric();
		std::vector<int> map(std::vector<int>); //Serve as wrapper for the below function, since recursion is asked by the question
		std::vector<int> inMap(std::vector<int>, int); //Recursion here
};
#endif