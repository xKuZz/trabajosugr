#include "generacion.h"

FILE* archivo_compilado;
int hay_principal = 0;
int contador_temporales = 0;
int contador_etiquetas = 0;

void escribirLibrerias() {
	fprintf(archivo_compilado, "#include <stdlib.h>\n#include <stdio.h>\n#include <stdbool.h>\n");
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

	// TO-DO: Parte optativa: añadir listas
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

	// 2. La declaramos
	declararTipo(exp1);
	fprintf(archivo_compilado, "%s;\n",  variable);
    fprintf(archivo_compilado, "%s = %s %s %s;\n", variable, exp1.lexema, op.lexema, exp2.lexema);
	exp->lexema = variable;
}

void generarUnario(atributos op, atributos exp1, atributos* exp) {
	char* variable = temporal();

	declararTipo(exp1);
	fprintf(archivo_compilado, "%s; \n", variable);
	fprintf(archivo_compilado, "%s = %s%s", variable, op.lexema, exp1.lexema);
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