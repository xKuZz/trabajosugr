
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef enum {
	marca, /* marca comienzo bloque */
	funcion, /* si es subprograma */
	variable, /* si es variable */
	parametro_formal, /* si es parametro formal */
} tipoEntrada ;

typedef enum {
    error,
	entero,
	real,
	caracter,
	booleano,
	lista,
	desconocido,
	no_asignado
} dtipo ;

typedef struct {
	tipoEntrada entrada ;
	char* nombre ;
	dtipo tipoDato ;
    dtipo tipoInterno;
	unsigned int parametros ;
	unsigned int dimensiones ;
} entradaTS ;


typedef struct {
        tipoEntrada entrada;
        dtipo tipo;
        dtipo tipo_interno; 
} tipoParametros;

#define MAX_TS 500
#define MAX_PARAMETROS 20
extern unsigned int TOPE, TOPE_PARAMS; /* Tope de la pila */
extern unsigned int subProg; /* Indicador de comienzo de bloque de un subprog */
extern entradaTS TS[MAX_TS] ; /* Pila de la tabla de símbolos */
extern tipoParametros listaParametros[MAX_PARAMETROS];
extern dtipo TipoTmp, TipoTmp2;
extern int yylineno;

typedef struct {
	int atrib ; /* Atributo del símbolo (si tiene) */
	char *lexema ; /* Nombre del lexema */
	dtipo tipo ; /* Tipo del símbolo */
    dtipo tipo_interno;
} atributos ;
#define YYSTYPE atributos /* A partir de ahora, cada símbolo tiene */
/* una estructura de tipo atributos */



void comprobarTamPila();

void insertarIdentificador(atributos atr);

void insertarID(atributos atr, tipoEntrada tipo);

long int buscarMarca();

long int encontrarIdentificador(char* nombre, long int posicionMarca);

void insertarMarca();

void vaciarEntradas();

void insertarFuncion(atributos atrib);

void insertarParametros(atributos atrib);

void comprobarBooleanoLoop(atributos atrib);

void comprobarTipoUnario(atributos op, atributos atrib, atributos* expresion);

void comprobarTipoUnarioMasMenos(atributos op, atributos atrib, atributos* expresion);

void comprobarTipoBinario(atributos op, atributos expr1, atributos expr2, atributos* expresion);

void comprobarTipoIgualdad(atributos op, atributos expr1, atributos expr2, atributos* expresion);

void comprobarTipoAnd(atributos expr1, atributos expr2, atributos* expresion);

void comprobarTipoOr(atributos expr1, atributos expr2, atributos *expresion);

void comprobarTipoRelacional(atributos op, atributos expr1, atributos expr2, atributos* expresion);

void comprobarTipoTernario(atributos expr1, atributos expr2, atributos expr3, atributos *expresion);

void comprobarTipoArroba(atributos expr1, atributos expr2, atributos *expresion);

void comprobarTipoMasMenos(atributos op, atributos expr1, atributos expr2, atributos* expresion);

void asignarTipoIdentificador(atributos identificador, atributos* expresion);

void comprobarAsignacion(atributos identificador, atributos expresion);

void comprobarTipoDesplaza(atributos operador, atributos expresion);
/** COMPROBAR FUNCIONES**/

void insertarMarcaFuncion();

void limpiarMarcaFuncion();

void comprobarFuncion(atributos identificador, atributos *expresion);

void guardarParametro(atributos parametro);

void comprobarReturnDolar(atributos operador, atributos parametro);

/** IMPRIMIR DATOS **/
void printTipo(dtipo tipo);

char* getTipo(dtipo tipo, dtipo tipo_interno);

char* getAtribTipo(atributos atrib);

char* getIDTipo(int pos);

void ImprimirTablaSimbolos();

