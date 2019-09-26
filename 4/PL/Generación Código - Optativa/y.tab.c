/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "sintactico.y" /* yacc.c:339  */

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "generacion.h"
	#include "semantico.h"
	extern int yylex(void);
	void yyerror(const char * msg);
	#define YYDEBUG 1
	#define YYERROR_VERBOSE

#line 78 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    DECLARACION = 258,
    FINDECLARACION = 259,
    PRINCIPAL = 260,
    ABRE_LLAVE = 261,
    CIERRA_LLAVE = 262,
    PUNTO_COMA = 263,
    ABRE_PAREN = 264,
    CIERRA_PAREN = 265,
    DESPLAZA = 266,
    DEVOLVER_DOLAR = 267,
    REPETIR = 268,
    HASTA = 269,
    ASIGNACION = 270,
    SI = 271,
    SINO = 272,
    MIENTRAS = 273,
    LEER = 274,
    ESCRIBIR = 275,
    LISTA_DE = 276,
    TIPO = 277,
    CONSTANTE = 278,
    IDENTIFICADOR = 279,
    CADENA = 280,
    COMA = 281,
    ABRE_CORCHETE = 282,
    CIERRA_CORCHETE = 283,
    OP_TERNARIO1 = 284,
    OP_RELACIONAL_OR = 285,
    OP_RELACIONAL_AND = 286,
    OP_RELACIONAL_IGUALDAD = 287,
    OP_RELACIONAL = 288,
    MAS_MENOS = 289,
    OP_BINARIO = 290,
    ARROBA = 291,
    OP_UNARIO = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 164 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   280

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  152

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    62,    62,    62,    64,    64,    70,    70,    72,    72,
      75,    76,    78,    78,    80,    80,    80,    82,    83,    84,
      86,    86,    88,    88,    88,    88,    88,    90,    92,    92,
      94,    94,    94,    94,    94,    94,    94,    95,    95,    97,
      99,   101,   102,   102,   104,   104,   104,   106,   108,   108,
     108,   110,   112,   112,   114,   114,   116,   116,   118,   120,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   139,   144,   150,   150,
     152,   154,   154,   161,   172
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DECLARACION", "FINDECLARACION",
  "PRINCIPAL", "ABRE_LLAVE", "CIERRA_LLAVE", "PUNTO_COMA", "ABRE_PAREN",
  "CIERRA_PAREN", "DESPLAZA", "DEVOLVER_DOLAR", "REPETIR", "HASTA",
  "ASIGNACION", "SI", "SINO", "MIENTRAS", "LEER", "ESCRIBIR", "LISTA_DE",
  "TIPO", "CONSTANTE", "IDENTIFICADOR", "CADENA", "COMA", "ABRE_CORCHETE",
  "CIERRA_CORCHETE", "OP_TERNARIO1", "OP_RELACIONAL_OR",
  "OP_RELACIONAL_AND", "OP_RELACIONAL_IGUALDAD", "OP_RELACIONAL",
  "MAS_MENOS", "OP_BINARIO", "ARROBA", "OP_UNARIO", "$accept", "programa",
  "$@1", "bloque", "$@2", "declar_de_subprogs", "declar_subprograma",
  "$@3", "declar_de_variables_locales", "variables_locales",
  "cuerpo_declar_variables", "$@4", "lista_id", "cabecera_subprograma",
  "$@5", "lista_parametros", "$@6", "parametro", "sentencias", "sentencia",
  "sentencia_asignacion", "condicion_if", "sentencia_if", "$@7",
  "sentencia_while", "$@8", "$@9", "sentencia_entrada", "lista_leer",
  "sentencia_salida", "lista_expresiones_o_cadena", "expr_cad",
  "sentencia_repeat_until", "$@10", "sentencia_return_comienzo_lista",
  "avanzar_retroceder_lista", "expresion", "funcion", "tipo_t",
  "agregado_lista", "lista_f", "lista", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

#define YYPACT_NINF -35

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-35)))

