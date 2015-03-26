  /* definitions */

keyword   void|int|double|bool|string|class|interface|null|this|extends|implements|for|while|if|else|return|break|New|NewArray|Print|ReadInteger|ReadLine


idstart [A-Za-z]
idbody [A-Za-z0-9_]
tidtrail [[:space:]]*\[[[:space:]]*\]|[[:space:]]+{idstart}{idbody}*
   
%{

#include <iostream>

using namespace std;

#include "tokentype.h"

string resultString;
int lineNo;
Token* myTok;

int error(string msg, int line)
{
  cout << msg << " on line " << line << endl;
  return -1;
}

TokenType makeToken(TokenType type) {
    myTok = new Token(type, yytext, yylineno);
    return type;
}


%}

%option yylineno
%x STRING
%x COMMENT
%x BLOCK
%x DOUBLE

%%

  /* =================== rules ===================== */

  /* other */

\+ { makeToken(Y_Plus); return '+'; }
\- { makeToken(Y_Minus); return '-';}
\* { makeToken(Y_Times); return '*'; }
\/ { makeToken(Y_Div); return '/';}
\% { makeToken(Y_Mod); return '%';}
\< { makeToken(Y_Less); return '<';}
\<\= {return makeToken(Y_LessEqual);}
\> { makeToken(Y_Greater); return '>';}
\>\= {return makeToken(Y_GreaterEqual);}
\= { makeToken(Y_Assign); return '=';}
\=\= { return makeToken(Y_Equal); }
\!\= { return makeToken(Y_NotEqual); }
\&\& { return makeToken(Y_And); }
\|\| { return makeToken(Y_Or); }
\! { makeToken(Y_Not); return '!';}
\; { makeToken(Y_Semicolon); return ';';}
\, { makeToken(Y_Comma); return ',';}
\. { makeToken(Y_Dot); return '.';}
\[ { makeToken(Y_LBracket); return '[';}
\] { makeToken(Y_RBracket); return ']';}
\( { makeToken(Y_LParen); return '(';}
\) { makeToken(Y_RParen); return ')';}
\{ { makeToken(Y_LBrace); return '{';}
\} { makeToken(Y_RBrace); return '}';}

  /* keywords */

void/{tidtrail}?  		{ return makeToken(Y_Void); }
int/{tidtrail}? 		{ return makeToken(Y_Int); }
double/{tidtrail}? 		{ return makeToken(Y_Double); }
bool/{tidtrail}? 		{ return makeToken(Y_Bool); }
string/{tidtrail}?		{ return makeToken(Y_String); }
class/{tidtrail}? 		{ return makeToken(Y_Class); }
interface/{tidtrail}?  	{ return makeToken(Y_Interface); }
null/{tidtrail}?		{ return makeToken(Y_Null); }
this/{tidtrail}?  		{ return makeToken(Y_This); }
extends/{tidtrail}?   	{ return makeToken(Y_Extends); }
implements/{tidtrail}?	{ return makeToken(Y_Implements); }
for/{tidtrail}?   		{ return makeToken(Y_For); }
while/{tidtrail}?   	{ return makeToken(Y_While); }
if/{tidtrail}?   		{ return makeToken(Y_If); }
else/{tidtrail}?   		{ return makeToken(Y_Else); }
return/{tidtrail}?  	{ return makeToken(Y_Return); }
break/{tidtrail}?  	 	{ return makeToken(Y_Break); }
New/{tidtrail}?   		{ return makeToken(Y_New); }
NewArray/{tidtrail}? 	{ return makeToken(Y_NewArray); }
Print/{tidtrail}?   	{ return makeToken(Y_Print); }
ReadInteger/{tidtrail}?	{ return makeToken(Y_ReadInteger); }
ReadLine/{tidtrail}? 	{ return makeToken(Y_ReadLine); }

  /* bools */

true  							{ return makeToken(Y_BoolConstant); }
false  							{ return makeToken(Y_BoolConstant); }


  /* ignore whitespace | [[:space:]] */

  /* identifier */
[A-Za-z][A-Za-z0-9_]*/([[:space:]]+{keyword})?		{ 
								resultString = "";
								resultString += yytext;
								if(resultString.length() > 31){
									return error("identifier \"" + resultString + "\" too long", yylineno); 
								}
								return makeToken(Y_Identifier); 
								
							}
							
[A-Za-z][A-Za-z0-9_]*/[[:space:]]+{tidtrail} 		{ 
								resultString = "";
								resultString += yytext;
								if(resultString.length() > 31){
									return error("identifier \"" + resultString + "\" too long", yylineno); 
								}
								return makeToken(Y_TypeIdentifier); 
								
							}




  /* ints */
[0-9]+ 							{ return makeToken(Y_IntConstant); }
0[Xx][0-9A-Fa-f]+ 				{ return makeToken(Y_IntConstant); }

  /* doubles */
  
[0-9]+\.[0-9]*[Ee][+-]?[0-9]+ 	{ return makeToken(Y_DoubleConstant); } 

[0-9]+\.[0-9]* 					{ return makeToken(Y_DoubleConstant); } 





  /* string */


\n {}

\" { BEGIN(STRING); resultString = "\""; }
<STRING>[^\n"]* { resultString += yytext; }
<STRING>\n      {return error("missing \" at end of string constant", 
		yylineno-1); }
<STRING><<EOF>>  {return error("missing \" at end of string constant", 
		yylineno); } 
<STRING>\"     { BEGIN(INITIAL); 
	         myTok = new Token(Y_StringConstant,resultString + "\"", 
                                  yylineno);
		 return Y_StringConstant; }

  /* comments */
  
\/\/ { BEGIN(COMMENT); }
<COMMENT>[^\n]* { }
<COMMENT><<EOF>> { return error("missing new line character before EOF (how does this even happen?)",
		 yylineno); }
<COMMENT>\n  	 { BEGIN(INITIAL);}




\/\* { BEGIN(BLOCK); lineNo = yylineno; }
<BLOCK>\*\/  	 { BEGIN(INITIAL);}
<BLOCK><<EOF>> { return error("missing */ at end of comment block", lineNo); }
<BLOCK>(.|\n) { }




[^ \t\n] { resultString = "stray '"; resultString += yytext; resultString += "'"; return error(resultString, yylineno); }
[ \t\n] {}
                  
<<EOF>> { return -1; }

%%

  /* subroutines */

int yywrap(void) {

    return 1;  // makes it stop at EOF.
} 


