#include "dec_dat"

int main() {
	Lista l;
	inicializar(&l);
	EntradaLista valor;
	valor.entero = 2;
	l = add_elemento_posicion(&l, valor, 0);
	escribir(&l);
}