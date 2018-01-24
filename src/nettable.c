/*****************************************************************************/
/**  Functions of "nettable".                       <jmbenedi@prhlt.upv.es> **/
/*****************************************************************************/
#include <stdio.h>
#include <limits.h> 
#include <stdlib.h>
#include <string.h>
#include "nettable.h"
/*****************************************************************************/
struct Gconst {   /*************************************** General Constants */
  int  batch;
  int  threads;
  int  seed;
  int  device;
  int  cuDNN;
  int  cuBLAS;
  char *log;
} gconst = {100, 4, 1234, -1, 0, 1, "netparser.log"};

TDDATA tdd [MaxTdD]; /******************************************* Data Table */
TDDATA tddini = {"",-1,NONE,NONE,"",NONE,-1,-1,-1,-1,-1};
int    ptdd = 0;
int    leveldata = 0;

TDNET  tdn [MaxTdN]; /**************************************** Network Table */
TDNET  tdnini = {"",-1,NONE,-1,NONE,-1,NONE,-1,-1,-1};
int    ptdn = 0;

TDLAY  tdl [MaxTdL]; /****************************************** Layer Table */
TDLAY  tdlini = {"", -1, -1, -1, -1, FALSE, FALSE, INT_MIN, INT_MIN, INT_MIN, 
		 INT_MIN, INT_MIN, INT_MIN, INT_MIN, 0, 0, NULL, NULL};
int    ptdl = 0;

char   *mem[MaxMem]; /*********************************************** Memory */
int    pmem = 0;

int      pstv = 1;        /**** Pointer to the segment of temporal variables */
ptsymbol ptnames = NULL;  /************************** head to the name table */
int      fcteneg = FALSE;

TDMACRO  tdm [MaxTdM];    /*************************** Remplace: Macro Table */
int      ptdm = 0;

