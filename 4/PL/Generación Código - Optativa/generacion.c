#include "generacion.h"

FILE* archivo_compilado;
FILE* aux;
int hay_principal = 0;
int contador_temporales = 0;
int contador_etiquetas = 0;
int contador_subprogramas = 0;

void escribirLibrerias() {
	fprintf(archivo_compilado, "#include <stdlib.h>\n#include <stdio.h>\n#include <stdbool.h>\n#include \"dec_dat\"\n#include \"dec_fun\"\n");
}

void abrirBloque() {
	if (hay_principal)
		fprintf(archivo_compilado, " {\n");
}
void cerrarBloque() {
	fprintf(archivo_compilado, "}\n");
}

void declararTipo(atributos tip) {
	dtipo tipo = tip.tipo;
	if (tipo == entero) {
		fprintf(archivo_compilado, "int ");
	}
	else if (tipo == booleano) {
		fprintf(archivo_compilado, "bool ");
	}
	else if (tipo == real) {
		fprintf(archivo_compilado, "float ");
	}
	else if (tipo == caracter) {
		fprintf(archivo_compilado, "char ");
	}
	else if (tipo == lista) {
		fprintf(archivo_compilado, "Lista ");
	}
}

void declararVariable(atributos variable) {
	fprintf(archivo_compilado, "%s", variable.lexema);
}
void escribirComa() {
	fprintf(archivo_compilado, ", ");
}
void escribirPuntoYComa() {
	fprintf(archivo_compilado, ";\n");
}

void introducirMain(){
	fprintf(archivo_compilado, "int main() {\n");
	hay_principal = 1;
}

char* temporal() {
	char* nombre = malloc(8*sizeof(char)) ;
	sprintf(nombre, "temp%d", contador_temporales);
	++contador_temporales;
	return nombre;
}

void generarAsignacion(atributos id, atributos exp) {
	fprintf(archivo_compilado, "%s = %s;\n", id.lexema, exp.lexema);
}
void generarIDoConst(atributos atrib) {
	fprintf(archivo_compilado, "%s", atrib.lexema);
}

