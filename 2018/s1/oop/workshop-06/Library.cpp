#include <string>
#include "Book.h"
#include "Library.h"

using namespace std;

void Library::addBook(Book bookname) {
	if (counter < 400){	
		
		if (bookExist(bookname) == 0){
			currentBook[counter] = bookname.getName();
			counter +=1;
		}

		else {
			currentBook[counter] = bookname.getName() + std::to_string(counter);

		}
	}
	
	else if (counter == 400){
		cout << "Sorry, we are out of spaces!";
	}

}

bool Library::bookExist(Book bookname){
	for (int i = 0; i< counter; i++){
		if( bookname.getName() == currentBook[i]){
			return 1;
			break;
		}
		else {
			return 0;
		}

	}
}

void Library::borrow(Book bookname){
	if(bookExist == 1){
		cout<<"You now are borrowing " << bookname.getName()<<"\n"
	}
}