FILE *fc; FILE *fd;                    /* Remplace: file names: input output */
int ismacro = FALSE, dump = TRUE, numlin = 0;                    /* Remplace */
/*****************************************************************************/
/***************************** general constants *****************************/
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
  case DEVICE: { 
    gconst.device = cte;
    break;
  }
  case CUDNN: { 
    gconst.cuDNN = cte;
    break;
  }
  case CUBLAS: { 
    gconst.cuBLAS = cte;
    break;
  }
  case LOG: { 
    gconst.log = filename;
    break;
  }
  }
}
/*****************************************************************************/
void get_gconstants()
{ char line[140];
  sprintf(line,"Const batch %d", gconst.batch);     emit(line);  
  sprintf(line,"Const threads %d", gconst.threads); emit(line);  
  sprintf(line,"Const seed %d", gconst.seed);       emit(line);  
  if (gconst.device < 0) 
    { sprintf(line,"Const device cpu"); emit(line);  }
  else { sprintf(line,"Const device gpu%d", gconst.device); emit(line); }
  sprintf(line,"Const cuDNN %d", gconst.cuDNN);     emit(line); 
  sprintf(line,"Const cuBLAS %d", gconst.cuBLAS);   emit(line); 
  sprintf(line,"Const log %s", gconst.log);         emit(line);  
}
/*****************************************************************************/
/****************************** data definition ******************************/
/*****************************************************************************/
int search_data (char *named)
{ int i, k = -1, ok = TRUE;

  for (i = 0; ((i < ptdd) && ok); i++)
    if (strcmp(tdd[i].name, named) == 0) 
      { k = i; ok = FALSE; }
  return k;
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
void inser_param_data (int cod, char *namef, int cte1, int cte2, int cte3)
{ int j = ptdd-1;

  switch (cod) {
  case FILES: {
    tdd[j].type = FILES;
    if (strlen(namef) == 0) tdd[j].filetype = cte1;  
    else tdd[j].namefile = namef;  
    break;
  }
  case GENERATED: {
    tdd[j].type = GENERATED;
    if (cte1 > 0) tdd[j].gentype  = cte1; 
    if (cte2 > 0) tdd[j].numnodes = cte2;
    if (cte3 > 0) tdd[j].pos      = cte3;
    break;
  }
  case CREADATA: {
    tdd[j].type = CREADATA;
    if (cte1 > 0) tdd[j].nrows      = cte1; 
    if (cte2 >= 0) tdd[j].ncolsample = cte2;
    if (cte3 >= 0) tdd[j].ncoltarget = cte3;
    break;
  }
  }
}
/*****************************************************************************/
void check_param_data (int cod)
{ int j = ptdd-1;

  switch (cod) {
  case FILES: {
    if (tdd[j].filetype == NONE) tdd[j].filetype=BINARY;
    if (strlen(tdd[j].namefile) == 0)
      yyerror("File name is mandatory");
    break;
  }
  case GENERATED: {
    if (tdd[j].gentype == NONE)
      yyerror("The type of generated file is mandatory");
    if (tdd[j].numnodes < 0)
      yyerror("The number of nodes is mandatory");
    if ((tdd[j].gentype != ONESHOT) && (tdd[j].pos >= 0))
      yyerror("Only for 'oneshot' is possible the additional constant");
    break;
  }
  case CREADATA: {
    if (tdd[j].nrows < 0)
      yyerror("The number of rows is mandatory");
    if (tdd[j].ncolsample < 0)
      yyerror("The number of columns of the sample is mandatory");
    if (tdd[j].ncoltarget < 0)
      yyerror("The number of columns of the target is mandatory");
    break;
  }
  }
}
/*****************************************************************************/
void get_data()
{ char line[140]; int i; char *aux;

  for (i = 0; (i < ptdd); i++) 
    if (tdd[i].level == leveldata) {
      switch (tdd[i].type) {
      case FILES: {
        if (tdd[i].filetype == ASCII) aux = "ascii";
        else aux = "binary";
        sprintf(line,"Data F %s %s %s", tdd[i].name, aux, tdd[i].namefile);
        break;
      }
      case GENERATED: {
        switch (tdd[i].gentype) {
	case GAUSS:   { aux = "gauss";   break; }
	case UNIFORM: { aux = "uniform"; break; }
	case ONES:    { aux = "ones";    break; }
	case ZEROS:   { aux = "zeros";   break; }
	case ONESHOT: { aux = "oneshot"; break; }
	}
	sprintf(line,"Data G %s %s %d %d", tdd[i].name, aux,
		tdd[i].numnodes, tdd[i].pos);
        break;
      }
      case CREADATA: {
        sprintf(line,"Data C %s %d %d %d", tdd[i].name, tdd[i].nrows, 
		tdd[i].ncolsample, tdd[i].ncoltarget);
        break;
      }
      }
      emit(line);
    }
  leveldata++;
}
/*****************************************************************************/
int inser_new_name_data (char *named)
{ 
  if (ptdd == MaxTdD)
    yyerror("Table of data is completely full");
  else {
    tdd[ptdd].name  = named; 
    tdd[ptdd].level = leveldata;
    tdd[ptdd].type  = CREADATA;
    ptdd++; tdd[ptdd] = tddini; 
  }
  return ptdd-1;
}
/*****************************************************************************/
/******************************* network data ********************************/
/*****************************************************************************/
void inser_param_net_data (int cod, int ref)
{ int j=ptdn-1;

  switch (cod) {
  case TR: {
    tdn[j].reftr = ref; 
    break;
  }
  case TS: {
    tdn[j].refts = ref; 
    break;
  }
  case VA: {
    tdn[j].refva = ref; 
    break;
  }
  }
}
/*****************************************************************************/
 void get_net_data()
 { int n = ptdn-1; char line[140]; char *aux1;

  sprintf(line,"Network %s",tdn[n].name); emit(line);

  if (tdn[n].reftr >= 0) { 
    if (tdd[tdn[n].reftr].type == FILES) aux1="F";
    else if (tdd[tdn[n].reftr].type == GENERATED) aux1="G"; 
    else aux1="C";
    sprintf(line,"data tr %s %s", aux1, tdd[tdn[n].reftr].name); 
    emit(line); 
  }
  if (tdn[n].refts >= 0) { 
    if (tdd[tdn[n].refts].type == FILES) aux1="F";
    else if (tdd[tdn[n].refts].type == GENERATED) aux1="G";
    else aux1="C"; 
    sprintf(line,"data ts %s %s", aux1, tdd[tdn[n].refts].name); 
    emit(line); 
  }
  if (tdn[n].refva >= 0) { 
    if (tdd[tdn[n].refva].type == FILES) aux1="F";
    else if (tdd[tdn[n].refva].type == GENERATED) aux1="G";
    else aux1="C";
    sprintf(line,"data va %s %s", aux1, tdd[tdn[n].refva].name); 
    emit(line); 
  }
}
/*****************************************************************************/
/******************************* network layers ******************************/
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
{ int j=ptdl;

  switch (cod) {
  case 1: {
    tdl[j].cte1 = val;
    break;
  }
  case 2: {
    tdl[j].cte2 = val;
    break;
  }
  case 3: {
    tdl[j].cte3 = val;
    break;
  }
  case 4: {
    tdl[j].cte4 = val;
    break;
  }
  case 5: {
    tdl[j].cte5 = val;
    break;
  }
  case 6: {
    tdl[j].cte6 = val;
    break;
  }
  case 7: {
    tdl[j].cte7 = val;
    break;
  }
  }
}
/*****************************************************************************/
 void check_param_layer (int n)
{ int i=1, ok=TRUE;
  int aux [MaxPar] = {FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE}; 
 
  if (tdl[ptdl].cte1 > INT_MIN) aux[0] = TRUE;
  if (tdl[ptdl].cte2 > INT_MIN) aux[1] = TRUE;
  if (tdl[ptdl].cte3 > INT_MIN) aux[2] = TRUE;
  if (tdl[ptdl].cte4 > INT_MIN) aux[3] = TRUE;
  if (tdl[ptdl].cte5 > INT_MIN) aux[4] = TRUE;
  if (tdl[ptdl].cte6 > INT_MIN) aux[5] = TRUE;
  if (tdl[ptdl].cte7 > INT_MIN) aux[6] = TRUE;
  for (i = 0; ((i< n) && (ok == TRUE)); i++)
    if (aux[i] != TRUE) ok = FALSE;
  if (ok == FALSE)
    yyerror("Error, mandatory parameters incomplete.");
}
/*****************************************************************************/
 void get_net_layers (int n)
{ char line[140], line2[140]; char *aux,*aux2; int i,j;

  for (i=tdn[n].belem; (i <= tdn[n].eelem); i++) 
  if (n == tdl[i].refnet) 
      switch (tdl[i].type) {
      case F: {
        sprintf(line,"layer %s F numnodes %d", tdl[i].name, tdl[i].cte1);
	emit(line);
        break;
      }
      case R: {
	j = tdl[i].cte1;
        sprintf(line,"layer %s R %s %s", tdl[i].name, 
		tdn[tdl[j].refnet].name, tdl[j].name);
	emit(line);
        break;
	}
      case FI: {
	sprintf(line,"layer %s FI", tdl[i].name);

 	j = tdl[i].cte1;
	if (j > INT_MIN) 
	  sprintf(line2, " %s %s", tdn[tdl[j].refnet].name,
		  tdl[j].name);
	else sprintf(line2, " NULL NULL");
	strcat(line,line2);

        j = tdl[i].cte2;
	if (j > INT_MIN) 
	  sprintf(line2," %s", tdd[j].name);
	else  sprintf(line2," NULL");
	strcat(line,line2);

	emit(line);
        break;
      }
      case CI: {
        sprintf(line,"layer %s CI nz %d nr %d nc %d", tdl[i].name,
		tdl[i].cte1, tdl[i].cte2, tdl[i].cte3);
        if (tdl[i].cte4 > INT_MIN) sprintf(line2," cr %d", tdl[i].cte4);
	else sprintf(line2," cr %d", tdl[i].cte2);
	strcat(line,line2);
        if (tdl[i].cte5 > INT_MIN) sprintf(line2," cc %d", tdl[i].cte5);
	else sprintf(line2," cc %d", tdl[i].cte3);
	strcat(line,line2);

 	j = tdl[i].cte6;
	if (j > INT_MIN) 
	  sprintf(line2, " %s %s", tdn[tdl[j].refnet].name,
		  tdl[j].name);
	else sprintf(line2, " NULL NULL");
	strcat(line,line2);

        j = tdl[i].cte7;
	if (j > INT_MIN) 
	  sprintf(line2," %s", tdd[j].name);
	else  sprintf(line2," NULL");
	strcat(line,line2);

        emit(line);
        break;
	}
      case FO: { 
        switch (tdl[i].cte1) {
        case CLASSIFICATION: { aux = "classification"; break; }
	case REGRESSION:     { aux = "regression";     break; }
	case AUTOENCODER:    { aux = "autoencoder";    break; }
	case MAX:            { aux = "max";            break; }
	case MIN:            { aux = "min";            break; }
	case MAXLOG:         { aux = "maxlog";         break; }
	case MINLOG:         { aux = "minlog";         break; }
	}
	sprintf(line, "layer %s FO %s", tdl[i].name, aux);

	j = tdl[i].cte2;
	if (j > INT_MIN) 
	  sprintf(line2, " %s %s", tdn[tdl[j].refnet].name,
		  tdl[j].name);
	else sprintf(line2, " NULL NULL");
	strcat(line,line2);

        j = tdl[i].cte3;
	if (j > INT_MIN) 
	  sprintf(line2," %s", tdd[j].name);
	else  sprintf(line2," NULL");
	strcat(line,line2);

	emit(line);
        break;
      }
      case C:  {
        sprintf(line,"layer %s C nk %d kr %d kc %d", tdl[i].name, 
		tdl[i].cte1, tdl[i].cte2, tdl[i].cte3);
        if (tdl[i].cte4 > INT_MIN) sprintf(line2," rpad %d",tdl[i].cte4);
	else sprintf(line2," rpad 0");
	strcat(line,line2);
        if (tdl[i].cte5 > INT_MIN) sprintf(line2," cpad %d",   tdl[i].cte5);
	else sprintf(line2," cpad 0");
	strcat(line,line2);
        if (tdl[i].cte6 > INT_MIN) sprintf(line2," stride %d", tdl[i].cte6);
        else sprintf(line2," stride 1");
	strcat(line,line2); 
        emit(line);
        break;
      }
      case MP: {
        sprintf(line,"layer %s MP sizer %d sizec %d", tdl[i].name,
		tdl[i].cte1,tdl[i].cte2);
	emit(line);
        break;
	}
      case CAT: {
        sprintf(line,"layer %s CAT",tdl[i].name);
	emit(line);
        break;
      }
      case ADD: {
        sprintf(line,"layer %s ADD",tdl[i].name);
	emit(line);
        break;
      }
      case O: {
        switch (tdl[i].cte1) {
        case ADDITION:    { aux = "add";     break; }
        case SUBTRACTION: { aux = "sub";     break; }
        case DIVISION:    { aux = "div";     break; }
        case INNERMULT:   { aux = "imult";   break; }
        case OUTERMULT:   { aux = "omult";   break; }
        case SIGMOID:     { aux = "sigmoid"; break; }
        case TANH:        { aux = "tanh";    break; }
        case LOGARITHM:   { aux = "log";     break; }
        case RELU:        { aux = "relu";    break; }
	}
      	sprintf(line, "layer %s O %s", tdl[i].name, aux);
	emit(line);
        break;
      }
      }
}
/*****************************************************************************/
/**************************** network links **********************************/
/*****************************************************************************/
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
  /* reshape control: insert param layer R */
  if ((tdl[b].type == R) && (tdl[b].refnet == (ptdn -1))) 
    tdl[b].cte1 = a;
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
{ char line[140]; int i,c, s,queue [MaxTdL]; pnode p; int phq, ptq;
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

        sprintf(line,"link %s %s %s %s",tdn[tdl[c].refnet].name,
		  tdl[c].name, tdn[tdl[s].refnet].name, tdl[s].name);
	  emit(line);
	p = p -> succ;
      }
    }
  }
}
/*****************************************************************************/
/******************************* network *************************************/
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
int search_network (char *named)
{ int i, k = -1, ok = TRUE;

  for (i = 0; ((i < ptdn) && ok); i++)
    if (strcmp(tdn[i].name, named) == 0) 
	{ k = i; ok = FALSE; }
  return k;
}
/*****************************************************************************/
 void get_network()
{ char line[140]; int i, k, j = ptdn-1, nsti = 0, ok = TRUE;
  /*   checking the network: initial, internal and final layers   */
  for (i = tdn[j].belem; i <= tdn[j].eelem; i++) {
    switch (tdl[i].type) {
    case FO: {
      if (!((tdl[i].nsucc >= 0) && (tdl[i].nprev > 0))) {
	/* ok = FALSE; */
        /* yyerror("Error in the accessibility of final layer"); */
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
	/* ok = FALSE; */
	/* yyerror("Error in the accessibility of initial layer"); */
      }
      break;
    }
    case C: case MP: {
      if (!((tdl[i].nsucc > 0) && (tdl[i].nprev == 1))) {
	/* ok = FALSE; */
	/* yyerror("Error in the accessibility of internal layer1"); */
      }
      break;
    }
    case CAT: case ADD: case F: case R: {
      if (!((tdl[i].nsucc > 0) && (tdl[i].nprev > 0))) {
	/* ok = FALSE; */
	/* yyerror("Error in the accessibility of internal layer2"); */
      }
      break;
    }
    }
  }
  if (nsti == 0)
    yyerror("Error: a network must have an initial layer");
  else if (ok == TRUE) {
    /* sprintf(line,"Network %s",tdn[j].name); emit(line); */
    /*   getting data files of network   */
    /*    get_net_data(j); */
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
    sprintf(line,"EndNetwork"); emit(line);
  }
}
/*****************************************************************************/
/********************************* amendment *********************************/
/*****************************************************************************/
void get_amendment(int type, int ref, int cod, EXPRE value)
{ char line[140], opd[140]; char *aux;

  strexpre(opd,value);
  switch (cod) {
    case mu:         { aux = "mu";         break; }
    case mmu:        { aux = "mmu";        break; }
    case l2:         { aux = "l2";         break; }
    case l1:         { aux = "l1";         break; }
    case maxn:       { aux = "maxn";       break; }
    case drop:       { aux = "drop";       break; }
    case noiser:     { aux = "noiser";     break; }
    case noisesd:    { aux = "noisesd";    break; }
    case brightness: { aux = "brightness"; break; }
    case contrast:   { aux = "contrast";   break; }
    case lambda:     { aux = "lambda";     break; }
    case noiseb:     { aux = "noiseb";     break; }
    case advf:       { aux = "advf";       break; }
    case bn:         { aux = "bn";         break; }
    case act:        { aux = "act";        break; }
    case shift:      { aux = "shift";      break; }
    case flip:       { aux = "flip";       break; }
    case adv:        { aux = "adv";        break; }
    case cropmode:   { aux = "cropmode";   break; }
    case balance:    { aux = "balance";    break; }
    case trainable : { aux = "trainable";  break; }
  }
  switch (type) {
  case DATA: {
    if (cod == balance) 
      sprintf(line,"amendment data %s balance %s", tdd[ref].name, opd);
    else yyerror("Parameter is not allowed for data");
    break;
  }
  case LAYER: {
    if ((cod == cropmode)||(cod == balance)) 
      yyerror("Parameter is not allowed for layers");
    else 
      sprintf(line,"amendment layer %s %s %s %s", tdn[tdl[ref].refnet].name,
	      tdl[ref].name, aux, opd);
    break;
  }
  case NETWORK: {
    sprintf(line,"amendment network %s %s %s", tdn[ref].name, aux, opd);
    break;
  }
  }
  emit(line);
}
/*****************************************************************************/
/********************************* command ***********************************/
/*****************************************************************************/
void get_echo(char *aux)
{ char line[140]; 

  sprintf(line,"command %s", aux);
  emit(line);
}
/*****************************************************************************/
void get_if(EXPRE exp1)
{ char line[140], opd1[140];

  strexpre(opd1, exp1); 
  sprintf(line, "command If %s", opd1);
  emit(line);
}
/*****************************************************************************/
void get_else()
{ char line[140];

  sprintf(line,"command Else");
  emit(line);
}
/*****************************************************************************/
void get_endif()
{ char line[140];

  sprintf(line,"command EndIf");
  emit(line);
}
/*****************************************************************************/
void get_for(ptsymbol s, EXPRE exp1, EXPRE exp2, EXPRE exp3)
{ char line[140], opd1[140], opd2[140], opd3[140];

  strexpre(opd1, exp1); strexpre(opd2, exp2); strexpre(opd3, exp3);
  sprintf(line, "command For %s %s %s %s", s->ident, opd1, opd2, opd3);
  emit(line);
}
/*****************************************************************************/
void get_endfor()
{ char line[140];

  sprintf(line,"command EndFor");
  emit(line);
}
/*****************************************************************************/
/****************************** command layers *******************************/
/*****************************************************************************/
void get_com_lay_file(int refn, int refl, int cod, char *nfil)
{ char line[140]; char *aux;

  if (cod == printkernels) aux ="printkernels";
  sprintf(line,"command layer %s %s %s %s", aux, tdn[refn].name, 
	  tdl[refl].name, nfil);
  emit(line);
}
/*****************************************************************************/
void get_com_lay_datlay(int refnd, int refld, int cod, int refns, int refls)
{ char line[140]; char *aux;

  if (cod == change) aux ="change";
  if ( (tdl[refld].type == FI) || (tdl[refld].type == CI)||
       (tdl[refld].type == FO) ) {
    if (refls < 0)
      sprintf(line,"command layer %s %s %s NULL NULL %s", aux, tdn[refnd].name,
	      tdl[refld].name, tdd[refns].name);
    else 
      sprintf(line,"command layer %s %s %s %s %s NULL", aux, tdn[refnd].name,
	      tdl[refld].name, tdn[refns].name, tdl[refls].name);
    emit(line);
  }
  else yyerror("Destination layer type not allowed for this command");
}
/*****************************************************************************/
void get_com_lay_copy(int ref1, int ref2, int cod, char *aux)
{ char line[140]; char *aux2;

  if (cod == copy) aux2 ="copy";
  sprintf(line,"command layer %s %s %s %s", aux2, tdn[ref1].name, 
	  tdl[ref2].name, aux);
  printf("#########################[%s] %d\n",line,(int)strlen(line));

  emit(line);
}
/*****************************************************************************/
/***************************** command networks ******************************/
/*****************************************************************************/
void get_com_net_void (int ref, int cod)
{ char line[140]; char *aux;

  switch (cod) {
  case forward:     {aux = "forward";     break;}
  case backward:    {aux = "backward";    break;}
  case resetstats:  {aux = "resetstats";  break;}
  case printerrors: {aux = "printerrors"; break;}
  case reseterrors: {aux = "reseterrors"; break;}
  case trainmode:   {aux = "trainmode";   break;}
  case testmode:    {aux = "testmode";    break;}
  case update:      {aux = "update";      break;}
  }
  sprintf(line,"command network %s %s", aux, tdn[ref].name);
  emit(line);
}
/*****************************************************************************/
void get_com_net_file(int ref, int cod, char *nfil)
{ char line[140];  char *aux;

  switch (cod) {
  case load:    {aux = "load";    break;}
  case save:    {aux = "save";    break;}
  case testout: {aux = "testout"; break;}
  }
  sprintf(line,"command network %s %s %s", aux, tdn[ref].name, nfil);
  emit(line);
}
/*****************************************************************************/
void get_com_net_dat(int ref1, int cod, int ref2) 
{ char line[140]; char *aux;

  if (cod == test) aux = "test"; else aux = "evaluate";
  if (ref2 >= 0)
    sprintf(line,"command network %s %s %s", aux, tdn[ref1].name,  
	    tdd[ref2].name);
  else sprintf(line, "command network %s %s NULL", aux, tdn[ref1].name);
  emit(line);
}
/*****************************************************************************/
void get_com_net_exp (int ref, int cod, EXPRE val) 
{ char line[140], opd[140]; char *aux;

  strexpre(opd, val);
  if (cod == train) aux ="train";
  sprintf(line,"command network %s %s %s", aux, tdn[ref].name, opd);
  emit(line);
}
/*****************************************************************************/
/******************************* command data ********************************/
/*****************************************************************************/
void get_com_data_void_rank(int ref, RANGO r, int cod)
{ char line[140], opd1[140], opd2[140], opd3[140], opd4[140]; char *aux,*aux2;

  switch (cod) {
  case zscore:   {aux = "zscore";  break;}
  case center:   {aux = "center";  break;}
  case yuv:      {aux = "yuv";     break;}
  case maxmin:   {aux = "maxmin";  break;}
  default: yyerror("This command does not support a rank");
  }
  strexpre(opd1,r.row.ini); strexpre(opd2,r.row.fin); 
  strexpre(opd3,r.col.ini); strexpre(opd4,r.col.fin);

  if (r.col.aux < 0) aux2 = "NONE";
  else 
    switch (r.col.aux) {
    case (REAL):   {aux2 = "REAL";   break;}
    case (BIN):    {aux2 = "BIN";    break;}
    case (INT):    {aux2 = "INT";    break;}
    case (TARGET): {aux2 = "TARGET"; break;}
    case (SAMPLE): {aux2 = "SAMPLE"; break;}
    }
  sprintf(line, "command data %s %s %s %s %s %s %s", aux, tdd[ref].name,
	  opd1, opd2, opd3, opd4, aux2 );
  emit(line);
}
/*****************************************************************************/
void get_com_data_void(int ref, int cod)
{ char line[140], opd[140]; char *aux; EXPRE e; 

  switch (cod) {
  case zscore:   {aux = "zscore";  break;}
  case center:   {aux = "center";  break;}
  case yuv:      {aux = "yuv";     break;}
  case maxmin:   {aux = "maxmin";  break;}
  case shuffle:  {aux = "shuffle"; break;}
  case next:     {aux = "next";    break;}
  }
  e.psymbol = NULL;  e.reftemp = cr_var_temp_cte_1();
  strexpre(opd, e);

  if ((cod==shuffle)||(cod==next)) 
    sprintf(line, "command data %s %s", aux, tdd[ref].name);
  else 
    sprintf(line, "command data %s %s %s %s %s %s NONE", aux,
	    tdd[ref].name,opd, opd, opd, opd);
  emit(line);
}
/*****************************************************************************/
void get_com_data_file(int ref, int cod, char *valor)
{ char line[140], opd[140]; char *aux;

  if (cod == store) aux ="store";
  sprintf(line, "command data %s %s %s", aux, tdd[ref].name, valor);
  emit(line);
}
/*****************************************************************************/
void get_com_data_dat(int ref, int cod, int ref2)
{ char line[140], opd[140];  char *aux;

  if (cod == getstats) aux ="getstats";
  sprintf(line, "command data %s %s %s", aux, tdd[ref].name, tdd[ref2].name);
  emit(line);
}
/*****************************************************************************/
void get_com_data_exp_rank(int ref, RANGO r, int cod, EXPRE val)
{ char line[140], opd[140], opd1[140], opd2[140], opd3[140], opd4[140]; 
  char *aux,*aux2;

  strexpre(opd,val);
  switch (cod) {
  case (multiplication): {aux = "mul"; break; }
  case (division):       {aux = "div"; break; }
  case (addition):       {aux = "add"; break; }
  case (subtraction):    {aux = "sub"; break; }
  case (set):            {aux = "set"; break; }
  }
  strexpre(opd1,r.row.ini); strexpre(opd2,r.row.fin); 
  strexpre(opd3,r.col.ini); strexpre(opd4,r.col.fin);

  if (r.col.aux < 0) aux2 = "NONE";
  else 
    switch (r.col.aux) {
    case (REAL):   {aux2 = "REAL";   break;}
    case (BIN):    {aux2 = "BIN";    break;}
    case (INT):    {aux2 = "INT";    break;}
    case (TARGET): {aux2 = "TARGET"; break;}
    case (SAMPLE): {aux2 = "SAMPLE"; break;}
    }
  sprintf(line, "command data %s %s %s %s %s %s %s %s", aux, tdd[ref].name,
	  opd1, opd2, opd3, opd4, aux2, opd);
  emit(line);
}
/*****************************************************************************/
void get_com_data_exp (int ref, int cod, EXPRE val)
{ char line[140], opd[140], opd1[140];  char *aux; EXPRE e; 

  strexpre(opd1,val);
  switch (cod) {
  case (multiplication): {aux = "mul"; break; }
  case (division):       {aux = "div"; break; }
  case (addition):       {aux = "add"; break; }
  case (subtraction):    {aux = "sub"; break; }
  case (set):            {aux = "set"; break; }
  }
  e.psymbol = NULL;  e.reftemp = cr_var_temp_cte_1();
  strexpre(opd, e);
  sprintf(line, "command data %s %s %s %s %s %s NONE %s", aux, tdd[ref].name,
	  opd, opd, opd, opd, opd1);
  emit(line);
}
/*****************************************************************************/
void get_com_data_copy_rank(int ref, RANGO r, int cod, char *aux)
{ char line[140], opd1[140], opd2[140], opd3[140], opd4[140]; 
  char *aux1, *aux2;

  if (cod == copy) aux1 ="copy";
  strexpre(opd1,r.row.ini); strexpre(opd2,r.row.fin); 
  strexpre(opd3,r.col.ini); strexpre(opd4,r.col.fin);
  if (r.col.aux < 0) aux2 = "NONE";
  else 
    switch (r.col.aux) {
    case (REAL):   {aux2 = "REAL";   break;}
    case (BIN):    {aux2 = "BIN";    break;}
    case (INT):    {aux2 = "INT";    break;}
    case (TARGET): {aux2 = "TARGET"; break;}
    case (SAMPLE): {aux2 = "SAMPLE"; break;}
    }
  sprintf(line, "command data %s %s %s %s %s %s %s %s", aux1, tdd[ref].name,
	  opd1, opd2, opd3, opd4, aux2, aux);
  emit(line);
}
/*****************************************************************************/
void get_com_data_copy (int ref, int cod, char *aux)
{ char line[140], opd[140]; char *aux2; EXPRE e; 

  if (cod == copy) aux2 ="copy";
  e.psymbol = NULL;  e.reftemp = cr_var_temp_cte_1();
  strexpre(opd, e);
  sprintf(line, "command data %s %s %s %s %s %s NONE %s", aux2, tdd[ref].name,
	  opd, opd, opd, opd, aux);
  emit(line);
}
/*****************************************************************************/
/******************************** expressions ********************************/
/*****************************************************************************/
void get_init_cte(int ref, float val)
{ char line[140]; 
 
  sprintf(line, "var initcte #%d %f", ref, val);
  emit(line);
}
/*****************************************************************************/
void get_init_elem(int ref, int dat, EXPRE f, EXPRE c)
{ char line[140], opd1[140], opd2[140]; 
 
  strexpre(opd1, f); strexpre(opd2, c);
  sprintf(line, "var initelem #%d %s %s %s", ref, tdd[dat].name, opd1, opd2);
  emit(line);
}
/*****************************************************************************/
void get_init_amend(int type, int ref, int dat, int cod)
{ char line[140]; char *aux; 
 
  switch (cod) {
    case mu:         { aux = "mu";         break; }
    case mmu:        { aux = "mmu";        break; }
    case l2:         { aux = "l2";         break; }
    case l1:         { aux = "l1";         break; }
    case maxn:       { aux = "maxn";       break; }
    case drop:       { aux = "drop";       break; }
    case noiser:     { aux = "noiser";     break; }
    case noisesd:    { aux = "noisesd";    break; }
    case brightness: { aux = "brightness"; break; }
    case contrast:   { aux = "contrast";   break; }
    case lambda:     { aux = "lambda";     break; }
    case noiseb:     { aux = "noiseb";     break; }
    case advf:       { aux = "advf";       break; }
    case bn:         { aux = "bn";         break; }
    case act:        { aux = "act";        break; }
    case shift:      { aux = "shift";      break; }
    case flip:       { aux = "flip";       break; }
    case adv:        { aux = "adv";        break; }
    case cropmode:   { aux = "cropmode";   break; }
    case balance:    { aux = "balance";    break; }
    case trainable : { aux = "trainable";  break; }
  }
  switch (type) {
  case DATA: {
    if (cod == balance) 
      sprintf(line,"var initdat #%d %s %s", ref, tdd[dat].name, aux);
    else yyerror("Parameter is not allowed for data");
    break;
  }
  case LAYER: {
    if ((cod == cropmode)||(cod == balance)) 
      yyerror("Parameter is not allowed for layers");
    else 
      sprintf(line,"var initlay #%d %s %s %s", ref, tdn[tdl[dat].refnet].name,
	      tdl[dat].name, aux);
    break;
  }
  case NETWORK: {
    sprintf(line,"var initnet #%d %s %s", ref, tdn[dat].name, aux);
    break;
  }
  }
  emit(line);
}
/*****************************************************************************/
void  get_exp_unary(int ref, int cod, EXPRE val)
{ char line[140];  char *aux;
 
  switch(cod) {
  case (ADDITION):    { aux = "+"; break;}
  case (SUBTRACTION): { aux = "-"; break;}
  case (NOT):         { aux = "!"; break;}
  }
  if (val.psymbol == NULL) 
    sprintf(line, "var unaryop #%d %s #%d", ref, aux, val.reftemp);
  else sprintf(line, "var unaryop #%d %s %s", ref, aux, val.psymbol->ident);
  emit(line);
}
/*****************************************************************************/
void get_functions(int ref, int cod, EXPRE val)
{ char line[140];  char *aux;
 
  switch(cod) {
  case (LOGARITHM):   { aux = "log"; break;}
  case (EXPONENTIAL): { aux = "exp"; break;}
  case (SQUARE):      { aux = "sqr"; break;}
  }
  if (val.psymbol == NULL) 
    sprintf(line, "var function #%d %s #%d", ref, aux, val.reftemp);
  else sprintf(line, "var function #%d %s %s", ref, aux, val.psymbol->ident);
  emit(line);
}

