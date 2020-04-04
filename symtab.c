#include "symtab.h"

SymbolTable *symbolTables = NULL;

int hash(char *name){
    int h = 0;
    while(*name){
        h = ((h << SHIFT) + (*(name++))) % HASHNUM;
    }
    return h;
}

void newSymbolTable(TreeNode *node){
    SymbolTable *t = (SymbolTable *)malloc(sizeof(SymbolTable));
    memset(t, 0, sizeof(SymbolTable));
    t->next = symbolTables;
    symbolTables = t;

    if(!node)
        return;

    char *name = node->attr.name;
    if(name){
        t->name = (char *)malloc(sizeof(name));
        strcpy(t->name, name);
    }
    t->resType = node->type;

    TreeNode *p = node->child[0];
    ArgsLink *arg = NULL;
    while(p){
        ArgsLink *newArg = (ArgsLink *) malloc(sizeof(ArgsLink));
        newArg->type = p->type;
        newArg->next = arg;
        arg = newArg;
        p = p->sibling;
    }
    t->argsType = arg;
}

void delSymbolTable(){
    SymbolTable *t = symbolTables;
    symbolTables = symbolTables->next;
    free(t);
}

void insertSymbol(TreeNode *node){
    if(!node){
        return;
    }
    char *name = node->attr.name;
    if(!searchSymbolNow(name, symbolTables)){
        int h = hash(name);
        SymbolItem *t = (SymbolItem *)malloc(sizeof(SymbolItem));
        t->name = (char *)malloc(strlen(name) * sizeof(char));
        strcpy(t->name, name);
        t->next = symbolTables->bucket[h];
        symbolTables->bucket[h] = t;
    }
}

// 搜索全部作用域中的某符号
int searchSymbolAll(char *name){
    SymbolTable *t = symbolTables;
    while(t){
        searchSymbolNow(name, t);
    }
    return 0;
}

// 搜索指定作用域中的某符号
int searchSymbolNow(char *name, SymbolTable *sTable){
    int h = hash(name);
    SymbolItem *item = sTable->bucket[h];
    while(item){
        if(!strcmp(name, item->name)){
            return 1;
        }
        item = item->next;
    }
    return 0;
}

char *searchRegionName(){
    SymbolTable *t = symbolTables;
    while(t){
        if(t->name){ 
            return t->name;
        }
        t = t->next;
    }
    return NULL;
}