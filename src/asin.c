/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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
     for_ = 375,
     copy_ = 376,
     imult_ = 377,
     omult_ = 378,
     sigmoid_ = 379,
     tanh_ = 380,
     relu_ = 381,
     BCB_ = 382,
     ECB_ = 383,
     BSB_ = 384,
     ESB_ = 385,
     BRB_ = 386,
     ERB_ = 387,
     PER_ = 388,
     COM_ = 389,
     EQ_ = 390,
     RAR_ = 391,
     COL_ = 392,
     MAS_ = 393,
     MENOS_ = 394,
     POR_ = 395,
     DIV_ = 396,
     MOD_ = 397,
     PORPOR_ = 398,
     log_ = 399,
     exp_ = 400,
     sqr_ = 401,
     id_ = 402,
     nfile_ = 403,
     cecho_ = 404,
     cte_ = 405
   };
#endif
/* Tokens.  */
#define batch_ 258
#define threads_ 259
#define seed_ 260
#define cpu_ 261
#define gpu_ 262
#define device_ 263
#define cuDNN_ 264
#define cuBLAS_ 265
#define filename_ 266
#define tr_ 267
#define ts_ 268
#define va_ 269
#define ascii_ 270
#define binary_ 271
#define gauss_ 272
#define uniform_ 273
#define ones_ 274
#define zeros_ 275
#define oneshot_ 276
#define pos_ 277
#define nrows_ 278
#define ncolsample_ 279
#define ncoltarget_ 280
#define F_ 281
#define FI_ 282
#define FO_ 283
#define C_ 284
#define CI_ 285
#define MP_ 286
#define CAT_ 287
#define O_ 288
#define ADD_ 289
#define classification_ 290
#define regression_ 291
#define autoencoder_ 292
#define max_ 293
#define min_ 294
#define maxlog_ 295
#define minlog_ 296
#define nz_ 297
#define nr_ 298
#define nc_ 299
#define cr_ 300
#define cc_ 301
#define numnodes_ 302
#define T_ 303
#define S_ 304
#define W_ 305
#define GW_ 306
#define B_ 307
#define GB_ 308
#define N_ 309
#define nk_ 310
#define kr_ 311
#define kc_ 312
#define rpad_ 313
#define cpad_ 314
#define stride_ 315
#define sizer_ 316
#define sizec_ 317
#define mu_ 318
#define mmu_ 319
#define l2_ 320
#define l1_ 321
#define maxn_ 322
#define drop_ 323
#define noiser_ 324
#define noisesd_ 325
#define brightness_ 326
#define contrast_ 327
#define lambda_ 328
#define noiseb_ 329
#define advf_ 330
#define bn_ 331
#define act_ 332
#define shift_ 333
#define flip_ 334
#define adv_ 335
#define balance_ 336
#define cropmode_ 337
#define trainable_ 338
#define const_ 339
#define data_ 340
#define network_ 341
#define script_ 342
#define printkernels_ 343
#define change_ 344
#define train_ 345
#define save_ 346
#define load_ 347
#define testout_ 348
#define forward_ 349
#define backward_ 350
#define resetstats_ 351
#define printerrors_ 352
#define reseterrors_ 353
#define trainmode_ 354
#define testmode_ 355
#define update_ 356
#define test_ 357
#define evaluate_ 358
#define zscore_ 359
#define center_ 360
#define yuv_ 361
#define maxmin_ 362
#define shuffle_ 363
#define next_ 364
#define set_ 365
#define mul_ 366
#define div_ 367
#define add_ 368
#define sub_ 369
#define store_ 370
#define getstats_ 371
#define bin_ 372
#define int_ 373
#define real_ 374
#define for_ 375
#define copy_ 376
#define imult_ 377
#define omult_ 378
#define sigmoid_ 379
#define tanh_ 380
#define relu_ 381
#define BCB_ 382
#define ECB_ 383
#define BSB_ 384
#define ESB_ 385
#define BRB_ 386
#define ERB_ 387
#define PER_ 388
#define COM_ 389
#define EQ_ 390
#define RAR_ 391
#define COL_ 392
#define MAS_ 393
#define MENOS_ 394
#define POR_ 395
#define DIV_ 396
#define MOD_ 397
#define PORPOR_ 398
#define log_ 399
#define exp_ 400
#define sqr_ 401
#define id_ 402
#define nfile_ 403
#define cecho_ 404
#define cte_ 405




/* Copy the first part of user declarations.  */
#line 1 "asin.y"

