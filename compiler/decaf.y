%token Y_Void
%token Y_Int
%token Y_Double
%token Y_Bool
%token Y_String
%token Y_Class
%token Y_Interface
%token Y_Null
%token Y_This
%token Y_Extends
%token Y_Implements
%token Y_For
%token Y_While
%token Y_If
%token Y_Else
%token Y_Return
%token Y_Break
%token Y_New
%token Y_NewArray
%token Y_Print
%token Y_ReadInteger
%token Y_ReadLine
%token Y_Identifier
%token Y_TypeIdentifier
%token Y_IntConstant
%token Y_BoolConstant
%token Y_DoubleConstant
%token Y_StringConstant
%token Y_Plus
%token Y_Minus
%token Y_Times
%token Y_Div
%token Y_Mod
%token Y_Less
%token Y_LessEqual
%token Y_Greater
%token Y_GreaterEqual
%token Y_Assign
%token Y_Equal
%token Y_NotEqual
%token Y_And
%token Y_Or
%token Y_Not
%token Y_Semicolon
%token Y_Comma
%token Y_Dot
%token Y_LBracket
%token Y_RBracket
%token Y_LParen
%token Y_RParen
%token Y_LBrace
%token Y_RBrace

%{
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "tokentype.h"
#include "parsetree.h"
#include <stack>

extern ParseTree * top;
extern Token * myTok;


  /* we are building parse trees */
#define YYSTYPE ParseTree *


using namespace std;

stack<Token *> opstack;

void PUSH(){
	opstack.push(myTok);
}


Token* POP(){
	Token *result = opstack.top();
	opstack.pop();
	return result;
}


%}


%nonassoc '='
%left Y_Or
%left Y_And
%nonassoc Y_Equal Y_NotEqual
%nonassoc '<' Y_LessEqual '>' Y_GreaterEqual
%left '+' '-'
%left '*' '/' '%'
%right '!'
%left '[' '.'



%start program

%%

/*
Tokens:
	Tokens Token {
		$1->addChild($2);
		$$ = $1;
	}
	| Token {
		ParseTree *result = new ParseTree("Tokens");
		result->addChild($1);
		top = $$ = result;
	}
	
;


Token: 

	Y_Void { $$ = new ParseTree(myTok);}
	| Y_Int { $$ = new ParseTree(myTok);}
	| Y_Double { $$ = new ParseTree(myTok);}
	| Y_Bool { $$ = new ParseTree(myTok);}
	| Y_String { $$ = new ParseTree(myTok);}
	| Y_Class { $$ = new ParseTree(myTok);}
	| Y_Interface { $$ = new ParseTree(myTok);}
	| Y_Null { $$ = new ParseTree(myTok);}
	| Y_This { $$ = new ParseTree(myTok);}
	| Y_Extends { $$ = new ParseTree(myTok);}
	| Y_Implements { $$ = new ParseTree(myTok);}
	| Y_For { $$ = new ParseTree(myTok);}
	| Y_While { $$ = new ParseTree(myTok);}
	| Y_If { $$ = new ParseTree(myTok);}
	| Y_Else { $$ = new ParseTree(myTok);}
	| Y_Return { $$ = new ParseTree(myTok);}
	| Y_Break { $$ = new ParseTree(myTok);}
	| Y_New { $$ = new ParseTree(myTok);}
	| Y_NewArray { $$ = new ParseTree(myTok);}
	| Y_Print { $$ = new ParseTree(myTok);}
	| Y_ReadInteger { $$ = new ParseTree(myTok);}
	| Y_ReadLine { $$ = new ParseTree(myTok);}
	| Y_Identifier { $$ = new ParseTree(myTok);}
	| Y_TypeIdentifier { $$ = new ParseTree(myTok);}
	| Y_IntConstant { $$ = new ParseTree(myTok);}
	| Y_BoolConstant { $$ = new ParseTree(myTok);}
	| Y_DoubleConstant { $$ = new ParseTree(myTok);}
	| Y_StringConstant { $$ = new ParseTree(myTok);}
	| '+' { $$ = new ParseTree(myTok);}
	| '-' { $$ = new ParseTree(myTok);}
	| '*' { $$ = new ParseTree(myTok);}
	| '/' { $$ = new ParseTree(myTok);}
	| '%' { $$ = new ParseTree(myTok);}
	| '<' { $$ = new ParseTree(myTok);}
	| Y_LessEqual { $$ = new ParseTree(myTok);}
	| '>' { $$ = new ParseTree(myTok);}
	| Y_GreaterEqual { $$ = new ParseTree(myTok);}
	| '=' { $$ = new ParseTree(myTok);}
	| Y_Equal { $$ = new ParseTree(myTok);}
	| Y_NotEqual { $$ = new ParseTree(myTok);}
	| Y_And { $$ = new ParseTree(myTok);}
	| Y_Or { $$ = new ParseTree(myTok);}
	| '!' { $$ = new ParseTree(myTok);}
	| ';' { $$ = new ParseTree(myTok);}
	| ',' { $$ = new ParseTree(myTok);}
	| '.' { $$ = new ParseTree(myTok);}
	| '[' { $$ = new ParseTree(myTok);}
	| ']' { $$ = new ParseTree(myTok);}
	| '(' { $$ = new ParseTree(myTok);}
	| ')' { $$ = new ParseTree(myTok);}
	| '{' { $$ = new ParseTree(myTok);}
	| '}' { $$ = new ParseTree(myTok);}
	
;
*/
program:
	decls {
		ParseTree *result = new ParseTree("START PROGRAM");
		result->addChild($1);
		top = $$ = result;
	}
