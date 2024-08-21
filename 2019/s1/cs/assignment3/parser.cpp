#include <iostream>
#include <string>
#include <vector>
#include "iobuffer.h"
#include "symbols.h"
#include "abstract-syntax-tree.h"

// to shorten our code:
using namespace std ;
using namespace CS_Symbol_Tables ;
using namespace Jack_Compiler ;

// ***** WHAT TO DO *****
//
// MODIFY the skipeleton code below to parse a Jack class and construct the equivalent abstract syntax tree, ast.
//        The main function will print the ast formatted as XML
//
// NOTE: the correct segment and offset is recorded with every variable in the ast
//       so the code generator does not need to use any symbol tables
//
// NOTE: use the fatal function below to print fatal error messages with the current
//       input file position marked.
//
// The skipeleton code has one function per non-terminal in the Jack grammer
//  - comments describing how to create relevant ast nodes prefix most functions
//  - ast nodes are immutable - you must create all the sub-trees before creating a new node
//
// The structure of the skipeleton code is just a suggestion
//  - it matches the grammar but does not quite match the ast structure
//  - you will need to change the parameters / results / functions to suit your own logic
//  - you can change it as much as you like
//
// NOTE: the best place to start is to write code to parse the input without attempting to create
//       any ast nodes. If correct this parser will report errors when it finds syntax errors but
//       correct programs will fail because the tree printer will not be provided with a valid ast.
//       Once the parsing works modify your code to create the ast nodes.
//
// NOTE: the return -1 ; statements are only present so that this skipeleton code will compile.
//       these statements need to be replaced by code that creates ast nodes.
//

// fatal error handling
static void fatal(string message)
{
    fatal_error(0,"***** Error:\n" + token_context() + message) ;
}
// The Jack grammar to be recognised:
// program          ::= One or more classes, each class in a separate file named <class_name>'.Jack'
// class            ::= 'class' identifier '{' class_var_decs subr_decs '}'
// class_var_decs   ::= (static_var_dec | field_var_dec)*
// static_var_dec   ::= 'static' type identifier (',' identifier)* ';'
// field_var_dec    ::= 'field' type identifier (',' identifier)* ';'
// type             ::= 'int' | 'char' | 'boolean' | identifier
// vtype            ::= 'void' | type
// subr_decs        ::= (constructor | function | method)*
// constructor      ::= 'constructor' identifier identifier '(' param_list ')' subr_body
// function         ::= 'function' vtype identifier '(' param_list ')' subr_body
// method           ::= 'method' vtype identifier '(' param_list ')' subr_body
// param_list       ::= ((type identifier) (',' type identifier)*)?
// subr_body        ::= '{' var_decs statements '}'
// var_decs         ::= var_dec*
// var_dec          ::= 'var' type identifier (',' identifier)* ';'

// statements       ::= statement*
// statement        ::= let | if | while | do | return
// let              ::= 'let' identifier ('[' expr ']')? '=' expr ';'
// if               ::= 'if' '(' expr ')' '{' statements '}' ('else' '{' statements '}')?
// while            ::= 'while' '(' expr ')' '{' statements '}'
// do               ::= 'do' (identifier '.')? identifier '(' expr_list ')' ';'
// return           ::= 'return' expr? ';'

// expr             ::= term (infix_op term)*
// term             ::= integer_constant | string_constant | 'true' | 'false' | 'null' | 'this' | '(' expr ')' | unary_op term | var_term
// var_term         ::= identifier | identifier '[' expr ']' | subr_call
// subr_call        ::= (identifier '.')? identifier '(' expr_list ')'
// expr_list        ::= (expr (',' expr)*)?
// infix_op         ::= '+' | '-' | '*' | '/' | '&' | '|' | '<' | '>' | '='
// unary_op         ::= '-' | '~'


// forward declarations of one function per non-terminal rule in the Jack grammar
ast parse_class() ;
ast parse_class_var_decs() ;
ast parse_static_var_dec() ;
ast parse_field_var_dec() ;
ast parse_type() ;
ast parse_vtype() ;
ast parse_subr_decs() ;
ast parse_constructor() ;
ast parse_function() ;
ast parse_method() ;
ast parse_param_list() ;
ast parse_subr_body() ;
ast parse_var_decs() ;
ast parse_var_dec() ;
ast parse_statements() ;
ast parse_statement() ;
ast parse_let() ;
ast parse_if() ;
ast parse_while() ;
ast parse_do() ;
ast parse_return() ;
ast parse_expr() ;
ast parse_term(Token, bool) ;
ast parse_array_index() ;
ast parse_subr_call(Token) ;
ast parse_expr_list() ;
ast parse_infix_op(Token) ;
ast parse_unary_op(Token) ;
ast parse_keyword_constant() ;

