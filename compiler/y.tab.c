#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>
#include <string.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20070509

#define YYEMPTY (-1)
#define yyclearin    (yychar = YYEMPTY)
#define yyerrok      (yyerrflag = 0)
#define YYRECOVERING (yyerrflag != 0)

extern int yyparse(void);

static int yygrowstack(void);
#define YYPREFIX "yy"
#line 55 "decaf.y"
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


#line 56 "y.tab.c"
#define Y_Void 257
#define Y_Int 258
#define Y_Double 259
#define Y_Bool 260
#define Y_String 261
#define Y_Class 262
#define Y_Interface 263
#define Y_Null 264
#define Y_This 265
#define Y_Extends 266
#define Y_Implements 267
#define Y_For 268
#define Y_While 269
#define Y_If 270
#define Y_Else 271
#define Y_Return 272
#define Y_Break 273
#define Y_New 274
#define Y_NewArray 275
#define Y_Print 276
#define Y_ReadInteger 277
#define Y_ReadLine 278
#define Y_Identifier 279
#define Y_TypeIdentifier 280
#define Y_IntConstant 281
#define Y_BoolConstant 282
#define Y_DoubleConstant 283
#define Y_StringConstant 284
#define Y_Plus 285
#define Y_Minus 286
#define Y_Times 287
#define Y_Div 288
#define Y_Mod 289
#define Y_Less 290
#define Y_LessEqual 291
#define Y_Greater 292
#define Y_GreaterEqual 293
#define Y_Assign 294
#define Y_Equal 295
#define Y_NotEqual 296
#define Y_And 297
#define Y_Or 298
#define Y_Not 299
#define Y_Semicolon 300
#define Y_Comma 301
#define Y_Dot 302
#define Y_LBracket 303
#define Y_RBracket 304
#define Y_LParen 305
#define Y_RParen 306
#define Y_LBrace 307
#define Y_RBrace 308
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    1,    1,    2,    2,    2,    2,    8,    6,    9,
    9,   10,   10,   11,   11,   15,   15,   16,   16,    3,
   12,   12,   12,   12,   12,   12,    4,    4,   18,    5,
   22,   19,   19,   24,   20,   20,   21,   21,   25,   25,
   26,   26,   23,   23,   13,   13,   13,   17,   27,   27,
   28,   28,   32,   30,   34,   33,   29,   29,   38,   38,
   38,   38,   38,   36,   36,   36,   36,   37,   37,   37,
   47,   46,   50,   49,   52,   51,   53,   40,   41,   42,
   43,   43,   44,   45,   54,   54,   54,   54,   54,   31,
   31,   48,   56,   48,   48,   48,   48,   58,   48,   59,
   48,   60,   48,   61,   48,   62,   48,   63,   48,   64,
   48,   65,   48,   66,   48,   67,   48,   68,   48,   69,
   48,   70,   48,   48,   71,   48,   72,   48,   73,   48,
   74,   48,   75,   48,   76,   48,   55,   55,   55,   77,
   57,   57,   78,   78,   35,   35,    7,   14,   39,
};
short yylen[] = {                                         2,
    1,    2,    1,    2,    1,    1,    1,    0,    6,    1,
    0,    2,    1,    6,    6,    1,    0,    3,    2,    2,
    1,    1,    1,    1,    1,    3,    6,    6,    0,    8,
    0,    3,    0,    0,    3,    0,    1,    0,    2,    1,
    2,    1,    3,    1,    3,    1,    0,    4,    1,    0,
    2,    1,    0,    4,    0,    6,    1,    1,    2,    2,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    0,    5,    0,    5,    0,    9,    3,    2,    2,    2,
    2,    2,    2,    2,    1,    1,    1,    1,    1,    1,
    0,    1,    0,    4,    1,    1,    1,    0,    4,    0,
    4,    0,    4,    0,    4,    0,    4,    0,    4,    0,
    4,    0,    4,    0,    4,    0,    4,    0,    4,    0,
    4,    0,    4,    3,    0,    3,    0,    3,    0,    4,
    0,    4,    0,    5,    0,    7,    1,    1,    4,    3,
    4,    4,    1,    0,    3,    1,    1,    1,    1,
};
short yydefred[] = {                                      0,
  148,   21,   22,   23,   24,   29,    8,   25,    0,    0,
    3,    0,    5,    6,    7,    0,    0,    0,    0,    2,
    4,  147,    0,    0,    0,    0,    0,   26,    0,    0,
   31,    0,    0,   46,    0,    0,    0,    0,   34,    0,
    0,    0,   13,    0,    0,   20,    0,    0,    0,   32,
    0,    0,    9,   12,    0,    0,    0,   27,   45,   28,
   44,    0,    0,   42,    0,    0,   40,    0,    0,    0,
    0,    0,    0,   41,   30,   39,    0,    0,   19,   89,
   96,   75,   73,   71,   53,  149,  133,  135,   55,  129,
  131,   85,   87,   86,   88,  125,  127,    0,    0,   63,
    0,    0,   52,   61,    0,   62,   57,   58,   64,    0,
   65,   66,   67,   68,   69,   70,    0,    0,    0,    0,
    0,   92,    0,   97,    0,    0,   43,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   48,   51,   60,   59,   81,    0,  112,  116,
  114,  118,  120,  122,  108,  110,   98,  100,  102,  104,
  106,    0,    0,   79,   83,   80,   84,   78,   82,   93,
    0,   18,   14,   15,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  124,    0,    0,    0,   77,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  140,    0,    0,    0,    0,    0,
   54,    0,    0,    0,  130,  132,    0,  142,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  139,    0,  141,    0,   74,   72,  134,    0,    0,
    0,    0,    0,   56,    0,  136,    0,   76,
};
short yydgoto[] = {                                       9,
   10,   11,   34,   13,   14,   15,   99,   19,   41,   42,
   43,   35,   36,   17,   71,   72,  100,   18,   32,   40,
   65,   38,   62,   51,   66,   67,  101,  102,  103,  104,
  105,  133,  106,  136,  187,  107,  108,  109,  110,  111,
  112,  113,  114,  115,  116,  117,  132,  118,  119,  131,
  120,  130,  121,  122,  123,  206,  124,  199,  200,  201,
  202,  203,  197,  198,  191,  193,  192,  194,  195,  196,
  139,  140,  137,  138,  134,  135,  125,  189,
};
short yysindex[] = {                                     83,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   83,
    0,  -31,    0,    0,    0,  -90, -250, -250, -250,    0,
    0,    0,  -53,    9,   10, -208,  -57,    0,   90,   90,
    0, -191, -108,    0,  -90,   18,  117, -250,    0,  -35,
  -14, -108,    0,  -90, -250,    0,  -13,   90,  -13,    0,
 -250, -108,    0,    0,   77,   79,   90,    0,    0,    0,
    0,   82,   69,    0,   11, -108,    0,   90,   90,   76,
  611,   90, -250,    0,    0,    0,  143,  166,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  632,  114,    0,
   12,  611,    0,    0,  103,    0,    0,    0,    0,  108,
    0,    0,    0,    0,    0,    0,  611,  337,  611,  611,
  611,    0,   95,    0,  133,  115,    0,  119,  127,  142,
  151,  152,  632,  162,  175,  177,  179,  183,  632,  632,
   97,  632,    0,    0,    0,    0,    0,  -73,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  632, -250,    0,    0,    0,    0,    0,    0,    0,
  632,    0,    0,    0,  632,  632,  632,  147, -250,  632,
  632,  198,  200,  263,  -34,    0,  180,  337,  206,    0,
  632,  632,  632,  632,  632,  632,  632,  632,  632,  632,
  632,  632,  632,  123,    0,  632,  211,  203,  134,  158,
    0,  216,  184,  193,    0,    0,  632,    0,  270,  270,
  511,  511,  423,  397,  270,  270,  263,  263,  -34,  -34,
  -34,    0,  337,    0,  632,    0,    0,    0,   90,  207,
  337,  244,  -38,    0,  632,    0,  232,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  276,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  218,    0, -121,    0,    0,  194,  194,
    0,  140,  153,    0,    0,    0,    0,    0,    0,    0,
    0,  154,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  155,    0,    0,    0,    0,  541,    0,    0,    0,
    0,  159,    0,    0,    0,  168,    0,  194,  194,    0,
  -32,  564,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -37,    0,
    0,  -28,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  224,  -27,  224,  224,
  224,    0,    1,    0,  -26,    0,    0,    0,    0,    0,
    0,    0,  224,    0,    0,    0,    0,    0,    0,    0,
    0,  243,    0,    0,    0,    0,    0,  586,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  243,    0,    0,    0,  224,    0,    0,    0,    0,    0,
    0,    0,    0,  450,   27,    0,  254,  199,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  209,  345,
  104,  149,  192,  472,  365,  404,  458,  485,   36,   62,
   71,    0,  505,    0,    0,    0,    0,    0,    0,    0,
  204,    0,    0,    0,  260,    0,    0,    0,
};
short yygindex[] = {                                      0,
    0,  298,   75,  -15,    0,    0,  544,    0,    0,    0,
  269,  222,   22,   -3,    0,    0,   35,    0,    0,    0,
    0,    0,    0,    0,    0,  248,    0,    0,  -76,    0,
 -120,    0,    0,    0,  138,   92,  -19,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  759,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  150,
};
#define YYTABLESIZE 994
short yytable[] = {                                     137,
   23,   33,  246,  137,  137,  137,  137,  137,  137,  137,
  138,  163,  178,   90,  138,  138,  138,  138,  138,  138,
  138,  137,  137,  137,  137,  144,   91,   21,   22,   45,
   91,   90,  138,  138,  138,  138,   64,   95,   45,   28,
  147,   95,   95,   95,   95,   95,   95,   95,   29,   30,
   64,   37,   23,  137,  208,  137,  162,   31,   47,   95,
   95,   48,   95,  128,  138,   33,  138,  128,  128,  128,
  128,  128,  103,  128,   12,   39,  103,  103,  103,  103,
  103,   58,  103,   60,   12,  128,  128,   52,  128,   77,
   78,   95,   50,   95,  103,  103,   49,  103,  105,  165,
  167,  169,  105,  105,  105,  105,  105,  107,  105,   57,
   53,  107,  107,  107,  107,  107,   68,  107,   69,  128,
  105,  105,   59,  105,  247,   73,   63,   74,  103,  107,
  107,   70,  107,  161,   79,   75,  143,  186,  159,  157,
   63,  158,  163,  160,  115,   33,  126,  115,    1,    2,
    3,    4,    5,  142,  105,  170,  155,   49,  156,  161,
   48,  145,  115,  107,  159,  157,  146,  158,  163,  160,
  161,    8,  171,  172,  236,  159,  157,  173,  158,  163,
  160,  175,  155,  128,  156,  174,   48,  162,   22,  119,
  176,  177,  119,  155,  161,  156,  115,  190,  237,  159,
  157,  179,  158,  163,  160,  211,  129,  119,  148,   48,
  164,  166,  168,  162,  180,  232,  181,  155,  182,  156,
  161,   16,  183,  217,  162,  159,  157,  239,  158,  163,
  160,   16,  121,  240,   47,  121,  217,   47,  215,  146,
  216,  119,  146,  155,  145,  156,  218,  145,  162,  113,
  121,  234,  113,  137,   44,  137,  238,  137,  137,  137,
  137,  235,   36,   44,  138,  244,  138,  113,  138,  138,
  138,  138,  248,   16,  162,    1,   20,   11,   10,   38,
  161,   35,   91,  144,  121,  159,  157,   16,  158,  163,
  160,   95,   37,   95,  143,   95,   95,   95,   95,  161,
   91,  113,  245,  155,  159,  156,  161,   20,  163,  160,
   54,  159,  157,   76,  158,  163,  160,  128,  214,  128,
  207,  128,  128,  128,  128,    0,  103,    0,  103,    0,
  103,  103,  103,  103,  162,    0,    0,    0,    0,    1,
    2,    3,    4,    5,    6,    7,    0,    2,    3,    4,
    5,    0,  105,  162,  105,    0,  105,  105,  105,  105,
  162,  107,    8,  107,    0,  107,  107,  107,  107,    8,
    0,    0,    0,  161,    0,    0,    0,    0,  159,  157,
    0,  158,  163,  160,    0,  117,    0,  149,  117,  150,
    0,  151,  152,  153,  154,    0,  155,    0,  156,    0,
  115,  115,    0,  117,    0,  109,    0,    0,  109,    0,
    0,    0,    0,  149,    0,  150,    0,  151,  152,  153,
  154,    0,    0,  109,  149,    0,  150,  162,  151,  152,
  153,  154,    0,  161,    0,    0,    0,  117,  159,  157,
    0,  158,  163,  160,  111,  119,  119,  111,  149,    0,
  150,    0,  151,  152,  153,  154,  155,  109,  156,  161,
  243,    0,  111,    0,  159,  157,    0,  158,  163,  160,
    0,    0,    0,    0,  149,    0,  150,    0,  151,  152,
  153,  154,  155,    0,  156,    0,    0,  162,  121,  121,
  126,    0,  126,  126,  126,    0,  111,    0,   99,    0,
   99,   99,   99,  113,  113,  113,  113,    0,  126,  126,
    0,  126,  123,  162,    0,  123,   99,   99,    0,   99,
    0,    0,    0,    0,    0,  101,    0,  101,  101,  101,
  123,    0,    0,    0,  149,    0,  150,    0,  151,  152,
  153,  154,  126,  101,  101,   94,  101,  161,   94,    0,
   99,    0,  159,  157,    0,  158,  163,  160,    0,   24,
   25,   26,   27,   94,  123,    0,    0,    0,    0,    0,
  155,    0,  156,   17,    0,    0,    0,  101,   46,    0,
   17,   50,    0,    0,    0,   17,    0,   55,   56,    0,
    0,    0,    0,    0,   61,    0,   16,   94,    0,   17,
    0,  162,    0,   16,    0,    0,    0,    0,   16,    0,
    0,    0,    0,    0,    0,    0,  127,    0,   57,    0,
    0,    0,   16,    0,    0,   57,    0,  149,    0,  150,
   57,  151,  152,  153,  154,    0,    0,    0,    0,  117,
  117,  117,  117,   97,   57,    0,    0,    0,    0,    0,
   98,    0,    0,    0,    0,   96,    0,    0,    0,  109,
  109,  109,  109,   17,   97,   17,    0,    0,    0,    0,
    0,   98,    0,    0,    0,    0,   96,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   16,  149,   16,  150,
    0,  151,  152,  153,    0,    0,    0,    0,  111,  111,
  111,  111,    0,    0,    0,    0,  205,    0,   57,    0,
   57,    0,    0,  149,    0,  150,    0,  151,  152,    0,
    0,    0,  212,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   57,    0,    0,    0,    0,    0,    0,
  126,    0,  126,    0,  126,  126,  126,  126,   99,    0,
   99,    0,   99,   99,   99,   99,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  123,
    0,    0,    0,    0,    0,  101,    0,  101,    0,  101,
  101,  101,  101,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  149,    0,  150,   17,   17,    0,    0,   17,   17,
   17,    0,   17,   17,   17,   17,   17,   17,   17,   17,
    0,   17,   17,   17,   17,    0,    0,   16,   16,    0,
    0,   16,   16,   16,    0,   16,   16,   16,   16,   16,
   16,   16,   16,    0,   16,   16,   16,   16,    0,   57,
   57,    0,    0,   57,   57,   57,  141,   57,   57,   57,
   57,   57,   57,   57,   57,    0,   57,   57,   57,   57,
    0,    0,    0,    0,   80,   81,    0,    0,   82,   83,
   84,    0,   85,   86,   87,   88,   89,   90,   91,   22,
    0,   92,   93,   94,   95,   80,   81,  184,  185,    0,
  188,    0,    0,    0,    0,   87,   88,    0,   90,   91,
   22,    0,   92,   93,   94,   95,    0,    0,    0,    0,
  204,    0,    0,    0,    0,    0,    0,    0,    0,  188,
    0,    0,    0,    0,  209,  210,    0,    0,  213,  188,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  219,
  220,  221,  222,  223,  224,  225,  226,  227,  228,  229,
  230,  231,    0,    0,  233,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  241,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  242,
};
short yycheck[] = {                                      37,
   91,  123,   41,   41,   42,   43,   44,   45,   46,   47,
   37,   46,  133,   41,   41,   42,   43,   44,   45,   46,
   47,   59,   60,   61,   62,  102,   59,   59,  279,   33,
   59,   59,   59,   60,   61,   62,   52,   37,   42,   93,
  117,   41,   42,   43,   44,   45,   46,   47,   40,   40,
   66,   30,   91,   91,  175,   93,   91,  266,   41,   59,
   60,   44,   62,   37,   91,  123,   93,   41,   42,   43,
   44,   45,   37,   47,    0,  267,   41,   42,   43,   44,
   45,   47,   47,   49,   10,   59,   60,  123,   62,   68,
   69,   91,  125,   93,   59,   60,  125,   62,   37,  119,
  120,  121,   41,   42,   43,   44,   45,   37,   47,  123,
  125,   41,   42,   43,   44,   45,   40,   47,   40,   93,
   59,   60,   48,   62,  245,   44,   52,   59,   93,   59,
   60,   57,   62,   37,   59,  125,  125,   41,   42,   43,
   66,   45,   46,   47,   41,  267,   72,   44,  257,  258,
  259,  260,  261,   40,   93,   61,   60,   41,   62,   37,
   44,   59,   59,   93,   42,   43,   59,   45,   46,   47,
   37,  280,   40,   59,   41,   42,   43,   59,   45,   46,
   47,   40,   60,   41,   62,   59,   44,   91,  279,   41,
   40,   40,   44,   60,   37,   62,   93,  271,   41,   42,
   43,   40,   45,   46,   47,   59,   41,   59,  117,   44,
  119,  120,  121,   91,   40,   93,   40,   60,   40,   62,
   37,    0,   40,   44,   91,   42,   43,   44,   45,   46,
   47,   10,   41,   41,   41,   44,   44,   44,   41,   41,
   41,   93,   44,   60,   41,   62,   41,   44,   91,   41,
   59,   41,   44,  291,   33,  293,   41,  295,  296,  297,
  298,   59,  123,   42,  291,   59,  293,   59,  295,  296,
  297,  298,   41,   52,   91,    0,   59,  125,  125,  125,
   37,  123,   59,   41,   93,   42,   43,   66,   45,   46,
   47,  291,  125,  293,   41,  295,  296,  297,  298,   37,
   41,   93,   59,   60,   42,   62,   37,   10,   46,   47,
   42,   42,   43,   66,   45,   46,   47,  291,  181,  293,
  171,  295,  296,  297,  298,   -1,  291,   -1,  293,   -1,
  295,  296,  297,  298,   91,   -1,   -1,   -1,   -1,  257,
  258,  259,  260,  261,  262,  263,   -1,  258,  259,  260,
  261,   -1,  291,   91,  293,   -1,  295,  296,  297,  298,
   91,  291,  280,  293,   -1,  295,  296,  297,  298,  280,
   -1,   -1,   -1,   37,   -1,   -1,   -1,   -1,   42,   43,
   -1,   45,   46,   47,   -1,   41,   -1,  291,   44,  293,
   -1,  295,  296,  297,  298,   -1,   60,   -1,   62,   -1,
  297,  298,   -1,   59,   -1,   41,   -1,   -1,   44,   -1,
   -1,   -1,   -1,  291,   -1,  293,   -1,  295,  296,  297,
  298,   -1,   -1,   59,  291,   -1,  293,   91,  295,  296,
  297,  298,   -1,   37,   -1,   -1,   -1,   93,   42,   43,
   -1,   45,   46,   47,   41,  297,  298,   44,  291,   -1,
  293,   -1,  295,  296,  297,  298,   60,   93,   62,   37,
  239,   -1,   59,   -1,   42,   43,   -1,   45,   46,   47,
   -1,   -1,   -1,   -1,  291,   -1,  293,   -1,  295,  296,
  297,  298,   60,   -1,   62,   -1,   -1,   91,  297,  298,
   41,   -1,   43,   44,   45,   -1,   93,   -1,   41,   -1,
   43,   44,   45,  295,  296,  297,  298,   -1,   59,   60,
   -1,   62,   41,   91,   -1,   44,   59,   60,   -1,   62,
   -1,   -1,   -1,   -1,   -1,   41,   -1,   43,   44,   45,
   59,   -1,   -1,   -1,  291,   -1,  293,   -1,  295,  296,
  297,  298,   93,   59,   60,   41,   62,   37,   44,   -1,
   93,   -1,   42,   43,   -1,   45,   46,   47,   -1,   16,
   17,   18,   19,   59,   93,   -1,   -1,   -1,   -1,   -1,
   60,   -1,   62,   33,   -1,   -1,   -1,   93,   35,   -1,
   40,   38,   -1,   -1,   -1,   45,   -1,   44,   45,   -1,
   -1,   -1,   -1,   -1,   51,   -1,   33,   93,   -1,   59,
   -1,   91,   -1,   40,   -1,   -1,   -1,   -1,   45,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   73,   -1,   33,   -1,
   -1,   -1,   59,   -1,   -1,   40,   -1,  291,   -1,  293,
   45,  295,  296,  297,  298,   -1,   -1,   -1,   -1,  295,
  296,  297,  298,   33,   59,   -1,   -1,   -1,   -1,   -1,
   40,   -1,   -1,   -1,   -1,   45,   -1,   -1,   -1,  295,
  296,  297,  298,  123,   33,  125,   -1,   -1,   -1,   -1,
   -1,   40,   -1,   -1,   -1,   -1,   45,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  123,  291,  125,  293,
   -1,  295,  296,  297,   -1,   -1,   -1,   -1,  295,  296,
  297,  298,   -1,   -1,   -1,   -1,  163,   -1,  123,   -1,
  125,   -1,   -1,  291,   -1,  293,   -1,  295,  296,   -1,
   -1,   -1,  179,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  123,   -1,   -1,   -1,   -1,   -1,   -1,
  291,   -1,  293,   -1,  295,  296,  297,  298,  291,   -1,
  293,   -1,  295,  296,  297,  298,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  298,
   -1,   -1,   -1,   -1,   -1,  291,   -1,  293,   -1,  295,
  296,  297,  298,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  291,   -1,  293,  264,  265,   -1,   -1,  268,  269,
  270,   -1,  272,  273,  274,  275,  276,  277,  278,  279,
   -1,  281,  282,  283,  284,   -1,   -1,  264,  265,   -1,
   -1,  268,  269,  270,   -1,  272,  273,  274,  275,  276,
  277,  278,  279,   -1,  281,  282,  283,  284,   -1,  264,
  265,   -1,   -1,  268,  269,  270,   98,  272,  273,  274,
  275,  276,  277,  278,  279,   -1,  281,  282,  283,  284,
   -1,   -1,   -1,   -1,  264,  265,   -1,   -1,  268,  269,
  270,   -1,  272,  273,  274,  275,  276,  277,  278,  279,
   -1,  281,  282,  283,  284,  264,  265,  139,  140,   -1,
  142,   -1,   -1,   -1,   -1,  274,  275,   -1,  277,  278,
  279,   -1,  281,  282,  283,  284,   -1,   -1,   -1,   -1,
  162,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  171,
   -1,   -1,   -1,   -1,  176,  177,   -1,   -1,  180,  181,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  191,
  192,  193,  194,  195,  196,  197,  198,  199,  200,  201,
  202,  203,   -1,   -1,  206,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  217,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  235,
};
#define YYFINAL 9
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 308
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,"'%'",0,0,"'('","')'","'*'","'+'","','","'-'","'.'","'/'",0,0,0,0,0,
0,0,0,0,0,0,"';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Y_Void","Y_Int","Y_Double","Y_Bool",
"Y_String","Y_Class","Y_Interface","Y_Null","Y_This","Y_Extends","Y_Implements",
"Y_For","Y_While","Y_If","Y_Else","Y_Return","Y_Break","Y_New","Y_NewArray",
"Y_Print","Y_ReadInteger","Y_ReadLine","Y_Identifier","Y_TypeIdentifier",
"Y_IntConstant","Y_BoolConstant","Y_DoubleConstant","Y_StringConstant","Y_Plus",
"Y_Minus","Y_Times","Y_Div","Y_Mod","Y_Less","Y_LessEqual","Y_Greater",
"Y_GreaterEqual","Y_Assign","Y_Equal","Y_NotEqual","Y_And","Y_Or","Y_Not",
"Y_Semicolon","Y_Comma","Y_Dot","Y_LBracket","Y_RBracket","Y_LParen","Y_RParen",
"Y_LBrace","Y_RBrace",
};
char *yyrule[] = {
"$accept : program",
"program : decls",
"decls : decls decl",
"decls : decl",
"decl : variable ';'",
"decl : functionDecl",
"decl : classDecl",
"decl : interfaceDecl",
"$$1 :",
"interfaceDecl : Y_Interface $$1 identifier '{' nprototypes '}'",
"nprototypes : prototypes",
"nprototypes :",
"prototypes : prototypes prototype",
"prototypes : prototype",
"prototype : type identifier '(' formals ')' ';'",
"prototype : void identifier '(' formals ')' ';'",
"nvariableDecls : variableDecls",
"nvariableDecls :",
"variableDecls : variableDecls variable ';'",
"variableDecls : variable ';'",
"variable : type identifier",
"type : Y_Int",
"type : Y_Double",
"type : Y_Bool",
"type : Y_String",
"type : Y_TypeIdentifier",
"type : type '[' ']'",
"functionDecl : type identifier '(' formals ')' stmtBlock",
"functionDecl : void identifier '(' formals ')' stmtBlock",
"$$2 :",
"classDecl : Y_Class $$2 identifier extends_ident implements_ident '{' nfields '}'",
"$$3 :",
"extends_ident : Y_Extends $$3 identifier",
"extends_ident :",
"$$4 :",
"implements_ident : Y_Implements $$4 identifiers",
"implements_ident :",
"nfields : fields",
"nfields :",
"fields : fields field",
"fields : field",
"field : variable ';'",
"field : functionDecl",
"identifiers : identifiers ',' identifier",
"identifiers : identifier",
"formals : formals ',' variable",
"formals : variable",
"formals :",
"stmtBlock : '{' nvariableDecls nstmts '}'",
"nstmts : stmts",
"nstmts :",
"stmts : stmts stmt",
"stmts : stmt",
"$$5 :",
"returnStmt : Y_Return $$5 nexpr ';'",
"$$6 :",
"printStmt : Y_Print $$6 '(' exprs ')' ';'",
"stmt : matched_stmt",
"stmt : open_stmt",
"other_stmt : breakStmt ';'",
"other_stmt : nexpr ';'",
"other_stmt : returnStmt",
"other_stmt : printStmt",
"other_stmt : stmtBlock",
"matched_stmt : other_stmt",
"matched_stmt : matched_if",
"matched_stmt : matched_while",
"matched_stmt : matched_for",
"open_stmt : open_if",
"open_stmt : open_while",
"open_stmt : open_for",
"$$7 :",
"commonIf : Y_If $$7 '(' expr ')'",
"$$8 :",
"commonWhile : Y_While $$8 '(' expr ')'",
"$$9 :",
"commonFor : Y_For $$9 '(' nexpr ';' expr ';' nexpr ')'",
"common_matched_else : commonIf matched_stmt Y_Else",
"matched_if : common_matched_else matched_stmt",
"matched_while : commonWhile matched_stmt",
"matched_for : commonFor matched_stmt",
"open_if : commonIf stmt",
"open_if : common_matched_else open_stmt",
"open_while : commonWhile open_stmt",
"open_for : commonFor open_stmt",
"constant : Y_IntConstant",
"constant : Y_DoubleConstant",
"constant : Y_BoolConstant",
"constant : Y_StringConstant",
"constant : Y_Null",
"nexpr : expr",
"nexpr :",
"expr : constant",
"$$10 :",
"expr : lvalue '=' $$10 expr",
"expr : lvalue",
"expr : Y_This",
"expr : call",
"$$11 :",
"expr : expr '+' $$11 expr",
"$$12 :",
"expr : expr '-' $$12 expr",
"$$13 :",
"expr : expr '*' $$13 expr",
"$$14 :",
"expr : expr '/' $$14 expr",
"$$15 :",
"expr : expr '%' $$15 expr",
"$$16 :",
"expr : expr '<' $$16 expr",
"$$17 :",
"expr : expr '>' $$17 expr",
"$$18 :",
"expr : expr Y_LessEqual $$18 expr",
"$$19 :",
"expr : expr Y_Equal $$19 expr",
"$$20 :",
"expr : expr Y_GreaterEqual $$20 expr",
"$$21 :",
"expr : expr Y_NotEqual $$21 expr",
"$$22 :",
"expr : expr Y_And $$22 expr",
"$$23 :",
"expr : expr Y_Or $$23 expr",
"expr : '(' expr ')'",
"$$24 :",
"expr : '-' $$24 expr",
"$$25 :",
"expr : '!' $$25 expr",
"$$26 :",
"expr : Y_ReadInteger $$26 '(' ')'",
"$$27 :",
"expr : Y_ReadLine $$27 '(' ')'",
"$$28 :",
"expr : Y_New $$28 '(' identifier ')'",
"$$29 :",
"expr : Y_NewArray $$29 '(' expr ',' type ')'",
"lvalue : identifier",
"lvalue : dot",
"lvalue : expr '[' expr ']'",
"dot : expr '.' identifier",
"call : dot '(' actuals ')'",
"call : identifier '(' actuals ')'",
"actuals : exprs",
"actuals :",
"exprs : exprs ',' expr",
"exprs : expr",
"identifier : Y_Identifier",
"void : Y_Void",
"breakStmt : Y_Break",
};
#endif
#ifndef YYSTYPE
typedef int YYSTYPE;
#endif
#if YYDEBUG
#include <stdio.h>
#endif

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;
int      yyerrflag;
int      yychar;
short   *yyssp;
YYSTYPE *yyvsp;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static short   *yyss;
static short   *yysslim;
static YYSTYPE *yyvs;
static int      yystacksize;
#line 801 "decaf.y"

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
#line 679 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = yyssp - yyss;
    newss = (yyss != 0)
          ? (short *)realloc(yyss, newsize * sizeof(*newss))
          : (short *)malloc(newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    yyss  = newss;
    yyssp = newss + i;
    newvs = (yyvs != 0)
          ? (YYSTYPE *)realloc(yyvs, newsize * sizeof(*newvs))
          : (YYSTYPE *)malloc(newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse(void)
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

#ifdef lint
    goto yyerrlab;
#endif

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 179 "decaf.y"
{
		ParseTree *result = new ParseTree("START PROGRAM");
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 2:
#line 189 "decaf.y"
{
		yyvsp[-1]->addChild(yyvsp[0]);
		yyval = yyvsp[-1];
	}
break;
case 3:
#line 193 "decaf.y"
{
		ParseTree *result = new ParseTree("==== DECLARATIONS ====");
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 4:
#line 201 "decaf.y"
{yyval = yyvsp[-1];}
break;
case 5:
#line 202 "decaf.y"
{yyval = yyvsp[0];}
break;
case 6:
#line 203 "decaf.y"
{yyval = yyvsp[0];}
break;
case 7:
#line 204 "decaf.y"
{yyval = yyvsp[0];}
break;
case 8:
#line 208 "decaf.y"
{PUSH();}
break;
case 9:
#line 208 "decaf.y"
{
		ParseTree *result = new ParseTree("==== INTERFACE ====");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[-3]);
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 10:
#line 218 "decaf.y"
{yyval = yyvsp[0];}
break;
case 11:
#line 219 "decaf.y"
{yyval = NULL;}
break;
case 12:
#line 222 "decaf.y"
{
		yyvsp[-1]->addChild(yyvsp[0]);
		yyval = yyvsp[-1];
	}
break;
case 13:
#line 226 "decaf.y"
{
		ParseTree *result = new ParseTree("==== PROTOTYPES ====");
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 14:
#line 234 "decaf.y"
{
		ParseTree *result = new ParseTree("PROTOTYPE");
		result->addChild(yyvsp[-5]);
		result->addChild(yyvsp[-4]);
		result->addChild(yyvsp[-2]);
		top = yyval = result;
	}
break;
case 15:
#line 241 "decaf.y"
{
		ParseTree *result = new ParseTree("PROTOTYPE");
		result->addChild(yyvsp[-5]);
		result->addChild(yyvsp[-4]);
		result->addChild(yyvsp[-2]);
		top = yyval = result;
	}
break;
case 16:
#line 252 "decaf.y"
{yyval = yyvsp[0];}
break;
case 17:
#line 253 "decaf.y"
{yyval = NULL;}
break;
case 18:
#line 257 "decaf.y"
{
		yyvsp[-2]->addChild(yyvsp[-1]);
		yyval = yyvsp[-2];
	}
break;
case 19:
#line 261 "decaf.y"
{
		ParseTree *result = new ParseTree("==== VARIABLE DECLARATIONS ====");
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 20:
#line 269 "decaf.y"
{
		ParseTree *result = new ParseTree("VARIABLE");
		result->addChild(yyvsp[-1]);
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 21:
#line 281 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
case 22:
#line 282 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
case 23:
#line 283 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
case 24:
#line 284 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
case 25:
#line 285 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
case 26:
#line 286 "decaf.y"
{
		ParseTree *result = new ParseTree("ARRAY:");
		result->addChild(yyvsp[-2]);
		top = yyval = result;
	}
break;
case 27:
#line 295 "decaf.y"
{
		ParseTree *result = new ParseTree("==== FUNCTION ====");
		result->addChild(yyvsp[-5]);
		result->addChild(yyvsp[-4]);
		result->addChild(yyvsp[-2]);
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 28:
#line 304 "decaf.y"
{
		ParseTree *result = new ParseTree("==== FUNCTION ====");
		result->addChild(yyvsp[-5]);
		result->addChild(yyvsp[-4]);
		result->addChild(yyvsp[-2]);
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 29:
#line 317 "decaf.y"
{PUSH();}
break;
case 30:
#line 317 "decaf.y"
{
		ParseTree *result = new ParseTree("==== CLASS ====");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[-5]);
		result->addChild(yyvsp[-4]);
		result->addChild(yyvsp[-3]);
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 31:
#line 328 "decaf.y"
{PUSH();}
break;
case 32:
#line 328 "decaf.y"
{
		ParseTree *result = new ParseTree("EXTENDS");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 33:
#line 334 "decaf.y"
{yyval = NULL;}
break;
case 34:
#line 337 "decaf.y"
{PUSH();}
break;
case 35:
#line 337 "decaf.y"
{
		ParseTree *result = new ParseTree("IMPLEMENTS");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 36:
#line 343 "decaf.y"
{yyval = NULL;}
break;
case 37:
#line 346 "decaf.y"
{yyval = yyvsp[0];}
break;
case 38:
#line 347 "decaf.y"
{yyval = NULL;}
break;
case 39:
#line 350 "decaf.y"
{
		yyvsp[-1]->addChild(yyvsp[0]);
		yyval = yyvsp[-1];
	}
break;
case 40:
#line 354 "decaf.y"
{
		ParseTree *result = new ParseTree("==== FIELDS ====");
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 41:
#line 361 "decaf.y"
{yyval = yyvsp[-1];}
break;
case 42:
#line 362 "decaf.y"
{yyval = yyvsp[0];}
break;
case 43:
#line 365 "decaf.y"
{
		yyvsp[-2]->addChild(yyvsp[0]);
		yyval = yyvsp[-2];
	}
break;
case 44:
#line 369 "decaf.y"
{
		ParseTree *result = new ParseTree("==== IDENTIFIERS ====");
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 45:
#line 380 "decaf.y"
{
		yyvsp[-2]->addChild(yyvsp[0]);
		yyval = yyvsp[-2];
	}
break;
case 46:
#line 384 "decaf.y"
{
		ParseTree *result = new ParseTree("==== FORMALS ====");
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 47:
#line 389 "decaf.y"
{yyval = NULL;}
break;
case 48:
#line 394 "decaf.y"
{ 
		ParseTree *result = new ParseTree("STATEMENT BLOCK");
		result->addChild(yyvsp[-2]);
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 49:
#line 403 "decaf.y"
{yyval = yyvsp[0];}
break;
case 50:
#line 404 "decaf.y"
{yyval = NULL;}
break;
case 51:
#line 409 "decaf.y"
{
		yyvsp[-1]->addChild(yyvsp[0]);
		yyval = yyvsp[-1];
	}
break;
case 52:
#line 413 "decaf.y"
{
		ParseTree *result = new ParseTree("==== STATEMENTS ====");
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 53:
#line 422 "decaf.y"
{PUSH();}
break;
case 54:
#line 422 "decaf.y"
{
		ParseTree *result = new ParseTree("RETURN");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 55:
#line 431 "decaf.y"
{PUSH();}
break;
case 56:
#line 431 "decaf.y"
{
		ParseTree *result = new ParseTree("PRINT");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[-2]);
		top = yyval = result;
	}
break;
case 57:
#line 442 "decaf.y"
{yyval = yyvsp[0];}
break;
case 58:
#line 443 "decaf.y"
{yyval = yyvsp[0];}
break;
case 59:
#line 447 "decaf.y"
{yyval = yyvsp[-1];}
break;
case 60:
#line 448 "decaf.y"
{yyval = yyvsp[-1];}
break;
case 61:
#line 449 "decaf.y"
{yyval = yyvsp[0];}
break;
case 62:
#line 450 "decaf.y"
{yyval = yyvsp[0];}
break;
case 63:
#line 451 "decaf.y"
{yyval = yyvsp[0];}
break;
case 64:
#line 456 "decaf.y"
{yyval = yyvsp[0];}
break;
case 65:
#line 457 "decaf.y"
{yyval = yyvsp[0];}
break;
case 66:
#line 458 "decaf.y"
{yyval = yyvsp[0];}
break;
case 67:
#line 459 "decaf.y"
{yyval = yyvsp[0];}
break;
case 68:
#line 464 "decaf.y"
{yyval = yyvsp[0];}
break;
case 69:
#line 465 "decaf.y"
{yyval = yyvsp[0];}
break;
case 70:
#line 466 "decaf.y"
{yyval = yyvsp[0];}
break;
case 71:
#line 471 "decaf.y"
{PUSH();}
break;
case 72:
#line 471 "decaf.y"
{ yyval = yyvsp[-1];}
break;
case 73:
#line 476 "decaf.y"
{PUSH();}
break;
case 74:
#line 476 "decaf.y"
{ yyval = yyvsp[-1];}
break;
case 75:
#line 479 "decaf.y"
{PUSH();}
break;
case 76:
#line 479 "decaf.y"
{ 
		ParseTree *result = new ParseTree("(expr?; expr; expr?)");
		result->addChild(yyvsp[-5]);
		result->addChild(yyvsp[-3]);
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 77:
#line 490 "decaf.y"
{
		PUSH();
		ParseTree *result = new ParseTree("condition + statement");
		result->addChild(yyvsp[-2]);
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 78:
#line 500 "decaf.y"
{
		ParseTree *result = new ParseTree("STATEMENT: if/else");
		Token* a_else = POP();
		Token* a_if = POP();
		result->addChild(new ParseTree(a_if));
		result->addChild(yyvsp[-1]);
		result->addChild(new ParseTree(a_else));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 79:
#line 513 "decaf.y"
{
		ParseTree *result = new ParseTree("STATEMENT: while");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[-1]);
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 80:
#line 522 "decaf.y"
{
		ParseTree *result = new ParseTree("STATEMENT: for");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[-1]);
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 81:
#line 533 "decaf.y"
{
		ParseTree *result = new ParseTree("STATEMENT: if");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[-1]);
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 82:
#line 540 "decaf.y"
{
		ParseTree *result = new ParseTree("STATEMENT: if/else");
		Token* a_else = POP();
		Token* a_if = POP();
		result->addChild(new ParseTree(a_if));
		result->addChild(yyvsp[-1]);
		result->addChild(new ParseTree(a_else));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 83:
#line 554 "decaf.y"
{
		ParseTree *result = new ParseTree("STATEMENT: while");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[-1]);
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 84:
#line 563 "decaf.y"
{
		ParseTree *result = new ParseTree("STATEMENT: for");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[-1]);
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 85:
#line 575 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
case 86:
#line 576 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
case 87:
#line 577 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
case 88:
#line 578 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
case 89:
#line 579 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
case 90:
#line 586 "decaf.y"
{yyval = yyvsp[0];}
break;
case 91:
#line 587 "decaf.y"
{yyval = NULL;}
break;
case 92:
#line 591 "decaf.y"
{yyval = yyvsp[0];}
break;
case 93:
#line 592 "decaf.y"
{PUSH();}
break;
case 94:
#line 592 "decaf.y"
{
		ParseTree *result = new ParseTree("bexpr: lvalue = expr");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 95:
#line 599 "decaf.y"
{yyval = yyvsp[0];}
break;
case 96:
#line 600 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
case 97:
#line 601 "decaf.y"
{yyval = yyvsp[0];}
break;
case 98:
#line 602 "decaf.y"
{PUSH();}
break;
case 99:
#line 602 "decaf.y"
{
		ParseTree *result = new ParseTree("bexpr: +");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 100:
#line 609 "decaf.y"
{PUSH();}
break;
case 101:
#line 609 "decaf.y"
{
		ParseTree *result = new ParseTree("bexpr: -");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 102:
#line 616 "decaf.y"
{PUSH();}
break;
case 103:
#line 616 "decaf.y"
{
		ParseTree *result = new ParseTree("bexpr: *");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;	
	}
break;
case 104:
#line 623 "decaf.y"
{PUSH();}
break;
case 105:
#line 623 "decaf.y"
{
		ParseTree *result = new ParseTree("bexpr: /");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 106:
#line 630 "decaf.y"
{PUSH();}
break;
case 107:
#line 630 "decaf.y"
{
		ParseTree *result = new ParseTree("bexpr: %");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 108:
#line 637 "decaf.y"
{PUSH();}
break;
case 109:
#line 637 "decaf.y"
{
		ParseTree *result = new ParseTree("bexpr: <");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 110:
#line 644 "decaf.y"
{PUSH();}
break;
case 111:
#line 644 "decaf.y"
{
		ParseTree *result = new ParseTree("bexpr: >");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 112:
#line 651 "decaf.y"
{PUSH();}
break;
case 113:
#line 651 "decaf.y"
{
		ParseTree *result = new ParseTree("bexpr: <=");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 114:
#line 658 "decaf.y"
{PUSH();}
break;
case 115:
#line 658 "decaf.y"
{
		ParseTree *result = new ParseTree("bexpr: ==");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 116:
#line 665 "decaf.y"
{PUSH();}
break;
case 117:
#line 665 "decaf.y"
{
		ParseTree *result = new ParseTree("bexpr: >=");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 118:
#line 672 "decaf.y"
{PUSH();}
break;
case 119:
#line 672 "decaf.y"
{
		ParseTree *result = new ParseTree("bexpr: !=");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 120:
#line 679 "decaf.y"
{PUSH();}
break;
case 121:
#line 679 "decaf.y"
{
		ParseTree *result = new ParseTree("bexpr: &&");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 122:
#line 686 "decaf.y"
{PUSH();}
break;
case 123:
#line 686 "decaf.y"
{
		ParseTree *result = new ParseTree("bexpr: ||");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 124:
#line 693 "decaf.y"
{
		/*ParseTree *result = new ParseTree("expr: (expr)");*/
		/*result->addChild($2);*/
		/*top = $$ = result;*/
		yyval = yyvsp[-1];
	}
break;
case 125:
#line 699 "decaf.y"
{PUSH();}
break;
case 126:
#line 699 "decaf.y"
{
		ParseTree *result = new ParseTree("expr: -expr");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 127:
#line 705 "decaf.y"
{PUSH();}
break;
case 128:
#line 705 "decaf.y"
{
		ParseTree *result = new ParseTree("expr: !expr");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 129:
#line 711 "decaf.y"
{PUSH();}
break;
case 130:
#line 711 "decaf.y"
{
		ParseTree *result = new ParseTree("ReadInteger()");
		result->addChild(new ParseTree(POP()));
		top = yyval = result;
	}
break;
case 131:
#line 716 "decaf.y"
{PUSH();}
break;
case 132:
#line 716 "decaf.y"
{
		ParseTree *result = new ParseTree("ReadLine()");
		result->addChild(new ParseTree(POP()));
		top = yyval = result;
	}
break;
case 133:
#line 722 "decaf.y"
{PUSH();}
break;
case 134:
#line 722 "decaf.y"
{
		ParseTree *result = new ParseTree("New(ident)");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 135:
#line 728 "decaf.y"
{PUSH();}
break;
case 136:
#line 728 "decaf.y"
{
		ParseTree *result = new ParseTree("NewArray(expr, type)");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[-3]);
		result->addChild(yyvsp[-1]);
		top = yyval = result;
		
	}
break;
case 137:
#line 739 "decaf.y"
{yyval = yyvsp[0];}
break;
case 138:
#line 740 "decaf.y"
{yyval = yyvsp[0];}
break;
case 139:
#line 741 "decaf.y"
{
		ParseTree *result = new ParseTree("ARRAY: expr[expr]");
		result->addChild(yyvsp[-3]);
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 140:
#line 751 "decaf.y"
{
		ParseTree *result = new ParseTree("DOT");
		result->addChild(yyvsp[-2]);
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 141:
#line 761 "decaf.y"
{
		ParseTree *result = new ParseTree("CALL: expr.ident(exprs)");
		result->addChild(yyvsp[-3]);
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 142:
#line 767 "decaf.y"
{
		ParseTree *result = new ParseTree("CALL: ident(exprs)");
		result->addChild(yyvsp[-3]);
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 143:
#line 777 "decaf.y"
{yyval = yyvsp[0];}
break;
case 144:
#line 778 "decaf.y"
{yyval = NULL;}
break;
case 145:
#line 781 "decaf.y"
{
		yyvsp[-2]->addChild(yyvsp[0]);
		yyval = yyvsp[-2];
	}
break;
case 146:
#line 785 "decaf.y"
{
		ParseTree *result = new ParseTree("==== EXPRESSIONS ====");
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 147:
#line 795 "decaf.y"
{ yyval = new ParseTree(myTok);}
break;
case 148:
#line 796 "decaf.y"
{ yyval = new ParseTree(myTok);}
break;
case 149:
#line 797 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
#line 1789 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    return (1);

yyaccept:
    return (0);
}
