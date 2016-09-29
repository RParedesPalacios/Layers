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
     filename_ = 261,
     tr_ = 262,
     ts_ = 263,
     va_ = 264,
     ascii_ = 265,
     binary_ = 266,
     F_ = 267,
     FI_ = 268,
     FO_ = 269,
     C_ = 270,
     CI_ = 271,
     MP_ = 272,
     CA_ = 273,
     classification_ = 274,
     regression_ = 275,
     autoencoder_ = 276,
     nz_ = 277,
     nr_ = 278,
     nc_ = 279,
     cr_ = 280,
     cc_ = 281,
     numnodes_ = 282,
     nk_ = 283,
     kr_ = 284,
     kc_ = 285,
     rpad_ = 286,
     cpad_ = 287,
     stride_ = 288,
     sizer_ = 289,
     sizec_ = 290,
     mu_ = 291,
     mmu_ = 292,
     drop_ = 293,
     l2_ = 294,
     l1_ = 295,
     maxn_ = 296,
     act_ = 297,
     noiser_ = 298,
     noisesd_ = 299,
     lambda_ = 300,
     shift_ = 301,
     flip_ = 302,
     brightness_ = 303,
     contrast_ = 304,
     bn_ = 305,
     balance_ = 306,
     noiseb_ = 307,
     const_ = 308,
     data_ = 309,
     network_ = 310,
     script_ = 311,
     train_ = 312,
     save_ = 313,
     zscore_ = 314,
     yuv_ = 315,
     printkernels_ = 316,
     copy_ = 317,
     local_ = 318,
     load_ = 319,
     testout_ = 320,
     center_ = 321,
     div_ = 322,
     test_ = 323,
     BCB_ = 324,
     ECB_ = 325,
     BSB_ = 326,
     ESB_ = 327,
     BRB_ = 328,
     ERB_ = 329,
     PER_ = 330,
     COM_ = 331,
     EQ_ = 332,
     RAR_ = 333,
     id_ = 334,
     nfile_ = 335,
     cte_ = 336
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
#line 207 "asin.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 219 "asin.c"

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
#define YYLAST   275

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  82
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  117
/* YYNRULES -- Number of states.  */
#define YYNSTATES  253

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   336

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
      75,    76,    77,    78,    79,    80,    81
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     5,    10,    11,    16,    19,    21,
      25,    29,    33,    36,    38,    40,    42,    44,    49,    52,
      54,    55,    61,    65,    67,    71,    73,    75,    77,    78,
      86,    91,    92,    95,    99,   103,   106,   108,   110,   112,
     115,   121,   127,   133,   139,   145,   148,   152,   154,   156,
     158,   160,   164,   166,   170,   174,   178,   182,   186,   187,
     189,   193,   197,   199,   203,   207,   211,   215,   219,   223,
     227,   229,   233,   237,   241,   245,   247,   252,   255,   257,
     259,   261,   267,   271,   277,   286,   295,   303,   310,   317,
     324,   331,   338,   345,   352,   358,   365,   366,   370,   371,
     373,   377,   381,   383,   385,   387,   389,   391,   393,   395,
     397,   399,   401,   403,   405,   407,   409,   411
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      83,     0,    -1,    -1,    -1,    84,    86,    85,    89,    -1,
      -1,    53,    69,    87,    70,    -1,    87,    88,    -1,    88,
      -1,     3,    77,    81,    -1,     4,    77,    81,    -1,     5,
      77,    80,    -1,    89,    90,    -1,    90,    -1,    91,    -1,
      98,    -1,   117,    -1,    54,    69,    92,    70,    -1,    92,
      93,    -1,    93,    -1,    -1,    79,    94,    71,    95,    72,
      -1,    95,    76,    96,    -1,    96,    -1,     6,    77,    80,
      -1,    97,    -1,    10,    -1,    11,    -1,    -1,    55,    79,
      99,    69,   100,   103,    70,    -1,    54,     7,    79,   101,
      -1,    -1,   101,   102,    -1,    54,     8,    79,    -1,    54,
       9,    79,    -1,   103,   104,    -1,   104,    -1,   105,    -1,
     115,    -1,    13,    79,    -1,    14,    79,    71,   106,    72,
      -1,    16,    79,    71,   108,    72,    -1,    12,    79,    71,
     110,    72,    -1,    15,    79,    71,   111,    72,    -1,    17,
      79,    71,   113,    72,    -1,    18,    79,    -1,   106,    76,
     107,    -1,   107,    -1,    19,    -1,    20,    -1,    21,    -1,
     108,    76,   109,    -1,   109,    -1,    22,    77,    81,    -1,
      23,    77,    81,    -1,    24,    77,    81,    -1,    25,    77,
      81,    -1,    26,    77,    81,    -1,    -1,    63,    -1,    27,
      77,    81,    -1,   111,    76,   112,    -1,   112,    -1,    28,
      77,    81,    -1,    29,    77,    81,    -1,    30,    77,    81,
      -1,    31,    77,    81,    -1,    32,    77,    81,    -1,    33,
      77,    81,    -1,   113,    76,   114,    -1,   114,    -1,    34,
      77,    81,    -1,    35,    77,    81,    -1,   116,    78,   116,
      -1,    79,    75,    79,    -1,    79,    -1,    56,    69,   118,
      70,    -1,   118,   119,    -1,   119,    -1,   120,    -1,   121,
      -1,    79,    75,    79,    75,   124,    -1,    79,    75,   124,
      -1,    79,    75,    51,    77,    81,    -1,    79,    75,    79,
      75,    61,    73,    80,    74,    -1,    79,    75,    79,    75,
      62,    79,    75,    79,    -1,    57,    73,    81,    76,    81,
     122,    74,    -1,    79,    75,    57,    73,    81,    74,    -1,
      79,    75,    68,    73,   123,    74,    -1,    79,    75,    58,
      73,    80,    74,    -1,    79,    75,    64,    73,    80,    74,
      -1,    79,    75,    65,    73,    80,    74,    -1,    79,    75,
      59,    73,   123,    74,    -1,    79,    75,    66,    73,   123,
      74,    -1,    79,    75,    60,    73,    74,    -1,    79,    75,
      67,    73,    81,    74,    -1,    -1,   122,    76,    79,    -1,
      -1,    79,    -1,   125,    77,    81,    -1,   126,    77,    81,
      -1,    36,    -1,    37,    -1,    39,    -1,    40,    -1,    41,
      -1,    38,    -1,    43,    -1,    44,    -1,    48,    -1,    49,
      -1,    45,    -1,    52,    -1,    50,    -1,    42,    -1,    46,
      -1,    47,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    41,    41,    45,    41,    52,    54,    58,    59,    63,
      67,    71,    77,    78,    82,    86,    90,    94,    98,    99,
     104,   102,   113,   114,   118,   122,   128,   129,   135,   133,
     141,   150,   152,   156,   164,   174,   175,   179,   180,   183,
     190,   201,   212,   224,   235,   246,   256,   257,   261,   265,
     269,   275,   276,   280,   284,   288,   292,   296,   304,   309,
     316,   325,   326,   330,   334,   338,   342,   346,   350,   356,
     357,   361,   365,   371,   377,   381,   388,   392,   393,   397,
     398,   402,   415,   422,   431,   444,   457,   461,   468,   481,
     489,   497,   505,   518,   531,   538,   549,   551,   558,   559,
     563,   567,   573,   574,   575,   576,   577,   578,   579,   580,
     581,   582,   583,   584,   588,   589,   590,   591
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "batch_", "threads_", "log_",
  "filename_", "tr_", "ts_", "va_", "ascii_", "binary_", "F_", "FI_",
  "FO_", "C_", "CI_", "MP_", "CA_", "classification_", "regression_",
  "autoencoder_", "nz_", "nr_", "nc_", "cr_", "cc_", "numnodes_", "nk_",
  "kr_", "kc_", "rpad_", "cpad_", "stride_", "sizer_", "sizec_", "mu_",
  "mmu_", "drop_", "l2_", "l1_", "maxn_", "act_", "noiser_", "noisesd_",
  "lambda_", "shift_", "flip_", "brightness_", "contrast_", "bn_",
  "balance_", "noiseb_", "const_", "data_", "network_", "script_",
  "train_", "save_", "zscore_", "yuv_", "printkernels_", "copy_", "local_",
  "load_", "testout_", "center_", "div_", "test_", "BCB_", "ECB_", "BSB_",
  "ESB_", "BRB_", "ERB_", "PER_", "COM_", "EQ_", "RAR_", "id_", "nfile_",
  "cte_", "$accept", "experiment", "$@1", "$@2", "def_constants",
  "list_constants", "def_const", "list_definitions", "definition",
  "def_data", "list_data", "data", "$@3", "param_data", "def_param",
  "filetype", "def_network", "$@4", "net_data", "rest_data", "net_defdata",
  "list_statements", "statement", "layer", "fo_lparam", "fo_param",
  "ci_lparam", "ci_param", "f_param", "c_lparam", "c_param", "mp_lparam",
  "mp_param", "edge", "name_layer", "def_script", "list_actions", "action",
  "amendment", "command", "rest_train", "other_data", "parameter",
  "param_ctr", "param_cte", 0
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
     335,   336
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    82,    84,    85,    83,    86,    86,    87,    87,    88,
      88,    88,    89,    89,    90,    90,    90,    91,    92,    92,
      94,    93,    95,    95,    96,    96,    97,    97,    99,    98,
     100,   101,   101,   102,   102,   103,   103,   104,   104,   105,
     105,   105,   105,   105,   105,   105,   106,   106,   107,   107,
     107,   108,   108,   109,   109,   109,   109,   109,   110,   110,
     110,   111,   111,   112,   112,   112,   112,   112,   112,   113,
     113,   114,   114,   115,   116,   116,   117,   118,   118,   119,
     119,   120,   120,   120,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   122,   122,   123,   123,
     124,   124,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   126,   126,   126,   126
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     4,     0,     4,     2,     1,     3,
       3,     3,     2,     1,     1,     1,     1,     4,     2,     1,
       0,     5,     3,     1,     3,     1,     1,     1,     0,     7,
       4,     0,     2,     3,     3,     2,     1,     1,     1,     2,
       5,     5,     5,     5,     5,     2,     3,     1,     1,     1,
       1,     3,     1,     3,     3,     3,     3,     3,     0,     1,
       3,     3,     1,     3,     3,     3,     3,     3,     3,     3,
       1,     3,     3,     3,     3,     1,     4,     2,     1,     1,
       1,     5,     3,     5,     8,     8,     7,     6,     6,     6,
       6,     6,     6,     6,     5,     6,     0,     3,     0,     1,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     5,     1,     0,     3,     0,     0,     0,     0,
       0,     0,     8,     0,     0,     0,     4,    13,    14,    15,
      16,     0,     0,     0,     6,     7,     0,    28,     0,    12,
       9,    10,    11,    20,     0,    19,     0,     0,     0,     0,
      78,    79,    80,     0,    17,    18,     0,     0,     0,    76,
      77,     0,     0,     0,     0,   102,   103,   107,   104,   105,
     106,   115,   108,   109,   112,   116,   117,   110,   111,   114,
       0,   113,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    82,     0,     0,     0,    26,    27,     0,    23,
      25,     0,     0,     0,     0,     0,     0,     0,     0,    75,
       0,    36,    37,    38,     0,     0,     0,     0,     0,    98,
       0,     0,     0,    98,     0,    98,     0,     0,     0,     0,
      21,     0,    31,     0,    39,     0,     0,     0,     0,    45,
       0,    29,    35,     0,    96,    83,     0,     0,    99,     0,
      94,     0,     0,     0,     0,     0,     0,     0,    81,   100,
     101,    24,    22,    30,    58,     0,     0,     0,     0,    74,
      73,     0,    87,    89,    92,    90,    91,    93,    95,    88,
       0,     0,     0,    32,     0,    59,     0,    48,    49,    50,
       0,    47,     0,     0,     0,     0,     0,     0,     0,    62,
       0,     0,     0,     0,     0,     0,    52,     0,     0,     0,
      70,    86,     0,     0,     0,     0,     0,     0,    42,    40,
       0,     0,     0,     0,     0,     0,     0,    43,     0,     0,
       0,     0,     0,     0,    41,     0,     0,     0,    44,     0,
      97,    84,    85,    33,    34,    60,    46,    63,    64,    65,
      66,    67,    68,    61,    53,    54,    55,    56,    57,    51,
      71,    72,    69
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     7,     5,    11,    12,    16,    17,    18,
      34,    35,    43,    88,    89,    90,    19,    36,    53,   153,
     173,   100,   101,   102,   180,   181,   195,   196,   176,   188,
     189,   199,   200,   103,   104,    20,    39,    40,    41,    42,
     161,   139,    82,    83,    84
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -72
static const yytype_int16 yypact[] =
{
     -72,    36,    16,   -72,    50,   -72,    74,    55,    43,    44,
      45,    11,   -72,    54,    23,    56,    55,   -72,   -72,   -72,
     -72,    47,    48,    51,   -72,   -72,    53,   -72,   -22,   -72,
     -72,   -72,   -72,   -72,   -28,   -72,    57,    60,    49,   -20,
     -72,   -72,   -72,    59,   -72,   -72,    73,    58,   -19,   -72,
     -72,    62,   127,    -5,    61,   -72,   -72,   -72,   -72,   -72,
     -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,
      63,   -72,    65,    68,    69,    70,    71,    72,    75,    76,
      77,    78,   -72,    79,    80,    81,   -72,   -72,    -1,   -72,
     -72,    67,    82,    83,    84,    85,    86,    87,    88,    94,
     -12,   -72,   -72,   -72,    90,    66,    89,    91,    95,    92,
      99,    96,    98,    92,   100,    92,    46,   101,   102,   104,
     -72,    62,   -72,    64,   -72,   103,   106,   108,   109,   -72,
     107,   -72,   -72,   110,   -72,   -72,   111,   113,   -72,   114,
     -72,   116,   117,   118,   119,   120,   122,   121,   -72,   -72,
     -72,   -72,   -72,   105,     7,    93,    33,    30,     9,   -72,
     -72,    41,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,
     123,   124,    97,   -72,   125,   -72,   126,   -72,   -72,   -72,
       4,   -72,   128,   129,   130,   131,   132,   133,    25,   -72,
     134,   135,   136,   137,   138,    27,   -72,   139,   140,    28,
     -72,   -72,   141,   144,   142,   143,   145,   115,   -72,   -72,
      93,   146,   147,   148,   149,   150,   151,   -72,    33,   152,
     153,   154,   155,   156,   -72,    30,   157,   158,   -72,     9,
     -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,
     -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,
     -72,   -72,   -72
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -72,   -72,   -72,   -72,   -72,   -72,   186,   -72,   185,   -72,
     -72,   170,   -72,   -72,    15,   -72,   -72,   -72,   -72,   -72,
     -72,   -72,    52,   -72,   -72,   -59,   -72,   -71,   -72,   -72,
     -63,   -72,   -69,   -72,   112,   -72,   -72,   180,   -72,   -72,
     -72,     3,   159,   -72,   -72
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      92,    93,    94,    95,    96,    97,    98,    92,    93,    94,
      95,    96,    97,    98,     8,     9,    10,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,   174,    37,     3,    37,    72,    73,
      74,    75,    44,   197,   198,    76,    77,    78,    79,    80,
      49,    33,   190,   191,   192,   193,   194,    38,   131,    38,
      81,   182,   183,   184,   185,   186,   187,    99,    85,     4,
     175,   120,    86,    87,    99,   121,   209,     8,     9,    10,
     210,    24,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,   217,    71,   224,
     228,   218,    27,   225,   229,   205,   206,   146,   147,    13,
      14,    15,   177,   178,   179,   201,   143,   202,   145,     6,
      21,    22,    23,    26,    48,    28,    46,    52,    30,    31,
      51,    32,    33,    47,    91,   154,   152,   105,   107,    54,
     106,   108,   109,   110,   111,   112,   122,   134,   113,   114,
     115,   236,   132,   116,   249,   243,   117,   118,   119,   172,
     252,   123,   124,   125,   126,   127,   128,   129,   133,   130,
     135,   138,   136,   140,   155,   137,   141,   156,   142,   157,
     158,   144,   149,   150,   151,   162,   159,   163,   164,    99,
     165,   166,   167,   168,   169,   170,   235,    25,   208,   204,
     171,    29,   207,   203,    45,   211,   212,   213,   214,   215,
     216,   219,   220,   221,   222,   223,   226,   227,   231,    50,
     230,   232,   233,     0,   234,     0,     0,   237,   238,   239,
     240,   241,   242,   244,   245,   246,   247,   248,   250,   251,
       0,     0,     0,     0,     0,   160,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   148
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-72))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      12,    13,    14,    15,    16,    17,    18,    12,    13,    14,
      15,    16,    17,    18,     3,     4,     5,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    27,    57,     0,    57,    57,    58,
      59,    60,    70,    34,    35,    64,    65,    66,    67,    68,
      70,    79,    22,    23,    24,    25,    26,    79,    70,    79,
      79,    28,    29,    30,    31,    32,    33,    79,     6,    53,
      63,    72,    10,    11,    79,    76,    72,     3,     4,     5,
      76,    70,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    72,    52,    72,
      72,    76,    79,    76,    76,     8,     9,    61,    62,    54,
      55,    56,    19,    20,    21,    74,   113,    76,   115,    69,
      77,    77,    77,    69,    75,    69,    69,    54,    81,    81,
      71,    80,    79,    73,     7,    71,   121,    76,    73,    81,
      77,    73,    73,    73,    73,    73,    79,    81,    73,    73,
      73,   210,   100,    75,   225,   218,    77,    77,    77,    54,
     229,    79,    79,    79,    79,    79,    79,    79,    78,    75,
      81,    79,    81,    74,    71,    80,    80,    71,    80,    71,
      71,    81,    81,    81,    80,    74,    79,    74,    74,    79,
      74,    74,    74,    74,    74,    73,    81,    11,    72,    75,
      79,    16,    77,    80,    34,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    74,    39,
      79,    79,    79,    -1,    79,    -1,    -1,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      -1,    -1,    -1,    -1,    -1,   133,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   116
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    83,    84,     0,    53,    86,    69,    85,     3,     4,
       5,    87,    88,    54,    55,    56,    89,    90,    91,    98,
     117,    77,    77,    77,    70,    88,    69,    79,    69,    90,
      81,    81,    80,    79,    92,    93,    99,    57,    79,   118,
     119,   120,   121,    94,    70,    93,    69,    73,    75,    70,
     119,    71,    54,   100,    81,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    57,    58,    59,    60,    64,    65,    66,    67,
      68,    79,   124,   125,   126,     6,    10,    11,    95,    96,
      97,     7,    12,    13,    14,    15,    16,    17,    18,    79,
     103,   104,   105,   115,   116,    76,    77,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    75,    77,    77,    77,
      72,    76,    79,    79,    79,    79,    79,    79,    79,    79,
      75,    70,   104,    78,    81,    81,    81,    80,    79,   123,
      74,    80,    80,   123,    81,   123,    61,    62,   124,    81,
      81,    80,    96,   101,    71,    71,    71,    71,    71,    79,
     116,   122,    74,    74,    74,    74,    74,    74,    74,    74,
      73,    79,    54,   102,    27,    63,   110,    19,    20,    21,
     106,   107,    28,    29,    30,    31,    32,    33,   111,   112,
      22,    23,    24,    25,    26,   108,   109,    34,    35,   113,
     114,    74,    76,    80,    75,     8,     9,    77,    72,    72,
      76,    77,    77,    77,    77,    77,    77,    72,    76,    77,
      77,    77,    77,    77,    72,    76,    77,    77,    72,    76,
      79,    74,    79,    79,    79,    81,   107,    81,    81,    81,
      81,    81,    81,   112,    81,    81,    81,    81,    81,   109,
      81,    81,   114
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
#line 41 "asin.y"
    { begin_experiment(); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 45 "asin.y"
    { get_gconstants(); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 49 "asin.y"
    { end_experiment(); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 65 "asin.y"
    { insert_gconstants(BATCH, (int)(yyvsp[(3) - (3)].creal), ""); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 69 "asin.y"
    { insert_gconstants(THREADS, (int)(yyvsp[(3) - (3)].creal), ""); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 73 "asin.y"
    { insert_gconstants(LOG, 0, (yyvsp[(3) - (3)].ident)); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 84 "asin.y"
    { get_data(); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 88 "asin.y"
    { get_network(); /* end_network(); */ }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 104 "asin.y"
    { int k = search_data((yyvsp[(1) - (1)].ident));
	 if (k < 0)  inser_name_data((yyvsp[(1) - (1)].ident));
	 else yyerror("Data name already exists");
       }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 120 "asin.y"
    { inser_param_data((yyvsp[(3) - (3)].ident), NONE); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 124 "asin.y"
    { inser_param_data("", (yyvsp[(1) - (1)].aux));   }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 128 "asin.y"
    { (yyval.aux) = ASCII;  }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 129 "asin.y"
    { (yyval.aux) = BINARY; }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 135 "asin.y"
    { insert_name_network((yyvsp[(2) - (2)].ident)); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 143 "asin.y"
    { int k = search_data ((yyvsp[(3) - (4)].ident));
	 if (k < 0)
	   yyerror("Data name does not exist");
	 else inser_param_net_data(tr, k);
       }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 158 "asin.y"
    { int k = search_data ((yyvsp[(3) - (3)].ident));
	 if (k < 0)
	   yyerror("Data name does not exist");
	 else inser_param_net_data(ts, k);
       }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 166 "asin.y"
    { int k = search_data ((yyvsp[(3) - (3)].ident));
	 if (k < 0)
	   yyerror("Data name does not exist");
	 else inser_param_net_data(va, k);
       }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 185 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (2)].ident));
	 if (k < 0) insert_name_layer((yyvsp[(2) - (2)].ident), FI);
	 else  yyerror("Layer name already exists in this network");
       }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 192 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (5)].ident));
	 if (k < 0) {
	   check_param_layer(1);
	   insert_name_layer((yyvsp[(2) - (5)].ident), FO);
	 }
	 else yyerror("Layer name already exists in this network");

       }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 203 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (5)].ident));
	 if (k < 0) {
	   check_param_layer(3);
	   insert_name_layer((yyvsp[(2) - (5)].ident), CI);
	 }
	 else yyerror("Layer name already exists in this network");

       }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 214 "asin.y"
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

  case 43:

