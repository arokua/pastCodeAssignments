#ifndef LIBRARY_H
#define LIBRARY_H
//This class assume each book in the library is unique
#include <iostream>
#include <string>
#include "Book.h"

using namespace std;

class Library {

	bool isBorrowed;
	string currentBook[400];
	int counter = 0; //Keep the total amount of books inthe library
	public:
		void addBook(Book);
		void borrow(Book);
		void unbow(Book);
		bool bookExist(Book);
};
#endif //LIBRARY_H