#define YYTABLE_NINF -64

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      12,   -35,     8,    48,   -35,   -35,   -35,    61,    19,   -35,
     -35,    52,   -35,    67,   -35,   -35,   107,   -35,   -35,   -35,
      51,   -35,    69,    69,   -35,    71,   -35,    57,    42,   -35,
       0,    69,    69,    69,   -35,   -35,   -35,    15,   -35,   -35,
     134,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   244,   -35,
      59,   -35,   -35,    18,    81,   175,   159,   134,    69,    82,
     -35,    24,   -35,    10,   -35,   227,   150,    69,   227,    27,
     -35,   -35,    48,   -35,   -35,    68,    86,    69,    69,    69,
      69,    69,    69,    69,    69,   -35,    90,   -35,    93,   -35,
     -35,    96,   202,    69,    94,   -35,    97,   -35,    42,   -35,
     227,     3,   167,    69,   -35,   -35,   -35,   -35,   235,   147,
      65,   103,   128,    88,    88,    88,   113,   -35,   -35,   123,
     -35,   210,   -35,   -35,   -35,   -35,    69,   -35,   227,   134,
      69,    26,    69,   -35,   227,   -35,    76,     4,   -35,   118,
     218,   134,   121,   -35,   -35,   -35,   140,   -35,   -35,    26,
     -35,   -35
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     2,     0,     0,     1,     4,     3,    11,     0,     7,
      16,     0,    78,     0,    13,    14,     0,    79,    10,    12,
       0,    75,     0,     0,    56,     0,    44,     0,     0,    72,
      71,     0,     0,     0,    30,     6,     8,     0,    29,    31,
       0,    32,    33,    34,    35,    36,    37,    38,     0,    73,
       0,    74,    17,     0,    71,     0,     0,     0,     0,     0,
      48,     0,    55,     0,    52,    54,     0,     0,    83,     0,
      61,    62,     0,     5,    28,    41,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    20,     0,    15,     0,    60,
      58,     0,     0,     0,     0,    47,     0,    51,     0,    77,
      81,     0,     0,     0,    80,     9,    42,    59,     0,    68,
      67,    66,    69,    70,    65,    64,     0,    19,    18,     0,
      40,     0,    50,    49,    53,    76,     0,    39,    84,     0,
       0,    26,     0,    45,    82,    43,    64,     0,    22,     0,
       0,     0,     0,    21,    23,    27,     0,    46,    25,     0,
      57,    24
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -35,   -35,   -35,     1,   -35,   -35,   -35,   -35,   -35,   -35,
     136,   -35,   -35,   -35,   -35,   -35,   -35,     6,   -35,   -34,
     -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,
     -35,    58,   -35,   -35,   -35,   -35,   -21,   -35,   -16,   -35,
     -35,   -35
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    34,     7,    16,    35,    72,     9,    13,
      14,    20,    53,    36,   116,   137,   149,   138,    37,    38,
      39,    40,    41,   129,    42,    59,   141,    43,    61,    44,
      63,    64,    45,    57,    46,    47,    48,    49,    15,    51,
     101,    69
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      50,    55,    56,    74,     6,   142,    75,    65,     4,    66,
      68,    70,    71,   125,   143,    67,    21,     1,    97,    86,
      10,     5,    73,    91,    22,    94,    87,    23,    24,   126,
     144,    25,    95,    26,    27,    28,    98,    92,    29,    30,
      11,    12,    31,    21,    88,   100,   102,    11,    12,    32,
      96,    22,    33,   103,     5,   104,   108,   109,   110,   111,
     112,   113,   114,   115,     8,    29,    54,    62,    10,    31,
      21,    18,   121,   105,    17,    52,    32,    65,    22,    33,
      58,    60,   128,    85,   -63,   106,   -63,   -63,    11,    12,
      66,    93,    29,    54,   107,   135,    31,    80,    81,    82,
      83,    84,   -63,    32,   -63,   134,    33,   147,    21,   136,
     119,   140,    84,     5,   117,   139,    22,   118,   122,    23,
      24,   123,   131,    25,    84,    26,    27,    28,    11,    12,
      29,    30,   132,   139,    31,    21,    81,    82,    83,    84,
       5,    32,   145,    22,    33,   148,    23,    24,   150,    19,
      25,    21,    26,    27,    28,   151,   124,    29,    30,    22,
      99,    31,    82,    83,    84,     0,     0,    90,    32,     0,
       0,    33,     0,    29,    54,   127,     0,    31,    79,    80,
      81,    82,    83,    84,    32,    89,     0,    33,    77,    78,
      79,    80,    81,    82,    83,    84,    77,    78,    79,    80,
      81,    82,    83,    84,    77,    78,    79,    80,    81,    82,
      83,    84,   120,     0,     0,     0,     0,     0,     0,     0,
     133,     0,     0,     0,     0,     0,     0,     0,   146,     0,
       0,    77,    78,    79,    80,    81,    82,    83,    84,    77,
      78,    79,    80,    81,    82,    83,    84,    77,    78,    79,
      80,    81,    82,    83,    84,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    77,    78,    79,    80,    81,    82,
      83,   130,     0,    77,    78,    79,    80,    81,    82,    83,
      84
};

