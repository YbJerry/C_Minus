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

    // TreeNode *p = node->child[0];
    // if(p){
    //     t->argsType = (ArgsLink *) malloc(sizeof(ArgsLink));
    //     t->argsType->type = p->type;
    //     t->argsType->next = NULL;
    //     p = p->sibling;
    //     ArgsLink *arg = t->argsType;

    //     while(p){
    //         arg->next = (ArgsLink *) malloc(sizeof(ArgsLink));
    //         arg = arg->next;
    //         arg->type = p->type;
    //         arg->next = NULL;
    //         p = p->sibling;
    //     }
    // }
}

void delSymbolTable(){
    SymbolTable *t = symbolTables;
    symbolTables = symbolTables->next;
    ArgsLink *arg = t->argsType;
    while(arg){
        t->argsType = t->argsType->next;
        free(arg);
        arg = t->argsType;
    }
    free(t);
}

void insertSymbol(TreeNode *node, int lineNo, int charNo, int loc){
    if(!node){
        return;
    }
    char *name = node->attr.name;
    if(!searchSymbolNow(name, symbolTables)){
        int h = hash(name);
        SymbolItem *t = (SymbolItem *)malloc(sizeof(SymbolItem));
        t->name = (char *)malloc(strlen(name) * sizeof(char));
        strcpy(t->name, name);
        t->argsType = NULL;
        t->kind = VarK;
        t->type = node->type;
        t->loc = loc;
        t->next = symbolTables->bucket[h];
        symbolTables->bucket[h] = t;

        if(node->nodeKind == DecK && node->kind.dec == FunK){
            t->kind = FunK;
            TreeNode *p = node->child[0];
            if(p){
                t->argsType = (ArgsLink *) malloc(sizeof(ArgsLink));
                t->argsType->type = p->type;
                t->argsType->next = NULL;
                p = p->sibling;
                ArgsLink *arg = t->argsType;

                while(p){
                    arg->next = (ArgsLink *) malloc(sizeof(ArgsLink));
                    arg = arg->next;
                    arg->type = p->type;
                    arg->next = NULL;
                    p = p->sibling;
                }
            }
        }
    }
}

// 搜索全部作用域中的某符号
SymbolItem * searchSymbolAll(char *name){
    SymbolTable *t = symbolTables;
    SymbolItem *res = NULL;
    while(t){
        if(res = searchSymbolNow(name, t))
            return res;
        t = t->next;
    }
    return NULL;
}

// 搜索指定作用域中的某符号
SymbolItem * searchSymbolNow(char *name, SymbolTable *sTable){
    int h = hash(name);
    SymbolItem *item = sTable->bucket[h];
    while(item){
        if(!strcmp(name, item->name)){
            return item;
        }
        item = item->next;
    }
    return NULL;
}

char *returnRegionName(){
    SymbolTable *t = symbolTables;
    while(t){
        if(t->name){ 
            return t->name;
        }
        t = t->next;
    }
    return NULL;
}

SymbolTable *searchRegionName(char *name){
    SymbolTable *t = symbolTables;
    while(t){
        if(t->name && !strcmp(t->name, name)){ 
            return t;
        }
        t = t->next;
    }
    return NULL;
}