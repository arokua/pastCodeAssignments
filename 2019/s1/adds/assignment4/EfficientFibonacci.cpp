#include <vector>
#include "EfficientFibonacci.h"
#include "FibonacciNumbers.h"
using namespace std;

EfficientFibonacci::EfficientFibonacci(){
	record.push_back(0);
	record.push_back(1);
}

int EfficientFibonacci::calc(int n){
    if (n < int(record.size()) ){
            return record[n]; //Base case
    }
    int a = calc(n - 1) + calc(n - 2);
    record.push_back(a);
    if (n < int(record.size()) ){ // If new size > 1 then just return latest number
        return record[n];
    }//Otherwise then just do n - 1 and recurse
    return calc(n - 1);
}