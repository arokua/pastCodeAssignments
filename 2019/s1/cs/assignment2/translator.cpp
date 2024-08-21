// convert an abstract syntax tree for Hack Assembly language into machine code
#include "iobuffer.h"
#include "symbols.h"
#include "tokeniser.h"
#include "abstract-syntax-tree.h"
#include <string>
#include <iostream>
#include <algorithm>
// to simplify the code
using namespace std ;
using namespace CS_Symbol_Tables ;
using namespace Hack_Assembler ;

//Dest, comp and jump in string of the C-instruction
static string Dest;
static string Comp;
static string Jump;
//name of A instruction
static string name;
//C-instruction map table
static symbols tableC;
static symbols tableA;
//Label name
static string label;
//Current memory
static int memStart = 0;
//First free RAM slot
static int memFree = 16;

//The ast program to be translated
static ast Program;

static void makeCTable(){
    tableC = create_strings();
    //Mapp all binary values to dest, comp and alu
    //This function is called only once per program to make a table

    //NULL is same for both dest and jump, comp doesnot have null
    insert_strings(tableC, "NULL", "000");
    //Mapping jumps
    insert_strings(tableC, "JMP", "111");
        //
    insert_strings(tableC, "JGT", "001");
    insert_strings(tableC, "JEQ", "010");
    insert_strings(tableC, "JLT", "100");
        //
    insert_strings(tableC, "JGE", "011");
    insert_strings(tableC, "JNE", "101");
    insert_strings(tableC, "JLE", "110");

    //Mapping dest
    insert_strings(tableC, "Mdest", "001");
    insert_strings(tableC, "Ddest", "010");
    insert_strings(tableC, "Adest", "100");
        //
    insert_strings(tableC, "MD", "011");
    insert_strings(tableC, "AD", "110");
    insert_strings(tableC, "AM", "101");
    insert_strings(tableC, "AMD", "111");

    //Mapping alu-s
        //a = 0 - nummeric ops
    insert_strings(tableC, "0", "0101010"); // 0
    insert_strings(tableC, "1", "0111111"); // 1
    insert_strings(tableC, "-1", "0111010"); // -1
        //a = 0 -single registers
    insert_strings(tableC, "D", "0001100"); // D
    insert_strings(tableC, "A", "0110000"); // A
    insert_strings(tableC, "!D", "0001101"); // !D
    insert_strings(tableC, "!A", "0110001"); // !A
    insert_strings(tableC, "-D", "0001111"); // -D
    insert_strings(tableC, "-A", "0110011"); // -A
        //a = 0 - binary operations
    insert_strings(tableC, "D+1", "0011111"); // D + 1
    insert_strings(tableC, "A+1", "0110111"); // A + 1
    insert_strings(tableC, "D-1", "0001110"); // D - 1
    insert_strings(tableC, "A-1", "0110010"); // A - 1
    insert_strings(tableC, "D+A", "0000010"); // D + A
    insert_strings(tableC, "D-A", "0010011"); // D - A
    insert_strings(tableC, "A-D", "0000111"); // A - D
    insert_strings(tableC, "D&A", "0000000"); // D & A
    insert_strings(tableC, "D|A", "0010101"); // D | A
        // a = 1  -all
    insert_strings(tableC, "M",   "1110000"); // M
    insert_strings(tableC, "!M",  "1110001"); // !M
    insert_strings(tableC, "-M",  "1110011"); // -M
    insert_strings(tableC, "M+1", "1110111"); // M + 1
    insert_strings(tableC, "M-1", "1110010"); // M - 1
    insert_strings(tableC, "D+M", "1000010"); // D + M
    insert_strings(tableC, "D-M", "1010011"); // D - M
    insert_strings(tableC, "M-D", "1000111"); // M - D
    insert_strings(tableC, "D&M", "1000000"); // D & M
    insert_strings(tableC, "D|M", "1010101"); // D | M 
}

static string parse_binary(int n){
    //create a 16-bit binary string from a given integer n
    string s = "";
    //Turn n to binary and add to s
    while (true){
        if (n == 1 or n == 0){
            s = to_string(n) + s;
            break;
        }else{
            if (n % 2 == 0) s = "0" + s;
            else s = "1" + s;
            n = n / 2;
        }
    }
    //Add the missing 0 bits to s
    while ( int(s.length()) < 16) {
        s = "0" + s;
    }
    return s;
}

