#include "iobuffer.h"
#include "symbols.h"
#include "abstract-syntax-tree.h"

// to shorten our code:
using namespace std ;
using namespace Jack_Compiler ;
using namespace CS_Symbol_Tables;

// ***** WHAT TO DO *****
//
// MODIFY the skeleton code below to walk an abstract syntax tree, ast, of a Jack class
//        and pretty print the equivalent Jack source code.
//
// The skeleton code has one function per node in the abstract tree
//  - they each extract all fields into local variables
//  - they each call the appropriate walk_* function to walk any sub-trees
//
// The structure of the skeleton code is just a suggestion
//  - you may want to change the parameters / results to suit your own logic
//  - you can change it as much as you like

// forward declarations of one function per node in the abstract syntax tree
void walk_class(ast t) ;
void walk_class_var_decs(ast t) ;
void walk_var_dec(ast t) ;
void walk_subr_decs(ast t) ;
void walk_subr(ast t) ;
void walk_constructor(ast t) ;
void walk_function(ast t) ;
void walk_method(ast t) ;
void walk_param_list(ast t) ;
void walk_subr_body(ast t) ;
void walk_var_decs(ast t) ;
void walk_statements(ast t) ;
void walk_statement(ast t) ;
void walk_let(ast t) ;
void walk_let_array(ast t) ;
void walk_if(ast t) ;
void walk_if_else(ast t) ;
void walk_while(ast t) ;
void walk_do(ast t) ;
void walk_call(ast t) ;
void walk_return(ast t) ;
void walk_return_expr(ast t) ;
void walk_expr_list(ast t) ;
void walk_expr(ast t) ;
void walk_term(ast t) ;
void walk_op(ast t) ;
void walk_int(ast t) ;
void walk_string(ast t) ;
void walk_bool(ast t) ;
void walk_null(ast t) ;
void walk_this(ast t) ;
void walk_var(ast t) ;
void walk_array_index(ast t) ;
void walk_unary_op(ast t) ;
//Set of function to store predefined classes and ops
void addMathOp();
void addStringOp();
void addScreen();
void addArray();
void addOutput();
void addKeyboard();
void addMemory();
void addSys();
void addClasses();
//Ident spaces,use inplace of t
static string indent = "    ";
static bool isClassVar;
static int indentLvl = 1;
//symbol table record subr name and number of parameters
static symbols subrs;
//symbol table to record subroutine names and predefined jack classes
static symbols validClasses;
//Symbol table to record current variable
static symbols vars;
//Is there need for a bracket or not
static bool needR = false;


void addClasses(){
    validClasses = create_strings();
    insert_strings(validClasses, "Math", "class");
    addMathOp();
    insert_strings(validClasses, "String", "class");
    addStringOp();
    insert_strings(validClasses, "Array", "class");
    addArray();
    insert_strings(validClasses, "Screen", "class");
    addScreen();
    insert_strings(validClasses, "Keyboard", "class");
    addKeyboard();
    insert_strings(validClasses, "Output", "class");
    addOutput();
    insert_strings(validClasses, "Sys", "class");
    addSys();
    insert_strings(validClasses, "Memory", "class");
    addMemory();
}

void addMathOp(){
    //Add math op to the subr table
    insert_ints(subrs, "abs", 1);
    insert_ints(subrs, "multiply",2 );
    insert_ints(subrs, "divide", 2);
    insert_ints(subrs, "min", 2);
    insert_ints(subrs, "max", 2);
    insert_ints(subrs, "sqrt", 1);
}

void addStringOp(){
    //Add string op to the subr table
    insert_ints(subrs,"new", 1);
    insert_ints(subrs,"dispose", 0);
    insert_ints(subrs,"length", 0);
    insert_ints(subrs,"charAt", 1);
    insert_ints(subrs,"setCharAt", 2);
    insert_ints(subrs,"appendChar", 1);
    insert_ints(subrs,"eraseLastChar", 0);
    insert_ints(subrs,"setInt", 1);
    insert_ints(subrs,"intValue", 0);
    insert_ints(subrs,"backSpace", 0);
    insert_ints(subrs,"doubleQuote", 0);
    insert_ints(subrs,"newLine", 0);
}

void addArray(){
    //Add array op to table
    insert_ints(subrs,"Array.new", 1);
    insert_ints(subrs,"Array.dispose", 0);
}

