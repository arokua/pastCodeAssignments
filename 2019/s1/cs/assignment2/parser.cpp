// convert Hack Assembly Language into an abstract syntax tree
#include "iobuffer.h"
#include "tokeniser.h"
#include "abstract-syntax-tree.h"
#include <iostream>
// to make out programs a bit neater
using namespace std ;

using namespace Hack_Assembler ;

// grammer to be parsed:
// a_program ::= instruction* eoi
// instruction ::= a_label | a_instr_name | a_instruction | c_instr_dest | c_instr_reg | c_instr_alu
// a_label ::= label
// a_instr_name ::= name
// a_instruction ::= number
// c_instr_reg ::= register (equals alu)? (semi jump)?
// c_instr_dest ::= dest equals alu (semi jump)?
// c_instr_alu ::= alu (semi jump)?
// Tokens: label, name, number, null, dest, register, alu, jump

// forward declare parsing functions - one per rule
ast parse_program() ;
ast parse_instruction() ;
ast parse_a_label() ;
ast parse_a_instr_name() ;
ast parse_a_instruction() ;
ast parse_c_instr_dest() ;
ast parse_c_instr_reg() ;
ast parse_c_instr_alu() ;

// Note: always read one token after the one recognised

// a_program ::= instruction* eoi
ast parse_program()
{
    vector<ast> instructions ;

    // we stop when we see the EOI token
    // this may be end of input or an error
    // we cannot tell so treat both as end of input
    // every new assembler instruction we find is appended to the_program
    while ( have(tk_instruction) )
    {
        instructions.push_back(parse_instruction()) ;
    }
    mustbe(tk_eoi) ;

    return create_program(instructions) ;
}

/*****************   REPLACE THE FOLLOWING CODE  ******************/

// a_program ::= instruction* eoi
ast parse_instruction()
{   
    
    // inspect the token to see what it might start
    if ( have(tk_label) ) return parse_a_label() ;
    if ( have(tk_name) ) return parse_a_instr_name() ;
    if ( have(tk_number) ) return parse_a_instruction() ;
    if ( have(tk_register) ) return parse_c_instr_reg() ;
    if ( have(tk_dest) ) return parse_c_instr_dest() ;
    if ( have(tk_alu_op) ){
        return parse_c_instr_alu() ;
    }
    mustbe(tk_instruction);
    return -1;
}

// tk_label is the token for '(' label ')'
ast parse_a_label()
{   
	//Create a label with spelling of current token
    string label = token_spelling(mustbe(tk_label));
    return create_label(label) ;
}

// tk_address is the token for '@' name
ast parse_a_instr_name()
{
    //Create ast node that is a symbol from an A instruction
    string name = token_spelling(mustbe(tk_name)) ;

    return create_a_name(name) ;
}

// tk_number is the token for '@' number
ast parse_a_instruction()
{
    /*Create ast node that holds the int value the A-instruction    
      points to*/
    int ivalue = token_ivalue(mustbe(tk_number));

    return create_a_instruction(ivalue) ;
}

// c_instruction ::= tk_register (tk_assign tk_alu)? (tk_semi tk_jump)?
ast parse_c_instr_reg()
{   
    //Create a c_instruction where the dest is a register

    //Holder to the current spelling since unknown is dest or is
    // alu
    string now = token_spelling(mustbe(tk_register)) ;
    string dest;
    string alu = "";
    string jump ="";
    if (token_kind() == tk_assign){
        //There is an alu op after first accepted token
	  // So dest is not null and alu_op is accepted from input
        dest = now;
        next_token();
        alu = token_spelling(mustbe(tk_alu_op));
        if (token_kind() == tk_semi){
		 //Check if there is a jump op right after
            next_token();
            jump = token_spelling(mustbe(tk_jump));
        }else{
            jump = "NULL";
        }
    }
    else if (token_kind() == tk_semi){
	   //No '=' sign, means now must be an alu op
        dest = "NULL";
        next_token();
        alu = now;
        jump = token_spelling(mustbe(tk_jump));

    }
    

    return create_c_instruction(dest,alu,jump) ;
}

// c_instruction ::= tk_dest tk_assign tk_alu (tk_semi tk_jump)?
ast parse_c_instr_dest()
{   
    //Create a c_instruction that is between a tk_dest and
    //tk_alu_op
    string dest = token_spelling(mustbe(tk_dest)) ;
    //Skip the assign
    next_token();
    string alu = token_spelling(mustbe(tk_alu_op));
    string jump;
    if (token_kind() == tk_semi){
        jump = token_spelling(mustbe(tk_jump));
    }else{
        jump = "NULL";
    }

    return create_c_instruction(dest,alu,jump) ;
}

// c_instruction ::= tk_alu (tk_semi tk_jump)?
ast parse_c_instr_alu()
{   
    //Create a C instruction for cases that can only be 
    // an alu op_and jump
    string dest = "NULL" ;
    string alu = token_spelling(mustbe(tk_alu_op));
    string jump;
    if (token_kind() == tk_semi){
        next_token();
        jump = token_spelling(mustbe(tk_jump));
    }else{
        jump = "NULL";
    }
    return create_c_instruction(dest,alu,jump) ;
}

/*****************        DOWN TO HERE         ******************/


// main program
int main(int argc,char **argv)
{
    // hide error messages
    //config_errors(iob_buffer) ;

    // initialise the tokeniser by reading the first token
    next_token() ;
    // parse a class and print the abstract syntax tree as XML
    ast_print_as_xml(parse_program(),4) ;

    // flush the output and any errors
    print_output() ;
    print_errors() ;
}

