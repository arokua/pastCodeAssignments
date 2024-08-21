#ifndef EFFICENTFIBONACCI_H

#define EFFICENTFIBONACCI_H


#include <vector>


class EfficientFibonacci {

	private:

		std::vector<int>record; //Hold the calculated numbers

	public:
		EfficientFibonacci();
		int calc(int);
};
#endif