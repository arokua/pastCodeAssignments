#include <iostream>

using namespace std;

extern int* readNumbers();
extern bool equalsArray(int *,int *,int) ;
extern int reverseArray(int *, int);

int main(){
	int * apointer = readNumbers();
	int * apointer2 = readNumbers();
    
        equalsArray(apointer, reverseArray(apointer2, 10),10);

}