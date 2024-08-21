#include <iostream>
#include <string>
#include <sstream>

using namespace std;
void print_as_binary(string decimal_number){
	int theNum = stoi(decimal_number);
	string final ="";
	int index = 0;
	while (theNum > 0.5){
		final += to_string(theNum % 2);
		theNum /=2;
		index += 1;
	}
	while( index > 0){
		index -= 1;
		cout<< final.at(index);

	}

	cout<<"\n";
}