//Offset value of static
static int offsetS = -1;
//Offset value of field
static int offsetF = -1;
//Offset value of Args
static int offsetA = -1;
//Offset value of Locals
static int offsetL = -1;
//Index to skip in vector
static int skip = -100;
//Count square bracket, use in parse expr
static int countSB = 0;

//Terms and ops of a single expresions in token
static vector<Token> exprs;

//Store current class name
static string className = "";
//Name of the class of the subr being called
static string subr_class_name;
//Segment name
static string segment ="";
//Name of var dec variable
static string var_dec_name ="";
//type of variable
static string type = "";
//Name of current argument of function returned by current token
static string argName = "";
//Name of current subroutine, one of constructor/function/method
static string subr_name;
//Store current variable on LHS of let statement name
static string nowLeVar;

//is the current array variable on LHS of let or not
static bool isLetArray= false;
//is the current variable in var_dec a local or argument
static bool isLocal = true;

//lookup table for static and  var mem
static symbols glob_mem;
//lookup table for argument var and local mem
static symbols subr_mem;
//lookup table for calls
static symbols toCalls;

void addMathJack();
void addStringJack();
void addArrayJack();
void addOutputJack();
void addScreenJack();
void addKeyJack();
void addSysJack();
void addMemJack();

/* Offset mappping to predefined Jack classes
Math -3
String -4
Array -5
Output -6
Screen -7
Keyboard -8
Sys -9
Memory -10
*/
void addBasicClasses(){
    //Intialize to_Calls table with predefine classes of Jack language
    insert_variables(toCalls, "Math", st_variable("Math", "Math", "class", -3));
    insert_variables(toCalls, "String", st_variable("String", "String", "class", -4));
    insert_variables(toCalls, "Array", st_variable("Array", "Array", "class", -5));
    insert_variables(toCalls, "Output", st_variable("Output", "Output", "class", -6));
    insert_variables(toCalls, "Screen", st_variable("Screen", "Screen", "class", -7));
    insert_variables(toCalls, "Keyboard", st_variable("Keyboard", "Keyboard", "class", -8));
    insert_variables(toCalls, "Sys", st_variable("Sys", "Sys", "class", -9));
    insert_variables(toCalls, "Memory", st_variable("Memory", "Memory", "class", -10));
}

void addJackMethods() {
    //Intialize to_Calls table with predefine methods of Jack language
    // st_variable grammar : name-type-segment-offset
    addMathJack();
    addStringJack();
    addArrayJack();
    addOutputJack();
    addScreenJack();
    addSysJack();
    addMemJack();
}

void addMathJack(){
    insert_variables(toCalls, "abs", st_variable("abs", "int", "function", -3));
    insert_variables(toCalls, "multiply", st_variable("multiply", "int", "function", -3));
    insert_variables(toCalls, "divide", st_variable("divide", "int", "function", -3));
    insert_variables(toCalls, "min", st_variable("min", "int", "function", -3));
    insert_variables(toCalls, "max", st_variable("max", "int", "function", -3));
    insert_variables(toCalls, "sqrt", st_variable("sqrt", "int", "function", -3));
}

void addStringJack(){
    insert_variables(toCalls, "new", st_variable("new", "String", "constructor", -4));
    insert_variables(toCalls, "dispose", st_variable("dispose", "void", "method", -4));
    insert_variables(toCalls, "length", st_variable("length", "int", "method", -4));
    insert_variables(toCalls, "charAt", st_variable("charAt", "char", "method", -4));
    insert_variables(toCalls, "setCharAt", st_variable("setCharAt", "void", "method", -4));
    insert_variables(toCalls, "appendChar", st_variable("appendChar", "String", "method", -4));
    insert_variables(toCalls, "eraseLastChar", st_variable("eraseLastChar", "void", "method", -4));
    insert_variables(toCalls, "setInt", st_variable("setInt", "int", "method", -4));
    insert_variables(toCalls, "intValue", st_variable("intValue", "void", "method", -4));
    insert_variables(toCalls, "backSpace", st_variable("backSpace", "char", "function", -4));
    insert_variables(toCalls, "doubleQuote", st_variable("doubleQuote", "char", "function", -4));
    insert_variables(toCalls, "newLine", st_variable("newLine", "char", "function", -4));
}

