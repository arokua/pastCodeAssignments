#include <iostream>
#include <string>
#include "person.h"
#include "player.h"

using namespace std;

int main(){
	Person *A;
	int kl[3] = {1,2,3};
	A = new Player("He", 10,kl,3);
	cout << A->get_occupation() << "\n";

}