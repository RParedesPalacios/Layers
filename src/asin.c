/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "asin.y"

/*****************************************************************************/
/**  Syntactic-semantic analyzer, 2016.             <jmbenedi@prhlt.upv.es> **/
/*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nettable.h"


/* Line 268 of yacc.c  */
#line 82 "asin.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     batch_ = 258,
     threads_ = 259,
     seed_ = 260,
     cpu_ = 261,
     gpu_ = 262,
     device_ = 263,
     cuDNN_ = 264,
     cuBLAS_ = 265,
     filename_ = 266,
     tr_ = 267,
     ts_ = 268,
     va_ = 269,
     ascii_ = 270,
     binary_ = 271,
     gauss_ = 272,
     uniform_ = 273,
     ones_ = 274,
     zeros_ = 275,
     oneshot_ = 276,
     pos_ = 277,
     nrows_ = 278,
     ncolsample_ = 279,
     ncoltarget_ = 280,
     F_ = 281,
     FI_ = 282,
     FO_ = 283,
     C_ = 284,
     CI_ = 285,
     MP_ = 286,
     CAT_ = 287,
     O_ = 288,
     ADD_ = 289,
     classification_ = 290,
     regression_ = 291,
     autoencoder_ = 292,
     max_ = 293,
     min_ = 294,
     maxlog_ = 295,
     minlog_ = 296,
     nz_ = 297,
     nr_ = 298,
     nc_ = 299,
     cr_ = 300,
     cc_ = 301,
     numnodes_ = 302,
     T_ = 303,
     S_ = 304,
     W_ = 305,
     GW_ = 306,
     B_ = 307,
     GB_ = 308,
     N_ = 309,
     nk_ = 310,
     kr_ = 311,
     kc_ = 312,
     rpad_ = 313,
     cpad_ = 314,
     stride_ = 315,
     sizer_ = 316,
     sizec_ = 317,
     mu_ = 318,
     mmu_ = 319,
     l2_ = 320,
     l1_ = 321,
     maxn_ = 322,
     drop_ = 323,
     noiser_ = 324,
     noisesd_ = 325,
     brightness_ = 326,
     contrast_ = 327,
     lambda_ = 328,
     noiseb_ = 329,
     advf_ = 330,
     bn_ = 331,
     act_ = 332,
     shift_ = 333,
     flip_ = 334,
     adv_ = 335,
     balance_ = 336,
     cropmode_ = 337,
     trainable_ = 338,
     const_ = 339,
     data_ = 340,
     network_ = 341,
     script_ = 342,
     printkernels_ = 343,
     change_ = 344,
     train_ = 345,
     save_ = 346,
     load_ = 347,
     testout_ = 348,
     forward_ = 349,
     backward_ = 350,
     resetstats_ = 351,
     printerrors_ = 352,
     reseterrors_ = 353,
     trainmode_ = 354,
     testmode_ = 355,
     update_ = 356,
     test_ = 357,
     evaluate_ = 358,
     zscore_ = 359,
     center_ = 360,
     yuv_ = 361,
     maxmin_ = 362,
     shuffle_ = 363,
     next_ = 364,
     set_ = 365,
     mul_ = 366,
     div_ = 367,
     add_ = 368,
     sub_ = 369,
     store_ = 370,
     getstats_ = 371,
     bin_ = 372,
     int_ = 373,
     real_ = 374,
     copy_ = 375,
     imult_ = 376,
     omult_ = 377,
     sigmoid_ = 378,
     tanh_ = 379,
     relu_ = 380,
     for_ = 381,
     if_ = 382,
     else_ = 383,
     BCB_ = 384,
     ECB_ = 385,
     BSB_ = 386,
     ESB_ = 387,
     BRB_ = 388,
     ERB_ = 389,
     PER_ = 390,
     COM_ = 391,
     EQ_ = 392,
     RAR_ = 393,
     COL_ = 394,
     MAS_ = 395,
     MENOS_ = 396,
     POR_ = 397,
     DIV_ = 398,
     MOD_ = 399,
     PORPOR_ = 400,
     log_ = 401,
     exp_ = 402,
     sqr_ = 403,
     TRUE_ = 404,
     FALSE_ = 405,
     AND_ = 406,
     OR_ = 407,
     EQUAL_ = 408,
     NOTEQUAL_ = 409,
     GREAT_ = 410,
     GREATEQ_ = 411,
     LESS_ = 412,
     LESSEQ_ = 413,
     NOT_ = 414,
     IFAUX_ = 415,
     id_ = 416,
     nfile_ = 417,
     cecho_ = 418,
     cte_ = 419
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 10 "asin.y"
 /********************************************************************/
  char*   ident;                      /* for the "identifier" terminal       */
  float   creal;                      /* for the "real constant" terminal    */
  int     aux;                        /* For non-terminals with 1 attributes */
  TUPLE   aux2;                       /* For non-terminals with 2 attributes */
  AUX4    aux4;                       /* For non-terminals with 4 attributes */
  RANGO   rango;                      /* For non-terminals with rank         */
  EXPRE   expre;                      /* For non-terminal expression         */
  EXPFOR  expfor;                     /* For two exp of FOR                  */



