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
                    break;
                case NumK:
                    break;
                case CallK:{
                    // SymbolTable *table = searchRegionName(tree->attr.name);
                    // ArgsLink *arg = table->argsType;
                    // TreeNode *t = tree->child[0];
                    // tree->type = table->resType;
                    // if(arg == NULL && t != NULL){
                    //     typeError("函数调用参数过多");
                    //     break;
                    // }
                    // while(arg){
                    //     if(!t){
                    //         typeError("函数调用参数过少");
                    //         break;
                    //     }else if(arg->type != t->type){
                    //         typeError("函数参数不匹配");
                    //         break;
                    //     }
                    //     arg = arg->next;
                    //     t = t->sibling;
                    // }
                    break;
                }
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