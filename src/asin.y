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
  int     aux;                        /* For non-terminals with 1 attributes */
  TUPLE   aux2;                       /* For non-terminals with 2 attributes */
  AUX4    aux4;                       /* For non-terminals with 4 attributes */
  RANGO   rango;                      /* For non-terminals with rank         */
  EXPRE   expre;                      /* For non-terminal expression         */
  EXPFOR  expfor;                     /* For two exp of FOR                  */
} /***************************************************************************/
%token
/**************************************************************** Parameters */
 batch_  threads_  seed_  cpu_  gpu_  device_  cuDNN_  cuBLAS_  filename_  
 tr_  ts_  va_  ascii_  binary_  gauss_  uniform_  ones_  zeros_  oneshot_  
 pos_  nrows_  ncolsample_  ncoltarget_  F_  FI_  FO_  C_  CI_  MP_  CAT_ O_ 
 ADD_  classification_  regression_  autoencoder_ max_ min_ maxlog_ minlog_
 nz_  nr_  nc_  cr_  cc_  numnodes_ T_ S_  W_  GW_  B_  GB_  N_
 nk_  kr_  kc_  rpad_  cpad_ stride_
 sizer_  sizec_   mu_  mmu_  l2_  l1_  maxn_  drop_  noiser_  noisesd_  
 brightness_  contrast_  lambda_  noiseb_  advf_  bn_  act_  shift_  flip_  
 adv_  balance_  cropmode_  trainable_
/*****************************************************************  Keywords */
 const_  data_  network_  script_  printkernels_  change_  train_  save_  load_
 testout_  forward_  backward_  resetstats_  printerrors_  reseterrors_
 trainmode_  testmode_  update_  test_  evaluate_  zscore_  center_  yuv_  
 maxmin_  shuffle_  next_  set_  mul_  div_  add_  sub_  store_  getstats_
 bin_  int_  real_  copy_ imult_ omult_ sigmoid_ tanh_ relu_ 
 for_  if_  else_ 
/****************************************************************  operators */
 BCB_  ECB_  BSB_  ESB_  BRB_  ERB_  PER_  COM_  EQ_  RAR_  COL_  
 MAS_  MENOS_  POR_  DIV_  MOD_  PORPOR_  log_  exp_  sqr_  TRUE_  FALSE_
 AND_  OR_  EQUAL_  NOTEQUAL_  GREAT_  GREATEQ_  LESS_  LESSEQ_  NOT_

%nonassoc IFAUX_
%nonassoc else_
/**************************************************** tokens with attributes */
%token<ident> id_  nfile_  cecho_
%token<creal> cte_
/********************************************** nonterminals with attributes */
%type<aux>    gentype  filetype  fparam  namelayer  parameter  
              functions  op_una  op_mul  op_add  op_rel  op_eq  op_log 
              comnetvoid  comnetfile  comnetdat  comnetexp  
              comdatvoid  comdatfile  comdatdat  comdatexp  
              comlayfile comlaydatlay  comcopy
%type<ident>  other_data  datcopy  matweights
%type<aux4>   alpha  beta  
%type<aux2>   datlay
%type<rango>  rank
%type<expfor> restfor
%type<expre>  exp_suf  exp_unary  exp_mul  exp_add  exp_rel  exp_eq  exp
/*****************************************************************************/
%%
/*****************************************************************************/
experiment: 
       { begin_experiment(); }

         constants 

       { get_gconstants(); }

         definitions

       { end_experiment(); }
       ;
/*****************************************************************************/
constants      
       : /*  empty string  */
       | const_  BCB_  lconstants  ECB_
       ;
/*****************************************************************************/
lconstants     
       : lconstants  const 
       | const
       ;
/*****************************************************************************/
const  : batch_   EQ_  cte_  

       { insert_gconstants(BATCH, (int)$3, ""); }

       | threads_ EQ_  cte_  

       { insert_gconstants(THREADS, (int)$3, ""); }

       | seed_  EQ_  cte_

       { insert_gconstants(SEED, (int)$3, ""); }

       | device_  EQ_  cpu_

       { insert_gconstants(DEVICE, -1, ""); }

       | device_  EQ_  gpu_  cte_

       { insert_gconstants(DEVICE, (int)$4, ""); }

       | cuDNN_  EQ_  cte_

       { insert_gconstants(CUDNN, (int)$3, ""); }

       | cuBLAS_  EQ_  cte_

       { insert_gconstants(CUBLAS, (int)$3, ""); }

       | log_  EQ_  nfile_

       { insert_gconstants(LOG, -1, $3); }
       ;