void addArrayJack(){
    insert_variables(toCalls, "new", st_variable("new", "Array", "function", -5));
    insert_variables(toCalls, "dispose", st_variable("dispose", "void", "method", -5));
}

void addOutputJack(){
    insert_variables(toCalls, "moveCursor", st_variable("moveCursor", "void", "function", -6));
    insert_variables(toCalls, "printChar", st_variable("printChar", "void", "function", -6));
    insert_variables(toCalls, "printString", st_variable("printString", "void", "function", -6));
    insert_variables(toCalls, "printInt", st_variable("printInt", "void", "function", -6));
    insert_variables(toCalls, "println", st_variable("println", "void", "function", -6));
    insert_variables(toCalls, "backSpace", st_variable("backSpace", "void", "function", -6));
}

void addScreenJack(){
    insert_variables(toCalls, "clearScreen", st_variable("clearScreen", "void", "function", -7));
    insert_variables(toCalls, "setColor", st_variable("setColor", "void", "function", -7));
    insert_variables(toCalls, "drawPixel", st_variable("drawPixel", "void", "function", -7));
    insert_variables(toCalls, "drawLine", st_variable("drawLine", "void", "function", -7));
    insert_variables(toCalls, "drawRectangle", st_variable("drawRectangle", "void", "function", -7));
    insert_variables(toCalls, "drawCircle", st_variable("drawCircle", "void", "function", -7));
}

void addKeyJack(){
    insert_variables(toCalls, "keyPressed", st_variable("keyPressed", "char", "function", -8));
    insert_variables(toCalls, "readChar", st_variable("readChar", "char", "function", -8));
    insert_variables(toCalls, "readLine", st_variable("readLine", "char", "function", -8));
    insert_variables(toCalls, "readInt", st_variable("readInt", "char", "function", -8));
}

void addSysJack(){
    insert_variables(toCalls, "halt", st_variable("halt", "void", "function", -9));
    insert_variables(toCalls, "error", st_variable("error", "void", "function", -9));
    insert_variables(toCalls, "wait", st_variable("wait", "void", "function", -9));
}

void addMemJack(){
    insert_variables(toCalls, "poke", st_variable("poke", "void", "function", -10));
    insert_variables(toCalls, "peek", st_variable("peek", "int", "function", -10));
    insert_variables(toCalls, "deAlloc", st_variable("deAlloc", "void", "function", -10));
    insert_variables(toCalls, "alloc", st_variable("alloc", "Array", "function", -10));
}

// class ::= 'class' identifier '{' class_var_decs subr_decs '}'
// create_class(myclassname,class_var_decs,class_subrs)
ast parse_class()
{   
    className = token_spelling(mustbe(tk_identifier));
    if (!have(tk_lcb)) fatal("Mustbe bracket after class  namedeclaration\n");
    mustbe(tk_lcb);
    insert_variables(toCalls, className, st_variable(className, "Main", "class", -2));
    ast CVD = parse_class_var_decs();
    ast subroutine = parse_subr_decs();
    if (!have(tk_rcb)) fatal("Mustbe bracket after class \n");
    mustbe(tk_rcb);
    
    return create_class(className, CVD, subroutine) ;
}

// class_var_decs ::= (static_var_dec | field_var_dec)*
// create_class_var_decs(vector<ast> decs)
ast parse_class_var_decs()
{   
        //Vector of ast_decs nodes, default is empty
    vector<ast> decs;
    while(have(tk_class_var)){
        //get segment name
        segment = token_spelling(mustbe(tk_class_var));
        //get variable type
        type  = token_spelling(mustbe(tk_type));
        // get variable name(s)
        while (token_kind() != tk_semi){
            //Name is an identifier
            if (token_kind() == tk_identifier){
                var_dec_name = token_spelling();
                //Field or var?
                if (segment == "static") decs.push_back(parse_static_var_dec());
                else decs.push_back(parse_field_var_dec());
            }
            next_token();
            if (have(tk_comma)){
                mustbe(tk_comma);
            }else if (!have(tk_semi)){
                fatal("Wrong syntax");
            }
        }
        mustbe(tk_semi); 
    }

    return create_class_var_decs(decs) ;
}

// static_var_dec ::= 'static' type identifier (',' identifier)* ';'
// create_var_dec(string name,string segment,int offset,string type)
ast parse_static_var_dec() {
    //Increment offset value 
    offsetS++;
    //create a new variable
    st_variable sVar(var_dec_name, type, "static", offsetS);
    //Add to static var table
    insert_variables(glob_mem, var_dec_name, sVar);
    return create_var_dec(var_dec_name, "static", offsetS, type);
}

