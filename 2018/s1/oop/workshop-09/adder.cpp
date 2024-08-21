#include <iostream>

using namespace std;

// program to add two numbers together
int main()
{
	int x,y,z ;

	// prompt for user input
	cout << "Enter x: " ;
	cin >> x ;
	cout << "Enter y: " ;
	cin >> y ;

	// work out the sum
	z = x + y ;

	// tell the user what was entered and the sum
	cout << "x = " << x << ", y = " << y << ", " ;
	cout << "x + y = " << z << endl ;

	// normal finish - exit with 0
	return 0 ;
}