/* Line 1806 of yacc.c  */
#line 226 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (5)].ident));
	 if (k >= 0)
	   yyerror("Layer name already exists in this network");
	 else {
	   check_param_layer(3);
	   insert_name_layer((yyvsp[(2) - (5)].ident), C);
	 }
       }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 237 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (5)].ident));
	 if (k >= 0)
	   yyerror("Layer name already exists in this network");
	 else {
	   check_param_layer(2);
	   insert_name_layer((yyvsp[(2) - (5)].ident), MP);
	 }
       }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 248 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (2)].ident));
	 if (k >= 0) 
	   yyerror("Layer name already exists in this network");
	 else insert_name_layer((yyvsp[(2) - (2)].ident), CA);
       }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 263 "asin.y"
    { insert_param_layer(1, CLASSIFICATION); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 267 "asin.y"
    { insert_param_layer(1, REGRESSION); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 271 "asin.y"
    { insert_param_layer(2, AUTOENCODER); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 282 "asin.y"
    { insert_param_layer(1, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 286 "asin.y"
    { insert_param_layer(2, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 290 "asin.y"
    { insert_param_layer(3, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 294 "asin.y"
    { insert_param_layer(4, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 298 "asin.y"
    { insert_param_layer(5, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 304 "asin.y"
    {
	 (yyval.aux) = FALSE;
	 insert_param_layer(1, 0);
       }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 311 "asin.y"
    { 
         (yyval.aux) = FALSE;
	 insert_param_layer(1, 1);
       }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 318 "asin.y"
    { 
         (yyval.aux) = TRUE;
	 insert_param_layer(1, (int)(yyvsp[(3) - (3)].creal));
       }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 332 "asin.y"
    { insert_param_layer(1, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 336 "asin.y"
    { insert_param_layer(2, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 340 "asin.y"
    { insert_param_layer(3, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 344 "asin.y"
    { insert_param_layer(4, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 348 "asin.y"
    { insert_param_layer(5, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 352 "asin.y"
    { insert_param_layer(6, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 363 "asin.y"
    { insert_param_layer(1, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 367 "asin.y"
    { insert_param_layer(2, (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 373 "asin.y"
    { insert_link((yyvsp[(1) - (3)].aux),(yyvsp[(3) - (3)].aux)); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 379 "asin.y"
    { (yyval.aux) = search_states((yyvsp[(1) - (3)].ident), (yyvsp[(3) - (3)].ident)); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 383 "asin.y"
    { (yyval.aux) = search_states("", (yyvsp[(1) - (1)].ident));  }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 404 "asin.y"
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

  case 82:

/* Line 1806 of yacc.c  */
#line 417 "asin.y"
    { int k = search_network ((yyvsp[(1) - (3)].ident));
	 if (k >= 0)  get_amendment(NETWORK, k, (yyvsp[(3) - (3)].ident));
	 else yyerror("Network name does not exist");
       }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 424 "asin.y"
    { int k = search_data ((yyvsp[(1) - (5)].ident));
	 if (k >= 0)  get_amendment_data(k, (int)(yyvsp[(5) - (5)].creal));
	 else yyerror("Data or network name does not exist");
       }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 433 "asin.y"
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

  case 85:

/* Line 1806 of yacc.c  */
#line 446 "asin.y"
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

  case 86:

/* Line 1806 of yacc.c  */
#line 459 "asin.y"
    { get_train((int)(yyvsp[(3) - (7)].creal), (int)(yyvsp[(5) - (7)].creal), (yyvsp[(6) - (7)].aux)); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 463 "asin.y"
    { int k = search_network ((yyvsp[(1) - (6)].ident));
	 if (k >= 0)  get_net_train(k, (int)(yyvsp[(5) - (6)].creal));
	 else yyerror("Network name does not exist");
       }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 470 "asin.y"
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

  case 89:

/* Line 1806 of yacc.c  */
#line 483 "asin.y"
    { int k = search_network ((yyvsp[(1) - (6)].ident));
	 if (k < 0)
	   yyerror("Network name does not exist");
	 else get_save(k, (yyvsp[(5) - (6)].ident));
       }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 491 "asin.y"
    { int k = search_network ((yyvsp[(1) - (6)].ident));
	 if (k < 0)
	   yyerror("Network name does not exist");
	 else get_load(k, (yyvsp[(5) - (6)].ident));
       }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 499 "asin.y"
    { int k = search_network ((yyvsp[(1) - (6)].ident));
	 if (k < 0)
	   yyerror("Network name does not exist");
	 else get_testout(k, (yyvsp[(5) - (6)].ident));
       }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 507 "asin.y"
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

  case 93:

/* Line 1806 of yacc.c  */
#line 520 "asin.y"
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

  case 94:

/* Line 1806 of yacc.c  */
#line 533 "asin.y"
    { int k = search_data ((yyvsp[(1) - (5)].ident));
	 if (k >= 0) get_yuv(k);
	 else yyerror("Data name does not exist");
       }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 540 "asin.y"
    { int k = search_data ((yyvsp[(1) - (6)].ident));
	 if (k >= 0) get_div(k, (yyvsp[(5) - (6)].creal));
	 else yyerror("Data name does not exist");
       }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 549 "asin.y"
    { (yyval.aux) = insert_net_stack(-1, ""); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 553 "asin.y"
    { (yyval.aux) = insert_net_stack((yyvsp[(1) - (3)].aux), (yyvsp[(3) - (3)].ident)); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 558 "asin.y"
    { (yyval.ident) = ""; }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 559 "asin.y"
    { (yyval.ident) = (yyvsp[(1) - (1)].ident); }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 565 "asin.y"
    { (yyval.ident) = get_amend_param_ctr((yyvsp[(1) - (3)].aux), (yyvsp[(3) - (3)].creal)); }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 569 "asin.y"
    { (yyval.ident) = get_amend_param_cte((yyvsp[(1) - (3)].aux), (int)(yyvsp[(3) - (3)].creal)); }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 573 "asin.y"
    { (yyval.aux) = mu;         }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 574 "asin.y"
    { (yyval.aux) = mmu;        }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 575 "asin.y"
    { (yyval.aux) = l2;         }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 576 "asin.y"
    { (yyval.aux) = l1;         }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 577 "asin.y"
    { (yyval.aux) = maxn;       }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 578 "asin.y"
    { (yyval.aux) = drop;       }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 579 "asin.y"
    { (yyval.aux) = noiser;     }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 580 "asin.y"
    { (yyval.aux) = noisesd;    }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 581 "asin.y"
    { (yyval.aux) = brightness; }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 582 "asin.y"
    { (yyval.aux) = contrast;   }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 583 "asin.y"
    { (yyval.aux) = lambda;     }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 584 "asin.y"
    { (yyval.aux) = noiseb;     }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 588 "asin.y"
    { (yyval.aux) = bn;         }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 589 "asin.y"
    { (yyval.aux) = act;        }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 590 "asin.y"
    { (yyval.aux) = shift;      }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 591 "asin.y"
    { (yyval.aux) = flip;       }
    break;



/* Line 1806 of yacc.c  */
#line 2413 "asin.c"
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
#line 594 "asin.y"

/*****************************************************************************/
/*****************************************************************************/

