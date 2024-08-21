#ifndef MEERKAT_H
#define MEERKAT_H

#include <string>

using namespace std;
class meerkat {
    int age;
    string name;
    public:
        void setName(string);
        string getName() ;
        void setAge(int);
        int getAge();
};
#endif //MEERKAT_H