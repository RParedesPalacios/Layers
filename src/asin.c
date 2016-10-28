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
     log_ = 260,
     seed_ = 261,
     gpu_ = 262,
     filename_ = 263,
     tr_ = 264,
     ts_ = 265,
     va_ = 266,
     ascii_ = 267,
     binary_ = 268,
     F_ = 269,
     FI_ = 270,
     FO_ = 271,
     C_ = 272,
     CI_ = 273,
     MP_ = 274,
     CAT_ = 275,
     ADD_ = 276,
     classification_ = 277,
     regression_ = 278,
     autoencoder_ = 279,
     nz_ = 280,
     nr_ = 281,
     nc_ = 282,
     cr_ = 283,
     cc_ = 284,
     numnodes_ = 285,
     nk_ = 286,
     kr_ = 287,
     kc_ = 288,
     rpad_ = 289,
     cpad_ = 290,
     stride_ = 291,
     sizer_ = 292,
     sizec_ = 293,
     mu_ = 294,
     mmu_ = 295,
     l2_ = 296,
     l1_ = 297,
     maxn_ = 298,
     drop_ = 299,
     noiser_ = 300,
     noisesd_ = 301,
     brightness_ = 302,
     contrast_ = 303,
     lambda_ = 304,
     noiseb_ = 305,
     advf_ = 306,
     bn_ = 307,
     act_ = 308,
     shift_ = 309,
     flip_ = 310,
     adv_ = 311,
     balance_ = 312,
     cropmode_ = 313,
     const_ = 314,
     data_ = 315,
     network_ = 316,
     script_ = 317,
     train_ = 318,
     evaluate_ = 319,
     save_ = 320,
     zscore_ = 321,
     yuv_ = 322,
     printkernels_ = 323,
     copy_ = 324,
     local_ = 325,
     load_ = 326,
     testout_ = 327,
     center_ = 328,
     div_ = 329,
     test_ = 330,
     add_ = 331,
     sub_ = 332,
     mul_ = 333,
     maxmin_ = 334,
     store_ = 335,
     BCB_ = 336,
     ECB_ = 337,
     BSB_ = 338,
     ESB_ = 339,
     BRB_ = 340,
     ERB_ = 341,
     PER_ = 342,
     COM_ = 343,
     EQ_ = 344,
     RAR_ = 345,
     id_ = 346,
     nfile_ = 347,
     cte_ = 348
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
  int     aux;