// field_var_dec ::= 'field' type identifier (',' identifier)* ';'
// create_var_dec(string name,string segment,int offset,string type)
ast parse_field_var_dec() 
{
    //Increment offset value 
    offsetF++;
    //create a new variable
    st_variable fVar(var_dec_name, type, "this", offsetF);
    //Add to static var table
    insert_variables(glob_mem, var_dec_name, fVar);
    return create_var_dec(var_dec_name, "this", offsetF, type);
}

// subr_decs ::= (constructor | function | method)*
// create_subr_decs(vector<ast> subrs)
// create_subr(ast subr)
ast parse_subr_decs()
{   
    vector<ast> subrs;
    ast current;
    //Some thing in class
    while(true){
        subr_name = token_spelling(mustbe(tk_subroutine)) ;
        //Reset local offset
        offsetL = -1;
        //Reset Argument off set
        offsetA = -1;
        if (subr_name == "constructor"){
            current = parse_constructor();
        }
        else if (subr_name == "function"){

            current = parse_function();
        }
        else if (subr_name == "method"){
            //Method arguments have offset starting at 1
            offsetA = 0;
            current = parse_method();
        }
        subrs.push_back(create_subr(current));
        
        if (!have(tk_subroutine)) next_token();
        if (!have(tk_subroutine)) break;
    }
    return create_subr_decs(subrs);
}

// constructor ::= 'constructor' identifier identifier '(' param_list ')' subr_body
// create_constructor(string vtype,string name,ast params,ast body)
ast parse_constructor()
{   
    string i1 = token_spelling(mustbe(tk_identifier));
    //constructor name
    string i2 = token_spelling(mustbe(tk_identifier));
    //create local lookuptables for arg and local var
    subr_mem = create_variables();
    insert_variables(toCalls, i1 + i2, st_variable(i1 + i2, "void", subr_name, -2));
    insert_variables(toCalls, i2, st_variable(i2, i2, subr_name, -2));
    //Get the parameters/arguments of this methods if any
    ast paras = parse_param_list();
    ast sBody = parse_subr_body();
    //delete the table
    delete_variables(subr_mem);
    return create_constructor(i1, i2, paras, sBody) ;
}

// function ::= 'function' vtype identifier '(' param_list ')' subr_body
// create_function(string vtype,string name,ast params,ast body)
ast parse_function()
{   
    string v_type = token_spelling(mustbe(tk_vtype));
    //functon name
    string myName = token_spelling(mustbe(tk_identifier));
    //create local lookuptables for arg and local var
    subr_mem = create_variables();
    insert_variables(toCalls, myName, st_variable(myName, v_type, subr_name, -2));
    //Get the parameters/arguments of this methods if any
    ast paras = parse_param_list();
    ast sBody = parse_subr_body();
    //delete the table
    delete_variables(subr_mem);
    return create_function(v_type, myName, paras, sBody) ;
}

// method ::= 'method' vtype identifier '(' param_list ')' subr_body
// create_method(string vtype,string name,ast params,ast body)
ast parse_method()
{
    string v_type = token_spelling(mustbe(tk_vtype));
    //method name
    string myName = token_spelling(mustbe(tk_identifier));
    //create local lookuptables for arg and local var
    subr_mem = create_variables();
    insert_variables(toCalls, myName, st_variable(myName, v_type, subr_name, -2));
    //Get the parameters/arguments of this methods if any
    ast paras = parse_param_list();
    ast sBody = parse_subr_body();
    //delete it
    delete_variables(subr_mem);
    return create_method(v_type, myName, paras, sBody) ;
}

// param_list ::= ((type identifier) (',' type identifier)*)?
// create_param_list(vector<ast> params)
// create_var_dec(string name,string segment,int offset,string type)
ast parse_param_list()
{   
    vector<ast> params;
    
    mustbe(tk_lrb);
    if (have(tk_type)){
        while(have(tk_type)){
            isLocal = false;            
            type = token_spelling(mustbe(tk_type));
            params.push_back(parse_var_dec());
            //skip coma, if there is any, else end
            next_token();
            if (have(tk_rrb)){
                mustbe(tk_rrb);
                break;
            }
        }
    }else{
        mustbe(tk_rrb);
    }
    return create_param_list(params) ;
}

// subr_body ::= '{' var_decs statements '}'
// create_subr_body(ast decs,ast body)
ast parse_subr_body()
{   
    ast decs;
    mustbe(tk_lcb);
    //Handle local variables
    decs = parse_var_decs();
    //Handle statements
    ast states = parse_statements();
    return create_subr_body(decs, states) ;
}

