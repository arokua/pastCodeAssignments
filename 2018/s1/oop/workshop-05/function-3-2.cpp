#include <iostream>
#include <string>

using namespace std;

int* readNumbers() {
    
    int *p = new int[10];
    for (int i = 0; i < 10; i++){

        cin>>*(p + i) ;
        
    }
    

    return p;
}


bool equalsArray(int *numbers1,int *numbers2,int length) {
	int goodCheck = 0;
	if ( length < 1){
		return false;
	}else {
		for ( int e = 0; e < length; e++) {
			if (*(numbers1 + e) == *(numbers2 + e)) {
				goodCheck += 1;
			}
		}

		if (goodCheck == length) {
			return true;
		}else {
			return false;
		}
	}
}

int *reverseArray(int *numbers1,int length) {
    int *fin = new int[length];
    for (int i = 0; i < length; i ++){
        *(fin + i) = *(numbers1 + i);
        cout << *(fin +i);
    }
    
    return fin;
    
}