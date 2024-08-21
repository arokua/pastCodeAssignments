// a skeleton implementation of a tokeniser

#include "tokeniser.h"
#include <iostream>
#include <ctype.h>
#include <string>
#include <vector>
// to shorten the code
using namespace std;

namespace Assignment_Tokeniser
{

    // is the token of the given kind or does it belong to the given grouping?
    bool is_keyword(Token token) {
        //Return true if the token kind belongs to tk_keyword, else false
        //The kind of the token
        TokenKind kind = token_kind(token);

        if (kind == tk_if    or
            kind == tk_while or
            kind == tk_else  or
            kind == tk_class or
            kind == tk_int   ){
            return true;
        }
        return false;
    }

    bool is_symbol(Token token) {
        //Return true if the token kind belongs to tk_symbol, else false
        //The kind of the token
        TokenKind kind = token_kind(token);

        if (kind == tk_at   or  kind == tk_semi       or kind == tk_colon or
            kind == tk_not  or  kind == tk_comma      or kind == tk_stop  or
            kind == tk_eq   or  kind == tk_spaceship  or kind == tk_rcb   or
            kind == tk_lcb  or  kind == tk_rrb        or kind == tk_lrb   or
            kind == tk_rsb  or  kind == tk_lsb        or kind == tk_div)
        {
            return true;
        }
        return false;
    }
    bool token_is_in(Token token,TokenKind kind_or_grouping)
    {
        TokenKind kind = token_kind(token) ;

        // check identity first
        if ( kind == kind_or_grouping ) return true ;

        switch(kind_or_grouping)
        {
            case tk_keyword: return is_keyword(token);
            case tk_symbol: return is_symbol(token);
            default:
                return false ;
        }
    }

    // the current input character, initiliased to ' ' which we ignore
    // it is an int so that the EOF marker is not confused with a legal character
    static int ch = ' ' ;

    // the current line number and column, initialised to line 1 column 0
    static int line_num = 1 ;
    static int column_num = 0 ;
    // Store all the lines that have been added in
    static vector<string> allLines; //First line is empty
    //Keep track of nearest two lines before current. Would have use vector if not because {vectorname}[-2] return seg fault in this program
    static string previous_line ="";
    static string beforePreviousLine = "";
    //Currrent line that is having the token
    static string current_line = "";
    // the line number and column for the first character in the current token
    static int start_line = 0 ;
    static int start_column = 0 ;
    //The line after the line contains the token for token_context
    static string afterToken = "    ";
    //The beginning line number of adhoc comment
    static int startComt = 1;
    //Final character of currentline
    static char c = current_line[-1];
    // generate a context string for the given token
    // it shows the line before the token,
    // the line containing the token, and
    // a line with a ^ marking the token's position
    // tab stops are every 8 characters
    // in the context string, tabs are replaced by spaces (1 to 8)
    // so that the next character starts on an 8 character boundary
    string token_context(Token token)
    {   
        string context_string = " ";
        if (line_num < 2){
            //There is only one text line to display
            context_string += "1: " + current_line;
            if (context_string.back() != '\n'){
                context_string += '\n' ;
            }
        }
        else{
            //Make a seperate case for adhoc comment
            if (token_kind(token) == tk_adhoc_comment){
                startComt = token_line(token);
                //Get the correct current line
                if (line_num > startComt){                   

                    if(previous_line.back() != '\n') {
                        context_string += to_string(startComt - 1) + ": " + beforePreviousLine + " " + to_string(startComt) + ": " + previous_line + '\n';
                    }
                    else{
                        context_string += to_string(startComt - 1) + ": " + beforePreviousLine + " " + to_string(startComt) + ": " + previous_line;
                    }
                }

                else{
                    if(current_line.back() != '\n') {
                        context_string += to_string(startComt - 1) + ": " + previous_line + " " + to_string(startComt) + ": " + current_line + '\n';
                    }
                    else{
                        context_string += to_string(startComt - 1) + ": " + previous_line + " " + to_string(startComt) + ": " + current_line;
                    }
                }
            }else {
                if(current_line.back() != '\n') {
                    context_string += to_string(line_num - 1) + ": " + previous_line + " " + to_string(start_line) + ": " + current_line + '\n';
                }
                else{
                    context_string += to_string(line_num - 1) + ": " + previous_line + " " + to_string(start_line) + ": " + current_line;
                }
            }
        
        }
        int lineNolength = to_string(line_num).length(); // Number of digits of the line number
        for (int i = 0; i < lineNolength + column_num + current_line.length(); i++){
            afterToken += " ";
        }
        //Add the modified string to the context_string
        context_string += afterToken.substr(0, token_column(token) + 2 + lineNolength) + '^' + '\n';
        return context_string ;
    }

