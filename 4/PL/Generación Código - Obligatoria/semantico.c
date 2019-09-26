#include "semantico.h"
unsigned int TOPE = 0; /* Tope de la pila */
unsigned int subProg = 0; /* Indicador de comienzo de bloque de un subprog */
entradaTS TS[MAX_TS] ; /* Pila de la tabla de símbolos */
tipoParametros listaParametros[MAX_PARAMETROS];
unsigned int TOPE_PARAMS = 0;
dtipo TipoTmp = desconocido;
dtipo TipoTmp2 = desconocido;


void comprobarTamPila(){
	// Si la pila está llena
	if (TOPE + 1 > MAX_TS) {
        printf("[ERROR] La pila se ha llenado.\n\n");
		exit(-1);
	}
}

void insertarIdentificador(atributos atr) {
	insertarID(atr, variable);
}

void insertarID(atributos atr, tipoEntrada tip) {
	// Si no hay marca
	long int posicionMarca = buscarMarca();


	// Si el identificador está duplicado
	long int posicionIdentificadorDuplicado = encontrarIdentificador(atr.lexema, buscarMarca());
	if (posicionIdentificadorDuplicado != -1) {
        printf("[ERROR SEMÁNTICO] Línea %d: El identificador %s había sido declarado "
            "previamente en el ámbito del bloque.\n\n", yylineno, atr.lexema);
	}
	else {
		// Insertamos el identificador
		TS[TOPE].entrada = tip;
		TS[TOPE].nombre = (char*) malloc(strlen(atr.lexema) * sizeof(char));
		strcpy(TS[TOPE].nombre, atr.lexema);
		TS[TOPE].tipoDato = TipoTmp;
        if (TipoTmp == lista)
            TS[TOPE].tipoInterno = TipoTmp2;
        else
            TS[TOPE].tipoInterno = desconocido;
		TS[TOPE].parametros = 0;
		TS[TOPE].dimensiones = 0;
		++TOPE;
	}
}

long int buscarMarca() {
	int i;
    for (i = TOPE - 1; TS[i].entrada != marca && i > -1; --i);
	if (i == -1){
        printf("[ERROR - TABLA DE SÍMBOLOS] No se ha encontrado la marca.\n\n");
    }
	return i;
}

long int encontrarIdentificador(char* nombre, long int posicionMarca) {
	long int posicion_final;
    posicion_final = posicionMarca;
	for (int posicion = TOPE-1; posicion >=posicion_final; --posicion) {
        if (TS[posicion].nombre != NULL && strcmp(nombre, TS[posicion].nombre) == 0) {
			return posicion;
        }
	}
	return -1;
}

void insertarMarca() {
	comprobarTamPila();
	TS[TOPE].entrada = marca;
    TS[TOPE].nombre = "";
    TS[TOPE].tipoDato = no_asignado;
    TS[TOPE].tipoInterno = no_asignado;
    TS[TOPE].parametros = 0;
    TS[TOPE].dimensiones = 0;
	++TOPE;
	if (subProg == 1) {
		int posicion;
        for (posicion = TOPE - 2; TS[posicion].entrada != funcion && posicion > -1; --posicion);
		if (posicion == -1) {
            printf("[Error] La función no ha sido declarada.\n\n");
			return;
		}
		else {
			long int LIMITE = TOPE - 1;
			for (int i = posicion; i < LIMITE; ++i){
				if (TS[i].entrada == parametro_formal) {
					comprobarTamPila();
					TS[TOPE].entrada = variable;
					TS[TOPE].nombre = (char*) malloc(strlen(TS[i].nombre)*sizeof(char));
					strcpy(TS[TOPE].nombre,TS[i].nombre);
					TS[TOPE].tipoDato = TS[i].tipoDato;
                    TS[TOPE].tipoInterno = TS[i].tipoInterno;
					TS[TOPE].parametros = TS[i].parametros;
					TS[TOPE].dimensiones = TS[i].dimensiones;
					++TOPE;
				}

			}
		}
	}
	
}

