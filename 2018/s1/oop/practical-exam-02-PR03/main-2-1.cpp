#include <iostream>
#include <string>

using namespace std;
// line 2 and 4 are needed so that the following lines are complie-able
extern string latest(string*, int );

int main() {
	// an array to the test the above imported function
	string atest[3] = {"June", "July", "March"};
	//Expected output: July

	//See if the "latest" function work as expected.
	cout<< latest(atest, 3);
}