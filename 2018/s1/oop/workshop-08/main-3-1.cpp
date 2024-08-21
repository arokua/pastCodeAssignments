#include <iostream>
#include "animal.h"
#include "vegie.h"
#include "hunter.h"

using namespace std;

int main(){
	hunter tig("Tiger");
	tig.set_name("GAO");

	hunter ti1g("Crocodile");
	ti1g.set_name("Sand Croc");
	
	hunter t3ig("Snake");
	t3ig.set_name("NoPyt");
	
	hunter ti2g("Lion");
	ti2g.set_name("MyMeat");

	vegie rhino("Rhinocerous");
	rhino.set_name("Rhiny");

	animal list[5] = {tig,ti1g, ti2g, t3ig, rhino};
	animal *p=&list[0];
	for(int i=0; i< 5; i++){
		cout<< (p + i)-> get_name() <<" the " << (p +i)->get_species()<< "\n";

	}
	
}