// var_decs ::= var_dec*
// create_var_decs(vector<ast> decs)
ast parse_var_decs()
{   
    //Get variable(s)
    vector<ast> decs;
    //GIf have a var
    if (token_kind()== tk_var){
        //Get the type
        mustbe(tk_var);

        type = token_spelling();
        //Go to next token
        next_token();
        if(!have(tk_identifier)) fatal("mustbe identifier or valid string of characters!\n");
        isLocal = true;
        while (true){
            if (token_kind() == tk_semi){
                mustbe(tk_semi);
                if (!have(tk_var)) {  ;
                    //End of variable section, go to next part
                    break;
                }else {
                    //Still have a variable
                    //Get the type
                    mustbe(tk_var);
                    type = token_spelling();
                    //Go to next token
                    next_token();
                }
            }else if (token_kind() == tk_comma) {
                next_token();
            }
            else{
                //Is a variable, know the var must be a identifier thus already
                //have a must be in function below
                decs.push_back(parse_var_dec());
        
            }
        }
    }
    return create_var_decs(decs) ;
}

// var_dec ::= 'var' type identifier (',' identifier)* ';'
// create_var_dec(string name,string segment,int offset,string type)
ast parse_var_dec()
{   
    //Handle variables
    if(!have(tk_identifier)) fatal("mustbe identifier!\n");
    argName = token_spelling(mustbe(tk_identifier));
    if (isLocal) {
        offsetL++;
        //create a new variable
        st_variable lVar(argName, type, "local", offsetL);
        //Add to subroutine var table
        insert_variables(subr_mem, argName, lVar);

        return create_var_dec(argName, "local", offsetL, type);
    }
    else{
        offsetA++;
        //create a new variable
        st_variable aVar(argName, type, "argument", offsetA);
        //Add to subroutine var table
        insert_variables(subr_mem, argName, aVar);
        return create_var_dec(argName, "argument", offsetA, type);
    }
}

// statements ::= statement*
// create_statements(vector<ast> statements)
ast parse_statements()
{   
    vector<ast> states;
    while (have(tk_statement)){
        states.push_back(parse_statement());
        
    }
    if (have(tk_identifier)){
        fatal("Not a statement");
    }
    return create_statements(states) ;
}

// statement ::= let | if | while | do | return
// create_statement(ast statement)
ast parse_statement()
{   
    switch(token_kind()) {
        case tk_let: return create_statement(parse_let());
        case tk_if: return create_statement(parse_if());
        case tk_do: return create_statement(parse_do());
        case tk_while: return create_statement(parse_while());
        case tk_return: return create_statement(parse_return());
        default:
            //Invalid statement, call fatal
            fatal("Not a valid statement");
    }   
}

// let ::= 'let' identifier ('[' expr ']')? '=' expr ';'
// create_let(ast var,ast expr)
// create_let_array(ast var,ast index,ast expr)
ast parse_let()
{       
    mustbe(tk_let);
    //Spelling of the variable
    //Temporaily add to token list, in case this is a let array statement
    if (!have(tk_identifier)) fatal("Not an identifier\n");
    string var_spell = token_spelling(mustbe(tk_identifier));
    // current variable
    st_variable now ;
    //expr part
    ast ex01;
    //Check if the variale is global or local
    if ( lookup_variables(glob_mem, var_spell).offset != -1 ){
        now = lookup_variables(glob_mem, var_spell);
    }
    else{
        now = lookup_variables(subr_mem, var_spell);
    }
    //ast node of current variable
    ast thisVar = create_var( now.name, now.segment, now.offset, now.type);
    //Store the name of current variable for possible lookup later
    nowLeVar = now.name;
    if (token_kind() == tk_eq){
        mustbe(tk_eq);
        ex01 = parse_expr();
        return create_let(thisVar, ex01) ;
    }
    //The expression before '='
    // Array index start with '['
    mustbe(tk_lsb);
    //Get the index
    isLetArray = true;
    ast ex00 = parse_expr();  
    isLetArray = false;
    //skip the '='
    if (!have(tk_eq))  fatal("mustbe tk eq");
    mustbe(tk_eq);
    ex01 = parse_expr();
    return create_let_array(thisVar, ex00, ex01) ;
}