/*****************************************************************************/
/**  Syntactic-semantic analyzer, 2016.             <jmbenedi@prhlt.upv.es> **/
/*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nettable.h"


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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 10 "asin.y"
{ /********************************************************************/
  char*   ident;                      /* for the "identifier" terminal       */
  float   creal;                      /* for the "real constant" terminal    */
  int     aux;                        /* For non-terminals with 1 attributes */
  TUPLE   aux2;                       /* For non-terminals with 2 attributes */
  AUX4    aux4;                       /* For non-terminals with 4 attributes */
  RANGO   rango;                      /* For non-terminals with rank         */
  EXPRE   expre;                      /* For non-terminal expression         */
  EXPFOR  expfor;                     /* For two exp of FOR                  */
}
/* Line 193 of yacc.c.  */
#line 417 "asin.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 430 "asin.c"

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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   550

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  151
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  78
/* YYNRULES -- Number of rules.  */
#define YYNRULES  254
/* YYNRULES -- Number of states.  */
#define YYNSTATES  463

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   405

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
     145,   146,   147,   148,   149,   150
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
     405,   409,   418,   420,   424,   432,   438,   440,   442,   444,
     446,   448,   450,   452,   454,   456,   458,   460,   462,   464,
     466,   468,   470,   472,   474,   476,   478,   480,   482,   491,
     500,   509,   515,   522,   529,   536,   543,   549,   556,   563,
     571,   578,   586,   593,   599,   601,   603,   606,   609,   613,
     615,   617,   620,   623,   627,   629,   631,   633,   635,   637,
     638,   640,   642,   644,   646,   648,   650,   652,   654,   656,
     658,   660,   662,   664,   666,   668,   670,   672,   674,   676,
     678,   680,   682,   684,   686,   688,   690,   692,   694,   696,
     698,   700,   702,   706,   708,   711,   717,   719,   721,   723,
     725,   727,   729,   733,   735,   739,   741,   746,   750,   752,
     754,   760,   764,   771,   773,   775,   777,   779,   781,   783,
     785,   788,   791,   793,   795
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     152,     0,    -1,    -1,    -1,   153,   155,   154,   158,    -1,
      -1,    84,   127,   156,   128,    -1,   156,   157,    -1,   157,
      -1,     3,   135,   227,    -1,     4,   135,   227,    -1,     5,
     135,   227,    -1,     8,   135,     6,    -1,     8,   135,     7,
     227,    -1,     9,   135,   227,    -1,    10,   135,   227,    -1,
     144,   135,   148,    -1,   158,   159,    -1,   159,    -1,    85,
     127,   163,   128,    -1,    -1,    -1,    86,   147,   160,   127,
     175,   161,   177,   128,    -1,    -1,   162,    87,   127,   195,
     128,    -1,   163,   164,    -1,   164,    -1,    -1,   147,   165,
     129,   166,   130,    -1,   167,    -1,   169,    -1,   171,    -1,
     167,   134,   168,    -1,   168,    -1,   173,    -1,    11,   135,
     148,    -1,   169,   134,   170,    -1,   170,    -1,   174,    -1,
      47,   135,   227,    -1,    22,   135,   227,    -1,   171,   134,
     172,    -1,   172,    -1,    23,   135,   227,    -1,    24,   135,
     227,    -1,    25,   135,   227,    -1,    15,    -1,    16,    -1,
      17,    -1,    18,    -1,    19,    -1,    20,    -1,    21,    -1,
      -1,   175,   176,    -1,    85,    12,   147,    -1,    85,    13,
     147,    -1,    85,    14,   147,    -1,   177,   178,    -1,   178,
      -1,   179,    -1,   193,    -1,    27,   147,   180,    -1,    30,
     147,   129,   183,   130,    -1,    28,   147,   129,   185,   130,
      -1,    26,   147,   129,   187,   130,    -1,    29,   147,   129,
     188,   130,    -1,    31,   147,   129,   190,   130,    -1,    32,
     147,    -1,    34,   147,    -1,    33,   147,   129,   192,   130,
      -1,    -1,   129,   181,   130,    -1,   181,   134,   182,    -1,
     182,    -1,   147,   133,   147,    -1,   147,    -1,   183,   134,
     184,    -1,   184,    -1,    42,   135,   227,    -1,    43,   135,
     227,    -1,    44,   135,   227,    -1,    45,   135,   227,    -1,
      46,   135,   227,    -1,   147,   133,   147,    -1,   147,    -1,
     185,   134,   186,    -1,   186,    -1,    35,    -1,    36,    -1,
      37,    -1,    38,    -1,    39,    -1,    41,    -1,    40,    -1,
     147,   133,   147,    -1,   147,    -1,    -1,    47,   135,   227,
      -1,   188,   134,   189,    -1,   189,    -1,    55,   135,   227,
      -1,    56,   135,   227,    -1,    57,   135,   227,    -1,    58,
     135,   227,    -1,    59,   135,   227,    -1,    60,   135,   227,
      -1,   190,   134,   191,    -1,   191,    -1,    61,   135,   227,
      -1,    62,   135,   227,    -1,   113,    -1,   114,    -1,   112,
      -1,   122,    -1,   123,    -1,   124,    -1,   125,    -1,   144,
      -1,   126,    -1,   194,   136,   194,    -1,   147,   133,   147,
      -1,   147,    -1,    -1,    -1,   195,   196,   197,    -1,   200,
      -1,   202,    -1,    -1,   120,   147,   135,   221,   137,   199,
     198,   127,   195,   128,    -1,   147,   135,   221,    -1,   147,
     131,   221,   134,   221,   132,   135,   221,    -1,   221,    -1,
     221,   137,   221,    -1,   147,   133,   147,   133,   201,   135,
     221,    -1,   147,   133,   201,   135,   221,    -1,    63,    -1,
      64,    -1,    65,    -1,    66,    -1,    67,    -1,    68,    -1,
      69,    -1,    70,    -1,    71,    -1,    72,    -1,    73,    -1,
      74,    -1,    75,    -1,    76,    -1,    77,    -1,    78,    -1,
      79,    -1,    80,    -1,    82,    -1,    81,    -1,    83,    -1,
     149,    -1,   147,   133,   147,   133,   216,   131,   148,   132,
      -1,   147,   133,   147,   133,   217,   131,   218,   132,    -1,
     147,   133,   147,   133,   214,   131,   219,   132,    -1,   147,
     133,   207,   131,   132,    -1,   147,   133,   208,   131,   148,
     132,    -1,   147,   133,   209,   131,   206,   132,    -1,   147,
     133,   210,   131,   221,   132,    -1,   147,   203,   133,   211,
     131,   132,    -1,   147,   133,   211,   131,   132,    -1,   147,
     133,   212,   131,   148,   132,    -1,   147,   133,   213,   131,
     147,   132,    -1,   147,   203,   133,   215,   131,   221,   132,
      -1,   147,   133,   215,   131,   221,   132,    -1,   147,   203,
     133,   214,   131,   219,   132,    -1,   147,   133,   214,   131,
     219,   132,    -1,   129,   204,   134,   205,   130,    -1,   137,
      -1,   221,    -1,   137,   221,    -1,   221,   137,    -1,   221,
     137,   221,    -1,   137,    -1,   221,    -1,   137,   221,    -1,
     221,   137,    -1,   221,   137,   221,    -1,   119,    -1,   117,
      -1,   118,    -1,    49,    -1,    48,    -1,    -1,   147,    -1,
      94,    -1,    95,    -1,    96,    -1,    97,    -1,    98,    -1,
      99,    -1,   100,    -1,   101,    -1,    92,    -1,    91,    -1,
      93,    -1,   102,    -1,   103,    -1,    90,    -1,   104,    -1,
     105,    -1,   106,    -1,   107,    -1,   108,    -1,   109,    -1,
     115,    -1,   116,    -1,   121,    -1,   111,    -1,   112,    -1,
     113,    -1,   114,    -1,   110,    -1,    88,    -1,    89,    -1,
     147,    -1,   147,   133,   147,    -1,   147,    -1,   147,   203,
      -1,   147,   133,   147,   133,   220,    -1,    50,    -1,    51,
      -1,    52,    -1,    53,    -1,    54,    -1,   222,    -1,   221,
     225,   222,    -1,   223,    -1,   222,   226,   223,    -1,   224,
      -1,   228,   131,   223,   132,    -1,   131,   221,   132,    -1,
     147,    -1,   227,    -1,   147,   133,   147,   133,   201,    -1,
     147,   133,   201,    -1,   147,   131,   221,   134,   221,   132,
      -1,   138,    -1,   139,    -1,   140,    -1,   141,    -1,   142,
      -1,   143,    -1,   150,    -1,   138,   150,    -1,   139,   150,
      -1,   144,    -1,   145,    -1,   146,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    60,    60,    64,    60,    71,    73,    77,    78,    81,
      85,    89,    93,    97,   101,   105,   109,   115,   116,   119,
     125,   129,   123,   135,   135,   142,   143,   148,   146,   156,
     160,   164,   170,   171,   175,   179,   185,   186,   189,   193,
     197,   203,   204,   207,   211,   215,   221,   222,   226,   227,
     228,   229,   230,   233,   235,   239,   247,   255,   265,   266,
     269,   270,   273,   280,   290,   300,   312,   323,   334,   342,
     350,   362,   364,   368,   369,   373,   387,   397,   398,   402,
     406,   410,   414,   418,   422,   436,   446,   447,   451,   455,
     459,   463,   467,   471,   475,   479,   493,   505,   507,   516,
     517,   521,   525,   529,   533,   537,   541,   547,   548,   552,
     556,   561,   565,   569,   573,   577,   581,   585,   589,   593,
     599,   605,   609,   614,   618,   616,   625,   626,   629,   627,
     638,   645,   653,   661,   667,   680,   693,   694,   695,   696,
     697,   698,   699,   700,   701,   702,   703,   704,   705,   706,
     707,   708,   709,   710,   711,   712,   713,   717,   719,   733,
     744,   755,   762,   769,   782,   789,   796,   803,   810,   821,
     828,   835,   842,   850,   859,   867,   871,   878,   885,   894,
     902,   906,   913,   920,   924,   932,   940,   948,   956,   966,
     967,   971,   972,   973,   974,   975,   976,   977,   978,   982,
     983,   984,   988,   989,   993,   997,   998,   999,  1000,  1001,
    1002,  1006,  1010,  1014,  1018,  1019,  1020,  1021,  1022,  1026,
    1030,  1033,  1040,  1052,  1061,  1085,  1102,  1103,  1104,  1105,
    1106,  1109,  1111,  1119,  1121,  1130,  1132,  1140,  1142,  1149,
    1160,  1174,  1186,  1195,  1196,  1199,  1200,  1201,  1202,  1205,
    1206,  1207,  1211,  1212,  1213
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
  "sub_", "store_", "getstats_", "bin_", "int_", "real_", "for_", "copy_",
  "imult_", "omult_", "sigmoid_", "tanh_", "relu_", "BCB_", "ECB_", "BSB_",
  "ESB_", "BRB_", "ERB_", "PER_", "COM_", "EQ_", "RAR_", "COL_", "MAS_",
  "MENOS_", "POR_", "DIV_", "MOD_", "PORPOR_", "log_", "exp_", "sqr_",
  "id_", "nfile_", "cecho_", "cte_", "$accept", "experiment", "@1", "@2",
  "constants", "lconstants", "const", "definitions", "def", "@3", "@4",
  "@5", "ldata", "data", "@6", "datapar", "ldparfile", "dparfile",
  "ldpargen", "dpargen", "ldparcrea", "dparcrea", "filetype", "gentype",
  "lnetdata", "netdata", "lnetstat", "netstat", "layer", "fiparameter",
  "filparam", "fiparam", "cilparam", "ciparam", "folparam", "foparam",
  "fparam", "clparam", "cparam", "mplparam", "mpparam", "oparam", "edge",
  "namelayer", "lactions", "@7", "actions", "@8", "rest", "amendment",
  "parameter", "command", "rank", "alpha", "beta", "other_data",
  "comnetvoid", "comnetfile", "comnetdat", "comnetexp", "comdatvoid",
  "comdatfile", "comdatdat", "comcopy", "comdatexp", "comlayfile",
  "comlaydatlay", "datlay", "datcopy", "matweights", "exp", "exp_mul",
  "exp_unary", "exp_suf", "op_add", "op_mul", "cte", "functions", 0
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
     405
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   151,   153,   154,   152,   155,   155,   156,   156,   157,
     157,   157,   157,   157,   157,   157,   157,   158,   158,   159,
     160,   161,   159,   162,   159,   163,   163,   165,   164,   166,
     166,   166,   167,   167,   168,   168,   169,   169,   170,   170,
     170,   171,   171,   172,   172,   172,   173,   173,   174,   174,
     174,   174,   174,   175,   175,   176,   176,   176,   177,   177,
     178,   178,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   180,   180,   181,   181,   182,   182,   183,   183,   184,
     184,   184,   184,   184,   184,   184,   185,   185,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   187,   187,   188,
     188,   189,   189,   189,   189,   189,   189,   190,   190,   191,
     191,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     193,   194,   194,   195,   196,   195,   197,   197,   198,   197,
     197,   197,   199,   199,   200,   200,   201,   201,   201,   201,
     201,   201,   201,   201,   201,   201,   201,   201,   201,   201,
     201,   201,   201,   201,   201,   201,   201,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   203,   204,   204,   204,   204,   204,   205,
     205,   205,   205,   205,   205,   205,   205,   205,   205,   206,
     206,   207,   207,   207,   207,   207,   207,   207,   207,   208,
     208,   208,   209,   209,   210,   211,   211,   211,   211,   211,
     211,   212,   213,   214,   215,   215,   215,   215,   215,   216,
     217,   218,   218,   219,   219,   219,   220,   220,   220,   220,
     220,   221,   221,   222,   222,   223,   223,   224,   224,   224,
     224,   224,   224,   225,   225,   226,   226,   226,   226,   227,
     227,   227,   228,   228,   228
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
       3,     3,     1,     0,     0,     3,     1,     1,     0,    10,
       3,     8,     1,     3,     7,     5,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     8,     8,
       8,     5,     6,     6,     6,     6,     5,     6,     6,     7,
       6,     7,     6,     5,     1,     1,     2,     2,     3,     1,
       1,     2,     2,     3,     1,     1,     1,     1,     1,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     2,     5,     1,     1,     1,     1,
       1,     1,     3,     1,     3,     1,     4,     3,     1,     1,
       5,     3,     6,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     5,     1,     0,     3,     0,    23,     0,     0,
       0,     0,     0,     0,     0,     0,     8,     0,     0,     4,
      18,     0,     0,     0,     0,     0,     0,     0,     0,     6,
       7,     0,    20,    17,     0,     0,     0,   249,     9,    10,
      11,    12,     0,    14,    15,    16,    27,     0,    26,     0,
     123,   250,   251,    13,     0,    19,    25,    53,   124,     0,
      21,    24,     0,     0,    46,    47,    48,    49,    50,    51,
      52,     0,     0,     0,     0,     0,     0,    29,    33,    30,
      37,    31,    42,    34,    38,     0,     0,    54,     0,     0,
     157,   125,   126,   127,     0,     0,     0,     0,     0,     0,
      28,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   122,     0,    59,    60,
      61,     0,     0,     0,     0,     0,     0,     0,    35,    40,
      43,    44,    45,    39,    32,    36,    41,    55,    56,    57,
       0,    71,     0,     0,     0,     0,    68,     0,    69,     0,
      22,    58,     0,     0,     0,   174,   252,   253,   254,   238,
       0,   175,   231,   233,   235,   239,     0,     0,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   155,   154,   156,   204,
     200,   199,   201,   191,   192,   193,   194,   195,   196,   197,
     198,   202,   203,   205,   206,   207,   208,   209,   210,   218,
     214,   215,   216,   217,   211,   212,   213,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   130,     0,
      97,     0,    62,     0,     0,     0,     0,     0,   121,   120,
       0,     0,   176,     0,     0,     0,   177,   243,   244,     0,
     245,   246,   247,   248,     0,     0,     0,     0,     0,     0,
       0,   189,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    76,     0,    74,    88,    89,    90,    91,
      92,    94,    93,    96,     0,    87,     0,     0,     0,     0,
       0,     0,     0,   100,     0,     0,     0,     0,     0,    85,
       0,    78,     0,     0,     0,   108,   113,   111,   112,   114,
     115,   116,   117,   119,   118,     0,     0,   237,     0,     0,
     241,   188,   187,   185,   186,   184,   179,     0,   180,   178,
     232,   234,     0,     0,   219,   220,     0,     0,     0,     0,
     135,   161,     0,   190,     0,     0,   166,     0,     0,   223,
       0,     0,     0,     0,     0,     0,    65,     0,    72,     0,
       0,    64,     0,     0,     0,     0,     0,     0,     0,    66,
       0,     0,     0,     0,     0,     0,     0,    63,     0,     0,
       0,    67,     0,    70,   128,   132,     0,     0,   181,   173,
     182,   236,     0,     0,     0,     0,     0,   162,   163,   164,
     167,   168,     0,   224,   172,   170,   165,     0,     0,    98,
      75,    73,    95,    86,   101,   102,   103,   104,   105,   106,
      99,    79,    80,    81,    82,    83,    84,    77,   109,   110,
     107,     0,     0,     0,   240,   183,     0,   134,     0,     0,
     221,     0,     0,   171,   169,   123,   133,   242,   131,   160,
     158,     0,   159,     0,   124,   222,   226,   227,   228,   229,
     230,   225,   129
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     7,     5,    15,    16,    19,    20,    49,
      86,    21,    47,    48,    54,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    60,    87,   117,   118,   119,   232,
     274,   275,   300,   301,   284,   285,   272,   292,   293,   304,
     305,   315,   120,   121,    58,    62,    91,   431,   384,    92,
     218,    93,   127,   160,   327,   344,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   338,   339,   441,   350,   461,
     161,   162,   163,   164,   249,   254,   165,   166
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -330
static const yytype_int16 yypact[] =
{
    -330,    25,   -46,  -330,   -55,  -330,    18,     8,   -33,   -23,
      15,    21,    38,    72,    99,     9,  -330,    12,    11,   110,
    -330,   180,   -49,   -49,   -49,   159,   -49,   -49,    87,  -330,
    -330,   118,  -330,  -330,   157,   144,   147,  -330,  -330,  -330,
    -330,  -330,   -49,  -330,  -330,  -330,  -330,  -113,  -330,   169,
    -330,  -330,  -330,  -330,   176,  -330,  -330,  -330,   187,    98,
     241,  -330,   -63,   192,  -330,  -330,  -330,  -330,  -330,  -330,
    -330,   205,   213,   280,   281,   282,   202,   285,  -330,   286,
    -330,   287,  -330,  -330,  -330,   307,    22,  -330,   276,    28,
    -330,  -330,  -330,  -330,   199,   -49,   -49,   -49,   -49,   -49,
    -330,   136,    49,   306,   277,   278,   279,   283,   284,   288,
     289,   290,   291,   292,   293,   294,   295,    13,  -330,  -330,
    -330,   298,   309,   154,   178,   148,   178,   299,  -330,  -330,
    -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,
     300,   304,   313,   316,   318,   319,  -330,   320,  -330,   303,
    -330,  -330,   305,   178,   178,   178,  -330,  -330,  -330,   -48,
     312,   197,   170,  -330,  -330,  -330,   322,    33,  -330,  -330,
    -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,
    -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,
    -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,
    -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,
    -330,  -330,  -330,  -330,  -330,  -330,  -330,   321,   323,   324,
     325,   326,   328,   329,   330,   331,   332,   333,     4,   297,
     375,   327,  -330,    23,   146,   -13,   212,   164,  -330,  -330,
     200,   -51,     4,   178,   296,   -39,   178,  -330,  -330,   178,
    -330,  -330,  -330,  -330,   178,   178,   178,   111,   178,   334,
     335,   337,   178,   336,   338,   340,   341,   178,   339,   342,
     344,   343,   346,   347,  -123,  -330,  -330,  -330,  -330,  -330,
    -330,  -330,  -330,   348,    34,  -330,   350,   354,   355,   356,
     357,   358,   103,  -330,   359,   360,   361,   362,   363,   349,
     172,  -330,   364,   365,   173,  -330,  -330,  -330,  -330,  -330,
    -330,  -330,  -330,  -330,  -330,   371,   178,  -330,   132,   369,
    -330,  -330,  -330,  -330,  -330,  -330,   178,   373,   217,     4,
     170,  -330,   345,   -35,  -330,  -330,   370,   376,   377,   378,
       4,  -330,   372,  -330,   374,    -8,  -330,   379,   380,   -38,
     381,    -6,   382,   341,   178,   -49,  -330,   368,  -330,   327,
     383,  -330,    23,   -49,   -49,   -49,   -49,   -49,   -49,  -330,
     146,   -49,   -49,   -49,   -49,   -49,   384,  -330,   -13,   -49,
     -49,  -330,   212,  -330,  -330,   275,   178,   317,     4,  -330,
     178,  -330,   385,   178,   341,   386,   388,  -330,  -330,  -330,
    -330,  -330,   389,  -330,  -330,  -330,  -330,   387,    -3,  -330,
    -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,
    -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,
    -330,   352,   178,    16,  -330,     4,   178,     4,   390,   391,
     392,   394,   395,  -330,  -330,  -330,     4,  -330,     4,  -330,
    -330,   393,  -330,   229,   396,  -330,  -330,  -330,  -330,  -330,
    -330,  -330,  -330
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -330,  -330,  -330,  -330,  -330,  -330,   412,  -330,   432,  -330,
    -330,  -330,  -330,   418,  -330,  -330,  -330,   366,  -330,   367,
    -330,   407,  -330,  -330,  -330,  -330,  -330,   399,  -330,  -330,
    -330,   112,  -330,    94,  -330,   155,  -330,  -330,   151,  -330,
     145,  -330,  -330,   397,    73,  -330,  -330,  -330,  -330,  -330,
    -241,  -330,   183,  -330,  -330,  -330,  -330,  -330,  -330,  -330,
     308,  -330,  -330,  -147,   310,  -330,  -330,  -330,  -329,  -330,
    -118,   301,   -45,  -330,  -330,  -330,   -22,  -330
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -24
static const yytype_int16 yytable[] =
{
      38,    39,    40,   320,    43,    44,   167,   358,   228,   321,
     322,   359,     8,     9,    10,    55,   336,    11,    12,    13,
      53,     8,     9,    10,   407,     3,    11,    12,    13,   294,
     295,   296,   297,   298,    46,   240,   241,   242,     4,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   107,   108,
     109,   110,   111,   112,   113,   114,   115,    88,   276,   277,
     278,   279,   280,   281,   282,   438,    66,    67,    68,    69,
      70,    71,     6,   129,   130,   131,   132,   133,   323,   324,
     325,   317,   269,   243,    89,   244,    90,   247,   248,    35,
      36,   123,   154,    17,    18,   402,    75,   392,   326,    35,
      36,    37,    22,   247,   248,   156,   157,   158,   159,    63,
     337,    37,    23,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,   399,   318,   405,   328,   329,   444,
     247,   248,   247,   248,   299,   247,   248,    29,   333,    31,
     340,   150,   247,   248,   345,    75,   434,    63,   447,   351,
      24,    64,    65,    14,   247,   248,    25,   123,    32,   124,
     116,   125,    14,   126,   361,    41,    42,   256,   362,   116,
     283,   247,   248,    26,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,    17,    18,   -23,   385,   334,
     335,   286,   287,   288,   289,   290,   291,    27,   388,   331,
     332,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   216,   369,    28,    45,   408,   370,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,    46,   386,    34,   433,   216,
     247,   248,   435,   302,   303,   437,   306,   307,   308,   456,
     457,   458,   459,   460,    50,   154,   309,   310,   311,   312,
     313,   155,    35,    36,    51,   217,    57,    52,   156,   157,
     158,   159,   377,   381,    37,    59,   378,   382,   314,   154,
     250,   251,   252,   253,   446,    61,    35,    36,   448,   104,
     105,   106,   156,   157,   158,   159,    85,    94,    37,    72,
      73,    74,   100,   409,   246,   247,   248,   316,   247,   248,
      95,   414,   415,   416,   417,   418,   419,   128,    96,   421,
     422,   423,   424,   425,   390,   247,   248,   428,   429,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   432,   247,   248,    97,    98,    99,   216,   101,
     102,   103,   271,   122,   137,   138,   139,    30,   149,   230,
     140,   141,   229,   231,   152,   142,   143,   144,   145,   146,
     147,   148,   233,   319,   153,   234,   245,   235,   236,   237,
     238,    33,   116,   255,   257,   259,   260,   261,   258,   262,
     263,   264,   265,   266,   267,    56,   341,   134,   346,   135,
     352,   411,   427,   353,   273,   354,   356,   391,   355,   445,
     357,   360,   376,   342,   343,   363,   347,   348,   349,   364,
     365,   366,   367,   368,   371,   372,   373,   374,   375,   379,
     380,   383,   387,   389,   397,   393,   398,   394,   395,   396,
     136,   400,   401,   404,   406,   410,   151,   413,   454,   443,
     436,   420,   449,   450,   462,   451,   452,   430,   453,     0,
     412,   426,   403,     0,   439,   440,   442,   268,     0,   270,
     455,     0,     0,     0,     0,     0,     0,     0,     0,   239,
     330
};

static const yytype_int16 yycheck[] =
{
      22,    23,    24,   244,    26,    27,   124,   130,   126,    48,
      49,   134,     3,     4,     5,   128,   257,     8,     9,    10,
      42,     3,     4,     5,   353,     0,     8,     9,    10,    42,
      43,    44,    45,    46,   147,   153,   154,   155,    84,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    26,    27,
      28,    29,    30,    31,    32,    33,    34,   120,    35,    36,
      37,    38,    39,    40,    41,   394,    17,    18,    19,    20,
      21,    22,   127,    95,    96,    97,    98,    99,   117,   118,
     119,   132,   229,   131,   147,   133,   149,   138,   139,   138,
     139,   129,   131,    85,    86,   133,    47,   132,   137,   138,
     139,   150,   135,   138,   139,   144,   145,   146,   147,    11,
     257,   150,   135,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,   132,   243,   132,   245,   246,   132,
     138,   139,   138,   139,   147,   138,   139,   128,   256,   127,
     258,   128,   138,   139,   262,    47,   387,    11,   132,   267,
     135,    15,    16,   144,   138,   139,   135,   129,   147,   131,
     147,   133,   144,   135,   130,     6,     7,   134,   134,   147,
     147,   138,   139,   135,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    85,    86,    87,   316,    88,
      89,    55,    56,    57,    58,    59,    60,   135,   326,   254,
     255,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,   121,   130,   135,   148,   354,   134,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   147,   134,    87,   386,   121,
     138,   139,   390,    61,    62,   393,   112,   113,   114,    50,
      51,    52,    53,    54,   127,   131,   122,   123,   124,   125,
     126,   137,   138,   139,   150,   147,   127,   150,   144,   145,
     146,   147,   130,   130,   150,   129,   134,   134,   144,   131,
     140,   141,   142,   143,   432,   128,   138,   139,   436,    12,
      13,    14,   144,   145,   146,   147,    85,   135,   150,    23,
      24,    25,   130,   355,   137,   138,   139,   137,   138,   139,
     135,   363,   364,   365,   366,   367,   368,   148,   135,   371,
     372,   373,   374,   375,   137,   138,   139,   379,   380,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   137,   138,   139,   135,   135,   135,   121,   134,
     134,   134,    47,   147,   147,   147,   147,    15,   133,   129,
     147,   147,   133,   129,   136,   147,   147,   147,   147,   147,
     147,   147,   129,   147,   135,   129,   134,   129,   129,   129,
     147,    19,   147,   131,   133,   131,   131,   131,   135,   131,
     131,   131,   131,   131,   131,    47,   132,   101,   132,   102,
     131,   359,   378,   131,   147,   131,   130,   132,   135,   127,
     133,   133,   133,   148,   147,   135,   148,   147,   147,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   130,   133,   130,   132,   135,   132,   131,   131,   131,
     103,   132,   132,   132,   132,   147,   117,   362,   445,   132,
     135,   370,   132,   132,   128,   133,   132,   382,   133,    -1,
     147,   147,   349,    -1,   148,   147,   147,   229,    -1,   229,
     147,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   152,
     249
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   152,   153,     0,    84,   155,   127,   154,     3,     4,
       5,     8,     9,    10,   144,   156,   157,    85,    86,   158,
     159,   162,   135,   135,   135,   135,   135,   135,   135,   128,
     157,   127,   147,   159,    87,   138,   139,   150,   227,   227,
     227,     6,     7,   227,   227,   148,   147,   163,   164,   160,
     127,   150,   150,   227,   165,   128,   164,   127,   195,   129,
     175,   128,   196,    11,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    47,   166,   167,   168,   169,
     170,   171,   172,   173,   174,    85,   161,   176,   120,   147,
     149,   197,   200,   202,   135,   135,   135,   135,   135,   135,
     130,   134,   134,   134,    12,    13,    14,    26,    27,    28,
      29,    30,    31,    32,    33,    34,   147,   177,   178,   179,
     193,   194,   147,   129,   131,   133,   135,   203,   148,   227,
     227,   227,   227,   227,   168,   170,   172,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   133,
     128,   178,   136,   135,   131,   137,   144,   145,   146,   147,
     204,   221,   222,   223,   224,   227,   228,   221,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   121,   147,   201,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   221,   133,
     129,   129,   180,   129,   129,   129,   129,   129,   147,   194,
     221,   221,   221,   131,   133,   134,   137,   138,   139,   225,
     140,   141,   142,   143,   226,   131,   134,   133,   135,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   211,   214,
     215,    47,   187,   147,   181,   182,    35,    36,    37,    38,
      39,    40,    41,   147,   185,   186,    55,    56,    57,    58,
      59,    60,   188,   189,    42,    43,    44,    45,    46,   147,
     183,   184,    61,    62,   190,   191,   112,   113,   114,   122,
     123,   124,   125,   126,   144,   192,   137,   132,   221,   147,
     201,    48,    49,   117,   118,   119,   137,   205,   221,   221,
     222,   223,   223,   221,    88,    89,   201,   214,   216,   217,
     221,   132,   148,   147,   206,   221,   132,   148,   147,   147,
     219,   221,   131,   131,   131,   135,   130,   133,   130,   134,
     133,   130,   134,   135,   135,   135,   135,   135,   135,   130,
     134,   135,   135,   135,   135,   135,   133,   130,   134,   135,
     135,   130,   134,   130,   199,   221,   134,   133,   221,   130,
     137,   132,   132,   135,   131,   131,   131,   132,   132,   132,
     132,   132,   133,   203,   132,   132,   132,   219,   221,   227,
     147,   182,   147,   186,   227,   227,   227,   227,   227,   227,
     189,   227,   227,   227,   227,   227,   147,   184,   227,   227,
     191,   198,   137,   221,   201,   221,   135,   221,   219,   148,
     147,   218,   147,   132,   132,   127,   221,   132,   221,   132,
     132,   133,   132,   133,   195,   147,    50,    51,    52,    53,
      54,   220,   128
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
#line 60 "asin.y"
    { begin_experiment(); ;}
    break;

  case 3:
#line 64 "asin.y"
    { get_gconstants(); ;}
    break;

  case 4:
#line 68 "asin.y"
    { end_experiment(); ;}
    break;

  case 9:
#line 83 "asin.y"
    { insert_gconstants(BATCH, (int)(yyvsp[(3) - (3)].creal), ""); ;}
    break;

  case 10:
#line 87 "asin.y"
    { insert_gconstants(THREADS, (int)(yyvsp[(3) - (3)].creal), ""); ;}
    break;

  case 11:
#line 91 "asin.y"
    { insert_gconstants(SEED, (int)(yyvsp[(3) - (3)].creal), ""); ;}
    break;

  case 12:
#line 95 "asin.y"
    { insert_gconstants(DEVICE, -1, ""); ;}
    break;

  case 13:
#line 99 "asin.y"
    { insert_gconstants(DEVICE, (int)(yyvsp[(4) - (4)].creal), ""); ;}
    break;

  case 14:
#line 103 "asin.y"
    { insert_gconstants(CUDNN, (int)(yyvsp[(3) - (3)].creal), ""); ;}
    break;

  case 15:
#line 107 "asin.y"
    { insert_gconstants(CUBLAS, (int)(yyvsp[(3) - (3)].creal), ""); ;}
    break;

  case 16:
#line 111 "asin.y"
    { insert_gconstants(LOG, -1, (yyvsp[(3) - (3)].ident)); ;}
    break;

  case 19:
#line 121 "asin.y"
    { get_data(); ;}
    break;

  case 20:
#line 125 "asin.y"
    { insert_name_network((yyvsp[(2) - (2)].ident)); ;}
    break;

  case 21:
#line 129 "asin.y"
    { get_net_data(); ;}
    break;

  case 22:
#line 133 "asin.y"
    { get_network(); ;}
    break;

  case 23:
#line 135 "asin.y"
    { create_list_names(); ;}
    break;

  case 27:
#line 148 "asin.y"
    { int k = search_data((yyvsp[(1) - (1)].ident));
	 if (k < 0)  inser_name_data((yyvsp[(1) - (1)].ident));
	 else yyerror("Data name already exists");
       ;}
    break;

  case 29:
#line 158 "asin.y"
    { check_param_data(FILES); ;}
    break;

  case 30:
#line 162 "asin.y"
    { check_param_data(GENERATED); ;}
    break;

  case 31:
#line 166 "asin.y"
    { check_param_data(CREADATA); ;}
    break;

  case 34:
#line 177 "asin.y"
    { inser_param_data(FILES, "", (yyvsp[(1) - (1)].aux), -1, -1); ;}
    break;

  case 35:
#line 181 "asin.y"
    { inser_param_data(FILES, (yyvsp[(3) - (3)].ident), -1, -1, -1); ;}
    break;

  case 38:
#line 191 "asin.y"
    { inser_param_data(GENERATED, "", (yyvsp[(1) - (1)].aux), -1, -1); ;}
    break;

  case 39:
#line 195 "asin.y"
    { inser_param_data(GENERATED, "", -1, (int)(yyvsp[(3) - (3)].creal), -1); ;}
    break;

  case 40:
#line 199 "asin.y"
    { inser_param_data(GENERATED, "", -1, -1, (int)(yyvsp[(3) - (3)].creal)); ;}
    break;

  case 43:
#line 209 "asin.y"
    { inser_param_data(CREADATA, "", (int)(yyvsp[(3) - (3)].creal), -1, -1); ;}
    break;

  case 44:
#line 213 "asin.y"
    { inser_param_data(CREADATA, "", -1, (int)(yyvsp[(3) - (3)].creal), -1); ;}
    break;

  case 45:
#line 217 "asin.y"
    { inser_param_data(CREADATA, "", -1, -1, (int)(yyvsp[(3) - (3)].creal)); ;}
    break;

  case 46:
#line 221 "asin.y"
    { (yyval.aux) = ASCII;  ;}
    break;

  case 47:
#line 222 "asin.y"
    { (yyval.aux) = BINARY; ;}
    break;

  case 48:
#line 226 "asin.y"
    { (yyval.aux) = GAUSS;  ;}
    break;

  case 49:
#line 227 "asin.y"
    { (yyval.aux) = UNIFORM; ;}
    break;

  case 50:
#line 228 "asin.y"
    { (yyval.aux) = ONES;  ;}
    break;

  case 51:
#line 229 "asin.y"
    { (yyval.aux) = ZEROS;  ;}
    break;

  case 52:
#line 230 "asin.y"
    { (yyval.aux) = ONESHOT;  ;}
    break;

  case 55:
#line 241 "asin.y"
    { int k = search_data ((yyvsp[(3) - (3)].ident));
         if (k < 0)
           yyerror("Data name does not exist");
         else inser_param_net_data(TR, k);
       ;}
    break;

  case 56:
#line 249 "asin.y"
    { int k = search_data ((yyvsp[(3) - (3)].ident));
         if (k < 0)
           yyerror("Data name does not exist");
         else inser_param_net_data(TS, k);
       ;}
    break;

  case 57:
#line 257 "asin.y"
    { int k = search_data ((yyvsp[(3) - (3)].ident));
         if (k < 0)
           yyerror("Data name does not exist");
         else inser_param_net_data(VA, k);
       ;}
    break;

  case 62:
#line 275 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (3)].ident));
	 if (k < 0) insert_name_layer((yyvsp[(2) - (3)].ident), FI);
	 else  yyerror("Layer name already exists in this network");
       ;}
    break;

  case 63:
#line 282 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (5)].ident));
	 if (k < 0) {
	   check_param_layer(3);
	   insert_name_layer((yyvsp[(2) - (5)].ident), CI);
	 }
	 else yyerror("Layer name already exists in this network");
       ;}
    break;

  case 64:
#line 292 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (5)].ident));
	 if (k < 0) {
	   check_param_layer(1);
	   insert_name_layer((yyvsp[(2) - (5)].ident), FO);
	 }
	 else yyerror("Layer name already exists in this network");
       ;}
    break;

  case 65:
#line 302 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (5)].ident));
	 if (k >= 0) 
	   yyerror("Layer name already exists in this network");
	 else if ((yyvsp[(4) - (5)].aux) == TRUE) {
	   check_param_layer(1);
	   insert_name_layer((yyvsp[(2) - (5)].ident), F);
	 }
	 else insert_name_layer((yyvsp[(2) - (5)].ident), R);
       ;}
    break;

  case 66:
#line 314 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (5)].ident));
	 if (k >= 0)
	   yyerror("Layer name already exists in this network");
	 else {
	   check_param_layer(3);
	   insert_name_layer((yyvsp[(2) - (5)].ident), C);
	 }
       ;}
    break;

  case 67:
#line 325 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (5)].ident));
	 if (k >= 0)
	   yyerror("Layer name already exists in this network");
	 else {
	   check_param_layer(2);
	   insert_name_layer((yyvsp[(2) - (5)].ident), MP);
	 }
       ;}
    break;

  case 68:
#line 336 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (2)].ident));
	 if (k >= 0) 
	   yyerror("Layer name already exists in this network");
	 else insert_name_layer((yyvsp[(2) - (2)].ident), CAT);
       ;}
    break;

  case 69:
#line 344 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (2)].ident));
	 if (k >= 0) 
	   yyerror("Layer name already exists in this network");
	 else insert_name_layer((yyvsp[(2) - (2)].ident), ADD);
       ;}
    break;

  case 70:
#line 352 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (5)].ident));
	 if (k >= 0) 
	   yyerror("Layer name already exists in this network");
	 else {
	   check_param_layer(1);
	   insert_name_layer((yyvsp[(2) - (5)].ident), O);
	 } 
       ;}
    break;

  case 75:
#line 375 "asin.y"
    { int k2, k1 =  search_network ((yyvsp[(1) - (3)].ident));

	 if (k1 >= 0) {
           k2 = search_layer(k1, (yyvsp[(3) - (3)].ident));
	   if (k2 >= 0) 
	     insert_param_layer(1, k2);
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       ;}
    break;

  case 76:
#line 389 "asin.y"
    { int k = search_data ((yyvsp[(1) - (1)].ident));
         if (k < 0)
           yyerror("Data name does not exist");
         insert_param_layer(2, k);
       ;}
    break;

  case 79:
#line 404 "asin.y"
    { insert_param_layer(1, (int)(yyvsp[(3) - (3)].creal)); ;}
    break;

  case 80:
#line 408 "asin.y"
    { insert_param_layer(2, (int)(yyvsp[(3) - (3)].creal)); ;}
    break;

  case 81:
#line 412 "asin.y"
    { insert_param_layer(3, (int)(yyvsp[(3) - (3)].creal)); ;}
    break;

  case 82:
#line 416 "asin.y"
    { insert_param_layer(4, (int)(yyvsp[(3) - (3)].creal)); ;}
    break;

  case 83:
#line 420 "asin.y"
    { insert_param_layer(5, (int)(yyvsp[(3) - (3)].creal)); ;}
    break;

  case 84:
#line 424 "asin.y"
    { int k2, k1 =  search_network ((yyvsp[(1) - (3)].ident));

	 if (k1 >= 0) {
           k2 = search_layer(k1, (yyvsp[(3) - (3)].ident));
	   if (k2 >= 0) 
	     insert_param_layer(6, k2);
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       ;}
    break;

  case 85:
#line 438 "asin.y"
    { int k = search_data ((yyvsp[(1) - (1)].ident));
         if (k < 0)
           yyerror("Data name does not exist");
         insert_param_layer(7, k);
       ;}
    break;

  case 88:
#line 453 "asin.y"
    { insert_param_layer(1, CLASSIFICATION); ;}
    break;

  case 89:
#line 457 "asin.y"
    { insert_param_layer(1, REGRESSION); ;}
    break;

  case 90:
#line 461 "asin.y"
    { insert_param_layer(1, AUTOENCODER); ;}
    break;

  case 91:
#line 465 "asin.y"
    { insert_param_layer(1, MAX); ;}
    break;

  case 92:
#line 469 "asin.y"
    { insert_param_layer(1, MIN); ;}
    break;

  case 93:
#line 473 "asin.y"
    { insert_param_layer(1, MINLOG); ;}
    break;

  case 94:
#line 477 "asin.y"
    { insert_param_layer(1, MAXLOG); ;}
    break;

  case 95:
#line 481 "asin.y"
    { int k2, k1 =  search_network ((yyvsp[(1) - (3)].ident));

	 if (k1 >= 0) {
           k2 = search_layer(k1, (yyvsp[(3) - (3)].ident));
	   if (k2 >= 0) 
	     insert_param_layer(2, k2);
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       ;}
    break;

  case 96:
#line 495 "asin.y"
    { int k = search_data ((yyvsp[(1) - (1)].ident));
         if (k < 0)
           yyerror("Data name does not exist");
         insert_param_layer(3, k);
       ;}
    break;

  case 97:
#line 505 "asin.y"
    { (yyval.aux) = FALSE; ;}
    break;

  case 98:
#line 509 "asin.y"
    { 
         (yyval.aux) = TRUE;
	 insert_param_layer(1, (int)(yyvsp[(3) - (3)].creal));
       ;}
    break;

  case 101:
#line 523 "asin.y"
    { insert_param_layer(1, (int)(yyvsp[(3) - (3)].creal)); ;}
    break;

  case 102:
#line 527 "asin.y"
    { insert_param_layer(2, (int)(yyvsp[(3) - (3)].creal)); ;}
    break;

  case 103:
#line 531 "asin.y"
    { insert_param_layer(3, (int)(yyvsp[(3) - (3)].creal)); ;}
    break;

  case 104:
#line 535 "asin.y"
    { insert_param_layer(4, (int)(yyvsp[(3) - (3)].creal)); ;}
    break;

  case 105:
#line 539 "asin.y"
    { insert_param_layer(5, (int)(yyvsp[(3) - (3)].creal)); ;}
    break;

  case 106:
#line 543 "asin.y"
    { insert_param_layer(6, (int)(yyvsp[(3) - (3)].creal)); ;}
    break;

  case 109:
#line 554 "asin.y"
    { insert_param_layer(1, (int)(yyvsp[(3) - (3)].creal)); ;}
    break;

  case 110:
#line 558 "asin.y"
    { insert_param_layer(2, (int)(yyvsp[(3) - (3)].creal)); ;}
    break;

  case 111:
#line 563 "asin.y"
    { insert_param_layer(1, ADDITION); ;}
    break;

  case 112:
#line 567 "asin.y"
    { insert_param_layer(1, SUBTRACTION); ;}
    break;

  case 113:
#line 571 "asin.y"
    { insert_param_layer(1, DIVISION); ;}
    break;

  case 114:
#line 575 "asin.y"
    { insert_param_layer(1, INNERMULT); ;}
    break;

  case 115:
#line 579 "asin.y"
    { insert_param_layer(1, OUTERMULT); ;}
    break;

  case 116:
#line 583 "asin.y"
    { insert_param_layer(1, SIGMOID); ;}
    break;

  case 117:
#line 587 "asin.y"
    { insert_param_layer(1, TANH); ;}
    break;

  case 118:
#line 591 "asin.y"
    { insert_param_layer(1, LOGARITHM); ;}
    break;

  case 119:
#line 595 "asin.y"
    { insert_param_layer(1, RELU); ;}
    break;

  case 120:
#line 601 "asin.y"
    { insert_link((yyvsp[(1) - (3)].aux),(yyvsp[(3) - (3)].aux)); ;}
    break;

  case 121:
#line 607 "asin.y"
    { (yyval.aux) = search_states((yyvsp[(1) - (3)].ident), (yyvsp[(3) - (3)].ident)); ;}
    break;

  case 122:
#line 611 "asin.y"
    { (yyval.aux) = search_states("", (yyvsp[(1) - (1)].ident));  ;}
    break;

  case 124:
#line 618 "asin.y"
    { (yyval.aux) = pstv; ;}
    break;

  case 125:
#line 622 "asin.y"
    { pstv = (yyvsp[(2) - (3)].aux); ;}
    break;

  case 128:
#line 629 "asin.y"
    { ptsymbol t = search_name((yyvsp[(2) - (6)].ident));
         if (t == NULL) t = insert_name((yyvsp[(2) - (6)].ident)); 
         get_for(t, (yyvsp[(4) - (6)].expre), (yyvsp[(6) - (6)].expfor).expre1, (yyvsp[(6) - (6)].expfor).expre2);
       ;}
    break;

  case 129:
#line 636 "asin.y"
    { get_endfor(); ;}
    break;

  case 130:
#line 640 "asin.y"
    { ptsymbol t = search_name((yyvsp[(1) - (3)].ident));
         if (t == NULL)   t = insert_name((yyvsp[(1) - (3)].ident)); 
         get_exp_eqvar(t, (yyvsp[(3) - (3)].expre)); 
        ;}
    break;

  case 131:
#line 647 "asin.y"
    { int k =  search_data ((yyvsp[(1) - (8)].ident));
         if (k >= 0)  get_exp_eqelem(k, (yyvsp[(3) - (8)].expre), (yyvsp[(5) - (8)].expre), (yyvsp[(8) - (8)].expre));
         else yyerror("Data name does not exist");
       ;}
    break;

  case 132:
#line 655 "asin.y"
    { 
         (yyval.expfor).expre1.psymbol = NULL;  (yyval.expfor).expre1.reftemp = cr_var_temp();  
	 get_init_cte((yyval.expfor).expre1.reftemp, 1);
         (yyval.expfor).expre2 = (yyvsp[(1) - (1)].expre);
       ;}
    break;

  case 133:
#line 663 "asin.y"
    { (yyval.expfor).expre1 = (yyvsp[(1) - (3)].expre); (yyval.expfor).expre2 = (yyvsp[(3) - (3)].expre); ;}
    break;

  case 134:
#line 669 "asin.y"
    { int k2, k1 =  search_network ((yyvsp[(1) - (7)].ident));
	 if (k1 >= 0) {
           k2 = search_layer(k1, (yyvsp[(3) - (7)].ident));
	   if (k2 >= 0)
	     get_amendment(LAYER, k2, (yyvsp[(5) - (7)].aux), (yyvsp[(7) - (7)].expre));
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       ;}
    break;

  case 135:
#line 682 "asin.y"
    { int k = search_network ((yyvsp[(1) - (5)].ident));
	 if (k >= 0)  get_amendment(NETWORK, k, (yyvsp[(3) - (5)].aux), (yyvsp[(5) - (5)].expre));
	 else { 
	   k = search_data ((yyvsp[(1) - (5)].ident));
	   if (k >= 0)  get_amendment(DATA, k, (yyvsp[(3) - (5)].aux), (yyvsp[(5) - (5)].expre));
	   else yyerror("Data or network name does not exist");
	 }
       ;}
    break;

  case 136:
#line 693 "asin.y"
    { (yyval.aux) = mu;         ;}
    break;

  case 137:
#line 694 "asin.y"
    { (yyval.aux) = mmu;        ;}
    break;

  case 138:
#line 695 "asin.y"
    { (yyval.aux) = l2;         ;}
    break;

  case 139:
#line 696 "asin.y"
    { (yyval.aux) = l1;         ;}
    break;

  case 140:
#line 697 "asin.y"
    { (yyval.aux) = maxn;       ;}
    break;

  case 141:
#line 698 "asin.y"
    { (yyval.aux) = drop;       ;}
    break;

  case 142:
#line 699 "asin.y"
    { (yyval.aux) = noiser;     ;}
    break;

  case 143:
#line 700 "asin.y"
    { (yyval.aux) = noisesd;    ;}
    break;

  case 144:
#line 701 "asin.y"
    { (yyval.aux) = brightness; ;}
    break;

  case 145:
#line 702 "asin.y"
    { (yyval.aux) = contrast;   ;}
    break;

  case 146:
#line 703 "asin.y"
    { (yyval.aux) = lambda;     ;}
    break;

  case 147:
#line 704 "asin.y"
    { (yyval.aux) = noiseb;     ;}
    break;

  case 148:
#line 705 "asin.y"
    { (yyval.aux) = advf;       ;}
    break;

  case 149:
#line 706 "asin.y"
    { (yyval.aux) = bn;         ;}
    break;

  case 150:
#line 707 "asin.y"
    { (yyval.aux) = act;        ;}
    break;

  case 151:
#line 708 "asin.y"
    { (yyval.aux) = shift;      ;}
    break;

  case 152:
#line 709 "asin.y"
    { (yyval.aux) = flip;       ;}
    break;

  case 153:
#line 710 "asin.y"
    { (yyval.aux) = adv;        ;}
    break;

  case 154:
#line 711 "asin.y"
    { (yyval.aux) = cropmode;   ;}
    break;

  case 155:
#line 712 "asin.y"
    { (yyval.aux) = balance;    ;}
    break;

  case 156:
#line 713 "asin.y"
    { (yyval.aux) = trainable;  ;}
    break;

  case 157:
#line 717 "asin.y"
    { get_echo((yyvsp[(1) - (1)].ident)); ;}
    break;

  case 158:
#line 721 "asin.y"
    { int k2, k1 =  search_network ((yyvsp[(1) - (8)].ident));

	 if (k1 >= 0) {
           k2 = search_layer(k1, (yyvsp[(3) - (8)].ident));
	   if (k2 >= 0) 
	     get_com_lay_file(k1, k2, (yyvsp[(5) - (8)].aux), (yyvsp[(7) - (8)].ident));
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       ;}
    break;

  case 159:
#line 735 "asin.y"
    { int d2, d1 =  search_network ((yyvsp[(1) - (8)].ident));
	 if (d1 >= 0) {
	   d2 = search_layer(d1, (yyvsp[(3) - (8)].ident));
	   if (d2 >= 0)  get_com_lay_datlay(d1, d2, (yyvsp[(5) - (8)].aux), (yyvsp[(7) - (8)].aux2).ref, (yyvsp[(7) - (8)].aux2).typ);
	   else yyerror("Destination layer does not exist");
	 }
	 else yyerror("Destination network does not exist");
       ;}
    break;

  case 160:
#line 746 "asin.y"
    { int k2, k1 =  search_network ((yyvsp[(1) - (8)].ident));
	 if (k1 >= 0) {
	   k2 = search_layer(k1, (yyvsp[(3) - (8)].ident)); 
	   if (k2 >= 0) get_com_lay_copy(k1, k2, (yyvsp[(5) - (8)].aux), (yyvsp[(7) - (8)].ident));
	   else yyerror("Destination layer does not exist");
	 }
	 else yyerror("Destination network does not exist");
       ;}
    break;

  case 161:
#line 757 "asin.y"
    { int k = search_network ((yyvsp[(1) - (5)].ident));
	 if (k >= 0) get_com_net_void(k, (yyvsp[(3) - (5)].aux));
	 else yyerror("Network name does not exist");
       ;}
    break;

  case 162:
#line 764 "asin.y"
    { int k = search_network ((yyvsp[(1) - (6)].ident));
	 if (k >= 0)   get_com_net_file(k, (yyvsp[(3) - (6)].aux), (yyvsp[(5) - (6)].ident));
	 else yyerror("Network name does not exist");
       ;}
    break;

  case 163:
#line 771 "asin.y"
    { int k2, k1 = search_network ((yyvsp[(1) - (6)].ident)); 
	 if (k1 >= 0)  
	   if (strlen((yyvsp[(5) - (6)].ident)) == 0)  get_com_net_dat(k1, (yyvsp[(3) - (6)].aux), -1);
	   else {
	     k2 = search_data ((yyvsp[(5) - (6)].ident));
	     if (k2 >= 0) get_com_net_dat(k1, (yyvsp[(3) - (6)].aux), k2);
	     else  yyerror("Data name does not exist");
	   }
	 else yyerror("Network name does not exist");
       ;}
    break;

  case 164:
#line 784 "asin.y"
    { int k = search_network ((yyvsp[(1) - (6)].ident));
	 if (k >= 0)  get_com_net_exp(k, (yyvsp[(3) - (6)].aux), (yyvsp[(5) - (6)].expre));
	 else yyerror("Network name does not exist");
       ;}
    break;

  case 165:
#line 791 "asin.y"
    { int k = search_data ((yyvsp[(1) - (6)].ident));
	 if (k >= 0)	get_com_data_void_rank(k, (yyvsp[(2) - (6)].rango), (yyvsp[(4) - (6)].aux));
         else yyerror("Data name does not exist");
       ;}
    break;

  case 166:
#line 798 "asin.y"
    { int k = search_data ((yyvsp[(1) - (5)].ident)); 
	 if (k >= 0)	get_com_data_void(k, (yyvsp[(3) - (5)].aux));
         else yyerror("Data name does not exist");
       ;}
    break;

  case 167:
#line 805 "asin.y"
    { int k = search_data ((yyvsp[(1) - (6)].ident)); 
         if (k >= 0)	get_com_data_file(k, (yyvsp[(3) - (6)].aux), (yyvsp[(5) - (6)].ident)); 
         else yyerror("Data name does not exist");
       ;}
    break;

  case 168:
#line 812 "asin.y"
    { int k2, k1 = search_data ((yyvsp[(1) - (6)].ident)); 
         if (k1 >= 0) {
	   k2 = search_data ((yyvsp[(5) - (6)].ident));
	   if (k2 >= 0)  get_com_data_dat(k1, (yyvsp[(3) - (6)].aux), k2);
	   else yyerror("Data name does not exist");
	 }
         else yyerror("Data name does not exist");
       ;}
    break;

  case 169:
#line 823 "asin.y"
    { int k = search_data ((yyvsp[(1) - (7)].ident));
         if (k >= 0)	get_com_data_exp_rank(k, (yyvsp[(2) - (7)].rango), (yyvsp[(4) - (7)].aux), (yyvsp[(6) - (7)].expre));
         else yyerror("Data name does not exist");
       ;}
    break;

  case 170:
#line 830 "asin.y"
    { int k = search_data ((yyvsp[(1) - (6)].ident)); 
         if (k >= 0)	get_com_data_exp(k, (yyvsp[(3) - (6)].aux), (yyvsp[(5) - (6)].expre));
         else yyerror("Data name does not exist");
       ;}
    break;

  case 171:
#line 837 "asin.y"
    { int k = search_data ((yyvsp[(1) - (7)].ident));
 	 if (k >= 0)  get_com_data_copy_rank(k, (yyvsp[(2) - (7)].rango), (yyvsp[(4) - (7)].aux), (yyvsp[(6) - (7)].ident));
	 else yyerror("Data name does not exist");
       ;}
    break;

  case 172:
#line 844 "asin.y"
    { int k = search_data ((yyvsp[(1) - (6)].ident));
         if (k < 0)  k = inser_new_name_data((yyvsp[(1) - (6)].ident));
	 get_com_data_copy(k, (yyvsp[(3) - (6)].aux), (yyvsp[(5) - (6)].ident));
       ;}
    break;

  case 173:
#line 852 "asin.y"
    { (yyval.rango).row = (yyvsp[(2) - (5)].aux4); (yyval.rango).col = (yyvsp[(4) - (5)].aux4); ;}
    break;

  case 174:
#line 861 "asin.y"
    { 
         (yyval.aux4).ini.psymbol = NULL; (yyval.aux4).ini.reftemp = cr_var_temp_cte(-1); 
         (yyval.aux4).fin.psymbol = NULL; (yyval.aux4).fin.reftemp = cr_var_temp_cte(-1); 
         (yyval.aux4).aux = -1; 
       ;}
    break;

  case 175:
#line 869 "asin.y"
    { (yyval.aux4).ini = (yyval.aux4).fin = (yyvsp[(1) - (1)].expre);  (yyval.aux4).aux = -1; ;}
    break;

  case 176:
#line 873 "asin.y"
    { 
         (yyval.aux4).ini.psymbol = NULL; (yyval.aux4).ini.reftemp = cr_var_temp_cte(-1); 
         (yyval.aux4).fin = (yyvsp[(2) - (2)].expre); (yyval.aux4).aux = -1; 
       ;}
    break;

  case 177:
#line 880 "asin.y"
    { 
         (yyval.aux4).ini = (yyvsp[(1) - (2)].expre); (yyval.aux4).aux = -1; 
         (yyval.aux4).fin.psymbol = NULL; (yyval.aux4).fin.reftemp = cr_var_temp_cte(-1); 
       ;}
    break;

  case 178:
#line 887 "asin.y"
    { (yyval.aux4).ini = (yyvsp[(1) - (3)].expre); (yyval.aux4).fin = (yyvsp[(3) - (3)].expre); (yyval.aux4).aux = -1; ;}
    break;

  case 179:
#line 896 "asin.y"
    { 
         (yyval.aux4).ini.psymbol = NULL; (yyval.aux4).ini.reftemp = cr_var_temp_cte(-1);
         (yyval.aux4).fin.psymbol = NULL; (yyval.aux4).fin.reftemp = cr_var_temp_cte(-1);
         (yyval.aux4).aux = -1; 
       ;}
    break;

  case 180:
#line 904 "asin.y"
    { (yyval.aux4).ini = (yyval.aux4).fin = (yyvsp[(1) - (1)].expre);  (yyval.aux4).aux = -1; ;}
    break;

  case 181:
#line 908 "asin.y"
    { 
         (yyval.aux4).ini.psymbol = NULL; (yyval.aux4).ini.reftemp = cr_var_temp_cte(-1);
         (yyval.aux4).fin = (yyvsp[(2) - (2)].expre); (yyval.aux4).aux = -1; 
       ;}
    break;

  case 182:
#line 915 "asin.y"
    { 
         (yyval.aux4).ini = (yyvsp[(1) - (2)].expre); (yyval.aux4).aux = -1; 
         (yyval.aux4).fin.psymbol = NULL; (yyval.aux4).fin.reftemp = cr_var_temp_cte(-1);
       ;}
    break;

  case 183:
#line 922 "asin.y"
    { (yyval.aux4).ini = (yyvsp[(1) - (3)].expre); (yyval.aux4).fin = (yyvsp[(3) - (3)].expre); (yyval.aux4).aux = -1; ;}
    break;

  case 184:
#line 926 "asin.y"
    { 
         (yyval.aux4).ini.psymbol = NULL; (yyval.aux4).ini.reftemp = cr_var_temp_cte(-1);
         (yyval.aux4).fin.psymbol = NULL; (yyval.aux4).fin.reftemp = cr_var_temp_cte(-1);
         (yyval.aux4).aux = REAL; 
       ;}
    break;

  case 185:
#line 934 "asin.y"
    { 
         (yyval.aux4).ini.psymbol = NULL; (yyval.aux4).ini.reftemp = cr_var_temp_cte(-1);
         (yyval.aux4).fin.psymbol = NULL; (yyval.aux4).fin.reftemp = cr_var_temp_cte(-1);
         (yyval.aux4).aux = BIN; 
       ;}
    break;

  case 186:
#line 942 "asin.y"
    { 
         (yyval.aux4).ini.psymbol = NULL; (yyval.aux4).ini.reftemp = cr_var_temp_cte(-1);
         (yyval.aux4).fin.psymbol = NULL; (yyval.aux4).fin.reftemp = cr_var_temp_cte(-1);
         (yyval.aux4).aux = INT; 
       ;}
    break;

  case 187:
#line 950 "asin.y"
    { 
         (yyval.aux4).ini.psymbol = NULL; (yyval.aux4).ini.reftemp = cr_var_temp_cte(-1);
         (yyval.aux4).fin.psymbol = NULL; (yyval.aux4).fin.reftemp = cr_var_temp_cte(-1);
         (yyval.aux4).aux = SAMPLE; 
       ;}
    break;

  case 188:
#line 958 "asin.y"
    { 
         (yyval.aux4).ini.psymbol = NULL; (yyval.aux4).ini.reftemp = cr_var_temp_cte(-1);
         (yyval.aux4).fin.psymbol = NULL; (yyval.aux4).fin.reftemp = cr_var_temp_cte(-1);
         (yyval.aux4).aux = TARGET; 
       ;}
    break;

  case 189:
#line 966 "asin.y"
    { (yyval.ident) = ""; ;}
    break;

  case 190:
#line 967 "asin.y"
    { (yyval.ident) = (yyvsp[(1) - (1)].ident); ;}
    break;

  case 191:
#line 971 "asin.y"
    { (yyval.aux) = forward;     ;}
    break;

  case 192:
#line 972 "asin.y"
    { (yyval.aux) = backward;    ;}
    break;

  case 193:
#line 973 "asin.y"
    { (yyval.aux) = resetstats;  ;}
    break;

  case 194:
#line 974 "asin.y"
    { (yyval.aux) = printerrors; ;}
    break;

  case 195:
#line 975 "asin.y"
    { (yyval.aux) = reseterrors; ;}
    break;

  case 196:
#line 976 "asin.y"
    { (yyval.aux) = trainmode;   ;}
    break;

  case 197:
#line 977 "asin.y"
    { (yyval.aux) = testmode;    ;}
    break;

  case 198:
#line 978 "asin.y"
    { (yyval.aux) = update;      ;}
    break;

  case 199:
#line 982 "asin.y"
    { (yyval.aux) = load;    ;}
    break;

  case 200:
#line 983 "asin.y"
    { (yyval.aux) = save;    ;}
    break;

  case 201:
#line 984 "asin.y"
    { (yyval.aux) = testout; ;}
    break;

  case 202:
#line 988 "asin.y"
    { (yyval.aux) = test; ;}
    break;

  case 203:
#line 989 "asin.y"
    { (yyval.aux) = evaluate; ;}
    break;

  case 204:
#line 993 "asin.y"
    { (yyval.aux) = train; ;}
    break;

  case 205:
#line 997 "asin.y"
    { (yyval.aux) = zscore;  ;}
    break;

  case 206:
#line 998 "asin.y"
    { (yyval.aux) = center;  ;}
    break;

  case 207:
#line 999 "asin.y"
    { (yyval.aux) = yuv;     ;}
    break;

  case 208:
#line 1000 "asin.y"
    { (yyval.aux) = maxmin;  ;}
    break;

  case 209:
#line 1001 "asin.y"
    { (yyval.aux) = shuffle; ;}
    break;

  case 210:
#line 1002 "asin.y"
    { (yyval.aux) = next;    ;}
    break;

  case 211:
#line 1006 "asin.y"
    { (yyval.aux) = store; ;}
    break;

  case 212:
#line 1010 "asin.y"
    { (yyval.aux) = getstats; ;}
    break;

  case 213:
#line 1014 "asin.y"
    { (yyval.aux) = copy; ;}
    break;

  case 214:
#line 1018 "asin.y"
    { (yyval.aux) = multiplication; ;}
    break;

  case 215:
#line 1019 "asin.y"
    { (yyval.aux) = division;       ;}
    break;

  case 216:
#line 1020 "asin.y"
    { (yyval.aux) = addition;       ;}
    break;

  case 217:
#line 1021 "asin.y"
    { (yyval.aux) = subtraction;    ;}
    break;

  case 218:
#line 1022 "asin.y"
    { (yyval.aux) = set;            ;}
    break;

  case 219:
#line 1026 "asin.y"
    { (yyval.aux) = printkernels; ;}
    break;

  case 220:
#line 1030 "asin.y"
    { (yyval.aux) = change; ;}
    break;

  case 221:
#line 1035 "asin.y"
    { int k = search_data((yyvsp[(1) - (1)].ident)); (yyval.aux2).ref = (yyval.aux2).typ = -1;
	 if (k >= 0)  (yyval.aux2).ref = k; 
	 else yyerror("Data name does not exist");
       ;}
    break;

  case 222:
#line 1042 "asin.y"
    { int k2, k1 =  search_network ((yyvsp[(1) - (3)].ident)); (yyval.aux2).ref = (yyval.aux2).typ = -1;
	 if (k1 >= 0) {
	   k2 =  search_layer(k1, (yyvsp[(3) - (3)].ident));
	   if (k2 >= 0) { (yyval.aux2).ref = k1; (yyval.aux2).typ = k2; }
	   else yyerror("Source layer does not exist");
	 }
	 else yyerror("Source network does not exist");
       ;}
    break;

  case 223:
#line 1054 "asin.y"
    { int k = search_data((yyvsp[(1) - (1)].ident)); char t[140] = ""; 

	 if (k >= 0)  sprintf(t, "data %s", (yyvsp[(1) - (1)].ident));
	 else yyerror("Data name does not exist");
         (yyval.ident) = t;
       ;}
    break;

  case 224:
#line 1063 "asin.y"
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
       ;}
    break;

  case 225:
#line 1087 "asin.y"
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
       ;}
    break;

  case 226:
#line 1102 "asin.y"
    { (yyval.ident) = "W";  ;}
    break;

  case 227:
#line 1103 "asin.y"
    { (yyval.ident) = "GW"; ;}
    break;

  case 228:
#line 1104 "asin.y"
    { (yyval.ident) = "B";  ;}
    break;

  case 229:
#line 1105 "asin.y"
    { (yyval.ident) = "GB"; ;}
    break;

  case 230:
#line 1106 "asin.y"
    { (yyval.ident) = "N";  ;}
    break;

  case 231:
#line 1109 "asin.y"
    { (yyval.expre) = (yyvsp[(1) - (1)].expre); ;}
    break;

  case 232:
#line 1113 "asin.y"
    { 
         (yyval.expre).psymbol = NULL;  (yyval.expre).reftemp = cr_var_temp();  
	 get_exp_add((yyval.expre).reftemp, (yyvsp[(1) - (3)].expre), (yyvsp[(2) - (3)].aux), (yyvsp[(3) - (3)].expre));
       ;}
    break;

  case 233:
#line 1119 "asin.y"
    { (yyval.expre) = (yyvsp[(1) - (1)].expre); ;}
    break;

  case 234:
#line 1123 "asin.y"
    { 
         (yyval.expre).psymbol = NULL;  (yyval.expre).reftemp = cr_var_temp();  
	 get_exp_mul((yyval.expre).reftemp, (yyvsp[(1) - (3)].expre), (yyvsp[(2) - (3)].aux), (yyvsp[(3) - (3)].expre));
       ;}
    break;

  case 235:
#line 1130 "asin.y"
    { (yyval.expre) = (yyvsp[(1) - (1)].expre); ;}
    break;

  case 236:
#line 1134 "asin.y"
    { 
         (yyval.expre).psymbol = NULL;  (yyval.expre).reftemp = cr_var_temp();  
	 get_functions((yyval.expre).reftemp, (yyvsp[(1) - (4)].aux), (yyvsp[(3) - (4)].expre));
       ;}
    break;

  case 237:
#line 1140 "asin.y"
    { (yyval.expre) = (yyvsp[(2) - (3)].expre); ;}
    break;

  case 238:
#line 1144 "asin.y"
    { 
         (yyval.expre).psymbol = search_name((yyvsp[(1) - (1)].ident));  (yyval.expre).reftemp = -1;
	 if ((yyval.expre).psymbol == NULL) yyerror("Undefined variable name");
       ;}
    break;

  case 239:
#line 1151 "asin.y"
    { 
         (yyval.expre).psymbol = NULL;  
	 if ((yyvsp[(1) - (1)].creal) == -1)     (yyval.expre).reftemp = cr_var_temp_cte(-1);
	 else {
	   (yyval.expre).reftemp = cr_var_temp();
	   get_init_cte((yyval.expre).reftemp, (yyvsp[(1) - (1)].creal));
	 }
       ;}
    break;

  case 240:
#line 1162 "asin.y"
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
       ;}
    break;

  case 241:
#line 1176 "asin.y"
    { int k = search_network ((yyvsp[(1) - (3)].ident));
         (yyval.expre).psymbol=NULL; (yyval.expre).reftemp = cr_var_temp();
	 if (k >= 0)  get_init_amend(NETWORK, (yyval.expre).reftemp, k, (yyvsp[(3) - (3)].aux));
	 else { 
	   k = search_data ((yyvsp[(1) - (3)].ident));
	   if (k >= 0)  get_init_amend(DATA, (yyval.expre).reftemp, k, (yyvsp[(3) - (3)].aux));
	   else yyerror("Data or network name does not exist");
	 }
       ;}
    break;

  case 242:
#line 1188 "asin.y"
    { int k =  search_data ((yyvsp[(1) - (6)].ident));
         (yyval.expre).psymbol=NULL; (yyval.expre).reftemp =  cr_var_temp();
	 if (k >= 0)  get_init_elem((yyval.expre).reftemp, k, (yyvsp[(3) - (6)].expre), (yyvsp[(5) - (6)].expre));
	 else yyerror("Data name does not exist");
       ;}
    break;

  case 243:
#line 1195 "asin.y"
    { (yyval.aux) = ADDITION; ;}
    break;

  case 244:
#line 1196 "asin.y"
    { (yyval.aux) = SUBTRACTION; ;}
    break;

  case 245:
#line 1199 "asin.y"
    { (yyval.aux) = MULTIPLICATION; ;}
    break;

  case 246:
#line 1200 "asin.y"
    { (yyval.aux) = DIVISION;       ;}
    break;

  case 247:
#line 1201 "asin.y"
    { (yyval.aux) = MODULUS;        ;}
    break;

  case 248:
#line 1202 "asin.y"
    { (yyval.aux) = EXPONET;        ;}
    break;

  case 249:
#line 1205 "asin.y"
    { (yyval.creal) = (yyvsp[(1) - (1)].creal);  ;}
    break;

  case 250:
#line 1206 "asin.y"
    { (yyval.creal) = (yyvsp[(2) - (2)].creal);  ;}
    break;

  case 251:
#line 1207 "asin.y"
    { (yyval.creal) = -(yyvsp[(2) - (2)].creal); ;}
    break;

  case 252:
#line 1211 "asin.y"
    { (yyval.aux) = LOGARITHM;   ;}
    break;

  case 253:
#line 1212 "asin.y"
    { (yyval.aux) = EXPONENTIAL; ;}
    break;

  case 254:
#line 1213 "asin.y"
    { (yyval.aux) = SQUARE;      ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3529 "asin.c"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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


#line 1215 "asin.y"

/*****************************************************************************/
/*****************************************************************************/

