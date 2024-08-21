#include <iostream>

using namespace std;

extern int* readNumbers();
extern bool equalsArray(int *,int *,int) ;

int main()
{
	int * apointer = readNumbers();
	int * apointer2 = readNumbers();
    
    equalsArray(apointer, apointer2, 10);

}