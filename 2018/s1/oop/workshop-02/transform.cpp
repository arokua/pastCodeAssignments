#include <iostream>
#include <string>
using namespace std;
int transform(int num, int toBase){
	int index = 0;
	int rawresult[] = {};
	string reverse;
	string nuu;

	if (toBase == 2) {
		while (num > 0.5){
			rawresult[index] = num % 2;
			nuu += to_string(num % 2);
			num = num  / 2;
						
			index += 1;
		}
		int len = nuu.length();

		while ( len > 0) {
			len -= 1;
			reverse += nuu.at(len);
		}
		cout<< reverse << "\n";

	}
}

int main() {
	transform(11, 2);  
}