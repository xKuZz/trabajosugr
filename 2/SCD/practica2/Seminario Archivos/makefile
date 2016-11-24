
.SUFFIXES:
.PHONY: msg, 1, 2, mu

msg:
	@echo "usa 'make 1' para compilar y ejecutar el programa del primer ejemplo."
	@echo "usa 'make 2' para compilar y ejecutar el programa del segundo ejemplo."
	@echo "usa 'make mu' para compilar y ejecutar el programa de las hebras contadoras de múltiplos"
	@echo "usa 'make clean' para borrar todos los archivos creados al compilar."


1: Principal1.class TipoHebra.class
	java Principal1 100

2: Principal2.class Dormilona.class
	java Principal2 10 50 3

mu: Contador.class Hebra.class Multiplos.class
	java Multiplos

Principal1.class TipoHebra.class: Principal1.java
	javac Principal1.java

Principal2.class Dormilona.class: Principal2.java
	javac Principal2.java


Contador.class Hebra.class Multiplos.class: Multiplos.java
	javac Multiplos.java

clean:
	rm -f *.class