static void makeATable(){
    //Hold memory addresses of all symbols encountered
    tableA = create_strings();
    //Predefined symbols
    // Advoid copy paste
    for (int i = 0; i < 16; i++){
        insert_strings(tableA,"R"+ to_string(i), parse_binary(i));
    }
    //SP first points at 0
    insert_strings(tableA,"SP", parse_binary(0));
    insert_strings(tableA,"LCL", parse_binary(1));
    insert_strings(tableA,"ARG", parse_binary(2));
    insert_strings(tableA,"THIS", parse_binary(3));
    insert_strings(tableA,"THAT", parse_binary(4));
    insert_strings(tableA,"SCREEN", parse_binary(16384));
    insert_strings(tableA,"KBD", parse_binary(24576));
}

static string c_instruct_in_bits(string dest, string alu, string jump){
    string c = ""; //Comp
    string d = "NULL"; //Dest
    string j = "NULL"; // Jump
    j = lookup_strings(tableC, jump);
    //Seperate same registers as dest with alu_ops
    if (dest != "NULL" && int(dest.length()) == 1) dest += "dest";
    d = lookup_strings(tableC, dest);
    c = lookup_strings(tableC, alu);
    return "111" + c + d + j + "\n";
}
// this function provides an example of how to walk an abstract syntax tree constructed by ast_parse_xml()s
void walk_program(ast the_program, bool doneFirstPass)
{   
    //Walk though given tree and create symbol table
    int ninstructions = size_of_program(the_program) ;
    if (doneFirstPass == false){
        
        for ( int i = 0 ; i < ninstructions ; i++ )
        {
            ast instruction = get_program(the_program,i) ;
            switch(ast_node_kind(instruction))
            {
            case ast_label:
                //Add the new label name to table
                insert_strings(tableA, get_label_name(instruction), "0");
                //Update its mem loc to newest
                update_strings(tableA, get_label_name(instruction), parse_binary(memStart));
                break ;
            case ast_a_name:
                //Increment mem address
                memStart++;
                break ;
            case ast_a_instruction:
                //Increment mem address
                memStart++;
                break ;
            case ast_c_instruction:
                //Increment mem address
                memStart++;
                break ;
            default:
                fatal_error(0,"// bad node - expected ast_label,ast_a_name,ast_a_instruction or ast_c_instruction\n") ;
                break ;
            }
        }
    }else {
        //Move to second pass to add variables name
        for ( int i = 0 ; i < ninstructions ; i++ )
        {
            ast instruction = get_program(the_program,i) ;
            switch(ast_node_kind(instruction))
            {
            case ast_label:
                break ;
            case ast_a_name:
                label = get_a_name_unresolved(instruction);
                if (lookup_strings(tableA, label) == ""){
                    insert_strings(tableA, label, "0");
                    update_strings(tableA, label, parse_binary(memFree));
                    memFree++;
                }
                break ;
            case ast_a_instruction:
                break ;
            case ast_c_instruction:
                break ;
            default:
                fatal_error(0,"// bad node - expected ast_label,ast_a_name,ast_a_instruction or ast_c_instruction\n") ;
                break ;
            }
        }
    }
}

// translate an abstract syntax tree representation of Hack Assembly language into Hack machine code
static void asm_translator(ast the_program)
{   
    //Walk though given program and prints out binary code
    int nodeCount = size_of_program(the_program) ;
    for ( int i = 0 ; i < nodeCount ; i++)
    {
        ast instruction = get_program(the_program,i) ;
        switch(ast_node_kind(instruction))
        {
        case ast_label:
            break ;
        case ast_a_name:
            write_to_output(lookup_strings(tableA, get_a_name_unresolved(instruction)) + "\n");
            break ;
        case ast_a_instruction:
            write_to_output(parse_binary( get_a_instruction_value(instruction)) + "\n");
            break ;
        case ast_c_instruction:
            // Get the individual values from the instruction
            Dest = get_c_instruction_dest(instruction);
            Comp = get_c_instruction_alu(instruction);
            Jump = get_c_instruction_jump(instruction);
            write_to_output(c_instruct_in_bits(Dest, Comp, Jump));
            break ;
        default:
            fatal_error(0,"// bad node - expected ast_label,ast_a_name,ast_a_instruction or ast_c_instruction\n") ;
            break ;
        }
    }
}

// main program
int main(int argc,char **argv)
{   
    Program = ast_parse_xml();
    // error messages
    config_errors(iob_buffer) ;
    //Make the c table
    makeCTable();
    //Make the symbol table from A instructions
    makeATable();
    walk_program(Program, false);
    walk_program(Program, true);
    // parse abstract syntax tree and pass to the translator
    asm_translator(Program) ;

    // flush output and errors
    print_output() ;
    print_errors() ;
}
