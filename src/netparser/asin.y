%{
/*****************************************************************************/
/**  Syntactic-semantic analyzer, 2016.             <jmbenedi@prhlt.upv.es> **/
/*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nettable.h"
%}
%union { /********************************************************************/
  char*   ident;                      /* for the "identifier" terminal       */
  int     cent;                       /* for the "integer constant" terminal */
  float   creal;                      /* for the "real constant" terminal    */
  int     aux;
} /***************************************************************************/
%token
/**************************************************************** Parameters */
 batch_  threads_  log_   
 filename_  tr_  ts_  va_  ascii_  binary_
 F_  FI_  FO_  C_  CI_  MP_  CA_  
 classification_  regression_  autoencoder_
 nz_  nr_  nc_  cr_  cc_  numnodes_ 
 nk_  kr_  kc_  rpad_  cpad_ stride_
 sizer_  sizec_  
 mu_  mmu_  drop_  l2_  l1_  maxn_  act_  noiser_  noisesd_  lambda_
 shift_  flip_  brightness_  contrast_  bn_  balance_
/*****************************************************************  Keywords */
 const_  data_  network_  script_  train_  save_  zscore_  yuv_  printkernels_
 local_  load_  testout_  center_  div_
/****************************************************************  operators */
 BCB_  ECB_  BSB_  ESB_  BRB_  ERB_  PER_  COM_  EQ_  RAR_
/**************************************************** tokens with attributes */
%token<ident> id_  nfile_
%token<cent>  cte_
%token<creal> ctr_
/********************************************** nonterminals with attributes */
%type<aux>   filetype  f_param  name_layer  param_ctr  param_cte  rest_train
%type<ident> other_data  parameter
/*****************************************************************************/
%%
/*****************************************************************************/
experiment: 
       { begin_experiment(); }

         def_constants 

       { get_gconstants(); }

         list_definitions

       { end_experiment(); }
       ;
/*****************************************************************************/
def_constants      
       : /* cadena vacia */
       | const_  BCB_  list_constants  ECB_
       ;
/*****************************************************************************/
list_constants     
       : list_constants  def_const 
       | def_const
       ;
/*****************************************************************************/
def_const
       : batch_   EQ_  cte_  

       { insert_gconstants(BATCH, $3, ""); }

       | threads_ EQ_  cte_  

       { insert_gconstants(THREADS, $3, ""); }

       | log_  EQ_  nfile_

       { insert_gconstants(LOG, 0, $3); }
       ;
/*****************************************************************************/
list_definitions
       : list_definitions  definition 
       | definition
       ;
/*****************************************************************************/
definition
       : def_data     

       { get_data(); }

       | def_network

       { get_network(); end_network(); }

       | def_script
       ; 
/*****************************************************************************/
def_data 
       : data_  BCB_  list_data  ECB_
       ;
/*****************************************************************************/
list_data
       : list_data  data
       | data
       ;
/*****************************************************************************/
data   : id_ 

       { int k = search_data($1);
	 if (k < 0)  inser_name_data($1);
	 else yyerror("Data name already exists");
       }

         BSB_  param_data  ESB_
       ;
/*****************************************************************************/
param_data
       : param_data  COM_  def_param 
       | def_param
       ;
/*****************************************************************************/
def_param          
       : filename_  EQ_  nfile_

       { inser_param_data($3, NONE); }

       | filetype 

       { inser_param_data("", $1);   }
       ;
/*****************************************************************************/
filetype
       : ascii_      { $$ = ASCII;  }
       | binary_     { $$ = BINARY; }
       ;
/*****************************************************************************/
def_network
       : network_  id_  

       { insert_name_network($2); }

         BCB_  net_data  list_statements  ECB_
       ;
/*****************************************************************************/
net_data           
       : data_  tr_  id_  rest_data

       { int k = search_data ($3);
	 if (k < 0)
	   yyerror("Data name does not exist");
	 else inser_param_net_data(tr, k);
       }
       ;
/*****************************************************************************/
rest_data          
       : /* cadena vacia */
       | rest_data  net_defdata
       ;
/*****************************************************************************/
net_defdata        
       : data_  ts_  id_

       { int k = search_data ($3);
	 if (k < 0)
	   yyerror("Data name does not exist");
	 else inser_param_net_data(ts, k);
       }

       | data_  va_  id_ 

       { int k = search_data ($3);
	 if (k < 0)
	   yyerror("Data name does not exist");
	 else inser_param_net_data(va, k);
       }
       ;
/*****************************************************************************/
list_statements
       : list_statements  statement
       | statement 
       ;
/*****************************************************************************/
statement
       : layer        
       | edge
       ;
