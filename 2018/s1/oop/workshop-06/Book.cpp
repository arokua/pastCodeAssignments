#include <string>
#include "Book.h"

using namespace std;

Book::Book(string Na, string AU)
{
	name = Na;
	author =AU;
	theNthTotal = 1;
}

string Book::getName(){
	return name;
}

void Book::addBook(int howMuch) {
	theNthTotal += howMuch;
}

int Book::amount(){
	return theNthTotal;
}