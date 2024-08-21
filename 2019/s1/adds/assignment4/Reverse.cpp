#include <string>
#include <cmath>
#include <iostream>
#include "Reverse.h"

using namespace std;

Reverse::Reverse(){
	
}
int Reverse::reverseDigits(int n){
	//Wrapper in order to have more parameters for recursive function
	return rD(n, int( to_string(n).length()), 0, 0); 
}
int Reverse::rD(int n, int length, int counter, int temp){
	if (counter == length){ //Base case
		return temp;
	}
	temp += int(n / pow(10, length - counter - 1)) * int(pow(10, counter)) ; //Get the first digit out of n
	return rD(n % int( pow(10, length - counter - 1)), length, counter + 1, temp); //n without the original first digit that has been moved to temp
}

string Reverse::reverseString(std::string s){
	return rS(s, int(s.length()), 0);
}

string Reverse::rS(std::string s, int len, int pos){
	if ( int(s.length()) == 2 * len ){
		return s.substr(len, len); // The second half of s is the reversed string
	}
	return rS(s + s.substr(len - pos - 1, 1), len, pos + 1); // append the i-th character from the right of s to the end of s
}