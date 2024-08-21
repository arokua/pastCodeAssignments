#include <iostream>
#include <string>

using namespace std;
class meerkat {
     int age;
     string name;
     public:
         void setName(string);
         string getName() {return name;};
         void setAge(int);
         int getAge(){return age;};
}