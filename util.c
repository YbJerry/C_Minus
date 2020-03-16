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
    char *temp = (char *)malloc(strlen(str) * sizeof(char));
    return strcpy(temp, str);
}