#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHNUM 211
#define SHIFT 4

typedef struct symbolTable SymbolTable;
typedef struct symbolItem SymbolItem;
typedef struct lineLink LineLink;

extern SymbolTable *symbolTables;

struct lineLink{
    int lineNo;
    LineLink *next;
};

struct symbolItem{
    char *name;
    LineLink lines;
    SymbolItem *next;
};

struct symbolTable{
    SymbolTable *next;
    SymbolItem *bucket[HASHNUM];
};

int hash(char *name);
void newSymbolTable();
void delSymbolTable();
void insertSymbol(char *name);
int searchSymbolAll(char *name);
int searchSymbolNow(char *name, SymbolTable *sTable);

#endif