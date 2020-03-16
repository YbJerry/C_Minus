%{
#include <stdio.h>
#include <unistd.h>
%}

digit       [0-9]
letter      [a-zA-Z]
identifier  {letter}+
number      {digit}+

%%

"if"            {printf("IF ");}
"else"          {printf("ELSE ");}
"int"           {printf("INT ");}
"return"        {printf("RETURN ");}
"void"          {printf("VOID ");}
"while"         {printf("WHILE ");}

{identifier}    {printf("ID ");}
{number}        {printf("NUM ");}

"+"             {printf("PLUS ");}
"-"             {printf("MINUS ");}
"*"             {printf("TIMES ");}
"/"             {printf("DIVIDE ");}
"<"             {printf("LT ");}
"<="            {printf("LEQ ");}
">"             {printf("GT ");}
">="            {printf("GEQ ");}
"=="            {printf("EQ ");}
"!="            {printf("NEQ ");}
"="             {printf("ASSIGN ");}
";"             {printf("SEMICOLON ");}
","             {printf("COMMA ");}
"("             {printf("LPAREN ");}
")"             {printf("RPAREN ");}
"["             {printf("LBRACKET ");}
"]"             {printf("RBRACKET ");}
"{"             {printf("LBRACE ");}
"}"             {printf("RBRACE ");}
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

"\r"            {}
"\n"            {printf("\n");}
"\t"            {printf("\t");}
" "             {printf(" ");}
.               {printf("ERROR\n");}

%%

int yywrap(void) {
    return 1;
}

int main(int argc, char **argv) {
    if(argc > 1){
        yyin = fopen(argv[1], "r");
    }
    else{
        yyin = stdin;
    }
    yylex();
    fclose(yyin);
    return 0;
}