    // read next character if not at the end of input
    // and update the line and column numbers
    static void nextch()
    {
        extern int read_char() ;

        if ( ch == EOF ) return ;

        if ( ch == '\n' )           // if last ch was newline ...
        {
            line_num++ ;            // increment line number
            column_num = 0 ;        // reset column number
            beforePreviousLine = previous_line;
            previous_line = current_line;
            allLines.push_back(current_line); //Add the current line to storage
            current_line = "";              // And the new line is a blank one at first
            afterToken = "    ";
        }

        ch = getchar() ;            // read the next character from stdin
        if (ch == '\t'){
            //Deal with tabs instead of spaces
            int spaces_inc;
            if (column_num % 8 == 0 ){
                spaces_inc = 8;
                column_num += spaces_inc;
            }else {
                spaces_inc = column_num % 8;
                column_num += spaces_inc;
            }
            for (int i = 0; i < spaces_inc; i++){
                current_line += ' ';
            }
        }else {
            //normal spaces
            column_num++ ;              // increment the column number
        }
        if (ch != '\r' and ch != '\t') {
            //ignore carriage return
            current_line += ch;         //Update current line
        }
        
    }

    ////////////////////////////////////////////////////////////////////////

    // called when we find end of input or we have a bad token
    Token parse_eoi()
    {
        // simulate end of input in case this is handling a bad token rather than a real end of input
        ch = EOF ;

        // return an eoi token
        return new_token(tk_eoi,"",start_line,start_column) ;
    }
    static Token eq(){
        //Is equal to case
        // read next character
        nextch();
        if (ch == '='){
            // a new token
            return new_token(tk_eq,"==",start_line,start_column);
        }
        // invalid character
        return parse_eoi();
    }

    static Token SpaceShip(){
        //tk_spaceship case
        //parse to character
        char c = char(ch);
        //error string
        string err = "" + c;
        //read next char
        nextch();
        err += ch;
        if (ch == '='){
            //Read next char again, since this is a 3 characters token
            nextch();
            err += ch;
            if (ch == '>'){
                //return a spaceship token
                return new_token(tk_spaceship, "<=>",start_line,start_column);
            }
            return new_token(tk_oops, err, start_line, start_column);
        }
        //invalid char
        return new_token(tk_oops, err, start_line, start_column);
    }
    static Token commentOrDiv(){
        // handles 3 tokens, comments and divide
        // read the next char to check cases
        nextch();
        if (ch == '/'){
            //eol comment
            string spelling = "";
            int currentLine = start_line;
            nextch();
            do {
                spelling += ch;
                nextch();
            } while (ch != '\n');
            return new_token(tk_eol_comment, spelling, currentLine, start_column) ;
        }else if (ch == '*'){
            //adhoc
            string spelling = "";
            nextch();
            do {
                if (ch == '*'){
                    nextch();
                    if (ch == '/'){
                        nextch();
                        //nextch();
                        return new_token(tk_adhoc_comment, spelling, start_line, start_column) ;
                    }
                    else{
                        spelling = spelling + '*';
                    }
                }
                spelling += ch;
                nextch();
            } while (true);
            
        }else{
            return new_token(tk_div, "/", start_line, start_column) ;
        }
    }

    static Token parse_symbol(TokenKind kind)
    {   // taken from workshop 5 with some small adjustments
        // first record the spelling
        string spelling = string(1,ch); 

        // read the next characters
        nextch() ;

        // return a new Token object
        return new_token(kind, spelling, start_line, start_column) ;
    }

    static Token parse_identifier()
    {   
        string spelling = "" ;

        do
        {
            spelling += ch ;            
            nextch();
        } while ( isalpha(ch) or isdigit(ch) or ch == '_' or ch == '$') ;
        // return a new Token object
        //Check if the spelling recieved is a keyword
        TokenKind tkk = string_to_token_kind(spelling);
        //If it is a keywrod then return the apporitae spelling
        if (7 < tkk < 13){
            if (spelling == "if"){
                return new_token(tk_if, "if", start_line, start_column);
            }

            if (spelling == "else"){
                return new_token(tk_else, "else", start_line, start_column);
            }

            if (spelling == "while"){
                return new_token(tk_while, "while", start_line, start_column);
            }

            if (spelling == "class"){
                return new_token(tk_class, "class", start_line, start_column);
            }

            if (spelling == "int"){
                return new_token(tk_int, "int", start_line, start_column);
            }
        }
        //If it is not a keyword
        return new_token(tk_identifier, spelling, start_line, start_column) ;
    }

