#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#define MAXCHILDNUM 3

typedef int TokenType;
typedef enum {StmK, ExpK, DecK} NodeKind;
typedef enum {IfK, WhileK, ReturnK, CompoundK} StmKind;
typedef enum {OpK, IdK} ExpKind;
typedef enum {VarK, FunK} DecKind;
typedef enum {Int, Void, Array} ExpType;

typedef struct treeNode TreeNode;
struct treeNode{
    TreeNode * child[MAXCHILDNUM];
    TreeNode * sibling;
    NodeKind nodeKind;
    union{StmKind stm; ExpKind exp; DecKind dec;} kind;
    union{
        TokenType op;
        int val;
        char *name;
        void *address;
    }attr;
    ExpType type;
};

#endif