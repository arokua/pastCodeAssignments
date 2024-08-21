#include "animal.h"
#include "vegie.h"
#include <string>

using namespace std;

vegie::vegie(string racal):animal(racal){
	typer = racal;
}
void vegie::set_favourite_food(string plantType){
	yummy = plantType;
}
string vegie::getFavouriteFood(){
	return yummy;
}