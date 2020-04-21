#include <stdio.h>
#include <stdlib.h>
#include "analyze.h"
#include "C_Minus.tab.h"
#include "globals.h"
#include "symtab.h"
#include "util.h"

extern TreeNode *savedTree;
extern FILE *yyin;
extern SymbolTable *symbolTables;
extern int location;

int main(int argc, char **argv) {
    if(argc > 1){
        yyin = fopen(argv[1], "r");
    }
    else{
        yyin = stdin;
    }

    newSymbolTable(NULL);
    yyparse();
    fclose(yyin);
    // printTree(savedTree);
    buildSymbolTable(savedTree);
    printSymbolTable(symbolTables);
    delSymbolTable();
    location = 0;
    return 0;
}