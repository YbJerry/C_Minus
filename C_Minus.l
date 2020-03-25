%{
#include <stdio.h>
#include <unistd.h>
#include "C_Minus.tab.h"

#define MAX_TOKEN_LEN 50

char tokenString[MAX_TOKEN_LEN+1];
%}

digit       [0-9]
letter      [a-zA-Z]
identifier  {letter}+
number      {digit}+

%%

"if"            {return IF;}
"else"          {return ELSE;}
"int"           {return INT;}
"return"        {return RETURN;}
"void"          {return VOID;}
"while"         {return WHILE;}

{identifier}    {
    strcpy(tokenString, yytext);
    return ID;
}
{number}        {
    strcpy(tokenString, yytext);
    return NUM;
}

"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return TIMES;}
"/"             {return DIVIDE;}
"<"             {return LT;}
"<="            {return LEQ;}
">"             {return GT;}
">="            {return GEQ;}
"=="            {return EQ;}
"!="            {return NEQ;}
"="             {return ASSIGN;}
";"             {return SEMICOLON;}
","             {return COMMA;}
"("             {return LPAREN;}
")"             {return RPAREN;}
"["             {return LBRACKET;}
"]"             {return RBRACKET;}
"{"             {return LBRACE;}
"}"             {return RBRACE;}
"/*"            {
                    int ch;
                    while(1){
                        if((ch = input()) != '*'){
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

"\r"|"\n"|"\t"|" "  {}
.               {return ERROR;}

%%

int yywrap(void) {
    return 1;
}


