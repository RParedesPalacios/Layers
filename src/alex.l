/*****************************************************************************/
/**  Lexical analyzer, 2016.                        <jmbenedi@prhlt.upv.es> **/
/*****************************************************************************/
%{
#include <stdio.h>
#include <string.h>
#include "nettable.h"
#include "asin.h"

int verbosity=FALSE;                     /* If you want to display the trace */
int numErrores=0;                        /* Counter for number of errors     */

#define  display(x) {if (verbosity) ECHO; return x;}
void createLiteral() ;
void emiteDirective() ;
void creatececho() ;
%}

%option noyywrap
%option yylineno
comentario      "//".*\n
delimitador	[ \t]+

letra 		[_a-zA-Z]
digito		[0-9]
nentero		{digito}+
nreal		({digito}+"."{digito}*)|({digito}*"."{digito}+)
constante       ({nentero}|{nreal})
identificador	{letra}({letra}|{digito})*
namefile        \"[^\0\" ]+\"
directive       "@".*\n
comecho         "echo".*\n

%%	
{delimitador}   { if (verbosity) ECHO;}
{comentario}    { if (verbosity) 
                    { ECHO; fprintf(stdout,"%3d.- ", yylineno); } }
"\n"            { if (verbosity) 
                    { ECHO; fprintf(stdout,"%3d.- ", yylineno); } }

batch           { display(batch_);    }
threads         { display(threads_);  }
log             { display(log_);      }
seed            { display(seed_);     }
cpu             { display(cpu_);      }
gpu             { display(gpu_);      }
device          { display(device_);   }
cuDNN           { display(cuDNN_);    }
cuBLAS          { display(cuBLAS_);   }

filename        { display(filename_);   } 
tr              { display(tr_);         }
ts              { display(ts_);         }
va              { display(va_);         }
ascii           { display(ascii_);      }
binary          { display(binary_);     }
gauss           { display(gauss_);      }   
uniform         { display(uniform_);    } 
ones            { display(ones_);       }   
zeros           { display(zeros_);      } 
oneshot         { display(oneshot_);    }
pos             { display(pos_);        } 
nrows           { display(nrows_);      } 
ncolsample      { display(ncolsample_); } 
ncoltarget      { display(ncoltarget_); } 
T               { display(T_);          }
S               { display(S_);          }
W               { display(W_);          }
GW              { display(GW_);         }
B               { display(B_);          }
GB              { display(GB_);         }
N               { display(N_);          }

F               { display(F_);   } 
FI              { display(FI_);  }
FO              { display(FO_);  }
C               { display(C_);   }
CI              { display(CI_);  }
MP              { display(MP_);  }
CAT             { display(CAT_); }
ADD             { display(ADD_); }
O               { display(O_);   }

classification  { display(classification_); }
regression      { display(regression_);     }
autoencoder     { display(autoencoder_);    }
max             { display(max_);            }
min             { display(min_);            }
maxlog          { display(maxlog_);         }
minlog          { display(minlog_);         }

nz              { display(nz_);             }
nr              { display(nr_);             }
nc              { display(nc_);             }
cr              { display(cr_);             }
cc              { display(cc_);             }
numnodes        { display(numnodes_);       }
nk              { display(nk_);             }
kr              { display(kr_);             }
kc              { display(kc_);             }
rpad            { display(rpad_);           }
cpad            { display(cpad_);           }
stride          { display(stride_);         }
sizer           { display(sizer_);          }
sizec           { display(sizec_);          }

mu              { display(mu_);         }
mmu             { display(mmu_);        }
l2              { display(l2_);         }      
l1              { display(l1_);         }       
maxn            { display(maxn_);       }       
drop            { display(drop_);       }      
noiser          { display(noiser_);     }      
noisesd         { display(noisesd_);    }     
brightness      { display(brightness_); }     
contrast        { display(contrast_);   }     
lambda          { display(lambda_);     } 
noiseb          { display(noiseb_);     } 
advf            { display(advf_);       } 
bn              { display(bn_);         } 
act             { display(act_);        }       
shift           { display(shift_);      }     
flip            { display(flip_);       }     
adv             { display(adv_);        } 
balance         { display(balance_);    } 
cropmode        { display(cropmode_);   } 
trainable       { display(trainable_);  } 
for             { display(for_);        } 