;



decls:
	decls decl {
		$1->addChild($2);
		$$ = $1;
	} 
	| decl {
		ParseTree *result = new ParseTree("==== DECLARATIONS ====");
		result->addChild($1);
		top = $$ = result;
	}
;

decl:
	variable ';' {$$ = $1;}
	| functionDecl {$$ = $1;}
	| classDecl {$$ = $1;}
	| interfaceDecl {$$ = $1;}
;

interfaceDecl:
	Y_Interface {PUSH();} identifier '{' nprototypes '}' {
		ParseTree *result = new ParseTree("==== INTERFACE ====");
		result->addChild(new ParseTree(POP()));
		result->addChild($3);
		result->addChild($5);
		top = $$ = result;
	}
;

nprototypes:
	prototypes {$$ = $1;}
	| {$$ = NULL;}
;
prototypes:
	prototypes prototype {
		$1->addChild($2);
		$$ = $1;
	}
	| prototype	{
		ParseTree *result = new ParseTree("==== PROTOTYPES ====");
		result->addChild($1);
		top = $$ = result;
	}
;

prototype:
	type identifier '(' formals ')' ';' {
		ParseTree *result = new ParseTree("PROTOTYPE");
		result->addChild($1);
		result->addChild($2);
		result->addChild($4);
		top = $$ = result;
	}
	| void identifier '(' formals ')' ';' {
		ParseTree *result = new ParseTree("PROTOTYPE");
		result->addChild($1);
		result->addChild($2);
		result->addChild($4);
		top = $$ = result;
	}
;
	

nvariableDecls:
	variableDecls {$$ = $1;}
	| {$$ = NULL;}
;

variableDecls:
	variableDecls variable ';' {
		$1->addChild($2);
		$$ = $1;
	}
	| variable ';' {
		ParseTree *result = new ParseTree("==== VARIABLE DECLARATIONS ====");
		result->addChild($1);
		top = $$ = result;
	}
;

variable:
	type identifier {
		ParseTree *result = new ParseTree("VARIABLE");
		result->addChild($1);
		result->addChild($2);
		top = $$ = result;
	}

;


type:

	Y_Int {$$ = new ParseTree(myTok);}
	| Y_Double {$$ = new ParseTree(myTok);}
	| Y_Bool {$$ = new ParseTree(myTok);}
	| Y_String {$$ = new ParseTree(myTok);}
	| Y_TypeIdentifier {$$ = new ParseTree(myTok);}
	| type '[' ']' {
		ParseTree *result = new ParseTree("ARRAY:");
		result->addChild($1);
		top = $$ = result;
	}

;

functionDecl:
	type identifier '(' formals ')' stmtBlock {
		ParseTree *result = new ParseTree("==== FUNCTION ====");
		result->addChild($1);
		result->addChild($2);
		result->addChild($4);
		result->addChild($6);
		top = $$ = result;
	}
	
	| void identifier '(' formals ')' stmtBlock {
		ParseTree *result = new ParseTree("==== FUNCTION ====");
		result->addChild($1);
		result->addChild($2);
		result->addChild($4);
		result->addChild($6);
		top = $$ = result;
	}
;



