#ifndef _UTIL_H_
#define _UTIL_H_

#include "globals.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef YYTOKENTYPE
#include "C_Minus.tab.h"
#endif

TreeNode * newStmNode(StmKind kind);
TreeNode * newExpNode(ExpKind kind);
TreeNode * newDecNode(DecKind kind);
char * tokenTrans(TokenType op);

char * copyString(char *str);

void printTree(TreeNode *tree);
void printNode(TreeNode *node);
void printSpaces();

#endif