/*****************************************************************************/
definitions
       : definitions  def 
       | def
       ;
/*****************************************************************************/
def    : data_  BCB_  ldata  ECB_

       { get_data(); }

       | network_  id_  

       { insert_name_network($2); }

         BCB_  lnetdata  

       { get_net_data(); }

         lnetstat  ECB_

       { get_network(); }

       | { create_list_names(); } 

         script_  BCB_  lactions  ECB_

	 /*{ show_list_names (); }*/
       ; 
/*****************************************************************************/
ldata  : ldata  data
       | data
       ;
/*****************************************************************************/
data   : id_ 

       { int k = search_data($1);
	 if (k < 0)  inser_name_data($1);
	 else yyerror("Data name already exists");
       }

         BSB_  datapar  ESB_
       ;
/*****************************************************************************/
datapar: ldparfile

       { check_param_data(FILES); }

       | ldpargen

       { check_param_data(GENERATED); }

       | ldparcrea

       { check_param_data(CREADATA); }
       ;
/*****************************************************************************/
ldparfile
       : ldparfile  COM_  dparfile 
       | dparfile
       ;
/*****************************************************************************/
dparfile
       : filetype

       { inser_param_data(FILES, "", $1, -1, -1); }

       | filename_  EQ_  nfile_ 

       { inser_param_data(FILES, $3, -1, -1, -1); }
       ;
/*****************************************************************************/
ldpargen
       : ldpargen  COM_  dpargen
       | dpargen
       ;
/*****************************************************************************/
dpargen: gentype 

       { inser_param_data(GENERATED, "", $1, -1, -1); }

       | numnodes_  EQ_  cte_  

       { inser_param_data(GENERATED, "", -1, (int)$3, -1); }

       | pos_  EQ_  cte_ 

       { inser_param_data(GENERATED, "", -1, -1, (int)$3); }
       ;
/*****************************************************************************/
ldparcrea
       : ldparcrea  COM_  dparcrea 
       | dparcrea
       ;
/*****************************************************************************/
dparcrea: nrows_  EQ_  cte_  

       { inser_param_data(CREADATA, "", (int)$3, -1, -1); }

       | ncolsample_  EQ_  cte_  

       { inser_param_data(CREADATA, "", -1, (int)$3, -1); }

       | ncoltarget_  EQ_  cte_ 

       { inser_param_data(CREADATA, "", -1, -1, (int)$3); }
       ;
/*****************************************************************************/
filetype
       : ascii_        { $$ = ASCII;  }
       | binary_       { $$ = BINARY; }
       ;
/*****************************************************************************/
gentype
       : gauss_        { $$ = GAUSS;  }
       | uniform_      { $$ = UNIFORM; }
       | ones_         { $$ = ONES;  }
       | zeros_        { $$ = ZEROS;  }
       | oneshot_      { $$ = ONESHOT;  }
       ;
/*****************************************************************************/
lnetdata           
       : /* Empty string */
       | lnetdata  netdata
       ;
/*****************************************************************************/
netdata
       : data_  tr_  id_ 

       { int k = search_data ($3);
         if (k < 0)
           yyerror("Data name does not exist");
         else inser_param_net_data(TR, k);
       }

       | data_  ts_  id_

       { int k = search_data ($3);
         if (k < 0)
           yyerror("Data name does not exist");
         else inser_param_net_data(TS, k);
       }

       | data_  va_  id_ 

       { int k = search_data ($3);
         if (k < 0)
           yyerror("Data name does not exist");
         else inser_param_net_data(VA, k);
       }
       ;
/*****************************************************************************/
lnetstat
       : lnetstat  netstat
       | netstat
       ;
/*****************************************************************************/
netstat: layer        
       | edge
       ;