void vaciarEntradas() {
	int posicion = buscarMarca();
	TOPE = posicion;
    //ImprimirTablaSimbolos();
}

void insertarFuncion(atributos atrib) {
	insertarID(atrib, funcion);
}

void insertarParametros(atributos atrib) {
	comprobarTamPila();

	// Buscamos el subpgroma correspondiente
	int posicion;
    for (posicion = TOPE -1; TS[posicion].entrada != funcion && posicion > -1; --posicion);
	if (encontrarIdentificador(atrib.lexema,posicion) != -1) {
		printf("[ERROR SEMÁNTICO] Línea %d: El parámetro %s ha sido declarado previamente "
         "como otro parámetro de la función %s.\n\n", yylineno, atrib.lexema, TS[posicion].nombre);
	}
	++TS[posicion].parametros;
	TS[TOPE].entrada = parametro_formal;
	TS[TOPE].nombre = (char*) malloc(strlen(atrib.lexema)*sizeof(char));
	strcpy(TS[TOPE].nombre,atrib.lexema);
	TS[TOPE].tipoDato = TipoTmp;
    if (TipoTmp == lista)
        TS[TOPE].tipoInterno = TipoTmp2;
    else
        TS[TOPE].tipoInterno = desconocido;
	TS[TOPE].parametros = 0;
	TS[TOPE].dimensiones = 0;
	++TOPE;
					

}

void comprobarBooleanoLoop(atributos atrib) {
    if (atrib.tipo != booleano) {
        printf("[ERROR SEMÁNTICO] Línea %d: La condición debe de ser una expresión booleana.\n\n", yylineno);
    }
}
void comprobarTipoUnario(atributos op, atributos atrib, atributos *expresion)
{
    if (op.atrib == 0) {
        if (atrib.tipo != lista) {
            printf("[ERROR SEMÁNTICO] Línea %d: El operador unario # debe ir seguido de una lista.\n", yylineno);
            printf("                  Tipo proporcionado: %s\n\n", getAtribTipo(atrib));
            expresion->tipo = error;
        }
        else
            expresion->tipo = entero;
    }
    else if (op.atrib == 1) {
        if (atrib.tipo != lista) {
            printf("[ERROR SEMÁNTICO] Línea %d: El operador unario # debe ir seguido de una lista.\n", yylineno);
            printf("                  Tipo proporcionado: %s\n\n", getAtribTipo(atrib));
            expresion->tipo = error;
        }
        else {
            expresion->tipo = atrib.tipo_interno;
        }
    }
    else if (op.atrib == 2) {
        if (atrib.tipo != booleano) {
            printf("[ERROR SEMÁNTICO] Línea %d: El operador unario ! debe ir seguido de una condición booleana.\n", yylineno);
            printf("                  Tipo proporcionado: %s\n\n", getAtribTipo(atrib));
            expresion->tipo = error;
        }
        else
            expresion->tipo = booleano;
    }
}


void comprobarTipoUnarioMasMenos(atributos op, atributos atrib, atributos *expresion)
{
    if (op.atrib == 0 && atrib.tipo != entero && atrib.tipo != real) {
        printf("[ERROR SEMÁNTICO] Línea %d: El operador unario - debe ir seguido de un entero o un real.\n",yylineno);
        printf("                  Tipo proporcionado: %s\n\n", getAtribTipo(atrib));
        expresion->tipo = error;
    }
    else if (op.atrib == 1 && atrib.tipo != entero && atrib.tipo != real) {
        printf("[ERROR SEMÁNTICO] Línea %d: El operador unario + debe ir seguido de un entero o un real.\n", yylineno);
        printf("                  Tipo proporcionado: %s\n\n", getAtribTipo(atrib));
        expresion->tipo = error;

    }
    else
        expresion->tipo = atrib.tipo;

}

