#include <iostream>
#include <vector>
using namespace std;


/* Task 2: Implement the following function recursively to produce the i-th element of the described sequence.
 */
int Sequence2(int i, int now){
	//Try tail-recursion version
	if ( i == 1){
		return now;
	}
	return Sequence2(i - 1, now + 6);
}

int Sequence(int i)
{
	return Sequence2( i, 12);
}
// You are not supposed to change the main function
int main() {
    cout << Sequence(1)<< endl; //
    cout << Sequence(2)<< endl; //
    cout << Sequence(150)<< endl; //

}