// if ::= 'if' '(' expr ')' '{' statements '}' ('else' '{' statements '}')?
// create_if(ast condition,ast if_true)
// create_if_else(ast condition,ast if_true,ast if_false)
ast parse_if()
{   
    mustbe(tk_if);
    mustbe(tk_lrb);
    ast condition;
    ast inStatements;
    //Get the condition
    condition = parse_expr();
    mustbe(tk_rrb);
    mustbe(tk_lcb);
    inStatements = parse_statements();
    mustbe(tk_rcb);
    if (!have(tk_else)){
        //If statements only
        return create_if(condition, inStatements) ;
    }
    mustbe(tk_else);

    mustbe(tk_lcb);
    //If false part
    ast inElse = parse_statements();

    mustbe(tk_rcb);
    return create_if_else(condition, inStatements, inElse);
}

// while ::= 'while' '(' expr ')' '{' statements '}'
// create_while(ast condition,ast body)
ast parse_while()
{
    mustbe(tk_while);
    //Check if current token is a round bracket, if not then stop
    if (!have(tk_lrb)) fatal("Mustbe bracket after while token!\n");
    mustbe(tk_lrb);
    ast condition;
    ast inStatements;
    //Get the condition
    condition = parse_expr();
    //error handling
    if (!have(tk_rrb)) fatal("Mustbe round bracket after condition!\n");
    mustbe(tk_rrb);
    //error handling
    if (!have(tk_lcb)) fatal("Mustbe curly bracket to start while loop!\n");
    mustbe(tk_lcb);
    //Inside statements
    inStatements = parse_statements();
    if (!have(tk_rcb)) fatal("Mustbe curly bracket after while loop contents!\n");
    mustbe(tk_rcb);
    return create_while(condition, inStatements) ;
}

// do ::= 'do' (identifier '.')? identifier '(' expr_list ')' ';'
// create_do(ast call)
// create_call(bool method_call,string class_name,string subr_name,ast expr_list)
ast parse_do()
{   
    //Skip the "do"
    mustbe(tk_do);
    ///Temporary  holder
    if(!have(tk_identifier)) fatal("must be identifier after do \n");
    string cName = token_spelling(mustbe(tk_identifier));
    //Check if cName is a class name
    if (lookup_variables(subr_mem, cName).segment == "local" ){
        //using a variable from a class some where, so type of this var is class name for subr
        cName = lookup_variables(subr_mem, cName).type;

    }
    else if (lookup_variables(toCalls, cName).segment != "class"){
        cName = className;   
    }
    //method call
    bool mCall;
    if (have(tk_stop)) mustbe(tk_stop);
    subr_name = token_spelling(mustbe(tk_identifier));
    //Check if is a method call
    if (lookup_variables(toCalls, subr_name).segment == "method" ) mCall = true;
    else mCall = false;
    //Chack if have correct token
    if (!have(tk_lrb)) fatal("In do statement\n");
    mustbe(tk_lrb);
    exprs.clear();
    //expr_list
    vector<ast> el;
    //expr node
    ast er = parse_expr();
    //IF the there is an expression then add
    if (size_of_expr(er) > 0)  el.push_back(er);
    if (!have(tk_rrb)) fatal("must be right round bracket\n");
    mustbe(tk_rrb);
    //Move to next line
    if (have(tk_semi)) mustbe(tk_semi);
    else if (!have(tk_semi) && !have(tk_rrb) && !have(tk_statement)) fatal("Invalid end of do statement\n");
    return create_do(create_call(mCall, cName, subr_name, create_expr_list(el))) ;
}

// return ::= 'return' expr? ';'
// create_return()
// create_return_expr(ast expr)
ast parse_return()
{
    //return a return node
    mustbe(tk_return);
    if (have(tk_semi) ){    
            mustbe(tk_semi);
            return create_return();
        }
    else if (have(tk_identifier) ||have(tk_class) || have(tk_term)){
        ast myExpr = parse_expr();
        if (have(tk_semi)) {
            mustbe(tk_semi);
        }else if (!have(tk_statement) && 
                  !have(tk_rcb)) {
            fatal("Invalid!\n");
        }
        return create_return_expr(myExpr);
    }else{
        //Call fatal if receive nothing or wrong tokens
        fatal("either valid identifier or end of line");
    }
    
}

