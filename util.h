#ifndef _UTIL_H_
#define _UTIL_H_

#ifndef YYTOKENTYPE
#include "C_Minus.tab.h"
#endif

#include "globals.h"
#include "symtab.h"
#include "analyze.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TreeNode * newStmNode(StmKind kind);
TreeNode * newExpNode(ExpKind kind);
TreeNode * newDecNode(DecKind kind);
char * tokenTrans(TokenType op);

char * copyString(char *str);

void printTree(TreeNode *tree);
void printNode(TreeNode *node);
void printSpaces();
void printSymbolTable(SymbolTable *sTable);

ExpType judgeType(TreeNode *node);

#endif