/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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
     local_ = 324,
     load_ = 325,
     testout_ = 326,
     center_ = 327,
     div_ = 328,
     test_ = 329,
     add_ = 330,
     sub_ = 331,
     mul_ = 332,
     maxmin_ = 333,
     store_ = 334,
     BCB_ = 335,
     ECB_ = 336,
     BSB_ = 337,
     ESB_ = 338,
     BRB_ = 339,
     ERB_ = 340,
     PER_ = 341,
     COM_ = 342,
     EQ_ = 343,
     RAR_ = 344,
     id_ = 345,
     nfile_ = 346,
     cte_ = 347
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 10 "asin.y"
 /********************************************************************/
  char*   ident;                      /* for the "identifier" terminal       */
  float   creal;                      /* for the "real constant" terminal    */
  int     aux;



/* Line 2068 of yacc.c  */
#line 150 "asin.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


