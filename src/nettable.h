/*****************************************************************************/
/**  Header of "nettable".                          <jmbenedi@prhlt.upv.es> **/
/*****************************************************************************/
#ifndef _LIBTDS_H
#define _LIBTDS_H
/********************************************************* General constants */
#define MaxTdM 1000         /* Maximum number of inputs in table of macros   */
#define MaxMem 1000         /* Maximum number of instructions                */
#define MaxTdN 1000         /* Maximum number of inputs in table of networks */
#define MaxTdL 1000         /* Maximum number of inputs in table of layers   */
#define MaxTdD 1000         /* Maximum number of inputs in table of data     */
#define MaxPar   7          /* Maximum number of parameters per layer        */
#define MaxSizeLin 1000     /* Maximum size lines                            */

#define FORMAL  0
#define ACTUAL  1

#define TRUE  1
#define FALSE 0

#define F    1
#define FI   2
#define FO   3
#define C    4
#define CI   5
#define MP   6
#define CAT  7
#define ADD  8
#define R    9
#define O   10

#define mu          0
#define mmu         1
#define l2          2   
#define l1          3
#define maxn        4
#define drop        5
#define noiser      6
#define noisesd     7
#define brightness  8
#define contrast    9
#define lambda     10
#define noiseb     11
#define advf       12
#define bn         13
#define act        14
#define shift      15
#define flip       16
#define adv        17
#define cropmode   18
#define balance    19
#define trainable  20

#define printkernels    0
#define change          1
#define copy            2
#define train           3
#define save            4
#define load            5
#define testout         6
#define forward         7
#define backward        8
#define resetstats      9
#define printerrors    10
#define reseterrors    11
#define trainmode      12
#define testmode       13
#define update         14
#define test           15
#define evaluate       16
#define zscore         17
#define center         18
#define yuv            19
#define maxmin         20
#define shuffle        21
#define next           22
#define multiplication 23
#define division       24
#define addition       25
#define subtraction    26
#define set            27
#define store          28
#define getstats       29

#define NONE   0
#define TR     1
#define TS     2
#define VA     3

#define BATCH    0
#define THREADS  1
#define SEED     2
#define DEVICE   3
#define CUDNN    4
#define CUBLAS   5
#define LOG      6
#define CLASSIFICATION 0
#define REGRESSION     1
#define AUTOENCODER    2
#define MAX            3
#define MIN            4
#define MAXLOG         5
#define MINLOG         6

#define NONE        0
#define FILES       1
#define GENERATED   2
#define CREADATA    3
#define ASCII       4
#define BINARY      5
#define GAUSS       6
#define UNIFORM     7
#define ONES        8
#define ZEROS       9
#define ONESHOT    10

#define NETWORK 0
#define LAYER   1
#define DATA    2

#define REAL   0
#define BIN    1
#define INT    2
#define TARGET 3
#define SAMPLE 4

#define  AND             0
#define  OR              1
#define  EQUAL           2
#define  NOTEQUAL        3
#define  GREAT           4
#define  GREATEQ         5
#define  LESS            6
#define  LESSEQ          7
#define  ADDITION        8
#define  SUBTRACTION     9
#define  MULTIPLICATION 10
#define  DIVISION       11
#define  MODULUS        12
#define  EXPONET        13
#define  NOT            14
#define  LOGARITHM      15
#define  EXPONENTIAL    16
#define  SQUARE         17
#define  INNERMULT      18
#define  OUTERMULT      19
#define  SIGMOID        20
#define  TANH           21
#define  RELU           22
/****************************************************** Auxiliary structures */
typedef struct symbol { /**************************************** Name Table */
  char *ident;
  struct symbol *succ;
} typesymbol;
typedef typesymbol *ptsymbol;
typedef struct expre { /******************************************************/
  ptsymbol psymbol;
  int     reftemp; 
  } EXPRE;
typedef struct aux4 { /*******************************************************/
  EXPRE ini;
  EXPRE fin;
  int   aux; 
  } AUX4;
typedef struct rango { /******************************************************/
  AUX4 row;
  AUX4 col;
  } RANGO;
typedef struct tuple { /******************************************************/
  int ref;
  int typ; 
  } TUPLE;
typedef struct tddata { /*************************** Elements of data table  */
  char *name;
  int   level;
  int   type;
  int   filetype;
  char *namefile;
  int   gentype;
  int   numnodes;
  int   pos;
  int   nrows;
  int   ncolsample;  
  int   ncoltarget;
  } TDDATA;
typedef struct tdnet { /************************** Elements of network table */
  char *name;
  int   reftr;
  int   typtr;
  int   refts;
  int   typts;
  int   refva;
  int   typva;
  int   belem;                   
  int   eelem;                   
  int   start;                   
  }TDNET;
typedef struct node {/********************************************************/
  int  refnet;
  int   reflay; 
  struct node *succ;
  } typenode;
