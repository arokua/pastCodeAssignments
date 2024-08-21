#include <iostream>
#include <stdlib.h>

extern void passorfail(char);
using namespace std;

int main(int argc,char **argv)
{
	passorfail('A');
	passorfail('B');
	passorfail('C');
	passorfail('D');
	passorfail('E');
	passorfail(12);
}

