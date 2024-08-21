#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "computer.h"
#include <vector>
#include <string>

class Tournament{

    private:

    std::vector< std::vector<computer *> > participants; // Contains all the computers in each round in the Tournament

    std::string* original;

    std::string winner;

    int rounds;

    public:

    Tournament(int);

    void myPlayers(std::vector< std::string >); // Get the list of player

    void begin();//Matching and get results
    std::string getWinner();//Wanted output

};

#endif