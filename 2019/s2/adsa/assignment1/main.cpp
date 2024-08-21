#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

//Forward declaration of all functions and global vars

//static int layer = 0;
//static void print_tabs(int);
static string current_answer = ""; // Karatsuba mul result
static void addZero(string *, string *);
static void removeZero(string *);
static vector<string> takeInput(); //Seperate given chain input by space and store them
static string make_sub(string *, int, int);//Alternate version of substr
static string SchoolAddition(string, string, int);
static string SchoolSubtraction(string, string, int);
static string SchoolMultiplication(string, int, int);
static string karatsuba_base10(string, string);
static string karatsuba(string *, string *, int);
static string whole_div(string, int, int);
static int big_num_mod(string *, int); //Return modulo of a big number
static string from_10(string *, int);//Base convert from decimal bases
static string to_10(string *, int); //Do the reverse of above
static string singleDigitMul(string, int, int);
//Division of cases that return quotient at max 10
static vector<string> div_by_sub(string, string);
//General division between vary large nums
static string string_string_div(string, string);

void addZero(string * a, string * b){
    //Add zero to the front of the second string until it have the same digits as the first
    int count = a->length() - b->length();
    while (count > 0){
         *b = "0" + (*b);
        count--;
    }
}

void removeZero(string * num){
    //Remove all leading zeros at the beginning of num
    while (true ){
        if ((*num).at(0) != '0' || num->length() == 1) break;
        (*num) =( *num).erase(0,1);
    }return;
}

vector<string> takeInput(){
    // take the list of strings from input, split them by space and store to vector
    string in;
    vector<string> pp;
    std::cout << "";
    getline (std::cin, in);
      
    int len = in.length(); //length of input
    string temp = ""; //tempoary string
    for (int i = 0; i < len; i++){
        char current = in.at(i);
        if (current != ' '){
          temp += current;
        }
        else{
            pp.push_back(temp);
            temp ="";
        }
        if (i == len - 1){
            pp.push_back(temp);
        }
    }
    return pp;
}

string make_sub(string * s, int start, int end){
    //return a substring between start and end
    string res = "";
    for (int i = start; i < end + 1; i++){
        res += s->at(i);
    }
    return res;
}

string SchoolAddition(string a, string b, int B){
    extern string SchoolSubtraction(string, string, int);
    int carry = 0;
    string sum;
    //The sum of a negative number and a positive number is an subtraction between them
    if (a[0] == '-') return SchoolSubtraction(b, a.substr(1, a.length() - 1), B);
    else if (b[0] == '-') return SchoolSubtraction(a, b.substr(1, b.length() - 1), B);
    //Add zeroes in the beggining so the two numbers have same amount of digits
    if (a == b && B < 10  && int(a.length()) == 1){
        //IF one of a or b is 0 then skip the operation
        if (a == "0") {
            return b;
        }
        else if (b == "0"){
            return "0";
        }
        //Single digit case, needs a leading zero
        a = "1" + a;
        b =  "0" + b;
        sum = a;
    }
    else if ( int(a.length()) > int(b.length()) ) {
        sum = a;
        addZero(&a, &b);
    }
    else if ( int(b.length()) != 1){
        sum = b;
        addZero(&b, &a);
    }
    // Number of digits from the right to be add from both num
    int totalDigits = a.length();
    int currentIndex = totalDigits - 1;
    
    while (totalDigits > 0){
        //Do the digit addition
        int now = a[currentIndex] + b[currentIndex] - 96 + carry ;
        string IndexSum = to_string (now % B);
        //Modify the original string
        if (currentIndex < int(a.length()) - 1) sum = sum.substr(0, currentIndex) +
        IndexSum + 
        sum.substr(currentIndex + 1, a.length() - currentIndex - 1);
        else sum = sum.substr(0, currentIndex) +  IndexSum;
        //Change the carry
        if (now > (B - 1)) carry = 1;
        else carry = 0;

        totalDigits--;currentIndex--;
    }
    if (carry == 1) sum = "1" + sum;
    return sum;
}

