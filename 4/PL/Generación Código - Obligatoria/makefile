generacion: main.o y.tab.o semantico.o generacion.o
	gcc -g -o generacion main.o y.tab.o semantico.o generacion.o -lfl

semantico.o: semantico.c semantico.h
	gcc -g -c semantico.c -o semantico.o

generacion.o: generacion.c generacion.h
	gcc -g -c generacion.c -o generacion.o

y.tab.o: y.tab.c
	gcc -g -c y.tab.c -lfl

main.o: main.c
	gcc -g -c main.c -o main.o -lfl

y.tab.c: sintactico.y lex.yy.c
	bison -v -Wconflicts-sr -Wconflicts-rr -o y.tab.c sintactico.y

lex.yy.c: lexico.l
	lex lexico.l

limpia: 
	rm -f semantico main.o y.tab.o y.tab.c lex.yy.c

todo: 
	make limpia
	make generacion