const           { display(const_);        }
data            { display(data_);         }

network         { display(network_);      }
script          { display(script_);       }

printkernels    { display(printkernels_); }
change          { display(change_);       }
train           { display(train_);        }
save            { display(save_);         }
load            { display(load_);         }
testout         { display(testout_);      }
forward         { display(forward_);      }
backward        { display(backward_);     }
resetstats      { display(resetstats_);   }
printerrors     { display(printerrors_);  }
reseterrors     { display(reseterrors_);  }
trainmode       { display(trainmode_);    }
testmode        { display(testmode_);     }
update          { display(update_);       }
test            { display(test_);         }
evaluate        { display(evaluate_);     }
zscore          { display(zscore_);       }
center          { display(center_);       }
yuv             { display(yuv_);          }
maxmin          { display(maxmin_);       }
shuffle         { display(shuffle_);      }
next            { display(next_);         }
imult           { display(imult_);        }
omult           { display(omult_);        }
sigmoid         { display(sigmoid_);      }
tanh            { display(tanh_);         }
relu            { display(relu_);         }
mul             { display(mul_);          }
set             { display(set_);          }
div             { display(div_);          }
add             { display(add_);          }
sub             { display(sub_);          }
store           { display(store_);        }
getstats        { display(getstats_);     }
copy            { display(copy_);         }


bin             { display(bin_);          }
int             { display(int_);          }
real            { display(real_);         }
exp             { display(exp_);          }
sqr             { display(sqr_);          }

"+"             { display(MAS_);    }
"-"             { display(MENOS_);  }
"*"             { display(POR_);    }
"/"             { display(DIV_);    }
"%"             { display(MOD_);    }
"**"            { display(PORPOR_); }
"{"             { display(BCB_);     /* Begin Curly  Brackets */ }
"}"             { display(ECB_);     /* End   Curly  Brackets */ }
"["             { display(BSB_);     /* Begin Square Brackets */ }
"]"             { display(ESB_);     /* End   Square Brackets */ }
"("             { display(BRB_);     /* Begin Round  Brackets */ }
")"             { display(ERB_);     /* End   Round  Brackets */ }
"."             { display(PER_);     /* period                */ }
":"             { display(COL_);     /* colon                 */ }
","             { display(COM_);     /* comma                 */ }
"="             { display(EQ_);      /* equal                 */ }
"->"            { display(RAR_);     /* rightarrow            */ }

{directive}     { emiteDirective();                                 }
{constante}	{ yylval.creal = atof(yytext);    display(cte_);    }
{identificador} { yylval.ident = strdup(yytext);  display(id_);     }
{namefile}      { createLiteral(); display(nfile_);                 }
{comecho}       { creatececho();   display(cecho_);                 }
.               { yyerror("unknown character"); if (verbosity) ECHO;}
%%
/*****************************************************************************/
void creatececho()
{ char *t;
  t = (char *)malloc(yyleng+1); strncpy(t, yytext, yyleng);
  t[yyleng-1] = '\0'; 
  yylval.ident = strdup(t);
  free(t);
}
/*****************************************************************************/
void createLiteral()
{ char *t; int i;
  t = (char *)malloc(yyleng-1); 
  for (i = 0; (i < yyleng-2); i++) t[i] = yytext[i+1];
  t[yyleng-2] = '\0';
  yylval.ident = strdup(t);
  free(t);
}
/*****************************************************************************/
void emiteDirective()
{ char *t; int i, l, p; 
  t = (char *)malloc(yyleng);
  for (i = 0; i < (yyleng-2); i++) t[i] = yytext[i+1]; 
  t[yyleng-2] = '\0';  
  p =  strspn(t, " \t"); l = strlen(t);
  for (i = 0; i < (l-p); i++) t[i] = t[i+p]; 
  t[l-p] = '\0'; 
  emit(t);  free(t);
}
/*****************************************************************************/
