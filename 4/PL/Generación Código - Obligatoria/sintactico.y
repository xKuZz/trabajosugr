%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "generacion.h"
	#include "semantico.h"
	extern int yylex(void);
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

%right OP_TERNARIO1

%left OP_RELACIONAL_OR
%left OP_RELACIONAL_AND
%left OP_RELACIONAL_IGUALDAD
%left OP_RELACIONAL
%left MAS_MENOS
%left OP_BINARIO
%left ARROBA
%right OP_UNARIO








%%
programa : PRINCIPAL {escribirLibrerias();} bloque;

bloque : ABRE_LLAVE {insertarMarca(); abrirBloque();}
	     declar_de_variables_locales 
	     declar_de_subprogs 
	     sentencias 
	     CIERRA_LLAVE {vaciarEntradas(); cerrarBloque();};

declar_de_subprogs : declar_de_subprogs declar_subprograma | ;

declar_subprograma : cabecera_subprograma {subProg = 1;} 
					 bloque {subProg = 0;};

declar_de_variables_locales : DECLARACION variables_locales FINDECLARACION {if (!hay_principal) introducirMain();}
							| {if (!hay_principal) introducirMain();};

variables_locales : variables_locales cuerpo_declar_variables | cuerpo_declar_variables ;

cuerpo_declar_variables : tipo_t {declararTipo($1);} lista_id PUNTO_COMA {escribirPuntoYComa();}| error;

lista_id : IDENTIFICADOR {insertarIdentificador($1); declararVariable($1);} 
         | lista_id COMA IDENTIFICADOR {insertarIdentificador($3);  escribirComa(); declararVariable($3);} 
         | lista_id error IDENTIFICADOR;

cabecera_subprograma : tipo_t IDENTIFICADOR {insertarFuncion($2);} ABRE_PAREN lista_parametros CIERRA_PAREN ;

lista_parametros : parametro | lista_parametros COMA parametro | lista_parametros error IDENTIFICADOR |;

parametro : tipo_t IDENTIFICADOR {insertarParametros($2);};

sentencias : sentencias sentencia | sentencia;

sentencia : bloque | sentencia_asignacion | sentencia_if | sentencia_while | sentencia_entrada | sentencia_salida | sentencia_repeat_until 
			| sentencia_return_comienzo_lista | avanzar_retroceder_lista;

sentencia_asignacion : IDENTIFICADOR ASIGNACION expresion PUNTO_COMA { comprobarAsignacion($1, $3); generarAsignacion($1, $3);};

condicion_if : SI ABRE_PAREN expresion CIERRA_PAREN {comprobarBooleanoLoop($3); addATabla($3); emitirSaltoElse(); abrirBloque();};

sentencia_if : condicion_if sentencia {cerrarBloque(); escribirEtiquetaElse(); quitarDeTabla();} |
			   condicion_if sentencia SINO {cerrarBloque(); emitirSaltoSalida(); escribirEtiquetaElse(); abrirBloque(); }sentencia {cerrarBloque(); escribirEtiquetaSalida(); quitarDeTabla(); };

sentencia_while: MIENTRAS {addATablaWhileRepeat($1);  escribirEtiquetaEntrada(); abrirBloque();} ABRE_PAREN expresion CIERRA_PAREN {comprobarBooleanoLoop($4); escribirNombreExpresionControl($4); saltoSalidaWhile();} sentencia {saltoEntradaWhileRepeat(); cerrarBloque(); escribirEtiquetaSalida(); quitarDeTabla();};

sentencia_entrada: LEER lista_leer PUNTO_COMA;

lista_leer: IDENTIFICADOR {leer($1);}  | lista_leer COMA IDENTIFICADOR {leer($3);} | lista_leer error IDENTIFICADOR;

sentencia_salida: ESCRIBIR lista_expresiones_o_cadena PUNTO_COMA;

lista_expresiones_o_cadena: expr_cad | lista_expresiones_o_cadena COMA expr_cad;

expr_cad: expresion {escribir($1);} | CADENA {escribir($1);};

sentencia_repeat_until : REPETIR {addATablaWhileRepeat($1); escribirEtiquetaEntrada(); abrirBloque();} sentencia HASTA ABRE_PAREN expresion CIERRA_PAREN PUNTO_COMA {comprobarBooleanoLoop($6); escribirNombreExpresionControl($6); saltoSalidaRepeat(); saltoEntradaWhileRepeat(); cerrarBloque(); escribirEtiquetaSalida(); quitarDeTabla();};

