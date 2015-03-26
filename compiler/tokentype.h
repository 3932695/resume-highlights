/* tokentype.h
   Alistair Campbell
   Fall 2014
   CS 310 Compilers

   A "mapping" between token types and their names
   In the future, this file, or one like it, will get 
   Generated automatically.

   Also contains the definition of a Token for purposes of 
   out lexical analysis phase.
*/

#ifndef SCANNER
#define SCANNER

#include <iostream>
#include <cstdlib>

using namespace std;

/* Constants for all 51 types of tokens in Decaf */
enum TokenType {
	
  /* The 22 keywords */
  Y_Void = 257, Y_Int, Y_Double, Y_Bool,
  Y_String, Y_Class, Y_Interface, Y_Null,
  Y_This, Y_Extends, Y_Implements, Y_For,
  Y_While, Y_If, Y_Else, Y_Return,
  Y_Break, Y_New, Y_NewArray, Y_Print,
  Y_ReadInteger, Y_ReadLine,
  /* 1 Identifier */
  Y_Identifier, Y_TypeIdentifier,
  /* The 4 kinds of constants (literals) */
  Y_IntConstant, Y_BoolConstant, Y_DoubleConstant, Y_StringConstant,
  /* The 24 other tokens 
     + - * / % < <= > >= = == != && || ! ; , . [ ] ( ) { } */
  Y_Plus, Y_Minus, Y_Times, Y_Div,
  Y_Mod, Y_Less, Y_LessEqual, Y_Greater,        
  Y_GreaterEqual, Y_Assign, Y_Equal, Y_NotEqual,
  Y_And, Y_Or, Y_Not, Y_Semicolon,
  Y_Comma, Y_Dot, Y_LBracket, Y_RBracket,
  Y_LParen, Y_RParen, Y_LBrace, Y_RBrace
};

/* And their associated names.  Which we will use solely to verify our
   scanner is working. */

static const char *TokenNames[] = {
  /* The 22 keywords */
  "Y_Void", "Y_Int", "Y_Double", "Y_Bool",
  "Y_String", "Y_Class", "Y_Interface", "Y_Null", 
  "Y_This", "Y_Extends", "Y_Implements", "Y_For",
  "Y_While", "Y_If", "Y_Else", "Y_Return", 
  "Y_Break", "Y_New", "Y_NewArray", "Y_Print",
  "Y_ReadInteger", "Y_ReadLine",
  /* 1 Identifier */
  "Y_Identifier", "Y_TypeIdentifier",
  /* The 4 kinds of constants (literals) */
  "Y_IntConstant", "Y_BoolConstant", "Y_DoubleConstant", "Y_StringConstant",
  /* The 24 other tokens 
     + - * / % < <= > >= = == != && || ! ; , . [ ] ( ) { } */
  "Y_Plus", "Y_Minus", "Y_Times", "Y_Div", 
  "Y_Mod", "Y_Less", "Y_LessEqual", "Y_Greater",        
  "Y_GreaterEqual", "Y_Assign", "Y_Equal", "Y_NotEqual",
  "Y_And", "Y_Or", "Y_Not", "Y_Semicolon",
  "Y_Comma", "Y_Dot", "Y_LBracket", "Y_RBracket",
  "Y_LParen", "Y_RParen", "Y_LBrace", "Y_RBrace"
};

/* The struct for tokens for the Decaf lexer assignment */

struct Token {
	
  int type;
  string text;
  int line;
  Token() {} // leave uninitialized
  Token(TokenType type, string text, int line) : type(type), text(text), line(line) {}
  string toString() {
    // convert line to a C string
    char lineStr[200];
    sprintf(lineStr,"%d",line);
    return string(TokenNames[type - 257]) + '(' + text + ',' + lineStr + ')';
  }
  void print() {
    cout << toString() << endl;
  }
};
 
#endif



