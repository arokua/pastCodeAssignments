#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> takeInput(){
    // Get input from console
    // Split them by / and store to a vector
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

void addZero(string * pA, string * pB){
    int l = pB->length();
    while (l < pA->length()){
        *pB = "0" + (*pB);
    }
    return;
}
int Intpower (int base, int expo) {
    int ans = 1;
    if (expo == 0){
        return 1;
    }
    else if ( expo > 0){
        for (int i = 0; i < expo; i ++){
            ans *= base;
        }
        return ans;
    }
    else if (expo < 0) {
        return 0;
    }
    else {
        return 0;
    }
}

string SchoolAddition(string a, string b, int B){
    
    string sum;
    if (a.length() >b.length()) addZero(&a, &b);
    else addZero(&b, &a);
    int total_digits = a.length();
    sum = a;
    int carry= 0;
    cout << a ;
    for (int i = total_digits - 1; i > -1; i--){
        cout <<i <<" ";
        int now = (a[i] - 48) +( b[i] - 48 ) + carry;
        sum = sum.substr(0, i) + to_string(now % B) + sum.substr(i + 1, total_digits - i - 1);
        if (now > B - 1) carry = 1;
        else carry = 0;
        
    }cout <<endl;
    if (carry == 1) sum = "1" + sum;
    cout << sum <<endl;
    return sum;
}


int karatsuba(string a, string b, int Base){
    
    int L1 = a.length();
    int L2 = b.length();
    int m = 0; //the expo power for B
   
    if (L1 == 1 && L2> 1){
        return (a[0] - 48) * stoi(b);
    }
    else if (L2 == 1 && L1> 1){
        return (b[0] - 48) * stoi(a);
    }
    else if (L1 == 1 && L2 == 1){
        return (a[0] - 48) * (b[0]-48);
    }
    
    else if (L1 > 1  && L2 >1) {

        if (L1 > L2){
            m = (L1 / 2) + 1;
        }else {
            m = (L2 / 2) + 1;
        }
        int BtoM = Intpower(Base, m);
        /*Desired var : z
        z = a1*b1*(B^ 2m) + (a1*b0 + a0*b1) ^(BtoM) + a0b0
        where a = a1*BtoM + a0
              b = b1*BtoM + b0
        */
        int a0= stoi(a) %(BtoM);
        int b0 = stoi(b)%(BtoM);
        int a1 = (stoi(a)- a0) / BtoM;
        int b1 = (stoi(b)- b0) / BtoM;
        
        //Starting recursion loop
        int a0b0 = karatsuba(to_string(a0), to_string(b0),Base);
        int a1b1 = karatsuba(to_string(a0), to_string(b0),Base);
        int CrossMul = karatsuba(to_string(a0 + b1), to_string(a1 + b0), Base) - a0b0 -a1b1;
        
        return a1b1 * Intpower(Base,2) + CrossMul* BtoM +a0b0;
    }else {
        return 0;
    }
}

int main()
{
    vector <string> inputs = takeInput();
    string numA = inputs[0];
    string numB = inputs[1];
    int base = stoi(inputs[2].c_str());
    cout << "||" + numA + "||" + numB <<" " << base<<endl;
    SchoolAddition(numA, numB, base);
}