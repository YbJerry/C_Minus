#include "analyze.h"

static int isFunc = 0;

void buildSymbolTable(TreeNode *tree){
    if(tree){
        if(tree->nodeKind == StmK && tree->kind.stm == CompoundK){
            if(isFunc)
                isFunc = 0;
            else
                newSymbolTable(NULL);
        }else if(tree->nodeKind == DecK && tree->kind.dec == FunK){
            insertSymbol(tree);
            newSymbolTable(tree);
            isFunc = 1;
        }else if(tree->nodeKind == DecK && tree->kind.dec == VarK){
            insertSymbol(tree);
        }//else if(tree->nodeKind == ExpK && (tree->kind.exp == IdK || tree->kind.exp == CallK)){
        //     insertSymbol(tree->attr.name);
        // }

        int i;
        for(i = 0; i < MAXCHILDNUM; ++i)
            buildSymbolTable(tree->child[i]);

        typeCheck(tree);
        
        if(tree->nodeKind == StmK && tree->kind.stm == CompoundK){
            printSymbolTable(symbolTables);
            delSymbolTable();
            // printSymbolTable(symbolTables);
            // delSymbolTable();
        }
        buildSymbolTable(tree->sibling);
    }
}

void typeCheck(TreeNode *tree){
    if(tree){
        switch(tree->nodeKind){
            case StmK:
                switch (tree->kind.stm)
                {
                case IfK:
                    if(tree->child[0]->type != Int){
                        typeError("if判断条件中出错");
                    }
                case WhileK:
                    if(tree->child[0]->type != Int){
                        typeError("while判断条件中出错");
                    }
                    break;
                case ReturnK:
                    break;
                default:
                    break;
                }
                break;
            case ExpK:
                switch (tree->kind.exp)
                {
                case OpK:
                    break;
                case IdK:
                    tree->type = Void;
                    break;
                case NumK:
                    break;
                case CallK:

                    break;
                default:
                    break;
                }
                break;
            case DecK:
                switch (tree->kind.dec)
                {
                case FunK:
                case VarK:
                    if(tree->child[0]->type != Int){
                        ;
                    }
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
        }
    }
}

void typeError(char *message){
    printf("%s\n", message);
}