void comprobarTipoBinario(atributos op, atributos expr1, atributos expr2, atributos *expresion)
{
    if (op.atrib == 0) {
        if (expr1.tipo != lista & expr1.tipo == expr2.tipo && expr1.tipo != booleano) {
            expresion->tipo == expr1.tipo;
        }
        else  {
            if ((expr1.tipo == lista && expr2.tipo != lista && expr2.tipo == expr1.tipo_interno && expr2.tipo != booleano) ||
                (expr2.tipo == lista && expr1.tipo != lista && expr1.tipo == expr2.tipo_interno && expr1.tipo != booleano)) {
                expresion->tipo = lista;
                return;
            }

            printf("[ERROR SEMÁNTICO] Línea %d: Operandos de multiplicación inválidos\n"
                   "                  Se pueden multiplicar todos los tipos elementales excepto booleanos.\n"
                   "                  Se puede multiplicar lista (no de booleanos) con su tipo de valor interno.\n"
                   "                  Se puede multiplicar tipo de valor interno con lista(no de booleanos).\n", yylineno);
            printf("                  Tipo proporcionado: %s * %s\n\n", getAtribTipo(expr1), getAtribTipo(expr2));
            expresion->tipo = error;
        }
    }
    else if (op.atrib == 1) {
        if (expr1.tipo != lista && expr1.tipo == expr2.tipo && expr1.tipo != booleano) {
            expresion->tipo == expr1.tipo;
        }
        else  {
            if (expr1.tipo == lista && expr2.tipo != lista && expr2.tipo == expr1.tipo_interno) {
                expresion->tipo = lista;
                return;
            }

            printf("[ERROR SEMÁNTICO] Línea %d: Operandos de división inválidos\n", yylineno);
            printf("                  Se pueden dividir todos los tipos elementales excepto booleanos.\n"
                   "                  Se puede dividir lista (no de booleanos) con su tipo de valor interno.\n");
            printf("                  Tipo proporcionado: %s / %s\n\n", getAtribTipo(expr1), getAtribTipo(expr2));
            expresion->tipo = error;
        }
    }
    else if (op.atrib == 2) {
        if (expr1.tipo == lista && expr2.tipo == entero) {
            expresion->tipo = lista;
            expresion->tipo_interno = expr1.tipo_interno;
        } else {
            printf("[ERROR SEMÁNTICO] Línea %d: El primer operando de %% ha de ser una lista y el segundo un entero.\n", yylineno);
            printf("                  Tipo proporcionado: %s %% %s\n\n", getAtribTipo(expr1), getAtribTipo(expr2));
            expresion->tipo = error;
        }
    }
    else if (op.atrib == 3) {
        if (expr1.tipo == lista && expr2.tipo == lista && expr1.tipo_interno == expr2.tipo_interno) {
            expresion->tipo = lista;
            expresion->tipo_interno = expr1.tipo_interno;
        }
        else {

        printf("[ERROR SEMÁNTICO] Línea %d: Los operandos de ** han de ser listas del mismo tipo.\n", yylineno);
        printf("                  Tipo proporcionado: %s ** %s\n\n", getAtribTipo(expr1), getAtribTipo(expr2));
        expresion->tipo = error;
    }
    }
    else if (op.atrib ==4) {
        if (expr1.tipo == lista && expr2.tipo == entero)
            expresion->tipo = lista;
        else {
            printf("[ERROR SEMÁNTICO] Línea %d: El primer operando de -- ha de ser una lista y el segundo un entero.\n", yylineno);
            printf("                  Tipo proporcionado: %s -- %s\n\n", getAtribTipo(expr1), getAtribTipo(expr2));
            expresion->tipo = error;
        }
    }
}

