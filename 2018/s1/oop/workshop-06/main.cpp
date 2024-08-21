#include <iostream>
#include "Book.h"
#include "Library.h"

using namespace std;

int main() {
	Book bookA("GH","Anon");
	Library aLi;
	aLi.addBook(bookA);
	cout<< aLi.bookExist(bookA)<< "\n";

}