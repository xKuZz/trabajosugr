sintactico: main.o y.tab.o
	gcc -o sintactico main.o y.tab.o -lfl

y.tab.o: y.tab.c
	gcc -c y.tab.c -lfl

main.o: main.c
	gcc -c main.c -lfl

y.tab.c: sintactico.y lex.yy.c
	bison -v -Wconflicts-sr -Wconflicts-rr -o y.tab.c sintactico.y

lex.yy.c: lexico.l
	lex lexico.l

limpia: 
	rm -f sintactico main.o y.tab.o y.tab.c lex.yy.c

todo: 
	reset
	make limpia
	make sintactico
