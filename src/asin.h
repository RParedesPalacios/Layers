/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
/* Line 1529 of yacc.c.  */
#line 360 "asin.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