classDecl:
	Y_Class {PUSH();} identifier extends_ident implements_ident  '{' nfields '}' {
		ParseTree *result = new ParseTree("==== CLASS ====");
		result->addChild(new ParseTree(POP()));
		result->addChild($3);
		result->addChild($4);
		result->addChild($5);
		result->addChild($7);
		top = $$ = result;
	}
;
extends_ident:
	Y_Extends {PUSH();} identifier {
		ParseTree *result = new ParseTree("EXTENDS");
		result->addChild(new ParseTree(POP()));
		result->addChild($3);
		top = $$ = result;
	}
	| {$$ = NULL;}
;
implements_ident:
	Y_Implements {PUSH();} identifiers {
		ParseTree *result = new ParseTree("IMPLEMENTS");
		result->addChild(new ParseTree(POP()));
		result->addChild($3);
		top = $$ = result;
	}
	| {$$ = NULL;}
;
nfields:
	fields {$$ = $1;}
	| {$$ = NULL;}
;
fields:
	fields field {
		$1->addChild($2);
		$$ = $1;
	}
	| field {
		ParseTree *result = new ParseTree("==== FIELDS ====");
		result->addChild($1);
		top = $$ = result;
	}
;
field:
	variable ';'	{$$ = $1;}
	| functionDecl {$$ = $1;}
;
identifiers:
	identifiers ',' identifier {
		$1->addChild($3);
		$$ = $1;
	}
	| identifier {
		ParseTree *result = new ParseTree("==== IDENTIFIERS ====");
		result->addChild($1);
		top = $$ = result;
	}
;




formals:
	formals ',' variable {
		$1->addChild($3);
		$$ = $1;
	}
	| variable {
		ParseTree *result = new ParseTree("==== FORMALS ====");
		result->addChild($1);
		top = $$ = result;
	}
	| {$$ = NULL;}
;	


stmtBlock:
	'{' nvariableDecls nstmts '}' { 
		ParseTree *result = new ParseTree("STATEMENT BLOCK");
		result->addChild($2);
		result->addChild($3);
		top = $$ = result;
	}
;

nstmts:
	stmts {$$ = $1;}
	| {$$ = NULL;}
;
	

stmts:
	stmts stmt {
		$1->addChild($2);
		$$ = $1;
	}
	| stmt {
		ParseTree *result = new ParseTree("==== STATEMENTS ====");
		result->addChild($1);
		top = $$ = result;
	}

;

returnStmt:
	Y_Return {PUSH();} nexpr ';' {
		ParseTree *result = new ParseTree("RETURN");
		result->addChild(new ParseTree(POP()));
		result->addChild($3);
		top = $$ = result;
	}
;

printStmt:
	Y_Print {PUSH();} '(' exprs ')' ';' {
		ParseTree *result = new ParseTree("PRINT");
		result->addChild(new ParseTree(POP()));
		result->addChild($4);
		top = $$ = result;
	}
;



stmt:
	matched_stmt{$$ = $1;}
	| open_stmt {$$ = $1;}
;

other_stmt:	 
	breakStmt ';' {$$ = $1;}
	| nexpr ';' {$$ = $1;}
	| returnStmt {$$ = $1;}
	| printStmt	{$$ = $1;}
	| stmtBlock	{$$ = $1;}
;


matched_stmt:
	other_stmt {$$ = $1;}
	| matched_if {$$ = $1;}
	| matched_while {$$ = $1;}
	| matched_for {$$ = $1;}

;

open_stmt:
	open_if {$$ = $1;} 
	| open_while {$$ = $1;}
	| open_for {$$ = $1;}
;


commonIf: 
	Y_If {PUSH();} '(' expr ')' { $$ = $4;}
;


commonWhile:
	Y_While {PUSH();} '(' expr ')' { $$ = $4;}
;
commonFor:
	Y_For {PUSH();} '(' nexpr ';' expr ';' nexpr ')' { 
		ParseTree *result = new ParseTree("(expr?; expr; expr?)");
		result->addChild($4);
		result->addChild($6);
		result->addChild($8);
		top = $$ = result;
	}
;


common_matched_else:
	commonIf matched_stmt Y_Else {
		PUSH();
		ParseTree *result = new ParseTree("condition + statement");
		result->addChild($1);
		result->addChild($2);
		top = $$ = result;
	}
;

matched_if: 
	common_matched_else matched_stmt {
		ParseTree *result = new ParseTree("STATEMENT: if/else");
		Token* a_else = POP();
		Token* a_if = POP();
		result->addChild(new ParseTree(a_if));
		result->addChild($1);
		result->addChild(new ParseTree(a_else));
		result->addChild($2);
		top = $$ = result;
	}