string SchoolSubtraction(string a, string b, int B){
    //If a is negative, then this is 
    if (a[0] == '-') return "-" + SchoolAddition(a.substr(1, a.length() - 1), b, B);
    if (b[0] == '-') return SchoolAddition(a, b.substr(1, b.length() - 1), B);
    if (a == b) return "0";    
    int carry = 0;
    string sub;
    if ( a.length() > b.length() ) {
        sub = a;
        addZero(&a, &b);
    }
    else {
        sub = b;
        addZero(&b, &a);
    }
    // Note: ASCII of '-' is larger than numerical values
    if (a < b ) {
        return "-" + SchoolSubtraction(b, a, B);
    }
    // Number of digits from the right to be add from both num
    int totalDigits = a.length();
    int currentIndex = totalDigits - 1;
    //print out an and b, for testing
    while (totalDigits > 0){
        int now ;
        //Do the digit subtraction
        if (a[currentIndex] < b[currentIndex]) {
            now = a[currentIndex] - '0';
            now += B;//Require a carry, add one more number to sub tract
            now = now - (int(b[currentIndex]) - 48) - carry;
            carry = 1;
        }
        else  {
            now = int(a[currentIndex] - '0') - int(b[currentIndex] - '0') - carry;
            if (now >= 0) carry = 0;
            else {
                carry = 1;
                now = B - (0 - now);
            }
        }
        string IndexSub = to_string (now % B);
        //Modify the original string
        if (currentIndex < max( int(a.length()), int(b.length())) ) sub = sub.substr(0, currentIndex) +
        IndexSub + 
        sub.substr(currentIndex + 1, max(a.length(), b.length()) - currentIndex - 1);
        else sub = sub.substr(0, currentIndex) +  IndexSub;
        
        totalDigits--;currentIndex--;
    }
    //Sign of result
    while (sub[0] == '0'){
        int l = sub.length() - 1;
        sub = sub.substr(1, l);
    }
    //This return negative number
    if (carry == 1 && sub[0] != '-') sub = "-" + sub;
    return sub;
}

string SchoolMultiplication(string a, int b, int Base){
    //Calculate the product of a and b where b is a small integer
    //Naive multiplication method
    if (a[0] == '-' ){
        return SchoolMultiplication(a.substr(1, a.length() - 1), b, Base);
    }
    //certain case return none so just to make sure
    if (a.back() == '0') return SchoolMultiplication(a.substr(0, int(a.length()) - 1), b, Base) + "0";
    if ( a.length() < 5 && Base == 10) return to_string(stoi(a) * b) ;
    string t = "";
    int zero_counter = 0;
    int d;
    string str_b = to_string(b);
    while ( str_b != ""){
        d = str_b.back() - '0';
        str_b = str_b.substr(0, int(str_b.length()) - 1);
        string now = singleDigitMul(a, d, Base);
        for (int i = 0; i < zero_counter; i++){
            now = now + "0";
        }
        t = SchoolAddition(t, now, Base);
        zero_counter++;
    }
    if (t == "" || t == "0"){
        //Error handling
        cout<<a << " " << b<<endl;
        throw exception();
    }
    return t;
}