void addScreen(){
    //Add screen op to table
    insert_ints(subrs, "clearScreen", 0);
    insert_ints(subrs, "setColor", 1);
    insert_ints(subrs, "drawPixel", 2);
    insert_ints(subrs, "drawLine", 4);
    insert_ints(subrs, "drawRectangle", 4);
    insert_ints(subrs, "drawCircle", 3);
}

void addOutput(){
    //Add output op to table
    insert_ints(subrs, "moveCursor", 2);
    insert_ints(subrs, "printChar", 1);
    insert_ints(subrs, "printString", 1);
    insert_ints(subrs, "printInt", 1);
    insert_ints(subrs, "println", 0);
    insert_ints(subrs, "backSpace", 0);
}

void addKeyboard(){
    //Add keyboard op to table
    insert_ints(subrs, "keyPressed", 0);
    insert_ints(subrs, "readChar", 0);
    insert_ints(subrs, "readLine", 1);
    insert_ints(subrs, "readInt", 1);
}

void addMemory(){
    //Add keyboard op to table
    insert_ints(subrs, "poke", 2);
    insert_ints(subrs, "peek", 1);
    insert_ints(subrs, "deAlloc", 1);
    insert_ints(subrs, "alloc", 1);
}

void addSys(){
    //Add sys op to table
    insert_ints(subrs, "halt", 0);
    insert_ints(subrs, "error", 1);
    insert_ints(subrs, "wait", 1);
}
void walk_class(ast t)
{
    string myclassname = get_class_class_name(t) ;
    //Write out class name
    cout << "class " + myclassname <<endl;
    cout << "{\n";
    ast var_decs = get_class_var_decs(t) ;
    ast subr_decs = get_class_subr_decs(t) ;
    //When reading global vars of a class, must print out said vars
    //This boolean helps decided that
    isClassVar = true;
    walk_class_var_decs(var_decs) ;
    isClassVar = false;
    //Go over the body of a class
    walk_subr_decs(subr_decs) ;
    cout << "}\n";
}

void walk_class_var_decs(ast t)
{
    int ndecs = size_of_class_var_decs(t) ;
    for ( int i = 0 ; i < ndecs ; i++ )
    {
        walk_var_dec(get_class_var_decs(t,i)) ;
        cout <<" ;\n";
    }
    if (ndecs > 0) cout << endl;
}

void walk_var_dec(ast t)
{
    string name = get_var_dec_name(t) ;
    //Variables to reuse
    insert_strings(validClasses, name, "variable");
    string type = get_var_dec_type(t) ;
    if (type != "int" || type != "bool" ||
        type != "void" || type != "string"||
        type != "static" || type != "this" || type!= "Main"){
        //These new 'types' can be external classes
        insert_strings(validClasses, type, "class");
    }
    string segment = get_var_dec_segment(t) ;
    if (segment == "this") segment = "field";
    //If is a class var dec, then needs to print out current segment
    if (isClassVar) cout <<indent + segment +" ";
    cout << type << " " << name ;
    int offset = get_var_dec_offset(t) ;
}

void walk_subr_decs(ast t)
{
    int size = size_of_subr_decs(t) ;
    for ( int i = 0 ; i < size ; i++ )
    {   
        cout << indent;
        walk_subr(get_subr_decs(t,i)) ;
        if (i < size - 1) cout <<endl;
    }
}

void walk_subr(ast t)
{
    ast subr = get_subr_subr(t) ;

    switch(ast_node_kind(subr))
    {
    case ast_constructor:
        walk_constructor(subr) ;
        break ;
    case ast_function:
        walk_function(subr) ;
        break ;
    case ast_method:
        walk_method(subr) ;
        break ;
    default:
        fatal_error(0,"Unexpected subroutine kind") ;
        break ;
    }
}

void walk_constructor(ast t)
{
    string vtype = get_constructor_vtype(t) ;
    cout << "constructor "+ vtype + " ";
    string name = get_constructor_name(t) ;
    cout << name+"(";

    ast param_list = get_constructor_param_list(t) ;
    //Add the constructor and its number of parameters to table
    insert_ints(subrs, name, size_of_param_list(param_list));

    walk_param_list(param_list) ;
    cout << ")\n"+ indent +"{\n";

    ast subr_body = get_constructor_subr_body(t) ;
    walk_subr_body(subr_body) ;
    cout << indent + "}\n";
    
    
}

