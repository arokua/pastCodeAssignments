#include <iostream>
using namespace std;

// The 'extern' keyword tells the complier that the function exists,
// but will be implemmented somewhere else.
extern int count(int[],int);

int main() {
    int array[5] = {4,5,6,7,0};
    cout<< "The number is: " << count(array, 5) << endl;
    return 0;

}