/*****************************************************************************/
layer  : FI_  id_  

       { int k = search_layer(-1, $2);
	 if (k < 0) insert_name_layer($2, FI);
	 else  yyerror("Layer name already exists in this network");
       }

       | FO_  id_  BSB_  fo_lparam  ESB_

       { int k = search_layer(-1, $2);
	 if (k < 0) {
	   check_param_layer(1);
	   insert_name_layer($2, FO);
	 }
	 else yyerror("Layer name already exists in this network");

       }

       | CI_  id_  BSB_  ci_lparam  ESB_

       { int k = search_layer(-1, $2);
	 if (k < 0) {
	   check_param_layer(3);
	   insert_name_layer($2, CI);
	 }
	 else yyerror("Layer name already exists in this network");

       }

       | F_  id_  BSB_  f_param  ESB_

       { int k = search_layer(-1, $2);
	 if (k >= 0) 
	   yyerror("Layer name already exists in this network");
	 else if ($4 == TRUE) insert_name_layer($2, F);
	 else insert_name_layer($2, R);
       }

       | C_  id_  BSB_  c_lparam  ESB_

       { int k = search_layer(-1, $2);
	 if (k >= 0)
	   yyerror("Layer name already exists in this network");
	 else {
	   check_param_layer(3);
	   insert_name_layer($2, C);
	 }
       }

       | MP_  id_  BSB_  mp_lparam  ESB_ 

       { int k = search_layer(-1, $2);
	 if (k >= 0)
	   yyerror("Layer name already exists in this network");
	 else {
	   check_param_layer(2);
	   insert_name_layer($2, MP);
	 }
       }

       | CA_  id_ 

       { int k = search_layer(-1, $2);
	 if (k >= 0) 
	   yyerror("Layer name already exists in this network");
	 else insert_name_layer($2, CA);
       }
       ;
/*****************************************************************************/
fo_lparam
       : fo_lparam  COM_  fo_param
       | fo_param
       ;
/*****************************************************************************/
fo_param
       : classification_   

       { insert_param_layer(1, CLASSIFICATION); }

       | regression_ 

       { insert_param_layer(1, REGRESSION); }

       | autoencoder_ 

       { insert_param_layer(2, AUTOENCODER); }
       ;
/*****************************************************************************/
ci_lparam          
       : ci_lparam  COM_  ci_param  
       | ci_param
       ;
/*****************************************************************************/
ci_param           
       : nz_  EQ_  cte_ 

       { insert_param_layer(1, $3); }
 
       | nr_  EQ_  cte_  

       { insert_param_layer(2, $3); }

       | nc_  EQ_  cte_

       { insert_param_layer(3, $3); }

       | cr_  EQ_  cte_

       { insert_param_layer(4, $3); }

       | cc_  EQ_  cte_

       { insert_param_layer(5, $3); }
       ;
/*****************************************************************************/
f_param
       : /* cadena vacia */

       {
	 $$ = FALSE;
	 insert_param_layer(1, 0);
       }

       | local_

       { 
         $$ = FALSE;
	 insert_param_layer(1, 1);
       }

       | numnodes_  EQ_  cte_ 

       { 
         $$ = TRUE;
	 insert_param_layer(1, $3);
       }
       ;
/*****************************************************************************/
c_lparam        
       : c_lparam  COM_  c_param
       | c_param
       ;
/*****************************************************************************/
c_param         
       : nk_  EQ_  cte_  

       { insert_param_layer(1, $3); }

       | kr_  EQ_  cte_  

       { insert_param_layer(2, $3); }

       | kc_  EQ_  cte_

       { insert_param_layer(3, $3); }

       | rpad_  EQ_  cte_  

       { insert_param_layer(4, $3); }

       | cpad_  EQ_  cte_ 

       { insert_param_layer(5, $3); }

       | stride_  EQ_  cte_

       { insert_param_layer(6, $3); }
       ;
/*****************************************************************************/
mp_lparam          
       : mp_lparam  COM_  mp_param  
       | mp_param
       ; 
/*****************************************************************************/
mp_param           
       : sizer_  EQ_  cte_  

       { insert_param_layer(1, $3); }

       | sizec_  EQ_  cte_ 

       { insert_param_layer(2, $3); }
       ;
/*****************************************************************************/
edge
       : name_layer  RAR_  name_layer

       { insert_link($1,$3); }
       ;
/*****************************************************************************/
name_layer
       : id_  PER_  id_

       { $$ = search_states($1, $3); }

       | id_

       { $$ = search_states("", $1);  }
       ;
/*****************************************************************************/
def_script
       : script_  BCB_  list_actions  ECB_
       ;
/*****************************************************************************/
list_actions
       : list_actions  action
       | action
       ;
/*****************************************************************************/
action
       : amendment
       | command
       ;
