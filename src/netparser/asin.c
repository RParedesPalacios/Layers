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
     shift_ = 300,
     flip_ = 301,
     brightness_ = 302,
     contrast_ = 303,
     bn_ = 304,
     const_ = 305,
     data_ = 306,
     network_ = 307,
     script_ = 308,
     train_ = 309,
     save_ = 310,
     zscore_ = 311,
     yuv_ = 312,
     printkernels_ = 313,
     local_ = 314,
     load_ = 315,
     testout_ = 316,
     BCB_ = 317,
     ECB_ = 318,
     BSB_ = 319,
     ESB_ = 320,
     BRB_ = 321,
     ERB_ = 322,
     PER_ = 323,
     COM_ = 324,
     EQ_ = 325,
     RAR_ = 326,
     id_ = 327,
     nfile_ = 328,
     cte_ = 329,
     ctr_ = 330
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 10 "asin.y"
 /********************************************************************/
  char*   ident;                      /* for the "identifier" terminal       */
  int     cent;                       /* for the "integer constant" terminal */
  float   creal;                      /* for the "real constant" terminal    */
  int     aux;



/* Line 293 of yacc.c  */
#line 202 "asin.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 214 "asin.c"

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
#define YYLAST   266

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  110
/* YYNRULES -- Number of states.  */
#define YYNSTATES  232

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   330

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
      75
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
     259,   261,   267,   271,   280,   288,   295,   302,   309,   316,
     323,   329,   330,   334,   335,   337,   341,   345,   347,   349,
     351,   353,   355,   357,   359,   361,   363,   365,   367,   369,
     371
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      77,     0,    -1,    -1,    -1,    78,    80,    79,    83,    -1,
      -1,    50,    62,    81,    63,    -1,    81,    82,    -1,    82,
      -1,     3,    70,    74,    -1,     4,    70,    74,    -1,     5,
      70,    73,    -1,    83,    84,    -1,    84,    -1,    85,    -1,
      92,    -1,   111,    -1,    51,    62,    86,    63,    -1,    86,
      87,    -1,    87,    -1,    -1,    72,    88,    64,    89,    65,
      -1,    89,    69,    90,    -1,    90,    -1,     6,    70,    73,
      -1,    91,    -1,    10,    -1,    11,    -1,    -1,    52,    72,
      93,    62,    94,    97,    63,    -1,    51,     7,    72,    95,
      -1,    -1,    95,    96,    -1,    51,     8,    72,    -1,    51,
       9,    72,    -1,    97,    98,    -1,    98,    -1,    99,    -1,
     109,    -1,    13,    72,    -1,    14,    72,    64,   100,    65,
      -1,    16,    72,    64,   102,    65,    -1,    12,    72,    64,
     104,    65,    -1,    15,    72,    64,   105,    65,    -1,    17,
      72,    64,   107,    65,    -1,    18,    72,    -1,   100,    69,
     101,    -1,   101,    -1,    19,    -1,    20,    -1,    21,    -1,
     102,    69,   103,    -1,   103,    -1,    22,    70,    74,    -1,
      23,    70,    74,    -1,    24,    70,    74,    -1,    25,    70,
      74,    -1,    26,    70,    74,    -1,    -1,    59,    -1,    27,
      70,    74,    -1,   105,    69,   106,    -1,   106,    -1,    28,
      70,    74,    -1,    29,    70,    74,    -1,    30,    70,    74,
      -1,    31,    70,    74,    -1,    32,    70,    74,    -1,    33,
      70,    74,    -1,   107,    69,   108,    -1,   108,    -1,    34,
      70,    74,    -1,    35,    70,    74,    -1,   110,    71,   110,
      -1,    72,    68,    72,    -1,    72,    -1,    53,    62,   112,
      63,    -1,   112,   113,    -1,   113,    -1,   114,    -1,   115,
      -1,    72,    68,    72,    68,   118,    -1,    72,    68,   118,
      -1,    72,    68,    72,    68,    58,    66,    73,    67,    -1,
      54,    66,    74,    69,    74,   116,    67,    -1,    72,    68,
      54,    66,    74,    67,    -1,    72,    68,    55,    66,    73,
      67,    -1,    72,    68,    60,    66,    73,    67,    -1,    72,
      68,    61,    66,    73,    67,    -1,    72,    68,    56,    66,
     117,    67,    -1,    72,    68,    57,    66,    67,    -1,    -1,
     116,    69,    72,    -1,    -1,    72,    -1,   119,    70,    75,
      -1,   120,    70,    74,    -1,    36,    -1,    37,    -1,    39,
      -1,    40,    -1,    41,    -1,    38,    -1,    43,    -1,    44,
      -1,    47,    -1,    48,    -1,    49,    -1,    42,    -1,    45,
      -1,    46,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    43,    43,    47,    43,    54,    56,    60,    61,    65,
      69,    73,    79,    80,    84,    88,    92,    96,   100,   101,
     106,   104,   115,   116,   120,   124,   130,   131,   137,   135,
     143,   152,   154,   158,   166,   176,   177,   181,   182,   185,
     192,   203,   214,   223,   234,   245,   255,   256,   260,   264,
     268,   274,   275,   279,   283,   287,   291,   295,   303,   308,
     315,   324,   325,   329,   333,   337,   341,   345,   349,   355,
     356,   360,   364,   370,   376,   380,   386,   390,   391,   395,
     396,   400,   413,   423,   436,   440,   447,   455,   463,   471,
     484,   496,   498,   505,   506,   510,   514,   520,   521,   522,
     523,   524,   525,   526,   527,   528,   529,   533,   534,   535,
     536
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
  "shift_", "flip_", "brightness_", "contrast_", "bn_", "const_", "data_",
  "network_", "script_", "train_", "save_", "zscore_", "yuv_",
  "printkernels_", "local_", "load_", "testout_", "BCB_", "ECB_", "BSB_",
  "ESB_", "BRB_", "ERB_", "PER_", "COM_", "EQ_", "RAR_", "id_", "nfile_",
  "cte_", "ctr_", "$accept", "experiment", "$@1", "$@2", "def_constants",
  "list_constants", "def_const", "list_definitions", "definition",
  "def_data", "list_data", "data", "$@3", "param_data", "def_param",
  "filetype", "def_network", "$@4", "net_data", "rest_data", "net_defdata",
  "list_statements", "statement", "layer", "fo_lparam", "fo_param",
  "ci_lparam", "ci_param", "f_param", "c_lparam", "c_param", "mp_lparam",
  "mp_param", "edge", "name_layer", "def_script", "list_actions", "action",
  "amendment", "command", "rest_train", "rest_zscore", "parameter",
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
     325,   326,   327,   328,   329,   330
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    76,    78,    79,    77,    80,    80,    81,    81,    82,
      82,    82,    83,    83,    84,    84,    84,    85,    86,    86,
      88,    87,    89,    89,    90,    90,    91,    91,    93,    92,
      94,    95,    95,    96,    96,    97,    97,    98,    98,    99,
      99,    99,    99,    99,    99,    99,   100,   100,   101,   101,
     101,   102,   102,   103,   103,   103,   103,   103,   104,   104,
     104,   105,   105,   106,   106,   106,   106,   106,   106,   107,
     107,   108,   108,   109,   110,   110,   111,   112,   112,   113,
     113,   114,   114,   115,   115,   115,   115,   115,   115,   115,
     115,   116,   116,   117,   117,   118,   118,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   120,   120,   120,
     120
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
       1,     5,     3,     8,     7,     6,     6,     6,     6,     6,
       5,     0,     3,     0,     1,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1
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
      77,     0,     0,     0,     0,    97,    98,   102,    99,   100,
     101,   108,   103,   104,   109,   110,   105,   106,   107,     0,
       0,     0,     0,     0,     0,     0,    82,     0,     0,     0,
      26,    27,     0,    23,    25,     0,     0,     0,     0,     0,
       0,     0,     0,    75,     0,    36,    37,    38,     0,     0,
       0,     0,    93,     0,     0,     0,     0,     0,     0,     0,
      21,     0,    31,     0,    39,     0,     0,     0,     0,    45,
       0,    29,    35,     0,    91,     0,     0,    94,     0,    90,
       0,     0,     0,    81,    95,    96,    24,    22,    30,    58,
       0,     0,     0,     0,    74,    73,     0,    85,    86,    89,
      87,    88,     0,     0,    32,     0,    59,     0,    48,    49,
      50,     0,    47,     0,     0,     0,     0,     0,     0,     0,
      62,     0,     0,     0,     0,     0,     0,    52,     0,     0,
       0,    70,    84,     0,     0,     0,     0,     0,    42,    40,
       0,     0,     0,     0,     0,     0,     0,    43,     0,     0,
       0,     0,     0,     0,    41,     0,     0,     0,    44,     0,
      92,    83,    33,    34,    60,    46,    63,    64,    65,    66,
      67,    68,    61,    53,    54,    55,    56,    57,    51,    71,
      72,    69
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     7,     5,    11,    12,    16,    17,    18,
      34,    35,    43,    82,    83,    84,    19,    36,    53,   138,
     154,    94,    95,    96,   161,   162,   176,   177,   157,   169,
     170,   180,   181,    97,    98,    20,    39,    40,    41,    42,
     146,   128,    76,    77,    78
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -70
static const yytype_int16 yypact[] =
{
     -70,    33,    -1,   -70,     2,   -70,    95,    50,     3,    21,
      38,    11,   -70,    51,    23,    52,    50,   -70,   -70,   -70,
     -70,    41,    42,    44,   -70,   -70,    47,   -70,   -22,   -70,
     -70,   -70,   -70,   -70,   -24,   -70,    56,    54,    53,   -20,
     -70,   -70,   -70,    48,   -70,   -70,    71,    49,   -19,   -70,
     -70,    34,   117,    -5,    57,   -70,   -70,   -70,   -70,   -70,
     -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,    59,
      61,    62,    63,    64,    65,    66,   -70,    67,    68,    69,
     -70,   -70,    -4,   -70,   -70,    60,    70,    72,    73,    74,
      75,    76,    77,    82,   -12,   -70,   -70,   -70,    80,    78,
      79,    81,    83,    89,    84,    86,    39,    58,    87,    90,
     -70,    34,   -70,    94,   -70,    96,    98,   100,   101,   -70,
      97,   -70,   -70,    99,   -70,   103,   105,   -70,   106,   -70,
     107,   108,   110,   -70,   -70,   -70,   -70,   -70,    92,     4,
      85,    26,    46,    12,   -70,   -70,    40,   -70,   -70,   -70,
     -70,   -70,    93,   102,   -70,   109,   -70,   112,   -70,   -70,
     -70,    -3,   -70,   111,   113,   114,   115,   116,   118,    24,
     -70,   119,   120,   121,   122,   123,    25,   -70,   124,   125,
      27,   -70,   -70,   126,   129,   127,   128,   104,   -70,   -70,
      85,   130,   131,   132,   133,   134,   135,   -70,    26,   136,
     137,   138,   139,   140,   -70,    46,   141,   142,   -70,    12,
     -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,
     -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,
     -70,   -70
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -70,   -70,   -70,   -70,   -70,   -70,   156,   -70,   152,   -70,
     -70,   146,   -70,   -70,    29,   -70,   -70,   -70,   -70,   -70,
     -70,   -70,    88,   -70,   -70,   -55,   -70,   -69,   -70,   -70,
     -57,   -70,    -8,   -70,   143,   -70,   -70,   148,   -70,   -70,
     -70,   -70,    91,   -70,   -70
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      86,    87,    88,    89,    90,    91,    92,    86,    87,    88,
      89,    90,    91,    92,     8,     9,    10,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,   155,    37,     3,    37,    69,    70,    71,    72,    44,
      79,    73,    74,    49,    80,    81,   178,   179,    33,     4,
      38,   121,    38,    75,   163,   164,   165,   166,   167,   168,
      93,   110,   189,   156,     6,   111,   190,    93,   171,   172,
     173,   174,   175,    21,    24,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,   197,
     204,    22,   208,   198,   205,    27,   209,   132,     8,     9,
      10,    13,    14,    15,   158,   159,   160,   182,    23,   183,
     185,   186,    51,    26,    28,    30,    31,    32,    46,    33,
      47,    48,    52,    54,    85,   100,    99,   101,   102,   103,
     104,   105,   112,   134,   106,   215,   228,   107,   108,   109,
     137,   222,   113,   153,   114,   115,   116,   117,   118,   119,
     120,   123,   124,   125,   126,   127,   129,   130,   139,   131,
     140,   135,   141,   136,   142,   143,   184,    25,    29,   144,
     147,    93,   148,   149,   150,   151,   152,   188,   214,   187,
      45,   191,   122,   192,   193,   194,   195,    50,   196,   199,
     200,   201,   202,   203,   206,   207,   211,   133,   210,   212,
     213,   231,     0,     0,   216,   217,   218,   219,   220,   221,
     223,   224,   225,   226,   227,   229,   230,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   145
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-70))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      12,    13,    14,    15,    16,    17,    18,    12,    13,    14,
      15,    16,    17,    18,     3,     4,     5,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    27,    54,     0,    54,    54,    55,    56,    57,    63,
       6,    60,    61,    63,    10,    11,    34,    35,    72,    50,
      72,    63,    72,    72,    28,    29,    30,    31,    32,    33,
      72,    65,    65,    59,    62,    69,    69,    72,    22,    23,
      24,    25,    26,    70,    63,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    65,
      65,    70,    65,    69,    69,    72,    69,    58,     3,     4,
       5,    51,    52,    53,    19,    20,    21,    67,    70,    69,
       8,     9,    64,    62,    62,    74,    74,    73,    62,    72,
      66,    68,    51,    74,     7,    66,    69,    66,    66,    66,
      66,    66,    72,    75,    68,   190,   205,    70,    70,    70,
     111,   198,    72,    51,    72,    72,    72,    72,    72,    72,
      68,    71,    74,    74,    73,    72,    67,    73,    64,    73,
      64,    74,    64,    73,    64,    64,    73,    11,    16,    72,
      67,    72,    67,    67,    67,    67,    66,    65,    74,    70,
      34,    70,    94,    70,    70,    70,    70,    39,    70,    70,
      70,    70,    70,    70,    70,    70,    67,   106,    72,    72,
      72,   209,    -1,    -1,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   123
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    77,    78,     0,    50,    80,    62,    79,     3,     4,
       5,    81,    82,    51,    52,    53,    83,    84,    85,    92,
     111,    70,    70,    70,    63,    82,    62,    72,    62,    84,
      74,    74,    73,    72,    86,    87,    93,    54,    72,   112,
     113,   114,   115,    88,    63,    87,    62,    66,    68,    63,
     113,    64,    51,    94,    74,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    54,
      55,    56,    57,    60,    61,    72,   118,   119,   120,     6,
      10,    11,    89,    90,    91,     7,    12,    13,    14,    15,
      16,    17,    18,    72,    97,    98,    99,   109,   110,    69,
      66,    66,    66,    66,    66,    66,    68,    70,    70,    70,
      65,    69,    72,    72,    72,    72,    72,    72,    72,    72,
      68,    63,    98,    71,    74,    74,    73,    72,   117,    67,
      73,    73,    58,   118,    75,    74,    73,    90,    95,    64,
      64,    64,    64,    64,    72,   110,   116,    67,    67,    67,
      67,    67,    66,    51,    96,    27,    59,   104,    19,    20,
      21,   100,   101,    28,    29,    30,    31,    32,    33,   105,
     106,    22,    23,    24,    25,    26,   102,   103,    34,    35,
     107,   108,    67,    69,    73,     8,     9,    70,    65,    65,
      69,    70,    70,    70,    70,    70,    70,    65,    69,    70,
      70,    70,    70,    70,    65,    69,    70,    70,    65,    69,
      72,    67,    72,    72,    74,   101,    74,    74,    74,    74,
      74,    74,   106,    74,    74,    74,    74,    74,   103,    74,
      74,   108
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
#line 43 "asin.y"
    { begin_experiment(); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 47 "asin.y"
    { get_gconstants(); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 51 "asin.y"
    { end_experiment(); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 67 "asin.y"
    { insert_gconstants(BATCH, (yyvsp[(3) - (3)].cent), ""); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 71 "asin.y"
    { insert_gconstants(THREADS, (yyvsp[(3) - (3)].cent), ""); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 75 "asin.y"
    { insert_gconstants(LOG, 0, (yyvsp[(3) - (3)].ident)); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 86 "asin.y"
    { get_data(); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 90 "asin.y"
    { get_network(); end_network(); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 106 "asin.y"
    { int k = search_data((yyvsp[(1) - (1)].ident));
	 if (k < 0)  inser_name_data((yyvsp[(1) - (1)].ident));
	 else yyerror("Data name already exists");
       }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 122 "asin.y"
    { inser_param_data((yyvsp[(3) - (3)].ident), NONE); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 126 "asin.y"
    { inser_param_data("", (yyvsp[(1) - (1)].aux));   }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 130 "asin.y"
    { (yyval.aux) = ASCII;  }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 131 "asin.y"
    { (yyval.aux) = BINARY; }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 137 "asin.y"
    { insert_name_network((yyvsp[(2) - (2)].ident)); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 145 "asin.y"
    { int k = search_data ((yyvsp[(3) - (4)].ident));
	 if (k < 0)
	   yyerror("Data name does not exist");
	 else inser_param_net_data(tr, k);
       }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 160 "asin.y"
    { int k = search_data ((yyvsp[(3) - (3)].ident));
	 if (k < 0)
	   yyerror("Data name does not exist");
	 else inser_param_net_data(ts, k);
       }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 168 "asin.y"
    { int k = search_data ((yyvsp[(3) - (3)].ident));
	 if (k < 0)
	   yyerror("Data name does not exist");
	 else inser_param_net_data(va, k);
       }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 187 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (2)].ident));
	 if (k < 0) insert_name_layer((yyvsp[(2) - (2)].ident), FI);
	 else  yyerror("Layer name already exists in this network");
       }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 194 "asin.y"
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
#line 205 "asin.y"
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
#line 216 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (5)].ident));
	 if (k >= 0) 
	   yyerror("Layer name already exists in this network");
	 else if ((yyvsp[(4) - (5)].aux) == TRUE) insert_name_layer((yyvsp[(2) - (5)].ident), F);
	 else insert_name_layer((yyvsp[(2) - (5)].ident), R);
       }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 225 "asin.y"
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
#line 236 "asin.y"
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
#line 247 "asin.y"
    { int k = search_layer(-1, (yyvsp[(2) - (2)].ident));
	 if (k >= 0) 
	   yyerror("Layer name already exists in this network");
	 else insert_name_layer((yyvsp[(2) - (2)].ident), CA);
       }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 262 "asin.y"
    { insert_param_layer(1, CLASSIFICATION); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 266 "asin.y"
    { insert_param_layer(1, REGRESSION); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 270 "asin.y"
    { insert_param_layer(2, AUTOENCODER); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 281 "asin.y"
    { insert_param_layer(1, (yyvsp[(3) - (3)].cent)); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 285 "asin.y"
    { insert_param_layer(2, (yyvsp[(3) - (3)].cent)); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 289 "asin.y"
    { insert_param_layer(3, (yyvsp[(3) - (3)].cent)); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 293 "asin.y"
    { insert_param_layer(4, (yyvsp[(3) - (3)].cent)); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 297 "asin.y"
    { insert_param_layer(5, (yyvsp[(3) - (3)].cent)); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 303 "asin.y"
    {
	 (yyval.aux) = FALSE;
	 insert_param_layer(1, 0);
       }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 310 "asin.y"
    { 
         (yyval.aux) = FALSE;
	 insert_param_layer(1, 1);
       }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 317 "asin.y"
    { 
         (yyval.aux) = TRUE;
	 insert_param_layer(1, (yyvsp[(3) - (3)].cent));
       }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 331 "asin.y"
    { insert_param_layer(1, (yyvsp[(3) - (3)].cent)); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 335 "asin.y"
    { insert_param_layer(2, (yyvsp[(3) - (3)].cent)); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 339 "asin.y"
    { insert_param_layer(3, (yyvsp[(3) - (3)].cent)); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 343 "asin.y"
    { insert_param_layer(4, (yyvsp[(3) - (3)].cent)); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 347 "asin.y"
    { insert_param_layer(5, (yyvsp[(3) - (3)].cent)); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 351 "asin.y"
    { insert_param_layer(6, (yyvsp[(3) - (3)].cent)); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 362 "asin.y"
    { insert_param_layer(1, (yyvsp[(3) - (3)].cent)); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 366 "asin.y"
    { insert_param_layer(2, (yyvsp[(3) - (3)].cent)); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 372 "asin.y"
    { insert_link((yyvsp[(1) - (3)].aux),(yyvsp[(3) - (3)].aux)); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 378 "asin.y"
    { (yyval.aux) = search_states((yyvsp[(1) - (3)].ident), (yyvsp[(3) - (3)].ident)); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 382 "asin.y"
    { (yyval.aux) = search_states("", (yyvsp[(1) - (1)].ident));  }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 402 "asin.y"
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
#line 415 "asin.y"
    { int k = search_network ((yyvsp[(1) - (3)].ident));
	 if (k < 0)
	   yyerror("Network name does not exist");
	 else get_amendment(NETWORK, k, (yyvsp[(3) - (3)].ident));
       }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 425 "asin.y"
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

  case 84:

/* Line 1806 of yacc.c  */
#line 438 "asin.y"
    { get_train((yyvsp[(3) - (7)].cent), (yyvsp[(5) - (7)].cent), (yyvsp[(6) - (7)].aux)); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 442 "asin.y"
    { int k = search_network ((yyvsp[(1) - (6)].ident));
	 if (k >= 0)  get_net_train(k, (yyvsp[(5) - (6)].cent));
	 else yyerror("Network name does not exist");
       }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 449 "asin.y"
    { int k = search_network ((yyvsp[(1) - (6)].ident));
	 if (k < 0)
	   yyerror("Network name does not exist");
	 else get_save(k, (yyvsp[(5) - (6)].ident));
       }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 457 "asin.y"
    { int k = search_network ((yyvsp[(1) - (6)].ident));
	 if (k < 0)
	   yyerror("Network name does not exist");
	 else get_load(k, (yyvsp[(5) - (6)].ident));
       }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 465 "asin.y"
    { int k = search_network ((yyvsp[(1) - (6)].ident));
	 if (k < 0)
	   yyerror("Network name does not exist");
	 else get_testout(k, (yyvsp[(5) - (6)].ident));
       }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 473 "asin.y"
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

  case 90:

/* Line 1806 of yacc.c  */
#line 486 "asin.y"
    { int k = search_data ((yyvsp[(1) - (5)].ident));
	 if (k >= 0) get_yuv(k);
	 else yyerror("Data name does not exist");
       }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 496 "asin.y"
    { (yyval.aux) = insert_net_stack(-1, ""); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 500 "asin.y"
    { (yyval.aux) = insert_net_stack((yyvsp[(1) - (3)].aux), (yyvsp[(3) - (3)].ident)); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 505 "asin.y"
    { (yyval.ident) = ""; }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 506 "asin.y"
    { (yyval.ident) = (yyvsp[(1) - (1)].ident); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 512 "asin.y"
    { (yyval.ident) = get_amend_param_ctr((yyvsp[(1) - (3)].aux), (yyvsp[(3) - (3)].creal)); }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 516 "asin.y"
    { (yyval.ident) = get_amend_param_cte((yyvsp[(1) - (3)].aux), (yyvsp[(3) - (3)].cent)); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 520 "asin.y"
    { (yyval.aux) = mu;         }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 521 "asin.y"
    { (yyval.aux) = mmu;        }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 522 "asin.y"
    { (yyval.aux) = l2;         }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 523 "asin.y"
    { (yyval.aux) = l1;         }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 524 "asin.y"
    { (yyval.aux) = maxn;       }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 525 "asin.y"
    { (yyval.aux) = drop;       }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 526 "asin.y"
    { (yyval.aux) = noiser;     }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 527 "asin.y"
    { (yyval.aux) = noisesd;    }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 528 "asin.y"
    { (yyval.aux) = brightness; }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 529 "asin.y"
    { (yyval.aux) = contrast;   }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 533 "asin.y"
    { (yyval.aux) = bn;         }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 534 "asin.y"
    { (yyval.aux) = act;        }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 535 "asin.y"
    { (yyval.aux) = shift;      }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 536 "asin.y"
    { (yyval.aux) = flip;       }
    break;



/* Line 1806 of yacc.c  */
#line 2310 "asin.c"
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
#line 539 "asin.y"

/*****************************************************************************/
int main (int argc, char **argv) 
/* Manages the command line and invokes the syntactic-semantic analyzer.     */
{ int i, n = 0;
  for (i=0; i<argc; ++i) 
    if (strcmp(argv[i], "-v")==0) { verbosity = TRUE; n++; }
  --argc; n++;
  if (argc == n) 
    if ((yyin = fopen (argv[argc], "r")) == NULL) {
      fprintf (stderr, "Invalid file: %s\n", argv[argc]);
      exit(1);      
    }
    else {        
      if (verbosity == TRUE) fprintf(stdout,"%3d.- ", yylineno);
      yyparse ();
      if (verbosity == TRUE) fprintf(stdout,"\n");  
      dump_file(); 
      }   
  else fprintf (stderr, "Use: cmc [-v] fichero\n");
  exit(0);
}
/*****************************************************************************/
/*****************************************************************************/

