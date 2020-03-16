#ifndef _UTIL_H_
#define _UTIL_H_

#include "globals.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

TreeNode * newStmNode(StmKind kind);
TreeNode * newExpNode(ExpKind kind);
TreeNode * newDecNode(DecKind kind);

char * copyString(char *str);

#endif