#include "iobuffer.h"
#include "symbols.h"
#include "abstract-syntax-tree.h"

// to shorten our code:
using namespace std ;
using namespace Jack_Compiler ;

// ***** WHAT TO DO *****
//
// MODIFY the skeleton code below to walk an abstract syntax tree, ast, of a Jack class
//        and generate the equivalent Hack Virtual Machine Code.
//
// NOTE: the correct segment and offset is recorded with every variable in the ast
//       so the code generator does not need to use any symbol tables
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
void walk_var(ast t, string s) ;
void walk_array_index(ast t) ;
void walk_unary_op(ast t) ;

//n-th while node encountered
static int countWhile = -1;
//n-th if node encountered
static int countIf = -1;
//class name
static string myclassname;
//current number of field num
static int field = 0;
//is it a function call in return statement
static bool returncall;
//length of string var in function
static int str_len;
void walk_class(ast t)
{
    myclassname = get_class_class_name(t) ;
    ast var_decs = get_class_var_decs(t) ;
    ast subr_decs = get_class_subr_decs(t) ;

    walk_class_var_decs(var_decs) ;
    walk_subr_decs(subr_decs) ;
}

void walk_class_var_decs(ast t)
{
    int ndecs = size_of_class_var_decs(t) ;
    for ( int i = 0 ; i < ndecs ; i++ )
    {
        walk_var_dec(get_class_var_decs(t,i)) ;
    }
}

void walk_var_dec(ast t)
{
    string name = get_var_dec_name(t) ;
    string type = get_var_dec_type(t) ;
    string segment = get_var_dec_segment(t) ;
    // Increase counted number of field variables
    if (segment == "this") field ++;
    int offset = get_var_dec_offset(t) ;
}