void generarBinario(atributos op, atributos exp1, atributos exp2, atributos* exp) {
	// 1. Cogemos la siguiente variable temporal
	char* variable = temporal();

	
	if (strcmp(op.lexema, "--") == 0) {
		// Borra de una posición de una lista
		declararTipo(exp1);
		fprintf(archivo_compilado, "%s;\n",  variable);
		fprintf(archivo_compilado, "%s = borrar_elemento_posicion(&%s, %s);\n", variable, exp1.lexema, exp2.lexema);
	}
	else if (strcmp(op.lexema, "%") == 0) {
		// Borra de una lista a partir de la posición.
		declararTipo(exp1);
		fprintf(archivo_compilado, "%s;\n",  variable);
		fprintf(archivo_compilado, "%s = borrar_lista_posicion(&%s, %s);\n", variable, exp1.lexema, exp2.lexema);
	}
	else if (strcmp(op.lexema, "**") == 0) {
		// Concatena dos listas
		declararTipo(exp1);
		fprintf(archivo_compilado, "%s;\n",  variable);
		fprintf(archivo_compilado, "%s = concatenar_listas(&%s, &%s);\n", variable, exp1.lexema, exp2.lexema);
	}
	else if (strcmp(op.lexema, "@") == 0) {
		// Devuelve el elemento en una posición
		atributos aux;
		aux.tipo = exp1.tipo_interno;
		declararTipo(aux);
		char* entradalista = temporal();
		fprintf(archivo_compilado, "%s;\n",  variable);
		fprintf(archivo_compilado, "EntradaLista %s;\n",  entradalista);
		fprintf(archivo_compilado, "%s = elemento_posicion(&%s, %s);\n", entradalista, exp1.lexema, exp2.lexema);
		fprintf(archivo_compilado, "%s = %s.%s;\n", variable, entradalista, getTipo(exp1.tipo_interno, real));
	}
	else if (strcmp(op.lexema, "+")==0 && exp1.tipo == lista && exp1.tipo_interno == exp2.tipo) {
		declararTipo(exp1);
		fprintf(archivo_compilado, "%s;\n",  variable);
		char* entradalista = temporal();
		fprintf(archivo_compilado, "EntradaLista %s;\n",  entradalista);
		char* tipo = getTipo(exp2.tipo, real);
		fprintf(archivo_compilado, "%s.%s = %s;\n", entradalista, tipo, exp2.lexema);
		fprintf(archivo_compilado, "%s = sumar(&%s, %s);\n", variable, exp1.lexema, entradalista);
	}
	else if (strcmp(op.lexema, "+")==0 && exp2.tipo == lista && exp2.tipo_interno == exp1.tipo) {
		declararTipo(exp2);
		fprintf(archivo_compilado, "%s;\n",  variable);
		char* entradalista = temporal();
		fprintf(archivo_compilado, "EntradaLista %s;\n",  entradalista);
		char* tipo = getTipo(exp1.tipo, real);
		fprintf(archivo_compilado, "%s.%s = %s;\n", entradalista, tipo, exp1.lexema);
		fprintf(archivo_compilado, "%s = sumar(&%s, %s);\n", variable, exp2.lexema, entradalista);
	}
	else if (strcmp(op.lexema, "*")==0 && exp1.tipo == lista && exp1.tipo_interno == exp2.tipo) {
		declararTipo(exp1);
		fprintf(archivo_compilado, "%s;\n",  variable);
		char* entradalista = temporal();
		fprintf(archivo_compilado, "EntradaLista %s;\n",  entradalista);
		char* tipo = getTipo(exp2.tipo, real);
		fprintf(archivo_compilado, "%s.%s = %s;\n", entradalista, tipo, exp2.lexema);
		fprintf(archivo_compilado, "%s = multiplicar(&%s, %s);\n", variable, exp1.lexema, entradalista);
	}
	else if (strcmp(op.lexema, "*")==0 && exp2.tipo == lista && exp2.tipo_interno == exp1.tipo) {
		declararTipo(exp2);
		fprintf(archivo_compilado, "%s;\n",  variable);
		char* entradalista = temporal();
		fprintf(archivo_compilado, "EntradaLista %s;\n",  entradalista);
		char* tipo = getTipo(exp1.tipo, real);
		fprintf(archivo_compilado, "%s.%s = %s;\n", entradalista, tipo, exp1.lexema);
		fprintf(archivo_compilado, "%s = multiplicar(&%s, %s);\n", variable, exp2.lexema, entradalista);
	}
	else if (strcmp(op.lexema, "-")==0 && exp1.tipo == lista && exp1.tipo_interno == exp2.tipo) {
		declararTipo(exp1);
		fprintf(archivo_compilado, "%s;\n",  variable);
		char* entradalista = temporal();
		fprintf(archivo_compilado, "EntradaLista %s;\n",  entradalista);
		char* tipo = getTipo(exp2.tipo, real);
		fprintf(archivo_compilado, "%s.%s = %s;\n", entradalista, tipo, exp2.lexema);
		fprintf(archivo_compilado, "%s = restar(&%s, %s);\n", variable, exp1.lexema, entradalista);
	}
	else if (strcmp(op.lexema, "/")==0 && exp1.tipo == lista && exp1.tipo_interno == exp2.tipo) {
		declararTipo(exp1);
		fprintf(archivo_compilado, "%s;\n",  variable);
		char* entradalista = temporal();
		fprintf(archivo_compilado, "EntradaLista %s;\n",  entradalista);
		char* tipo = getTipo(exp2.tipo, real);
		fprintf(archivo_compilado, "%s.%s = %s;\n", entradalista, tipo, exp2.lexema);
		fprintf(archivo_compilado, "%s = dividir(&%s, %s);\n", variable, exp1.lexema, entradalista);
	}
	else {
		declararTipo(exp1);
		fprintf(archivo_compilado, "%s;\n",  variable);
    	fprintf(archivo_compilado, "%s = %s %s %s;\n", variable, exp1.lexema, op.lexema, exp2.lexema);
    }
	exp->lexema = variable;

}

