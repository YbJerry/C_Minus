#ifndef _ANALYZE_H_
#define _ANALYZE_H_

#include <stdio.h>
#include <stdlib.h>
#include "symtab.h"
#include "util.h"

void buildSymbolTable(TreeNode *tree);
void typeCheck(TreeNode *tree);
void typeError(char *message, TreeNode *tree);

#endif