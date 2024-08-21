#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <string>
#include "person.h"

using namespace std;
class aircraft{


	string callsign;
	person A = person("",0);
	person B = person("", 0);

    public:
    	aircraft(string, person, person);
        void setPilot(person);
        person getPilot() ;
        void setCoPilot(person);
        person getCoPilot() ;
        void printDetails();
};
#endif //AIRCRAFT_H