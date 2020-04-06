#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"

#define HASHNUM 211
#define SHIFT 4

typedef struct symbolTable SymbolTable;
typedef struct symbolItem SymbolItem;
typedef struct lineLink LineLink;
typedef struct argsLink ArgsLink;

extern SymbolTable *symbolTables;

struct lineLink{
    int lineNo;
    LineLink *next;
};

struct symbolItem{
    char *name;
    DecKind kind;
    ExpType type;
    ArgsLink *argsType;
    LineLink lines;
    SymbolItem *next;
};

struct argsLink{
    ExpType type;
    struct argsLink *next;
};

struct symbolTable{
    char *name;
    ExpType resType;
    ArgsLink *argsType;
    SymbolTable *next;
    SymbolItem *bucket[HASHNUM];
};

int hash(char *name);
void newSymbolTable(TreeNode *node);
void delSymbolTable();
void insertSymbol(TreeNode *node);
SymbolItem *searchSymbolAll(char *name);
SymbolItem *searchSymbolNow(char *name, SymbolTable *sTable);
char *returnRegionName();
SymbolTable *searchRegionName(char *name);

#endif