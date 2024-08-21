#include <iostream>

using namespace std;

int maximum_sum(int *nums, int length){
    int sublength = 1;
    int currentSum = 0;
    int maxSum =0;
    int negativeNo = 0;
    
    for(int c = 0; c< length; c++){
        if (*(nums + c) < 0){
            negativeNo +=1;
        }
    }
    
    if (negativeNo == length){
        return 0;
    }else {
        while (sublength < (length + 1)) {
            for (int i = 0; i < length; i++){
                for (int j = 0; j < sublength;j++) {
                	if ( i +j <length){
                		currentSum += *(nums+i+j);
                	}
                    
                }if (currentSum > maxSum){
                        maxSum = currentSum;
                }
                currentSum = 0;
            }
            
            sublength += 1;
        }
        
        return maxSum;
    }
}