/*****************************************************************************/
/**  Header of "nettable".                          <jmbenedi@prhlt.upv.es> **/
/*****************************************************************************/
#ifndef _LIBTDS_H
#define _LIBTDS_H
/********************************************************* General constants */
#define TRUE  1
#define FALSE 0

#define F   1
#define FI  2
#define FO  3
#define C   4
#define CI  5
#define MP  6
#define CAT 7
#define ADD 8
#define R   9

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
#define balance    18

#define tr  0
#define ts  1
#define va  2

#define BATCH    0
#define THREADS  1
#define LOG      2
#define SEED     3
#define GPU      4

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
/* typedef size_t yy_size_t; */
/* extern yy_size_t yyleng;  */
extern int yyleng;
extern FILE *yyin;
extern int   yylineno;
extern char *yytext;
extern int yyparse (void);
extern int yylex(void);
/************************************** External variables defined in the AS */
extern int verbosity;
extern int numErrores;
/****************************************************** Headers of functions */
void yyerror(const char * msg) ;
int  netparser (char *nfich) ;
void emit (char *str) ;
void dump_file() ;
void begin_experiment() ;
void end_experiment() ;

void insert_gconstants (int ref, int cte, char *filename) ;
void inser_name_data (char *named) ;
void inser_param_data (char *namef, int cte1, int cte2) ;
void insert_name_network (char *name) ;
void inser_param_net_data (int cod, int ref) ;
void insert_name_layer (char *layname, int type) ;
void insert_param_layer(int cod, int val) ;
void insert_link (int a, int b) ;
int  insert_net_stack (int numl, int refnet) ;

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
void  get_amendment_onlynet(int ref, int aux) ;
void  get_amendment_data(int ref, int aux) ;
char *get_amend_param_ctr(int param, float value) ;
char *get_amend_param_cte(int param, int value) ;
void  get_printkernels (int refn, int refl, char *aux) ;
void  get_copy (int refnd, int refld, int refns, int refls) ;
void  get_train (int par1, int par2, int par3, int ref) ;
void  get_net_train (int refn, int par) ;
void  get_net_test (int refn, int ref2) ;
void  get_net_evaluate (int ref1, int ref2)  ;
void  get_save (int ref, char *aux) ;
void  get_load (int ref, char *aux) ;
void  get_testout (int ref, char *aux) ;
void  get_zscore (int ref1, int ref2) ;
void  get_center (int ref1, int ref2) ;
void  get_yuv (int ref1) ;
void  get_div (int ref1, float aux) ;
void  get_add (int ref1, float aux) ;
void  get_sub (int ref1, float aux) ;
void  get_mul (int ref1, float aux) ;
void  get_maxmin (int ref1) ;
void  get_store (int ref1, char *aux) ;
/*****************************************************************************/
#endif  /* _LIBTDS_H */
/*****************************************************************************/
