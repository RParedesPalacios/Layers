/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "asin.y" /* yacc.c:339  */

/*****************************************************************************/
/**  Syntactic-semantic analyzer, 2016.             <jmbenedi@prhlt.upv.es> **/
/*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nettable.h"

#line 76 "asin.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "asin.h".  */
#ifndef YY_YY_ASIN_H_INCLUDED
# define YY_YY_ASIN_H_INCLUDED
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
    local_ = 317,
    load_ = 318,
    testout_ = 319,
    center_ = 320,
    div_ = 321,
    test_ = 322,
    BCB_ = 323,
    ECB_ = 324,
    BSB_ = 325,
    ESB_ = 326,
    BRB_ = 327,
    ERB_ = 328,
    PER_ = 329,
    COM_ = 330,
    EQ_ = 331,
    RAR_ = 332,
    id_ = 333,
    nfile_ = 334,
    cte_ = 335
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 10 "asin.y" /* yacc.c:355  */
 /********************************************************************/
  char*   ident;                      /* for the "identifier" terminal       */
  float   creal;                      /* for the "real constant" terminal    */
  int     aux;

#line 203 "asin.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_ASIN_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 218 "asin.c" /* yacc.c:358  */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   275

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  116
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  249

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   335

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    41,    41,    45,    41,    52,    54,    58,    59,    63,
      67,    71,    77,    78,    82,    86,    90,    94,    98,    99,
     104,   102,   113,   114,   118,   122,   128,   129,   135,   133,
     141,   150,   152,   156,   164,   174,   175,   179,   180,   183,
     190,   201,   212,   221,   232,   243,   253,   254,   258,   262,
     266,   272,   273,   277,   281,   285,   289,   293,   301,   306,
     313,   322,   323,   327,   331,   335,   339,   343,   347,   353,
     354,   358,   362,   368,   374,   378,   385,   389,   390,   394,
     395,   399,   412,   419,   428,   441,   445,   452,   465,   473,
     481,   489,   502,   515,   522,   533,   535,   542,   543,   547,
     551,   557,   558,   559,   560,   561,   562,   563,   564,   565,
     566,   567,   568,   572,   573,   574,   575
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
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
  "train_", "save_", "zscore_", "yuv_", "printkernels_", "local_", "load_",
  "testout_", "center_", "div_", "test_", "BCB_", "ECB_", "BSB_", "ESB_",
  "BRB_", "ERB_", "PER_", "COM_", "EQ_", "RAR_", "id_", "nfile_", "cte_",
  "$accept", "experiment", "$@1", "$@2", "def_constants", "list_constants",
  "def_const", "list_definitions", "definition", "def_data", "list_data",
  "data", "$@3", "param_data", "def_param", "filetype", "def_network",
  "$@4", "net_data", "rest_data", "net_defdata", "list_statements",
  "statement", "layer", "fo_lparam", "fo_param", "ci_lparam", "ci_param",
  "f_param", "c_lparam", "c_param", "mp_lparam", "mp_param", "edge",
  "name_layer", "def_script", "list_actions", "action", "amendment",
  "command", "rest_train", "other_data", "parameter", "param_ctr",
  "param_cte", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335
};
# endif

