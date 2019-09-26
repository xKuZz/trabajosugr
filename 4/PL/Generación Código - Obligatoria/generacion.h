
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "semantico.h"

extern FILE* archivo_compilado;
extern int hay_principal;
extern int contador_temporales;
extern int contador_etiquetas;


void escribirLibrerias();
void abrirBloque();
void cerrarBloque();
void declararTipo(atributos tipo);
void declararVariable(atributos variable);
void escribirComa();
void escribirPuntoYComa();
void introducirMain();

void generarAsignacion(atributos id, atributos exp);

void generarIDoConst(atributos atrib);
void generarBinario(atributos op, atributos exp1, atributos exp2, atributos* exp);
void generarUnario(atributos op, atributos exp1, atributos* exp);
void escribir(atributos expresion);
void leer(atributos expresion);

void addATabla(atributos expresion);
int encontrarUltimoControl();
void emitirSaltoElse();
void emitirSaltoSalida();
void escribirEtiquetaElse();
void escribirEtiquetaSalida();
void quitarDeTabla();

void addATablaWhileRepeat(atributos expresion);
void escribirEtiquetaEntrada();
void saltoSalidaWhile();
void saltoEntradaWhileRepeat();
void saltoSalidaRepeat();
void escribirNombreExpresionControl(atributos expresion);
char* temporal();
char* etiqueta();