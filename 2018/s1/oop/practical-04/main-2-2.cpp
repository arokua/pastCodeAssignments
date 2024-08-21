#include <iostream>

using namespace std;

extern int maximum_sum(int *p,int );
int main()
{
 int a1[10] = { 31, -41, 59, 26, -53, 58, 97, -93, -23, 84 };
 int *p1 = &a1[0];
 
 cout<< maximum_sum(p1, 10);
}
