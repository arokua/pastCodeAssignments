#include <iostream>
#include <string>
#include "Palindrome.h"

using namespace std;


int main()
{
  Palindrome A;
  string in;
  cout << "";
  
  getline (cin, in);
  cout << A.isPalindrome(in)<< "\n";

}