void walk_function(ast t)
{
    string vtype = get_function_vtype(t) ;
    cout << "function "+ vtype + " ";
    string name = get_function_name(t) ;

    cout << name+"(";
    ast param_list = get_function_param_list(t) ;
    walk_param_list(param_list) ;
    //Add the subroutine and its number of parameters to table
    insert_ints(subrs, name, size_of_param_list(param_list));
    cout << ")\n"+ indent +"{\n";

    ast subr_body = get_function_subr_body(t) ;    
    walk_subr_body(subr_body) ;
    cout << indent + "}\n";
}

void walk_method(ast t)
{
    string vtype = get_method_vtype(t) ;
    cout << "method "+ vtype + " ";
    string name = get_method_name(t) ;

    cout << name+"(";
    
    ast param_list = get_method_param_list(t) ;
    //Add the subroutine and its number of parameters to table
    insert_ints(subrs, name, size_of_param_list(param_list));
    walk_param_list(param_list) ;
    cout << ")\n"+ indent +"{\n";
    
    ast subr_body = get_method_subr_body(t) ;
    walk_subr_body(subr_body) ;
    cout << indent + "}\n";
}

void walk_param_list(ast t)
{
    int ndecs = size_of_param_list(t) ;
    //Walk the parameter tree and print out any existing parameters of current subroutine
    for ( int i = 0 ; i < ndecs ; i++ )
    {
        walk_var_dec(get_param_list(t,i)) ;
        if (i < ndecs - 1) cout << ",";
    }
}

void walk_subr_body(ast t)
{
    ast decs = get_subr_body_decs(t) ;
    ast body = get_subr_body_body(t) ;

    walk_var_decs(decs) ;
    walk_statements(body) ;
}

void walk_var_decs(ast t)
{
    int ndecs = size_of_var_decs(t) ;
    for ( int i = 0 ; i < ndecs ; i++ )
    {
        cout << "        var ";
        walk_var_dec(get_var_decs(t,i)) ;
        cout << " ;\n";
    }
    if (ndecs > 0) cout << endl;
}

void walk_statements(ast t)
{
    int nstatements = size_of_statements(t) ;
    for ( int i = 0 ; i < nstatements ; i++ )
    {
        walk_statement(get_statements(t,i)) ;
        ast nowKind = ast_node_kind(get_statement_statement(get_statements(t,i)));
        if (nowKind == ast_if || nowKind == ast_if_else || nowKind == ast_while){
            if (i < nstatements - 1) cout << endl;
        }
    }
}

void walk_statement(ast t)
{
    ast statement = get_statement_statement(t) ;

    switch(ast_node_kind(statement))
    {
    case ast_let:
        walk_let(statement) ;
        break ;
    case ast_let_array:
        walk_let_array(statement) ;
        break ;
    case ast_if:
        walk_if(statement) ;
        break ;
    case ast_if_else:
        walk_if_else(statement) ;
        break ;
    case ast_while:
        walk_while(statement) ;
        break ;
    case ast_do:
        walk_do(statement) ;
        break ;
    case ast_return:
        walk_return(statement) ;
        break ;
    case ast_return_expr:
        walk_return_expr(statement) ;
        break ;
    case ast_statements:
        walk_statements(statement) ;
        break ;
    default:
        fatal_error(0,"Unexpected statement kind") ;
        break ;
    }
    
}

void walk_let(ast t)
{   
    ast var = get_let_var(t) ;
    ast expr = get_let_expr(t) ;
    //Print out the right hand side
    //Get correct indent
    string myIndent = "";
    for (int i = 0; i < indentLvl + 1; i++){
        myIndent += indent;
    }
    cout << myIndent + "let ";
    walk_var(var) ;
    cout << " = ";
    walk_expr(expr) ;
    cout <<" ;\n";
}

void walk_let_array(ast t)
{
    string myIndent;
    ast var = get_let_array_var(t) ;
    ast index = get_let_array_index(t) ;
    ast expr = get_let_array_expr(t) ;
    for (int i = 0; i < indentLvl + 1; i++){
        myIndent += indent;
    }
    cout << myIndent + "let ";

    walk_var(var) ;
    cout << "[";
    walk_expr(index) ;
    cout << "] = ";
    walk_expr(expr) ;
    cout <<" ;\n";
}