typedef typenode *pnode;
typedef struct tdlay  {/**************************** Elements of layer table */
  char *name;
  int   type;  
  int   refnet;
  int   ninit;
  int   root;
  int   visit;
  int   visit2;
  int   cte1;
  int   cte2;
  int   cte3;
  int   cte4;
  int   cte5;
  int   cte6;
  int   cte7;
  int   nsucc;
  int   nprev;
  pnode succ;    
  pnode prev;    
  }TDLAY;
typedef struct expfor { /*****************************************************/
  EXPRE expre1;
  EXPRE expre2; 
  } EXPFOR;
typedef struct param { /**************************************** Remplace ****/
  char *param;
  struct param *succ;
  } typeparam;
typedef typeparam *pparam;
typedef struct tdmacro  { /* Elements of macro table */
  char  *name;
  int    pini;  
  int    pfin;
  int    npfor;
  int    npact;
  pparam fpf;    
  pparam lpf;
  pparam fpa;    
  pparam lpa;
  }TDMACRO;
/************************************** External variables defined in the AL */
//extern int yyleng;
extern FILE *yyin;
extern int   yylineno;
extern char *yytext;
extern int yyparse (void);
extern int yylex(void);
/************************************** External variables defined in the AS */
extern int verbosity;
extern int numErrores;
extern int pstv;
/****************************************************** Headers of functions */
void  insert_gconstants (int ref, int cte, char *filename) ;
void  get_gconstants() ;

int   search_data (char *named) ;
void  inser_name_data (char *named) ;
void  inser_param_data (int cod, char *namef, int cte1, int cte2, int cte3) ;
void  check_param_data (int cod) ;
void  get_data() ;
int   inser_new_name_data (char *named) ;

void  inser_param_net_data (int cod, int ref) ;
void  get_net_data() ;

int   search_layer (int refnet, char *layname) ;
void  insert_name_layer (char *layname, int type) ;
void  insert_param_layer(int cod, int val) ;
void  check_param_layer (int n) ;
void  get_net_layers (int n) ;

void  insert_name_network (char *name) ;
int   search_network (char *named) ;
void  get_network() ;

void  insert_link (int a, int b) ;
int   search_states(char *netname, char *layname) ;
void  get_net_links(int n, int l) ;

void get_amendment(int type, int ref, int cod, EXPRE value) ;
void get_echo(char *aux) ;
void get_if(EXPRE exp1) ;
void get_else() ;
void get_endif() ;
void get_for(ptsymbol s, EXPRE exp1, EXPRE exp2, EXPRE exp3) ;
void get_endfor() ;

void get_com_lay_file(int refn, int refl, int cod, char *nfil) ;
void get_com_lay_datlay (int refnd, int refld, int cod, int refns, int refls) ;
void get_com_lay_copy(int ref1, int ref2, int cod, char *aux) ;

void get_com_net_void (int ref, int cod) ;
void get_com_net_file (int ref, int cod, char *nfil) ;
void get_com_net_dat(int ref1, int cod, int ref2) ;
void get_com_net_exp (int ref, int cod, EXPRE val) ;

void get_com_data_void_rank(int ref, RANGO r, int cod) ;
void get_com_data_void(int ref, int cod) ;
void get_com_data_file(int ref, int cod, char *valor) ;
void get_com_data_dat(int ref1, int cod, int ref2) ;
void get_com_data_exp_rank(int ref, RANGO r, int cod, EXPRE val) ;
void get_com_data_exp(int ref, int cod, EXPRE val) ;
void get_com_data_copy_rank(int ref, RANGO r, int cod, char *aux) ;
void get_com_data_copy (int ref, int cod, char *aux) ;

void get_init_cte(int ref, float val) ;
void get_init_elem(int ref, int dat, EXPRE f, EXPRE c) ;
void get_init_amend(int type, int ref, int lay, int cod) ;
void get_exp_unary(int ref, int aux, EXPRE val) ;
void get_functions(int ref, int aux, EXPRE val) ;
void get_exp_log(int ref, EXPRE op1, int op, EXPRE op2) ;
void get_exp_eq (int ref, EXPRE op1, int op, EXPRE op2) ;
void get_exp_rel(int ref, EXPRE op1, int op, EXPRE op2) ;
void get_exp_add(int ref, EXPRE op1, int op, EXPRE op2) ;
void get_exp_mul(int ref, EXPRE op1, int op, EXPRE op2) ;
void get_exp_eqvar(ptsymbol s, EXPRE op) ;
void get_exp_eqelem(int ref, EXPRE f, EXPRE c, EXPRE der) ;

void strexpre(char *p, EXPRE val) ;
int  cr_var_temp_cte_1() ; 
int  cr_var_temp() ;
void create_list_names() ;
void show_list_names () ;
ptsymbol insert_name(char *x) ;
ptsymbol search_name (char *x) ;

void yyerror(const char *msg) ;
void emit (char *str) ;
void dump_file() ;
void begin_experiment() ;
void end_experiment() ;
int  netparser (char *nfich) ;
/*****************************************************************************/
#endif  /* _LIBTDS_H */
/*****************************************************************************/