static const yytype_int16 yycheck[] =
{
      16,    22,    23,    37,     3,     1,    40,    28,     0,     9,
      31,    32,    33,    10,    10,    15,     1,     5,     8,     1,
       1,     6,     7,    57,     9,     1,     8,    12,    13,    26,
      26,    16,     8,    18,    19,    20,    26,    58,    23,    24,
      21,    22,    27,     1,    26,    66,    67,    21,    22,    34,
      26,     9,    37,    26,     6,    28,    77,    78,    79,    80,
      81,    82,    83,    84,     3,    23,    24,    25,     1,    27,
       1,     4,    93,    72,    22,    24,    34,    98,     9,    37,
       9,    24,   103,    24,     8,    17,    10,    11,    21,    22,
       9,     9,    23,    24,     8,   129,    27,    32,    33,    34,
      35,    36,    26,    34,    28,   126,    37,   141,     1,   130,
      14,   132,    36,     6,    24,   131,     9,    24,    24,    12,
      13,    24,     9,    16,    36,    18,    19,    20,    21,    22,
      23,    24,     9,   149,    27,     1,    33,    34,    35,    36,
       6,    34,    24,     9,    37,    24,    12,    13,     8,    13,
      16,     1,    18,    19,    20,   149,    98,    23,    24,     9,
      10,    27,    34,    35,    36,    -1,    -1,     8,    34,    -1,
      -1,    37,    -1,    23,    24,     8,    -1,    27,    31,    32,
      33,    34,    35,    36,    34,    10,    -1,    37,    29,    30,
      31,    32,    33,    34,    35,    36,    29,    30,    31,    32,
      33,    34,    35,    36,    29,    30,    31,    32,    33,    34,
      35,    36,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    10,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    36,    29,
      30,    31,    32,    33,    34,    35,    36,    29,    30,    31,
      32,    33,    34,    35,    36,    11,    29,    30,    31,    32,
      33,    34,    35,    36,    29,    30,    31,    32,    33,    34,
      35,    36,    -1,    29,    30,    31,    32,    33,    34,    35,
      36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,    39,    40,     0,     6,    41,    42,     3,    46,
       1,    21,    22,    47,    48,    76,    43,    22,     4,    48,
      49,     1,     9,    12,    13,    16,    18,    19,    20,    23,
      24,    27,    34,    37,    41,    44,    51,    56,    57,    58,
      59,    60,    62,    65,    67,    70,    72,    73,    74,    75,
      76,    77,    24,    50,    24,    74,    74,    71,     9,    63,
      24,    66,    25,    68,    69,    74,     9,    15,    74,    79,
      74,    74,    45,     7,    57,    57,    11,    29,    30,    31,
      32,    33,    34,    35,    36,    24,     1,     8,    26,    10,
       8,    57,    74,     9,     1,     8,    26,     8,    26,    10,
      74,    78,    74,    26,    28,    41,    17,     8,    74,    74,
      74,    74,    74,    74,    74,    74,    52,    24,    24,    14,
      10,    74,    24,    24,    69,    10,    26,     8,    74,    61,
      36,     9,     9,    10,    74,    57,    74,    53,    55,    76,
      74,    64,     1,    10,    26,    24,    10,    57,    24,    54,
       8,    55
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    40,    39,    42,    41,    43,    43,    45,    44,
      46,    46,    47,    47,    49,    48,    48,    50,    50,    50,
      52,    51,    53,    54,    53,    53,    53,    55,    56,    56,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    58,
      59,    60,    61,    60,    63,    64,    62,    65,    66,    66,
      66,    67,    68,    68,    69,    69,    71,    70,    72,    73,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    75,    75,    76,    76,
      77,    78,    78,    79,    79
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     0,     6,     2,     0,     0,     3,
       3,     0,     2,     1,     0,     4,     1,     1,     3,     3,
       0,     6,     1,     0,     4,     3,     0,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       4,     2,     0,     5,     0,     0,     7,     3,     1,     3,
       3,     3,     1,     3,     1,     1,     0,     8,     3,     3,
       3,     2,     2,     5,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     1,     1,     1,     4,     3,     1,     2,
       3,     1,     3,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 62 "sintactico.y" /* yacc.c:1646  */
    {escribirLibrerias();}
#line 1385 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 64 "sintactico.y" /* yacc.c:1646  */
    {insertarMarca(); abrirBloque();}
#line 1391 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 68 "sintactico.y" /* yacc.c:1646  */
    {vaciarEntradas(); cerrarBloque();}
#line 1397 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 72 "sintactico.y" /* yacc.c:1646  */
    {subProg = 1;}
#line 1403 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 73 "sintactico.y" /* yacc.c:1646  */
    {subProg = 0; --contador_subprogramas; volverAArchivoCompilado(); }
#line 1409 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 75 "sintactico.y" /* yacc.c:1646  */
    {if (!hay_principal) introducirMain();}
#line 1415 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 76 "sintactico.y" /* yacc.c:1646  */
    {if (!hay_principal) introducirMain();}
#line 1421 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 80 "sintactico.y" /* yacc.c:1646  */
    {declararTipo((yyvsp[0]));}
#line 1427 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 80 "sintactico.y" /* yacc.c:1646  */
    {escribirPuntoYComa();}
#line 1433 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 82 "sintactico.y" /* yacc.c:1646  */
    {insertarIdentificador((yyvsp[0])); declararVariable((yyvsp[0]));}
#line 1439 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 83 "sintactico.y" /* yacc.c:1646  */
    {insertarIdentificador((yyvsp[0]));  escribirComa(); declararVariable((yyvsp[0]));}
#line 1445 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 86 "sintactico.y" /* yacc.c:1646  */
    { ++contador_subprogramas; cambiarAArchivoFunciones(); ponerCabeceraFuncion((yyvsp[-1]), (yyvsp[0])); insertarFuncion((yyvsp[0]));}
#line 1451 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 86 "sintactico.y" /* yacc.c:1646  */
    { fprintf(archivo_compilado, ")"); }
#line 1457 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 88 "sintactico.y" /* yacc.c:1646  */
    {fprintf(archivo_compilado, ",");}
#line 1463 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 90 "sintactico.y" /* yacc.c:1646  */
    {insertarParametros((yyvsp[0])); declararTipo((yyvsp[-1])), fprintf(archivo_compilado, "%s", (yyvsp[0]).lexema);}
#line 1469 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 97 "sintactico.y" /* yacc.c:1646  */
    { comprobarAsignacion((yyvsp[-3]), (yyvsp[-1])); generarAsignacion((yyvsp[-3]), (yyvsp[-1]));}
#line 1475 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 99 "sintactico.y" /* yacc.c:1646  */
    {comprobarBooleanoLoop((yyvsp[-1])); addATabla((yyvsp[-1])); emitirSaltoElse(); abrirBloque();}
#line 1481 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 101 "sintactico.y" /* yacc.c:1646  */
    {cerrarBloque(); escribirEtiquetaElse(); quitarDeTabla();}
#line 1487 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 102 "sintactico.y" /* yacc.c:1646  */
    {cerrarBloque(); emitirSaltoSalida(); escribirEtiquetaElse(); abrirBloque(); }
#line 1493 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 102 "sintactico.y" /* yacc.c:1646  */
    {cerrarBloque(); escribirEtiquetaSalida(); quitarDeTabla(); }
#line 1499 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 104 "sintactico.y" /* yacc.c:1646  */
    {addATablaWhileRepeat((yyvsp[0]));  escribirEtiquetaEntrada(); abrirBloque();}
#line 1505 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 104 "sintactico.y" /* yacc.c:1646  */
    {comprobarBooleanoLoop((yyvsp[-1])); escribirNombreExpresionControl((yyvsp[-1])); saltoSalidaWhile();}
#line 1511 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 104 "sintactico.y" /* yacc.c:1646  */
    {saltoEntradaWhileRepeat(); cerrarBloque(); escribirEtiquetaSalida(); quitarDeTabla();}
#line 1517 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 108 "sintactico.y" /* yacc.c:1646  */
    {leer((yyvsp[0]));}
#line 1523 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 108 "sintactico.y" /* yacc.c:1646  */
    {leer((yyvsp[0]));}
#line 1529 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 114 "sintactico.y" /* yacc.c:1646  */
    {escribir((yyvsp[0]));}
#line 1535 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 114 "sintactico.y" /* yacc.c:1646  */
    {escribir((yyvsp[0]));}
#line 1541 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 116 "sintactico.y" /* yacc.c:1646  */
    {addATablaWhileRepeat((yyvsp[0])); escribirEtiquetaEntrada(); abrirBloque();}
#line 1547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 116 "sintactico.y" /* yacc.c:1646  */
    {comprobarBooleanoLoop((yyvsp[-2])); escribirNombreExpresionControl((yyvsp[-2])); saltoSalidaRepeat(); saltoEntradaWhileRepeat(); cerrarBloque(); escribirEtiquetaSalida(); quitarDeTabla();}
#line 1553 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 118 "sintactico.y" /* yacc.c:1646  */
    {comprobarReturnDolar((yyvsp[-2]),(yyvsp[-1])); if ((yyvsp[-2]).atrib == 0) comienzolista((yyvsp[-1])); else sentenciareturn((yyvsp[-1]));}
#line 1559 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 120 "sintactico.y" /* yacc.c:1646  */
    { comprobarTipoDesplaza((yyvsp[-1]), (yyvsp[-2])); moverposicionlista((yyvsp[-1]), (yyvsp[-2]));}
#line 1565 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 122 "sintactico.y" /* yacc.c:1646  */
    {(yyval).tipo = (yyvsp[-1]).tipo; (yyval).tipo_interno = (yyvsp[-1]).tipo_interno;}
#line 1571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 123 "sintactico.y" /* yacc.c:1646  */
    {comprobarTipoUnarioMasMenos((yyvsp[-1]), (yyvsp[0]), &(yyval)); generarUnario((yyvsp[-1]), (yyvsp[0]), &(yyval));}
#line 1577 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 124 "sintactico.y" /* yacc.c:1646  */
    {comprobarTipoUnario((yyvsp[-1]), (yyvsp[0]), &(yyval)); generarUnario((yyvsp[-1]), (yyvsp[0]), &(yyval));}
#line 1583 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 125 "sintactico.y" /* yacc.c:1646  */
    {comprobarTipoTernario((yyvsp[-4]), (yyvsp[-2]), (yyvsp[0]), &(yyval)); generarTernario((yyvsp[-4]), (yyvsp[-2]), (yyvsp[0]));}
#line 1589 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 126 "sintactico.y" /* yacc.c:1646  */
    {atributos arroba; arroba.lexema="@"; comprobarTipoArroba((yyvsp[-2]), (yyvsp[0]), &(yyval)); generarBinario(arroba, (yyvsp[-2]), (yyvsp[0]), &(yyval));}
#line 1595 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 127 "sintactico.y" /* yacc.c:1646  */
    {comprobarTipoBinario((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0]), &(yyval)); generarBinario((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0]), &(yyval));}