/* Line 293 of yacc.c  */
#line 219 "asin.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 231 "asin.c"

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
#define YYLAST   293

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  131
/* YYNRULES -- Number of states.  */
#define YYNSTATES  300

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   348

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
      85,    86,    87,    88,    89,    90,    91,    92,    93
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     5,    10,    11,    16,    19,    21,
      25,    29,    33,    37,    41,    44,    46,    48,    50,    52,
      57,    60,    62,    63,    69,    73,    75,    79,    81,    88,
      90,    92,    93,   101,   106,   107,   110,   114,   118,   121,
     123,   125,   127,   130,   136,   142,   148,   154,   160,   163,
     166,   170,   172,   174,   176,   178,   182,   186,   188,   192,
     196,   200,   204,   208,   209,   211,   215,   219,   221,   225,
     229,   233,   237,   241,   245,   249,   251,   255,   259,   263,
     267,   269,   274,   277,   279,   281,   283,   289,   293,   299,
     305,   314,   323,   333,   340,   347,   354,   361,   368,   375,
     382,   389,   395,   402,   409,   416,   422,   429,   436,   437,
     441,   442,   444,   448,   452,   454,   456,   458,   460,   462,
     464,   466,   468,   470,   472,   474,   476,   478,   480,   482,
     484,   486
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      95,     0,    -1,    -1,    -1,    96,    98,    97,   101,    -1,
      -1,    59,    81,    99,    82,    -1,    99,   100,    -1,   100,
      -1,     3,    89,    93,    -1,     4,    89,    93,    -1,     5,
      89,    92,    -1,     6,    89,    93,    -1,     7,    89,    93,
      -1,   101,   102,    -1,   102,    -1,   103,    -1,   110,    -1,
     129,    -1,    60,    81,   104,    82,    -1,   104,   105,    -1,
     105,    -1,    -1,    91,   106,    83,   107,    84,    -1,   107,
      88,   108,    -1,   108,    -1,     8,    89,    92,    -1,   109,
      -1,    91,    87,    91,    91,    87,    91,    -1,    12,    -1,
      13,    -1,    -1,    61,    91,   111,    81,   112,   115,    82,
      -1,    60,     9,    91,   113,    -1,    -1,   113,   114,    -1,
      60,    10,    91,    -1,    60,    11,    91,    -1,   115,   116,
      -1,   116,    -1,   117,    -1,   127,    -1,    15,    91,    -1,
      16,    91,    83,   118,    84,    -1,    18,    91,    83,   120,
      84,    -1,    14,    91,    83,   122,    84,    -1,    17,    91,
      83,   123,    84,    -1,    19,    91,    83,   125,    84,    -1,
      20,    91,    -1,    21,    91,    -1,   118,    88,   119,    -1,
     119,    -1,    22,    -1,    23,    -1,    24,    -1,    91,    87,
      91,    -1,   120,    88,   121,    -1,   121,    -1,    25,    89,
      93,    -1,    26,    89,    93,    -1,    27,    89,    93,    -1,
      28,    89,    93,    -1,    29,    89,    93,    -1,    -1,    70,
      -1,    30,    89,    93,    -1,   123,    88,   124,    -1,   124,
      -1,    31,    89,    93,    -1,    32,    89,    93,    -1,    33,
      89,    93,    -1,    34,    89,    93,    -1,    35,    89,    93,
      -1,    36,    89,    93,    -1,   125,    88,   126,    -1,   126,
      -1,    37,    89,    93,    -1,    38,    89,    93,    -1,   128,
      90,   128,    -1,    91,    87,    91,    -1,    91,    -1,    62,
      81,   130,    82,    -1,   130,   131,    -1,   131,    -1,   132,
      -1,   133,    -1,    91,    87,    91,    87,   136,    -1,    91,
      87,   136,    -1,    91,    87,    58,    89,    93,    -1,    91,
      87,    57,    89,    93,    -1,    91,    87,    91,    87,    68,
      85,    92,    86,    -1,    91,    87,    91,    87,    69,    91,
      87,    91,    -1,    63,    85,    93,    88,    93,    88,    93,
     134,    86,    -1,    91,    87,    63,    85,    93,    86,    -1,
      91,    87,    75,    85,   135,    86,    -1,    91,    87,    64,
      85,    91,    86,    -1,    91,    87,    65,    85,    92,    86,
      -1,    91,    87,    71,    85,    92,    86,    -1,    91,    87,
      72,    85,    92,    86,    -1,    91,    87,    66,    85,   135,
      86,    -1,    91,    87,    73,    85,   135,    86,    -1,    91,
      87,    67,    85,    86,    -1,    91,    87,    74,    85,    93,
      86,    -1,    91,    87,    76,    85,    93,    86,    -1,    91,
      87,    77,    85,    93,    86,    -1,    91,    87,    79,    85,
      86,    -1,    91,    87,    80,    85,    92,    86,    -1,    91,
      87,    78,    85,    93,    86,    -1,    -1,   134,    88,    91,
      -1,    -1,    91,    -1,   137,    89,    93,    -1,   138,    89,
      93,    -1,    39,    -1,    40,    -1,    41,    -1,    42,    -1,
      43,    -1,    44,    -1,    45,    -1,    46,    -1,    47,    -1,
      48,    -1,    49,    -1,    50,    -1,    51,    -1,    52,    -1,
      53,    -1,    54,    -1,    55,    -1,    56,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    42,    42,    46,    42,    53,    55,    59,    60,    64,
      68,    72,    76,    80,    86,    87,    91,    95,    99,   103,
     107,   108,   113,   111,   122,   123,   127,   131,   135,   157,
     158,   164,   162,   170,   179,   181,   185,   193,   203,   204,
     208,   209,   212,   219,   230,   241,   253,   264,   275,   283,
     293,   294,   298,   302,   306,   310,   325,   326,   330,   334,
     338,   342,   346,   354,   359,   366,   375,   376,   380,   384,
     388,   392,   396,   400,   406,   407,   411,   415,   421,   427,
     431,   438,   442,   443,   447,   448,   452,   465,   472,   479,
     488,   501,   514,   518,   525,   538,   549,   557,   565,   573,
     586,   599,   606,   613,   620,   627,   634,   641,   655,   657,
     667,   668,   672,   676,   682,   683,   684,   685,   686,   687,
     688,   689,   690,   691,   692,   693,   694,   698,   699,   700,
     701,   702
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "batch_", "threads_", "log_", "seed_",
  "gpu_", "filename_", "tr_", "ts_", "va_", "ascii_", "binary_", "F_",
  "FI_", "FO_", "C_", "CI_", "MP_", "CAT_", "ADD_", "classification_",
  "regression_", "autoencoder_", "nz_", "nr_", "nc_", "cr_", "cc_",
  "numnodes_", "nk_", "kr_", "kc_", "rpad_", "cpad_", "stride_", "sizer_",
  "sizec_", "mu_", "mmu_", "l2_", "l1_", "maxn_", "drop_", "noiser_",
  "noisesd_", "brightness_", "contrast_", "lambda_", "noiseb_", "advf_",
  "bn_", "act_", "shift_", "flip_", "adv_", "balance_", "cropmode_",
  "const_", "data_", "network_", "script_", "train_", "evaluate_", "save_",
  "zscore_", "yuv_", "printkernels_", "copy_", "local_", "load_",
  "testout_", "center_", "div_", "test_", "add_", "sub_", "mul_",
  "maxmin_", "store_", "BCB_", "ECB_", "BSB_", "ESB_", "BRB_", "ERB_",
  "PER_", "COM_", "EQ_", "RAR_", "id_", "nfile_", "cte_", "$accept",
  "experiment", "$@1", "$@2", "def_constants", "list_constants",
  "def_const", "list_definitions", "definition", "def_data", "list_data",
  "data", "$@3", "param_data", "def_param", "filetype", "def_network",
  "$@4", "net_data", "rest_data", "net_defdata", "list_statements",
  "statement", "layer", "fo_lparam", "fo_param", "ci_lparam", "ci_param",
  "f_param", "c_lparam", "c_param", "mp_lparam", "mp_param", "edge",
  "name_layer", "def_script", "list_actions", "action", "amendment",
  "command", "rest_train", "other_data", "parameter", "param_ctr",
  "param_cte", 0
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
     345,   346,   347,   348
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    94,    96,    97,    95,    98,    98,    99,    99,   100,
     100,   100,   100,   100,   101,   101,   102,   102,   102,   103,
     104,   104,   106,   105,   107,   107,   108,   108,   108,   109,
     109,   111,   110,   112,   113,   113,   114,   114,   115,   115,
     116,   116,   117,   117,   117,   117,   117,   117,   117,   117,
     118,   118,   119,   119,   119,   119,   120,   120,   121,   121,
     121,   121,   121,   122,   122,   122,   123,   123,   124,   124,
     124,   124,   124,   124,   125,   125,   126,   126,   127,   128,
     128,   129,   130,   130,   131,   131,   132,   132,   132,   132,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   134,   134,
     135,   135,   136,   136,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   138,   138,   138,
     138,   138
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     4,     0,     4,     2,     1,     3,
       3,     3,     3,     3,     2,     1,     1,     1,     1,     4,
       2,     1,     0,     5,     3,     1,     3,     1,     6,     1,
       1,     0,     7,     4,     0,     2,     3,     3,     2,     1,
       1,     1,     2,     5,     5,     5,     5,     5,     2,     2,
       3,     1,     1,     1,     1,     3,     3,     1,     3,     3,
       3,     3,     3,     0,     1,     3,     3,     1,     3,     3,
       3,     3,     3,     3,     3,     1,     3,     3,     3,     3,
       1,     4,     2,     1,     1,     1,     5,     3,     5,     5,
       8,     8,     9,     6,     6,     6,     6,     6,     6,     6,
       6,     5,     6,     6,     6,     5,     6,     6,     0,     3,
       0,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     5,     1,     0,     3,     0,     0,     0,     0,
       0,     0,     0,     0,     8,     0,     0,     0,     4,    15,
      16,    17,    18,     0,     0,     0,     0,     0,     6,     7,
       0,    31,     0,    14,     9,    10,    11,    12,    13,    22,
       0,    21,     0,     0,     0,     0,    83,    84,    85,     0,
      19,    20,     0,     0,     0,    81,    82,     0,     0,     0,
       0,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    87,     0,     0,
       0,    29,    30,     0,     0,    25,    27,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    80,     0,    39,    40,
      41,     0,     0,     0,     0,     0,     0,     0,   110,     0,
       0,     0,   110,     0,   110,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    23,     0,    34,     0,    42,
       0,     0,     0,     0,    48,    49,     0,    32,    38,     0,
       0,    89,    88,     0,     0,     0,   111,     0,   101,     0,
       0,     0,     0,     0,     0,     0,     0,   105,     0,     0,
       0,    86,   112,   113,    26,     0,    24,    33,    63,     0,
       0,     0,     0,    79,    78,     0,    93,    95,    96,    99,
      97,    98,   100,   102,    94,   103,   104,   107,   106,     0,
       0,     0,     0,    35,     0,    64,     0,    52,    53,    54,
       0,     0,    51,     0,     0,     0,     0,     0,     0,     0,
      67,     0,     0,     0,     0,     0,     0,    57,     0,     0,
       0,    75,   108,     0,     0,     0,     0,     0,     0,    45,
       0,    43,     0,     0,     0,     0,     0,     0,     0,    46,
       0,     0,     0,     0,     0,     0,    44,     0,     0,     0,
      47,     0,     0,    90,    91,    28,    36,    37,    65,    55,
      50,    68,    69,    70,    71,    72,    73,    66,    58,    59,
      60,    61,    62,    56,    76,    77,    74,    92,     0,   109
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     7,     5,    13,    14,    18,    19,    20,
      40,    41,    49,   104,   105,   106,    21,    42,    59,   187,
     213,   117,   118,   119,   221,   222,   236,   237,   216,   229,
     230,   240,   241,   120,   121,    22,    45,    46,    47,    48,
     272,   167,    97,    98,    99
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -87
static const yytype_int16 yypact[] =
{
     -87,    27,    -2,   -87,   -30,   -87,    68,    74,    52,    53,
      54,    55,    56,     3,   -87,     0,    -7,    65,    74,   -87,
     -87,   -87,   -87,    57,    60,    62,    63,    64,   -87,   -87,
      -4,   -87,   -15,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
     -32,   -87,    66,    67,    61,    -5,   -87,   -87,   -87,    72,
     -87,   -87,    89,    69,   -11,   -87,   -87,    -8,   142,     5,
      70,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,    71,
      75,    76,    78,    80,    81,    82,    83,    84,    86,    87,
      88,    91,    92,    93,    94,    95,    96,   -87,    97,    98,
      99,   -87,   -87,   102,    -6,   -87,   -87,    79,   100,   101,
     103,   104,   105,   106,   107,   108,   113,    -3,   -87,   -87,
     -87,   111,   109,   110,   112,   114,   115,   116,   118,    73,
     119,   121,   118,   117,   118,   122,   123,   124,   126,   127,
      58,   125,   128,   130,   129,   -87,    -8,   -87,   131,   -87,
     140,   141,   143,   144,   -87,   -87,   134,   -87,   -87,   137,
     145,   -87,   -87,   146,   148,   149,   -87,   150,   -87,   151,
     152,   153,   154,   155,   156,   157,   158,   -87,   159,   161,
     138,   -87,   -87,   -87,   -87,   139,   -87,   133,    19,   -21,
      59,    90,    85,   -87,   -87,   160,   -87,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   162,
     163,   164,   120,   -87,   166,   -87,   147,   -87,   -87,   -87,
     165,    36,   -87,   167,   168,   169,   170,   171,   172,    37,
     -87,   173,   174,   175,   176,   177,    44,   -87,   178,   179,
      45,   -87,   -87,   183,   180,   181,   182,   184,   185,   -87,
     186,   -87,   -21,   187,   188,   189,   190,   191,   192,   -87,
      59,   193,   194,   195,   196,   197,   -87,    90,   198,   199,
     -87,    85,    51,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   202,   -87
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -87,   -87,   -87,   -87,   -87,   -87,   234,   -87,   230,   -87,
     -87,   135,   -87,   -87,    28,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,   132,   -87,   -87,   -71,   -87,   -85,   -87,   -87,
     -76,   -87,   -86,   -87,    31,   -87,   -87,   225,   -87,   -87,
     -87,     6,   136,   -87,   -87
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     100,   217,   218,   219,   101,   102,     8,     9,    10,    11,
      12,   108,   109,   110,   111,   112,   113,   114,   115,   108,
     109,   110,   111,   112,   113,   114,   115,     3,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    43,   214,
      50,     6,    81,    82,    83,    84,    85,     4,    43,    39,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
     220,     8,     9,    10,    11,    12,    44,    55,   145,   157,
      96,    30,   146,   103,    31,    28,    44,    39,   116,   215,
     223,   224,   225,   226,   227,   228,   116,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,   231,   232,   233,   234,   235,
     251,   259,   238,   239,   252,   260,   179,   180,   266,   270,
     246,   247,   267,   271,    15,    16,    17,   297,   171,   298,
     173,    23,    24,    25,    26,    27,    32,    52,    54,    58,
      34,   107,    53,    35,    36,    57,    37,    38,   122,   168,
     123,   125,    60,   126,   124,   127,   128,   129,   130,   131,
     147,   132,   133,   134,   186,    51,   135,   136,   137,   138,
     139,   280,   293,   140,   287,   296,   141,   142,   143,   144,
     194,   148,   149,   212,   150,   151,   152,   153,   154,   155,
     156,   159,   160,   161,     0,   162,   164,   163,   165,   166,
     172,   169,   177,   170,   188,   174,   175,   176,   182,   178,
     185,   183,   184,   189,   190,   193,   191,   192,   116,   210,
     211,   249,   196,   195,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,    29,    33,   158,
     244,   245,   250,   242,   243,   248,   253,   254,   255,   256,
     257,   258,   261,   262,   263,   264,   265,   268,   269,   273,
      56,   274,   275,   276,     0,   277,   181,   279,   278,     0,
     281,   282,   283,   284,   285,   286,   288,   289,   290,   291,
     292,   294,   295,   299
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-87))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       8,    22,    23,    24,    12,    13,     3,     4,     5,     6,
       7,    14,    15,    16,    17,    18,    19,    20,    21,    14,
      15,    16,    17,    18,    19,    20,    21,     0,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    63,    30,
      82,    81,    63,    64,    65,    66,    67,    59,    63,    91,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      91,     3,     4,     5,     6,     7,    91,    82,    84,    82,
      91,    81,    88,    91,    91,    82,    91,    91,    91,    70,
      31,    32,    33,    34,    35,    36,    91,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    25,    26,    27,    28,    29,
      84,    84,    37,    38,    88,    88,    68,    69,    84,    84,
      10,    11,    88,    88,    60,    61,    62,    86,   132,    88,
     134,    89,    89,    89,    89,    89,    81,    81,    87,    60,
      93,     9,    85,    93,    92,    83,    93,    93,    88,    86,
      89,    85,    93,    85,    89,    85,    85,    85,    85,    85,
      91,    85,    85,    85,   146,    40,    85,    85,    85,    85,
      85,   252,   267,    87,   260,   271,    89,    89,    89,    87,
     159,    91,    91,    60,    91,    91,    91,    91,    91,    91,
      87,    90,    93,    93,    -1,    93,    91,    93,    92,    91,
      93,    92,    86,    92,    83,    93,    93,    93,    93,    92,
      91,    93,    92,    83,    83,    91,    83,    83,    91,    91,
      91,    84,    86,    88,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    85,    13,    18,   117,
      87,    87,    87,    93,    92,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    86,
      45,    91,    91,    91,    -1,    91,   140,    91,    93,    -1,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    91
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    95,    96,     0,    59,    98,    81,    97,     3,     4,
       5,     6,     7,    99,   100,    60,    61,    62,   101,   102,
     103,   110,   129,    89,    89,    89,    89,    89,    82,   100,
      81,    91,    81,   102,    93,    93,    92,    93,    93,    91,
     104,   105,   111,    63,    91,   130,   131,   132,   133,   106,
      82,   105,    81,    85,    87,    82,   131,    83,    60,   112,
      93,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    63,    64,    65,    66,    67,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    91,   136,   137,   138,
       8,    12,    13,    91,   107,   108,   109,     9,    14,    15,
      16,    17,    18,    19,    20,    21,    91,   115,   116,   117,
     127,   128,    88,    89,    89,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      87,    89,    89,    89,    87,    84,    88,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    87,    82,   116,    90,
      93,    93,    93,    93,    91,    92,    91,   135,    86,    92,
      92,   135,    93,   135,    93,    93,    93,    86,    92,    68,
      69,   136,    93,    93,    92,    91,   108,   113,    83,    83,
      83,    83,    83,    91,   128,    88,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    85,
      91,    91,    60,   114,    30,    70,   122,    22,    23,    24,
      91,   118,   119,    31,    32,    33,    34,    35,    36,   123,
     124,    25,    26,    27,    28,    29,   120,   121,    37,    38,
     125,   126,    93,    92,    87,    87,    10,    11,    89,    84,
      87,    84,    88,    89,    89,    89,    89,    89,    89,    84,
      88,    89,    89,    89,    89,    89,    84,    88,    89,    89,
      84,    88,   134,    86,    91,    91,    91,    91,    93,    91,
     119,    93,    93,    93,    93,    93,    93,   124,    93,    93,
      93,    93,    93,   121,    93,    93,   126,    86,    88,    91
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
#line 42 "asin.y"
    { begin_experiment(); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 46 "asin.y"
    { get_gconstants(); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 50 "asin.y"
    { end_experiment(); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 66 "asin.y"
    { insert_gconstants(BATCH, (int)(yyvsp[(3) - (3)].creal), ""); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 70 "asin.y"
    { insert_gconstants(THREADS, (int)(yyvsp[(3) - (3)].creal), ""); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 74 "asin.y"
    { insert_gconstants(LOG, 0, (yyvsp[(3) - (3)].ident)); }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 78 "asin.y"
    { insert_gconstants(SEED, (int)(yyvsp[(3) - (3)].creal), ""); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 82 "asin.y"
    { insert_gconstants(GPU, (int)(yyvsp[(3) - (3)].creal), ""); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 93 "asin.y"
    { get_data(); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 97 "asin.y"
    { get_network(); /* end_network(); */ }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 113 "asin.y"
    { int k = search_data((yyvsp[(1) - (1)].ident));
	 if (k < 0)  inser_name_data((yyvsp[(1) - (1)].ident));
	 else yyerror("Data name already exists");
       }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 129 "asin.y"
    { inser_param_data((yyvsp[(3) - (3)].ident), -1, -1); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 133 "asin.y"
    { inser_param_data("", (yyvsp[(1) - (1)].aux), -1); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 137 "asin.y"
    { int kf2, kt2, kf1 = search_network((yyvsp[(1) - (6)].ident)), kt1 = search_network((yyvsp[(4) - (6)].ident));

	 if (kf1 >= 0) {
	   kf2 = search_layer(kf1, (yyvsp[(3) - (6)].ident));
	   if (kf2 >= 0)
	     if (kt1 >= 0) {
	       kt2 = search_layer(kt1, (yyvsp[(6) - (6)].ident));
	       if (kt2 >= 0)
		 if (kf1 == kt1)  inser_param_data("", kf2, kt2); 
		 else yyerror("Network name must be unique");
	       else yyerror("Layer name does not exist on this network");
	     }
	     else yyerror("Network name does not exist");
	   else yyerror("Layer name does not exist on this network");
	 }
         else yyerror("Network name does not exist");
       }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 157 "asin.y"
    { (yyval.aux) = ASCII;  }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 158 "asin.y"
    { (yyval.aux) = BINARY; }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 164 "asin.y"
    { insert_name_network((yyvsp[(2) - (2)].ident)); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 172 "asin.y"
    { int k = search_data ((yyvsp[(3) - (4)].ident));
	 if (k < 0)
	   yyerror("Data name does not exist");
	 else inser_param_net_data(tr, k);
       }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 187 "asin.y"
    { int k = search_data ((yyvsp[(3) - (3)].ident));
	 if (k < 0)
	   yyerror("Data name does not exist");
	 else inser_param_net_data(ts, k);
       }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 195 "asin.y"
    { int k = search_data ((yyvsp[(3) - (3)].ident));
	 if (k < 0)
	   yyerror("Data name does not exist");
	 else inser_param_net_data(va, k);
       }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 214 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (2)].ident));
	 if (k < 0) insert_name_layer((yyvsp[(2) - (2)].ident), FI);
	 else  yyerror("Layer name already exists in this network");
       }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 221 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (5)].ident));
	 if (k < 0) {
	   check_param_layer(1);
	   insert_name_layer((yyvsp[(2) - (5)].ident), FO);
	 }
	 else yyerror("Layer name already exists in this network");

       }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 232 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (5)].ident));
	 if (k < 0) {
	   check_param_layer(3);
	   insert_name_layer((yyvsp[(2) - (5)].ident), CI);
	 }
	 else yyerror("Layer name already exists in this network");

       }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 243 "asin.y"
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

  case 46:

/* Line 1806 of yacc.c  */
#line 255 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (5)].ident));
	 if (k >= 0)
	   yyerror("Layer name already exists in this network");
	 else {
	   check_param_layer(3);
	   insert_name_layer((yyvsp[(2) - (5)].ident), C);
	 }
       }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 266 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (5)].ident));
	 if (k >= 0)
	   yyerror("Layer name already exists in this network");
	 else {
	   check_param_layer(2);
	   insert_name_layer((yyvsp[(2) - (5)].ident), MP);
	 }
       }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 277 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (2)].ident));
	 if (k >= 0) 
	   yyerror("Layer name already exists in this network");
	 else insert_name_layer((yyvsp[(2) - (2)].ident), CAT);
       }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 285 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (2)].ident));
	 if (k >= 0) 
	   yyerror("Layer name already exists in this network");
	 else insert_name_layer((yyvsp[(2) - (2)].ident), ADD);
       }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 300 "asin.y"
    { insert_param_layer(1, CLASSIFICATION); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 304 "asin.y"
    { insert_param_layer(1, REGRESSION); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 308 "asin.y"
    { insert_param_layer(1, AUTOENCODER); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 312 "asin.y"
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

  case 58:

/* Line 1806 of yacc.c  */
#line 332 "asin.y"
    { insert_param_layer(1, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 336 "asin.y"
    { insert_param_layer(2, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 340 "asin.y"
    { insert_param_layer(3, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 344 "asin.y"
    { insert_param_layer(4, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 348 "asin.y"
    { insert_param_layer(5, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 354 "asin.y"
    {
	 (yyval.aux) = FALSE;
	 insert_param_layer(1, 0);
       }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 361 "asin.y"
    { 
         (yyval.aux) = FALSE;
	 insert_param_layer(1, 1);
       }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 368 "asin.y"
    { 
         (yyval.aux) = TRUE;
	 insert_param_layer(1, (int)(yyvsp[(3) - (3)].creal));
       }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 382 "asin.y"
    { insert_param_layer(1, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 386 "asin.y"
    { insert_param_layer(2, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 390 "asin.y"
    { insert_param_layer(3, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 394 "asin.y"
    { insert_param_layer(4, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 398 "asin.y"
    { insert_param_layer(5, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 402 "asin.y"
    { insert_param_layer(6, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 413 "asin.y"
    { insert_param_layer(1, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 417 "asin.y"
    { insert_param_layer(2, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 423 "asin.y"
    { insert_link((yyvsp[(1) - (3)].aux),(yyvsp[(3) - (3)].aux)); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 429 "asin.y"
    { (yyval.aux) = search_states((yyvsp[(1) - (3)].ident), (yyvsp[(3) - (3)].ident)); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 433 "asin.y"
    { (yyval.aux) = search_states("", (yyvsp[(1) - (1)].ident));  }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 454 "asin.y"
    { int k2, k1 =  search_network ((yyvsp[(1) - (5)].ident));
	 if (k1 >= 0) {
           k2 = search_layer(k1, (yyvsp[(3) - (5)].ident));
	   if (k2 >= 0)
	     get_amendment(LAYER, k2, (yyvsp[(5) - (5)].ident));
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 467 "asin.y"
    { int k = search_network ((yyvsp[(1) - (3)].ident));
	 if (k >= 0)  get_amendment(NETWORK, k, (yyvsp[(3) - (3)].ident));
	 else yyerror("Network name does not exist");
       }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 474 "asin.y"
    { int k = search_network ((yyvsp[(1) - (5)].ident));
	 if (k >= 0)  get_amendment_onlynet(k, (int)(yyvsp[(5) - (5)].creal));
	 else yyerror("Network name does not exist");
       }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 481 "asin.y"
    { int k = search_data ((yyvsp[(1) - (5)].ident));
	 if (k >= 0)  get_amendment_data(k, (int)(yyvsp[(5) - (5)].creal));
	 else yyerror("Data or network name does not exist");
       }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 490 "asin.y"
    { int k2, k1 =  search_network ((yyvsp[(1) - (8)].ident));
	 if (k1 >= 0) {
           k2 = search_layer(k1, (yyvsp[(3) - (8)].ident));
	   if (k2 >= 0) 
	     get_printkernels(k1, k2, (yyvsp[(7) - (8)].ident));
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 503 "asin.y"
    { int d2, d1 =  search_network ((yyvsp[(1) - (8)].ident));
         int s2, s1 =  search_network ((yyvsp[(6) - (8)].ident));

         d2 = search_layer(d1, (yyvsp[(3) - (8)].ident)); s2 = search_layer(s1, (yyvsp[(8) - (8)].ident));
	 if (d1 < 0) yyerror("Destination network does not exist");
	 else if (d2 < 0) yyerror("Destination layer does not exist");
	 else if (s1 < 0) yyerror("Source network does not exist");
         else if (s2 < 0) yyerror("Source layer does not exist");
	 else get_copy(d1, d2, s1, s2);
       }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 516 "asin.y"
    { get_train((int)(yyvsp[(3) - (9)].creal), (int)(yyvsp[(5) - (9)].creal), (int)(yyvsp[(7) - (9)].creal), (yyvsp[(8) - (9)].aux)); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 520 "asin.y"
    { int k = search_network ((yyvsp[(1) - (6)].ident));
	 if (k >= 0)  get_net_train(k, (int)(yyvsp[(5) - (6)].creal));
	 else yyerror("Network name does not exist");
       }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 527 "asin.y"
    { int k2, k1 = search_network ((yyvsp[(1) - (6)].ident));
	 if (k1 >= 0)  
	   if (strlen((yyvsp[(5) - (6)].ident)) > 0) {
	     k2 = search_data ((yyvsp[(5) - (6)].ident));
	     if (k2 >= 0) get_net_test(k1, k2);
	     else yyerror("Data name does not exist");
	   }
	   else  get_net_test(k1,-1);
	 else yyerror("Network name does not exist");
       }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 540 "asin.y"
    { int k2, k1 = search_network ((yyvsp[(1) - (6)].ident));
	 if (k1 >= 0) {
	   k2 = search_data ((yyvsp[(5) - (6)].ident));
	   if (k2 >= 0) get_net_evaluate(k1, k2);
	   else yyerror("Data name does not exist");
	 }
	 else yyerror("Network name does not exist");
       }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 551 "asin.y"
    { int k = search_network ((yyvsp[(1) - (6)].ident));
	 if (k < 0)
	   yyerror("Network name does not exist");
	 else get_save(k, (yyvsp[(5) - (6)].ident));
       }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 559 "asin.y"
    { int k = search_network ((yyvsp[(1) - (6)].ident));
	 if (k < 0)
	   yyerror("Network name does not exist");
	 else get_load(k, (yyvsp[(5) - (6)].ident));
       }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 567 "asin.y"
    { int k = search_network ((yyvsp[(1) - (6)].ident));
	 if (k < 0)
	   yyerror("Network name does not exist");
	 else get_testout(k, (yyvsp[(5) - (6)].ident));
       }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 575 "asin.y"
    { int k2, k1 = search_data ((yyvsp[(1) - (6)].ident));
	 if (k1 >= 0) 
	   if (strlen((yyvsp[(5) - (6)].ident)) > 0) {
	     k2 = search_data ((yyvsp[(5) - (6)].ident));
	     if (k2 >= 0) get_zscore(k1,k2);
	     else yyerror("Data name does not exist");
	   }
	   else  get_zscore(k1,-1);
	 else yyerror("Data name does not exist");
       }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 588 "asin.y"
    { int k2, k1 = search_data ((yyvsp[(1) - (6)].ident));
	 if (k1 >= 0) 
	   if (strlen((yyvsp[(5) - (6)].ident)) > 0) {
	     k2 = search_data ((yyvsp[(5) - (6)].ident));
	     if (k2 >= 0) get_center(k1,k2);
	     else yyerror("Data name does not exist");
	   }
	   else  get_center(k1,-1);
	 else yyerror("Data name does not exist");
       }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 601 "asin.y"
    { int k = search_data ((yyvsp[(1) - (5)].ident));
	 if (k >= 0) get_yuv(k);
	 else yyerror("Data name does not exist");
       }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 608 "asin.y"
    { int k = search_data ((yyvsp[(1) - (6)].ident));
	 if (k >= 0) get_div(k, (yyvsp[(5) - (6)].creal));
	 else yyerror("Data name does not exist");
       }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 615 "asin.y"
    { int k = search_data ((yyvsp[(1) - (6)].ident));
	 if (k >= 0) get_add(k, (yyvsp[(5) - (6)].creal));
	 else yyerror("Data name does not exist");
       }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 622 "asin.y"
    { int k = search_data ((yyvsp[(1) - (6)].ident));
	 if (k >= 0) get_sub(k, (yyvsp[(5) - (6)].creal));
	 else yyerror("Data name does not exist");
       }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 629 "asin.y"
    { int k = search_data ((yyvsp[(1) - (5)].ident));
	 if (k >= 0) get_maxmin(k);
	 else yyerror("Data name does not exist");
       }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 636 "asin.y"
    { int k = search_data ((yyvsp[(1) - (6)].ident));
	 if (k >= 0) get_store(k, (yyvsp[(5) - (6)].ident));
	 else yyerror("Data name does not exist");
       }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 643 "asin.y"
    { int k = search_data ((yyvsp[(1) - (6)].ident));
	 if (k >= 0) get_mul(k, (yyvsp[(5) - (6)].creal));
	 else yyerror("Data name does not exist");
       }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 655 "asin.y"
    { (yyval.aux) = insert_net_stack(-1, -1); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 659 "asin.y"
    { int k = search_network((yyvsp[(3) - (3)].ident)); (yyval.aux) = (yyvsp[(1) - (3)].aux);

	 if (k >= 0) (yyval.aux) = insert_net_stack((yyvsp[(1) - (3)].aux), k); 
	 else yyerror("The name of network does not exist");
       }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 667 "asin.y"
    { (yyval.ident) = ""; }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 668 "asin.y"
    { (yyval.ident) = (yyvsp[(1) - (1)].ident); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 674 "asin.y"
    { (yyval.ident) = get_amend_param_ctr((yyvsp[(1) - (3)].aux), (yyvsp[(3) - (3)].creal)); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 678 "asin.y"
    { (yyval.ident) = get_amend_param_cte((yyvsp[(1) - (3)].aux), (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 682 "asin.y"
    { (yyval.aux) = mu;         }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 683 "asin.y"
    { (yyval.aux) = mmu;        }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 684 "asin.y"
    { (yyval.aux) = l2;         }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 685 "asin.y"
    { (yyval.aux) = l1;         }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 686 "asin.y"
    { (yyval.aux) = maxn;       }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 687 "asin.y"
    { (yyval.aux) = drop;       }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 688 "asin.y"
    { (yyval.aux) = noiser;     }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 689 "asin.y"
    { (yyval.aux) = noisesd;    }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 690 "asin.y"
    { (yyval.aux) = brightness; }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 691 "asin.y"
    { (yyval.aux) = contrast;   }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 692 "asin.y"
    { (yyval.aux) = lambda;     }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 693 "asin.y"
    { (yyval.aux) = noiseb;     }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 694 "asin.y"
    { (yyval.aux) = advf;       }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 698 "asin.y"
    { (yyval.aux) = bn;         }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 699 "asin.y"
    { (yyval.aux) = act;        }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 700 "asin.y"
    { (yyval.aux) = shift;      }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 701 "asin.y"
    { (yyval.aux) = flip;       }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 702 "asin.y"
    { (yyval.aux) = adv;        }
    break;



/* Line 1806 of yacc.c  */
#line 2616 "asin.c"
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
#line 705 "asin.y"

/*****************************************************************************/
/*****************************************************************************/