;

matched_while:
	commonWhile matched_stmt {
		ParseTree *result = new ParseTree("STATEMENT: while");
		result->addChild(new ParseTree(POP()));
		result->addChild($1);
		result->addChild($2);
		top = $$ = result;
	}
;
matched_for:
	commonFor matched_stmt {
		ParseTree *result = new ParseTree("STATEMENT: for");
		result->addChild(new ParseTree(POP()));
		result->addChild($1);
		result->addChild($2);
		top = $$ = result;
	}
;


open_if:
	commonIf stmt {
		ParseTree *result = new ParseTree("STATEMENT: if");
		result->addChild(new ParseTree(POP()));
		result->addChild($1);
		result->addChild($2);
		top = $$ = result;
	} 
	| common_matched_else open_stmt {
		ParseTree *result = new ParseTree("STATEMENT: if/else");
		Token* a_else = POP();
		Token* a_if = POP();
		result->addChild(new ParseTree(a_if));
		result->addChild($1);
		result->addChild(new ParseTree(a_else));
		result->addChild($2);
		top = $$ = result;
	}
;


open_while:
	commonWhile open_stmt {
		ParseTree *result = new ParseTree("STATEMENT: while");
		result->addChild(new ParseTree(POP()));
		result->addChild($1);
		result->addChild($2);
		top = $$ = result;
	}
;
open_for:
	commonFor open_stmt {
		ParseTree *result = new ParseTree("STATEMENT: for");
		result->addChild(new ParseTree(POP()));
		result->addChild($1);
		result->addChild($2);
		top = $$ = result;
	}
;



constant:
	Y_IntConstant {$$ = new ParseTree(myTok);}
	| Y_DoubleConstant {$$ = new ParseTree(myTok);}
	| Y_BoolConstant {$$ = new ParseTree(myTok);}
	| Y_StringConstant{$$ = new ParseTree(myTok);}
	| Y_Null {$$ = new ParseTree(myTok);}
;




nexpr:
	expr {$$ = $1;}
	| {$$ = NULL;}
;

