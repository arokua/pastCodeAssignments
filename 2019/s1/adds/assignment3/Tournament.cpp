#include <iostream>
#include <string>
#include <vector>
#include "computer.h"
#include "Avalanche.h"
#include "Bureaucrat.h"
#include "Crescendo.h"
#include "FistfullODollars.h"
#include "PaperDoll.h"
#include "ToolBox.h"
#include "referee.h"
#include "RandomComputer.h"
#include "Tournament.h"

using namespace std;

int logarthmic(int base, int pow){
    //Do the calculation log of pow base base
    while (pow > 1){
        return 1 + logarthmic(base, int(pow / base));
    }
    return 0;
}

Tournament::Tournament(int players) {
    rounds = logarthmic(2, players);
    //The extra + 1 as the holder for the final winner
    for (int i = 0; i < rounds + 1; i++){
        vector<computer *> thisRound;
        thisRound.reserve(players);
        participants.push_back(thisRound);
        players /= 2;
    }
}

void Tournament::myPlayers(vector<string> partic) {
    original = new string[8];
    for (int i = 0; i < 8; i++){
        if (partic[i] == "Avalanche"){
            participants[0].push_back(new Avalanche(5, i));
        }
        else if (partic[i] == "Bureaucrat"){
            participants[0].push_back(new Bureaucrat(5, i));
        }
        else if (partic[i] == "Crescendo"){
            participants[0].push_back(new Crescendo(5, i));
        }
        else if (partic[i] == "FistfullODollars"){
            participants[0].push_back(new FistfullODollars(5, i));
        }else if (partic[i] == "PaperDoll"){
            participants[0].push_back(new PaperDoll(5, i));
        }else{
            participants[0].push_back(new ToolBox(5, i));
        }
        original[i] = partic[i];
    }
}

void Tournament::begin(){
    referee R;
    for (int r = 0; r < rounds; r++){
        int matches = participants[r].size(); //Number of matches in each round
        for (int p = 0; p < matches; p+= 2){
            //Setting the match between each pair
            participants[r][p]->makeMoves();
            participants[r][p + 1]->makeMoves();

            int judge = R.result( R.match(participants[r][p]->getMoves(),
                                          participants[r][p+ 1]->getMoves()));
            //Get the winner to the next bracket/ round
            if (judge == -1){
                participants[r + 1].push_back(participants[r][p + 1]); //Second player
            }else {
                participants[r + 1].push_back(participants[r][p]); // First
            }
            
        }
        participants[r].clear();
    }
    winner = original[participants[3][0]->id()];
}

string Tournament::getWinner(){
    return winner;
}