/* Line 293 of yacc.c  */
#line 295 "asin.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 307 "asin.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   580

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  165
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  87
/* YYNRULES -- Number of rules.  */
#define YYNRULES  276
/* YYNRULES -- Number of states.  */
#define YYNSTATES  496

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   419

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     5,    10,    11,    16,    19,    21,
      25,    29,    33,    37,    42,    46,    50,    54,    57,    59,
      64,    65,    66,    75,    76,    82,    85,    87,    88,    94,
      96,    98,   100,   104,   106,   108,   112,   116,   118,   120,
     124,   128,   132,   134,   138,   142,   146,   148,   150,   152,
     154,   156,   158,   160,   161,   164,   168,   172,   176,   179,
     181,   183,   185,   189,   195,   201,   207,   213,   219,   222,
     225,   231,   232,   236,   240,   242,   246,   248,   252,   254,
     258,   262,   266,   270,   274,   278,   280,   284,   286,   288,
     290,   292,   294,   296,   298,   300,   304,   306,   307,   311,
     315,   317,   321,   325,   329,   333,   337,   341,   345,   347,
     351,   355,   357,   359,   361,   363,   365,   367,   369,   371,
     373,   377,   381,   383,   384,   385,   389,   391,   393,   394,
     404,   405,   416,   420,   429,   430,   431,   437,   439,   443,
     451,   457,   459,   461,   463,   465,   467,   469,   471,   473,
     475,   477,   479,   481,   483,   485,   487,   489,   491,   493,
     495,   497,   499,   501,   510,   519,   528,   534,   541,   548,
     555,   562,   568,   575,   582,   590,   597,   605,   612,   618,
     620,   622,   625,   628,   632,   634,   636,   639,   642,   646,
     648,   650,   652,   654,   656,   657,   659,   661,   663,   665,
     667,   669,   671,   673,   675,   677,   679,   681,   683,   685,
     687,   689,   691,   693,   695,   697,   699,   701,   703,   705,
     707,   709,   711,   713,   715,   717,   719,   721,   725,   727,
     730,   736,   738,   740,   742,   744,   746,   748,   752,   754,
     758,   760,   764,   766,   770,   772,   776,   778,   781,   786,
     790,   792,   794,   796,   798,   804,   808,   815,   817,   819,
     821,   823,   825,   827,   829,   831,   833,   835,   837,   839,
     841,   843,   845,   847,   849,   851,   853
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     166,     0,    -1,    -1,    -1,   167,   169,   168,   172,    -1,
      -1,    84,   129,   170,   130,    -1,   170,   171,    -1,   171,
      -1,     3,   137,   164,    -1,     4,   137,   164,    -1,     5,
     137,   164,    -1,     8,   137,     6,    -1,     8,   137,     7,
     164,    -1,     9,   137,   164,    -1,    10,   137,   164,    -1,
     146,   137,   162,    -1,   172,   173,    -1,   173,    -1,    85,
     129,   177,   130,    -1,    -1,    -1,    86,   161,   174,   129,
     189,   175,   191,   130,    -1,    -1,   176,    87,   129,   209,
     130,    -1,   177,   178,    -1,   178,    -1,    -1,   161,   179,
     131,   180,   132,    -1,   181,    -1,   183,    -1,   185,    -1,
     181,   136,   182,    -1,   182,    -1,   187,    -1,    11,   137,
     162,    -1,   183,   136,   184,    -1,   184,    -1,   188,    -1,
      47,   137,   164,    -1,    22,   137,   164,    -1,   185,   136,
     186,    -1,   186,    -1,    23,   137,   164,    -1,    24,   137,
     164,    -1,    25,   137,   164,    -1,    15,    -1,    16,    -1,
      17,    -1,    18,    -1,    19,    -1,    20,    -1,    21,    -1,
      -1,   189,   190,    -1,    85,    12,   161,    -1,    85,    13,
     161,    -1,    85,    14,   161,    -1,   191,   192,    -1,   192,
      -1,   193,    -1,   207,    -1,    27,   161,   194,    -1,    30,
     161,   131,   197,   132,    -1,    28,   161,   131,   199,   132,
      -1,    26,   161,   131,   201,   132,    -1,    29,   161,   131,
     202,   132,    -1,    31,   161,   131,   204,   132,    -1,    32,
     161,    -1,    34,   161,    -1,    33,   161,   131,   206,   132,
      -1,    -1,   131,   195,   132,    -1,   195,   136,   196,    -1,
     196,    -1,   161,   135,   161,    -1,   161,    -1,   197,   136,
     198,    -1,   198,    -1,    42,   137,   164,    -1,    43,   137,
     164,    -1,    44,   137,   164,    -1,    45,   137,   164,    -1,
      46,   137,   164,    -1,   161,   135,   161,    -1,   161,    -1,
     199,   136,   200,    -1,   200,    -1,    35,    -1,    36,    -1,
      37,    -1,    38,    -1,    39,    -1,    41,    -1,    40,    -1,
     161,   135,   161,    -1,   161,    -1,    -1,    47,   137,   164,
      -1,   202,   136,   203,    -1,   203,    -1,    55,   137,   164,
      -1,    56,   137,   164,    -1,    57,   137,   164,    -1,    58,
     137,   164,    -1,    59,   137,   164,    -1,    60,   137,   164,
      -1,   204,   136,   205,    -1,   205,    -1,    61,   137,   164,
      -1,    62,   137,   164,    -1,   113,    -1,   114,    -1,   112,
      -1,   121,    -1,   122,    -1,   123,    -1,   124,    -1,   146,
      -1,   125,    -1,   208,   138,   208,    -1,   161,   135,   161,
      -1,   161,    -1,    -1,    -1,   209,   210,   211,    -1,   217,
      -1,   219,    -1,    -1,   127,   133,   238,   134,   212,   129,
     209,   130,   214,    -1,    -1,   126,   161,   137,   238,   139,
     216,   213,   129,   209,   130,    -1,   161,   137,   238,    -1,
     161,   133,   238,   136,   238,   134,   137,   238,    -1,    -1,
      -1,   128,   215,   129,   209,   130,    -1,   238,    -1,   238,
     139,   238,    -1,   161,   135,   161,   135,   218,   137,   238,
      -1,   161,   135,   218,   137,   238,    -1,    63,    -1,    64,
      -1,    65,    -1,    66,    -1,    67,    -1,    68,    -1,    69,
      -1,    70,    -1,    71,    -1,    72,    -1,    73,    -1,    74,
      -1,    75,    -1,    76,    -1,    77,    -1,    78,    -1,    79,
      -1,    80,    -1,    82,    -1,    81,    -1,    83,    -1,   163,
      -1,   161,   135,   161,   135,   233,   133,   162,   134,    -1,
     161,   135,   161,   135,   234,   133,   235,   134,    -1,   161,
     135,   161,   135,   231,   133,   236,   134,    -1,   161,   135,
     224,   133,   134,    -1,   161,   135,   225,   133,   162,   134,
      -1,   161,   135,   226,   133,   223,   134,    -1,   161,   135,
     227,   133,   238,   134,    -1,   161,   220,   135,   228,   133,
     134,    -1,   161,   135,   228,   133,   134,    -1,   161,   135,
     229,   133,   162,   134,    -1,   161,   135,   230,   133,   161,
     134,    -1,   161,   220,   135,   232,   133,   238,   134,    -1,
     161,   135,   232,   133,   238,   134,    -1,   161,   220,   135,
     231,   133,   236,   134,    -1,   161,   135,   231,   133,   236,
     134,    -1,   131,   221,   136,   222,   132,    -1,   139,    -1,
     238,    -1,   139,   238,    -1,   238,   139,    -1,   238,   139,
     238,    -1,   139,    -1,   238,    -1,   139,   238,    -1,   238,
     139,    -1,   238,   139,   238,    -1,   119,    -1,   117,    -1,
     118,    -1,    49,    -1,    48,    -1,    -1,   161,    -1,    94,
      -1,    95,    -1,    96,    -1,    97,    -1,    98,    -1,    99,
      -1,   100,    -1,   101,    -1,    92,    -1,    91,    -1,    93,
      -1,   102,    -1,   103,    -1,    90,    -1,   104,    -1,   105,
      -1,   106,    -1,   107,    -1,   108,    -1,   109,    -1,   115,
      -1,   116,    -1,   120,    -1,   111,    -1,   112,    -1,   113,
      -1,   114,    -1,   110,    -1,    88,    -1,    89,    -1,   161,
      -1,   161,   135,   161,    -1,   161,    -1,   161,   220,    -1,
     161,   135,   161,   135,   237,    -1,    50,    -1,    51,    -1,
      52,    -1,    53,    -1,    54,    -1,   239,    -1,   238,   245,
     239,    -1,   240,    -1,   239,   246,   240,    -1,   241,    -1,
     240,   247,   241,    -1,   242,    -1,   241,   248,   242,    -1,
     243,    -1,   242,   249,   243,    -1,   244,    -1,   250,   243,
      -1,   251,   133,   243,   134,    -1,   133,   238,   134,    -1,
     161,    -1,   164,    -1,   149,    -1,   150,    -1,   161,   135,
     161,   135,   218,    -1,   161,   135,   218,    -1,   161,   133,
     238,   136,   238,   134,    -1,   151,    -1,   152,    -1,   153,
      -1,   154,    -1,   155,    -1,   156,    -1,   157,    -1,   158,
      -1,   140,    -1,   141,    -1,   142,    -1,   143,    -1,   144,
      -1,   145,    -1,   140,    -1,   141,    -1,   159,    -1,   146,
      -1,   147,    -1,   148,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    64,    64,    68,    64,    75,    77,    81,    82,    85,
      89,    93,    97,   101,   105,   109,   113,   119,   120,   123,
     129,   133,   127,   139,   139,   146,   147,   152,   150,   160,
     164,   168,   174,   175,   179,   183,   189,   190,   193,   197,
     201,   207,   208,   211,   215,   219,   225,   226,   230,   231,
     232,   233,   234,   237,   239,   243,   251,   259,   269,   270,
     273,   274,   277,   284,   294,   304,   316,   327,   338,   346,
     354,   366,   368,   372,   373,   377,   391,   401,   402,   406,
     410,   414,   418,   422,   426,   440,   450,   451,   455,   459,
     463,   467,   471,   475,   479,   483,   497,   509,   511,   520,
     521,   525,   529,   533,   537,   541,   545,   551,   552,   556,
     560,   565,   569,   573,   577,   581,   585,   589,   593,   597,
     603,   609,   613,   618,   622,   620,   629,   630,   634,   632,
     642,   640,   651,   658,   666,   672,   670,   677,   685,   691,
     704,   717,   718,   719,   720,   721,   722,   723,   724,   725,
     726,   727,   728,   729,   730,   731,   732,   733,   734,   735,
     736,   737,   741,   743,   757,   768,   779,   786,   793,   806,
     813,   820,   827,   834,   845,   852,   859,   866,   874,   883,
     891,   895,   902,   909,   918,   926,   930,   937,   944,   948,
     956,   964,   972,   980,   990,   991,   995,   996,   997,   998,
     999,  1000,  1001,  1002,  1006,  1007,  1008,  1012,  1013,  1017,
    1021,  1022,  1023,  1024,  1025,  1026,  1030,  1034,  1038,  1042,
    1043,  1044,  1045,  1046,  1050,  1054,  1057,  1064,  1076,  1085,
    1109,  1126,  1127,  1128,  1129,  1130,  1133,  1135,  1143,  1145,
    1153,  1155,  1163,  1165,  1173,  1175,  1184,  1186,  1193,  1201,
    1203,  1210,  1217,  1224,  1231,  1245,  1257,  1266,  1267,  1270,
    1271,  1274,  1275,  1276,  1277,  1280,  1281,  1284,  1285,  1286,
    1287,  1290,  1291,  1292,  1296,  1297,  1298
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "batch_", "threads_", "seed_", "cpu_",
  "gpu_", "device_", "cuDNN_", "cuBLAS_", "filename_", "tr_", "ts_", "va_",
  "ascii_", "binary_", "gauss_", "uniform_", "ones_", "zeros_", "oneshot_",
  "pos_", "nrows_", "ncolsample_", "ncoltarget_", "F_", "FI_", "FO_", "C_",
  "CI_", "MP_", "CAT_", "O_", "ADD_", "classification_", "regression_",
  "autoencoder_", "max_", "min_", "maxlog_", "minlog_", "nz_", "nr_",
  "nc_", "cr_", "cc_", "numnodes_", "T_", "S_", "W_", "GW_", "B_", "GB_",
  "N_", "nk_", "kr_", "kc_", "rpad_", "cpad_", "stride_", "sizer_",
  "sizec_", "mu_", "mmu_", "l2_", "l1_", "maxn_", "drop_", "noiser_",
  "noisesd_", "brightness_", "contrast_", "lambda_", "noiseb_", "advf_",
  "bn_", "act_", "shift_", "flip_", "adv_", "balance_", "cropmode_",
  "trainable_", "const_", "data_", "network_", "script_", "printkernels_",
  "change_", "train_", "save_", "load_", "testout_", "forward_",
  "backward_", "resetstats_", "printerrors_", "reseterrors_", "trainmode_",
  "testmode_", "update_", "test_", "evaluate_", "zscore_", "center_",
  "yuv_", "maxmin_", "shuffle_", "next_", "set_", "mul_", "div_", "add_",
  "sub_", "store_", "getstats_", "bin_", "int_", "real_", "copy_",
  "imult_", "omult_", "sigmoid_", "tanh_", "relu_", "for_", "if_", "else_",
  "BCB_", "ECB_", "BSB_", "ESB_", "BRB_", "ERB_", "PER_", "COM_", "EQ_",
  "RAR_", "COL_", "MAS_", "MENOS_", "POR_", "DIV_", "MOD_", "PORPOR_",
  "log_", "exp_", "sqr_", "TRUE_", "FALSE_", "AND_", "OR_", "EQUAL_",
  "NOTEQUAL_", "GREAT_", "GREATEQ_", "LESS_", "LESSEQ_", "NOT_", "IFAUX_",
  "id_", "nfile_", "cecho_", "cte_", "$accept", "experiment", "$@1", "$@2",
  "constants", "lconstants", "const", "definitions", "def", "$@3", "$@4",
  "$@5", "ldata", "data", "$@6", "datapar", "ldparfile", "dparfile",
  "ldpargen", "dpargen", "ldparcrea", "dparcrea", "filetype", "gentype",
  "lnetdata", "netdata", "lnetstat", "netstat", "layer", "fiparameter",
  "filparam", "fiparam", "cilparam", "ciparam", "folparam", "foparam",
  "fparam", "clparam", "cparam", "mplparam", "mpparam", "oparam", "edge",
  "namelayer", "lactions", "@7", "actions", "$@8", "$@9", "restif", "$@10",
  "restfor", "amendment", "parameter", "command", "rank", "alpha", "beta",
  "other_data", "comnetvoid", "comnetfile", "comnetdat", "comnetexp",
  "comdatvoid", "comdatfile", "comdatdat", "comcopy", "comdatexp",
  "comlayfile", "comlaydatlay", "datlay", "datcopy", "matweights", "exp",
  "exp_eq", "exp_rel", "exp_add", "exp_mul", "exp_unary", "exp_suf",
  "op_log", "op_eq", "op_rel", "op_add", "op_mul", "op_una", "functions", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   165,   167,   168,   166,   169,   169,   170,   170,   171,
     171,   171,   171,   171,   171,   171,   171,   172,   172,   173,
     174,   175,   173,   176,   173,   177,   177,   179,   178,   180,
     180,   180,   181,   181,   182,   182,   183,   183,   184,   184,
     184,   185,   185,   186,   186,   186,   187,   187,   188,   188,
     188,   188,   188,   189,   189,   190,   190,   190,   191,   191,
     192,   192,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   194,   194,   195,   195,   196,   196,   197,   197,   198,
     198,   198,   198,   198,   198,   198,   199,   199,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   201,   201,   202,
     202,   203,   203,   203,   203,   203,   203,   204,   204,   205,
     205,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     207,   208,   208,   209,   210,   209,   211,   211,   212,   211,
     213,   211,   211,   211,   214,   215,   214,   216,   216,   217,
     217,   218,   218,   218,   218,   218,   218,   218,   218,   218,
     218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
     218,   218,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   220,   221,
     221,   221,   221,   221,   222,   222,   222,   222,   222,   222,
     222,   222,   222,   222,   223,   223,   224,   224,   224,   224,
     224,   224,   224,   224,   225,   225,   225,   226,   226,   227,
     228,   228,   228,   228,   228,   228,   229,   230,   231,   232,
     232,   232,   232,   232,   233,   234,   235,   235,   236,   236,
     236,   237,   237,   237,   237,   237,   238,   238,   239,   239,
     240,   240,   241,   241,   242,   242,   243,   243,   243,   244,
     244,   244,   244,   244,   244,   244,   244,   245,   245,   246,
     246,   247,   247,   247,   247,   248,   248,   249,   249,   249,
     249,   250,   250,   250,   251,   251,   251
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     4,     0,     4,     2,     1,     3,
       3,     3,     3,     4,     3,     3,     3,     2,     1,     4,
       0,     0,     8,     0,     5,     2,     1,     0,     5,     1,
       1,     1,     3,     1,     1,     3,     3,     1,     1,     3,
       3,     3,     1,     3,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     0,     2,     3,     3,     3,     2,     1,
       1,     1,     3,     5,     5,     5,     5,     5,     2,     2,
       5,     0,     3,     3,     1,     3,     1,     3,     1,     3,
       3,     3,     3,     3,     3,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     0,     3,     3,
       1,     3,     3,     3,     3,     3,     3,     3,     1,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     1,     0,     0,     3,     1,     1,     0,     9,
       0,    10,     3,     8,     0,     0,     5,     1,     3,     7,
       5,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     8,     8,     8,     5,     6,     6,     6,
       6,     5,     6,     6,     7,     6,     7,     6,     5,     1,
       1,     2,     2,     3,     1,     1,     2,     2,     3,     1,
       1,     1,     1,     1,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     2,
       5,     1,     1,     1,     1,     1,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     2,     4,     3,
       1,     1,     1,     1,     5,     3,     6,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     5,     1,     0,     3,     0,    23,     0,     0,
       0,     0,     0,     0,     0,     0,     8,     0,     0,     4,
      18,     0,     0,     0,     0,     0,     0,     0,     0,     6,
       7,     0,    20,    17,     0,     9,    10,    11,    12,     0,
      14,    15,    16,    27,     0,    26,     0,   123,    13,     0,
      19,    25,    53,   124,     0,    21,    24,     0,     0,    46,
      47,    48,    49,    50,    51,    52,     0,     0,     0,     0,
       0,     0,    29,    33,    30,    37,    31,    42,    34,    38,
       0,     0,    54,     0,     0,     0,   162,   125,   126,   127,
       0,     0,     0,     0,     0,     0,    28,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   122,     0,    59,    60,    61,     0,     0,     0,
       0,     0,     0,     0,     0,    35,    40,    43,    44,    45,
      39,    32,    36,    41,    55,    56,    57,     0,    71,     0,
       0,     0,     0,    68,     0,    69,     0,    22,    58,     0,
       0,     0,   271,   272,   274,   275,   276,   252,   253,   273,
     250,   251,     0,   236,   238,   240,   242,   244,   246,     0,
       0,   179,     0,   180,     0,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   160,   159,   161,   209,   205,   204,   206,
     196,   197,   198,   199,   200,   201,   202,   203,   207,   208,
     210,   211,   212,   213,   214,   215,   223,   219,   220,   221,
     222,   216,   217,   218,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   132,     0,    97,     0,    62,
       0,     0,     0,     0,     0,   121,   120,     0,     0,     0,
       0,   128,   257,   258,     0,   259,   260,     0,   261,   262,
     263,   264,     0,   265,   266,     0,   267,   268,   269,   270,
       0,   247,     0,   181,     0,   182,     0,     0,     0,     0,
       0,   194,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    76,     0,    74,    88,    89,    90,    91,
      92,    94,    93,    96,     0,    87,     0,     0,     0,     0,
       0,     0,     0,   100,     0,     0,     0,     0,     0,    85,
       0,    78,     0,     0,     0,   108,   113,   111,   112,   114,
     115,   116,   117,   119,   118,     0,     0,   249,     0,     0,
     255,     0,   237,   239,   241,   243,   245,     0,   193,   192,
     190,   191,   189,   184,     0,   185,   183,     0,   224,   225,
       0,     0,     0,     0,   140,   166,     0,   195,     0,     0,
     171,     0,     0,   228,     0,     0,     0,     0,     0,     0,
      65,     0,    72,     0,     0,    64,     0,     0,     0,     0,
       0,     0,     0,    66,     0,     0,     0,     0,     0,     0,
       0,    63,     0,     0,     0,    67,     0,    70,   130,   137,
       0,     0,   123,   248,   186,   178,   187,     0,     0,     0,
       0,     0,   167,   168,   169,   172,   173,     0,   229,   177,
     175,   170,     0,     0,    98,    75,    73,    95,    86,   101,
     102,   103,   104,   105,   106,    99,    79,    80,    81,    82,
      83,    84,    77,   109,   110,   107,     0,     0,     0,   254,
     124,   188,     0,   139,     0,     0,   226,     0,     0,   176,
     174,   123,   138,   256,   134,   133,   165,   163,     0,   164,
       0,   124,   135,   129,   227,   231,   232,   233,   234,   235,
     230,   131,     0,   123,   124,   136
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     7,     5,    15,    16,    19,    20,    46,
      81,    21,    44,    45,    49,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    55,    82,   113,   114,   115,   239,
     294,   295,   320,   321,   304,   305,   292,   312,   313,   324,
     325,   335,   116,   117,    53,    57,    87,   341,   456,   483,
     492,   408,    88,   225,    89,   124,   172,   354,   368,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   362,   363,
     467,   374,   490,   162,   163,   164,   165,   166,   167,   168,
     254,   257,   262,   265,   270,   169,   170
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -400
static const yytype_int16 yypact[] =
{
    -400,    74,    41,  -400,  -111,  -400,    11,   -28,   -46,   -18,
       9,    28,    46,    75,    83,     1,  -400,   103,    -2,   -22,
    -400,   170,   128,   133,   174,   129,   196,   201,   204,  -400,
    -400,   206,  -400,  -400,   202,  -400,  -400,  -400,  -400,   210,
    -400,  -400,  -400,  -400,   -68,  -400,   244,  -400,  -400,   245,
    -400,  -400,  -400,   247,    64,   290,  -400,   -66,   241,  -400,
    -400,  -400,  -400,  -400,  -400,  -400,   242,   243,   248,   282,
     283,   250,   285,  -400,   286,  -400,   287,  -400,  -400,  -400,
     322,    16,  -400,   223,   292,    84,  -400,  -400,  -400,  -400,
     264,   263,   265,   266,   267,   268,  -400,   169,    49,   320,
     272,   273,   274,   275,   277,   278,   279,   280,   281,   284,
     288,   289,   293,     7,  -400,  -400,  -400,   299,   306,   222,
     200,   222,   171,   222,   309,  -400,  -400,  -400,  -400,  -400,
    -400,  -400,  -400,  -400,  -400,  -400,  -400,   315,   316,   317,
     321,   323,   325,  -400,   326,  -400,   294,  -400,  -400,   297,
     222,   222,  -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,
     -21,  -400,   -30,    22,   165,    48,   209,  -400,  -400,   222,
     318,   222,   327,   -49,   -35,  -400,  -400,  -400,  -400,  -400,
    -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,
    -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,
    -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,
    -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,
    -400,  -400,  -400,  -400,   329,   328,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   143,   304,   406,   298,  -400,
     -13,   167,    10,   296,    20,  -400,  -400,    -1,   -24,   222,
     127,  -400,  -400,  -400,   222,  -400,  -400,   222,  -400,  -400,
    -400,  -400,   222,  -400,  -400,   222,  -400,  -400,  -400,  -400,
     222,  -400,   222,   143,   -41,   222,   222,   236,   222,   342,
     300,   314,   222,   343,   319,   330,   331,   222,   345,   346,
     347,   348,   350,   349,    -6,  -400,  -400,  -400,  -400,  -400,
    -400,  -400,  -400,   351,    17,  -400,   352,   353,   356,   357,
     358,   359,    82,  -400,   360,   361,   362,   363,   364,   367,
     123,  -400,   366,   368,   124,  -400,  -400,  -400,  -400,  -400,
    -400,  -400,  -400,  -400,  -400,   355,   222,  -400,   -12,   369,
    -400,   332,    22,   165,    48,   209,  -400,   354,  -400,  -400,
    -400,  -400,  -400,   222,   374,    21,   143,    18,  -400,  -400,
     370,   375,   376,   377,   143,  -400,   378,  -400,   379,    27,
    -400,   380,   381,   158,   382,    30,   383,   331,   222,   365,
    -400,   371,  -400,   298,   372,  -400,   -13,   373,   384,   385,
     386,   387,   388,  -400,   167,   389,   390,   391,   392,   393,
     397,  -400,    10,   395,   396,  -400,   296,  -400,  -400,    35,
     222,   324,  -400,  -400,   143,  -400,   222,   394,   222,   331,
     399,   401,  -400,  -400,  -400,  -400,  -400,   402,  -400,  -400,
    -400,  -400,   400,    77,  -400,  -400,  -400,  -400,  -400,  -400,
    -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,
    -400,  -400,  -400,  -400,  -400,  -400,   398,   222,    79,  -400,
     405,   143,   222,   143,   404,   407,   408,   410,   411,  -400,
    -400,  -400,   143,  -400,   412,   143,  -400,  -400,   403,  -400,
     276,   409,  -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,
    -400,  -400,   413,  -400,   415,  -400
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -400,  -400,  -400,  -400,  -400,  -400,   445,  -400,   464,  -400,
    -400,  -400,  -400,   467,  -400,  -400,  -400,   421,  -400,   422,
    -400,   420,  -400,  -400,  -400,  -400,  -400,   417,  -400,  -400,
    -400,   138,  -400,   120,  -400,   137,  -400,  -400,   130,  -400,
     119,  -400,  -400,   416,  -399,  -400,  -400,  -400,  -400,  -400,
    -400,  -400,  -400,  -248,  -400,   153,  -400,  -400,  -400,  -400,
    -400,  -400,  -400,   311,  -400,  -400,  -204,   344,  -400,  -400,
    -400,  -360,  -400,  -120,   312,   271,   305,   303,  -157,  -400,
    -400,  -400,  -400,  -400,  -400,  -400,  -400
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -24
static const yytype_int16 yytable[] =
{
     173,   174,   340,   235,     8,     9,    10,   348,   349,    11,
      12,    13,   271,   460,     8,     9,    10,   432,     6,    11,
      12,    13,   296,   297,   298,   299,   300,   301,   302,   360,
     247,   248,   289,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   273,   314,   315,   316,   317,   318,    17,    18,   464,
      83,    84,    50,    17,    18,   -23,    61,    62,    63,    64,
      65,    66,   481,   361,     3,    58,   350,   351,   352,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
     275,    22,   151,    43,   494,    85,    70,    86,   353,   152,
     153,   276,   252,   253,   251,   154,   155,   156,   157,   158,
     337,    70,   249,   346,   250,   347,   252,   253,   159,    23,
     160,   252,   253,   161,   410,     4,   382,   252,   253,   338,
     383,    29,   326,   327,   328,    38,    39,   147,   336,   252,
     253,   329,   330,   331,   332,   333,    24,    14,   303,   385,
     252,   253,   417,   386,   355,   356,   357,    14,   364,    32,
     416,   424,   369,   459,   430,    25,   334,   375,   112,   252,
     253,   319,   252,   253,   457,   255,   256,   112,   252,   253,
      58,   252,   253,    26,    59,    60,   252,   253,   263,   264,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   470,    27,   473,   393,   120,   409,   121,   394,   122,
      28,   123,   306,   307,   308,   309,   310,   311,   252,   253,
     252,   253,    31,   414,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   401,   405,    34,   433,   402,
     406,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   339,   120,
     458,   223,    35,   427,   252,   253,   461,    36,   463,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     258,   259,   260,   261,   358,   359,   485,   486,   487,   488,
     489,    47,   224,   151,   100,   101,   102,   472,    37,   171,
     152,   153,   475,    67,    68,    69,   154,   155,   156,   157,
     158,   266,   267,   268,   269,   151,   223,   322,   323,   159,
      40,   160,   152,   153,   161,    41,    42,    43,   154,   155,
     156,   157,   158,    52,    48,    80,    54,    56,    90,    91,
      92,   159,    96,   160,   118,    93,   161,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,    94,
      95,    97,    98,    99,   223,   119,   125,   126,   146,   127,
     128,   129,   130,   134,   135,   136,   137,   149,   138,   139,
     140,   141,   142,   150,   236,   143,   237,   238,   240,   144,
     145,   272,   241,   291,   242,   245,   243,   244,   112,   293,
      30,   412,   366,   274,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   367,   365,   370,   376,   377,
     378,   371,   380,    33,   381,   379,   384,   407,   413,   387,
     388,   372,   373,   389,   390,   391,   392,   395,   396,   397,
     398,   399,   400,   403,   411,   404,   415,   418,   419,   420,
     421,    51,   422,   423,   425,   426,   429,   431,   131,   133,
     132,   436,   452,   438,   445,   455,   428,   471,   343,   434,
     148,   462,   435,   437,   469,   474,     0,   439,   476,   491,
     482,   477,   493,   478,   479,   495,   480,   288,   440,   441,
     442,   443,   444,   446,   447,   448,   449,   450,   451,   453,
     454,   465,   466,   468,   484,   246,   342,   344,   345,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     290
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-400))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
     120,   121,   250,   123,     3,     4,     5,    48,    49,     8,
       9,    10,   169,   412,     3,     4,     5,   377,   129,     8,
       9,    10,    35,    36,    37,    38,    39,    40,    41,   277,
     150,   151,   236,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    26,    27,    28,    29,    30,    31,    32,    33,
      34,   171,    42,    43,    44,    45,    46,    85,    86,   419,
     126,   127,   130,    85,    86,    87,    17,    18,    19,    20,
      21,    22,   471,   277,     0,    11,   117,   118,   119,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
     139,   137,   133,   161,   493,   161,    47,   163,   139,   140,
     141,   136,   151,   152,   134,   146,   147,   148,   149,   150,
     134,    47,   133,   270,   135,   272,   151,   152,   159,   137,
     161,   151,   152,   164,   136,    84,   132,   151,   152,   249,
     136,   130,   112,   113,   114,     6,     7,   130,   139,   151,
     152,   121,   122,   123,   124,   125,   137,   146,   161,   132,
     151,   152,   134,   136,   274,   275,   276,   146,   278,   161,
     139,   134,   282,   411,   134,   137,   146,   287,   161,   151,
     152,   161,   151,   152,   139,   153,   154,   161,   151,   152,
      11,   151,   152,   137,    15,    16,   151,   152,   140,   141,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,   134,   137,   134,   132,   131,   336,   133,   136,   135,
     137,   137,    55,    56,    57,    58,    59,    60,   151,   152,
     151,   152,   129,   353,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,   132,   132,    87,   378,   136,
     136,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   161,   131,
     410,   120,   164,   135,   151,   152,   416,   164,   418,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
     155,   156,   157,   158,    88,    89,    50,    51,    52,    53,
      54,   129,   161,   133,    12,    13,    14,   457,   164,   139,
     140,   141,   462,    23,    24,    25,   146,   147,   148,   149,
     150,   142,   143,   144,   145,   133,   120,    61,    62,   159,
     164,   161,   140,   141,   164,   164,   162,   161,   146,   147,
     148,   149,   150,   129,   164,    85,   131,   130,   137,   137,
     137,   159,   132,   161,   161,   137,   164,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   137,
     137,   136,   136,   136,   120,   133,   162,   164,   135,   164,
     164,   164,   164,   161,   161,   161,   161,   138,   161,   161,
     161,   161,   161,   137,   135,   161,   131,   131,   131,   161,
     161,   133,   131,    47,   131,   161,   131,   131,   161,   161,
      15,   129,   162,   136,   135,   137,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   161,   134,   134,   133,   133,
     133,   162,   132,    19,   135,   137,   135,   132,   134,   137,
     137,   161,   161,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   135,   137,   135,   137,   132,   137,   133,   133,
     133,    44,   134,   134,   134,   134,   134,   134,    97,    99,
      98,   383,   402,   386,   394,   406,   373,   129,   257,   164,
     113,   137,   161,   161,   134,   130,    -1,   164,   134,   130,
     128,   134,   129,   135,   134,   130,   135,   236,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   161,   164,
     164,   162,   161,   161,   161,   149,   254,   262,   265,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     236
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   166,   167,     0,    84,   169,   129,   168,     3,     4,
       5,     8,     9,    10,   146,   170,   171,    85,    86,   172,
     173,   176,   137,   137,   137,   137,   137,   137,   137,   130,
     171,   129,   161,   173,    87,   164,   164,   164,     6,     7,
     164,   164,   162,   161,   177,   178,   174,   129,   164,   179,
     130,   178,   129,   209,   131,   189,   130,   210,    11,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      47,   180,   181,   182,   183,   184,   185,   186,   187,   188,
      85,   175,   190,   126,   127,   161,   163,   211,   217,   219,
     137,   137,   137,   137,   137,   137,   132,   136,   136,   136,
      12,    13,    14,    26,    27,    28,    29,    30,    31,    32,
      33,    34,   161,   191,   192,   193,   207,   208,   161,   133,
     131,   133,   135,   137,   220,   162,   164,   164,   164,   164,
     164,   182,   184,   186,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   135,   130,   192,   138,
     137,   133,   140,   141,   146,   147,   148,   149,   150,   159,
     161,   164,   238,   239,   240,   241,   242,   243,   244,   250,
     251,   139,   221,   238,   238,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   120,   161,   218,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   238,   135,   131,   131,   194,
     131,   131,   131,   131,   131,   161,   208,   238,   238,   133,
     135,   134,   151,   152,   245,   153,   154,   246,   155,   156,
     157,   158,   247,   140,   141,   248,   142,   143,   144,   145,
     249,   243,   133,   238,   136,   139,   136,   135,   137,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   228,   231,
     232,    47,   201,   161,   195,   196,    35,    36,    37,    38,
      39,    40,    41,   161,   199,   200,    55,    56,    57,    58,
      59,    60,   202,   203,    42,    43,    44,    45,    46,   161,
     197,   198,    61,    62,   204,   205,   112,   113,   114,   121,
     122,   123,   124,   125,   146,   206,   139,   134,   238,   161,
     218,   212,   239,   240,   241,   242,   243,   243,    48,    49,
     117,   118,   119,   139,   222,   238,   238,   238,    88,    89,
     218,   231,   233,   234,   238,   134,   162,   161,   223,   238,
     134,   162,   161,   161,   236,   238,   133,   133,   133,   137,
     132,   135,   132,   136,   135,   132,   136,   137,   137,   137,
     137,   137,   137,   132,   136,   137,   137,   137,   137,   137,
     135,   132,   136,   137,   137,   132,   136,   132,   216,   238,
     136,   135,   129,   134,   238,   132,   139,   134,   137,   133,
     133,   133,   134,   134,   134,   134,   134,   135,   220,   134,
     134,   134,   236,   238,   164,   161,   196,   161,   200,   164,
     164,   164,   164,   164,   164,   203,   164,   164,   164,   164,
     164,   161,   198,   164,   164,   205,   213,   139,   238,   218,
     209,   238,   137,   238,   236,   162,   161,   235,   161,   134,
     134,   129,   238,   134,   130,   238,   134,   134,   135,   134,
     135,   209,   128,   214,   161,    50,    51,    52,    53,    54,
     237,   130,   215,   129,   209,   130
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
      yychar = YYLEX;
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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

