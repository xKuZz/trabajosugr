#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
extern FILE* archivo_compilado;

int yyparse(void);

FILE *abrir_entrada(int argc, char *argv[] )
{
FILE *f = NULL;
if (argc == 3) 
{
	f = fopen(argv[1], "r");
	if (f==NULL)
	{
		fprintf(stderr, "fichero ´%s´ no encontrado\n", argv[1]);
		exit(1);
	} else
		printf("leyendo fichero ´%s´.\n", argv[1]);

	archivo_compilado = fopen(argv[2], "w");
	if (archivo_compilado==NULL)
	{
		fprintf(stderr, "fichero ´%s´ no se puede escribir\n", argv[2]);
		exit(1);
	} else
		printf("escribiendo fichero ´%s´.\n", argv[2]);
}
else {
	printf("Formato: ./generacion <archivo_entrada> <archivo_salida>\n");
	exit(1);
}

return f;
}

int main( int argc, char *argv[1])
{
	yyin = abrir_entrada(argc, argv);

	return yyparse();
}