#line 1601 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 128 "sintactico.y" /* yacc.c:1646  */
    {comprobarTipoIgualdad((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0]), &(yyval)); generarBinario((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0]), &(yyval));}
#line 1607 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 129 "sintactico.y" /* yacc.c:1646  */
    {comprobarTipoAnd((yyvsp[-2]), (yyvsp[0]), &(yyval)); generarBinario((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0]), &(yyval));}
#line 1613 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 130 "sintactico.y" /* yacc.c:1646  */
    {comprobarTipoOr((yyvsp[-2]), (yyvsp[0]), &(yyval)); generarBinario((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0]), &(yyval));}
#line 1619 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 131 "sintactico.y" /* yacc.c:1646  */
    {comprobarTipoRelacional((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0]), &(yyval)); generarBinario((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0]), &(yyval));}
#line 1625 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 132 "sintactico.y" /* yacc.c:1646  */
    {comprobarTipoMasMenos((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0]), &(yyval)); generarBinario((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0]), &(yyval));}
#line 1631 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 133 "sintactico.y" /* yacc.c:1646  */
    {asignarTipoIdentificador((yyvsp[0]), &(yyval)); }
#line 1637 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 134 "sintactico.y" /* yacc.c:1646  */
    {(yyval).tipo = (yyvsp[0]).tipo; (yyval).tipo_interno = (yyvsp[0]).tipo_interno;}
