%{
// switch (yyn)
// 若想监控每个状态的变化，在C_Minus.tab.c中对上面一行打断点
// 此外发现bison是后序遍历

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

%type <tree> program declaration-list declaration var-declaration fun-declaration 
%type <tree> params param-list param
%type <tree> compound-stmt local-declarations statement-list statement
%type <tree> expression-stmt selection-stmt iteration-stmt return-stmt else-stmt
%type <tree> expression var simple-expression additive-expression
%type <tree> term factor call args arg-list
%type <type> type-specifier 
%type <op> relop addop mulop

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
| fun-declaration   {$$ = $1;}
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

fun-declaration:
type-specifier ID {
    savedName = copyString(tokenString);
}
LPAREN params RPAREN compound-stmt {
    $$ = newDecNode(FunK);
    $$->attr.name = savedName;
    $$->child[0] = $5;
    $$->child[1] = $7;
    $$->type = $1;
}
;

params:
param-list { $$ = $1; }
| VOID {$$ = NULL;}
;

param-list:
param-list COMMA param {
    TreeNode *t = $1;
    while(t->sibling){
        t = t->sibling;
    }
    t->sibling = $3;
    $$ = $1;
}
| param { $$ = $1; }
;

param:
type-specifier ID {
    savedName = copyString(tokenString);
    $$ = newDecNode(VarK);
    $$->attr.name = savedName;
    $$->type = $1;
}
| type-specifier ID{
    savedName = copyString(tokenString);
} 
LBRACKET RBRACKET{
    $$ = newDecNode(VarK);
    $$->attr.name = savedName;
    $$->type = Array;
}
;

compound-stmt:
LBRACE local-declarations statement-list RBRACE {
    $$ = newStmNode(CompoundK);
    $$->child[0] = $2;
    $$->child[1] = $3;
}
;

local-declarations:
local-declarations var-declaration {
    TreeNode *t = $1;
    // 如果local-declaration为empty状态时，
    // 在empty中生成语法树会有奇奇怪怪的问题，放到这里最佳
    if(!t)
        $$ = $2;
    else{
        while(t->sibling){
            t = t->sibling;
        }
        t->sibling = $2;
        $$ = $1;
    }
}
| %empty {$$ = NULL;}
;

statement-list:
statement-list statement {
    TreeNode *t = $1;
    if(!t)
        $$ = $2;
    else{
        while(t->sibling){
            t = t->sibling;
        }
        t->sibling = $2;
        $$ = $1;
    }
}
| %empty {$$ = NULL;}
;

statement:
expression-stmt {$$ = $1;}
| compound-stmt {$$ = $1;}
| selection-stmt {$$ = $1;}
| iteration-stmt {$$ = $1;}
| return-stmt {$$ = $1;}
;

expression-stmt:
expression SEMICOLON {
    $$ = $1;
}
| SEMICOLON {$$ = NULL;}
;

selection-stmt:
IF LPAREN expression RPAREN statement else-stmt {
    $$ = newStmNode(IfK);
    $$->child[0] = $3;
    $$->child[1] = $5;
    $$->child[2] = $6;
}
;

else-stmt:
ELSE statement{
    $$ = $2;
}
| %empty {$$ = NULL;}
;

iteration-stmt:
WHILE LPAREN expression RPAREN statement {
    $$ = newStmNode(WhileK);
    $$->child[0] = $3;
    $$->child[1] = $5;
}
;

return-stmt:
RETURN SEMICOLON {
    $$ = newStmNode(ReturnK);
}

| RETURN expression SEMICOLON {
    $$ = newStmNode(IfK);
    $$->child[0] = $2;
}
;

expression:
var ASSIGN expression {
    $$ = newExpNode(OpK);
    $$->attr.op = ASSIGN; 
    $$->child[0] = $1;
    $$->child[1] = $3;
}
| simple-expression {
    $$ = $1;
}
;

var:
ID { 
    $$ = newExpNode(IdK);
    $$->attr.name = copyString(tokenString);
    $$->type = Int;
}
| ID LBRACKET expression RBRACKET{
    $$ = newExpNode(IdK);
    $$->attr.name = copyString(tokenString);
    $$->type = Array;
    $$->child[0] = $3;
}
;

simple-expression:
additive-expression relop additive-expression{
    $$ = newExpNode(OpK);
    $$->attr.op = $2;
    $$->child[0] = $1;
    $$->child[1] = $3;
}
| additive-expression { $$ = $1; }
;

relop:
LEQ { $$ = LEQ; }
| LT { $$ = LT; }
| GT { $$ = GT; }
| GEQ { $$ = GEQ; }
| EQ { $$ = EQ; }
| NEQ { $$ = NEQ; }
;

additive-expression:
additive-expression addop term {
    $$ = newExpNode(OpK);
    $$->attr.op = $2;
    $$->child[0] = $1;
    $$->child[1] = $3;
}
| term { $$ = $1; }
;

addop:
PLUS { $$ = PLUS; }
| MINUS { $$ = MINUS; }
;

term:
term mulop factor {
    $$ = newExpNode(OpK);
    $$->attr.op = $2;
    $$->child[0] = $1;
    $$->child[1] = $3;
}
| factor { $$ = $1; }
;

mulop:
TIMES { $$ = TIMES; }
| DIVIDE { $$ = DIVIDE; }
;

factor:
LPAREN expression RPAREN { $$ = $2; }
| var { $$ = $1; }
| call { $$ = $1; }
| NUM {
    char *temp = copyString(tokenString);
    $$ = newExpNode(NumK);
    $$->attr.val = atoi(temp);
}
;

call:
ID {
    savedName = copyString(tokenString);
} LPAREN args RPAREN {
    $$ = newExpNode(CallK);
    $$->attr.name = savedName;
    $$->child[0] = $4;
}
;

args:
arg-list
| %empty { $$ = NULL; }
;

arg-list:
arg-list COMMA expression {
    TreeNode *t = $1;
    while(t->sibling){
        t = t->sibling;
    }
    t->sibling = $3;
}
| expression {
    $$ = $1;
}
;

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
