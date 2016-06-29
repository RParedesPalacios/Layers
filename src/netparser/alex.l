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
char *createName();
char *createLiteral();

%}

%option yylineno
comentario      "//".*\n
delimitador	[ \t]+

letra 		[_a-zA-Z]
digito		[0-9]
nentero		{digito}+
nreal		({digito}+"."{digito}*)|({digito}*"."{digito}+)
identificador	{letra}({letra}|{digito})*
literal         ("/"|"."|".."|{identificador})+(\.{identificador})?
namefile        \"{literal}\"

%%	
{delimitador}   { if (verbosity) ECHO;}
{comentario}    { if (verbosity) 
                    { ECHO; fprintf(stdout,"%3d.- ", yylineno); } }
"\n"            { if (verbosity) 
                    { ECHO; fprintf(stdout,"%3d.- ", yylineno); } }

batch           { display(batch_);    }
threads         { display(threads_);  }
log             { display(log_);      }
filename        { display(filename_); }
tr              { display(tr_);       }
ts              { display(ts_);       }
va              { display(va_);       }
ascii           { display(ascii_);    }
binary          { display(binary_);   }
local           { display(local_);   }

F               { display(F_);  }
FI              { display(FI_); }
FO              { display(FO_); }
C               { display(C_);  }
CI              { display(CI_); }
MP              { display(MP_); }
CA              { display(CA_); }

classification  { display(classification_); }
regression      { display(regression_);     }
autoencoder     { display(autoencoder_);    }
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
drop            { display(drop_);       }      
l2              { display(l2_);         }      
l1              { display(l1_);         }       
maxn            { display(maxn_);       }       
act             { display(act_);        }       
noiser          { display(noiser_);     }      
noisesd         { display(noisesd_);    }     
shift           { display(shift_);      }     
flip            { display(flip_);       }     
brightness      { display(brightness_); }     
contrast        { display(contrast_);   }     
bn              { display(bn_);         } 
balance         { display(balance_);    } 
noiseb          { display(noiseb_);     } 
lambda          { display(lambda_);     } 

center          { display(center_);       }
const           { display(const_);        }
data            { display(data_);         }
div             { display(div_);          }
network         { display(network_);      }
script          { display(script_);       }
train           { display(train_);        }
printkernels    { display(printkernels_); }
save            { display(save_);         }
load            { display(load_);         }
testout         { display(testout_);      }
zscore          { display(zscore_);       }
yuv             { display(yuv_);          }

"{"             { display(BCB_);   /* Begin Curly  Brackets */ }
"}"             { display(ECB_);   /* End   Curly  Brackets */ }
"["             { display(BSB_);   /* Begin Square Brackets */ }
"]"             { display(ESB_);   /* End   Square Brackets */ }
"("             { display(BRB_);   /* Begin Round  Brackets */ }
")"             { display(ERB_);   /* End   Round  Brackets */ }
"."             { display(PER_);   /* period                */ }
","             { display(COM_);   /* comma                 */ }
"="             { display(EQ_);    /* equal                 */ }
"->"            { display(RAR_);   /* rightarrow            */ }

{nentero}       { yylval.cent  = atoi(yytext);    display(cte_);}
{nreal}	        { yylval.creal = atof(yytext);    display(ctr_);}
{identificador} { yylval.ident = createName();    display(id_); }
{namefile}      { yylval.ident = createLiteral(); display(nfile_); }
.               { yyerror("unknown character"); if (verbosity) ECHO;}
%%
/*****************************************************************************/
char *createName()
{ char *t;
  t = (char *)malloc(yyleng+1); strncpy(t, yytext, yyleng);
  t[yyleng] = '\0'; 
  return t;
}
/*****************************************************************************/
char *createLiteral()
{ char *t; int i;
  t = (char *)malloc(yyleng+1); 
  for (i = 0; (i < yyleng-2); i++) t[i] = yytext[i+1];
  t[yyleng] = '\0';
  return t;
}
/*****************************************************************************/
