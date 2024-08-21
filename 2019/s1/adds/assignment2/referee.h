#ifndef REFEREE_H
#define REFEREE_H

#include <vector>
#include <string>

class referee {
    public:
    referee();
    char roundResult(char a, char b);
    std::string matchRe(std::vector<char> Amoves, std::vector<char> Bmoves);
};
#endif //REFEREE_H