void walk_subr_decs(ast t)
{
    int size = size_of_subr_decs(t) ;
    for ( int i = 0 ; i < size ; i++ )
    {   
        //All subroutines represented as functions
        write_to_output("function ");
        walk_subr(get_subr_decs(t,i)) ;
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
    //reset number of  if encountered
    countIf = -1;       
    string vtype = get_constructor_vtype(t) ;
    string name = get_constructor_name(t) ;
    ast param_list = get_constructor_param_list(t) ;
    ast subr_body = get_constructor_subr_body(t) ;

    write_to_output(myclassname +"." +name + " " + to_string(size_of_var_decs(get_subr_body_decs(subr_body)))) ;
    write_to_output("\n");
    //Number of field variables is constant
    write_to_output("push constant " + to_string(field) + "\n");
    //Allocate 1 mmemory position when constructin
    write_to_output("call Memory.alloc 1\n");
    walk_param_list(param_list) ;
    walk_subr_body(subr_body) ;
}

void walk_function(ast t)
{   
    countIf = -1;
    string vtype = get_function_vtype(t) ;
    string name = get_function_name(t) ;
    ast param_list = get_function_param_list(t) ;
    ast subr_body = get_function_subr_body(t) ;
    write_to_output(myclassname +"." +name + " " + to_string(size_of_var_decs(get_subr_body_decs(subr_body)))) ;
    write_to_output("\n");
    walk_param_list(param_list) ;
    returncall = false;
    walk_subr_body(subr_body) ;
}

void walk_method(ast t)
{
    countIf = -1;
    string vtype = get_method_vtype(t) ;
    string name = get_method_name(t) ;
    ast param_list = get_method_param_list(t) ;
    ast subr_body = get_method_subr_body(t) ;
    write_to_output(myclassname +"." +name + " " + to_string(size_of_var_decs(get_subr_body_decs(subr_body)))) ;
    write_to_output("\n");
    walk_param_list(param_list) ;
    write_to_output("push argument 0\n");
    returncall = true;
    walk_subr_body(subr_body) ;
    returncall = false;
}

void walk_param_list(ast t)
{
    int ndecs = size_of_param_list(t) ;
    for ( int i = 0 ; i < ndecs ; i++ )
    {
        walk_var_dec(get_param_list(t,i)) ;
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
        walk_var_dec(get_var_decs(t,i)) ;
    }
}

void walk_statements(ast t)
{
    
    int nstatements = size_of_statements(t) ;
    for ( int i = 0 ; i < nstatements ; i++ )
    {
        walk_statement(get_statements(t,i)) ;
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
        countIf++;
        walk_if(statement) ;
        break ;
    case ast_if_else:
        countIf++;
        walk_if_else(statement) ;
        break ;
    case ast_while:
        countWhile++;
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
    //Right hand side of let
    ast expr = get_let_expr(t) ;
    
    walk_expr(expr);
    // Pop to left hand
    walk_var(var, "pop") ;
}

void walk_let_array(ast t)
{
    ast var = get_let_array_var(t) ;
    ast index = get_let_array_index(t) ;
    ast expr = get_let_array_expr(t) ;

    
    walk_expr(expr) ;
    //Store result to a temp
    write_to_output("pop temp 0\n");
    //Get it to a pointer
    write_to_output("pop pointer 1\n");
    //leave it on  stack
    walk_expr(index) ;
    write_to_output("push temp 0\n");    
    //store to another
    write_to_output("pop that 0\n");

    walk_var(var, "pop") ;
}

void walk_if(ast t)
{
    //current if num
    int myLvl = countIf;
    ast condition = get_if_condition(t) ;
    ast if_true = get_if_if_true(t) ;
    //Print the condition
    walk_expr(condition) ;
    //if true
    write_to_output("if-goto IF_TRUE" + to_string(myLvl) + "\n");
    write_to_output("goto IF_FALSE" + to_string(myLvl) + "\n");
    write_to_output("label IF_TRUE" + to_string(myLvl) + "\n");
    myLvl++; //
    walk_statements(if_true) ;    
    myLvl--;
    write_to_output("label IF_FALSE" + to_string(myLvl) + "\n");
}

void walk_if_else(ast t)
{
    ast condition = get_if_else_condition(t) ;
    ast if_true = get_if_else_if_true(t) ;
    ast if_false = get_if_else_if_false(t) ;
    walk_expr(condition);
    //the number of if
    int myLvl = countIf;
    write_to_output("if-goto IF_TRUE" + to_string(myLvl) + "\n");
    write_to_output("goto IF_FALSE" + to_string(myLvl) + "\n");
    write_to_output("label IF_TRUE" + to_string(myLvl) + "\n");
    myLvl++;
    walk_statements(if_true) ;
    myLvl--;
    write_to_output("goto IF_END" + to_string(myLvl) + "\n");
    write_to_output("label IF_FALSE" + to_string(myLvl) + "\n");
    myLvl++;    
    walk_statements(if_false) ;
    myLvl--;
    write_to_output("label IF_END" + to_string(myLvl) + "\n");
}

void walk_while(ast t)
{       
    ast condition = get_while_condition(t) ;
    ast body = get_while_body(t) ;
    int myLvl = countWhile;
    write_to_output("label WHILE_EXP" + to_string(myLvl) +"\n");
    walk_expr(condition) ;
    write_to_output("not\nif-goto WHILE_END" + to_string(myLvl) +"\n");
    myLvl++;
    walk_statements(body) ;
    myLvl--;
    write_to_output("goto WHILE_EXP" + to_string(myLvl) + "\n");
    write_to_output("label WHILE_END" + to_string(myLvl) +"\n");
}

void walk_do(ast t)
{
    ast call = get_do_call(t) ;
    walk_call(call) ;
    write_to_output("pop temp 0\n");
}

void walk_call(ast t)
{
    
    bool method_call = get_call_method_call(t) ;
    string class_name = get_call_class_name(t) ;
    
    string subr_name = get_call_subr_name(t) ;
    ast expr_list = get_call_expr_list(t) ;
    walk_expr_list(expr_list) ;
    write_to_output("call " + class_name + "." +subr_name + " " + to_string( size_of_expr_list(expr_list) ) +"\n");
}

void walk_return(ast t)
{  
    write_to_output("push constant 0\n");
    write_to_output( "return\n");
}

void walk_return_expr(ast t)
{   
    returncall = true;
    ast expr = get_return_expr(t) ;
    // get the first node from the expression
    ast exp1 = get_expr(expr, 0);
    //Get the first term of that node
    ast termFirst = get_term_term(exp1);
    walk_expr(expr) ;
    write_to_output( "return\n");
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
    //Make a list of ops
    vector <ast> ops;
    int term_ops = size_of_expr(t) ;
    //Record the operators
    for ( int i = 0 ; i < term_ops ; i++ )
    {
        ast term_op = get_expr(t,i) ;
        if ( i % 2 == 1 ) ops.push_back(term_op);        
    }
    //Print out output
    for ( int i = 0 ; i < term_ops ; i++ )
    {
        ast term_op = get_expr(t,i) ;
        if ( i % 2 == 0 )
        {   
            if (ast_node_kind(get_term_term(term_op)) == ast_call) {
                if (i > 1) walk_op(ops[(i - 2)/2]);
                walk_term(term_op);
            }
            else {
                walk_term(term_op);
                if (i > 1) walk_op(ops[(i - 2)/2]);
            }
        }        
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
        walk_var(term, "push") ;
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
    string op = get_op_op(t) ;
    if (op == "+") write_to_output("add\n");
    else if (op == "-") write_to_output("sub\n");
    else if (op == ">") write_to_output("gt\n");
    else if (op == "<") write_to_output("lt\n");
    else if (op == "*") write_to_output("call Math.multiply 2\n");
    else if (op == "/") write_to_output("call Math.divide 2\n");
}

void walk_int(ast t)
{
    int _constant = get_int_constant(t) ;
    write_to_output("push constant " + to_string(_constant) +"\n");
}

void walk_string(ast t)
{
    string _constant = get_string_constant(t) ;
    write_to_output("push constant " + to_string(_constant.length()) +"\n");
    //Call a function to recieve a new string
    write_to_output("call String.new 1\n");
    //Convert these string to ASCII val and add it
    for (int i = 0; i < int(_constant.length()); i++){
        char c = _constant.at(i);
        write_to_output("push constant " + to_string(int(c)) +"\n");
        write_to_output("call String.appendChar 2\n");
    }
}

void walk_bool(ast t)
{
    bool _constant = get_bool_t_or_f(t) ;
    write_to_output("push constant 0\n");
    if (_constant) write_to_output("not\n");
}

void walk_null(ast t)
{
}

void walk_this(ast t)
{
    if (returncall == true){
        returncall = false;
        write_to_output("pop pointer 0\n");
    }
    
    write_to_output("push pointer 0\n");
}

void walk_var(ast t, string stat)
{
    string name = get_var_name(t) ;
    string type = get_var_type(t) ;
    string segment = get_var_segment(t) ;
    int offset = get_var_offset(t) ;
    if (segment == "this"  || returncall == true ) {
        write_to_output("pop pointer 0\n");
    }
    if (stat != "pop") write_to_output("push " + segment + " " + to_string(offset) + "\n");
    else {
        write_to_output("pop " + segment + " " + to_string(offset) + "\n");
    }
}

void walk_array_index(ast t)
{

    ast var = get_array_index_var(t) ;
    ast index = get_array_index_index(t) ;
    walk_expr(index) ;
    walk_var(var, "push") ;
    //Accessing an array value
    write_to_output("pop pointer 1\n");
    
}

void walk_unary_op(ast t)
{
    string uop = get_unary_op_op(t);

    ast term = get_unary_op_term(t) ;

    walk_term(term) ;
    if (uop == "-"){
        write_to_output("neg\n");
    }
}

// main program
int main(int argc,char **argv)
{
    //config_errors(iob_buffer);
    // walk an AST parsed from XML and print VM code
    walk_class(ast_parse_xml()) ;

    // flush the output and any errors
    print_output() ;
    print_errors() ;
}