void generarUnario(atributos op, atributos exp1, atributos* exp) {
	char* variable = temporal();
	if (strcmp(op.lexema, "#") == 0) {
		fprintf(archivo_compilado, "int %s = longitud(&%s);\n", variable, exp1.lexema);
	}
	else if (strcmp(op.lexema, "?") == 0) {
		char* entradalista = temporal();
		fprintf(archivo_compilado, "EntradaLista %s;\n", entradalista);
		fprintf(archivo_compilado, "%s = elemento_actual(&%s);\n", entradalista, exp1.lexema);
		atributos aux;
		aux.tipo = exp1.tipo_interno;
		declararTipo(aux);
		fprintf(archivo_compilado, "%s; \n", variable);
		fprintf(archivo_compilado, "%s = %s.%s;\n", variable, entradalista, getTipo(exp1.tipo_interno, real));

	}
	else {
		declararTipo(exp1);
		fprintf(archivo_compilado, "%s; \n", variable);
		fprintf(archivo_compilado, "%s = %s%s", variable, op.lexema, exp1.lexema);
	}
	exp->lexema = variable;
}

void escribir(atributos expresion) {
	if (expresion.tipo == cadena) {
		fprintf(archivo_compilado, "printf(\"%%s\", %s);\n", expresion.lexema);
	}
	else if (expresion.tipo == entero || expresion.tipo == booleano) {
		fprintf(archivo_compilado, "printf(\"%%d\", %s);\n", expresion.lexema);
	}
	else if (expresion.tipo ==  caracter) {
		fprintf(archivo_compilado, "printf(\"%%c\", %s);\n", expresion.lexema);
	}
	else if (expresion.tipo == real) {
		fprintf(archivo_compilado, "printf(\"%%f\", %s);\n", expresion.lexema);
	}
	else if (expresion.tipo == lista) {
		fprintf(archivo_compilado, "escribir(&%s);\n", expresion.lexema);
	}
}

void leer(atributos expresion) {
	int pos = encontrarIdentificador(expresion.lexema, 0);
	dtipo tipo = TS[pos].tipoDato;
	if (tipo == cadena) {
		fprintf(archivo_compilado, "scanf(\"%%s\", &%s);\n", expresion.lexema);
	}
	else if (tipo == entero || tipo == booleano) {
		fprintf(archivo_compilado, "scanf(\"%%d\", &%s);\n", expresion.lexema);
	}
	else if (tipo ==  caracter) {
		fprintf(archivo_compilado, "scanf(\"%%c\", &%s);\n", expresion.lexema);
	}
	else if (tipo == real) {
		fprintf(archivo_compilado, "scanf(\"%%f\", &%s);\n", expresion.lexema);
	}
}

char* etiqueta() {
	char* nombre = malloc(11*sizeof(char)) ;
	sprintf(nombre, "etiqueta%d", contador_etiquetas);
	++contador_etiquetas;
	return nombre;
}

void addATabla(atributos expresion) {
	DescriptorDeInstrControl control;
	control.NombreVarControl = expresion.lexema;
	control.EtiquetaElse = etiqueta();
	control.EtiquetaSalida = etiqueta();

	TS[TOPE].entrada = instruccionControl;
	TS[TOPE].control = control;
	++TOPE;
}

int encontrarUltimoControl() {
	int i = TOPE-1;
	for (; TS[i].entrada != instruccionControl; --i);
	return i;
}
void emitirSaltoElse() {
	// Recogemos el último control de la tabla de símbolos
	int pos = encontrarUltimoControl();
	fprintf(archivo_compilado, "if (!%s) goto %s;\n", TS[pos].control.NombreVarControl,
			TS[pos].control.EtiquetaElse);
}

void emitirSaltoSalida() {
	int pos = encontrarUltimoControl();
	fprintf(archivo_compilado, "goto %s;\n", TS[pos].control.EtiquetaSalida);
}


void escribirEtiquetaElse() {
	int pos = encontrarUltimoControl();
	fprintf(archivo_compilado, "%s:\n;\n", TS[pos].control.EtiquetaElse);
}
void escribirEtiquetaSalida() {
	int pos = encontrarUltimoControl();
	fprintf(archivo_compilado, "%s:\n;\n", TS[pos].control.EtiquetaSalida);
}
void quitarDeTabla() {
	int pos = encontrarUltimoControl();
	TOPE = pos;
}

void addATablaWhileRepeat(atributos expresion) {
	DescriptorDeInstrControl control;
	control.NombreVarControl = expresion.lexema;
	control.EtiquetaEntrada = etiqueta();
	control.EtiquetaSalida = etiqueta();

	TS[TOPE].entrada = instruccionControl;
	TS[TOPE].control = control;
	++TOPE;
}

