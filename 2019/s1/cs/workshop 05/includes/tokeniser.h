#ifndef WORKSHOP_TOKENISER_H
#define WORKSHOP_TOKENISER_H

#include <string>

// Interface for the workshop tokeniser
namespace Workshop_Tokeniser
{
    // shorthand name for the string type
    typedef std::string string ;

    // the ID used to reference a Token - the implementation is hidden
    typedef int Token ;

    // The kinds of token that are recognised?
    enum TokenKind
    {
        // *** BNF syntax for tokens
        // * literals inside ' '
        // * grouping ( )
        // * ASCII ranges -
        // * alternatives |
        // * 0 or 1 ?
        // * 0 or more *
        // * 1 or more +
        //

        // Workshop Example Language Tokeniser Tokens
        // TOKEN: DEFINITION
        // identifier:      ('a'-'z'|'A'-'Z')('a'-'z'|'A'-'Z'|'0'-'9')*
        // integer:         ('0'-'9')('0'-'9')*
        // relop:           '<' | '<=' | '==' | '!=' | '>' | >='
        // op:              '+' | '-' | '*' | '/'
        // keyword:         'var' | 'while' | 'if' | 'else' | 'let'
        // symbol:          '@' | '{' | '}' | '(' | ')' | ':' | ';' | '=' | '.' | ',' | '"'

        tk_identifier,      // any identifier
        tk_integer,         // any integer

        tk_var,             // 'var'
        tk_while,           // 'while'
        tk_if,              // 'if'
        tk_else,            // 'else'
        tk_let,             // 'let'

        tk_op,              // one of tk_add, tk_sub, tk_times, tk_divide
        tk_add,             // '+'
        tk_sub,             // '-'
        tk_times,           // '*'
        tk_divide,          // '/'

        tk_relop,           // one of tk_lt, tk_le, tk_eq, tk_ne, tk_ge, tk_gt
        tk_lt,              // '<'
        tk_le,              // '<='
        tk_eq,              // '=='
        tk_ne,              // '!='
        tk_ge,              // '>='
        tk_gt,              // '>'

        tk_at,              // '@'
        tk_lcb,             // '{'
        tk_rcb,             // '}'
        tk_lrb,             // '('
        tk_rrb,             // ')'
        tk_colon,           // ':'
        tk_semi,            // ';'
        tk_assign,          // '='
        tk_dot,             // '.'
        tk_comma,           // ','
        tk_dquote,          // '"'


        tk_eoi,            // end of input reached or a legal token cannot be formed
        tk_oops            // for error handling
    } ;

    // ***** the following are implemented in the pre-compiled lib/tokens.o object file *****

    // return a string representation of the given token kind
    extern string token_kind_to_string(TokenKind kind) ;

    // returns the TokenKind that would cause token_kind_to_string to return s
    extern TokenKind string_to_token_kind(string s) ;

    // is the token of the given kind or does it belong to the given grouping?
    extern bool token_is_in(Token token,TokenKind kind_or_grouping) ;

    // create a new Token object and return its ID
    extern Token new_token(TokenKind kind,string spelling) ;

    // return the TokenKind for the given token
    extern TokenKind token_kind(Token token) ;

    // return the characters that make up the given token
    extern string token_spelling(Token token) ;

    // return a string representation of the given token
    extern string token_to_string(Token token) ;

    // the current input character, initiliased to ' ' which we ignore
    // it is an int so that the eof marker is not confused with a legal character
    extern int ch ;

    // read next character if not at the end of input, you must use this to update ch
    extern void nextch() ;

    // ***** the workshop involves implementing the following function by completing tokeniser.cpp *****

    // read the next token from standard input
    extern Token next_token() ;
}

#endif //WORKSHOP_TOKENISER_H