    static Token parse_string(){
        string spelling = "" ;
        nextch();
        do
        {   
            //A string can contains almost all characters in it except '"'
            if (ch == '"'){
                nextch();
                break;
            }else{
                spelling += ch ;            
                nextch() ;
            }
        } while ( true) ;
        return new_token(tk_string, spelling, start_line, start_column);
    }
    static Token parse_number()
    {
        string spelling = "" ;
        bool isDouble = false;
        //These next two bools are two make sure there are no cases such as 3.2+e12e to be accepted as doubles
        bool hasE = false;
        bool hasaP = false; // has a '+'
        bool hasaM = false; // has a '-'
        // append digits to spelling until we read past the end of the integer
        do
        {
            //In case the input is 000
            if (ch == '0'){
                spelling += '0';
                nextch();
                if (ch == '0'){
                    if (spelling.length() == 1){
                        break;
                    }
                }
            }
            // Meet a dot first time
            if (!isdigit(ch)){
                if (ch == '.'){
                    if(isDouble == false){
                        isDouble = true;
                        spelling += '.';
                        nextch();
                        if (!isdigit(ch)){
                            return parse_eoi();
                        }
                    }
                    else{
                        break;
                    }
                }//Expotential number
                else if (ch == 'e' or ch == 'E'){
                    if (spelling.at( int(spelling.length()) - 1 ) == '.'){
                        return parse_eoi();
                    }
                    if ( !hasE){
                        isDouble = true;
                        hasE = true;
                        spelling += 'e';
                        nextch();
                        //Signs
                        if ( ch == '+'){
                            if (!hasaP and !hasaM){
                                hasaP = true;
                                spelling += '+';
                                nextch();
                                if (!isdigit(ch)){
                                    return parse_eoi();
                                }
                            }
                        }
                        else if ( ch == '-'){
                            if (!hasaP and !hasaM){
                                hasaM = true;
                                spelling += '-';
                                nextch();
                                if (!isdigit(ch)){
                                    return parse_eoi();
                                }
                            }
                        }
                        else if (isdigit(ch)){
                            spelling += '+';
                            spelling += ch;
                            nextch();
                        }
                    }else{
                        break;
                    }
                }
                else{
                    break;
                }
            }
            else{
                spelling += ch ;
                nextch() ;
            }
        } while ( true) ;


        // return a new Token object
        if (isDouble){
            return new_token(tk_double, spelling, start_line, start_column) ;
        }else{
            return new_token(tk_integer, spelling, start_line, start_column) ;
        }
    }

    // return the next token object by reading more of the input
    Token next_token()
    {
        // you must read input using the nextch() function
        // the last character read is in the static variable ch
        // always read one character past the end of the token being returned

        // this loop reads one character at a time until it reaches end of input
        while ( ch != EOF )
        {
            start_line = line_num ;                 // remember current position in case we find a token
            start_column = column_num ;
            switch(ch)                              // ch is always the next char to read
            {
            case ' ':                               // ignore space, tab, CR and LF
            case '\t': 
            case '\r':
            case '\n':
                nextch() ;                          // read one more character and try again
                                                    // add additional case labels here for characters that can start tokens
                                                    // call a parse_* function to complete and return each kind of token
                break ;
            //comments and singular characters
            case '!': return parse_symbol(tk_not);
            case '@': return parse_symbol(tk_at);
            case ';': return parse_symbol(tk_semi);
            case ':': return parse_symbol(tk_colon);            
            case '.': return parse_symbol(tk_stop);
            case ',': return parse_symbol(tk_comma);
            case '=': return eq();
            case '(': return parse_symbol(tk_lrb);
            case ')': return parse_symbol(tk_rrb);
            case '[': return parse_symbol(tk_lsb);
            case ']': return parse_symbol(tk_rsb);
            case '{': return parse_symbol(tk_lcb);
            case '}': return parse_symbol(tk_rcb);
            case '<': return SpaceShip();
            case '/': return commentOrDiv();
            case '-':return parse_eoi();

            //alphabet characters and digits
            case 'a'...'z': return parse_identifier();
            case 'A'...'Z': return parse_identifier();
            case '0'...'9': return parse_number();
            case '"': return parse_string();
            default:
                return parse_eoi() ;                // the next character cannot start a token, return an EOI token
            }
        }

        start_line = line_num ;                     // remember current position so EOI token is correct
        start_column = column_num ;

        return parse_eoi() ;                         // return an EOI token
    }
}