void walk_if(ast t)
{
    ast condition = get_if_condition(t) ;
    ast if_true = get_if_if_true(t) ;
    //Get correct indent
    string myIndent = "";
    for (int i = 0; i < indentLvl + 1; i++){
        myIndent += indent;
    }
    cout << myIndent + "if (";
    walk_expr(condition) ;
    //print the corresponding bracket
    cout << ")\n";
    cout << myIndent + "{\n";  
    //Increase indent
    indentLvl++;
    walk_statements(if_true) ;
    //Decrease indent after done in body
    indentLvl--;
    cout << myIndent + "}\n";
}

void walk_if_else(ast t)
{
    ast condition = get_if_else_condition(t) ;
    ast if_true = get_if_else_if_true(t) ;
    ast if_false = get_if_else_if_false(t) ;
    string myIndent = "";
    for (int i = 0; i < indentLvl + 1; i++){
        myIndent += indent;
    }
    cout << myIndent + "if (";
    walk_expr(condition) ;
    cout << ")\n";
    cout << myIndent + "{\n";
    //Increase indent
    indentLvl++;
    walk_statements(if_true) ;
    //Decrease back sincee out of body
    indentLvl--;
    cout << myIndent + "}\n";
    //Print out else part
    cout << myIndent + "else\n";
    cout << myIndent + "{\n";
    //Increase indent again for else statement
    indentLvl++;
    walk_statements(if_false) ;
    indentLvl--;
    cout << myIndent + "}\n";
    }

void walk_while(ast t)
{
    ast condition = get_while_condition(t) ;
    ast body = get_while_body(t) ;
    //Get correct indent
    string myIndent = "";
    for (int i = 0; i < indentLvl + 1; i++){
        myIndent += indent;
    }
    cout << myIndent + "while (";
    walk_expr(condition) ;
    cout << ")\n";
    cout << myIndent + "{\n";
    //Increase indent
    indentLvl++;
    walk_statements(body) ;
    //Decrease indent after done in body
    indentLvl--;
    cout << myIndent + "}\n";
}

void walk_do(ast t)
{   
    ast call = get_do_call(t) ;
    string subr_name = get_call_subr_name(call);
    string myIndent;
    for (int i = 0; i < indentLvl + 1; i++){
        myIndent += indent;
    }
    ast expr_list = get_call_expr_list(call) ;
    cout << myIndent + "do ";
    

    walk_call(call) ;
    cout << " ;\n";
}

void walk_call(ast t)
{
    bool method_call = get_call_method_call(t) ;
    string class_name = get_call_class_name(t) ;
    string subr_name = get_call_subr_name(t) ;
    //Total argument of this func
    int totArgs = lookup_ints(subrs, subr_name);
    
    ast expr_list = get_call_expr_list(t) ;
    
    int nexpressions = size_of_expr_list(expr_list) ;
    //Print the class name if current subr is not a call from a var
    ast temp ;
    int i = nexpressions - totArgs;
    if (nexpressions > totArgs && nexpressions > 0){        
        //Get the node to check if it is a var, if it is then is it a class type var
        //If not then all the nodes in explist go to inside
        temp = get_term_term(get_expr(get_expr_list(expr_list, 0), 0));
        if (ast_node_kind(temp) != ast_var && ast_node_kind(temp) != ast_this) {
            i = 0;
            cout << class_name;
        }
        else if (ast_node_kind(temp) == ast_var){
            if (get_var_type(temp) == class_name) {
                walk_expr(get_expr_list(expr_list, 0));
                // subroutine does not have any reistered arg, expression list then contains the param list
                if (totArgs < 1) i = 1;
            }else {
                cout << class_name;
                i = 0;
            }
        }
        else walk_expr(get_expr_list(expr_list, 0));
    }
    else {
        cout << class_name;
        i = nexpressions - totArgs;
    }
    //Print the subr name
    cout << "." + subr_name + "(";
    //Print out parameter list, if there us any
    if (i >= 0){
        for (i = i; i < nexpressions; i++){
            walk_expr(get_expr_list(expr_list, i));
            if (i < nexpressions - 1) cout << ",";
        }
    }
    cout <<")";
    
}

void walk_return(ast t)
{
    cout <<indent + indent +"return ;\n";
}

