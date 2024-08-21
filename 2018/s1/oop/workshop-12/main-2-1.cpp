#include <iostream>
#include <string> 
#include "animal.h"
#include "hunter.h"

using namespace std;

int main (){
	animal* hA;
	hA = new hunter("Lion Me", 100);

	hunter B("JAU", 50);

	cout<<B->getName() <<"\n";
	return 0;
}