void printTipo(dtipo tipo) {
    if (tipo == entero)
        printf("%12s","entero");
    else if (tipo == error)
        printf("%12s","error");
    else if (tipo == real)
        printf("%12s","real");
    else if (tipo == caracter)
        printf("%12s","caracter");
    else if (tipo == booleano)
        printf("%12s","booleano");
    else if (tipo == lista)
        printf("%12s","lista");
    else if (tipo == no_asignado)
        printf("%12s","sin asignar");
    else
        printf("%12s","desconocido");
}
void ImprimirTablaSimbolos()
{
    printf("\t\tENTRADA\t   IDENTIFICADOR\t\tTIPO\t\tT_IN\t  N_PARAMS\t    N_DIMS\n");
    for (int i = 0; i < TOPE; ++i) {
        printf("Posición %d: \t", i);
        if (TS[i].entrada == marca)
            printf("Marca\t\t");
        else if (TS[i].entrada == funcion)
            printf("Función\t\t");
        else if (TS[i].entrada == variable)
            printf("Variable\t");
        else if (TS[i].entrada == parametro_formal)
            printf("Parámetro\t");
        if (TS[i].nombre == NULL)
            printf("%8s\t","");
        else
            printf("%8s\t", TS[i].nombre);

        printTipo(TS[i].tipoDato);
        printf("\t");
        printTipo(TS[i].tipoInterno);
        printf("\t\t");
        printf("%2u", TS[i].parametros);
        printf("\t\t");
        printf("%2u", TS[i].dimensiones);


        printf("\n");
    }
}

void comprobarTipoIgualdad(atributos op, atributos expr1, atributos expr2, atributos *expresion)
{
    if (op.atrib == 0) {
        if (expr1.tipo == lista && expr2.tipo == lista && expr1.tipo_interno == expr2.tipo_interno) {
            expresion->tipo = booleano;
        } else if (expr1.tipo != lista && expr1.tipo == expr2.tipo) {
            expresion->tipo = booleano;
        } else {
            expresion->tipo = error;
            printf("[ERROR SEMÁNTICO] Línea %d: Ambas expresiones con el operador == han de ser del mismo tipo.\n",
                   yylineno);
             printf("                  Tipo proporcionado: %s == %s\n\n", getAtribTipo(expr1), getAtribTipo(expr2));
        }
    } else if (op.atrib == 1) {
        if (expr1.tipo == lista && expr2.tipo == lista && expr1.tipo_interno == expr2.tipo_interno) {
            expresion->tipo = booleano;
        } else if (expr1.tipo != lista && expr1.tipo == expr2.tipo) {
            expresion->tipo = booleano;
        } else {
            expresion->tipo = error;
            printf("[ERROR SEMÁNTICO] Línea %d: Ambas expresiones con el operador != han de ser del mismo tipo.\n",
                   yylineno);
            printf("                  Tipo proporcionado: %s != %s\n\n", getAtribTipo(expr1), getAtribTipo(expr2));
        }
    }
}

void comprobarTipoAnd(atributos expr1, atributos expr2, atributos *expresion)
{
    if (expr1.tipo == booleano && expr2.tipo == booleano)
        expresion->tipo = booleano;
    else {
        expresion->tipo = error;
        printf("[ERROR SEMÁNTICO] Línea %d: Ambas expresiones con el operador && han de ser de tipo booleano.\n",
               yylineno);
        printf("                  Tipo proporcionado: %s && %s\n\n", getAtribTipo(expr1), getAtribTipo(expr2));
    }
}

void comprobarTipoOr(atributos expr1, atributos expr2, atributos *expresion)
{
    if (expr1.tipo == booleano && expr2.tipo == booleano)
        expresion->tipo = booleano;
    else {
        expresion->tipo = error;
        printf("[ERROR SEMÁNTICO] Línea %d: Ambas expresiones con el operador || han de ser de tipo booleano.\n",
               yylineno);
        printf("                  Tipo proporcionado: %s || %s\n\n", getAtribTipo(expr1), getAtribTipo(expr2));
    }
}

