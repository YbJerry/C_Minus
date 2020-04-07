#include "util.h"

extern int lineNo, charNo;

TreeNode * newStmNode(StmKind kind){
    TreeNode * res = (TreeNode *)malloc(sizeof(TreeNode));
    if(res == NULL){
        printf("Error!\n");
        return res;
    }

    int i;
    for(i = 0; i < MAXCHILDNUM; ++i){
        res->child[i] = NULL;
    }
    res->sibling = NULL;
    res->nodeKind = StmK;
    res->kind.stm = kind;
    res->pos.lineNo = lineNo;
    res->pos.charNo = charNo;

    return res;
}

TreeNode * newExpNode(ExpKind kind){
    TreeNode * res = (TreeNode *)malloc(sizeof(TreeNode));
    if(res == NULL){
        printf("Error!\n");
        return res;
    }

    int i;
    for(i = 0; i < MAXCHILDNUM; ++i){
        res->child[i] = NULL;
    }
    res->sibling = NULL;
    res->nodeKind = ExpK;
    res->kind.exp = kind;
    res->pos.lineNo = lineNo;
    res->pos.charNo = charNo;
    
    return res;
}

TreeNode * newDecNode(DecKind kind){
    TreeNode * res = (TreeNode *)malloc(sizeof(TreeNode));
    if(res == NULL){
        printf("Error!\n");
        return res;
    }

    int i;
    for(i = 0; i < MAXCHILDNUM; ++i){
        res->child[i] = NULL;
    }
    res->sibling = NULL;
    res->nodeKind = DecK;
    res->kind.dec = kind;
    res->pos.lineNo = lineNo;
    res->pos.charNo = charNo;

    return res;
}

char * copyString(char *str){
    char *temp = (char *)malloc((strlen(str)+1) * sizeof(char));
    return strcpy(temp, str);
}

static int treeLevel = -4;

void printTree(TreeNode *tree){
    treeLevel += 4;
    int i;
    while(tree != NULL){
        printNode(tree);
        for(i = 0; i < MAXCHILDNUM; ++i)
            printTree(tree->child[i]);
        tree = tree->sibling;
    }
    treeLevel -= 4;
}

void printNode(TreeNode *node){
    printSpaces();
    if(node->nodeKind == DecK){
        switch(node->kind.dec){
            case VarK:
                printf("var-dec: %s\n", node->attr.name);
                break;
            case FunK:
                printf("fun-dec: %s\n", node->attr.name);
                break;
            default:
                printf("error\n");
                break;
        }
    }else if(node->nodeKind == ExpK){
        switch(node->kind.exp){
            case OpK:
                printf("op: %s\n", tokenTrans(node->attr.op));
                break;
            case IdK:
                if(node->type == Array)
                    printf("array: %s\n", node->attr.name);
                else
                    printf("id: %s\n", node->attr.name);
                break;
            case NumK:
                printf("num: %d\n", node->attr.val);
                break;
            case CallK:
                printf("call: %s\n", node->attr.name);
                break;
            default:
                printf("error\n");
                break;
        }
    }else if(node->nodeKind == StmK){
        switch(node->kind.stm){
            case IfK:
                printf("if:\n");
                break;
            case WhileK:
                printf("while:\n");
                break;
            case ReturnK:
                printf("return:\n");
                break;
            case CompoundK:
                printf("{}:\n");
                break;
            default:
                printf("error\n");
                break;
        }
    }else if(node->nodeKind == ComK){
        treeLevel -= 4;
    }else{
        printf("error\n");
    }
}

void printSpaces(){
    int i;
    for(i = 0; i < treeLevel; ++i){
        putchar(' ');
    }
}

char * typeTrans(ExpType type){
    switch (type)
    {
    case Int:
        return "int";
    case Void:
        return "void";
    case Array:
        return "array";
    }
}

char * tokenTrans(TokenType op){
    switch(op){
        case PLUS:
            return "+";
        case MINUS:
			return "-";
        case TIMES:
			return "*";
        case DIVIDE:
			return "/";
        case LT:
			return "<"; 
        case LEQ:
			return "<=";
        case GT:
			return ">";
        case GEQ:
			return ">=";
        case EQ:
			return "==";
        case NEQ:
			return "!=";
        case ASSIGN:
			return "=";
        case SEMICOLON:
			return ";";
        case COMMA:
			return ",";
 		case LPAREN:
			return "(";
 		case RPAREN:
			return ")";
 		case LBRACKET:
			return "[";
 		case RBRACKET:
			return "]";
 		case LBRACE:
			return "{";
 		case RBRACE:
			return "}";
        // case IF:
		// 	return "if";
        // case ELSE:
		// 	return "else";
        // case INT:
		// 	return "int";
        // case RETURN:
		// 	return "return";
        // case VOID:
		// 	return "void";
        // case WHILE:
        //     return "while";
    }
}

void printSymbolTable(SymbolTable *sTable){
    
    if(sTable){
        if(sTable->name){
            printf("fun: %s\n", sTable->name);
            // printf("res: %s\n", (sTable->resType == Int)?"Int":"Void");
            // printf("args: ");
            // ArgsLink *l = sTable->argsType;
            // while(l){
            //     if(l->type == Int)
            //         printf("%s  ", "int");
            //     else if(l->type == Void)
            //         printf("%s  ", "void");
            //     else if(l->type == Array)
            //         printf("%s  ", "array");
            //     l = l->next;
            // }
            // putchar('\n');
        }else
        {
            printf("non-name:\n");
        }
        
        int i;
        for(i = 0; i < HASHNUM; ++i){
            SymbolItem *item = sTable->bucket[i];
            while(item){
                if(item->kind == FunK){
                    printf("| %10s (function)\n", item->name);
                }else
                    printf("| %10s\n", item->name);
                item = item->next;
            }
        }
        printf("\n");
    }
}