string karatsuba_base10(string a, string b){
    //layer++;
    removeZero(&a);
    removeZero(&b);
    int l_a = a.length();
    int l_b = b.length();
    //print_tabs(layer);
    //cout <<"Go in layer " << layer << endl;
    //print_tabs(layer); cout << a << " " <<l_a<<endl;
    //print_tabs(layer); cout << b << " " <<l_b <<endl;
    if (l_a < 4 && l_b < 4){
        current_answer = to_string(stoi(a) * stoi(b));
    }
    else if (l_a < 5){
        current_answer = SchoolMultiplication(b, stoi(a), 10);
    }
    else if (l_b < 5){
        current_answer = SchoolMultiplication(a, stoi(b), 10);
    }
    else {
        //Count the zeros
        size_t z_count_a = count(a.begin(), a.end(), '0');
        size_t z_count_b = count(b.begin(), b.end(), '0');
        int i;
    
        if (int(z_count_a) == l_a - 1 && a[0] != '0'){
            for (i = 0; i < int( z_count_a ); i++){
                b = b + "0";
            }
            
            current_answer = singleDigitMul(b, int(a[0] - 48), 10);
        }
        else if (int(z_count_b) == l_b - 1 && b[0] != '0'){
            for (i = 0; i < int( z_count_b ); i++){
                a = a + "0";
            }
            current_answer = singleDigitMul(a, int(b[0] - 48), 10);
        }
        else if (l_a == int(z_count_a) || l_b == int(z_count_b)) current_answer = "0";
        else {
            int m;
            if (l_a >= 2*l_b || l_b >= 2* l_a) m = min(l_a, l_b) - 1;
            else m = 1 + max(l_a, l_b) / 2;
            //Split a and b
            string a1, a0, b1, b0;
            a1 = make_sub(&a, 0, l_a - m - 1);
            a0 = make_sub(&a,l_a - m, l_a - 1);
            b1 = make_sub(&b,0, l_b - m - 1);
            b0 = make_sub(&b, l_b - m, l_b - 1);
            if (a1 == "") a1 = "0";
            if (b1 == "") b1 = "0";/*
            print_tabs(layer + 1); cout << "m: " << m <<endl;
            print_tabs(layer + 1); cout << "a1: " << a1 <<endl;
            print_tabs(layer + 1); cout << "a0: " << a0 <<endl;
            print_tabs(layer + 1); cout << "b1: " << b1<<endl;
            print_tabs(layer + 1); cout << "b0: " << b0 <<endl;*/
            
            //Calculate smaller components
            string z0, z2;
            
            if (a1 != "0" && b1 != "0") z2 = karatsuba_base10(a1, b1);
            else z2 = "0";
            //print_tabs(layer + 1); cout << "z2: " << z2 +"\n\n";
            if (a0 != "0" && b0 != "0") z0 = karatsuba_base10(a0, b0);
            else z0 = "0";
            //print_tabs(layer + 1); cout << "z0: " << z0 +"\n\n";
            string temp_1 = SchoolAddition(a0, a1, 10);
            string temp_2 = SchoolAddition(b0, b1, 10);
            string z1 = karatsuba_base10(temp_1, temp_2);
            //print_tabs(layer + 1); cout << "z1.1 : " << z1 +"\n\n";
            
            temp_1 = SchoolSubtraction(z1,z0,10);
            //print_tabs(layer + 1); cout << "temp_1: " << temp_1 +"\n\n";
            
            z1 = SchoolSubtraction(temp_1, z2, 10);
            //print_tabs(layer + 1); cout << "z1.2: " << z1 +"\n\n";
            //Pad zeros in
            for (i = 0; i < m; i++){
                if (z2 != "0") z2 = z2 + "00";
                if (z1 != "0") z1 = z1 + "0";
            }
            current_answer = SchoolAddition(z2, z1, 10);
            current_answer = SchoolAddition(current_answer, z0, 10);
        }
    }
    //print_tabs(layer); cout << "Final result of this layer, " << layer << ", is " + current_answer + "\n";
    //print_tabs(layer); cout << "Exiting layer " << layer <<endl;
    //layer--;
    
    return current_answer;
}

string karatsuba(string * a, string * b, int Base){
    //Incomplete
    removeZero(a);
    removeZero(b);
    if ( (*b) == "1") return *a;
    else if ( (*a) == "1") return  (*b);
    else if ( (*b) == "0" ||  (*a) == "0" ) return "0";
    if (Base == 10) {
        current_answer = karatsuba_base10(*a, *b);
    }

    else {
        current_answer = karatsuba_base10(to_10(a, Base), to_10(b, Base));
        current_answer = from_10(&current_answer, Base);
    }
    return current_answer;
}

int big_num_mod(string * ss, int m){
    //Calculate the modulo of a very big number to a small int
    //Using rules of modular arthimetic
    int remain = 0;
    for (int i = 0; i < int(ss->length()); i++){
        remain = (remain * 10 + int(ss->at(i) - '0')) % m ;
    }
    return remain;
}