void comprobarTipoRelacional(atributos op, atributos expr1, atributos expr2, atributos *expresion)
{
    char operador[3]="";
    if (op.atrib == 0) {
        operador[0] = '<';
        operador[1] = '\0';
    } else if (op.atrib == 1) {
        operador[0] = '>';
        operador[1] = '\0';
    } else if (op.atrib == 2) {
        operador[0] = '<';
        operador[1] = '=';
        operador[2] = '\0';
    } else if (op.atrib == 3) {
        operador[0] = '>';
        operador[1] = '=';
        operador[2] = '\0';
    }

    if (expr1.tipo != booleano && expr1.tipo != lista && expr1.tipo == expr2.tipo)
        expresion->tipo = booleano;
    else {
        expresion->tipo = error;
        printf("[ERROR SEMÁNTICO] Línea %d: Ambas expresiones con el operador binario %s han de ser del mismo tipo."
               " No pueden ser booleanos ni listas.\n",
               yylineno, operador);
        printf("                  Tipo proporcionado: %s %s %s\n\n", getAtribTipo(expr1), operador, getAtribTipo(expr2));
    }
}

void comprobarTipoTernario(atributos expr1, atributos expr2, atributos expr3, atributos *expresion)
{
    if (expr1.tipo == lista && expr2.tipo == expr1.tipo_interno && expr3.tipo == entero) {
        expresion->tipo = lista;
        expresion->tipo_interno = expr1.tipo_interno;
    }
    else {
        expresion->tipo = error;
        printf("[ERROR SEMÁNTICO] Línea %d:  Tipo incorrecto. Debe ser <lista> ++ <tipo_interno_lista> @ <entero>.\n"
               "                  Tipo proporcionado: %s ++ %s @ %s\n\n",
               yylineno, getAtribTipo(expr1), getAtribTipo(expr2), getAtribTipo(expr3));
    }
}

void comprobarTipoArroba(atributos expr1, atributos expr2, atributos *expresion)
{
    if (expr1.tipo == lista && expr2.tipo == entero)
        expresion->tipo = expr1.tipo_interno;
    else {
        expresion->tipo = error;
        printf("[ERROR SEMÁNTICO] Línea %d:  Tipo incorrecto para operador binario @.\n"
               "                  Tipo proporcionado: %s @ %s\n"
               "                  Tipo esperado: %s @ %s\n\n",
               yylineno, getTipo(lista, no_asignado), getTipo(entero, entero), getAtribTipo(expr1), getAtribTipo(expr2));
    }
}

void comprobarTipoMasMenos(atributos op, atributos expr1, atributos expr2, atributos *expresion)
{
    if (op.atrib == 1) {
        if (expr1.tipo != lista & expr1.tipo == expr2.tipo && expr1.tipo != booleano) {
            expresion->tipo == expr1.tipo;
        }
        else  {
            if ((expr1.tipo == lista && expr2.tipo != lista && expr2.tipo == expr1.tipo_interno && expr2.tipo != booleano) ||
                (expr2.tipo == lista && expr1.tipo != lista && expr1.tipo == expr2.tipo_interno
                 && expr1.tipo_interno != booleano)) {
                expresion->tipo = lista;
                return;
            }

            printf("[ERROR SEMÁNTICO] Línea %d: Operandos de suma inválidos.\n"
                   "                  Se pueden sumar todos los tipos elementales excepto booleanos.\n"
                   "                  Se puede sumar lista (no de booleanos) con su tipo de valor interno.\n"
                   "                  Se puede sumar tipo de valor interno con lista(no de booleanos).\n"
                   "                  Tipos proporcionados: %s + %s\n\n", yylineno, getAtribTipo(expr1), getAtribTipo(expr2));
            expresion->tipo = error;
        }
    }
    else if (op.atrib == 0) {
        if (expr1.tipo != lista && expr1.tipo == expr2.tipo && expr1.tipo != booleano) {
            expresion->tipo == expr1.tipo;
        }
        else  {
            if (expr1.tipo == lista && expr2.tipo != lista && expr2.tipo == expr1.tipo_interno && expr1.tipo_interno != booleano) {
                expresion->tipo = lista;
                return;
            }

            printf("[ERROR SEMÁNTICO] Línea %d: Operandos de resta inválidos. No se pueden restar booleanos.\n"
                   "                  Se pueden restar todos los tipos elementales excepto booleanos.\n"
                   "                  Se puede restar lista (no de booleanos) con su tipo de valor interno.\n"
                   "                  Tipos proporcionados: %s - %s\n\n", yylineno, getAtribTipo(expr1), getAtribTipo(expr2));
            expresion->tipo = error;
        }
    }
}

