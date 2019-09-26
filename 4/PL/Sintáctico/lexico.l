%{


%}

%%
"declaracion" {  return DECLARACION;}
"findeclaracion" {  return FINDECLARACION;}
"principal" {  return PRINCIPAL;}
"{" {  return ABRE_LLAVE;}
"}" {  return CIERRA_LLAVE;}
";" { return PUNTO_COMA;}
"(" {  return ABRE_PAREN;}
")" {  return CIERRA_PAREN;}
">>" {  return DESPLAZA;}
"<<" {  return DESPLAZA;}
"$" {  return DEVOLVER_DOLAR;}
"devolver" {  return DEVOLVER_DOLAR;}
"repetir" {  return REPETIR;}
"hasta" {  return HASTA; }
"=" {  return ASIGNACION;}
"si" {  return SI;}
"sino" {  return SINO;}
"mientras" { return MIENTRAS;}
"leer" {  return LEER;}
"escribir" { return ESCRIBIR;}
"#" { return OP_UNARIO;}
"?" { return OP_UNARIO;}
"!" { return OP_UNARIO;}
"+" { return MAS_MENOS;}
"-" { return MAS_MENOS;}
"*" { return OP_BINARIO;}
"/" { return OP_BINARIO;}
"%" { return OP_BINARIO;}
"**" { return OP_BINARIO;}
"--" { return OP_BINARIO;}
"==" { return OP_RELACIONAL_IGUALDAD;}
"!=" { return OP_RELACIONAL_IGUALDAD;}
"<" { return OP_RELACIONAL;}
">" { return OP_RELACIONAL;}
"<=" { return OP_RELACIONAL;}
">=" { return OP_RELACIONAL;}
"&&" { return OP_RELACIONAL_AND;}
"||" { return OP_RELACIONAL_OR;}
"^" { return OP_BINARIO;}
"++" { return OP_TERNARIO1;}
"@" { return ARROBA;}
"lista de" { return LISTA_DE;}
"entero" { return TIPO;}
"booleano" { return TIPO;}
"real" { return TIPO;}
"caracter" { return TIPO;}
[0-9]+ { return CONSTANTE;}
\'[^\']\' { return CONSTANTE;}
[0-9]+"."[0-9]+ { return CONSTANTE;}
"V" { return CONSTANTE;}
"F" { return CONSTANTE;}
\"[^\"]+\" { return CADENA;}
"," { return COMA;}
"[" { return ABRE_CORCHETE;}
"]" { return CIERRA_CORCHETE;}
([a-z]|[A-Z])([a-z]|[A-Z]|[0-9])* { return IDENTIFICADOR;}
"\n" {++yylineno;}
[ \t ] ;
. {printf("Error léxico en la línea número %d\n", yylineno);}

%%