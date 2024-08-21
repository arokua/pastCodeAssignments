#include <iostream>
#include <vector>
#include <string>

using namespace std;
static bool isError = false;
static vector<string> ops;
static vector<int> stack;
vector<string> takeInput(){
    // Get input from console
    // Split them by spaces and store to a vector
    string in;
    vector<string> pp;
    std::cout << "";
    getline (std::cin, in);
    int len = in.length(); //length of input
    string temp = ""; //tempoary string
    for (int i = 0; i < len; i++){
        char current = in.at(i);
        if (current != ' '){
            //Ignore tabs
            if (current !="\t") temp += current;
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

int add(int a, int b){
    return a + b;
}

int sub(int a, int b){
    return a - b;
}

int mul(int a, int b){
    return a * b;
}

int Div(int a, int b){
    //Divide a by b if b is not 0, else return 0 and prints 0
    if (b != 0)   return a / b;
    cout << "Error\n";
    return 0;
}

void getOps(vector<string> input){
    //Create a list of operations to be carry out, order:last to first
    string str;
    for (int i = 0; i < int(input.size()); i++){
        str = input[i];
        if (str == "+" || str == "-" ||
            str == "*" || str == "/")
            {    
                ops.push_back(str);
            }
    }
    for (int o = 0; o < int(ops.size()); o++){
        cout << ops[o] << " ";
    }cout << endl;
    return ;
}
vector<int> makeStack (vector<string> input) {
    //Stack of numbers to do calcs on, first->last
    string str;
    //Number of operations
    int countOps = 0;
    for (int i = 0; i < int(input.size()); i++){
        str = input[i];
        if (str != "+" && str != "-" &&
            str != "*" && str != "/")
            {    
                //parsing
                int n = stoi(str.c_str());
                stack.push_back(n);
            }
        else {
            countOps ++;
        }
    }
    //Predetermine whether there needs to do calculation
    if (countOps != int(stack.size() - 1)) {
        isError = true;
    }
    else getOps(input);
    cout << "Operands: ";
    for (int i = 0; i < stack.size(); i++){
        cout << stack[i] << " " ;
    }
    cout<<endl;
    return stack;
}

int calc(vector<string> op_s, vector<int> st_ack) {
    int a = 0;
    bool start = true;
    for (int o = int (op_s.size()) - 1; o > -1; o--){
        //Innermost operation that haven't been done
        string op = op_s[o];
        int reverse = int (op_s.size()) - o -1;
        if (op == "+"){
            if (start) {
                a = add(a, add(st_ack[2 * reverse], st_ack[2 * reverse + 1]));
                st_ack.pop_back();
                st_ack.pop_back();
                start = false;
            }else {
                a = add(a,  st_ack[1 + reverse]);
                st_ack.pop_back();
            }
        }
        if (op == "-"){
                if (start) {
                    a = add(a, sub(st_ack[2 * reverse], st_ack[2 * reverse + 1]));
                    st_ack.pop_back();
                    st_ack.pop_back();
                    start = false;
                }else {
                    a = sub(a,  st_ack[1 + reverse]);
                    st_ack.pop_back();
                }
            }

        if (op == "*"){
            if (start) {
                a = add(a, mul(st_ack[2 * reverse], st_ack[2 * reverse + 1]));
                st_ack.pop_back();
                st_ack.pop_back();
                start = false;
            }else {
                a = mul(a,  st_ack[1 + reverse]);
                st_ack.pop_back();
            }
        }
        if (op == "/"){
            if (start) {
                a = add(a, Div(st_ack[2 * reverse], st_ack[2 * reverse + 1]));
                st_ack.pop_back();
                st_ack.pop_back();
                start = false;
            }else {
                a = Div(a,  st_ack[1 + reverse]);
                st_ack.pop_back();
            }
        }
    }
    cout << a <<endl;
    return a;
}
int main(){
    vector<string> input = takeInput();
    cout << "Input is ";
    for (int i = 0; i < int(input.size()); i++){
        cout << input[i] ;
        if (i < int(input.size()) - 1 ) cout << " ";
    }cout << endl;
    makeStack(input);
    if (isError) cout << "Error, invalid number of operators\n";
    else calc(ops, stack);
}