void asignarTipoIdentificador(atributos identificador, atributos *expresion)
{
    int pos = encontrarIdentificador(identificador.lexema, 0);
    if (pos == -1) {
        expresion->tipo = error;
        printf("[ERROR SEMÁNTICO] Línea %d: La variable %s no ha sido declarada antes de su uso.\n\n",
               yylineno, identificador.lexema);
    }
    else {
        expresion->tipo = TS[pos].tipoDato;
        expresion->tipo_interno = TS[pos].tipoInterno;
    }
}





void comprobarAsignacion(atributos identificador, atributos expresion)
{
    int pos = encontrarIdentificador(identificador.lexema, 0);
    if (pos == -1) {
        expresion.tipo = error;
        printf("[ERROR SEMÁNTICO] Línea %d: La variable %s no ha sido declarada antes de su uso.\n\n",
               yylineno, identificador.lexema);
    }
    else {
        if (!((TS[pos].tipoDato == lista && expresion.tipo == lista &&
            TS[pos].tipoInterno == expresion.tipo_interno) ||
            (TS[pos].tipoDato != lista && TS[pos].tipoDato == expresion.tipo))) {
            printf("[ERROR SEMÁNTICO] Línea %d: El tipo de la variable a asignar difiere de el de la expresión.\n"
                   "                  Tipo variable %s: %s\n"
                   "                  Tipo expresión: %s\n\n",
                   yylineno, identificador.lexema, getIDTipo(pos), getAtribTipo(expresion));
        }

    }
}

void comprobarFuncion(atributos identificador, atributos* expresion)
{
    // 1. Buscamos la función en la pila
    int pos_func = encontrarIdentificador(identificador.lexema, 0);
    expresion->tipo = error;
    if (pos_func == -1) {
        printf("[ERROR SEMÁNTICO] Línea %d: La función %s no ha sido definida antes de su uso.\n\n",
               yylineno, identificador.lexema);
    }
    else {
        expresion->tipo = TS[pos_func].tipoDato;
        expresion->tipo_interno = TS[pos_func].tipoInterno;
        // 2. Comprobramos que el número de parámetros sea el correcto
        int pos_marca = TOPE_PARAMS-1;
        for (; listaParametros[pos_marca].entrada != marca; --pos_marca);
        int num_params = TOPE_PARAMS -1 - pos_marca;
        if (TS[pos_func].parametros != num_params) {
            printf("[ERROR SEMÁNTICO] Línea %d: La función %s tiene %d parámetros y se han proporcionado %d.\n\n",
                   yylineno, identificador.lexema, TS[pos_func].parametros, num_params);
            expresion->tipo = error;
        }
        else {
            // 3. Comprobamos en orden los tipos de los parámetros

            for (int i = 0; i < num_params; ++i) {
                if (TS[pos_func+1+i].tipoDato != listaParametros[i+pos_marca+1].tipo
                    || (listaParametros[i+pos_marca+1].tipo == lista &&
                        TS[pos_func+1+i].tipoInterno != listaParametros[i+pos_marca+1].tipo_interno)) {
                    printf("[ERROR SEMÁNTICO] Línea %d: El parámetro número %d de la función %s es de tipo incorrecto.\n"
                           "                  Tipo proporcionado: %s\n"
                           "                  Tipo esperado: %s\n\n",
                           yylineno, i-pos_marca, identificador.lexema, getTipo(listaParametros[i+pos_marca+1].tipo,
                           listaParametros[i+pos_marca+1].tipo_interno),
                                                              getIDTipo(pos_func + 1 + i));
                    expresion->tipo = error;
                }
            }
        }
    }

}

void guardarParametro(atributos parametro)
{
    listaParametros[TOPE_PARAMS].entrada = parametro_formal;
    listaParametros[TOPE_PARAMS].tipo = parametro.tipo;
    listaParametros[TOPE_PARAMS].tipo_interno = parametro.tipo_interno;
    ++TOPE_PARAMS;
}