void walk_return_expr(ast t)
{
    ast expr = get_return_expr(t) ;
    cout <<indent + indent + "return ";
    walk_expr(expr) ;
    cout << " ;\n";
}

void walk_expr_list(ast t)
{
    int nexpressions = size_of_expr_list(t) ;
    for ( int i = 0 ; i < nexpressions ; i++ )
    {
        walk_expr(get_expr_list(t,i)) ;
    }
}

void walk_expr(ast t)
{
    int term_ops = size_of_expr(t) ;
    bool bracket = false;
    int reInx = -1;
    
    for ( int i = 0 ; i < term_ops ; i++ )
    {
        ast term_op = get_expr(t,i) ;
        if ( i % 2 == 1)
        {   
            //string representation
            string to_sp = get_op_op(term_op) ;
            if (to_sp == "<" || to_sp == ">" || to_sp == "=") reInx = i - 1;
        }
    }
    
    for ( int i = 0 ; i < term_ops ; i++ )
    {
        ast term_op = get_expr(t,i) ;
        if ( i % 2 == 0 )
        {   
            //If the current node is actually another expression, add brackets around it
            if (ast_node_kind(get_term_term(term_op)) == ast_expr){
                bracket = true;
            }
            if (i == reInx && reInx > - 1) cout << "(";
            if (bracket){
                cout << "(";
            }
             
            walk_term(term_op) ;
            if (bracket) cout <<")";
            if (i == reInx + 2 && reInx > -1) cout << ")";
        }
        else
        {
            walk_op(term_op) ;
        }
        bracket = false;
    }
}

void walk_term(ast t)
{
    ast term = get_term_term(t) ;

    switch(ast_node_kind(term))
    {
    case ast_int:
        walk_int(term) ;
        break ;
    case ast_string:
        walk_string(term) ;
        break ;
    case ast_bool:
        walk_bool(term) ;
        break ;
    case ast_null:
        walk_null(term) ;
        break ;
    case ast_this:
        walk_this(term) ;
        break ;
    case ast_expr:
        walk_expr(term) ;
        break ;
    case ast_var:
        walk_var(term) ;
        break ;
    case ast_array_index:
        walk_array_index(term) ;
        break ;
    case ast_unary_op:
        walk_unary_op(term) ;
        break ;
    case ast_call:
        walk_call(term) ;
        break ;
    default:
        fatal_error(0,"Unexpected term kind") ;
        break ;
    }
}

void walk_op(ast t)
{   
    //1 space before and after operator
    string op = get_op_op(t) ;
    cout <<" " + op + " ";
}

void walk_int(ast t)
{
    int _constant = get_int_constant(t) ;
    cout << _constant;
}

void walk_string(ast t)
{
    string _constant = get_string_constant(t) ;
    cout <<'"' + _constant +'"';
}

void walk_bool(ast t)
{
    bool _constant = get_bool_t_or_f(t) ;
    cout << boolalpha << _constant;
}

void walk_null(ast t)
{
    cout << "null";
}

void walk_this(ast t)
{
    cout << "this";
}

void walk_var(ast t)
{
    string name = get_var_name(t) ;
    cout << name;
    string type = get_var_type(t) ;
    string segment = get_var_segment(t) ;
    int offset = get_var_offset(t) ;
}

void walk_array_index(ast t)
{
    ast var = get_array_index_var(t) ;
    ast index = get_array_index_index(t) ;

    walk_var(var) ;
    cout <<"[";
    int term_ops = size_of_expr(index) ;
    if (term_ops > 1){
    }
    for ( int i = 0 ; i < term_ops ; i++ )
    {
        ast term_op = get_expr(index,i) ;
        if ( i % 2 == 0 )
        {
            walk_term(term_op) ;
        }
        else
        {
            walk_op(term_op) ;
        }
    }
    cout <<"]";
}

void walk_unary_op(ast t)
{
    string uop = get_unary_op_op(t);
    cout << uop;
    ast term = get_unary_op_term(t) ;

    walk_term(term) ;
}

// main program
int main(int argc,char **argv)
{
    subrs = create_ints();
    addClasses();    
    // walk an AST parsed from XML and pretty print equivalent Jack code
    walk_class(ast_parse_xml()) ;

    // flush the output and any errors
    print_output() ;
    print_errors() ;
}

