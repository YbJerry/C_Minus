#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#define MAXCHILDNUM 3
#define MAX_TOKEN_LEN 50

typedef int TokenType;
typedef enum {StmK, ExpK, DecK, ComK} NodeKind;
typedef enum {IfK, WhileK, ReturnK, CompoundK} StmKind;
typedef enum {OpK, IdK, NumK, CallK} ExpKind;
typedef enum {VarK, FunK} DecKind;
typedef enum {Int, Void, Array} ExpType;

typedef struct _pos Pos;
struct _pos {
    int lineNo;
    int charNo;
};

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
    Pos pos;
};

typedef struct _TokenStringStack TokenStringStack;
struct _TokenStringStack{
    char tokenString[MAX_TOKEN_LEN+1];
    TokenStringStack *next;
};

#endif