/*****************************************************************************/
layer  : FI_  id_  fiparameter

       { int k = search_layer(-1, $2);
	 if (k < 0) insert_name_layer($2, FI);
	 else  yyerror("Layer name already exists in this network");
       }

       | CI_  id_  BSB_  cilparam  ESB_

       { int k = search_layer(-1, $2);
	 if (k < 0) {
	   check_param_layer(3);
	   insert_name_layer($2, CI);
	 }
	 else yyerror("Layer name already exists in this network");
       }

       | FO_  id_  BSB_  folparam  ESB_

       { int k = search_layer(-1, $2);
	 if (k < 0) {
	   check_param_layer(1);
	   insert_name_layer($2, FO);
	 }
	 else yyerror("Layer name already exists in this network");
       }

       | F_  id_  BSB_  fparam  ESB_

       { int k = search_layer(-1, $2);
	 if (k >= 0) 
	   yyerror("Layer name already exists in this network");
	 else if ($4 == TRUE) {
	   check_param_layer(1);
	   insert_name_layer($2, F);
	 }
	 else insert_name_layer($2, R);
       }
 
       | C_  id_  BSB_  clparam  ESB_

       { int k = search_layer(-1, $2);
	 if (k >= 0)
	   yyerror("Layer name already exists in this network");
	 else {
	   check_param_layer(3);
	   insert_name_layer($2, C);
	 }
       }

       | MP_  id_  BSB_  mplparam  ESB_ 

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

       | O_  id_  BSB_  oparam  ESB_

       { int k = search_layer(-1, $2);
	 if (k >= 0) 
	   yyerror("Layer name already exists in this network");
	 else {
	   check_param_layer(1);
	   insert_name_layer($2, O);
	 } 
       }
       ;
/*****************************************************************************/
fiparameter
       : /* Empty string */
       | BSB_  filparam  ESB_
       ;
/*****************************************************************************/
filparam
       : filparam  COM_  fiparam  
       | fiparam
       ;