#define YYPACT_NINF -73

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-73)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -73,    36,   -10,   -73,     2,   -73,   104,    56,     3,    46,
      47,    11,   -73,    33,    42,    53,    56,   -73,   -73,   -73,
     -73,    48,    49,    51,   -73,   -73,    54,   -73,   -22,   -73,
     -73,   -73,   -73,   -73,   -27,   -73,    57,    55,    50,   -20,
     -73,   -73,   -73,    61,   -73,   -73,    72,    58,   -19,   -73,
     -73,    44,   126,    -5,    59,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,
      60,   -73,    63,    65,    67,    68,    69,    70,    71,    73,
      74,    75,   -73,    76,    77,    78,   -73,   -73,    -4,   -73,
     -73,    66,    79,    80,    81,    82,    83,    84,    85,    90,
     -12,   -73,   -73,   -73,    88,    86,    87,    89,    91,    93,
      95,    97,    98,    93,    92,    93,    45,    99,   100,   102,
     -73,    44,   -73,   103,   -73,   105,   108,   112,   113,   -73,
     106,   -73,   -73,   107,   -73,   -73,   101,   114,   -73,   115,
     -73,   116,   117,   118,   119,   120,   122,   -73,   -73,   -73,
     -73,   -73,   132,     7,    94,    32,    52,    18,   -73,   -73,
      43,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   121,
      96,   -73,   123,   -73,   124,   -73,   -73,   -73,    -3,   -73,
     125,   127,   128,   129,   130,   131,    25,   -73,   133,   134,
     135,   136,   137,    27,   -73,   138,   139,    28,   -73,   -73,
     140,   143,   141,   142,   144,   -73,   -73,    94,   145,   146,
     147,   148,   149,   150,   -73,    32,   151,   152,   153,   154,
     155,   -73,    52,   156,   157,   -73,    18,   -73,   -73,   -73,
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     5,     1,     0,     3,     0,     0,     0,     0,
       0,     0,     8,     0,     0,     0,     4,    13,    14,    15,
      16,     0,     0,     0,     6,     7,     0,    28,     0,    12,
       9,    10,    11,    20,     0,    19,     0,     0,     0,     0,
      78,    79,    80,     0,    17,    18,     0,     0,     0,    76,
      77,     0,     0,     0,     0,   101,   102,   106,   103,   104,
     105,   114,   107,   108,   111,   115,   116,   109,   110,   113,
       0,   112,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    82,     0,     0,     0,    26,    27,     0,    23,
      25,     0,     0,     0,     0,     0,     0,     0,     0,    75,
       0,    36,    37,    38,     0,     0,     0,     0,     0,    97,
       0,     0,     0,    97,     0,    97,     0,     0,     0,     0,
      21,     0,    31,     0,    39,     0,     0,     0,     0,    45,
       0,    29,    35,     0,    95,    83,     0,     0,    98,     0,
      93,     0,     0,     0,     0,     0,     0,    81,    99,   100,
      24,    22,    30,    58,     0,     0,     0,     0,    74,    73,
       0,    86,    88,    91,    89,    90,    92,    94,    87,     0,
       0,    32,     0,    59,     0,    48,    49,    50,     0,    47,
       0,     0,     0,     0,     0,     0,     0,    62,     0,     0,
       0,     0,     0,     0,    52,     0,     0,     0,    70,    85,
       0,     0,     0,     0,     0,    42,    40,     0,     0,     0,
       0,     0,     0,     0,    43,     0,     0,     0,     0,     0,
       0,    41,     0,     0,     0,    44,     0,    96,    84,    33,
      34,    60,    46,    63,    64,    65,    66,    67,    68,    61,
      53,    54,    55,    56,    57,    51,    71,    72,    69
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -73,   -73,   -73,   -73,   -73,   -73,   185,   -73,   181,   -73,
     -73,   164,   -73,   -73,    26,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,   158,   -73,   -73,   -59,   -73,   -72,   -73,   -73,
     -64,   -73,   -71,   -73,    23,   -73,   -73,   163,   -73,   -73,
     -73,     4,   159,   -73,   -73
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     7,     5,    11,    12,    16,    17,    18,
      34,    35,    43,    88,    89,    90,    19,    36,    53,   152,
     171,   100,   101,   102,   178,   179,   193,   194,   174,   186,
     187,   197,   198,   103,   104,    20,    39,    40,    41,    42,
     160,   139,    82,    83,    84
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      92,    93,    94,    95,    96,    97,    98,    92,    93,    94,
      95,    96,    97,    98,     8,     9,    10,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,   172,    37,     3,    37,    72,    73,
      74,    75,    44,     4,    76,    77,    78,    79,    80,    49,
      85,    33,   195,   196,    86,    87,    38,   131,    38,    81,
     180,   181,   182,   183,   184,   185,    99,   120,   206,   173,
       6,   121,   207,    99,   188,   189,   190,   191,   192,    21,
      24,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,   214,    71,   221,   225,
     215,    26,   222,   226,   202,   203,   146,     8,     9,    10,
      13,    14,    15,   175,   176,   177,   199,   143,   200,   145,
      27,    28,    22,    23,    48,    46,    52,    47,    30,    31,
      32,    51,    33,    91,   105,   107,   106,   108,    54,   109,
     110,   111,   112,   113,   122,   114,   115,   151,   232,   116,
     245,   239,   117,   118,   119,   248,   159,   123,   124,   125,
     126,   127,   128,   129,   130,   133,   134,   135,   140,   136,
     137,   138,   144,   153,   161,   154,   141,   142,   155,   148,
     149,   150,   156,   157,   158,    99,   170,   162,   163,   164,
     165,   166,   167,   168,   169,   205,    25,    29,    45,   204,
     201,   208,    50,   209,   210,   211,   212,   213,     0,   216,
     217,   218,   219,   220,   223,   224,   228,     0,   227,   229,
     230,     0,     0,     0,   231,   233,   234,   235,   236,   237,
     238,   240,   241,   242,   243,   244,   246,   247,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   132,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   147
};

