#include <iostream>
#include <string>
#include "Reverse.h"
#include "FibonacciNumbers.h"
#include "EfficientFibonacci.h"
#include <vector>
#include <typeinfo>
#include <stdlib.h>

using namespace std;
vector<string> takeInput(){
    // Split input by spaces
    string in;
    vector<string> re;
    std::cout << "";
    getline (std::cin, in);
      
    int len = in.length();
    string temp = "";
    for (int i = 0; i < len; i++){
        char now = in.at(i);
        if (now != ' '){
          temp += now;
        }
        else{
            re.push_back(temp);
            temp = "";
        }
        if (i == len - 1){
            re.push_back(temp);
        }
    }
    return re;
}

bool allNum(string toCheck){
    //Check if this string can be convert to int
    return toCheck.find_first_not_of("0123456789") == string::npos;
}
int main(){
    // Make objects of the three classes
	Reverse rr;
    FibonacciNumbers fn;
    EfficientFibonacci ef;
	vector<string> in = takeInput();

    //Errors handling
    if (allNum(in[0])){
        cout<< rr.reverseDigits(stoi(in[0])) <<" ";
    }else{cout <<"ERROR ";}

    cout<<rr.reverseString(in[1]) << " ";
    if (allNum(in[2])){
        cout<< fn.calc(stoi(in[2])) << " ";
    }else{cout <<"ERROR ";}

    if (allNum(in[3])){
        cout<< ef.calc(stoi(in[3]))<< endl;
    }else{cout <<"ERROR\n";}
    

    /*Fibonacci testing
    Replace n with an int between 0 and 40 (larger will take too much time) 
    for (int i = 0; i < n; i++){
        cout << i << " " << fn.calc(i) << " " << ef.calc(i) <<endl;
    }
    */
}