// tokeniser implementation for the workshop example language

#include "tokeniser.h"
#include <ctype.h>

// to shorten the code
using namespace std ;

// we are extending the Workshop_Tokeniser namespace

namespace Workshop_Tokeniser
{
    // parse a single character symbol
    // we know ch is the one character symbol
    static Token parse_symbol(TokenKind kind)
    {
        // first record the spelling
        string spelling = string(1,ch); 

        // always read one character past the end of the token
        nextch() ;

        // return a new Token object
        return new_token(kind,spelling) ;
    }

    static Token parse_less(){
        // always read one character past the end of the token
        nextch();
        //Then return a new token object depends on the case
        if (ch == '='){
            // always read one character past the end of the token
            nextch();
            return new_token(tk_le, "<=");
        }return new_token(tk_lt, "<");
        
    }

    static Token parse_more(){
        nextch();
        if (ch == '='){
            // always read one character past the end of the token
            nextch();
            return new_token(tk_ge, ">=");
        }return new_token(tk_gt, ">");
        
    }

    static Token notEqual(){
        nextch();
        if (ch == '='){
            // always read one character past the end of the token
            nextch();
            return new_token(tk_ne, "!=");
        }return new_token(tk_oops, "!");
    }

    static Token EqualOrAssign(){
        nextch();
        if (ch == '='){
            // always read one character past the end of the token
            nextch();
            return new_token(tk_eq, "==");
        }return new_token(tk_assign, "=")       ; 
    }

    // parse a number - always read one extra character
    // we know ch is the first digit of the number
    static Token parse_integer()
    {
        string spelling = "" ;

        // append digits to spelling until we read past the end of the integer
        do
        {
            spelling += ch ;
            nextch() ;
        } while ( isdigit(ch) ) ;

        // return a new Token object
        return new_token(tk_integer,spelling) ;
    }

    static Token parse_identifier()
    {
        string spelling = "" ;

        // append digits to spelling until we read past the end of the integer
        do
        {
            spelling += ch ;
            
            nextch() ;
        } while ( isalpha(ch) or isdigit(ch)) ;
        // return a new Token object
        if (spelling == "if"){
            return new_token(tk_if, "if");
        }

        if (spelling == "else"){
            return new_token(tk_else, "else");
        }

        if (spelling == "while"){
            return new_token(tk_while, "while");
        }

        if (spelling == "var"){
            return new_token(tk_var, "var");
        }

        if (spelling == "let"){
            return new_token(tk_let, "let");
        }
        return new_token(tk_identifier,spelling) ;
    }

    // return the next Token object by reading more of the input
    Token next_token()
    {
        while ( ch != EOF )	            // loop until EOF or a token is read
        {
            switch(ch)			        // ch is always the next char to read
            {
            case ' ':			        // ignore whitespace
            case '\t':
            case '\r':
            case '\n':
                nextch() ;              // read next character and go around again
                break ;
                                        // when we find the first character of a token
                                        // call a function to read all of its characters

            case '{':
                return parse_symbol(tk_lcb) ;
            case '}':
                return parse_symbol(tk_rcb) ;
            case '<': return parse_less();
            case '>': return parse_more();
            case '!':return notEqual();
            case '=': return EqualOrAssign();
            // single special
            case '@': return parse_symbol(tk_at);
            case '(': return parse_symbol(tk_lrb);
            case ')': return parse_symbol(tk_rrb);
            case ':': return parse_symbol(tk_colon);
            case ';': return parse_symbol(tk_semi);
            case '.': return parse_symbol(tk_dot);
            case ',': return parse_symbol(tk_comma);
            case '"': return parse_symbol(tk_dquote);

            // ops
            case '+': return parse_symbol(tk_add);
            case '-': return parse_symbol(tk_sub);
            case '*': return parse_symbol(tk_times);
            case '/': return parse_symbol(tk_divide);
                

            case '0'...'9':             // you can use ranges such as '0' to '9'
                return parse_integer() ;
            case 'a'...'z':
                return parse_identifier();
            case 'A'...'Z':
                return parse_identifier();
            default:			        // anything unexpected - return ?
                ch = EOF ;
                return new_token(tk_eoi,"") ;
            }
        }
        ch = EOF ;
        return new_token(tk_eoi,"") ;
    }
}

