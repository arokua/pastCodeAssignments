#include <iostream>

using namespace std;

extern int* readNumbers();
extern void hexDigits(int*, int);

int main()
{
	int * apointer= readNumbers();
    hexDigits(apointer, 10);

}