/*****************************************************************************/
fiparam
       : id_  PER_  id_

       { int k2, k1 =  search_network ($1);

	 if (k1 >= 0) {
           k2 = search_layer(k1, $3);
	   if (k2 >= 0) 
	     insert_param_layer(1, k2);
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       }

       |  id_

       { int k = search_data ($1);
         if (k < 0)
           yyerror("Data name does not exist");
         insert_param_layer(2, k);
       }
       ;
/*****************************************************************************/
cilparam          
       : cilparam  COM_  ciparam  
       | ciparam
       ;
/*****************************************************************************/
ciparam           
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

       | id_  PER_  id_ 

       { int k2, k1 =  search_network ($1);

	 if (k1 >= 0) {
           k2 = search_layer(k1, $3);
	   if (k2 >= 0) 
	     insert_param_layer(6, k2);
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       }

       | id_

       { int k = search_data ($1);
         if (k < 0)
           yyerror("Data name does not exist");
         insert_param_layer(7, k);
       }
       ;
/*****************************************************************************/
folparam          
       : folparam  COM_  foparam  
       | foparam
       ;
/*****************************************************************************/
foparam
       : classification_   

       { insert_param_layer(1, CLASSIFICATION); }

       | regression_ 

       { insert_param_layer(1, REGRESSION); }

       | autoencoder_ 

       { insert_param_layer(1, AUTOENCODER); }

       | max_ 

       { insert_param_layer(1, MAX); }

       | min_ 

       { insert_param_layer(1, MIN); }
 
       | minlog_ 

       { insert_param_layer(1, MINLOG); }

       | maxlog_ 

       { insert_param_layer(1, MAXLOG); }

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

       | id_

       { int k = search_data ($1);
         if (k < 0)
           yyerror("Data name does not exist");
         insert_param_layer(3, k);
       }
       ;
/*****************************************************************************/
fparam
       : /* cadena vacia */

       { $$ = FALSE; }

       | numnodes_  EQ_  cte_

       { 
         $$ = TRUE;
	 insert_param_layer(1, (int)$3);
       }
       ;
/*****************************************************************************/
clparam        
       : clparam  COM_  cparam
       | cparam
       ;
/*****************************************************************************/
cparam         
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
mplparam          
       : mplparam  COM_  mpparam  
       | mpparam
       ; 
/*****************************************************************************/
mpparam           
       : sizer_  EQ_  cte_  

       { insert_param_layer(1, (int)$3); }

       | sizec_  EQ_  cte_ 

       { insert_param_layer(2, (int)$3); }
       ;
/*****************************************************************************/
oparam : add_

       { insert_param_layer(1, ADDITION); }

       | sub_

       { insert_param_layer(1, SUBTRACTION); }

       | div_

       { insert_param_layer(1, DIVISION); }

       | imult_

       { insert_param_layer(1, INNERMULT); }

       | omult_

       { insert_param_layer(1, OUTERMULT); }

       | sigmoid_

       { insert_param_layer(1, SIGMOID); }

       | tanh_

       { insert_param_layer(1, TANH); }

       | log_

       { insert_param_layer(1, LOGARITHM); }

       | relu_

       { insert_param_layer(1, RELU); }
       ;
/*****************************************************************************/
edge
       : namelayer  RAR_  namelayer

       { insert_link($1,$3); }
       ;
/*****************************************************************************/
namelayer
       : id_  PER_  id_

       { $$ = search_states($1, $3); }

       | id_

       { $$ = search_states("", $1);  }
       ;
/*****************************************************************************/
lactions
       : /*  Empty string  */
       | lactions 

       { $<aux>$ = pstv; }

         actions  

       { pstv = $<aux>2; }
       ;
/*****************************************************************************/
actions: amendment
       | command
   
       | if_  BRB_  exp  ERB_

       { get_if($3); } 
   
         BCB_  lactions  ECB_  restif

       { get_endif(); } 
       
       | for_  id_  EQ_  exp  COL_ restfor 

       { ptsymbol t = search_name($2);
         if (t == NULL) t = insert_name($2); 
         get_for(t, $4, $6.expre1, $6.expre2);
       } 

         BCB_  lactions  ECB_

       { get_endfor(); }

       | id_  EQ_  exp

       { ptsymbol t = search_name($1);
         if (t == NULL)   t = insert_name($1); 
         get_exp_eqvar(t, $3); 
        }

       | id_  BRB_  exp  COM_  exp  ERB_  EQ_  exp

       { int k =  search_data ($1);
         if (k >= 0)  get_exp_eqelem(k, $3, $5, $8);
         else yyerror("Data name does not exist");
       }
       ;
/*****************************************************************************/
restif :  %prec IFAUX_

       { get_else(); } 

       | else_  
   
       { get_else(); } 

         BCB_  lactions  ECB_  
       ;
/*****************************************************************************/
restfor: exp

       { 
         $$.expre1.psymbol = NULL;  $$.expre1.reftemp = cr_var_temp();  
	 get_init_cte($$.expre1.reftemp, 1);
         $$.expre2 = $1;
       } 

       | exp  COL_  exp        

       { $$.expre1 = $1; $$.expre2 = $3; }  
       ;
/*****************************************************************************/
amendment
       : id_  PER_  id_  PER_  parameter  EQ_  exp

       { int k2, k1 =  search_network ($1);
	 if (k1 >= 0) {
           k2 = search_layer(k1, $3);
	   if (k2 >= 0)
	     get_amendment(LAYER, k2, $5, $7);
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       }

       | id_  PER_  parameter  EQ_  exp

       { int k = search_network ($1);
	 if (k >= 0)  get_amendment(NETWORK, k, $3, $5);
	 else { 
	   k = search_data ($1);
	   if (k >= 0)  get_amendment(DATA, k, $3, $5);
	   else yyerror("Data or network name does not exist");
	 }
       }
       ;
/*****************************************************************************/
parameter                                     /* Real parameters */
       : mu_            { $$ = mu;         }     /*  0.0001  */
       | mmu_           { $$ = mmu;        }     /*  0.9     */ 
       | l2_            { $$ = l2;         }     /*  0.0     */ 
       | l1_            { $$ = l1;         }     /*  0.0     */ 
       | maxn_          { $$ = maxn;       }     /*  0.0     */ 
       | drop_          { $$ = drop;       }
       | noiser_        { $$ = noiser;     }     /*  0       */ 
       | noisesd_       { $$ = noisesd;    }     /*  0       */ 
       | brightness_    { $$ = brightness; }
       | contrast_      { $$ = contrast;   }
       | lambda_        { $$ = lambda;     }
       | noiseb_        { $$ = noiseb;     }
       | advf_          { $$ = advf;       }
       | bn_            { $$ = bn;         }  /* Integer parameters */
       | act_           { $$ = act;        }     /*  1       */ 
       | shift_         { $$ = shift;      }
       | flip_          { $$ = flip;       }
       | adv_           { $$ = adv;        }
       | cropmode_      { $$ = cropmode;   }
       | balance_       { $$ = balance;    }
       | trainable_     { $$ = trainable;  }
       ;
/*****************************************************************************/
command
       : cecho_    { get_echo($1); }

       | id_  PER_  id_  PER_  comlayfile  BRB_  nfile_  ERB_

       { int k2, k1 =  search_network ($1);

	 if (k1 >= 0) {
           k2 = search_layer(k1, $3);
	   if (k2 >= 0) 
	     get_com_lay_file(k1, k2, $5, $7);
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       }

       | id_  PER_  id_  PER_  comlaydatlay  BRB_  datlay  ERB_

       { int d2, d1 =  search_network ($1);
	 if (d1 >= 0) {
	   d2 = search_layer(d1, $3);
	   if (d2 >= 0)  get_com_lay_datlay(d1, d2, $5, $7.ref, $7.typ);
	   else yyerror("Destination layer does not exist");
	 }
	 else yyerror("Destination network does not exist");
       }

       | id_  PER_  id_  PER_  comcopy  BRB_  datcopy  ERB_

       { int k2, k1 =  search_network ($1);
	 if (k1 >= 0) {
	   k2 = search_layer(k1, $3); 
	   if (k2 >= 0) get_com_lay_copy(k1, k2, $5, $7);
	   else yyerror("Destination layer does not exist");
	 }
	 else yyerror("Destination network does not exist");
       }

       | id_  PER_  comnetvoid  BRB_  ERB_

       { int k = search_network ($1);
	 if (k >= 0) get_com_net_void(k, $3);
	 else yyerror("Network name does not exist");
       }

       | id_  PER_  comnetfile  BRB_  nfile_  ERB_

       { int k = search_network ($1);
	 if (k >= 0)   get_com_net_file(k, $3, $5);
	 else yyerror("Network name does not exist");
       }

       | id_  PER_  comnetdat  BRB_  other_data  ERB_

       { int k2, k1 = search_network ($1); 
	 if (k1 >= 0)  
	   if (strlen($5) == 0)  get_com_net_dat(k1, $3, -1);
	   else {
	     k2 = search_data ($5);
	     if (k2 >= 0) get_com_net_dat(k1, $3, k2);
	     else  yyerror("Data name does not exist");
	   }
	 else yyerror("Network name does not exist");
       }

       | id_  PER_  comnetexp  BRB_  exp  ERB_

       { int k = search_network ($1);
	 if (k >= 0)  get_com_net_exp(k, $3, $5);
	 else yyerror("Network name does not exist");
       }

       | id_  rank  PER_  comdatvoid  BRB_  ERB_

       { int k = search_data ($1);
	 if (k >= 0)	get_com_data_void_rank(k, $2, $4);
         else yyerror("Data name does not exist");
       }

       | id_  PER_  comdatvoid  BRB_  ERB_

       { int k = search_data ($1); 
	 if (k >= 0)	get_com_data_void(k, $3);
         else yyerror("Data name does not exist");
       }

       | id_  PER_  comdatfile  BRB_  nfile_  ERB_

       { int k = search_data ($1); 
         if (k >= 0)	get_com_data_file(k, $3, $5); 
         else yyerror("Data name does not exist");
       }

       | id_  PER_  comdatdat  BRB_  id_  ERB_

       { int k2, k1 = search_data ($1); 
         if (k1 >= 0) {
	   k2 = search_data ($5);
	   if (k2 >= 0)  get_com_data_dat(k1, $3, k2);
	   else yyerror("Data name does not exist");
	 }
         else yyerror("Data name does not exist");
       }

       | id_  rank  PER_  comdatexp  BRB_  exp  ERB_

       { int k = search_data ($1);
         if (k >= 0)	get_com_data_exp_rank(k, $2, $4, $6);
         else yyerror("Data name does not exist");
       }

       | id_  PER_  comdatexp  BRB_  exp  ERB_

       { int k = search_data ($1); 
         if (k >= 0)	get_com_data_exp(k, $3, $5);
         else yyerror("Data name does not exist");
       }

       | id_  rank  PER_  comcopy  BRB_  datcopy  ERB_

       { int k = search_data ($1);
 	 if (k >= 0)  get_com_data_copy_rank(k, $2, $4, $6);
	 else yyerror("Data name does not exist");
       } 

       | id_  PER_  comcopy  BRB_  datcopy  ERB_

       { int k = search_data ($1);
         if (k < 0)  k = inser_new_name_data($1);
	 get_com_data_copy(k, $3, $5);
       }
       ;
/*****************************************************************************/
rank   : BSB_  alpha  COM_  beta  ESB_ 

       { $$.row = $2; $$.col = $4; }
       ;
/*****************************************************************************/
alpha  /* : Empty string  

       { $$.cte1 = $$.cte2 = $$.cte3 = $$.cte4 = -1; } */

       : COL_      

       { 
         $$.ini.psymbol = NULL; $$.ini.reftemp = cr_var_temp_cte_1(); 
         $$.fin.psymbol = NULL; $$.fin.reftemp = cr_var_temp_cte_1(); 
         $$.aux = -1; 
       }

       | exp  

       { $$.ini = $$.fin = $1;  $$.aux = -1; }

       | COL_  exp   

       { 
         $$.ini.psymbol = NULL; $$.ini.reftemp = cr_var_temp_cte_1(); 
         $$.fin = $2; $$.aux = -1; 
       }

       | exp  COL_   

       { 
         $$.ini = $1; $$.aux = -1; 
         $$.fin.psymbol = NULL; $$.fin.reftemp = cr_var_temp_cte_1(); 
       }

       | exp  COL_  exp 

       { $$.ini = $1; $$.fin = $3; $$.aux = -1; }
       ;
/*****************************************************************************/
beta   /* : Empty string   

       { $$.cte1 = $$.cte2 = $$.cte3 = -1; $$.cte4 = NONE; } */

       : COL_                

       { 
         $$.ini.psymbol = NULL; $$.ini.reftemp = cr_var_temp_cte_1();
         $$.fin.psymbol = NULL; $$.fin.reftemp = cr_var_temp_cte_1();
         $$.aux = -1; 
       }

       | exp

       { $$.ini = $$.fin = $1;  $$.aux = -1; }

       | COL_  exp               

       { 
         $$.ini.psymbol = NULL; $$.ini.reftemp = cr_var_temp_cte_1();
         $$.fin = $2; $$.aux = -1; 
       }

       | exp  COL_   

       { 
         $$.ini = $1; $$.aux = -1; 
         $$.fin.psymbol = NULL; $$.fin.reftemp = cr_var_temp_cte_1();
       }

       | exp  COL_  exp

       { $$.ini = $1; $$.fin = $3; $$.aux = -1; }

       | real_         

       { 
         $$.ini.psymbol = NULL; $$.ini.reftemp = cr_var_temp_cte_1();
         $$.fin.psymbol = NULL; $$.fin.reftemp = cr_var_temp_cte_1();
         $$.aux = REAL; 
       }

       | bin_         
    
       { 
         $$.ini.psymbol = NULL; $$.ini.reftemp = cr_var_temp_cte_1();
         $$.fin.psymbol = NULL; $$.fin.reftemp = cr_var_temp_cte_1();
         $$.aux = BIN; 
       } 

       | int_        

       { 
         $$.ini.psymbol = NULL; $$.ini.reftemp = cr_var_temp_cte_1();
         $$.fin.psymbol = NULL; $$.fin.reftemp = cr_var_temp_cte_1();
         $$.aux = INT; 
       }
 
       | S_           

       { 
         $$.ini.psymbol = NULL; $$.ini.reftemp = cr_var_temp_cte_1();
         $$.fin.psymbol = NULL; $$.fin.reftemp = cr_var_temp_cte_1();
         $$.aux = SAMPLE; 
       }

       | T_           

       { 
         $$.ini.psymbol = NULL; $$.ini.reftemp = cr_var_temp_cte_1();
         $$.fin.psymbol = NULL; $$.fin.reftemp = cr_var_temp_cte_1();
         $$.aux = TARGET; 
       } 
       ;
/*****************************************************************************/
other_data
       : /* Empty string */  { $$ = ""; }
       | id_                 { $$ = $1; }
       ;
/*****************************************************************************/
comnetvoid
       : forward_     { $$ = forward;     }
       | backward_    { $$ = backward;    }
       | resetstats_  { $$ = resetstats;  }
       | printerrors_ { $$ = printerrors; }
       | reseterrors_ { $$ = reseterrors; }
       | trainmode_   { $$ = trainmode;   }
       | testmode_    { $$ = testmode;    }
       | update_      { $$ = update;      }
       ;
/*****************************************************************************/
comnetfile
       : load_        { $$ = load;    }
       | save_        { $$ = save;    }
       | testout_     { $$ = testout; }
       ;
/*****************************************************************************/
comnetdat
       : test_        { $$ = test; }
       | evaluate_    { $$ = evaluate; }
       ;
/*****************************************************************************/
comnetexp
       : train_        { $$ = train; }
       ;
/*****************************************************************************/
comdatvoid
       : zscore_     { $$ = zscore;  }
       | center_     { $$ = center;  }
       | yuv_        { $$ = yuv;     }
       | maxmin_     { $$ = maxmin;  }
       | shuffle_    { $$ = shuffle; }
       | next_       { $$ = next;    }
       ;
/*****************************************************************************/
comdatfile
       : store_      { $$ = store; }
       ;
/*****************************************************************************/
comdatdat
       : getstats_      { $$ = getstats; }
       ;
/*****************************************************************************/
comcopy
       : copy_     { $$ = copy; }
       ;
/*****************************************************************************/
comdatexp
       : mul_      { $$ = multiplication; }
       | div_      { $$ = division;       }
       | add_      { $$ = addition;       }
       | sub_      { $$ = subtraction;    }
       | set_      { $$ = set;            }
       ;
/*****************************************************************************/
comlayfile
       : printkernels_      { $$ = printkernels; }
       ;
/*****************************************************************************/
comlaydatlay
       : change_      { $$ = change; }
       ;
/*****************************************************************************/
datlay : id_
 
       { int k = search_data($1); $$.ref = $$.typ = -1;
	 if (k >= 0)  $$.ref = k; 
	 else yyerror("Data name does not exist");
       }

       | id_  PER_  id_

       { int k2, k1 =  search_network ($1); $$.ref = $$.typ = -1;
	 if (k1 >= 0) {
	   k2 =  search_layer(k1, $3);
	   if (k2 >= 0) { $$.ref = k1; $$.typ = k2; }
	   else yyerror("Source layer does not exist");
	 }
	 else yyerror("Source network does not exist");
       }
       ;
/*****************************************************************************/
datcopy: id_

       { int k = search_data($1); char t[140] = ""; 

	 if (k >= 0)  sprintf(t, "data %s", $1);
	 else yyerror("Data name does not exist");
         $$ = t;
       }

       | id_  rank

       { char opd1[140], opd2[140], opd3[140], opd4[140], t[140] = "";
         int k = search_data($1); char *aux; 

	 if (k >= 0)  {
	   strexpre(opd1,$2.row.ini); strexpre(opd2,$2.row.fin);
	   strexpre(opd3,$2.col.ini); strexpre(opd4,$2.col.fin);
	   if ($2.col.aux < 0) aux = "NONE";
	   else 
	     switch ($2.col.aux) {
	     case (REAL):   {aux = "REAL";   break;}
             case (BIN):    {aux = "BIN";    break;}
             case (INT):    {aux = "INT";    break;}
             case (TARGET): {aux = "TARGET"; break;}
             case (SAMPLE): {aux = "SAMPLE"; break;}
           }
	   sprintf(t, "rank %s %s %s %s %s %s", $1, 
		   opd1, opd2, opd3, opd4, aux);
	 }
	 else yyerror("Data name does not exist");
	 $$ = t;
       }

       | id_  PER_  id_  PER_  matweights

       { int k2, k1 = search_network ($1); char t[140] = "";

	 if (k1 >= 0) {
           k2 = search_layer(k1, $3);
	   if (k2 >= 0) 
	     sprintf(t, "layer %s %s %s", $1, $3, $5);
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
         $$ = t;
       }
       ;
/*****************************************************************************/
matweights
       : W_         { $$ = "W";  }
       | GW_        { $$ = "GW"; }
       | B_         { $$ = "B";  }
       | GB_        { $$ = "GB"; }
       | N_         { $$ = "N";  }
       ;
/*****************************************************************************/
exp    :  exp_eq           { $$ = $1; }   

       |  exp  op_log  exp_eq

       { 
         $$.psymbol = NULL;  $$.reftemp = cr_var_temp();  
	 get_exp_log($$.reftemp, $1, $2, $3);
       }
       ;
/*****************************************************************************/
exp_eq :  exp_rel           { $$ = $1; }   

       |  exp_eq  op_eq  exp_rel

       { 
         $$.psymbol = NULL;  $$.reftemp = cr_var_temp();  
	 get_exp_eq($$.reftemp, $1, $2, $3);
       }
       ;
/*****************************************************************************/
exp_rel:  exp_add           { $$ = $1; }   

       |  exp_rel  op_rel  exp_add

       { 
         $$.psymbol = NULL;  $$.reftemp = cr_var_temp();  
	 get_exp_rel($$.reftemp, $1, $2, $3);
       }
       ;
/*****************************************************************************/
exp_add:  exp_mul           { $$ = $1; }   

       |  exp_add  op_add  exp_mul

       { 
         $$.psymbol = NULL;  $$.reftemp = cr_var_temp();  
	 get_exp_add($$.reftemp, $1, $2, $3);
       }
       ;
/*****************************************************************************/
exp_mul:  exp_unary         { $$ = $1; }   

       |  exp_mul  op_mul  exp_unary

       { 
         $$.psymbol = NULL;  $$.reftemp = cr_var_temp();  
	 get_exp_mul($$.reftemp, $1, $2, $3);
       }
       ;
/*****************************************************************************/
exp_unary
       :  exp_suf           { $$ = $1; }   

       |  op_una  exp_unary

       { 
         $$.psymbol = NULL;  $$.reftemp = cr_var_temp();  
	 get_exp_unary($$.reftemp, $1, $2);
       }

       |  functions  BRB_  exp_unary  ERB_

       { 
         $$.psymbol = NULL;  $$.reftemp = cr_var_temp();  
	 get_functions($$.reftemp, $1, $3);
       }
       ;
/*****************************************************************************/
exp_suf:  BRB_  exp  ERB_   { $$ = $2; }   

       |  id_

       { 
         $$.psymbol = search_name($1);  $$.reftemp = -1;
	 if ($$.psymbol == NULL) yyerror("Undefined variable name");
       }

       |  cte_

       { 
         $$.psymbol = NULL; $$.reftemp = cr_var_temp();
         get_init_cte($$.reftemp, $1);
       }

       |  TRUE_

       { 
         $$.psymbol = NULL; $$.reftemp = cr_var_temp();
         get_init_cte($$.reftemp, 1.0);
       }

       |  FALSE_

       { 
         $$.psymbol = NULL; $$.reftemp = cr_var_temp();
         get_init_cte($$.reftemp, 0.0);
       }

       |  id_  PER_  id_  PER_  parameter   

       { int k2, k1 =  search_network ($1);
         $$.psymbol=NULL; $$.reftemp = cr_var_temp();
	 if (k1 >= 0) {
           k2 = search_layer(k1, $3);
	   if (k2 >= 0)
	     get_init_amend(LAYER, $$.reftemp, k2, $5);
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       }

       |  id_  PER_  parameter 

       { int k = search_network ($1);
         $$.psymbol=NULL; $$.reftemp = cr_var_temp();
	 if (k >= 0)  get_init_amend(NETWORK, $$.reftemp, k, $3);
	 else { 
	   k = search_data ($1);
	   if (k >= 0)  get_init_amend(DATA, $$.reftemp, k, $3);
	   else yyerror("Data or network name does not exist");
	 }
       }

       |  id_  BRB_  exp  COM_  exp  ERB_ 

       { int k =  search_data ($1);
         $$.psymbol=NULL; $$.reftemp =  cr_var_temp();
	 if (k >= 0)  get_init_elem(DATA, $$.reftemp, k, $3, $5);
	 else yyerror("Data name does not exist");
       }

       |  id_  PER_  id_  BRB_  exp  COM_  exp  ERB_

       { int k2, k1 =  search_network ($1);
         $$.psymbol=NULL; $$.reftemp = cr_var_temp();
	 if (k1 >= 0) {
           k2 = search_layer(k1, $3);
	   if (k2 >= 0)
	     get_init_elem(LAYER, $$.reftemp, k2, $5, $7);
	   else 
	     yyerror("The name of the layer does not exist on this network");
	 }
	 else yyerror("Network name does not exist");
       }

       ;
/*****************************************************************************/
op_log :  AND_       { $$ = AND; }
       |  OR_        { $$ = OR;  }
       ;
/*****************************************************************************/
op_eq  :  EQUAL_     { $$ = EQUAL;    }
       |  NOTEQUAL_  { $$ = NOTEQUAL; }
       ;
/*****************************************************************************/
op_rel :  GREAT_     { $$ = GREAT;   }
       |  GREATEQ_   { $$ = GREATEQ; }
       |  LESS_      { $$ = LESS;    }
       |  LESSEQ_    { $$ = LESSEQ;  }
       ;
/*****************************************************************************/
op_add :  MAS_       { $$ = ADDITION; }
       |  MENOS_     { $$ = SUBTRACTION; }
       ;
/*****************************************************************************/
op_mul :  POR_       { $$ = MULTIPLICATION; }
       |  DIV_       { $$ = DIVISION;       }
       |  MOD_       { $$ = MODULUS;        }
       |  PORPOR_    { $$ = EXPONET;        }
       ; 
/*****************************************************************************/
op_una :  MAS_       { $$ = ADDITION;    }
       |  MENOS_     { $$ = SUBTRACTION; }
       |  NOT_       { $$ = NOT;         }
       ;
/*****************************************************************************/
functions
       :  log_     { $$ = LOGARITHM;   }
       |  exp_     { $$ = EXPONENTIAL; }
       |  sqr_     { $$ = SQUARE;      }
       ;
%%
/*****************************************************************************/
/*****************************************************************************/
