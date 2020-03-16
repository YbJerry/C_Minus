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
    }
}

void printSpaces(){
    int i;
    for(i = 0; i < treeLevel; ++i){
        putchar(' ');
    }
}