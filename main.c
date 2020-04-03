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

int main(int argc, char **argv) {
    if(argc > 1){
        yyin = fopen(argv[1], "r");
    }
    else{
        yyin = stdin;
    }
    newSymbolTable();
    yyparse();
    fclose(yyin);
    // printTree(savedTree);
    buildSymbolTable(savedTree);
    printSymbolTable(symbolTables);
    return 0;
}