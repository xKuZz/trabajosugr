%{
#include "y.tab.h"

%}

%%
"declaracion" { ECHO; return DECLARACION;}
"findeclaracion" { ECHO; return FINDECLARACION;}
"principal" { ECHO; return PRINCIPAL;}
"{" { ECHO; return ABRE_LLAVE;}
"}" { ECHO; return CIERRA_LLAVE;}
";" {ECHO; return PUNTO_COMA;}
"(" { ECHO; return ABRE_PAREN;}
")" { ECHO; return CIERRA_PAREN;}
">>" { ECHO; return DESPLAZA;}
"<<" { ECHO; return DESPLAZA;}
"$" { ECHO; return DEVOLVER_DOLAR;}
"devolver" { ECHO; return DEVOLVER_DOLAR;}
"repetir" { ECHO; return REPETIR;}
"hasta" { ECHO; return HASTA; }
"=" { ECHO; return ASIGNACION;}
"si" { ECHO; return SI;}
"sino" { ECHO; return SINO;}
"mientras" {ECHO; return MIENTRAS;}
"leer" { ECHO; return LEER;}
"escribir" {ECHO; return ESCRIBIR;}
"#" {ECHO; return OP_UNARIO;}
"?" {ECHO; return OP_UNARIO;}
"!" {ECHO; return OP_UNARIO;}
"+" {ECHO; return MAS_MENOS;}
"-" {ECHO; return MAS_MENOS;}
"*" {ECHO; return OP_BINARIO;}
"/" {ECHO; return OP_BINARIO;}
"%" {ECHO; return OP_BINARIO;}
"**" {ECHO; return OP_BINARIO;}
"--" {ECHO; return OP_BINARIO;}
"==" {ECHO; return OP_BINARIO;}
"!=" {ECHO; return OP_BINARIO;}
"<" {ECHO; return OP_BINARIO;}
">" {ECHO; return OP_BINARIO;}
"<=" {ECHO; return OP_BINARIO;}
">=" {ECHO; return OP_BINARIO;}
"&&" {ECHO; return OP_BINARIO;}
"||" {ECHO; return OP_BINARIO;}
"^" {ECHO; return OP_BINARIO;}
"++" {ECHO; return OP_TERNARIO1;}
"@" {ECHO; return OP_TERNARIO2;}
"lista de" {ECHO; return LISTA_DE;}
"entero" {ECHO; return TIPO;}
"booleano" {ECHO; return TIPO;}
"real" {ECHO; return TIPO;}
"caracter" {ECHO; return TIPO;}
[0-9]+ {ECHO; return CONSTANTE;}
\'[^\']\' {ECHO; return CONSTANTE;}
[0-9]+"."[0-9]+ {ECHO; return CONSTANTE;}
"V" {ECHO; return CONSTANTE;}
"F" {ECHO; return CONSTANTE;}
([a-z]|[A-Z])([a-z]|[A-Z]|[0-9])* {ECHO; return IDENTIFICADOR;}
\"[^\"]+\" {ECHO; return CADENA;}
"," {ECHO; return COMA;}
"[" {ECHO; return ABRE_CORCHETE;}
"]" {ECHO; return CIERRA_CORCHETE;}
"\n" {++yylineno;}
[ \t ] ;
. {printf("Error léxico en la línea número %d\n", yylineno);}

%%
int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Formato: <nombre programa> <archivo entrada> <archivo salida>");
        exit(-1);
    }

    yyin = fopen(argv[1], "r");
    yyout = fopen(argv[2], "w");

    int val;
    do {
        val = yylex();
        printf("%d\n", val);
    } while (val != 0);
}
