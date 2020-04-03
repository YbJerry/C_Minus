#include "analyze.h"

void buildSymbolTable(TreeNode *tree){
    if(tree){
        if(tree->nodeKind == StmK && tree->kind.stm == CompoundK){
            newSymbolTable();
        }else if(tree->nodeKind == DecK && tree->kind.dec == FunK){
            insertSymbol(tree->attr.name);
            newSymbolTable();
        }else if(tree->nodeKind == DecK && tree->kind.dec == VarK){
            insertSymbol(tree->attr.name);
        }else if(tree->nodeKind == ExpK && (tree->kind.exp == IdK || tree->kind.exp == CallK)){
            insertSymbol(tree->attr.name);
        }

        int i;
        for(i = 0; i < MAXCHILDNUM; ++i)
            buildSymbolTable(tree->child[i]);
        
        if(tree->nodeKind == StmK && tree->kind.stm == CompoundK){
            printSymbolTable(symbolTables);
            delSymbolTable();
            printSymbolTable(symbolTables);
            delSymbolTable();
        }
        buildSymbolTable(tree->sibling);
    }
}

// void typeCheck(TreeNode *tree){
//     if(tree){
//         int i;
//         for(i = 0; i < MAXCHILDNUM; ++i)
//             typeCheck(tree->child[i]);
//         switch(tree->nodeKind){
//             case StmK:
//                 switch (tree->kind)
//                 {
//                 case IfK:
//                 case WhileK:
//                     if(tree->child[0]->type != Int){
//                         ;
//                     }
//                     break;
//                 default:
//                     break;
//                 }
//                 break;
//             case ExpK:
//                 break;
//             case DecK:
//                 break;
//             case ComK:
//                 break;
//             default:
//                 break;
//         }
//         typeCheck(tree->sibling);
//     }
// }

void typeError(char *message){
    printf("%s\n", message);
}