void insertarMarcaFuncion()
{
    listaParametros[TOPE_PARAMS].entrada = marca;
    ++TOPE_PARAMS;
}

void limpiarMarcaFuncion()
{
    int i;
    for (i = TOPE_PARAMS-1; listaParametros[i].entrada != marca && i > -1; --i);
    if (i == -1) {
        printf("Línea %d: [ERROR DE IMPLEMENTACIÓN - SEMÁNTICO]\n", yylineno);
    }
    else
        TOPE_PARAMS = i;
}


void comprobarReturnDolar(atributos operador, atributos parametro)
{
    if (operador.atrib == 0) {
        if (parametro.tipo != lista)
            printf("[ERROR SEMÁNTICO] Línea %d: El operador $ no va seguido por un tipo válido.\n"
                   "                  Tipo proporcionado: %s\n"
                   "                  Tipo esperado: %s\n\n",
                   yylineno, getAtribTipo(parametro), getTipo(lista, no_asignado) );
    }
    else if (operador.atrib == 1) {
        // 1. Buscamos la marca
        int posMarca = buscarMarca();
        // 2. Buscamos la función antes de la marca;
        int posFuncion;
        for (posFuncion = posMarca; TS[posFuncion].entrada != funcion && posFuncion > -1;--posFuncion);
        if (posFuncion == -1){
            printf("[ERROR SEMÁNTICO] Línea %d: No se puede hacer devolver en el contexto actual.\n\n", yylineno);
        }
        else {
            if ((TS[posFuncion].tipoDato != lista && TS[posFuncion].tipoDato != parametro.tipo) ||
                (TS[posFuncion].tipoDato == lista && (TS[posFuncion].tipoDato != parametro.tipo ||
                                                      TS[posFuncion].tipoInterno != parametro.tipo_interno))
                    ) {
                printf("[ERROR SEMÁNTICO] Línea %d: Error de tipo en devolución de la función %s.\n"
                       "                  Tipo proporcionado: %s\n"
                       "                  Tipo esperado: %s\n\n",
                       yylineno, TS[posFuncion].nombre, getAtribTipo(parametro), getIDTipo(posFuncion));
            }

        }
    }
}


char* getTipo(dtipo tipo, dtipo tipo_interno)
{
    if (tipo == lista) {
        if (tipo_interno == entero)
            return "lista de enteros";
        else if (tipo_interno == booleano)
            return "lista de booleanos";
        else if (tipo_interno == caracter)
            return "lista de caracteres";
        else if (tipo_interno == real)
            return "lista de reales";
        else if (tipo_interno == desconocido)
            return "lista desconocida";
        else if (tipo_interno == error)
            return "lista <tipo interno erróneo>";
        else if (tipo_interno == no_asignado)
            return "lista de <booleano | entero | real | caracter>";
    }
    else if (tipo == entero)
        return "entero";
    else if (tipo == booleano)
        return "booleano";
    else if (tipo == real)
        return "real";
    else if (tipo == caracter)
        return "caracter";
    else if (tipo == error)
        return "error";
    else if (tipo == desconocido)
        return "desconocido";
    else if (tipo_interno == no_asignado);
}

char *getAtribTipo(atributos atrib)
{
    return getTipo(atrib.tipo, atrib.tipo_interno);
}

char *getIDTipo(int pos)
{
    return getTipo(TS[pos].tipoDato, TS[pos].tipoInterno);
}


void comprobarTipoDesplaza(atributos op, atributos expresion)
{
    char operador[3];
    if (op.atrib == 1) {
        operador[0] = '<';
        operador[1] = '<';
        operador[2] = '\0';
    }
    else {
        operador[0] = '>';
        operador[1] = '>';
        operador[2] = '\0';
    }
    if (expresion.tipo != lista) {
        printf("[ERROR SEMÁNTICO] Línea %d: El operador %s ha de ir precedido de una lista.\n"
               "                  Tipo proporcionado: %s\n\n", yylineno, operador, getAtribTipo(expresion));
    }
}