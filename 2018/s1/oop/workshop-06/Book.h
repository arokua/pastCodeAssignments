#ifndef BOOK_H
#define BOOK_H

#include <string>

using namespace std;

class Book {
	string name;
	string author;

	int theNthTotal ; //The amount of this same book

	public:
		Book(string, string);
		void addBook(int);
		string getName();
		int amount(); //The amount of the same books
};
#endif //BOOK_H