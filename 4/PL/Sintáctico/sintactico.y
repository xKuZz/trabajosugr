%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>

	void yyerror(const char * msg);
	#define YYDEBUG 1
	#define YYERROR_VERBOSE
%}

%error-verbose	


%token DECLARACION
%token FINDECLARACION
%token PRINCIPAL
%token ABRE_LLAVE
%token CIERRA_LLAVE
%token PUNTO_COMA
%token ABRE_PAREN
%token CIERRA_PAREN
%token DESPLAZA
%token DEVOLVER_DOLAR
%token REPETIR
%token HASTA
%token ASIGNACION
%token SI
%token SINO
%token MIENTRAS
%token LEER
%token ESCRIBIR
%token LISTA_DE
%token TIPO
%token CONSTANTE
%token IDENTIFICADOR
%token CADENA
%token COMA
%token ABRE_CORCHETE
%token CIERRA_CORCHETE

%right ARROBA
%left OP_RELACIONAL_OR
%left OP_RELACIONAL_AND
%left OP_RELACIONAL_IGUALDAD
%left OP_RELACIONAL
%left MAS_MENOS
%left OP_BINARIO
%right OP_UNARIO
%left OP_TERNARIO1






%%
programa : PRINCIPAL bloque;

bloque : ABRE_LLAVE declar_de_variables_locales declar_de_subprogs sentencias CIERRA_LLAVE;

declar_de_subprogs : declar_de_subprogs declar_subprograma | ;

declar_subprograma : cabecera_subprograma bloque;

declar_de_variables_locales : DECLARACION variables_locales FINDECLARACION | ;

variables_locales : variables_locales cuerpo_declar_variables | cuerpo_declar_variables ;

cuerpo_declar_variables : tipo_t lista_id PUNTO_COMA | error;

lista_id : IDENTIFICADOR | lista_id COMA IDENTIFICADOR | lista_id error IDENTIFICADOR;

cabecera_subprograma : tipo_t IDENTIFICADOR ABRE_PAREN lista_parametros CIERRA_PAREN;

lista_parametros : parametro | lista_parametros COMA parametro | lista_paremetros error IDENTIFICADOR |;

parametro : tipo_t IDENTIFICADOR;

sentencias : sentencias sentencia | sentencia;

sentencia : bloque | sentencia_asignacion | sentencia_if | sentencia_while | sentencia_entrada | sentencia_salida | sentencia_repeat_until 
			| sentencia_return_comienzo_lista | avanzar_retroceder_lista;

sentencia_asignacion : IDENTIFICADOR ASIGNACION expresion PUNTO_COMA;

sentencia_if : SI ABRE_PAREN expresion CIERRA_PAREN sentencia |
			   SI ABRE_PAREN expresion CIERRA_PAREN sentencia SINO sentencia;

sentencia_while: MIENTRAS ABRE_PAREN expresion CIERRA_PAREN sentencia;

sentencia_entrada: LEER lista_id PUNTO_COMA;

sentencia_salida: ESCRIBIR lista_expresiones_o_cadena PUNTO_COMA;

lista_expresiones_o_cadena: expr_cad | lista_expresiones_o_cadena COMA expr_cad;

expr_cad: expresion | CADENA;

sentencia_repeat_until : REPETIR sentencia HASTA ABRE_PAREN expresion CIERRA_PAREN PUNTO_COMA;

sentencia_return_comienzo_lista: DEVOLVER_DOLAR expresion PUNTO_COMA;

avanzar_retroceder_lista: expresion DESPLAZA PUNTO_COMA;

expresion: ABRE_PAREN expresion CIERRA_PAREN
		 | MAS_MENOS expresion %prec OP_UNARIO
		 | OP_UNARIO expresion 
		 | expresion OP_BINARIO expresion
		 | expresion OP_RELACIONAL_IGUALDAD expresion
		 | expresion OP_RELACIONAL_AND expresion
		 | expresion OP_RELACIONAL_OR expresion
		 | expresion OP_RELACIONAL expresion
		 | expresion OP_TERNARIO1 expresion ARROBA expresion
		 | expresion ARROBA expresion %prec OP_BINARIO
		 | expresion MAS_MENOS expresion %prec OP_BINARIO
		 | IDENTIFICADOR 
		 | CONSTANTE
		 | funcion
		 | agregado_lista
		 | error;

funcion : IDENTIFICADOR ABRE_PAREN lista CIERRA_PAREN
		| IDENTIFICADOR ABRE_PAREN CIERRA_PAREN;

tipo_t: TIPO | LISTA_DE TIPO;

agregado_lista : ABRE_CORCHETE lista CIERRA_CORCHETE;

lista : expresion | lista COMA expresion;

%%

#include "lex.yy.c"

void yyerror(const char *msg) {
	printf("[Línea %d]: %s\n", yylineno, msg);
}

