
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "semantico.h"

extern FILE* archivo_compilado;
extern FILE* aux;
extern int hay_principal;
extern int contador_temporales;
extern int contador_etiquetas;
extern int contador_subprogramas;

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
void generarTernario(atributos lista, atributos valor, atributos posicion);
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

void generarListaTemporal(atributos expresion, atributos* lista);
void addValorALista(atributos lista, atributos valor);
void comienzolista(atributos lista);
void moverposicionlista(atributos op, atributos lista);
void cambiarAArchivoFunciones();
void volverAArchivoCompilado();
void ponerCabeceraFuncion(atributos tipo, atributos id);
void sentenciareturn(atributos id);

void ampliarLexema(atributos lex_original, atributos ampliacion, atributos* resultado);