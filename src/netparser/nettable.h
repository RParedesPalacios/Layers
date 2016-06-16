/*****************************************************************************/
/**  Header of "nettable".                          <jmbenedi@prhlt.upv.es> **/
/*****************************************************************************/
#ifndef _LIBTDS_H
#define _LIBTDS_H
/********************************************************* General constants */
#define TRUE  1
#define FALSE 0

#define F  1
#define FI 2
#define FO 3
#define C  4
#define CI 5
#define MP 6
#define CA 7
#define R  8

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
#define bn         10
#define act        11
#define shift      12
#define flip       13
#define balance    14

#define tr  0
#define ts  1
#define va  2

#define BATCH    0
#define THREADS  1
#define LOG      2

#define CLASSIFICATION 0
#define REGRESSION     1
#define AUTOENCODER    2

#define NONE   0
#define ASCII  1
#define BINARY 2

#define NETWORK 0
#define LAYER   1
#define DATA    2
/************************************** External variables defined in the AL */
extern FILE *yyin;
extern int   yylineno;
extern int   yyleng;
extern char *yytext;
/************************************** External variables defined in the AS */
extern int verbosity;
extern int numErrores;
/****************************************************** Headers of functions */
void yyerror(const char * msg) ;
void emit (char *str) ;
void dump_file() ;
void end_experiment() ;
void end_network() ;

void insert_gconstants (int ref, int cte1, char *filename) ;
void inser_name_data (char *named) ;
void inser_param_data (char *namef, int ft) ;
void insert_name_network (char *name) ;
void inser_param_net_data (int cod, int ref) ;
void insert_name_layer (char *layname, int type) ;
void insert_param_layer(int cod, int val) ;
void insert_link (int a, int b) ;
int  insert_net_stack (int numl, char *namel) ;

void check_param_layer (int n) ;
int  search_data (char *named) ;
int  search_layer (int refnet, char *layname) ;
int  search_network (char *named) ;
int  search_states(char *netname, char *layname) ;

void  get_gconstants() ;
void  get_data() ;
void  get_net_data(int n) ;
void  get_net_layers (int n) ;
void  get_net_links(int n, int l) ;
void  get_network() ;
void  get_amendment(int type, int ref, char *aux) ;
void  get_amendment_data(int ref, int aux) ;
char *get_amend_param_ctr(int param, float value) ;
char *get_amend_param_cte(int param, int value) ;
void  get_train (int par1, int par2, int ref) ;
void  get_net_train (int refn, int par) ;
void  get_printkernels (int refn, int refl, char *aux) ;
void  get_save (int ref, char *aux) ;
void  get_load (int ref, char *aux) ;
void  get_testout (int ref, char *aux) ;
void  get_zscore (int ref1, int ref2) ;
void  get_center (int ref1, int ref2) ;
void  get_yuv (int ref1) ;
void  get_div (int ref1, float aux) ;
/*****************************************************************************/
#endif  /* _LIBTDS_H */
/*****************************************************************************/
