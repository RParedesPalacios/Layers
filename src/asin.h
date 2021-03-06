/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 10 "asin.y" /* yacc.c:1909  */
 /********************************************************************/
  char*   ident;                      /* for the "identifier" terminal       */
  float   creal;                      /* for the "real constant" terminal    */
  int     aux;                        /* For non-terminals with 1 attributes */
  TUPLE   aux2;                       /* For non-terminals with 2 attributes */
  AUX4    aux4;                       /* For non-terminals with 4 attributes */
  RANGO   rango;                      /* For non-terminals with rank         */
  EXPRE   expre;                      /* For non-terminal expression         */
  EXPFOR  expfor;                     /* For two exp of FOR                  */

#line 230 "asin.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_ASIN_H_INCLUDED  */
