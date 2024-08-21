#ifndef PALINDROME_H
#define PALINDROME_H
#include <string>

using namespace std;

class Palindrome{
    public:
    	Palindrome();
        string removeNonLetters(string s);
        string lowerCase(string s);
        string isPalindrome(string txt);
        ~Palindrome();
};

#endif //PALINDROME_H