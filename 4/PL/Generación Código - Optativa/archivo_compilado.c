#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "dec_dat"
#include "dec_fun"
Lista lalista;
int main() {
Lista temp6 = inicializar();
temp6.tipo_lista = entero;
EntradaLista temp7;
temp7.entero = 1;
temp6 = add_elemento_posicion(&temp6, temp7, longitud(&temp6));
EntradaLista temp8;
temp8.entero = 2;
temp6 = add_elemento_posicion(&temp6, temp8, longitud(&temp6));
EntradaLista temp9;
temp9.entero = 3;
temp6 = add_elemento_posicion(&temp6, temp9, longitud(&temp6));
EntradaLista temp10;
temp10.entero = 4;
temp6 = add_elemento_posicion(&temp6, temp10, longitud(&temp6));
EntradaLista temp11;
temp11.entero = 5;
temp6 = add_elemento_posicion(&temp6, temp11, longitud(&temp6));
EntradaLista temp12;
temp12.entero = 6;
temp6 = add_elemento_posicion(&temp6, temp12, longitud(&temp6));
lalista = temp6;
printf("%s", "La sumatoria de los elementos de la lista es: ");
printf("%d", sumarLista(lalista));
printf("%s", "\n");
retroceder(&lalista);
printf("%s", "El penúltimo elemento de lista es: ");
EntradaLista temp14;
temp14 = elemento_actual(&lalista);
int temp13; 
temp13 = temp14.entero;
printf("%d", temp13);
printf("%s", "\n");
printf("%s", "El elemento en la posición 2 de la lista es: ");
int temp15;
EntradaLista temp16;
temp16 = elemento_posicion(&lalista, 2);
temp15 = temp16.entero;
printf("%d", temp15);
printf("%s", "\n");
printf("%s", "Si añadimos al final de lista un 7 nos queda: ");
int temp17 = longitud(&lalista);
EntradaLista temp18;
temp18.entero = 7;
lalista = add_elemento_posicion(&lalista, temp18, temp17);
escribir(&lalista);
printf("%s", "\n");
}