sentencia_return_comienzo_lista: DEVOLVER_DOLAR expresion PUNTO_COMA {comprobarReturnDolar($1,$2);};

avanzar_retroceder_lista: expresion DESPLAZA PUNTO_COMA { comprobarTipoDesplaza($2, $1); };

expresion: ABRE_PAREN expresion CIERRA_PAREN {$$.tipo = $2.tipo; $$.tipo_interno = $2.tipo_interno;}
		 | MAS_MENOS expresion %prec OP_UNARIO {comprobarTipoUnarioMasMenos($1, $2, &$$); generarUnario($1, $2, &$$);}
		 | OP_UNARIO expresion {comprobarTipoUnario($1, $2, &$$);}
		 | expresion OP_TERNARIO1 expresion ARROBA expresion %prec OP_TERNARIO1 {comprobarTipoTernario($1, $3, $5, &$$);}
		 | expresion ARROBA expresion %prec OP_BINARIO {comprobarTipoArroba($1, $3, &$$); generarBinario($2, $1, $3, &$$);}
		 | expresion OP_BINARIO expresion {comprobarTipoBinario($2, $1, $3, &$$); generarBinario($2, $1, $3, &$$);}
		 | expresion OP_RELACIONAL_IGUALDAD expresion {comprobarTipoIgualdad($2, $1, $3, &$$); generarBinario($2, $1, $3, &$$);}
		 | expresion OP_RELACIONAL_AND expresion {comprobarTipoAnd($1, $3, &$$); generarBinario($2, $1, $3, &$$);}
		 | expresion OP_RELACIONAL_OR expresion {comprobarTipoOr($1, $3, &$$); generarBinario($2, $1, $3, &$$);}
		 | expresion OP_RELACIONAL expresion {comprobarTipoRelacional($2, $1, $3, &$$); generarBinario($2, $1, $3, &$$);}
		 | expresion MAS_MENOS expresion %prec OP_BINARIO {comprobarTipoMasMenos($2, $1, $3, &$$); generarBinario($2, $1, $3, &$$);}
		 | IDENTIFICADOR {asignarTipoIdentificador($1, &$$); }
		 | CONSTANTE {$$.tipo = $1.tipo; $$.tipo_interno = $1.tipo_interno;}
		 | funcion {$$.tipo = $1.tipo; $$.tipo_interno = $1.tipo_interno; }
		 | agregado_lista {$$.tipo = $1.tipo; $$.tipo_interno = $1.tipo_interno;}
		 | error {$$.tipo = error;};

funcion : IDENTIFICADOR ABRE_PAREN lista_f CIERRA_PAREN {comprobarFuncion($1, &$$); limpiarMarcaFuncion();}
		| IDENTIFICADOR ABRE_PAREN CIERRA_PAREN {insertarMarcaFuncion(); comprobarFuncion($1, &$$); limpiarMarcaFuncion();};

tipo_t: TIPO {TipoTmp = $1.tipo;} | LISTA_DE TIPO {TipoTmp = $1.tipo; TipoTmp2 = $2.tipo;};

agregado_lista : ABRE_CORCHETE lista CIERRA_CORCHETE {$$.tipo = $2.tipo; $$.tipo_interno = $2.tipo_interno;};

lista_f : expresion {insertarMarcaFuncion(); guardarParametro($1);} | lista_f COMA expresion {guardarParametro($3);}

lista : expresion 
        {if ($1.tipo == lista) {
        	$$.tipo = error;
        	printf("[ERROR SEMÁNTICO] Línea %d: No se pueden tener listas de listas.\n", yylineno);
         }
         else {
         	$$.tipo = lista;
         	$$.tipo_interno = $1.tipo;
         }
	    }
	 | lista COMA expresion 
	 { 
	 	if ($3.tipo == lista)  {
	 		$$.tipo = error;
        	printf("[ERROR SEMÁNTICO] Línea %d: No se pueden tener listas de listas.\n", yylineno);
	 	}
	 	else if ($3.tipo == $1.tipo_interno)  {
	 		$$.tipo = lista;
	 		$$.tipo_interno = $3.tipo;
	 	}
	 	else {
	 		$$.tipo = error;
	 		printf("[ERROR SEMÁNTICO] Línea %d: No coinciden los tipos del agregado de la lista.\n", yylineno);
	 	}

	 };

%%

#include "lex.yy.c"

void yyerror(const char *msg) {
	printf("[ERROR SINTÁCTICO] Línea %d: %s\n\n", yylineno, msg);
}

