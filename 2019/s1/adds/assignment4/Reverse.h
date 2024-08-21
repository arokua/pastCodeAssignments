#ifndef REVERSE_H
#define REVERSE_H

#include <string>

class Reverse {
	public:
		Reverse();
		int reverseDigits(int); //Wraper
		int rD(int, int, int, int); //Actual recursive func
		std::string reverseString(std::string); //Wrapper
		std::string rS(std::string, int, int); //recursion here
};
#endif