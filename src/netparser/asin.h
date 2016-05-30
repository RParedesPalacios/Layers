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
     BCB_ = 315,
     ECB_ = 316,
     BSB_ = 317,
     ESB_ = 318,
     BRB_ = 319,
     ERB_ = 320,
     PER_ = 321,
     COM_ = 322,
     EQ_ = 323,
     RAR_ = 324,
     id_ = 325,
     nfile_ = 326,
     cte_ = 327,
     ctr_ = 328
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 10 "asin.y"
 /********************************************************************/
  char*   ident;                      /* for the "identifier" terminal       */
  int     cent;                       /* for the "integer constant" terminal */
  float   creal;                      /* for the "real constant" terminal    */
  int     aux;



/* Line 2068 of yacc.c  */
#line 132 "asin.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


