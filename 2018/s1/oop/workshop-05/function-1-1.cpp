#include <iostream>


using namespace std;

int* readNumbers() {
    
    int *p = new int[10];
    for (int i = 0; i < 10; i++){

        cin>>*(p + i) ;
        
    }
    

    return p;
}

void printNumbers(int *numbers,int length) {
    for ( int j = 0; j < length; j++) {
        cout<< j<< " "<< *(numbers + j) << "\n";
    }
}
    

    

