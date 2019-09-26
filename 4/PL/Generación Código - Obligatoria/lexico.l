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
">>" { yylval.atrib = 0; return DESPLAZA;}
"<<" { yylval.atrib = 1; return DESPLAZA;}
"$" {  yylval.atrib = 0; return DEVOLVER_DOLAR;}
"devolver" { yylval.atrib = 1; return DEVOLVER_DOLAR;}
"repetir" {  return REPETIR;}
"hasta" {  return HASTA; }
"=" {  return ASIGNACION;}
"si" {  return SI;}
"sino" {  return SINO;}
"mientras" { return MIENTRAS;}
"leer" {  return LEER;}
"escribir" { return ESCRIBIR;}
"#" { yylval.atrib = 0; yylval.lexema=strdup(yytext); return OP_UNARIO;}
"?" { yylval.atrib = 1; yylval.lexema=strdup(yytext); return OP_UNARIO;}
"!" { yylval.atrib = 2; yylval.lexema=strdup(yytext); return OP_UNARIO;}
"+" { yylval.atrib = 1; yylval.lexema=strdup(yytext); return MAS_MENOS;}
"-" { yylval.atrib = 0; yylval.lexema=strdup(yytext); return MAS_MENOS;}
"*" { yylval.atrib = 0; yylval.lexema=strdup(yytext); return OP_BINARIO;}
"/" { yylval.atrib = 1; yylval.lexema=strdup(yytext); return OP_BINARIO;}
"%" { yylval.atrib = 2; yylval.lexema=strdup(yytext); return OP_BINARIO;}
"**" { yylval.atrib = 3; yylval.lexema=strdup(yytext); return OP_BINARIO;}
"--" { yylval.atrib = 4; yylval.lexema=strdup(yytext); return OP_BINARIO;}
"==" { yylval.atrib = 0; yylval.lexema=strdup(yytext); return OP_RELACIONAL_IGUALDAD;}
"!=" { yylval.atrib = 1; yylval.lexema=strdup(yytext); return OP_RELACIONAL_IGUALDAD;}
"<" { yylval.atrib = 0; yylval.lexema=strdup(yytext); return OP_RELACIONAL;}
">" { yylval.atrib = 1; yylval.lexema=strdup(yytext); return OP_RELACIONAL;}
"<=" { yylval.atrib = 2; yylval.lexema=strdup(yytext); return OP_RELACIONAL;}
">=" { yylval.atrib = 3; yylval.lexema=strdup(yytext); return OP_RELACIONAL;}
"&&" { return OP_RELACIONAL_AND; yylval.lexema=strdup(yytext); }
"||" { return OP_RELACIONAL_OR; yylval.lexema=strdup(yytext); }
"++" { return OP_TERNARIO1; yylval.lexema=strdup(yytext); }
"@" { return ARROBA; yylval.lexema=strdup(yytext); }
"lista de" { yylval.tipo = lista; return LISTA_DE;}
"entero" { yylval.tipo = entero; yylval.atrib = 0; return TIPO;}
"booleano" { yylval.tipo = booleano; yylval.atrib = 1; return TIPO;}
"real" { yylval.tipo = real; yylval.atrib = 2; return TIPO;}
"caracter" { yylval.tipo = caracter; yylval.atrib = 3; return TIPO;}
[0-9]+ { yylval.atrib = 0; yylval.tipo = entero; yylval.lexema = strdup(yytext); return CONSTANTE;}
\'[^\']\' { yylval.atrib = 1; yylval.tipo = caracter; yylval.lexema = strdup(yytext); return CONSTANTE;}
[0-9]+"."[0-9]+ { yylval.atrib = 2; yylval.tipo = real; yylval.lexema = strdup(yytext); return CONSTANTE;}
"V" { yylval.atrib = 3; yylval.tipo = booleano; yylval.lexema = "V"; return CONSTANTE;}
"F" { yylval.atrib = 4; yylval.tipo = booleano; yylval.lexema = "F"; return CONSTANTE;}
\"[^\"]+\" { yylval.lexema = strdup(yytext); yylval.tipo = cadena; return CADENA; }
"," { return COMA;}
"[" { return ABRE_CORCHETE;}
"]" { return CIERRA_CORCHETE;}
([a-z]|[A-Z])([a-z]|[A-Z]|[0-9])* { yylval.lexema = strdup(yytext); return IDENTIFICADOR;}
"\n" {++yylineno;}
"//".* {}
[ \t ] ;
. {printf("[ERROR LÉXICO] Línea %d\n\n", yylineno);}

%%