#line 1643 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 135 "sintactico.y" /* yacc.c:1646  */
    {(yyval).tipo = (yyvsp[0]).tipo; (yyval).tipo_interno = (yyvsp[0]).tipo_interno; }
#line 1649 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 136 "sintactico.y" /* yacc.c:1646  */
    {(yyval).tipo = (yyvsp[0]).tipo; (yyval).tipo_interno = (yyvsp[0]).tipo_interno;}
#line 1655 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 137 "sintactico.y" /* yacc.c:1646  */
    {(yyval).tipo = error;}
#line 1661 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 139 "sintactico.y" /* yacc.c:1646  */
    {comprobarFuncion((yyvsp[-3]), &(yyval)); limpiarMarcaFuncion(); 
														ampliarLexema((yyvsp[-3]), (yyvsp[-2]), &(yyval));
														ampliarLexema((yyval), (yyvsp[-1]), &(yyval));
														ampliarLexema((yyval), (yyvsp[0]), &(yyval));
														}
#line 1671 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 144 "sintactico.y" /* yacc.c:1646  */
    {insertarMarcaFuncion(); comprobarFuncion((yyvsp[-2]), &(yyval)); limpiarMarcaFuncion();
		  atributos parentesis;
		  parentesis.lexema = "()";
		  ampliarLexema((yyvsp[-2]), parentesis, &(yyval));
		  }
