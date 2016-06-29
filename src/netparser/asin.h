/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

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
    BCB_ = 322,
    ECB_ = 323,
    BSB_ = 324,
    ESB_ = 325,
    BRB_ = 326,
    ERB_ = 327,
    PER_ = 328,
    COM_ = 329,
    EQ_ = 330,
    RAR_ = 331,
    id_ = 332,
    nfile_ = 333,
    cte_ = 334,
    ctr_ = 335
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 10 "asin.y" /* yacc.c:1909  */
 /********************************************************************/
  char*   ident;                      /* for the "identifier" terminal       */
  int     cent;                       /* for the "integer constant" terminal */
  float   creal;                      /* for the "real constant" terminal    */
  int     aux;

#line 142 "asin.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_ASIN_H_INCLUDED  */
