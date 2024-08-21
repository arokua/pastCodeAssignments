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

void hexDigits(int *numbers,int length) {
	int hexn ;
	string pri;
    for ( int j = 0; j < length; j++) {
        switch (hexn = *(numbers + j)) {
        	case 0:
	        	pri = "0";
	        	break;
	        case 1:
	        	pri = "1";
	        	break;
	        case 2:
	        	pri = "2";
	        	break;
	        case 3:
	        	pri = "3";
	        	break;
	        case 4:
	        	pri = "4";
	        	break;
	        case 5:
	        	pri = "5";
	        	break;
	        case 6:
	        	pri = "6";
	        	break;
	        case 7:
	        	pri = "7";
	        	break;
	        case 8:
	        	pri = "8";
	        	break;

	        case 9:
	        	pri = "9";
	        	break;

	        case 10:
	        	pri = "A";
	        	break;
	        case 11:
	        	pri = "B";
	        	break;
	        case 12:
	        	pri = "C";
	        	break;
	        case 13:
	        	pri = "D";
	        	break;
	        case 14:
	        	pri = "E";
	        	break;
	        case 15:
	        	pri = "F";
	        	break;
        }
        cout<< j<< " "<< *(numbers + j) << " "<< pri <<"\n";
    }

}

    

    