// expr ::= term (infix_op term)*
// create_expr(vector<ast> expr)
ast parse_expr()
{   
    //Create an ast_expr node
    //iscall is when parse_exp is used to read normal terms and ops, 1 for expr_list
    //list of expressions
    vector<ast> expr;
    while (true) {
        if ( have(tk_semi) ||have(tk_rrb) || have(tk_rcb)  ){
            break;
        }
        if (isLetArray){
            if (have(tk_rsb)){
                break;
            }
        }
        else if (have(tk_rsb)  || have(tk_rrb) ){
                exprs.push_back(current_token());
        }
        //Add the token to the token vector, break if reach end line or expresiion
        if (token_kind() != tk_lrb && token_kind() != tk_stop &&
            token_kind() != tk_comma ){
            if (!have(tk_term) && !have(tk_infix_op) && !have(tk_rsb) && !have(tk_lsb)) fatal("Wrong token\n");
            exprs.push_back(current_token());
        }
        next_token();
    }

    //Add the terms and op to expr
    //If the first or second identifier is a subroutine name 
    if (lookup_variables(toCalls, token_spelling(exprs[0])).offset <= -2 ) {
        expr.push_back(parse_term(exprs[0], true));
        if (token_kind() == tk_semi) mustbe(tk_semi);
        return create_expr(expr) ;
    }else if (exprs.size() > 1 && lookup_variables(toCalls, token_spelling(exprs[1])).offset <= -2 ) {
        expr.push_back(parse_term(exprs[0], true));
        if (token_kind() == tk_semi) mustbe(tk_semi);
        return create_expr(expr) ;
    }
    else {
        for (int i = 0; i <int(exprs.size()); i++) {
            if (i > skip){
                if (have(exprs[i], tk_infix_op) ){
                    expr.push_back(parse_infix_op(exprs[i])) ;
                }
                else if (have(exprs[i], tk_term) && !have(exprs[i], tk_rrb)){
                        expr.push_back(parse_term(exprs[i], false));
                }
                else if (token_kind(exprs[i]) == tk_lsb && !isLetArray){
                    //Idea immplemmentation of array index on RHS of parse_term:

                    //Met a '[' character, meaning this can be an array index term
                    //expression list of array index
                    vector<ast> expr2;
                    //Remove the previous node from the expr list as it is not a seperate node anymore
                    expr.pop_back();
                    st_variable arrayOne = lookup_variables(subr_mem, token_spelling(exprs[i - 1]));
                    skip = i + 1;
                    countSB = 1;
                    for (int j = skip; j < int(exprs.size()); j++){
                        if (have(exprs[j], tk_infix_op) ) {
                           expr2.push_back(parse_infix_op(exprs[j])) ;
                        }else if (have(exprs[j], tk_term)){
                            expr2.push_back(parse_term(exprs[j], false)) ;
                        }else if (have(exprs[j], tk_lsb)){
                            countSB++;
                        }else if (have(exprs[j], tk_rsb)){
                            countSB--;
                            if (countSB == 0){
                                skip ++;
                                break;
                            }
                        }
                        skip++;
                        //
                        if (skip == exprs.size()) break;
                    }

                    ast arrayNode = create_array_index(create_var(arrayOne.name, arrayOne.segment, arrayOne.offset, arrayOne.type), create_expr(expr2));
                    expr.push_back(create_term(arrayNode));
                    //clearing expr2
                    expr2.clear();
                }
                else if (token_kind(exprs[i]) != tk_rsb) {
                    //fatal("Error in expr read \n");
                }
            }
        }
    }
    skip = -1;
    exprs.clear();
    if ( !have(tk_rrb) && !have(tk_statement))  next_token();
    if (have(tk_semi))  next_token();
    return create_expr(expr) ;    
}

// term ::= integer_constant | string_constant | 'true' | 'false' | 'null' | 'this' | '(' expr ')' | unary_op term | var_term
// create_term(ast term)
// create_int(int _constant)
// create_string(string _constant)
// create_bool(bool t_or_f)
// create_null()
// create_this()
// create_unary_op(string op,ast term)
ast parse_term(Token token, bool aDotCall )
{   
    //aDotCall means is a subr call of type identifier.subr(??);

    if (!aDotCall){
        string sp; // Holder for the identifier token currently being read
        ast var;
        st_variable temp; //temporary st_variable
        switch(token_kind(token)) {
            case tk_integerConstant:
                //Return an integer term
                return create_term(create_int(token_ivalue(token)));
            case tk_true:
                return create_term(create_bool(true));
            case tk_false:
                return create_term(create_bool(false));
            case tk_this:
                return create_term(create_this()); //this
            case tk_stringConstant:
                //String in double quote
                return create_term(create_string(token_spelling(token)));
            case tk_identifier:
                //Check whether this is just a string or it is actually a var or a subr call
                sp = token_spelling(token);
                if ( lookup_variables(glob_mem, sp).offset != -1 ){
                    //If so, return a var term
                    temp = lookup_variables(glob_mem, sp);
                    var = create_var( temp.name, temp.segment, temp.offset, temp.type);
                    return create_term(var);
                }else if ( lookup_variables(subr_mem, sp).offset != -1 ){
                    //If so, return a var term
                    temp = lookup_variables(subr_mem, sp);
                    var = create_var( temp.name, temp.segment, temp.offset, temp.type);
                    return create_term(var);
                }else if ( lookup_variables(toCalls, sp).offset < -1){
                    return create_term(parse_subr_call(token));
                }
                else {
                    //Identifier revieved is not a variable or subroutine
                    return create_term(create_string(token_spelling(token)));
                }
            case tk_unary_op:
                // met an unary op token
                // Move to unary op token and return the value from it
                return create_term(parse_unary_op(token));
            case tk_null:
                return create_term(create_null());
            default:
                fatal_error (0,"***** Error:\n" + token_context(token) + "Not a valid term!\n");
            }
    }
    // Jump straight to subr call
    return create_term(parse_subr_call(exprs[0]));
}

