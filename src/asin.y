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
  float   creal;                      /* for the "real constant" terminal    */
  int     aux;
} /***************************************************************************/
%token
/**************************************************************** Parameters */
 batch_  threads_  log_  seed_  gpu_
 filename_  tr_  ts_  va_  ascii_  binary_
 F_  FI_  FO_  C_  CI_  MP_  CAT_  ADD_  
 classification_  regression_  autoencoder_
 nz_  nr_  nc_  cr_  cc_  numnodes_ 
 nk_  kr_  kc_  rpad_  cpad_ stride_
 sizer_  sizec_  
 mu_  mmu_  l2_  l1_  maxn_  drop_  noiser_  noisesd_  brightness_  contrast_
 lambda_  noiseb_  advf_  bn_  act_  shift_  flip_  adv_  balance_  cropmode_
/*****************************************************************  Keywords */
 const_  data_  network_  script_  train_  evaluate_  save_  zscore_  yuv_  
 printkernels_  local_  load_  testout_  center_  div_  test_  add_  sub_  
 mul_ maxmin_  store_
/****************************************************************  operators */
 BCB_  ECB_  BSB_  ESB_  BRB_  ERB_  PER_  COM_  EQ_  RAR_
/**************************************************** tokens with attributes */
%token<ident> id_  nfile_
%token<creal> cte_
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

       { insert_gconstants(BATCH, (int)$3, ""); }

       | threads_ EQ_  cte_  

       { insert_gconstants(THREADS, (int)$3, ""); }

       | log_  EQ_  nfile_

       { insert_gconstants(LOG, 0, $3); }

       | seed_  EQ_  cte_

       { insert_gconstants(SEED, (int)$3, ""); }

       | gpu_  EQ_  cte_

       { insert_gconstants(GPU, (int)$3, ""); }
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

       { get_network(); /* end_network(); */ }

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

       { inser_param_data($3, -1, -1); }

       | filetype 

       { inser_param_data("", $1, -1); }

       | id_  PER_  id_  id_  PER_  id_

       { int kf2, kt2, kf1 = search_network($1), kt1 = search_network($4);

	 if (kf1 >= 0) {
	   kf2 = search_layer(kf1, $3);
	   if (kf2 >= 0)
	     if (kt1 >= 0) {
	       kt2 = search_layer(kt1, $6);
	       if (kt2 >= 0)
		 if (kf1 == kt1)  inser_param_data("", kf2, kt2); 
		 else yyerror("Network name must be unique");
	       else yyerror("Layer name does not exist on this network");
	     }
	     else yyerror("Network name does not exist");
	   else yyerror("Layer name does not exist on this network");
	 }
         else yyerror("Network name does not exist");
       }
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
	 else if ($4 == TRUE) {
	   check_param_layer(1);
	   insert_name_layer($2, F);
	 }
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

       | CAT_  id_ 

       { int k = search_layer(-1, $2);
	 if (k >= 0) 
	   yyerror("Layer name already exists in this network");
	 else insert_name_layer($2, CAT);
       }

       | ADD_  id_ 

       { int k = search_layer(-1, $2);
	 if (k >= 0) 
	   yyerror("Layer name already exists in this network");
	 else insert_name_layer($2, ADD);
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

       { insert_param_layer(1, AUTOENCODER); }

       | id_  PER_  id_

       { int k2, k1 =  search_network ($1);
	 if (k1 >= 0) {
           k2 = search_layer(k1, $3);
	   if (k2 >= 0) 
	     insert_param_layer(2, k2);
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       }
       ;
/*****************************************************************************/
ci_lparam          
       : ci_lparam  COM_  ci_param  
       | ci_param
       ;
/*****************************************************************************/
ci_param           
       : nz_  EQ_  cte_ 

       { insert_param_layer(1, (int)$3); }
 
       | nr_  EQ_  cte_  

       { insert_param_layer(2, (int)$3); }

       | nc_  EQ_  cte_

       { insert_param_layer(3, (int)$3); }

       | cr_  EQ_  cte_

       { insert_param_layer(4, (int)$3); }

       | cc_  EQ_  cte_

       { insert_param_layer(5, (int)$3); }
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
	 insert_param_layer(1, (int)$3);
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

       { insert_param_layer(1, (int)$3); }

       | kr_  EQ_  cte_  

       { insert_param_layer(2, (int)$3); }

       | kc_  EQ_  cte_

       { insert_param_layer(3, (int)$3); }

       | rpad_  EQ_  cte_  

       { insert_param_layer(4, (int)$3); }

       | cpad_  EQ_  cte_ 

       { insert_param_layer(5, (int)$3); }

       | stride_  EQ_  cte_

       { insert_param_layer(6, (int)$3); }
       ;
/*****************************************************************************/
mp_lparam          
       : mp_lparam  COM_  mp_param  
       | mp_param
       ; 
/*****************************************************************************/
mp_param           
       : sizer_  EQ_  cte_  

       { insert_param_layer(1, (int)$3); }

       | sizec_  EQ_  cte_ 

       { insert_param_layer(2, (int)$3); }
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

       | id_  PER_  cropmode_  EQ_  cte_

       { int k = search_network ($1);
	 if (k >= 0)  get_amendment_onlynet(k, (int)$5);
	 else yyerror("Network name does not exist");
       }

       | id_  PER_  balance_  EQ_  cte_

       { int k = search_data ($1);
	 if (k >= 0)  get_amendment_data(k, (int)$5);
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

       | id_  PER_  id_  EQ_  id_  PER_  id_

       { int d2, d1 =  search_network ($1);
         int s2, s1 =  search_network ($5);

         d2 = search_layer(d1, $3); s2 = search_layer(s1, $7);
	 if (d1 < 0) yyerror("Destination network does not exist");
	 else if (d2 < 0) yyerror("Destination layer does not exist");
	 else if (s1 < 0) yyerror("Source network does not exist");
         else if (s2 < 0) yyerror("Source layer does not exist");
	 else get_copy(d1, d2, s1, s2);
       }

       | train_  BRB_  cte_  COM_  cte_  COM_  cte_  rest_train  ERB_

       { get_train((int)$3, (int)$5, (int)$7, $8); }

       | id_  PER_  train_  BRB_  cte_  ERB_

       { int k = search_network ($1);
	 if (k >= 0)  get_net_train(k, (int)$5);
	 else yyerror("Network name does not exist");
       }

       | id_  PER_  test_  BRB_  other_data  ERB_

       { int k2, k1 = search_network ($1);
	 if (k1 >= 0)  
	   if (strlen($5) > 0) {
	     k2 = search_data ($5);
	     if (k2 >= 0) get_net_test(k1, k2);
	     else yyerror("Data name does not exist");
	   }
	   else  get_net_test(k1,-1);
	 else yyerror("Network name does not exist");
       }

       | id_  PER_  evaluate_  BRB_  id_  ERB_

       { int k2, k1 = search_network ($1);
	 if (k1 >= 0) {
	   k2 = search_data ($5);
	   if (k2 >= 0) get_net_evaluate(k1, k2);
	   else yyerror("Data name does not exist");
	 }
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

       | id_  PER_  div_  BRB_  cte_  ERB_

       { int k = search_data ($1);
	 if (k >= 0) get_div(k, $5);
	 else yyerror("Data name does not exist");
       }

       | id_  PER_  add_  BRB_  cte_  ERB_

       { int k = search_data ($1);
	 if (k >= 0) get_add(k, $5);
	 else yyerror("Data name does not exist");
       }

       | id_  PER_  sub_  BRB_  cte_  ERB_

       { int k = search_data ($1);
	 if (k >= 0) get_sub(k, $5);
	 else yyerror("Data name does not exist");
       }

       | id_  PER_  maxmin_  BRB_  ERB_

       { int k = search_data ($1);
	 if (k >= 0) get_maxmin(k);
	 else yyerror("Data name does not exist");
       }

       | id_  PER_  store_  BRB_  nfile_  ERB_

       { int k = search_data ($1);
	 if (k >= 0) get_store(k, $5);
	 else yyerror("Data name does not exist");
       }

       | id_  PER_  mul_  BRB_  cte_  ERB_

       { int k = search_data ($1);
	 if (k >= 0) get_mul(k, $5);
	 else yyerror("Data name does not exist");
       }



       ;
/*****************************************************************************/
rest_train
       : /* cadena vacia */

       { $$ = insert_net_stack(-1, -1); }

       | rest_train  COM_  id_  

       { int k = search_network($3); $$ = $1;

	 if (k >= 0) $$ = insert_net_stack($1, k); 
	 else yyerror("The name of network does not exist");
       }
       ;
/*****************************************************************************/
other_data
       :      { $$ = ""; }  /* instruccion vacia */      
       | id_  { $$ = $1; }
       ;
/*****************************************************************************/
parameter 
       : param_ctr  EQ_  cte_

       { $$ = get_amend_param_ctr($1, $3); }

       | param_cte  EQ_  cte_

       { $$ = get_amend_param_cte($1, (int)$3); }
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
       | noiseb_        { $$ = noiseb;     }
       | advf_          { $$ = advf;       }
       ;
/*****************************************************************************/
param_cte
       : bn_            { $$ = bn;         }
       | act_           { $$ = act;        }  /*  1       */ 
       | shift_         { $$ = shift;      }
       | flip_          { $$ = flip;       }
       | adv_           { $$ = adv;        }
       ;
/*****************************************************************************/
%%
/*****************************************************************************/
/*****************************************************************************/