/*****************************************************************************/
amendment
       : id_  PER_  id_  PER_  parameter

       { int k2, k1 =  search_network ($1);
	 if (k1 >= 0) {
           k2 = search_layer(k1, $3);
	   if (k2 >= 0)
	     get_amendment(LAYER, k2, $5);
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       }

       | id_  PER_  parameter

       { int k = search_network ($1);
	 if (k >= 0)  get_amendment(NETWORK, k, $3);
	 else yyerror("Network name does not exist");
       }

       | id_  PER_  balance_  EQ_  cte_

       { int k = search_data ($1);
	 if (k >= 0)  get_amendment_data(k, $5);
	 else yyerror("Data or network name does not exist");
       }
       ;
/*****************************************************************************/
command
       : id_  PER_  id_  PER_  printkernels_  BRB_  nfile_  ERB_

       { int k2, k1 =  search_network ($1);
	 if (k1 >= 0) {
           k2 = search_layer(k1, $3);
	   if (k2 >= 0) 
	     get_printkernels(k1, k2, $7);
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       }

       | train_  BRB_  cte_  COM_  cte_  rest_train  ERB_

       { get_train($3, $5, $6); }

       | id_  PER_  train_  BRB_  cte_  ERB_

       { int k = search_network ($1);
	 if (k >= 0)  get_net_train(k, $5);
	 else yyerror("Network name does not exist");
       }

       | id_  PER_  save_  BRB_  nfile_  ERB_

       { int k = search_network ($1);
	 if (k < 0)
	   yyerror("Network name does not exist");
	 else get_save(k, $5);
       }

       | id_  PER_  load_  BRB_  nfile_  ERB_

       { int k = search_network ($1);
	 if (k < 0)
	   yyerror("Network name does not exist");
	 else get_load(k, $5);
       }

       | id_  PER_  testout_  BRB_  nfile_  ERB_

       { int k = search_network ($1);
	 if (k < 0)
	   yyerror("Network name does not exist");
	 else get_testout(k, $5);
       }

       | id_  PER_  zscore_  BRB_  other_data  ERB_

       { int k2, k1 = search_data ($1);
	 if (k1 >= 0) 
	   if (strlen($5) > 0) {
	     k2 = search_data ($5);
	     if (k2 >= 0) get_zscore(k1,k2);
	     else yyerror("Data name does not exist");
	   }
	   else  get_zscore(k1,-1);
	 else yyerror("Data name does not exist");
       }

       | id_  PER_  center_  BRB_  other_data  ERB_

       { int k2, k1 = search_data ($1);
	 if (k1 >= 0) 
	   if (strlen($5) > 0) {
	     k2 = search_data ($5);
	     if (k2 >= 0) get_center(k1,k2);
	     else yyerror("Data name does not exist");
	   }
	   else  get_center(k1,-1);
	 else yyerror("Data name does not exist");
       }

       | id_  PER_  yuv_  BRB_  ERB_

       { int k = search_data ($1);
	 if (k >= 0) get_yuv(k);
	 else yyerror("Data name does not exist");
       }

       | id_  PER_  div_  BRB_  ctr_  ERB_

       { int k = search_data ($1);
	 if (k >= 0) get_div(k, $5);
	 else yyerror("Data name does not exist");
       }
       ;
/*****************************************************************************/
rest_train
       : /* cadena vacia */

       { $$ = insert_net_stack(-1, ""); }

       | rest_train  COM_  id_  

       { $$ = insert_net_stack($1, $3); }

       ;
/*****************************************************************************/
other_data
       :      { $$ = ""; }  /* instruccion vacia */      
       | id_  { $$ = $1; }
       ;
/*****************************************************************************/
parameter 
       : param_ctr  EQ_  ctr_

       { $$ = get_amend_param_ctr($1, $3); }

       | param_cte  EQ_  cte_

       { $$ = get_amend_param_cte($1, $3); }
       ;
/*****************************************************************************/
param_ctr
       : mu_            { $$ = mu;         }  /*  0.0001  */
       | mmu_           { $$ = mmu;        }  /*  0.9     */ 
       | l2_            { $$ = l2;         }  /*  0.0     */ 
       | l1_            { $$ = l1;         }  /*  0.0     */ 
       | maxn_          { $$ = maxn;       }  /*  0.0     */ 
       | drop_          { $$ = drop;       }
       | noiser_        { $$ = noiser;     }  /*  0       */ 
       | noisesd_       { $$ = noisesd;    }  /*  0       */ 
       | brightness_    { $$ = brightness; }
       | contrast_      { $$ = contrast;   }
       | lambda_        { $$ = lambda;     }
       ;
/*****************************************************************************/
param_cte
       : bn_            { $$ = bn;         }
       | act_           { $$ = act;        }  /*  1       */ 
       | shift_         { $$ = shift;      }
       | flip_          { $$ = flip;       }
       ;
/*****************************************************************************/
%%
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
