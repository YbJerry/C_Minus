%{
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "C_Minus.tab.h"
#include "globals.h"
#include "util.h"

TokenStringStack *tokenStringStack = NULL;
int lineNo = 1;
int charNo = 1;

void tokenStringPush(char *token){
    TokenStringStack *s = (TokenStringStack *)malloc(sizeof(TokenStringStack));
    strcpy(s->tokenString, token);
    s->next = tokenStringStack;
    tokenStringStack = s;
}

%}

digit       [0-9]
letter      [a-zA-Z]
identifier  {letter}+
number      {digit}+

%%

"if"            {charNo += strlen(yytext); return IF;}
"else"          {charNo += strlen(yytext); return ELSE;}
"int"           {charNo += strlen(yytext); return INT;}
"return"        {charNo += strlen(yytext); return RETURN;}
"void"          {charNo += strlen(yytext); return VOID;}
"while"         {charNo += strlen(yytext); return WHILE;}

{identifier}    {
    tokenStringPush(yytext);
    charNo += strlen(yytext); 
    return ID;
}
{number}        {
    tokenStringPush(yytext);
    charNo += strlen(yytext); 
    return NUM;
}

"+"             {charNo += strlen(yytext); return PLUS;}
"-"             {charNo += strlen(yytext); return MINUS;}
"*"             {charNo += strlen(yytext); return TIMES;}
"/"             {charNo += strlen(yytext); return DIVIDE;}
"<"             {charNo += strlen(yytext); return LT;}
"<="            {charNo += strlen(yytext); return LEQ;}
">"             {charNo += strlen(yytext); return GT;}
">="            {charNo += strlen(yytext); return GEQ;}
"=="            {charNo += strlen(yytext); return EQ;}
"!="            {charNo += strlen(yytext); return NEQ;}
"="             {charNo += strlen(yytext); return ASSIGN;}
";"             {charNo += strlen(yytext); return SEMICOLON;}
","             {charNo += strlen(yytext); return COMMA;}
"("             {charNo += strlen(yytext); return LPAREN;}
")"             {charNo += strlen(yytext); return RPAREN;}
"["             {charNo += strlen(yytext); return LBRACKET;}
"]"             {charNo += strlen(yytext); return RBRACKET;}
"{"             {charNo += strlen(yytext); return LBRACE;}
"}"             {charNo += strlen(yytext); return RBRACE;}
"/*"            {
                    int ch;
                    while(1){
                        if((ch = input()) != '*'){
                            if(ch == '\r'){
                                if((ch = input()) != '\n'){
                                    unput(ch);
                                }
                                ++lineNo;
                                charNo = 1;
                            }else if(ch == '\n'){
                                ++lineNo;
                                charNo = 1;
                            }
                            continue;
                        }
                        unput(ch);

                        while((ch = input()) == '*'){
                            ;
                        }

                        if(ch == '/'){
                            break;
                        }
                    }
                }
"\r\n"          {++lineNo; charNo = 1;}
"\r"|"\n"       {++lineNo; charNo = 1;}
"\t"            {charNo = (charNo / TABDISTANCE + 1) * TABDISTANCE;}
" "             {charNo++;}
.               {return ERROR;}

%%

int yywrap(void) {
    return 1;
}