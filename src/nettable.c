/*****************************************************************************/
/**  Functions of "nettable".                       <jmbenedi@prhlt.upv.es> **/
/*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nettable.h"
/*****************************************************************************/
#define MaxMem 150
#define MaxTdN  10          /* Maximum number of inputs in table of networks */
#define MaxTdL 100          /* Maximum number of inputs in table of layers   */
#define MaxTdD  10          /* Maximum number of inputs in table of data     */
#define MaxPar   6          /* Maximum number of parameters per layer        */
typedef struct tdnet  /*************************** Elements of network table */
{
  char *name;
  int   reftr;
  int   refts;
  int   refva;
  int   belem;                   
  int   eelem;                   
  int   start;                   
}TDNET;

typedef struct node {
   int  refnet;
  int   reflay; 
   struct node *succ;
} typenode;

typedef typenode *pnode;

typedef struct tdlay  /***************************** Elements of layer table */
{
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
  int   nsucc;
  int   nprev;
  pnode succ;    
  pnode prev;    
}TDLAY;

typedef struct tddata  /**************************** Elements of data table  */
{
  char *name;
  int   level;
  int   lfrom;
  int   lto;
  char *namefile;
  int   filetype;                   
}TDDATA;
/*****************************************************************************/
char   *mem[MaxMem];
TDNET  tdn [MaxTdN]; 
TDNET  tdnini = {"",-1,-1,-1,-1,-1,-1};
int    ptdn = 0;
TDLAY  tdl [MaxTdL]; 
TDLAY  tdlini = {"",-1,-1,-1,-1,FALSE,FALSE,-1,-1,-1,-1,-1,-1,0,0,NULL,NULL};
int    ptdl = 0;
TDDATA tdd [MaxTdD];
TDDATA tddini = {"",-1,-1,-1,"",NONE};
int    ptdd = 0;
int    pmem = 0;
int leveldata = 0;

struct Gconst {
  int batch  ;
  int threads;
  int seed;
  int gpu;
  char *log;
} gconst = {100, 4, 1234, 0, "netparser.log"};