#line 1681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 150 "sintactico.y" /* yacc.c:1646  */
    {TipoTmp = (yyvsp[0]).tipo; (yyval).tipo = (yyvsp[0]).tipo;}
#line 1687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 150 "sintactico.y" /* yacc.c:1646  */
    {TipoTmp = (yyvsp[-1]).tipo; TipoTmp2 = (yyvsp[0]).tipo; (yyval).tipo = (yyvsp[-1]).tipo; (yyval).tipo_interno = (yyvsp[0]).tipo;}
#line 1693 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 152 "sintactico.y" /* yacc.c:1646  */
    {(yyval).tipo = (yyvsp[-1]).tipo; (yyval).tipo_interno = (yyvsp[-1]).tipo_interno; (yyval).lexema = (yyvsp[-1]).lexema;}
#line 1699 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 154 "sintactico.y" /* yacc.c:1646  */
    {insertarMarcaFuncion(); guardarParametro((yyvsp[0]));}
#line 1705 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 154 "sintactico.y" /* yacc.c:1646  */
    {guardarParametro((yyvsp[0]));
																			 atributos coma; 
																			 coma.lexema = ", " ;
																			 ampliarLexema((yyvsp[-2]), coma, &(yyval));
																			 ampliarLexema((yyval), (yyvsp[0]), &(yyval));
																			}
#line 1716 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 162 "sintactico.y" /* yacc.c:1646  */
    {if ((yyvsp[0]).tipo == lista) {
        	(yyval).tipo = error;
        	printf("[ERROR SEMÁNTICO] Línea %d: No se pueden tener listas de listas.\n", yylineno);
         }
         else {
         	(yyval).tipo = lista;
         	(yyval).tipo_interno = (yyvsp[0]).tipo;
         	generarListaTemporal((yyvsp[0]), &(yyval));
         }
	    }
#line 1731 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 173 "sintactico.y" /* yacc.c:1646  */
    { 
	 	if ((yyvsp[0]).tipo == lista)  {
	 		(yyval).tipo = error;
        	printf("[ERROR SEMÁNTICO] Línea %d: No se pueden tener listas de listas.\n", yylineno);
	 	}
	 	else if ((yyvsp[0]).tipo == (yyvsp[-2]).tipo_interno)  {
	 		(yyval).tipo = lista;
	 		(yyval).tipo_interno = (yyvsp[0]).tipo;
	 		addValorALista((yyvsp[-2]), (yyvsp[0]));
	 	}
	 	else {
	 		(yyval).tipo = error;
	 		printf("[ERROR SEMÁNTICO] Línea %d: No coinciden los tipos del agregado de la lista.\n", yylineno);
	 	}

	 }
#line 1752 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1756 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 190 "sintactico.y" /* yacc.c:1906  */


#include "lex.yy.c"

void yyerror(const char *msg) {
	printf("[ERROR SINTÁCTICO] Línea %d: %s\n\n", yylineno, msg);
}

