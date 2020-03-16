%{
#include <stdio.h>
#include "globals.h"
#include "util.h"

extern FILE *yyin;
extern char tokenString[];

static TreeNode *savedTree;
static char *savedName;
%}

%token ID NUM
%token IF ELSE INT RETURN VOID WHILE
%token PLUS MINUS TIMES DIVIDE LT LEQ GT GEQ EQ NEQ ASSIGN SEMICOLON COMMA LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE
%token ERROR

%code requires{
    #include "globals.h"
}

%union {
    TreeNode * tree;
    ExpType type;
    int op;
}

%type <tree> program declaration-list declaration var-declaration // fun-declaration 
// %type <tree> params param-list param
// %type <tree> compound-stmt local-declarations statement-list statement
// %type <tree> expression-stmt selection-stmt iteration-stmt return-stmt
// %type <tree> expression var simple-expression additive-expression
// %type <tree> term factor call args arg-list
%type <type> type-specifier 
// %type <op> relop addop mulop

%start program

%%

program:
declaration-list    {savedTree = $1;}
;

declaration-list:
declaration-list declaration    {
    TreeNode *t = $1;
    while(t->sibling != NULL){
        t = t->sibling;
    }
    t->sibling = $2;
    $$ = $1;
}
| declaration   {
    $$ = $1;
}
;

declaration:
var-declaration {$$ = $1;}
// | fun-declaration   {$$ = $1;}
;

var-declaration:
type-specifier ID {
    savedName = copyString(tokenString);
}
SEMICOLON {
    $$ = newDecNode(VarK);
    $$->attr.name = savedName;
    $$->type = $1;
}
| type-specifier ID {
    savedName = copyString(tokenString);
}
LBRACKET NUM RBRACKET SEMICOLON {
    $$ = newDecNode(VarK);
    $$->attr.name = savedName;
    $$->type = Array;
}
;

type-specifier:
INT     {$$ = Int;}
| VOID  {$$ = Void;}
;

// fun-declaration:
// type-specifier ID LPAREN params RPAREN
// | compound-stmt
// ;

// params:
// param-list
// | VOID
// ;

// param-list:
// param-list COMMA param
// | param
// ;

// param:
// type-specifier ID
// | type-specifier ID LBRACKET RBRACKET
// ;

// compound-stmt:
// LBRACE local-declarations statement-list RBRACE
// ;

// local-declarations:
// local-declarations var-declaration
// | empty
// ;

// statement-list:
// statement-list statement
// | empty
// ;

// statement:
// expression-stmt
// | compound-stmt
// | selection-stmt
// | iteration-stmt
// | return-stmt
// ;

// expression-stmt:
// expression SEMICOLON
// | SEMICOLON
// ;

// selection-stmt:
// IF LPAREN expression RPAREN statement
// | IF LPAREN expression RPAREN statement ELSE statement
// ;

// iteration-stmt:
// WHILE LPAREN expression RPAREN statement
// ;

// return-stmt:
// RETURN SEMICOLON
// | RETURN expression SEMICOLON
// ;

// expression:
// var ASSIGN expression
// | simple-expression
// ;

// var:
// ID
// | ID LBRACKET expression RBRACKET
// ;

// simple-expression:
// additive-expression relop additive-expression
// | additive-expression
// ;

// relop:
// LEQ
// | LT
// | GT
// | GEQ
// | EQ
// | NEQ
// ;

// additive-expression:
// additive-expression addop term
// | term
// ;

// addop:
// PLUS
// | MINUS
// ;

// term:
// term mulop factor
// | factor
// ;

// mulop:
// MINUS
// | DIVIDE
// ;

// factor:
// LPAREN expression RPAREN
// | var
// | call
// | NUM
// ;

// call:
// ID LPAREN args RPAREN
// ;

// args:
// arg-list
// | empty
// ;

// arg-list:
// arg-list COMMA expression
// | expression
// ;

// empty:
// ;

%%

int yyerror(char *msg)
{
    printf("Error: %s \n", msg);
}

int main(int argc, char **argv) {
    if(argc > 1){
        yyin = fopen(argv[1], "r");
    }
    else{
        yyin = stdin;
    }
    yyparse();
    fclose(yyin);
    printTree(savedTree);
    return 0;
}
