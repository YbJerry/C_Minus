#include "cgen.h"

// 符号表中存储的数据区变量
extern int location;

// 数据区临时变量堆栈偏移量
int tempOffset = 0;

void decGen(TreeNode *tree){
    int savedCodeLoc, savedDataLoc, currentCodeLoc;
    switch (tree->kind.dec)
    {
    case VarK:
        insertSymbol(tree, 0, 0, location);
        if(tree->type == Array){
            // 如果数组声明只是int a[]类型的(作为函数形参),只保存地址
            if(tree->child[0] == NULL){
                location++;
            }else{
                location += tree->child[0]->attr.val;
            }
        }else{
            location++;
        }
        break;
    case FunK:
        currentCodeLoc = emitSkip(0);
        savedDataLoc = location;
        insertSymbol(tree, 0, 0, currentCodeLoc);
        // codeGen(tree->child[0]);
        TreeNode *t = tree->child[0];
        while(t){
            searchSymbolAll(t->attr.name);
        }
        codeGen(tree->child[1]);
        location = savedDataLoc;
        break;
    default:
        break;
    }
}

void expGen(TreeNode *tree){
    int dataLoc, codeLoc;
    switch (tree->kind.exp)
    {
    case OpK:
        // 注意压栈顺序
        cGen(tree->child[0]);
        emitRM("ST", ac, tempOffset--, mp, "op: push left");
        cGen(tree->child[1]);
        emitRM("LD", ac1, ++tempOffset, mp, "op: load left");
        switch (tree->attr.op) {
            case PLUS:
                emitRO("ADD",ac,ac1,ac,"op +");
                break;
            case MINUS:
                emitRO("SUB",ac,ac1,ac,"op -");
                break;
            case TIMES:
                emitRO("MUL",ac,ac1,ac,"op *");
                break;
            case DIVIDE:
                emitRO("DIV",ac,ac1,ac,"op /");
                break;
            case LT:
                emitRO("SUB",ac,ac1,ac,"op <") ;
                emitRM("JLT",ac,2,pc,"br if true") ;
                emitRM("LDC",ac,0,ac,"false case") ;
                emitRM("LDA",pc,1,pc,"unconditional jmp") ;
                emitRM("LDC",ac,1,ac,"true case") ;
                break;
            case LEQ:
                emitRO("SUB",ac,ac1,ac,"op <=") ;
                emitRM("JLE",ac,2,pc,"br if true") ;
                emitRM("LDC",ac,0,ac,"false case") ;
                emitRM("LDA",pc,1,pc,"unconditional jmp") ;
                emitRM("LDC",ac,1,ac,"true case") ;
                break;
            case GT:
                emitRO("SUB",ac,ac1,ac,"op >") ;
                emitRM("JGT",ac,2,pc,"br if true") ;
                emitRM("LDC",ac,0,ac,"false case") ;
                emitRM("LDA",pc,1,pc,"unconditional jmp") ;
                emitRM("LDC",ac,1,ac,"true case") ;
                break;
            case GEQ:
                emitRO("SUB",ac,ac1,ac,"op >=") ;
                emitRM("JGE",ac,2,pc,"br if true") ;
                emitRM("LDC",ac,0,ac,"false case") ;
                emitRM("LDA",pc,1,pc,"unconditional jmp") ;
                emitRM("LDC",ac,1,ac,"true case") ;
                break;
            case EQ:
                emitRO("SUB",ac,ac1,ac,"op ==") ;
                emitRM("JEQ",ac,2,pc,"br if true");
                emitRM("LDC",ac,0,ac,"false case") ;
                emitRM("LDA",pc,1,pc,"unconditional jmp") ;
                emitRM("LDC",ac,1,ac,"true case") ;
                break;
            case NEQ:
                emitRO("SUB",ac,ac1,ac,"op !=") ;
                emitRM("JNE",ac,2,pc,"br if true") ;
                emitRM("LDC",ac,0,ac,"false case") ;
                emitRM("LDA",pc,1,pc,"unconditional jmp") ;
                emitRM("LDC",ac,1,ac,"true case") ;
                break;
            default:
                emitComment("BUG: Unknown operator");
                break;
         }
        break;
    case IdK:
        dataLoc = searchSymbolAll(tree->attr.name)->loc;
        emitRM("LD", ac, dataLoc, gp, "load id value");
        break;
    case NumK:
        emitRM("LDC", ac, tree->attr.val, 0, "load const");
        break;
    case CallK:
        codeLoc = searchSymbolAll(tree->attr.name)->loc;
        
        break;
    default:
        break;
    }
}

void stmGen(TreeNode *tree){
    
}

void codeGen(TreeNode *tree){
    if(!tree)
        return;
    switch (tree->nodeKind)
    {
    case StmK:
        stmGen(tree);
        break;
    case ExpK:
        expGen(tree);
        break;
    case DecK:
        decGen(tree);
        break;
    // 复合语句，直接忽略
    case ComK:
    default:
        break;
    }
    codeGen(tree->sibling);
}

// 此处代码直接copy了《编译原理与实践》中Tiny语言的部分
// 由于只是简单的初始化以及结束，所以没有自己写
void codeGen(TreeNode * syntaxTree, char * codefile)
{  char * s = malloc(strlen(codefile)+7);
   strcpy(s,"File: ");
   strcat(s,codefile);
   emitComment("TINY Compilation to TM Code");
   emitComment(s);
   /* generate standard prelude */
   emitComment("Standard prelude:");
   emitRM("LD",mp,0,ac,"load maxaddress from location 0");
   emitRM("ST",ac,0,ac,"clear location 0");
   emitComment("End of standard prelude.");
   /* generate code for TINY program */
   cGen(syntaxTree);
   /* finish */
   emitComment("End of execution.");
   emitRO("HALT",0,0,0,"");
}