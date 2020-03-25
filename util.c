#include "util.h"

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

    return res;
}

char * copyString(char *str){
    char *temp = (char *)malloc((strlen(str)+1) * sizeof(char));
    return strcpy(temp, str);
}

static int treeLevel = 0;

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
                printf("var-declaration\n");
                break;
            case FunK:
                printf("fun-declaration\n");
                break;
        }
    }else if(node->nodeKind == ExpK){
        switch(node->kind.exp){
            case OpK:
                printf("op: %s\n", tokenTrans(node->attr.op));
                break;
            case IdK:
                printf("id: %s\n", node->attr.name);
                break;
        }
    }
}

void printSpaces(){
    int i;
    for(i = 0; i < treeLevel; ++i){
        putchar(' ');
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
    }
}