void escribirEtiquetaEntrada() {
	int pos = encontrarUltimoControl();
	fprintf(archivo_compilado, "%s:\n;\n", TS[pos].control.EtiquetaEntrada);
}

void saltoSalidaWhile() {
	int pos = encontrarUltimoControl();
	fprintf(archivo_compilado, "if (!%s) goto %s;\n", TS[pos].control.NombreVarControl,
			TS[pos].control.EtiquetaSalida);
}

void saltoSalidaRepeat() {
	int pos = encontrarUltimoControl();
	fprintf(archivo_compilado, "if (%s) goto %s;\n", TS[pos].control.NombreVarControl,
			TS[pos].control.EtiquetaSalida);
}

void saltoEntradaWhileRepeat() {
	int pos = encontrarUltimoControl();
	fprintf(archivo_compilado, "goto %s;\n", TS[pos].control.EtiquetaEntrada);
}

void escribirNombreExpresionControl(atributos expresion) {
	int pos = encontrarUltimoControl();
	TS[pos].control.NombreVarControl = expresion.lexema;
}

void generarListaTemporal(atributos expresion, atributos* lista) {
	char* nombre = temporal();
	char* nombre2 = temporal();
	char* tipo = getTipo(expresion.tipo, real);
	fprintf(archivo_compilado, "Lista %s = inicializar();\n", nombre);
	//fprintf(archivo_compilado, "inicializar(&%s);\n", nombre);
	fprintf(archivo_compilado, "%s.tipo_lista = %s;\n", nombre, tipo);
	fprintf(archivo_compilado, "EntradaLista %s;\n", nombre2);
	fprintf(archivo_compilado, "%s.%s = %s;\n", nombre2, tipo, expresion.lexema);
	fprintf(archivo_compilado, "%s = add_elemento_posicion(&%s, %s, longitud(&%s));\n", nombre, nombre, nombre2, nombre);
	lista->lexema = nombre;
}

void addValorALista(atributos lista, atributos valor) {
	char* nombre = temporal();
	char* tipo = getTipo(valor.tipo, real);
	fprintf(archivo_compilado, "EntradaLista %s;\n", nombre);
	fprintf(archivo_compilado, "%s.%s = %s;\n", nombre, tipo, valor.lexema);
	fprintf(archivo_compilado, "%s = add_elemento_posicion(&%s, %s, longitud(&%s));\n", lista.lexema, lista.lexema, nombre, lista.lexema);
}

void comienzolista(atributos lista) {
	fprintf(archivo_compilado, "comienzo(&%s);\n",lista.lexema);
}

void moverposicionlista(atributos op, atributos lista) {
	if (op.atrib == 0)
		fprintf(archivo_compilado, "avanzar(&%s);\n",lista.lexema);
	else
		fprintf(archivo_compilado, "retroceder(&%s);\n",lista.lexema);

}

void cambiarAArchivoFunciones() {
	if (contador_subprogramas == 1) {
		aux = archivo_compilado;
		archivo_compilado = fopen("dec_fun", "a");
	}
}


void volverAArchivoCompilado() {
	if (contador_subprogramas == 0) {
		archivo_compilado = aux;
	}
}

void ponerCabeceraFuncion(atributos tipo, atributos id) {
	declararTipo(tipo);
	fprintf(archivo_compilado, "%s(", id.lexema);
}

void sentenciareturn(atributos id) {
	fprintf(archivo_compilado, "return %s;\n", id.lexema);
}

void ampliarLexema(atributos lex_original, atributos ampliacion, atributos* resultado){
	char* original = lex_original.lexema;
	char* amp = ampliacion.lexema;
	resultado->lexema = (char*) malloc((strlen(original) + strlen(amp))*sizeof(char));
	strcpy(resultado->lexema, original);
	strcat(resultado->lexema, amp);
}

void generarTernario(atributos lista, atributos valor, atributos posicion) {
	char* nombre = temporal();
	char* tipo = getTipo(valor.tipo, real);
	fprintf(archivo_compilado, "EntradaLista %s;\n", nombre);
	fprintf(archivo_compilado, "%s.%s = %s;\n", nombre, tipo, valor.lexema);
	fprintf(archivo_compilado, "%s = add_elemento_posicion(&%s, %s, %s);\n", lista.lexema, lista.lexema, nombre, posicion.lexema);
}