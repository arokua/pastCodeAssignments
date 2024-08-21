#ifndef REFEREE_H
#define REFEREE_H

#include <vector>
#include <string>

class referee {
    public:
    referee();
    char roundResult(char a, char b);
    std::vector<char> match(std::vector<char> Amoves, std::vector<char> Bmoves);
    int result(std::vector<char>);
};
#endif //REFEREE_H