/* Line 1806 of yacc.c  */
#line 64 "asin.y"
    { begin_experiment(); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 68 "asin.y"
    { get_gconstants(); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 72 "asin.y"
    { end_experiment(); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 87 "asin.y"
    { insert_gconstants(BATCH, (int)(yyvsp[(3) - (3)].creal), ""); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 91 "asin.y"
    { insert_gconstants(THREADS, (int)(yyvsp[(3) - (3)].creal), ""); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 95 "asin.y"
    { insert_gconstants(SEED, (int)(yyvsp[(3) - (3)].creal), ""); }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 99 "asin.y"
    { insert_gconstants(DEVICE, -1, ""); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 103 "asin.y"
    { insert_gconstants(DEVICE, (int)(yyvsp[(4) - (4)].creal), ""); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 107 "asin.y"
    { insert_gconstants(CUDNN, (int)(yyvsp[(3) - (3)].creal), ""); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 111 "asin.y"
    { insert_gconstants(CUBLAS, (int)(yyvsp[(3) - (3)].creal), ""); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 115 "asin.y"
    { insert_gconstants(LOG, -1, (yyvsp[(3) - (3)].ident)); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 125 "asin.y"
    { get_data(); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 129 "asin.y"
    { insert_name_network((yyvsp[(2) - (2)].ident)); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 133 "asin.y"
    { get_net_data(); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 137 "asin.y"
    { get_network(); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 139 "asin.y"
    { create_list_names(); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 152 "asin.y"
    { int k = search_data((yyvsp[(1) - (1)].ident));
	 if (k < 0)  inser_name_data((yyvsp[(1) - (1)].ident));
	 else yyerror("Data name already exists");
       }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 162 "asin.y"
    { check_param_data(FILES); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 166 "asin.y"
    { check_param_data(GENERATED); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 170 "asin.y"
    { check_param_data(CREADATA); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 181 "asin.y"
    { inser_param_data(FILES, "", (yyvsp[(1) - (1)].aux), -1, -1); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 185 "asin.y"
    { inser_param_data(FILES, (yyvsp[(3) - (3)].ident), -1, -1, -1); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 195 "asin.y"
    { inser_param_data(GENERATED, "", (yyvsp[(1) - (1)].aux), -1, -1); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 199 "asin.y"
    { inser_param_data(GENERATED, "", -1, (int)(yyvsp[(3) - (3)].creal), -1); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 203 "asin.y"
    { inser_param_data(GENERATED, "", -1, -1, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 213 "asin.y"
    { inser_param_data(CREADATA, "", (int)(yyvsp[(3) - (3)].creal), -1, -1); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 217 "asin.y"
    { inser_param_data(CREADATA, "", -1, (int)(yyvsp[(3) - (3)].creal), -1); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 221 "asin.y"
    { inser_param_data(CREADATA, "", -1, -1, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 225 "asin.y"
    { (yyval.aux) = ASCII;  }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 226 "asin.y"
    { (yyval.aux) = BINARY; }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 230 "asin.y"
    { (yyval.aux) = GAUSS;  }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 231 "asin.y"
    { (yyval.aux) = UNIFORM; }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 232 "asin.y"
    { (yyval.aux) = ONES;  }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 233 "asin.y"
    { (yyval.aux) = ZEROS;  }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 234 "asin.y"
    { (yyval.aux) = ONESHOT;  }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 245 "asin.y"
    { int k = search_data ((yyvsp[(3) - (3)].ident));
         if (k < 0)
           yyerror("Data name does not exist");
         else inser_param_net_data(TR, k);
       }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 253 "asin.y"
    { int k = search_data ((yyvsp[(3) - (3)].ident));
         if (k < 0)
           yyerror("Data name does not exist");
         else inser_param_net_data(TS, k);
       }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 261 "asin.y"
    { int k = search_data ((yyvsp[(3) - (3)].ident));
         if (k < 0)
           yyerror("Data name does not exist");
         else inser_param_net_data(VA, k);
       }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 279 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (3)].ident));
	 if (k < 0) insert_name_layer((yyvsp[(2) - (3)].ident), FI);
	 else  yyerror("Layer name already exists in this network");
       }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 286 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (5)].ident));
	 if (k < 0) {
	   check_param_layer(3);
	   insert_name_layer((yyvsp[(2) - (5)].ident), CI);
	 }
	 else yyerror("Layer name already exists in this network");
       }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 296 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (5)].ident));
	 if (k < 0) {
	   check_param_layer(1);
	   insert_name_layer((yyvsp[(2) - (5)].ident), FO);
	 }
	 else yyerror("Layer name already exists in this network");
       }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 306 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (5)].ident));
	 if (k >= 0) 
	   yyerror("Layer name already exists in this network");
	 else if ((yyvsp[(4) - (5)].aux) == TRUE) {
	   check_param_layer(1);
	   insert_name_layer((yyvsp[(2) - (5)].ident), F);
	 }
	 else insert_name_layer((yyvsp[(2) - (5)].ident), R);
       }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 318 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (5)].ident));
	 if (k >= 0)
	   yyerror("Layer name already exists in this network");
	 else {
	   check_param_layer(3);
	   insert_name_layer((yyvsp[(2) - (5)].ident), C);
	 }
       }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 329 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (5)].ident));
	 if (k >= 0)
	   yyerror("Layer name already exists in this network");
	 else {
	   check_param_layer(2);
	   insert_name_layer((yyvsp[(2) - (5)].ident), MP);
	 }
       }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 340 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (2)].ident));
	 if (k >= 0) 
	   yyerror("Layer name already exists in this network");
	 else insert_name_layer((yyvsp[(2) - (2)].ident), CAT);
       }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 348 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (2)].ident));
	 if (k >= 0) 
	   yyerror("Layer name already exists in this network");
	 else insert_name_layer((yyvsp[(2) - (2)].ident), ADD);
       }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 356 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (5)].ident));
	 if (k >= 0) 
	   yyerror("Layer name already exists in this network");
	 else {
	   check_param_layer(1);
	   insert_name_layer((yyvsp[(2) - (5)].ident), O);
	 } 
       }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 379 "asin.y"
    { int k2, k1 =  search_network ((yyvsp[(1) - (3)].ident));

	 if (k1 >= 0) {
           k2 = search_layer(k1, (yyvsp[(3) - (3)].ident));
	   if (k2 >= 0) 
	     insert_param_layer(1, k2);
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 393 "asin.y"
    { int k = search_data ((yyvsp[(1) - (1)].ident));
         if (k < 0)
           yyerror("Data name does not exist");
         insert_param_layer(2, k);
       }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 408 "asin.y"
    { insert_param_layer(1, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 412 "asin.y"
    { insert_param_layer(2, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 416 "asin.y"
    { insert_param_layer(3, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 420 "asin.y"
    { insert_param_layer(4, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 424 "asin.y"
    { insert_param_layer(5, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 428 "asin.y"
    { int k2, k1 =  search_network ((yyvsp[(1) - (3)].ident));

	 if (k1 >= 0) {
           k2 = search_layer(k1, (yyvsp[(3) - (3)].ident));
	   if (k2 >= 0) 
	     insert_param_layer(6, k2);
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 442 "asin.y"
    { int k = search_data ((yyvsp[(1) - (1)].ident));
         if (k < 0)
           yyerror("Data name does not exist");
         insert_param_layer(7, k);
       }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 457 "asin.y"
    { insert_param_layer(1, CLASSIFICATION); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 461 "asin.y"
    { insert_param_layer(1, REGRESSION); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 465 "asin.y"
    { insert_param_layer(1, AUTOENCODER); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 469 "asin.y"
    { insert_param_layer(1, MAX); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 473 "asin.y"
    { insert_param_layer(1, MIN); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 477 "asin.y"
    { insert_param_layer(1, MINLOG); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 481 "asin.y"
    { insert_param_layer(1, MAXLOG); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 485 "asin.y"
    { int k2, k1 =  search_network ((yyvsp[(1) - (3)].ident));

	 if (k1 >= 0) {
           k2 = search_layer(k1, (yyvsp[(3) - (3)].ident));
	   if (k2 >= 0) 
	     insert_param_layer(2, k2);
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 499 "asin.y"
    { int k = search_data ((yyvsp[(1) - (1)].ident));
         if (k < 0)
           yyerror("Data name does not exist");
         insert_param_layer(3, k);
       }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 509 "asin.y"
    { (yyval.aux) = FALSE; }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 513 "asin.y"
    { 
         (yyval.aux) = TRUE;
	 insert_param_layer(1, (int)(yyvsp[(3) - (3)].creal));
       }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 527 "asin.y"
    { insert_param_layer(1, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 531 "asin.y"
    { insert_param_layer(2, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 535 "asin.y"
    { insert_param_layer(3, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 539 "asin.y"
    { insert_param_layer(4, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 543 "asin.y"
    { insert_param_layer(5, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 547 "asin.y"
    { insert_param_layer(6, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 558 "asin.y"
    { insert_param_layer(1, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 562 "asin.y"
    { insert_param_layer(2, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 567 "asin.y"
    { insert_param_layer(1, ADDITION); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 571 "asin.y"
    { insert_param_layer(1, SUBTRACTION); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 575 "asin.y"
    { insert_param_layer(1, DIVISION); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 579 "asin.y"
    { insert_param_layer(1, INNERMULT); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 583 "asin.y"
    { insert_param_layer(1, OUTERMULT); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 587 "asin.y"
    { insert_param_layer(1, SIGMOID); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 591 "asin.y"
    { insert_param_layer(1, TANH); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 595 "asin.y"
    { insert_param_layer(1, LOGARITHM); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 599 "asin.y"
    { insert_param_layer(1, RELU); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 605 "asin.y"
    { insert_link((yyvsp[(1) - (3)].aux),(yyvsp[(3) - (3)].aux)); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 611 "asin.y"
    { (yyval.aux) = search_states((yyvsp[(1) - (3)].ident), (yyvsp[(3) - (3)].ident)); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 615 "asin.y"
    { (yyval.aux) = search_states("", (yyvsp[(1) - (1)].ident));  }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 622 "asin.y"
    { (yyval.aux) = pstv; }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 626 "asin.y"
    { pstv = (yyvsp[(2) - (3)].aux); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 634 "asin.y"
    { get_if((yyvsp[(3) - (4)].expre)); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 638 "asin.y"
    { get_endif(); }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 642 "asin.y"
    { ptsymbol t = search_name((yyvsp[(2) - (6)].ident));
         if (t == NULL) t = insert_name((yyvsp[(2) - (6)].ident)); 
         get_for(t, (yyvsp[(4) - (6)].expre), (yyvsp[(6) - (6)].expfor).expre1, (yyvsp[(6) - (6)].expfor).expre2);
       }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 649 "asin.y"
    { get_endfor(); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 653 "asin.y"
    { ptsymbol t = search_name((yyvsp[(1) - (3)].ident));
         if (t == NULL)   t = insert_name((yyvsp[(1) - (3)].ident)); 
         get_exp_eqvar(t, (yyvsp[(3) - (3)].expre)); 
        }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 660 "asin.y"
    { int k =  search_data ((yyvsp[(1) - (8)].ident));
         if (k >= 0)  get_exp_eqelem(k, (yyvsp[(3) - (8)].expre), (yyvsp[(5) - (8)].expre), (yyvsp[(8) - (8)].expre));
         else yyerror("Data name does not exist");
       }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 668 "asin.y"
    { get_else(); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 672 "asin.y"
    { get_else(); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 679 "asin.y"
    { 
         (yyval.expfor).expre1.psymbol = NULL;  (yyval.expfor).expre1.reftemp = cr_var_temp();  
	 get_init_cte((yyval.expfor).expre1.reftemp, 1);
         (yyval.expfor).expre2 = (yyvsp[(1) - (1)].expre);
       }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 687 "asin.y"
    { (yyval.expfor).expre1 = (yyvsp[(1) - (3)].expre); (yyval.expfor).expre2 = (yyvsp[(3) - (3)].expre); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 693 "asin.y"
    { int k2, k1 =  search_network ((yyvsp[(1) - (7)].ident));
	 if (k1 >= 0) {
           k2 = search_layer(k1, (yyvsp[(3) - (7)].ident));
	   if (k2 >= 0)
	     get_amendment(LAYER, k2, (yyvsp[(5) - (7)].aux), (yyvsp[(7) - (7)].expre));
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 706 "asin.y"
    { int k = search_network ((yyvsp[(1) - (5)].ident));
	 if (k >= 0)  get_amendment(NETWORK, k, (yyvsp[(3) - (5)].aux), (yyvsp[(5) - (5)].expre));
	 else { 
	   k = search_data ((yyvsp[(1) - (5)].ident));
	   if (k >= 0)  get_amendment(DATA, k, (yyvsp[(3) - (5)].aux), (yyvsp[(5) - (5)].expre));
	   else yyerror("Data or network name does not exist");
	 }
       }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 717 "asin.y"
    { (yyval.aux) = mu;         }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 718 "asin.y"
    { (yyval.aux) = mmu;        }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 719 "asin.y"
    { (yyval.aux) = l2;         }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 720 "asin.y"
    { (yyval.aux) = l1;         }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 721 "asin.y"
    { (yyval.aux) = maxn;       }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 722 "asin.y"
    { (yyval.aux) = drop;       }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 723 "asin.y"
    { (yyval.aux) = noiser;     }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 724 "asin.y"
    { (yyval.aux) = noisesd;    }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 725 "asin.y"
    { (yyval.aux) = brightness; }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 726 "asin.y"
    { (yyval.aux) = contrast;   }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 727 "asin.y"
    { (yyval.aux) = lambda;     }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 728 "asin.y"
    { (yyval.aux) = noiseb;     }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 729 "asin.y"
    { (yyval.aux) = advf;       }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 730 "asin.y"
    { (yyval.aux) = bn;         }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 731 "asin.y"
    { (yyval.aux) = act;        }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 732 "asin.y"
    { (yyval.aux) = shift;      }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 733 "asin.y"
    { (yyval.aux) = flip;       }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 734 "asin.y"
    { (yyval.aux) = adv;        }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 735 "asin.y"
    { (yyval.aux) = cropmode;   }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 736 "asin.y"
    { (yyval.aux) = balance;    }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 737 "asin.y"
    { (yyval.aux) = trainable;  }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 741 "asin.y"
    { get_echo((yyvsp[(1) - (1)].ident)); }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 745 "asin.y"
    { int k2, k1 =  search_network ((yyvsp[(1) - (8)].ident));

	 if (k1 >= 0) {
           k2 = search_layer(k1, (yyvsp[(3) - (8)].ident));
	   if (k2 >= 0) 
	     get_com_lay_file(k1, k2, (yyvsp[(5) - (8)].aux), (yyvsp[(7) - (8)].ident));
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 759 "asin.y"
    { int d2, d1 =  search_network ((yyvsp[(1) - (8)].ident));
	 if (d1 >= 0) {
	   d2 = search_layer(d1, (yyvsp[(3) - (8)].ident));
	   if (d2 >= 0)  get_com_lay_datlay(d1, d2, (yyvsp[(5) - (8)].aux), (yyvsp[(7) - (8)].aux2).ref, (yyvsp[(7) - (8)].aux2).typ);
	   else yyerror("Destination layer does not exist");
	 }
	 else yyerror("Destination network does not exist");
       }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 770 "asin.y"
    { int k2, k1 =  search_network ((yyvsp[(1) - (8)].ident));
	 if (k1 >= 0) {
	   k2 = search_layer(k1, (yyvsp[(3) - (8)].ident)); 
	   if (k2 >= 0) get_com_lay_copy(k1, k2, (yyvsp[(5) - (8)].aux), (yyvsp[(7) - (8)].ident));
	   else yyerror("Destination layer does not exist");
	 }
	 else yyerror("Destination network does not exist");
       }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 781 "asin.y"
    { int k = search_network ((yyvsp[(1) - (5)].ident));
	 if (k >= 0) get_com_net_void(k, (yyvsp[(3) - (5)].aux));
	 else yyerror("Network name does not exist");
       }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 788 "asin.y"
    { int k = search_network ((yyvsp[(1) - (6)].ident));
	 if (k >= 0)   get_com_net_file(k, (yyvsp[(3) - (6)].aux), (yyvsp[(5) - (6)].ident));
	 else yyerror("Network name does not exist");
       }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 795 "asin.y"
    { int k2, k1 = search_network ((yyvsp[(1) - (6)].ident)); 
	 if (k1 >= 0)  
	   if (strlen((yyvsp[(5) - (6)].ident)) == 0)  get_com_net_dat(k1, (yyvsp[(3) - (6)].aux), -1);
	   else {
	     k2 = search_data ((yyvsp[(5) - (6)].ident));
	     if (k2 >= 0) get_com_net_dat(k1, (yyvsp[(3) - (6)].aux), k2);
	     else  yyerror("Data name does not exist");
	   }
	 else yyerror("Network name does not exist");
       }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 808 "asin.y"
    { int k = search_network ((yyvsp[(1) - (6)].ident));
	 if (k >= 0)  get_com_net_exp(k, (yyvsp[(3) - (6)].aux), (yyvsp[(5) - (6)].expre));
	 else yyerror("Network name does not exist");
       }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 815 "asin.y"
    { int k = search_data ((yyvsp[(1) - (6)].ident));
	 if (k >= 0)	get_com_data_void_rank(k, (yyvsp[(2) - (6)].rango), (yyvsp[(4) - (6)].aux));
         else yyerror("Data name does not exist");
       }
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 822 "asin.y"
    { int k = search_data ((yyvsp[(1) - (5)].ident)); 
	 if (k >= 0)	get_com_data_void(k, (yyvsp[(3) - (5)].aux));
         else yyerror("Data name does not exist");
       }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 829 "asin.y"
    { int k = search_data ((yyvsp[(1) - (6)].ident)); 
         if (k >= 0)	get_com_data_file(k, (yyvsp[(3) - (6)].aux), (yyvsp[(5) - (6)].ident)); 
         else yyerror("Data name does not exist");
       }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 836 "asin.y"
    { int k2, k1 = search_data ((yyvsp[(1) - (6)].ident)); 
         if (k1 >= 0) {
	   k2 = search_data ((yyvsp[(5) - (6)].ident));
	   if (k2 >= 0)  get_com_data_dat(k1, (yyvsp[(3) - (6)].aux), k2);
	   else yyerror("Data name does not exist");
	 }
         else yyerror("Data name does not exist");
       }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 847 "asin.y"
    { int k = search_data ((yyvsp[(1) - (7)].ident));
         if (k >= 0)	get_com_data_exp_rank(k, (yyvsp[(2) - (7)].rango), (yyvsp[(4) - (7)].aux), (yyvsp[(6) - (7)].expre));
         else yyerror("Data name does not exist");
       }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 854 "asin.y"
    { int k = search_data ((yyvsp[(1) - (6)].ident)); 
         if (k >= 0)	get_com_data_exp(k, (yyvsp[(3) - (6)].aux), (yyvsp[(5) - (6)].expre));
         else yyerror("Data name does not exist");
       }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 861 "asin.y"
    { int k = search_data ((yyvsp[(1) - (7)].ident));
 	 if (k >= 0)  get_com_data_copy_rank(k, (yyvsp[(2) - (7)].rango), (yyvsp[(4) - (7)].aux), (yyvsp[(6) - (7)].ident));
	 else yyerror("Data name does not exist");
       }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 868 "asin.y"
    { int k = search_data ((yyvsp[(1) - (6)].ident));
         if (k < 0)  k = inser_new_name_data((yyvsp[(1) - (6)].ident));
	 get_com_data_copy(k, (yyvsp[(3) - (6)].aux), (yyvsp[(5) - (6)].ident));
       }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 876 "asin.y"
    { (yyval.rango).row = (yyvsp[(2) - (5)].aux4); (yyval.rango).col = (yyvsp[(4) - (5)].aux4); }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 885 "asin.y"
    { 
         (yyval.aux4).ini.psymbol = NULL; (yyval.aux4).ini.reftemp = cr_var_temp_cte_1(); 
         (yyval.aux4).fin.psymbol = NULL; (yyval.aux4).fin.reftemp = cr_var_temp_cte_1(); 
         (yyval.aux4).aux = -1; 
       }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 893 "asin.y"
    { (yyval.aux4).ini = (yyval.aux4).fin = (yyvsp[(1) - (1)].expre);  (yyval.aux4).aux = -1; }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 897 "asin.y"
    { 
         (yyval.aux4).ini.psymbol = NULL; (yyval.aux4).ini.reftemp = cr_var_temp_cte_1(); 
         (yyval.aux4).fin = (yyvsp[(2) - (2)].expre); (yyval.aux4).aux = -1; 
       }
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 904 "asin.y"
    { 
         (yyval.aux4).ini = (yyvsp[(1) - (2)].expre); (yyval.aux4).aux = -1; 
         (yyval.aux4).fin.psymbol = NULL; (yyval.aux4).fin.reftemp = cr_var_temp_cte_1(); 
       }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 911 "asin.y"
    { (yyval.aux4).ini = (yyvsp[(1) - (3)].expre); (yyval.aux4).fin = (yyvsp[(3) - (3)].expre); (yyval.aux4).aux = -1; }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 920 "asin.y"
    { 
         (yyval.aux4).ini.psymbol = NULL; (yyval.aux4).ini.reftemp = cr_var_temp_cte_1();
         (yyval.aux4).fin.psymbol = NULL; (yyval.aux4).fin.reftemp = cr_var_temp_cte_1();
         (yyval.aux4).aux = -1; 
       }
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 928 "asin.y"
    { (yyval.aux4).ini = (yyval.aux4).fin = (yyvsp[(1) - (1)].expre);  (yyval.aux4).aux = -1; }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 932 "asin.y"
    { 
         (yyval.aux4).ini.psymbol = NULL; (yyval.aux4).ini.reftemp = cr_var_temp_cte_1();
         (yyval.aux4).fin = (yyvsp[(2) - (2)].expre); (yyval.aux4).aux = -1; 
       }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 939 "asin.y"
    { 
         (yyval.aux4).ini = (yyvsp[(1) - (2)].expre); (yyval.aux4).aux = -1; 
         (yyval.aux4).fin.psymbol = NULL; (yyval.aux4).fin.reftemp = cr_var_temp_cte_1();
       }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 946 "asin.y"
    { (yyval.aux4).ini = (yyvsp[(1) - (3)].expre); (yyval.aux4).fin = (yyvsp[(3) - (3)].expre); (yyval.aux4).aux = -1; }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 950 "asin.y"
    { 
         (yyval.aux4).ini.psymbol = NULL; (yyval.aux4).ini.reftemp = cr_var_temp_cte_1();
         (yyval.aux4).fin.psymbol = NULL; (yyval.aux4).fin.reftemp = cr_var_temp_cte_1();
         (yyval.aux4).aux = REAL; 
       }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 958 "asin.y"
    { 
         (yyval.aux4).ini.psymbol = NULL; (yyval.aux4).ini.reftemp = cr_var_temp_cte_1();
         (yyval.aux4).fin.psymbol = NULL; (yyval.aux4).fin.reftemp = cr_var_temp_cte_1();
         (yyval.aux4).aux = BIN; 
       }
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 966 "asin.y"
    { 
         (yyval.aux4).ini.psymbol = NULL; (yyval.aux4).ini.reftemp = cr_var_temp_cte_1();
         (yyval.aux4).fin.psymbol = NULL; (yyval.aux4).fin.reftemp = cr_var_temp_cte_1();
         (yyval.aux4).aux = INT; 
       }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 974 "asin.y"
    { 
         (yyval.aux4).ini.psymbol = NULL; (yyval.aux4).ini.reftemp = cr_var_temp_cte_1();
         (yyval.aux4).fin.psymbol = NULL; (yyval.aux4).fin.reftemp = cr_var_temp_cte_1();
         (yyval.aux4).aux = SAMPLE; 
       }
    break;

  case 193:

/* Line 1806 of yacc.c  */
#line 982 "asin.y"
    { 
         (yyval.aux4).ini.psymbol = NULL; (yyval.aux4).ini.reftemp = cr_var_temp_cte_1();
         (yyval.aux4).fin.psymbol = NULL; (yyval.aux4).fin.reftemp = cr_var_temp_cte_1();
         (yyval.aux4).aux = TARGET; 
       }
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 990 "asin.y"
    { (yyval.ident) = ""; }
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 991 "asin.y"
    { (yyval.ident) = (yyvsp[(1) - (1)].ident); }
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 995 "asin.y"
    { (yyval.aux) = forward;     }
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 996 "asin.y"
    { (yyval.aux) = backward;    }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 997 "asin.y"
    { (yyval.aux) = resetstats;  }
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 998 "asin.y"
    { (yyval.aux) = printerrors; }
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 999 "asin.y"
    { (yyval.aux) = reseterrors; }
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 1000 "asin.y"
    { (yyval.aux) = trainmode;   }
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 1001 "asin.y"
    { (yyval.aux) = testmode;    }
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 1002 "asin.y"
    { (yyval.aux) = update;      }
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 1006 "asin.y"
    { (yyval.aux) = load;    }
    break;

  case 205:

/* Line 1806 of yacc.c  */
#line 1007 "asin.y"
    { (yyval.aux) = save;    }
    break;

  case 206:

/* Line 1806 of yacc.c  */
#line 1008 "asin.y"
    { (yyval.aux) = testout; }
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 1012 "asin.y"
    { (yyval.aux) = test; }
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 1013 "asin.y"
    { (yyval.aux) = evaluate; }
    break;

  case 209:

/* Line 1806 of yacc.c  */
#line 1017 "asin.y"
    { (yyval.aux) = train; }
    break;

  case 210:

/* Line 1806 of yacc.c  */
#line 1021 "asin.y"
    { (yyval.aux) = zscore;  }
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 1022 "asin.y"
    { (yyval.aux) = center;  }
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 1023 "asin.y"
    { (yyval.aux) = yuv;     }
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 1024 "asin.y"
    { (yyval.aux) = maxmin;  }
    break;

  case 214:

/* Line 1806 of yacc.c  */
#line 1025 "asin.y"
    { (yyval.aux) = shuffle; }
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 1026 "asin.y"
    { (yyval.aux) = next;    }
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 1030 "asin.y"
    { (yyval.aux) = store; }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 1034 "asin.y"
    { (yyval.aux) = getstats; }
    break;

  case 218:

/* Line 1806 of yacc.c  */
#line 1038 "asin.y"
    { (yyval.aux) = copy; }
    break;

  case 219:

/* Line 1806 of yacc.c  */
#line 1042 "asin.y"
    { (yyval.aux) = multiplication; }
    break;

  case 220:

/* Line 1806 of yacc.c  */
#line 1043 "asin.y"
    { (yyval.aux) = division;       }
    break;

  case 221:

/* Line 1806 of yacc.c  */
#line 1044 "asin.y"
    { (yyval.aux) = addition;       }
    break;

  case 222:

/* Line 1806 of yacc.c  */
#line 1045 "asin.y"
    { (yyval.aux) = subtraction;    }
    break;

  case 223:

/* Line 1806 of yacc.c  */
#line 1046 "asin.y"
    { (yyval.aux) = set;            }
    break;

  case 224:

/* Line 1806 of yacc.c  */
#line 1050 "asin.y"
    { (yyval.aux) = printkernels; }
    break;

  case 225:

/* Line 1806 of yacc.c  */
#line 1054 "asin.y"
    { (yyval.aux) = change; }
    break;

  case 226:

/* Line 1806 of yacc.c  */
#line 1059 "asin.y"
    { int k = search_data((yyvsp[(1) - (1)].ident)); (yyval.aux2).ref = (yyval.aux2).typ = -1;
	 if (k >= 0)  (yyval.aux2).ref = k; 
	 else yyerror("Data name does not exist");
       }
    break;

  case 227:

/* Line 1806 of yacc.c  */
#line 1066 "asin.y"
    { int k2, k1 =  search_network ((yyvsp[(1) - (3)].ident)); (yyval.aux2).ref = (yyval.aux2).typ = -1;
	 if (k1 >= 0) {
	   k2 =  search_layer(k1, (yyvsp[(3) - (3)].ident));
	   if (k2 >= 0) { (yyval.aux2).ref = k1; (yyval.aux2).typ = k2; }
	   else yyerror("Source layer does not exist");
	 }
	 else yyerror("Source network does not exist");
       }
    break;

  case 228:

/* Line 1806 of yacc.c  */
#line 1078 "asin.y"
    { int k = search_data((yyvsp[(1) - (1)].ident)); char t[140] = ""; 

	 if (k >= 0)  sprintf(t, "data %s", (yyvsp[(1) - (1)].ident));
	 else yyerror("Data name does not exist");
         (yyval.ident) = t;
       }
    break;

  case 229:

/* Line 1806 of yacc.c  */
#line 1087 "asin.y"
    { char opd1[140], opd2[140], opd3[140], opd4[140], t[140] = "";
         int k = search_data((yyvsp[(1) - (2)].ident)); char *aux; 

	 if (k >= 0)  {
	   strexpre(opd1,(yyvsp[(2) - (2)].rango).row.ini); strexpre(opd2,(yyvsp[(2) - (2)].rango).row.fin);
	   strexpre(opd3,(yyvsp[(2) - (2)].rango).col.ini); strexpre(opd4,(yyvsp[(2) - (2)].rango).col.fin);
	   if ((yyvsp[(2) - (2)].rango).col.aux < 0) aux = "NONE";
	   else 
	     switch ((yyvsp[(2) - (2)].rango).col.aux) {
	     case (REAL):   {aux = "REAL";   break;}
             case (BIN):    {aux = "BIN";    break;}
             case (INT):    {aux = "INT";    break;}
             case (TARGET): {aux = "TARGET"; break;}
             case (SAMPLE): {aux = "SAMPLE"; break;}
           }
	   sprintf(t, "rank %s %s %s %s %s %s", (yyvsp[(1) - (2)].ident), 
		   opd1, opd2, opd3, opd4, aux);
	 }
	 else yyerror("Data name does not exist");
	 (yyval.ident) = t;
       }
    break;

  case 230:

/* Line 1806 of yacc.c  */
#line 1111 "asin.y"
    { int k2, k1 = search_network ((yyvsp[(1) - (5)].ident)); char t[140] = "";

	 if (k1 >= 0) {
           k2 = search_layer(k1, (yyvsp[(3) - (5)].ident));
	   if (k2 >= 0) 
	     sprintf(t, "layer %s %s %s", (yyvsp[(1) - (5)].ident), (yyvsp[(3) - (5)].ident), (yyvsp[(5) - (5)].ident));
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
         (yyval.ident) = t;
       }
    break;

  case 231:

/* Line 1806 of yacc.c  */
#line 1126 "asin.y"
    { (yyval.ident) = "W";  }
    break;

  case 232:

/* Line 1806 of yacc.c  */
#line 1127 "asin.y"
    { (yyval.ident) = "GW"; }
    break;

  case 233:

/* Line 1806 of yacc.c  */
#line 1128 "asin.y"
    { (yyval.ident) = "B";  }
    break;

  case 234:

/* Line 1806 of yacc.c  */
#line 1129 "asin.y"
    { (yyval.ident) = "GB"; }
    break;

  case 235:

/* Line 1806 of yacc.c  */
#line 1130 "asin.y"
    { (yyval.ident) = "N";  }
    break;

  case 236:

/* Line 1806 of yacc.c  */
#line 1133 "asin.y"
    { (yyval.expre) = (yyvsp[(1) - (1)].expre); }
    break;

  case 237:

/* Line 1806 of yacc.c  */
#line 1137 "asin.y"
    { 
         (yyval.expre).psymbol = NULL;  (yyval.expre).reftemp = cr_var_temp();  
	 get_exp_log((yyval.expre).reftemp, (yyvsp[(1) - (3)].expre), (yyvsp[(2) - (3)].aux), (yyvsp[(3) - (3)].expre));
       }
    break;

  case 238:

/* Line 1806 of yacc.c  */
#line 1143 "asin.y"
    { (yyval.expre) = (yyvsp[(1) - (1)].expre); }
    break;

  case 239:

/* Line 1806 of yacc.c  */
#line 1147 "asin.y"
    { 
         (yyval.expre).psymbol = NULL;  (yyval.expre).reftemp = cr_var_temp();  
	 get_exp_eq((yyval.expre).reftemp, (yyvsp[(1) - (3)].expre), (yyvsp[(2) - (3)].aux), (yyvsp[(3) - (3)].expre));
       }
    break;

  case 240:

/* Line 1806 of yacc.c  */
#line 1153 "asin.y"
    { (yyval.expre) = (yyvsp[(1) - (1)].expre); }
    break;

  case 241:

/* Line 1806 of yacc.c  */
#line 1157 "asin.y"
    { 
         (yyval.expre).psymbol = NULL;  (yyval.expre).reftemp = cr_var_temp();  
	 get_exp_rel((yyval.expre).reftemp, (yyvsp[(1) - (3)].expre), (yyvsp[(2) - (3)].aux), (yyvsp[(3) - (3)].expre));
       }
    break;

  case 242:

/* Line 1806 of yacc.c  */
#line 1163 "asin.y"
    { (yyval.expre) = (yyvsp[(1) - (1)].expre); }
    break;

  case 243:

/* Line 1806 of yacc.c  */
#line 1167 "asin.y"
    { 
         (yyval.expre).psymbol = NULL;  (yyval.expre).reftemp = cr_var_temp();  
	 get_exp_add((yyval.expre).reftemp, (yyvsp[(1) - (3)].expre), (yyvsp[(2) - (3)].aux), (yyvsp[(3) - (3)].expre));
       }
    break;

  case 244:

/* Line 1806 of yacc.c  */
#line 1173 "asin.y"
    { (yyval.expre) = (yyvsp[(1) - (1)].expre); }
    break;

  case 245:

/* Line 1806 of yacc.c  */
#line 1177 "asin.y"
    { 
         (yyval.expre).psymbol = NULL;  (yyval.expre).reftemp = cr_var_temp();  
	 get_exp_mul((yyval.expre).reftemp, (yyvsp[(1) - (3)].expre), (yyvsp[(2) - (3)].aux), (yyvsp[(3) - (3)].expre));
       }
    break;

  case 246:

/* Line 1806 of yacc.c  */
#line 1184 "asin.y"
    { (yyval.expre) = (yyvsp[(1) - (1)].expre); }
    break;

  case 247:

/* Line 1806 of yacc.c  */
#line 1188 "asin.y"
    { 
         (yyval.expre).psymbol = NULL;  (yyval.expre).reftemp = cr_var_temp();  
	 get_exp_unary((yyval.expre).reftemp, (yyvsp[(1) - (2)].aux), (yyvsp[(2) - (2)].expre));
       }
    break;

  case 248:

/* Line 1806 of yacc.c  */
#line 1195 "asin.y"
    { 
         (yyval.expre).psymbol = NULL;  (yyval.expre).reftemp = cr_var_temp();  
	 get_functions((yyval.expre).reftemp, (yyvsp[(1) - (4)].aux), (yyvsp[(3) - (4)].expre));
       }
    break;

  case 249:

/* Line 1806 of yacc.c  */
#line 1201 "asin.y"
    { (yyval.expre) = (yyvsp[(2) - (3)].expre); }
    break;

  case 250:

/* Line 1806 of yacc.c  */
#line 1205 "asin.y"
    { 
         (yyval.expre).psymbol = search_name((yyvsp[(1) - (1)].ident));  (yyval.expre).reftemp = -1;
	 if ((yyval.expre).psymbol == NULL) yyerror("Undefined variable name");
       }
    break;

  case 251:

/* Line 1806 of yacc.c  */
#line 1212 "asin.y"
    { 
         (yyval.expre).psymbol = NULL; (yyval.expre).reftemp = cr_var_temp();
         get_init_cte((yyval.expre).reftemp, (yyvsp[(1) - (1)].creal));
       }
    break;

  case 252:

/* Line 1806 of yacc.c  */
#line 1219 "asin.y"
    { 
         (yyval.expre).psymbol = NULL; (yyval.expre).reftemp = cr_var_temp();
         get_init_cte((yyval.expre).reftemp, 1.0);
       }
    break;

  case 253:

/* Line 1806 of yacc.c  */
#line 1226 "asin.y"
    { 
         (yyval.expre).psymbol = NULL; (yyval.expre).reftemp = cr_var_temp();
         get_init_cte((yyval.expre).reftemp, 0.0);
       }
    break;

  case 254:

/* Line 1806 of yacc.c  */
#line 1233 "asin.y"
    { int k2, k1 =  search_network ((yyvsp[(1) - (5)].ident));
         (yyval.expre).psymbol=NULL; (yyval.expre).reftemp = cr_var_temp();
	 if (k1 >= 0) {
           k2 = search_layer(k1, (yyvsp[(3) - (5)].ident));
	   if (k2 >= 0)
	     get_init_amend(LAYER, (yyval.expre).reftemp, k2, (yyvsp[(5) - (5)].aux));
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       }
    break;

  case 255:

/* Line 1806 of yacc.c  */
#line 1247 "asin.y"
    { int k = search_network ((yyvsp[(1) - (3)].ident));
         (yyval.expre).psymbol=NULL; (yyval.expre).reftemp = cr_var_temp();
	 if (k >= 0)  get_init_amend(NETWORK, (yyval.expre).reftemp, k, (yyvsp[(3) - (3)].aux));
	 else { 
	   k = search_data ((yyvsp[(1) - (3)].ident));
	   if (k >= 0)  get_init_amend(DATA, (yyval.expre).reftemp, k, (yyvsp[(3) - (3)].aux));
	   else yyerror("Data or network name does not exist");
	 }
       }
    break;

  case 256:

/* Line 1806 of yacc.c  */
#line 1259 "asin.y"
    { int k =  search_data ((yyvsp[(1) - (6)].ident));
         (yyval.expre).psymbol=NULL; (yyval.expre).reftemp =  cr_var_temp();
	 if (k >= 0)  get_init_elem((yyval.expre).reftemp, k, (yyvsp[(3) - (6)].expre), (yyvsp[(5) - (6)].expre));
	 else yyerror("Data name does not exist");
       }
    break;

  case 257:

/* Line 1806 of yacc.c  */
#line 1266 "asin.y"
    { (yyval.aux) = AND; }
    break;

  case 258:

/* Line 1806 of yacc.c  */
#line 1267 "asin.y"
    { (yyval.aux) = OR;  }
    break;

  case 259:

/* Line 1806 of yacc.c  */
#line 1270 "asin.y"
    { (yyval.aux) = EQUAL;    }
    break;

  case 260:

/* Line 1806 of yacc.c  */
#line 1271 "asin.y"
    { (yyval.aux) = NOTEQUAL; }
    break;

  case 261:

/* Line 1806 of yacc.c  */
#line 1274 "asin.y"
    { (yyval.aux) = GREAT;   }
    break;

  case 262:

/* Line 1806 of yacc.c  */
#line 1275 "asin.y"
    { (yyval.aux) = GREATEQ; }
    break;

  case 263:

/* Line 1806 of yacc.c  */
#line 1276 "asin.y"
    { (yyval.aux) = LESS;    }
    break;

  case 264:

/* Line 1806 of yacc.c  */
#line 1277 "asin.y"
    { (yyval.aux) = LESSEQ;  }
    break;

  case 265:

/* Line 1806 of yacc.c  */
#line 1280 "asin.y"
    { (yyval.aux) = ADDITION; }
    break;

  case 266:

/* Line 1806 of yacc.c  */
#line 1281 "asin.y"
    { (yyval.aux) = SUBTRACTION; }
    break;

  case 267:

/* Line 1806 of yacc.c  */
#line 1284 "asin.y"
    { (yyval.aux) = MULTIPLICATION; }
    break;

  case 268:

/* Line 1806 of yacc.c  */
#line 1285 "asin.y"
    { (yyval.aux) = DIVISION;       }
    break;

  case 269:

/* Line 1806 of yacc.c  */
#line 1286 "asin.y"
    { (yyval.aux) = MODULUS;        }
    break;

  case 270:

/* Line 1806 of yacc.c  */
#line 1287 "asin.y"
    { (yyval.aux) = EXPONET;        }
    break;

  case 271:

/* Line 1806 of yacc.c  */
#line 1290 "asin.y"
    { (yyval.aux) = ADDITION;    }
    break;

  case 272:

/* Line 1806 of yacc.c  */
#line 1291 "asin.y"
    { (yyval.aux) = SUBTRACTION; }
    break;

  case 273:

/* Line 1806 of yacc.c  */
#line 1292 "asin.y"
    { (yyval.aux) = NOT;         }
    break;

  case 274:

/* Line 1806 of yacc.c  */
#line 1296 "asin.y"
    { (yyval.aux) = LOGARITHM;   }
    break;

  case 275:

/* Line 1806 of yacc.c  */
#line 1297 "asin.y"
    { (yyval.aux) = EXPONENTIAL; }
    break;

  case 276:

/* Line 1806 of yacc.c  */
#line 1298 "asin.y"
    { (yyval.aux) = SQUARE;      }
    break;



/* Line 1806 of yacc.c  */
#line 4065 "asin.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 1300 "asin.y"

/*****************************************************************************/
/*****************************************************************************/