// subr_call ::= (identifier '.')? identifier '(' expr_list ')'
// create_call(bool method_call,string class_name,string subr_name,ast expr_list)
ast parse_subr_call(Token token)
{
    //Is this subroutine a method
    bool method_call = false;
    if (lookup_variables(toCalls, token_spelling(token)).segment == "class" ||
       lookup_variables(toCalls, token_spelling(exprs[0])).offset != -2)  {
        //Get the subr name
        token = exprs[1];    
    }
    
    //Get the subr class name based on mapped off set to registed function
    //If a function has an offset as -2, they are defined in Main or current Jack file
    //Name of subroutine
    string subr_name = token_spelling(token);

    if (lookup_variables(toCalls, subr_name).offset != -2){
        subr_class_name = token_spelling(exprs[0]);

    }else{
        subr_class_name = className;
    }
    if (lookup_variables(toCalls, subr_name).segment == "method" ){
        method_call = true;
    }
    else if (subr_name == "run") method_call = true;
    ast expList = parse_expr_list();
    next_token();
    return create_call(method_call, subr_class_name, subr_name, expList) ;
}

// expr_list ::= (expr (',' expr)*)?
// create_expr_list(vector<ast> exprs)
ast parse_expr_list()
{   
    //vector to return
    vector<ast> exlist;
    //vector of exprs
    vector<ast> exprsNode;
    //Add all term that is not class name and subroutine name to exprlist
    if (lookup_variables(toCalls, token_spelling(exprs[0]) ).offset == -2 && 
        lookup_variables(toCalls, token_spelling(exprs[0])).segment != "class" ){
        //current subroutine call does not have any class before it
        exprsNode.push_back(create_term(create_this()));
        exlist.push_back(create_expr(exprsNode));
        exprsNode.pop_back();
    }
    for (int i = 0; i < int(exprs.size()); i++){
        if (have(exprs[i], tk_infix_op)){

        }
        else if (lookup_variables(toCalls, token_spelling(exprs[i]) ).offset >= -1 ||
            lookup_variables(subr_mem, token_spelling(exprs[i]) ).segment == "local" ||
            lookup_variables(subr_mem, token_spelling(exprs[i]) ).segment == "argument"){                
            exprsNode.push_back(parse_term(exprs[i], false));
            exlist.push_back(create_expr(exprsNode));
            exprsNode.pop_back();
        }
    }
    exprs.clear();
    //Reset token vector
    return create_expr_list(exlist);
}

// infix_op ::= '+' | '-' | '*' | '/' | '&' | '|' | '<' | '>' | '='
ast parse_infix_op(Token token)
{
    return create_op(token_spelling(token));
}

// unary_op ::= '-' | '~'
ast parse_unary_op(Token token)
{
    //mustbe(tk_unary_op, "");
    return create_unary_op(token_spelling(token), exprs.back()) ;
}

ast jack_parser()
{
    // read the first token to get the tokeniser initialised
    next_token();
    if (!have( tk_class)){
        //Wrong token
        fatal("must start with 'class'");
    }
    mustbe(tk_class);

    // construct tree and return as result
    return parse_class() ;
}

// main program
int main(int argc,char **argv)
{   
    //Hide error
    config_errors(iob_buffer);
    //Intitalize the tables
    glob_mem = create_variables();
    
    toCalls = create_variables();
    //Add Jack basic class and methods
    addBasicClasses();
    addJackMethods();
    // parse a Jack class and print the abstract syntax tree as XML
    ast_print_as_xml(jack_parser(),4) ;
    //Delete table
    delete_variables(glob_mem);
    // flush the output and any errors
    print_output() ;
    print_errors() ;
}