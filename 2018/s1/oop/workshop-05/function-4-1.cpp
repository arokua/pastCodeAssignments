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

int  secondSmallestSum(int *nums, int length){
    int sublength = 1;
    int currentSum = 0;
    int to_re = 0;
    int minSum = *nums;

    while (sublength < (length + 1)) {
        for (int i = 0; i < length; i++){
            for (int j = 0; j < sublength;j++) {
                if (i + j < length){
                    currentSum += *(nums+i+j);                
                }
            }if (currentSum < minSum){
                    to_re = minSum;

                    minSum = currentSum;
            }
            currentSum = 0;
        }
        
        sublength += 1;
    }
    
    return to_re;


}