string whole_div(string num, int divisor, int Base){
    //Do whole division, result is rounded down (floor) to actual result
    //For the purpose of this assignment, Base is 10 as default
    if (divisor == 0) return "Div by zero! \n";
    else if (divisor == 1) return num;
    else if (divisor < 0) return "-" + whole_div(num, 0-divisor, Base);
    num = SchoolSubtraction(num, to_string(big_num_mod(&num, divisor)), Base);
    //Current digit we are looking at
    int current_digit = 0;
    //The smallest part to do division
    int temp = num[current_digit] - '0';
    while (temp < divisor) {
        current_digit++;
        temp = temp * 10 + (num[current_digit] - '0');
    }
    string result = "";
    //Keep running until we reached last digit
    while (current_digit < int(num.length())){
        result += (temp / divisor) + '0'; //0 is to convert to string
        //Add new digit to temp and remove old
        temp = temp % divisor;
        current_digit++;
        temp = temp * 10 + (num[current_digit] - '0');
    }
    if (result !="") return result;
    else return "0";
}

string string_string_div(string a, string b){
	//Divide between 2 large numbers
	int l_a = a.length();
	int l_b = b.length();
	//When the divisor is larger than the number it is dividing
	if (l_a < l_b) return "0";
	if (l_a == l_b && a < b) return "0";
	//Small cases, reduce loop time somewhat
	if (l_b < 5) return whole_div(a, stoi(b), 10);
	string temp = a.substr(0, l_b);
	a = a.substr(l_b, l_a - l_b);
	if (temp < b) {
		temp += a[0];
		a = a.substr(1,  a.length());
	}
	string result = "";
	while (true){
		if (a == "") {
			if (temp >= b || int(temp.length()) > l_b){
				result += div_by_sub(temp, b)[0];
			}else if (temp < b) result += "0"; //Final temp smaller create a 0 as quotient as final result
			break;
		}

		if (temp >= b || int(temp.length()) > l_b){
			 vector<string> temp_2 = div_by_sub(temp, b);
			result += temp_2[0];
			temp = temp_2[1];
		}else {
			result += "0";
			temp = temp;
		}
		//All the remainders of the previous division plus one new character
		if (temp[0] == '0' && temp.back() == '0') temp = "";
		temp += a[0];
		a = a.substr(1, int(a.length()) - 1);
	}
	return result;
}

vector<string> div_by_sub(string a, string b){
	//if a is at max 9 times b, use this
	int count = 0;
	while ( true){
		if (a.length() < b.length()) break;
		else if (a< b && a.length() == b.length()) break;
		count++;
		//Keep subtracting until done
		a = SchoolSubtraction(a, b, 10);
	}
	vector<string> ret;
	ret.push_back(to_string(count));
	ret.push_back(a);
	return ret;
}
string from_10(string * num, int target_base){
    //Convert a num from base 10 to target base
    //The remainders
    string chain = "";
    int current_remain = big_num_mod(num, target_base);
    while ( *num != "0"){
        chain = to_string(current_remain) + chain;
        (*num) = whole_div(*num, target_base, 10);
        current_remain = big_num_mod(num, target_base);
    }
    return chain;
}

string to_10(string * num, int original){
    //Convert number to base 10
    string re = "0";
    for (int i = 0; i < int(num->length()); i++){
        re = singleDigitMul(re, original, 10);
        string pn(1, num->at(i));
        re = SchoolAddition(re, pn, 10);
    }
    return re;
}

string singleDigitMul(string a, int digit, int Base){
    //Return a times digit in Base
    if (digit == 0 || a == "0") return "0";
    if (digit == 1) return a;
    
    return SchoolAddition(a, singleDigitMul(a, digit - 1, Base), Base);
}

/* Use for debug purposes
void print_tabs(int n){
    //Print a certain number of tabs out to console for format when print values
    for (int i = 1; i< n; i++){
        cout <<"\t";
    }return;
}*/

int main()
{    
    vector <string> input = takeInput();
    string firstNum = input[0];
    string secondNum = input[1];
    int ba_se = stoi(input[2].c_str());
    //Addition result
    cout << SchoolAddition(firstNum, secondNum, ba_se) + " ";
    //Karatsuba multiplication result
    cout << karatsuba(&firstNum, &secondNum, ba_se) +" ";
    //Division , default val 0
    string div_re = string_string_div(to_10(&input[0], ba_se), to_10(&input[1], ba_se));
    cout << from_10(&div_re, ba_se) << endl;
}