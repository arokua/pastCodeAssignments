#include "Palindrome.h"
#include <string>
#include <algorithm>

using namespace std;

Palindrome::Palindrome() { }

string Palindrome::removeNonLetters(string s){
	//Generate a new string by checking the ASCII value of each individual characters
    string p = "";
    for (int i = 0; i < int(s.length()); i++){
        int c = int(s.at(i));
        if ((96 < c and c < 123) or ( 64 < c and c < 91)){
            p += s.at(i);
        }
    }
    return p;
}

string Palindrome::lowerCase(string s){
    // This function works on assuming the removeNonLetters function has been called on s
    string p = "";
    for (int i = 0; i < int(s.length()); i++){
        int c = int(s.at(i));
        if (64 < c and c < 91){
            p += char( c + 32); // Note that ASCIII of 'A' is 65 and 'a' is 97 Thus just need to increase the value by 32 and it would be lower cased
        }
        else{
            p += s.at(i);
        }
    }
    return p;
}

string Palindrome::isPalindrome(string txt){
    string nS = lowerCase(removeNonLetters(txt));
    string back = nS; // a copy of the original proccessed string since said string will be modded
    reverse(nS.begin(), nS.end());
    if (nS == back){
        return "Yes";
    }
    return "No";
}

Palindrome::~Palindrome(){}