static const yytype_int16 yycheck[] =
{
      12,    13,    14,    15,    16,    17,    18,    12,    13,    14,
      15,    16,    17,    18,     3,     4,     5,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    27,    57,     0,    57,    57,    58,
      59,    60,    69,    53,    63,    64,    65,    66,    67,    69,
       6,    78,    34,    35,    10,    11,    78,    69,    78,    78,
      28,    29,    30,    31,    32,    33,    78,    71,    71,    62,
      68,    75,    75,    78,    22,    23,    24,    25,    26,    76,
      69,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    71,    52,    71,    71,
      75,    68,    75,    75,     8,     9,    61,     3,     4,     5,
      54,    55,    56,    19,    20,    21,    73,   113,    75,   115,
      78,    68,    76,    76,    74,    68,    54,    72,    80,    80,
      79,    70,    78,     7,    75,    72,    76,    72,    80,    72,
      72,    72,    72,    72,    78,    72,    72,   121,   207,    74,
     222,   215,    76,    76,    76,   226,   133,    78,    78,    78,
      78,    78,    78,    78,    74,    77,    80,    80,    73,    80,
      79,    78,    80,    70,    73,    70,    79,    79,    70,    80,
      80,    79,    70,    70,    78,    78,    54,    73,    73,    73,
      73,    73,    73,    73,    72,    71,    11,    16,    34,    76,
      79,    76,    39,    76,    76,    76,    76,    76,    -1,    76,
      76,    76,    76,    76,    76,    76,    73,    -1,    78,    78,
      78,    -1,    -1,    -1,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   116
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    82,    83,     0,    53,    85,    68,    84,     3,     4,
       5,    86,    87,    54,    55,    56,    88,    89,    90,    97,
     116,    76,    76,    76,    69,    87,    68,    78,    68,    89,
      80,    80,    79,    78,    91,    92,    98,    57,    78,   117,
     118,   119,   120,    93,    69,    92,    68,    72,    74,    69,
     118,    70,    54,    99,    80,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    57,    58,    59,    60,    63,    64,    65,    66,
      67,    78,   123,   124,   125,     6,    10,    11,    94,    95,
      96,     7,    12,    13,    14,    15,    16,    17,    18,    78,
     102,   103,   104,   114,   115,    75,    76,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    74,    76,    76,    76,
      71,    75,    78,    78,    78,    78,    78,    78,    78,    78,
      74,    69,   103,    77,    80,    80,    80,    79,    78,   122,
      73,    79,    79,   122,    80,   122,    61,   123,    80,    80,
      79,    95,   100,    70,    70,    70,    70,    70,    78,   115,
     121,    73,    73,    73,    73,    73,    73,    73,    73,    72,
      54,   101,    27,    62,   109,    19,    20,    21,   105,   106,
      28,    29,    30,    31,    32,    33,   110,   111,    22,    23,
      24,    25,    26,   107,   108,    34,    35,   112,   113,    73,
      75,    79,     8,     9,    76,    71,    71,    75,    76,    76,
      76,    76,    76,    76,    71,    75,    76,    76,    76,    76,
      76,    71,    75,    76,    76,    71,    75,    78,    73,    78,
      78,    80,   106,    80,    80,    80,    80,    80,    80,   111,
      80,    80,    80,    80,    80,   108,    80,    80,   113
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    83,    84,    82,    85,    85,    86,    86,    87,
      87,    87,    88,    88,    89,    89,    89,    90,    91,    91,
      93,    92,    94,    94,    95,    95,    96,    96,    98,    97,
      99,   100,   100,   101,   101,   102,   102,   103,   103,   104,
     104,   104,   104,   104,   104,   104,   105,   105,   106,   106,
     106,   107,   107,   108,   108,   108,   108,   108,   109,   109,
     109,   110,   110,   111,   111,   111,   111,   111,   111,   112,
     112,   113,   113,   114,   115,   115,   116,   117,   117,   118,
     118,   119,   119,   119,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   121,   121,   122,   122,   123,
     123,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   125,   125,   125,   125
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
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
       1,     5,     3,     5,     8,     7,     6,     6,     6,     6,
       6,     6,     6,     5,     6,     0,     3,     0,     1,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
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
#line 41 "asin.y" /* yacc.c:1646  */
    { begin_experiment(); }
#line 1484 "asin.c" /* yacc.c:1646  */
    break;

  case 3:
#line 45 "asin.y" /* yacc.c:1646  */
    { get_gconstants(); }
#line 1490 "asin.c" /* yacc.c:1646  */
    break;

  case 4:
#line 49 "asin.y" /* yacc.c:1646  */
    { end_experiment(); }
#line 1496 "asin.c" /* yacc.c:1646  */
    break;

  case 9:
#line 65 "asin.y" /* yacc.c:1646  */
    { insert_gconstants(BATCH, (int)(yyvsp[0].creal), ""); }
#line 1502 "asin.c" /* yacc.c:1646  */
    break;

  case 10:
#line 69 "asin.y" /* yacc.c:1646  */
    { insert_gconstants(THREADS, (int)(yyvsp[0].creal), ""); }
#line 1508 "asin.c" /* yacc.c:1646  */
    break;

  case 11:
#line 73 "asin.y" /* yacc.c:1646  */
    { insert_gconstants(LOG, 0, (yyvsp[0].ident)); }
#line 1514 "asin.c" /* yacc.c:1646  */
    break;

  case 14:
#line 84 "asin.y" /* yacc.c:1646  */
    { get_data(); }
#line 1520 "asin.c" /* yacc.c:1646  */
    break;

  case 15:
#line 88 "asin.y" /* yacc.c:1646  */
    { get_network(); /* end_network(); */ }
#line 1526 "asin.c" /* yacc.c:1646  */
    break;

  case 20:
#line 104 "asin.y" /* yacc.c:1646  */
    { int k = search_data((yyvsp[0].ident));
	 if (k < 0)  inser_name_data((yyvsp[0].ident));
	 else yyerror("Data name already exists");
       }
#line 1535 "asin.c" /* yacc.c:1646  */
    break;

  case 24:
#line 120 "asin.y" /* yacc.c:1646  */
    { inser_param_data((yyvsp[0].ident), NONE); }
#line 1541 "asin.c" /* yacc.c:1646  */
    break;

  case 25:
#line 124 "asin.y" /* yacc.c:1646  */
    { inser_param_data("", (yyvsp[0].aux));   }
#line 1547 "asin.c" /* yacc.c:1646  */
    break;

  case 26:
#line 128 "asin.y" /* yacc.c:1646  */
    { (yyval.aux) = ASCII;  }
#line 1553 "asin.c" /* yacc.c:1646  */
    break;

  case 27:
#line 129 "asin.y" /* yacc.c:1646  */
    { (yyval.aux) = BINARY; }
#line 1559 "asin.c" /* yacc.c:1646  */
    break;

  case 28:
#line 135 "asin.y" /* yacc.c:1646  */
    { insert_name_network((yyvsp[0].ident)); }
#line 1565 "asin.c" /* yacc.c:1646  */
    break;

  case 30:
#line 143 "asin.y" /* yacc.c:1646  */
    { int k = search_data ((yyvsp[-1].ident));
	 if (k < 0)
	   yyerror("Data name does not exist");
	 else inser_param_net_data(tr, k);
       }
#line 1575 "asin.c" /* yacc.c:1646  */
    break;

  case 33:
#line 158 "asin.y" /* yacc.c:1646  */
    { int k = search_data ((yyvsp[0].ident));
	 if (k < 0)
	   yyerror("Data name does not exist");
	 else inser_param_net_data(ts, k);
       }
#line 1585 "asin.c" /* yacc.c:1646  */
    break;

  case 34:
#line 166 "asin.y" /* yacc.c:1646  */
    { int k = search_data ((yyvsp[0].ident));
	 if (k < 0)
	   yyerror("Data name does not exist");
	 else inser_param_net_data(va, k);
       }
#line 1595 "asin.c" /* yacc.c:1646  */
    break;

  case 39:
#line 185 "asin.y" /* yacc.c:1646  */
    { int k = search_layer(-1, (yyvsp[0].ident));
	 if (k < 0) insert_name_layer((yyvsp[0].ident), FI);
	 else  yyerror("Layer name already exists in this network");
       }
#line 1604 "asin.c" /* yacc.c:1646  */
    break;

  case 40:
#line 192 "asin.y" /* yacc.c:1646  */
    { int k = search_layer(-1, (yyvsp[-3].ident));
	 if (k < 0) {
	   check_param_layer(1);
	   insert_name_layer((yyvsp[-3].ident), FO);
	 }
	 else yyerror("Layer name already exists in this network");

       }
#line 1617 "asin.c" /* yacc.c:1646  */
    break;

  case 41:
#line 203 "asin.y" /* yacc.c:1646  */
    { int k = search_layer(-1, (yyvsp[-3].ident));
	 if (k < 0) {
	   check_param_layer(3);
	   insert_name_layer((yyvsp[-3].ident), CI);
	 }
	 else yyerror("Layer name already exists in this network");

       }
#line 1630 "asin.c" /* yacc.c:1646  */
    break;

  case 42:
#line 214 "asin.y" /* yacc.c:1646  */
    { int k = search_layer(-1, (yyvsp[-3].ident));
	 if (k >= 0) 
	   yyerror("Layer name already exists in this network");
	 else if ((yyvsp[-1].aux) == TRUE) insert_name_layer((yyvsp[-3].ident), F);
	 else insert_name_layer((yyvsp[-3].ident), R);
       }
#line 1641 "asin.c" /* yacc.c:1646  */
    break;

  case 43:
#line 223 "asin.y" /* yacc.c:1646  */
    { int k = search_layer(-1, (yyvsp[-3].ident));
	 if (k >= 0)
	   yyerror("Layer name already exists in this network");
	 else {
	   check_param_layer(3);
	   insert_name_layer((yyvsp[-3].ident), C);
	 }
       }
#line 1654 "asin.c" /* yacc.c:1646  */
    break;

  case 44:
#line 234 "asin.y" /* yacc.c:1646  */
    { int k = search_layer(-1, (yyvsp[-3].ident));
	 if (k >= 0)
	   yyerror("Layer name already exists in this network");
	 else {
	   check_param_layer(2);
	   insert_name_layer((yyvsp[-3].ident), MP);
	 }
       }
#line 1667 "asin.c" /* yacc.c:1646  */
    break;

  case 45:
#line 245 "asin.y" /* yacc.c:1646  */
    { int k = search_layer(-1, (yyvsp[0].ident));
	 if (k >= 0) 
	   yyerror("Layer name already exists in this network");
	 else insert_name_layer((yyvsp[0].ident), CA);
       }
#line 1677 "asin.c" /* yacc.c:1646  */
    break;

  case 48:
#line 260 "asin.y" /* yacc.c:1646  */
    { insert_param_layer(1, CLASSIFICATION); }
#line 1683 "asin.c" /* yacc.c:1646  */
    break;

  case 49:
#line 264 "asin.y" /* yacc.c:1646  */
    { insert_param_layer(1, REGRESSION); }
#line 1689 "asin.c" /* yacc.c:1646  */
    break;

  case 50:
#line 268 "asin.y" /* yacc.c:1646  */
    { insert_param_layer(2, AUTOENCODER); }
#line 1695 "asin.c" /* yacc.c:1646  */
    break;

  case 53:
#line 279 "asin.y" /* yacc.c:1646  */
    { insert_param_layer(1, (int)(yyvsp[0].creal)); }
#line 1701 "asin.c" /* yacc.c:1646  */
    break;

  case 54:
#line 283 "asin.y" /* yacc.c:1646  */
    { insert_param_layer(2, (int)(yyvsp[0].creal)); }
#line 1707 "asin.c" /* yacc.c:1646  */
    break;

  case 55:
#line 287 "asin.y" /* yacc.c:1646  */
    { insert_param_layer(3, (int)(yyvsp[0].creal)); }
#line 1713 "asin.c" /* yacc.c:1646  */
    break;

  case 56:
#line 291 "asin.y" /* yacc.c:1646  */
    { insert_param_layer(4, (int)(yyvsp[0].creal)); }
#line 1719 "asin.c" /* yacc.c:1646  */
    break;

  case 57:
#line 295 "asin.y" /* yacc.c:1646  */
    { insert_param_layer(5, (int)(yyvsp[0].creal)); }
#line 1725 "asin.c" /* yacc.c:1646  */
    break;

  case 58:
#line 301 "asin.y" /* yacc.c:1646  */
    {
	 (yyval.aux) = FALSE;
	 insert_param_layer(1, 0);
       }
#line 1734 "asin.c" /* yacc.c:1646  */
    break;

  case 59:
#line 308 "asin.y" /* yacc.c:1646  */
    { 
         (yyval.aux) = FALSE;
	 insert_param_layer(1, 1);
       }
#line 1743 "asin.c" /* yacc.c:1646  */
    break;

  case 60:
#line 315 "asin.y" /* yacc.c:1646  */
    { 
         (yyval.aux) = TRUE;
	 insert_param_layer(1, (int)(yyvsp[0].creal));
       }
#line 1752 "asin.c" /* yacc.c:1646  */
    break;

  case 63:
#line 329 "asin.y" /* yacc.c:1646  */
    { insert_param_layer(1, (int)(yyvsp[0].creal)); }
#line 1758 "asin.c" /* yacc.c:1646  */
    break;

  case 64:
#line 333 "asin.y" /* yacc.c:1646  */
    { insert_param_layer(2, (int)(yyvsp[0].creal)); }
#line 1764 "asin.c" /* yacc.c:1646  */
    break;

  case 65:
#line 337 "asin.y" /* yacc.c:1646  */
    { insert_param_layer(3, (int)(yyvsp[0].creal)); }
#line 1770 "asin.c" /* yacc.c:1646  */
    break;

  case 66:
#line 341 "asin.y" /* yacc.c:1646  */
    { insert_param_layer(4, (int)(yyvsp[0].creal)); }
#line 1776 "asin.c" /* yacc.c:1646  */
    break;

  case 67:
#line 345 "asin.y" /* yacc.c:1646  */
    { insert_param_layer(5, (int)(yyvsp[0].creal)); }
#line 1782 "asin.c" /* yacc.c:1646  */
    break;

  case 68:
#line 349 "asin.y" /* yacc.c:1646  */
    { insert_param_layer(6, (int)(yyvsp[0].creal)); }
#line 1788 "asin.c" /* yacc.c:1646  */
    break;

  case 71:
#line 360 "asin.y" /* yacc.c:1646  */
    { insert_param_layer(1, (int)(yyvsp[0].creal)); }
#line 1794 "asin.c" /* yacc.c:1646  */
    break;

  case 72:
#line 364 "asin.y" /* yacc.c:1646  */
    { insert_param_layer(2, (int)(yyvsp[0].creal)); }
#line 1800 "asin.c" /* yacc.c:1646  */
    break;

  case 73:
#line 370 "asin.y" /* yacc.c:1646  */
    { insert_link((yyvsp[-2].aux),(yyvsp[0].aux)); }
#line 1806 "asin.c" /* yacc.c:1646  */
    break;

  case 74:
#line 376 "asin.y" /* yacc.c:1646  */
    { (yyval.aux) = search_states((yyvsp[-2].ident), (yyvsp[0].ident)); }
#line 1812 "asin.c" /* yacc.c:1646  */
    break;

  case 75:
#line 380 "asin.y" /* yacc.c:1646  */
    { (yyval.aux) = search_states("", (yyvsp[0].ident));  }
#line 1818 "asin.c" /* yacc.c:1646  */
    break;

  case 81:
#line 401 "asin.y" /* yacc.c:1646  */
    { int k2, k1 =  search_network ((yyvsp[-4].ident));
	 if (k1 >= 0) {
           k2 = search_layer(k1, (yyvsp[-2].ident));
	   if (k2 >= 0)
	     get_amendment(LAYER, k2, (yyvsp[0].ident));
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       }
#line 1833 "asin.c" /* yacc.c:1646  */
    break;

  case 82:
#line 414 "asin.y" /* yacc.c:1646  */
    { int k = search_network ((yyvsp[-2].ident));
	 if (k >= 0)  get_amendment(NETWORK, k, (yyvsp[0].ident));
	 else yyerror("Network name does not exist");
       }
#line 1842 "asin.c" /* yacc.c:1646  */
    break;

  case 83:
#line 421 "asin.y" /* yacc.c:1646  */
    { int k = search_data ((yyvsp[-4].ident));
	 if (k >= 0)  get_amendment_data(k, (int)(yyvsp[0].creal));
	 else yyerror("Data or network name does not exist");
       }
#line 1851 "asin.c" /* yacc.c:1646  */
    break;

  case 84:
#line 430 "asin.y" /* yacc.c:1646  */
    { int k2, k1 =  search_network ((yyvsp[-7].ident));
	 if (k1 >= 0) {
           k2 = search_layer(k1, (yyvsp[-5].ident));
	   if (k2 >= 0) 
	     get_printkernels(k1, k2, (yyvsp[-1].ident));
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       }
#line 1866 "asin.c" /* yacc.c:1646  */
    break;

  case 85:
#line 443 "asin.y" /* yacc.c:1646  */
    { get_train((int)(yyvsp[-4].creal), (int)(yyvsp[-2].creal), (yyvsp[-1].aux)); }
#line 1872 "asin.c" /* yacc.c:1646  */
    break;

  case 86:
#line 447 "asin.y" /* yacc.c:1646  */
    { int k = search_network ((yyvsp[-5].ident));
	 if (k >= 0)  get_net_train(k, (int)(yyvsp[-1].creal));
	 else yyerror("Network name does not exist");
       }
#line 1881 "asin.c" /* yacc.c:1646  */
    break;

  case 87:
#line 454 "asin.y" /* yacc.c:1646  */
    { int k2, k1 = search_network ((yyvsp[-5].ident));
	 if (k1 >= 0)  
	   if (strlen((yyvsp[-1].ident)) > 0) {
	     k2 = search_data ((yyvsp[-1].ident));
	     if (k2 >= 0) get_net_test(k1, k2);
	     else yyerror("Data name does not exist");
	   }
	   else  get_net_test(k1,-1);
	 else yyerror("Network name does not exist");
       }
#line 1896 "asin.c" /* yacc.c:1646  */
    break;

  case 88:
#line 467 "asin.y" /* yacc.c:1646  */
    { int k = search_network ((yyvsp[-5].ident));
	 if (k < 0)
	   yyerror("Network name does not exist");
	 else get_save(k, (yyvsp[-1].ident));
       }
#line 1906 "asin.c" /* yacc.c:1646  */
    break;

  case 89:
#line 475 "asin.y" /* yacc.c:1646  */
    { int k = search_network ((yyvsp[-5].ident));
	 if (k < 0)
	   yyerror("Network name does not exist");
	 else get_load(k, (yyvsp[-1].ident));
       }
#line 1916 "asin.c" /* yacc.c:1646  */
    break;

  case 90:
#line 483 "asin.y" /* yacc.c:1646  */
    { int k = search_network ((yyvsp[-5].ident));
	 if (k < 0)
	   yyerror("Network name does not exist");
	 else get_testout(k, (yyvsp[-1].ident));
       }
#line 1926 "asin.c" /* yacc.c:1646  */
    break;

  case 91:
#line 491 "asin.y" /* yacc.c:1646  */
    { int k2, k1 = search_data ((yyvsp[-5].ident));
	 if (k1 >= 0) 
	   if (strlen((yyvsp[-1].ident)) > 0) {
	     k2 = search_data ((yyvsp[-1].ident));
	     if (k2 >= 0) get_zscore(k1,k2);
	     else yyerror("Data name does not exist");
	   }
	   else  get_zscore(k1,-1);
	 else yyerror("Data name does not exist");
       }
#line 1941 "asin.c" /* yacc.c:1646  */
    break;

  case 92:
#line 504 "asin.y" /* yacc.c:1646  */
    { int k2, k1 = search_data ((yyvsp[-5].ident));
	 if (k1 >= 0) 
	   if (strlen((yyvsp[-1].ident)) > 0) {
	     k2 = search_data ((yyvsp[-1].ident));
	     if (k2 >= 0) get_center(k1,k2);
	     else yyerror("Data name does not exist");
	   }
	   else  get_center(k1,-1);
	 else yyerror("Data name does not exist");
       }
#line 1956 "asin.c" /* yacc.c:1646  */
    break;

  case 93:
#line 517 "asin.y" /* yacc.c:1646  */
    { int k = search_data ((yyvsp[-4].ident));
	 if (k >= 0) get_yuv(k);
	 else yyerror("Data name does not exist");
       }
#line 1965 "asin.c" /* yacc.c:1646  */
    break;

  case 94:
#line 524 "asin.y" /* yacc.c:1646  */
    { int k = search_data ((yyvsp[-5].ident));
	 if (k >= 0) get_div(k, (yyvsp[-1].creal));
	 else yyerror("Data name does not exist");
       }
#line 1974 "asin.c" /* yacc.c:1646  */
    break;

  case 95:
#line 533 "asin.y" /* yacc.c:1646  */
    { (yyval.aux) = insert_net_stack(-1, ""); }
#line 1980 "asin.c" /* yacc.c:1646  */
    break;

  case 96:
#line 537 "asin.y" /* yacc.c:1646  */
    { (yyval.aux) = insert_net_stack((yyvsp[-2].aux), (yyvsp[0].ident)); }
#line 1986 "asin.c" /* yacc.c:1646  */
    break;

  case 97:
#line 542 "asin.y" /* yacc.c:1646  */
    { (yyval.ident) = ""; }
#line 1992 "asin.c" /* yacc.c:1646  */
    break;

  case 98:
#line 543 "asin.y" /* yacc.c:1646  */
    { (yyval.ident) = (yyvsp[0].ident); }
#line 1998 "asin.c" /* yacc.c:1646  */
    break;

  case 99:
#line 549 "asin.y" /* yacc.c:1646  */
    { (yyval.ident) = get_amend_param_ctr((yyvsp[-2].aux), (yyvsp[0].creal)); }
#line 2004 "asin.c" /* yacc.c:1646  */
    break;

  case 100:
#line 553 "asin.y" /* yacc.c:1646  */
    { (yyval.ident) = get_amend_param_cte((yyvsp[-2].aux), (int)(yyvsp[0].creal)); }
#line 2010 "asin.c" /* yacc.c:1646  */
    break;

  case 101:
#line 557 "asin.y" /* yacc.c:1646  */
    { (yyval.aux) = mu;         }
#line 2016 "asin.c" /* yacc.c:1646  */
    break;

  case 102:
#line 558 "asin.y" /* yacc.c:1646  */
    { (yyval.aux) = mmu;        }
#line 2022 "asin.c" /* yacc.c:1646  */
    break;

  case 103:
#line 559 "asin.y" /* yacc.c:1646  */
    { (yyval.aux) = l2;         }
#line 2028 "asin.c" /* yacc.c:1646  */
    break;

  case 104:
#line 560 "asin.y" /* yacc.c:1646  */
    { (yyval.aux) = l1;         }
#line 2034 "asin.c" /* yacc.c:1646  */
    break;

  case 105:
#line 561 "asin.y" /* yacc.c:1646  */
    { (yyval.aux) = maxn;       }
#line 2040 "asin.c" /* yacc.c:1646  */
    break;

  case 106:
#line 562 "asin.y" /* yacc.c:1646  */
    { (yyval.aux) = drop;       }
#line 2046 "asin.c" /* yacc.c:1646  */
    break;

  case 107:
#line 563 "asin.y" /* yacc.c:1646  */
    { (yyval.aux) = noiser;     }
#line 2052 "asin.c" /* yacc.c:1646  */
    break;

  case 108:
#line 564 "asin.y" /* yacc.c:1646  */
    { (yyval.aux) = noisesd;    }
#line 2058 "asin.c" /* yacc.c:1646  */
    break;

  case 109:
#line 565 "asin.y" /* yacc.c:1646  */
    { (yyval.aux) = brightness; }
#line 2064 "asin.c" /* yacc.c:1646  */
    break;

  case 110:
#line 566 "asin.y" /* yacc.c:1646  */
    { (yyval.aux) = contrast;   }
#line 2070 "asin.c" /* yacc.c:1646  */
    break;

  case 111:
#line 567 "asin.y" /* yacc.c:1646  */
    { (yyval.aux) = lambda;     }
#line 2076 "asin.c" /* yacc.c:1646  */
    break;

  case 112:
#line 568 "asin.y" /* yacc.c:1646  */
    { (yyval.aux) = noiseb;     }
#line 2082 "asin.c" /* yacc.c:1646  */
    break;

  case 113:
#line 572 "asin.y" /* yacc.c:1646  */
    { (yyval.aux) = bn;         }
#line 2088 "asin.c" /* yacc.c:1646  */
    break;

  case 114:
#line 573 "asin.y" /* yacc.c:1646  */
    { (yyval.aux) = act;        }
#line 2094 "asin.c" /* yacc.c:1646  */
    break;

  case 115:
#line 574 "asin.y" /* yacc.c:1646  */
    { (yyval.aux) = shift;      }
#line 2100 "asin.c" /* yacc.c:1646  */
    break;

  case 116:
#line 575 "asin.y" /* yacc.c:1646  */
    { (yyval.aux) = flip;       }
#line 2106 "asin.c" /* yacc.c:1646  */
    break;


#line 2110 "asin.c" /* yacc.c:1646  */
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
#line 578 "asin.y" /* yacc.c:1906  */

/*****************************************************************************/
/*****************************************************************************/