/*****************************************************************************/
void get_exp_log(int ref, EXPRE op1, int op, EXPRE op2)
{ char line[140], line2[140];  char *aux;
 
  switch(op) {
  case (AND):  { aux = "&&";  break;}
  case (OR):   { aux = "||";  break;}
  }
  if (op1.psymbol == NULL) 
    sprintf(line, "var binaryop #%d %s #%d", ref, aux, op1.reftemp);
  else sprintf(line, "var binaryop #%d %s %s", ref, aux, op1.psymbol->ident);

  if (op2.psymbol == NULL)  sprintf(line2, " #%d", op2.reftemp);
  else sprintf(line2, " %s", op2.psymbol->ident);
  strcat(line,line2);
  emit(line);
}
/*****************************************************************************/
void get_exp_eq(int ref, EXPRE op1, int op, EXPRE op2)
{ char line[140], line2[140];  char *aux;
 
  switch(op) {
  case (EQUAL):    { aux = "==";  break;}
  case (NOTEQUAL): { aux = "!=";  break;}
  }
  if (op1.psymbol == NULL) 
    sprintf(line, "var binaryop #%d %s #%d", ref, aux, op1.reftemp);
  else sprintf(line, "var binaryop #%d %s %s", ref, aux, op1.psymbol->ident);

  if (op2.psymbol == NULL)  sprintf(line2, " #%d", op2.reftemp);
  else sprintf(line2, " %s", op2.psymbol->ident);
  strcat(line,line2);
  emit(line);
}
/*****************************************************************************/
void get_exp_rel(int ref, EXPRE op1, int op, EXPRE op2)
{ char line[140], line2[140];  char *aux;
 
  switch(op) {
  case (GREAT):   { aux = ">";  break;}
  case (GREATEQ): { aux = ">="; break;}
  case (LESS):    { aux = "<";  break;}
  case (LESSEQ):  { aux = "<="; break;}
  }
  if (op1.psymbol == NULL) 
    sprintf(line, "var binaryop #%d %s #%d", ref, aux, op1.reftemp);
  else sprintf(line, "var binaryop #%d %s %s", ref, aux, op1.psymbol->ident);

  if (op2.psymbol == NULL)  sprintf(line2, " #%d", op2.reftemp);
  else sprintf(line2, " %s", op2.psymbol->ident);
  strcat(line,line2);
  emit(line);
}
/*****************************************************************************/
void get_exp_add(int ref, EXPRE op1, int op, EXPRE op2)
{ char line[140], line2[140];  char *aux;
 
  switch(op) {
  case (ADDITION):    { aux = "+";  break;}
  case (SUBTRACTION): { aux = "-";  break;}
  }
  if (op1.psymbol == NULL) 
    sprintf(line, "var binaryop #%d %s #%d", ref, aux, op1.reftemp);
  else sprintf(line, "var binaryop #%d %s %s", ref, aux, op1.psymbol->ident);

  if (op2.psymbol == NULL)  sprintf(line2, " #%d", op2.reftemp);
  else sprintf(line2, " %s", op2.psymbol->ident);
  strcat(line,line2);
  emit(line);
}
/*****************************************************************************/
void get_exp_mul(int ref, EXPRE op1, int op, EXPRE op2)
{ char line[140], line2[140];  char *aux;
 
  switch(op) {
  case (MULTIPLICATION): { aux = "*";  break;}
  case (DIVISION):       { aux = "/";  break;}
  case (MODULUS):        { aux = "%";  break;}
  case (EXPONET):        { aux = "**"; break;}
  }
  if (op1.psymbol == NULL) 
    sprintf(line, "var binaryop #%d %s #%d", ref, aux, op1.reftemp);
  else sprintf(line, "var binaryop #%d %s %s", ref, aux, op1.psymbol->ident);

  if (op2.psymbol == NULL)  sprintf(line2, " #%d", op2.reftemp);
  else sprintf(line2, " %s", op2.psymbol->ident);
  strcat(line,line2);
  emit(line);
}
/*****************************************************************************/
void  get_exp_eqvar(ptsymbol s, EXPRE op)
{ char line[140];

  if (op.psymbol == NULL) 
    sprintf(line, "var eqvar %s #%d", s->ident, op.reftemp);
  else
    sprintf(line, "var eqvar %s %s", s->ident, op.psymbol->ident);
  emit(line);
}
/*****************************************************************************/
void  get_exp_eqelem(int ref, EXPRE f, EXPRE c, EXPRE der)
{ char line[140], opd1[140], opd2[140], opd[140];

  strexpre(opd1, f); strexpre(opd2, c); strexpre(opd, der);
  sprintf(line, "var eqelem %s %s %s %s", tdd[ref].name, opd1, opd2, opd);
  emit(line);
}
/*****************************************************************************/
/********************************* generales *********************************/
/*****************************************************************************/
void strexpre(char *p, EXPRE val)
{
 if (val.psymbol == NULL) sprintf(p,"#%d", val.reftemp);
 else sprintf(p, "%s" , val.psymbol->ident);
}
/*****************************************************************************/
int  cr_var_temp_cte_1() 
{ char line[140];

 if (fcteneg == FALSE) {
   sprintf(line, "var initcte #%d %f", 0, -1.0);
   emit(line); fcteneg = TRUE;
   return 0;
 }
 else return 0;
}
/*****************************************************************************/
int cr_var_temp()
{ pstv++; return pstv-1; }
/*****************************************************************************/
void create_list_names()
{ ptnames = NULL; }
/*****************************************************************************/
ptsymbol insert_name(char *x)
{ ptsymbol s;
  s =  (ptsymbol)malloc(sizeof(typesymbol)); 
  s->ident = x; s->succ = ptnames; 
  ptnames = s; 
  return s;
}
/*****************************************************************************/
ptsymbol search_name (char *x) 
{ ptsymbol s = ptnames;
  while ((s != NULL) && (strcmp(x, s->ident))) s = s->succ;
  return s;
}
/*****************************************************************************/
void show_list_names ()
{ ptsymbol t = ptnames;

  while (t != NULL) {
    printf("Var %s\n", t->ident);
    t = t->succ;
  }
}
/*****************************************************************************/
void yyerror(const char *msg)
/*  Error handling.                                                          */
{
  numErrores++;
  fprintf(stderr, "\nError at line %d: %s\n", yylineno, msg);
}
/*****************************************************************************/
void emit (char *s)
{ char *d = malloc (strlen(s) + 1); 

  strcpy (d,s); mem[pmem] = d; pmem++;
}
/*****************************************************************************/
void dump_file()
{ FILE *fd; char *t; int i;
 
  if(numErrores == 0) {
    fd = fopen ("netparser.run", "w");
    for (i=0; i < pmem; i++) { fprintf(fd,"%s\n",mem[i]); free(mem[i]); }
    fclose(fd);
  }
}
/*****************************************************************************/
void begin_experiment()
{ 
  tdn[ptdn] = tdnini; tdl[ptdl] = tdlini; tdd[ptdd] = tddini; 
}
/*****************************************************************************/
void end_experiment()
{ char line[140];

  sprintf(line,"End"); emit(line);
}
/*****************************************************************************/
/*****************************************************************************/
/***********************************************************************/
char *replace_str(char *str, char *orig, char *rep)
{  char *buffer;  char *p; char *q; char *r; char aux1[140], aux2[140];

  if(!(p = strstr(str, orig))) return str;

  buffer = (char*)malloc(MaxSizeLin);
  q = str; r = buffer;
  do {
    strncpy(r, q, p-q);  r = r + (p-q);
    memset(aux1, '\0', sizeof(aux1));
    strncpy(aux1,(p - 1), 1);
    memset(aux2, '\0', sizeof(aux2));
    strncpy(aux2,(p + strlen(orig)), 1); 
    if (((strcmp(aux1,"(")==0) || (strcmp(aux1," ")==0)  || 
         (strcmp(aux1,")")==0) || (strcmp(aux1,"\n")==0) ||
         (strcmp(aux1,"[")==0) || (strcmp(aux1,"\t")==0) ||
         (strcmp(aux1,"{")==0) || (strcmp(aux1,"=")==0)  ||
         (strcmp(aux1,"+")==0) || (strcmp(aux1,"-")==0)  ||
         (strcmp(aux1,"<")==0) || (strcmp(aux1,">")==0)  ||
         (strcmp(aux1,"!")==0) || (strcmp(aux1,"/")==0)  ||
         (strcmp(aux1,"&")==0) || (strcmp(aux1,"%")==0)  ||
         (strcmp(aux1,"|")==0) || (strcmp(aux1,".")==0)  || 
         (strcmp(aux1,"*")==0) || (strcmp(aux1,",")==0)) && 
        ((strcmp(aux2,"(")==0) || (strcmp(aux2," ")==0)  || 
         (strcmp(aux2,")")==0) || (strcmp(aux2,"\n")==0) ||
         (strcmp(aux2,"[")==0) || (strcmp(aux2,"\t")==0) ||
         (strcmp(aux2,"{")==0) || (strcmp(aux2,"=")==0)  ||
         (strcmp(aux2,"+")==0) || (strcmp(aux2,"-")==0)  ||
         (strcmp(aux2,"<")==0) || (strcmp(aux2,">")==0)  ||
         (strcmp(aux2,"!")==0) || (strcmp(aux2,"/")==0)  ||
         (strcmp(aux2,"&")==0) || (strcmp(aux2,"%")==0)  ||
         (strcmp(aux2,"|")==0) || (strcmp(aux2,".")==0)  || 
         (strcmp(aux2,"*")==0)))
    {
      sprintf(r, "%s", rep);
      p = p + strlen(orig);  r = r + strlen(rep);
    }
    else {
      sprintf(r, "%s", orig); 
      p = p + strlen(orig);  r = r + strlen(orig);
    }
    q = p;  /* we look for other occurrences of the parameter */
  } while (p = strstr(q, orig));
  sprintf(r, "%s", q);
  return buffer;
}
/***********************************************************************/
int replaceparam(int k)
{ int i; char *m, *pa, *pf; pparam q, p;

  if (tdm[k].npfor != tdm[k].npact) return FALSE; 
  for ( i = tdm[k].pini; (i <= tdm[k].pfin); i++) {
    m = mem[i];
    q = tdm[k].fpf; p = tdm[k].fpa;
    while ((q != NULL) && (p != NULL)) {
      pf = strdup(q->param); pa = strdup(p->param);
      m = replace_str(m, pf, pa);
      free(pf); free(pa);
      q = q->succ; p = p->succ;
    }
    fprintf(fd,"%s",m);
    if (strcmp(mem[i], m) != 0) free(m); 
  }
  return TRUE;
}
/***********************************************************************/
void storeline(int k, char *s)
{ char *d = malloc (strlen(s) + 1); 

  strcpy (d,s); mem[pmem] = d; pmem++;
  if ( tdm[k].pini < 0 ) tdm[k].pini = tdm[k].pfin = pmem-1;
  else tdm[k].pfin = pmem-1;
}
/***********************************************************************/
int searchmacro(char *macroname)
{ int i, k = -1, ok = TRUE;

  for (i = 0; ((i < ptdm) && ok); i++)
    if (strcmp(tdm[i].name, macroname) == 0) { k = i; ok = FALSE; }
  return k;
}
/***********************************************************************/
int crmacro(char *macroname)
{ int k = -1;

  if (searchmacro(macroname) < 0) {  
    tdm[ptdm].name  = strdup(macroname); 
    tdm[ptdm].npfor = 0;                 tdm[ptdm].npact = 0;
    tdm[ptdm].pini  = -1;                tdm[ptdm].pfin  = -1;        
    tdm[ptdm].fpf = NULL;                tdm[ptdm].lpf  = NULL;        
    tdm[ptdm].fpa = NULL;                tdm[ptdm].lpa  = NULL;        
    k = ptdm;  ptdm++;
  }
  return k;
}
/***********************************************************************/
int searchparam(int type, int k, char *paramname)
{ pparam p;

  if (type == FORMAL)  p = tdm[k].fpf;
  else  p = tdm[k].fpa;
  while (p != NULL) {
    if (strcmp(paramname, p->param) == 0) return TRUE;
    else p = p->succ;
  }
  return FALSE;
}
/***********************************************************************/
int addparam(int type, int k, char *paramname)
{ pparam p; 

  if (searchparam(type, k, paramname)) return FALSE;
  if (type == FORMAL)  { 
    p =  (pparam)malloc(sizeof(typeparam));
    p->param = strdup(paramname); p->succ = NULL; 
    tdm[k].npfor++;
    if (tdm[k].lpf == NULL) { tdm[k].fpf = p; tdm[k].lpf = p; }
    else { tdm[k].lpf->succ = p; tdm[k].lpf = p; }
  }
  else { /*  type == ACTUAL  */
    p =  (pparam)malloc(sizeof(typeparam));
    p->param = strdup(paramname); p->succ = NULL; 
    tdm[k].npact++; 
    if (tdm[k].lpa == NULL) { tdm[k].fpa = p; tdm[k].lpa = p; }
    else { tdm[k].lpa->succ = p; tdm[k].lpa = p; }
  }
  return TRUE;
}
/*****************************************************************************/
void error(const char *msg)
{ fprintf(stderr, "\nError at line %d: %s\n", numlin, msg); }
/*****************************************************************************/
int remplace(char *nfich)
{ char linea [1024]; char *res; char *token; int nm = -1, i; pparam p,q;

  if ((fc = fopen (nfich, "r")) == NULL) {
    fprintf (stderr, "Fichero %s erróneo\n", nfich);
    return FALSE;
  }
  fd = fopen ("aux.net", "w");
  /******************************************************* read/dump loop ****/
  while (fgets(linea, 1024, fc) != NULL) {
    linea[strlen(linea)] = '\0'; res = strdup(linea); numlin++;
    token = strtok(res, " \n\t"); 
    if (token == NULL) dump = TRUE;
    else {
      /************************************************* MACRO DEFINITION ****/
      if (strcmp(token, "define") == 0) {
	if ((ismacro == FALSE) && (dump == TRUE)) {
          /* extract name of macro and create macro */
	  token = strtok(NULL, " \n\t");
	  if (token != NULL) {
/*          printf("DEFINE %s\n",token);                  */
	    if ((nm = crmacro(token)) >= 0) {
	      token = strtok(NULL, " \n\t");
              /* extracts formal parameters */
	      while( token != NULL ) {
		if (! addparam(FORMAL, nm, token))
		  { error("Parameter name already exists\n"); return FALSE; }
		token = strtok(NULL, " \n\t");
	      }
	      ismacro = TRUE; dump = FALSE;
	    }
	    else { error("Macro name already exists\n"); return FALSE; }
	  }
	  else { error("Name of the macro is needed\n"); return FALSE; }
	}
	else { error("Nested macros are not allowed\n"); return FALSE; }
      }
      /*********************************************** MACRO TERMINATION ****/ 
      else if (strcmp(token, "done") == 0) {
	if (ismacro == TRUE) {
/*	  printf("DONE\n");                               */
	  ismacro = FALSE; nm = -1; dump = FALSE;
	}
	else { error("Error in macro definition\n"); return FALSE; }
      }
      /****************************************************** MACRO CALL ****/
      else if (strcmp(token, "call") == 0) {
	if ((ismacro == FALSE) && (dump == TRUE)) {
          /* extract name of macro */
	  token = strtok(NULL, " \n\t");
	  if (token != NULL) {
/*	    printf("CALL %s\n",token);                    */
	    if ((nm = searchmacro(token)) >= 0) {
              /* extracts actual parameters */
	      token = strtok(NULL, " \n\t");
	      while( token != NULL ) {
		if (! addparam(ACTUAL, nm, token))
		  { error("Parameter name already exists\n"); return FALSE; }
		token = strtok(NULL, " \n\t");
	      }
	      ismacro = FALSE; dump = FALSE;
/*            printf("%s: %d %d %d %d ->", tdm[nm].name, tdm[nm].pini,
/*  	  	     tdm[nm].pfin, tdm[nm].npfor, tdm[nm].npact);
/*  	      q = tdm[nm].fpf; p = tdm[nm].fpa;
/*  	      while ((q != NULL) && (p != NULL)) {
/*  	        printf("(%s, %s)", q->param, p->param);
/*  	        q = q->succ; p = p->succ;
/*  	      }
/*  	      printf("\n");                                      */
     	      /* Replace actual parameters for formal ones */
	      if (!replaceparam(nm))
		{ error("Number of parameters wrong\n"); return FALSE; }
       	      /* Release the memory of the current parameters */
	      while (tdm[nm].fpa != NULL) {
		p = tdm[nm].fpa; tdm[nm].fpa = p->succ; free(p);
	      }
	      tdm[nm].npact = 0; tdm[nm].fpa = NULL; tdm[nm].lpa = NULL;
	    }
	    else { error("Macro name not defined\n"); return FALSE; }
	  }
	  else { error("Name of the macro is needed\n"); return FALSE; }
	}
	else { error("Error in macro call\n"); return FALSE; }
      }
      /********************************************************** OTHERS *****/
      else dump = TRUE;
    } /* fin (token != NULL) */
    /************************************************* Dump lines of code ****/
    if (dump) {
      if (ismacro) storeline(nm, linea);
      else fprintf(fd,"%s",linea);
    }
    else dump = TRUE;
  } /****************************************** end of the read/dump loop ****/
  fclose(fc);  fclose(fd); 
  /* Release the memory of the formal parameters */
  for (i = 0; (i < ptdm); i++) {
    while (tdm[i].fpf != NULL) {
      p = tdm[i].fpf; tdm[i].fpf = p->succ; free(p);
    }
    tdm[i].npfor = 0; tdm[i].fpf = NULL; tdm[i].lpf = NULL;
  }
  pmem = 0;
  return TRUE;
}
/*****************************************************************************/
/*****************************************************************************/
int netparser (char *nfich) 
/* Manages the command line and invokes the syntactic-semantic analyzer.     */
{ int i, n = 0; char line[140]; FILE *fe;

  sprintf(line,"rm aux.net 2>/dev/null"); system(line); 
  sprintf(line,"rm netparser.run 2>/dev/null"); system(line);
  if (! remplace(nfich)) {
    fprintf (stderr, "Error in the first pass (macros)\n");
    exit(1);      
  }
  else {
    if ((yyin = fopen ("aux.net", "r")) == NULL) {
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
    return 0;
  }
}
/*****************************************************************************/
/*****************************************************************************/