expr: 
	constant							{$$ = $1;}
	| lvalue '=' {PUSH();} expr			{
		ParseTree *result = new ParseTree("bexpr: lvalue = expr");
		result->addChild($1);
		result->addChild(new ParseTree(POP()));
		result->addChild($4);
		top = $$ = result;
	}
	| lvalue 							{$$ = $1;}
	| Y_This 							{$$ = new ParseTree(myTok);}
	| call 								{$$ = $1;}
	| expr '+' {PUSH();} expr				{
		ParseTree *result = new ParseTree("bexpr: +");
		result->addChild($1);
		result->addChild(new ParseTree(POP()));
		result->addChild($4);
		top = $$ = result;
	}
	| expr '-' {PUSH();} expr 			{
		ParseTree *result = new ParseTree("bexpr: -");
		result->addChild($1);
		result->addChild(new ParseTree(POP()));
		result->addChild($4);
		top = $$ = result;
	}
	| expr '*' {PUSH();} expr 			{
		ParseTree *result = new ParseTree("bexpr: *");
		result->addChild($1);
		result->addChild(new ParseTree(POP()));
		result->addChild($4);
		top = $$ = result;	
	}
	| expr '/' {PUSH();} expr 			{
		ParseTree *result = new ParseTree("bexpr: /");
		result->addChild($1);
		result->addChild(new ParseTree(POP()));
		result->addChild($4);
		top = $$ = result;
	}
	| expr '%' {PUSH();} expr 			{
		ParseTree *result = new ParseTree("bexpr: %");
		result->addChild($1);
		result->addChild(new ParseTree(POP()));
		result->addChild($4);
		top = $$ = result;
	}
	| expr '<' {PUSH();} expr 			{
		ParseTree *result = new ParseTree("bexpr: <");
		result->addChild($1);
		result->addChild(new ParseTree(POP()));
		result->addChild($4);
		top = $$ = result;
	}
	| expr '>' {PUSH();} expr 			{
		ParseTree *result = new ParseTree("bexpr: >");
		result->addChild($1);
		result->addChild(new ParseTree(POP()));
		result->addChild($4);
		top = $$ = result;
	}
	| expr Y_LessEqual {PUSH();} expr 			{
		ParseTree *result = new ParseTree("bexpr: <=");
		result->addChild($1);
		result->addChild(new ParseTree(POP()));
		result->addChild($4);
		top = $$ = result;
	}
	| expr Y_Equal {PUSH();} expr 			{
		ParseTree *result = new ParseTree("bexpr: ==");
		result->addChild($1);
		result->addChild(new ParseTree(POP()));
		result->addChild($4);
		top = $$ = result;
	}
	| expr Y_GreaterEqual {PUSH();} expr 			{
		ParseTree *result = new ParseTree("bexpr: >=");
		result->addChild($1);
		result->addChild(new ParseTree(POP()));
		result->addChild($4);
		top = $$ = result;
	}
	| expr Y_NotEqual {PUSH();} expr 			{
		ParseTree *result = new ParseTree("bexpr: !=");
		result->addChild($1);
		result->addChild(new ParseTree(POP()));
		result->addChild($4);
		top = $$ = result;
	}
	| expr Y_And {PUSH();} expr 			{
		ParseTree *result = new ParseTree("bexpr: &&");
		result->addChild($1);
		result->addChild(new ParseTree(POP()));
		result->addChild($4);
		top = $$ = result;
	}
	| expr Y_Or {PUSH();} expr 			{
		ParseTree *result = new ParseTree("bexpr: ||");
		result->addChild($1);
		result->addChild(new ParseTree(POP()));
		result->addChild($4);
		top = $$ = result;
	}
	| '(' expr ')'  					{
		//ParseTree *result = new ParseTree("expr: (expr)");
		//result->addChild($2);
		//top = $$ = result;
		$$ = $2;
	}
	| '-' {PUSH();} expr 				{
		ParseTree *result = new ParseTree("expr: -expr");
		result->addChild(new ParseTree(POP()));
		result->addChild($3);
		top = $$ = result;
	}
	| '!' {PUSH();} expr 				{
		ParseTree *result = new ParseTree("expr: !expr");
		result->addChild(new ParseTree(POP()));
		result->addChild($3);
		top = $$ = result;
	}
	| Y_ReadInteger {PUSH();} '(' ')'				{
		ParseTree *result = new ParseTree("ReadInteger()");
		result->addChild(new ParseTree(POP()));
		top = $$ = result;
	}
	| Y_ReadLine {PUSH();} '(' ')'				{
		ParseTree *result = new ParseTree("ReadLine()");
		result->addChild(new ParseTree(POP()));
		top = $$ = result;
	}
	
	| Y_New {PUSH();} '(' identifier ')'				{
		ParseTree *result = new ParseTree("New(ident)");
		result->addChild(new ParseTree(POP()));
		result->addChild($4);
		top = $$ = result;
	}
	| Y_NewArray {PUSH();} '(' expr ',' type ')'				{
		ParseTree *result = new ParseTree("NewArray(expr, type)");
		result->addChild(new ParseTree(POP()));
		result->addChild($4);
		result->addChild($6);
		top = $$ = result;
		
	}
;

lvalue:
	identifier {$$ = $1;}	
	| dot {$$ = $1;}
	| expr '[' expr ']' {
		ParseTree *result = new ParseTree("ARRAY: expr[expr]");
		result->addChild($1);
		result->addChild($3);
		top = $$ = result;
	} 
;


dot: 
	expr '.' identifier {
		ParseTree *result = new ParseTree("DOT");
		result->addChild($1);
		result->addChild($3);
		top = $$ = result;
	}
;


call:
	dot '(' actuals ')' {
		ParseTree *result = new ParseTree("CALL: expr.ident(exprs)");
		result->addChild($1);
		result->addChild($3);
		top = $$ = result;
	}
	| identifier '(' actuals ')' {
		ParseTree *result = new ParseTree("CALL: ident(exprs)");
		result->addChild($1);
		result->addChild($3);
		top = $$ = result;
	}
;
 

actuals: 
	exprs {$$ = $1;}
	| {$$ = NULL;}

exprs:
	exprs ',' expr {
		$1->addChild($3);
		$$ = $1;
	}
	| expr {
		ParseTree *result = new ParseTree("==== EXPRESSIONS ====");
		result->addChild($1);
		top = $$ = result;
	}
;	



	
identifier: Y_Identifier { $$ = new ParseTree(myTok);};
void: Y_Void { $$ = new ParseTree(myTok);};
breakStmt: Y_Break {$$ = new ParseTree(myTok);};


%%

int yyerror(const char * s)
{
  fprintf(stderr, "%s\n", s);
  return 0;
}

/*
int main() {

  yyparse();
  traverseTree(top, 0, 0);
  return 0;
}
*/