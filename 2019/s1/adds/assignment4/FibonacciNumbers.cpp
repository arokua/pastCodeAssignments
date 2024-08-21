#include "FibonacciNumbers.h"

using namespace std;

FibonacciNumbers::FibonacciNumbers(){}

int FibonacciNumbers::calc(int n){
	if (n < 2){
		return n % 2; // base case
	}
	return calc(n - 1) + calc(n - 2);
}