#include <iostream>
#include <string>
#include "meerkat.h"

using namespace std;



int main() {
    meerkat a;
    meerkat b;
    meerkat c;
    meerkat d;

    a.setName("S");
    b.setName("D");
    c.setName("T");
    d.setName("P");

    a.setAge(10);
    b.setAge(9);
    c.setAge(102);
    d.setAge(11);

    meerkat li[4] = {a,b,c,d};
    
    for (int i = 0; i< 4; i++){
         cout<< li[i].getName() <<" "<< li[i].getAge() <<"\n";
    }

}