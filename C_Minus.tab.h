/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_C_MINUS_TAB_H_INCLUDED
# define YY_YY_C_MINUS_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 38 "C_Minus.y" /* yacc.c:1909  */

    #include "globals.h"

#line 48 "C_Minus.tab.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    NUM = 259,
    IF = 260,
    ELSE = 261,
    INT = 262,
    RETURN = 263,
    VOID = 264,
    WHILE = 265,
    PLUS = 266,
    MINUS = 267,
    TIMES = 268,
    DIVIDE = 269,
    LT = 270,
    LEQ = 271,
    GT = 272,
    GEQ = 273,
    EQ = 274,
    NEQ = 275,
    ASSIGN = 276,
    SEMICOLON = 277,
    COMMA = 278,
    LPAREN = 279,
    RPAREN = 280,
    LBRACKET = 281,
    RBRACKET = 282,
    LBRACE = 283,
    RBRACE = 284,
    ERROR = 285
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 42 "C_Minus.y" /* yacc.c:1909  */

    TreeNode * tree;
    ExpType type;
    int op;

#line 97 "C_Minus.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_C_MINUS_TAB_H_INCLUDED  */
