main:	lex.yy.c C_Minus.tab.c util.c symtab.c analyze.c main.c
	gcc -g lex.yy.c C_Minus.tab.c symtab.c analyze.c util.c main.c -o main

C_Minus.tab.h: C_Minus.tab.c
	echo "C_Minus.tab.h was created at the same time as C_Minus.tab.c"

C_Minus.tab.c: C_Minus.y
	bison -dv C_Minus.y

lex.yy.c: C_Minus.l C_Minus.tab.h
	flex C_Minus.l

clean:
	rm -f main lex.yy.c C_Minus.tab.h C_Minus.tab.c