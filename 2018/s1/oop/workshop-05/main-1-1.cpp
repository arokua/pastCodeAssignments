#include <iostream>

using namespace std;

extern int* readNumbers();
extern void printNumbers(int*, int);

int main()
{
	int * apointer= readNumbers();
    printNumbers(apointer, 10);

}