int sn [MaxTdN];
int psn;
/*****************************************************************************/
/*****************************************************************************/
void yyerror(const char *msg)
/*  Error handling.                                                          */
{
  numErrores++;
  fprintf(stderr, "\nError at line %d: %s\n", yylineno, msg);
}
/*****************************************************************************/
void emit (char *s)
{ char *d = malloc (strlen (s) + 1); 

  strcpy (d,s); mem[pmem] = d; pmem++; 
}
/*****************************************************************************/
void dump_file()
{ FILE *fd; char *t; int i; 

  if(numErrores == 0) {
    fd = fopen ("netparser.run", "w");
    for (i=0; i < pmem; i++) fprintf(fd,"%s\n",mem[i]);
    fclose(fd);
  }
}
/*****************************************************************************/
void begin_experiment()
{ int i; 

  tdn[ptdn] = tdnini;  tdl[ptdl] = tdlini;  tdd[ptdd] = tddini;
}
/*****************************************************************************/
 void end_experiment()
{ char line[140];

  sprintf(line,"END"); emit(line);
}
/*****************************************************************************/
void insert_gconstants (int ref, int cte, char *filename)
{
  switch (ref) {
  case BATCH: { 
    gconst.batch = cte;
    break;
  }
  case THREADS: { 
    gconst.threads = cte;
    break;
  }
  case SEED: { 
    gconst.seed = cte;
    break;
  }
  case GPU: { 
    gconst.gpu = cte;
    break;
  }
  case LOG: { 
    gconst.log = filename;
    break;
  }
  }
}
/*****************************************************************************/
void inser_name_data (char *named)
{ 
  if (ptdd == MaxTdD)
    yyerror("Table of data is completely full");
  else {
    tdd[ptdd].name = named; tdd[ptdd].level = leveldata;
    ptdd++; tdd[ptdd] = tddini; 
 }
}
/*****************************************************************************/
void inser_param_data (char *namef, int cte1, int cte2)
{ int j = ptdd-1;

  if (strlen(namef) == 0) 
    if (cte2 >= 0) { 
      tdd[j].lfrom = cte1;   tdd[j].lto = cte2;
    }
    else tdd[j].filetype = cte1;  
  else tdd[j].namefile = namef; 
}
/*****************************************************************************/
void insert_name_network (char *name)
{ 
  if (ptdn == MaxTdN) 
    yyerror("Table of networks is completely full");
  else {
    tdn[ptdn].name=name;
    ptdn++; tdn[ptdn] = tdnini;
  }
}
/*****************************************************************************/
void inser_param_net_data (int cod, int ref)
{ int j=ptdn-1;
  switch (cod) {
  case tr: {
    tdn[j].reftr = ref; 
    break;
  }
  case ts: {
    tdn[j].refts = ref;
    break;
  }
  case va: {
    tdn[j].refva = ref;
    break;
  }
  }
}
/*****************************************************************************/
void insert_name_layer (char *layname, int type)
{ int k, j = ptdn-1;

  if (ptdl == MaxTdL)
    yyerror("Table of layerss is completely full");
  else {      /*   Here the layer is created in the layer table   */
      tdl[ptdl].name   = layname; tdl[ptdl].type  = type;    
      tdl[ptdl].refnet = j;       tdl[ptdl].root  = TRUE;  
      /*   Here the network table is updated   */
     if (tdn[j].belem < 0)
       tdn[j].belem = tdn[j].eelem = ptdl;
     else tdn[j].eelem = ptdl;
     ptdl++; tdl[ptdl] = tdlini;
  }
}
/*****************************************************************************/
void insert_param_layer(int cod, int val)
{
  switch (cod) {
  case 1: {
    tdl[ptdl].cte1 = val;
    break;
  }
  case 2: {
    tdl[ptdl].cte2 = val;
    break;
  }
  case 3: {
    tdl[ptdl].cte3 = val;
    break;
  }
  case 4: {
    tdl[ptdl].cte4 = val;
    break;
  }
  case 5: {
    tdl[ptdl].cte5 = val;
    break;
  }
  case 6: {
    tdl[ptdl].cte6 = val;
    break;
  }
  }
}
/*****************************************************************************/
void insert_link (int a, int b)
{ pnode p,q; 

  tdl[b].root = FALSE;
  /*   creation of successor link   */
  p = (pnode)malloc(sizeof(typenode));
  p -> refnet = tdl[b].refnet; p -> reflay = b; p -> succ = NULL;

  if (tdl[a].succ == NULL) {
    tdl[a].succ = p; tdl[a].nsucc = 1;
  }
  else {
    q = tdl[a].succ;
    while (q -> succ != NULL) q = q -> succ;
    q -> succ = p; tdl[a].nsucc++;
  }
  /*   creation of predecessor link   */
  p = (pnode)malloc(sizeof(typenode));
  p -> refnet = tdl[a].refnet; p -> reflay = a; p -> succ = NULL;

  if (tdl[b].prev == NULL) {
    tdl[b].prev = p; tdl[b].nprev = 1;
  }
  else {
    q = tdl[b].prev;
    while (q -> succ != NULL) q = q -> succ;
    q -> succ = p; tdl[b].nprev++;
  }
}
/*****************************************************************************/
int insert_net_stack (int numnet, int refnet)
{ int i, k, ok = TRUE;

  if (numnet < 0) psn = 0;
  else { sn[numnet] = refnet; psn++;  }
  return psn;
}
/*****************************************************************************/
void check_param_layer (int n)
{ int i=1, ok=TRUE;
  int aux [MaxPar] = {FALSE,FALSE,FALSE,FALSE,FALSE,FALSE}; 
 
  if (tdl[ptdl].cte1 >= 0) aux[0] = TRUE;
  if (tdl[ptdl].cte2 >= 0) aux[1] = TRUE;
  if (tdl[ptdl].cte3 >= 0) aux[2] = TRUE;
  if (tdl[ptdl].cte4 >= 0) aux[3] = TRUE;
  if (tdl[ptdl].cte5 >= 0) aux[4] = TRUE;
  if (tdl[ptdl].cte6 >= 0) aux[5] = TRUE;
  for (i = 0; ((i< n) && (ok == TRUE)); i++)
    if (aux[i] != TRUE) ok = FALSE;
  if (ok == FALSE)
    yyerror("Error, mandatory parameters incomplete.");
}
/*****************************************************************************/
int search_data (char *named)
{ int i, k=-1, ok = TRUE;

  for (i = 0; ((i < ptdd) && ok); i++)
    if (strcmp(tdd[i].name, named) == 0) 
	{ k = i; ok = FALSE; }
  return k;
}
/*****************************************************************************/
int search_layer (int refnet, char *layname)
{ int i, j, k = -1, ok = TRUE;

  if (refnet < 0) j = ptdn-1;
  else j = refnet;
  if (tdn[j].belem >= 0)
    for (i = tdn[j].belem; ((i <= tdn[j].eelem) && ok); i++)
      if (strcmp(tdl[i].name, layname) == 0) { k = i; ok = FALSE; }
  return k;
}
/*****************************************************************************/
int search_network (char *named)
{ int i, k = -1, ok = TRUE;

  for (i = 0; ((i < ptdn) && ok); i++)
    if (strcmp(tdn[i].name, named) == 0) 
	{ k = i; ok = FALSE; }
  return k;
}
/*****************************************************************************/
int search_states(char *netname, char *layname)
{ int net, k, j, lay = -1, ok = TRUE;
  /*   search of network   */
  if (strlen(netname) == 0) net = ptdn-1;
  else net = search_network (netname);    
  if (net >= 0) {    /*   search of layer   */
    lay = search_layer(net, layname);
    if (lay >= 0) 
      if (net != (ptdn-1)) {    /*   insert a virtual layer   */
	k = search_layer(ptdn-1, layname);
        if (k < 0)   /*   the layer is created in "tdl"   */
          if (ptdl == MaxTdL)
            yyerror("Table of layerss is completely full");
          else {
            tdl[ptdl].name   = layname; tdl[ptdl].type  = tdl[lay].type; 
            tdl[ptdl].refnet = net;     tdl[ptdl].root  = TRUE;
             /*   the table "tdn" is updated   */
            if (tdn[ptdn-1].belem < 0)
	      tdn[ptdn-1].belem = tdn[ptdn-1].eelem = ptdl;
            else
	      tdn[ptdn-1].eelem = ptdl;
            lay = ptdl; ptdl++; tdl[ptdl] = tdlini;
	  }
	else lay = k;
      }
      else ;
    else yyerror("The name of the layer does not exist on this network");
  }
  else yyerror("Network name does not exist");
  return lay;
}
/*****************************************************************************/
void get_gconstants()
{ char line[140];

  sprintf(line,"Const batch %d", gconst.batch);     emit(line);  
  sprintf(line,"Const threads %d", gconst.threads); emit(line);  
  sprintf(line,"Const log %s", gconst.log);         emit(line);  
  sprintf(line,"Const seed %d", gconst.seed);       emit(line);  
  sprintf(line,"Const gpu %d", gconst.gpu);         emit(line);  
}
/*****************************************************************************/
void get_data()
{ char line[140]; int i; char *aux;

  for (i = 0; (i < ptdd); i++) 
    if (tdd[i].level == leveldata) {
      if (tdd[i].filetype == ASCII) aux = "ascii";
      else aux = "binary";

      if (strlen(tdd[i].namefile) >= 0) {
	if ((tdd[i].lfrom >= 0) && (tdd[i].lto >= 0))
	  if (tdd[i].filetype != NONE)
	    sprintf(line,
		    "Data %s 3 creadata %s %s %s %s filename %s filetype %s",
		    tdd[i].name, tdn[tdl[tdd[i].lfrom].refnet].name,
		    tdl[tdd[i].lfrom].name, tdn[tdl[tdd[i].lto].refnet].name,
		    tdl[tdd[i].lto].name, tdd[i].namefile, aux);
	  else
	    sprintf(line,"Data %s 2 creadata %s %s %s %s filename %s",
		    tdd[i].name, tdn[tdl[tdd[i].lfrom].refnet].name,
		    tdl[tdd[i].lfrom].name, tdn[tdl[tdd[i].lto].refnet].name,
		    tdl[tdd[i].lto].name, tdd[i].namefile);
	else
	  if (tdd[i].filetype != NONE)
	    sprintf(line,"Data %s 2 filename %s filetype %s",
		    tdd[i].name, tdd[i].namefile, aux);
	  else
	    sprintf(line,"Data %s 1 filename %s",
		    tdd[i].name, tdd[i].namefile);
	emit(line);
      }
      else yyerror("File name is a mandatory parameters.");
    }

  leveldata++;
}
/*****************************************************************************/
void get_net_data(int n)
{ char line[140];

  sprintf(line,"data tr %s", tdd[tdn[n].reftr].name); emit(line);
  if (tdn[n].refts >= 0) 
    { sprintf(line,"data ts %s",tdd[tdn[n].refts].name); emit(line); }
  if (tdn[n].refva >= 0) 
    { sprintf(line,"data va %s",tdd[tdn[n].refva].name); emit(line); } 
}
/*****************************************************************************/
void get_net_layers (int n)
{ char line[140], line2[140]; char *aux,*aux2; int i,j;

  for (i=tdn[n].belem; (i <= tdn[n].eelem); i++) 
    if (n == tdl[i].refnet) {
      switch (tdl[i].type) {
      case F: {
        sprintf(line,"layer %s F 1 numnodes %d", tdl[i].name, tdl[i].cte1);
	emit(line);
        break;
      }
      case R: {
        break;
      }
      case FI: {
	sprintf(line,"layer %s FI 0", tdl[i].name);
	emit(line);
        break;
      }
      case FO: { 
	sprintf(line,"layer %s FO ", tdl[i].name);
	switch (tdl[i].cte1) {
	case CLASSIFICATION: {
	  sprintf(line2,"1 criterion classification");
	  break;
	}
	case REGRESSION:{
	  j = tdl[i].cte2;
	  if (j >= 0) sprintf(line2,"2 criterion regression %s %s",
			      tdn[tdl[j].refnet].name, tdl[j].name);
	  else sprintf(line2,"1 criterion regression");
	  break;
	}
	case AUTOENCODER:{
	  sprintf(line2,"2 criterion regression autoencoder 1");
	  break;
	}
	}
	strcat(line,line2);
	emit(line);
        break;
      }
      case C:  {
        sprintf(line,"layer %s C 6 nk %d kr %d kc %d", tdl[i].name, 
		tdl[i].cte1, tdl[i].cte2, tdl[i].cte3);
        if (tdl[i].cte4 >= 0) sprintf(line2," rpad %d",tdl[i].cte4);
	else sprintf(line2," rpad 0");
	strcat(line,line2);
        if (tdl[i].cte5 >= 0) sprintf(line2," cpad %d",   tdl[i].cte5);
	else sprintf(line2," cpad 0");
	strcat(line,line2);
        if (tdl[i].cte6 >= 0) sprintf(line2," stride %d", tdl[i].cte6);
        else sprintf(line2," stride 1");
	strcat(line,line2); 
        emit(line);
        break;
      }
      case CI: {
        sprintf(line,"layer %s CI 5 nz %d nr %d nc %d", tdl[i].name,
		tdl[i].cte1,tdl[i].cte2,tdl[i].cte3);
        if (tdl[i].cte4 >= 0) sprintf(line2," cr %d",   tdl[i].cte4);
	else sprintf(line2," cr %d", tdl[i].cte2);
	strcat(line,line2);
        if (tdl[i].cte5 >= 0) sprintf(line2," cc %d",   tdl[i].cte5);
	else sprintf(line2," cc %d", tdl[i].cte3);
	strcat(line,line2);
        emit(line);
        break;
      }
      case MP: {
        sprintf(line,"layer %s MP 2 sizer %d sizec %d", tdl[i].name,
		tdl[i].cte1,tdl[i].cte2);
	emit(line);
        break;
      }
      case CAT: {
        sprintf(line,"layer %s CAT 0",tdl[i].name);
	emit(line);
        break;
      }
      case ADD: {
        sprintf(line,"layer %s ADD 0",tdl[i].name);
	emit(line);
        break;
      }
      }
    }
}
/*****************************************************************************/
int is_acyclic()
{ int ok = TRUE;  int queue [MaxTdL]; int i, c, s, phq, ptq; pnode p;

  phq = ptq = 0; /*   initialize empty queue   */
  for (i = 0; i < ptdl; i++) 
    if ((tdl[i].nprev == 0) && (tdl[i].visit2 == FALSE))
      if (ptq == MaxTdL)          /* add item to the end of the queue   */
	yyerror("Queue of layerss is completely full");
      else { tdl[i].visit2 = TRUE; queue[ptq] = i; ptq++; }   /* encolar*/
    else;

  while (! (phq == ptq)) {    /* while the queue is not empty */
    c = queue[phq]; phq++;    /* remove item from the head of the queue */

    p = tdl[c].succ;
    while (p != NULL) {
	s = p -> reflay;
	tdl[s].nprev--;
	p = p -> succ;
    }

    for (i = 0; i < ptdl; i++)
      if ((tdl[i].nprev == 0) && (tdl[i].visit2 == FALSE))
	if (ptq == MaxTdL)          /* add item to the end of the queue   */
	  yyerror("Queue of layerss is completely full");
	else { tdl[i].visit2 = TRUE; queue[ptq] = i; ptq++; }
      else ;
  }
 
  for (i = 0; ((i < ptdl) && ok); i++)
    if (tdl[i].visit2 == FALSE) ok = FALSE;

  return ok;
}
/*****************************************************************************/
void get_net_links(int n, int l)
{ char line[140]; char *aux; int i,c, s,queue [MaxTdL]; pnode p; int phq, ptq;
  /*   Breadth-First-Search   */
  phq = ptq = 0; /*   initialize empty queue   */
  if (ptq == MaxTdL)          /* add item to the end of the queue   */
    yyerror("Queue of layerss is completely full");
  else { queue[ptq] = l; ptq++; }
  while (! (phq == ptq)) {    /* while the queue is not empty */
    c = queue[phq]; phq++;    /* remove item from the head of the queue */
    if (tdl[c].visit == FALSE) {
      tdl[c].visit = TRUE;
      p = tdl[c].succ;
      while (p != NULL) {
	s = p -> reflay;
  	if (ptq == MaxTdL) /* add item to the end of the queue */
	  yyerror("Queue of layerss is completely full");
        else { queue[ptq] = s; ptq++; }
        if ((tdl[s].type == R) && (tdl[s].refnet == (ptdn -1))) {
	  if (tdl[s].cte1 == 1) aux ="local 1";
	  else aux = "local 0";
	  sprintf(line,"layer %s R 2 prevlayer %s %s %s", tdl[s].name,
		  tdn[tdl[c].refnet].name, tdl[c].name, aux);
	  emit(line);
	}
	else { 
          sprintf(line,"link %s %s %s %s",tdn[tdl[c].refnet].name,
		  tdl[c].name, tdn[tdl[s].refnet].name, tdl[s].name);
	  emit(line);
	}
	p = p -> succ;
      }
    }
  }
}
/*****************************************************************************/
void get_network()
{ char line[140]; int i, k, j = ptdn-1, nsti = 0, ok = TRUE;
  /*   checking the network: initial, internal and final layers   */
  for (i = tdn[j].belem; i <= tdn[j].eelem; i++) {
    switch (tdl[i].type) {
    case FO: {
      if (!((tdl[i].nsucc >= 0) && (tdl[i].nprev > 0))) {
	ok = FALSE;
	yyerror("Error in the accessibility of final layer");
      }
      break;
    }
    case FI: case CI: {
      if ((tdl[i].nsucc > 0) && (tdl[i].nprev == 0))  {
	if (nsti == 0) {
	  tdn[j].start = i;  nsti++;
	}
	else {
	  k = tdn[j].start;
	  while (tdl[k].ninit > 0) k = tdl[k].ninit;
	  tdl[k].ninit = i; nsti++;
	}
      }
      else {
	ok = FALSE;
	yyerror("Error in the accessibility of initial layer");
      }
      break;
    }
    case C: case MP: {
      if (!((tdl[i].nsucc > 0) && (tdl[i].nprev == 1))) {
	ok = FALSE;
	yyerror("Error in the accessibility of internal layer1");
      }
      break;
    }
    case CAT: case ADD: case F: case R: {
      if (!((tdl[i].nsucc > 0) && (tdl[i].nprev > 0))) {
	ok = FALSE;
	yyerror("Error in the accessibility of internal layer2");
      }
      break;
    }
    }
  }
  if (nsti == 0)
    yyerror("Error: a network must have an initial layer");
  else if (ok == TRUE) {
    sprintf(line,"Network %s",tdn[j].name); emit(line);
    /*   getting data files of network   */
    get_net_data(j);
    /*   getting layers of network   */
    if (is_acyclic() == FALSE)
      yyerror("Error, possible loop in the network");
    get_net_layers(j);
    /*   getting links of network   */
    k = tdn[j].start;
    get_net_links(j, k);
    while (tdl[k].ninit > 0) {
      k = tdl[k].ninit;
      get_net_links(j, k);
    }
    /* end network */ 
    sprintf(line,"END_Network"); emit(line);
  }
}
/*****************************************************************************/
void get_amendment(int type, int ref, char *aux)
{ char line[140];
 
  if (type == LAYER)
    sprintf(line,"amendment %s %s %s", tdn[tdl[ref].refnet].name,
	    tdl[ref].name, aux);
  else sprintf(line,"amendment %s * %s", tdn[ref].name, aux);
  emit(line);
}
/*****************************************************************************/
void get_amendment_onlynet(int ref, int aux)
{ char line[140];
 
  if (aux == 0)
    sprintf(line,"amendment %s * cropmode 0", tdn[ref].name);
  else sprintf(line,"amendment %s * cropmode 1", tdn[ref].name);
  emit(line);
}
/*****************************************************************************/
void get_amendment_data(int ref, int aux)
{ char line[140];
  sprintf(line,"amendment %s balance %d", tdd[ref].name, aux);
  emit(line);
}
/*****************************************************************************/
char *get_amend_param_ctr(int param, float value)
{ char line[140];  char *d;

  switch (param) {
  case mu: { 
    sprintf(line,"mu %f",value);
    break;
  }
  case mmu: {
    sprintf(line,"mmu %f",value);
    break;
  }
  case l2: { 
    sprintf(line,"l2 %f",value);
    break;
  }
  case l1: { 
    sprintf(line,"l1 %f",value);
    break;
  }
  case maxn: { 
    sprintf(line,"maxn %f",value);
    break;
  }
  case drop: { 
    sprintf(line,"drop %f",value);
    break;
  }
  case noiser: { 
    sprintf(line,"noiser %f",value);
    break;
  }
  case noisesd: { 
    sprintf(line,"noisesd %f",value);
    break;
  }
  case brightness: { 
    sprintf(line,"brightness %f",value);
    break;
  }
  case contrast: { 
    sprintf(line,"contrast %f",value);
    break;
  }
  case lambda: { 
    sprintf(line,"lambda %f",value);
    break;
  }
  case noiseb: { 
    sprintf(line,"noiseb %f",value);
    break;
  }
  case advf: { 
    sprintf(line,"advf %f",value);
    break;
  }
  }
  d = malloc (strlen (line) + 1);
  strcpy (d,line);
  return d;
}
/*****************************************************************************/
char *get_amend_param_cte(int param, int value)
{ char line[140]; char *d;

  switch (param) {
  case bn: { 
    sprintf(line,"bn %d",value);
    break;
  }
  case act: { 
    sprintf(line,"act %d",value);
    break;
  }
  case shift: { 
    sprintf(line,"shift %d",value);
    break;
  }
  case flip: { 
    sprintf(line,"flip %d",value);
    break;
  }
  case adv: { 
    sprintf(line,"adv %d",value);
    break;
  }
  case balance: { 
    sprintf(line,"balance %d",value);
    break;
  }
  }
  d = malloc (strlen (line) + 1); 
  strcpy (d,line);
  return d;
}
/*****************************************************************************/
void get_printkernels (int refn, int refl, char *aux)
{ char line[140]; 

  sprintf(line,"command %s %s printkernels 1 %s", tdn[refn].name, 
	  tdl[refl].name, aux);
  emit(line);
}
/*****************************************************************************/
void get_copy (int refnd, int refld, int refns, int refls)
{ char line[140]; 

  sprintf(line,"command %s %s copy %s %s", tdn[refnd].name, 
	  tdl[refld].name, tdn[refns].name, tdl[refls].name);
  emit(line);
}
/*****************************************************************************/
void get_train (int par1, int par2, int par3, int ref)
{ char line[140]; int i;

  sprintf(line,"command list train numiter %d numnet %d", par1, ref);
  emit(line);
  for (i = 0; (i < ref); i++) {
    sprintf(line,"command %s train 2 nepoch %d numbatch %d", 
	    tdn[sn[i]].name, par2, par3);
    emit(line);
  }
  sprintf(line,"command list train start");
  emit(line);
}
/*****************************************************************************/
void get_net_train (int refn, int par) 
{ char line[140];
 
  sprintf(line,"command %s train 1 nepoch %d",tdn[refn].name, par);
  emit(line);
}
/*****************************************************************************/
void get_net_test (int ref1, int ref2) 
{ char line[140], line2[140]; 

  if (ref2 < 0) sprintf(line2,"0");
  else  sprintf(line2,"1 %s",tdd[ref2].name);
  sprintf(line,"command %s test %s", tdd[ref1].name, line2);
  emit(line);
}
/*****************************************************************************/
void get_net_evaluate (int ref1, int ref2) 
{ char line[140];

  sprintf(line,"command %s evaluate 1 %s", tdn[ref1].name, tdd[ref2].name);
  emit(line);
}
/*****************************************************************************/
void get_save (int ref, char *aux)
{ char line[140]; 

  sprintf(line,"command %s save 1 %s", tdn[ref].name, aux);
  emit(line);
}
/*****************************************************************************/
void get_load (int ref, char *aux)
{ char line[140]; 

  sprintf(line,"command %s load 1 %s", tdn[ref].name, aux);
  emit(line);
}
/*****************************************************************************/
void get_testout (int ref, char *aux)
{ char line[140]; 

  sprintf(line,"command %s testout 1 %s", tdn[ref].name, aux);
  emit(line);
}
/*****************************************************************************/
void get_zscore (int ref1, int ref2)
{ char line[140], line2[140]; 

  if (ref2 < 0) sprintf(line2,"0");
  else  sprintf(line2,"1 %s",tdd[ref2].name);
  sprintf(line,"command %s zscore %s", tdd[ref1].name, line2);
  emit(line);
}
/*****************************************************************************/
void get_center (int ref1, int ref2)
{ char line[140], line2[140]; 

  if (ref2 < 0) sprintf(line2,"0");
  else  sprintf(line2,"1 %s",tdd[ref2].name);
  sprintf(line,"command %s center %s", tdd[ref1].name, line2);
  emit(line);
}
/*****************************************************************************/
void get_yuv (int ref1)
{ char line[140]; 

  sprintf(line,"command %s yuv 0",tdd[ref1].name);
  emit(line);
}
/*****************************************************************************/
void get_div (int ref1, float aux)
{ char line[140]; 

  sprintf(line,"command %s div 1 %f",tdd[ref1].name, aux);
  emit(line);
}
/*****************************************************************************/
void get_add (int ref1, float aux)
{ char line[140]; 

  sprintf(line,"command %s add 1 %f",tdd[ref1].name, aux);
  emit(line);
}
/*****************************************************************************/
void get_sub (int ref1, float aux)
{ char line[140]; 

  sprintf(line,"command %s sub 1 %f",tdd[ref1].name, aux);
  emit(line);
}
/*****************************************************************************/
void get_mul (int ref1, float aux)
{ char line[140]; 

  sprintf(line,"command %s mul 1 %f",tdd[ref1].name, aux);
  emit(line);
}
/*****************************************************************************/
void get_maxmin (int ref1)
{ char line[140]; 

  sprintf(line,"command %s maxmin 0",tdd[ref1].name);
  emit(line);
}
/*****************************************************************************/
void get_store (int ref1, char *aux)
{ char line[140]; 

  sprintf(line,"command %s store 1 %s",tdd[ref1].name, aux);
  emit(line);
}
/*****************************************************************************/
int netparser (char *nfich) 
/* Manages the command line and invokes the syntactic-semantic analyzer.     */
{ int i, n = 0; char line[140]; FILE *fe;

  sprintf(line,"rm netparser.run 2>/dev/null"); system(line);
  if ((yyin = fopen (nfich, "r")) == NULL) {
    fprintf (stderr, "Invalid file: %s\n", nfich);
    exit(1);      
  }
  else {        
    yyparse (); dump_file(); 

    fe=fopen("netparser.run","rt");
    if (fe == NULL) { /* parser failed */
      fprintf(stdout,"%3d.- ", yylineno); yyparse ();
      fprintf(stdout,"\n");               dump_file(); 
      exit(1);
    }
    fclose(fe);
  }
}
/*****************************************************************************/
/*****************************************************************************/
