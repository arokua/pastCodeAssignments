#ifndef CART_H
#define CART_H

#include <iostream>
#include "meerkat.h"
#include <string>

using namespace std;

using namespace std;
class cart {
	meerkat amount[4]; //The amount of meerkat(s)
	int n = 0;

    public:
        bool addMeerkat(meerkat);   // adds a meerkat to the cart, returns false if full
		void emptyCart();               // remove all meerkats from the cart
		void printMeerkats();           // print the name, a space, the age, then a new line
};
#endif //CART_H
