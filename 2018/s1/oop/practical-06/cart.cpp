#include <iostream>
#include "meerkat.h"
#include "cart.h"
using namespace std;

bool cart::addMeerkat(meerkat aCat){
    while (n < 4){
    	if (n == 4){
    		return false;
    		break;
    	}
    	amount[n] = aCat;
    	return true;
    	n +=1;
    }
}

void meerkat::setAge(int n){
    age = n;
}

string meerkat::getName(){
    return name;
}

int meerkat::getAge(){
    return age;
}




