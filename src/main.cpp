#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, fOBree, rand */
#include <string.h>

#include "layer.h"
#include "data.h"
#include "net.h"
#include "utils.h"


#ifdef fGPU
#include "./gpu/execution.h"
#endif

extern "C" int netparser (char *nfich) ;

#define MAX_ITEM 1000
#define MAX_CHAR 1000
#define MAX_VAR 10000


////////////////////////////////////
// GLOBAL
extern int useCPU;
int blas,cdnn;

// DATA
Data **DTable;
int Dc=0;

// Layer
Layer **LTable;
int Lc=0;

// Variables
// VTable
char VName[MAX_VAR][MAX_CHAR];
float VTable[MAX_VAR];
int vnum=0;

// RLayer
char R[MAX_ITEM][MAX_CHAR];
int vari[MAX_ITEM];
int RLc=0;

// Network
Net **NTable;
int Nc=0;

char innet[MAX_CHAR];
FILE *flog;
int threads=4;
int batch=100;
char logname[MAX_CHAR];
int seed;



void err(const char* c1,const char* c2)
{
  fprintf(stderr,"=================================================\n");
  fprintf(stderr,"Error: %s in %s\n",c1,c2);
  fprintf(stderr,"=================================================\n");
  exit(1);
}

//////////////////////////////////////
class IBlock {

  char **block;
  int sb,point;

public:

  IBlock(int s) {
    if (VERBOSE) fprintf(stderr,"Creating Inst Block with %d instructions\n",s);
    sb=s;
    point=0;
    block=(char **)malloc(sb*sizeof(char *));
    for(int i=0;i<sb;i++)
      block[i]=(char *)malloc(MAX_CHAR*sizeof(char *));
  }

  IBlock(IBlock *b,int ini,int fin) {
    sb=(fin-ini)+1;
    if (VERBOSE) fprintf(stderr,"Creating Inst Block with %d instructions\n",sb);

    point=0;
    block=(char **)malloc(sb*sizeof(char *));
    for(int i=0;i<sb;i++)
      block[i]=(char *)malloc(MAX_CHAR*sizeof(char *));

    for(int i=0;i<sb;i++)
      strcpy(block[i],b->block[ini+i]);

  }

  void put(char *cad,int p) {
    strcpy(block[p],cad);
  }

  void runConst(char *line) {
    char cad[MAX_CHAR],cad2[MAX_CHAR];


    sscanf(line,"Const %s %s\n",cad,cad2);
    

    if (!strcmp(cad,"threads")) {
      sscanf(line,"Const %s %d\n",cad,&threads);
      fprintf(stderr,"setting threads to %d\n",threads);
      setNbThreads(threads);
    }
    if (!strcmp(cad,"batch")) {
      sscanf(line,"Const %s %d\n",cad,&batch);
      fprintf(stderr,"setting batch to %d\n",batch);
    }
    if (!strcmp(cad,"log")) {

      sscanf(line,"Const %s %s\n",cad,logname);
      fprintf(stderr,"setting logfile %s\n",logname);
      flog=fopen(logname,"wt");
      fprintf(flog,"Start\n");
    }
    if (!strcmp(cad,"seed")) {
      sscanf(line,"Const %s %d\n",cad,&seed);
      fprintf(stderr,"setting random seed to %d\n",seed);

      srand(seed);
    }
    if (!strcmp(cad,"device")) {
      sscanf(line,"Const %s %s\n",cad,cad2);
      if (!strcmp(cad2,"cpu")) {
	useCPU=1;
	fprintf(stderr,"Layers using CPU\n");
      }
      else {
#ifdef fGPU
	int dev;
	sscanf(line,"Const device gpu %d\n",&dev);

	gpu_tensor_op.gpu_info(dev);

	cublasInit();
	curandInit();
	useCPU=0;
	fprintf(stderr,"Layers using GPU %d\n",dev);

#else
	fprintf(stderr,"Not compiled for GPU\n");
	exit(-1);
#endif
      }
    }
  }

  void runData(char *line) {
    char name[MAX_CHAR];
    char fname[MAX_CHAR];
    char ftype[MAX_CHAR];
    char dtype[MAX_CHAR];
    int sam,dim,out,param;


    //Data D4 ../train binary
    sscanf(line,"Data %s ",dtype);
    if (VERBOSE) fprintf(stderr,"#### %s\n",line);
    if (!strcmp(dtype,"F")) {
      //Data F id (binary, ascii) text
      sscanf(line,"Data F %s %s %s",name,ftype,fname);
      if (!strcmp(ftype,"ascii"))
        DTable[Dc]=new Data(fname, batch,name);
      else
        DTable[Dc]=new Data(1,fname, batch,name);

      DTable[Dc]->detect();
      Dc++;
    }
    else if (!strcmp(dtype,"G")) {
      //Data G id (gauss, uniform, ones, zeros, oneshot) numdata (-1, cte)
      sscanf(line,"Data G %s %s %d %d",name,ftype,&dim,&param);
      //GData::GData(int n,int d,int t,char *name)
      if (!strcmp(ftype,"zeros"))
        DTable[Dc]=new GData(batch,dim,0,param,name);
      else if (!strcmp(ftype,"ones"))
        DTable[Dc]=new GData(batch,dim,1,param,name);
      else if (!strcmp(ftype,"gauss"))
        DTable[Dc]=new GData(batch,dim,2,param,name);
      else if (!strcmp(ftype,"uniform"))
        DTable[Dc]=new GData(batch,dim,3,param,name);
      else if (!strcmp(ftype,"suniform"))
        DTable[Dc]=new GData(batch,dim,4,param,name);
      else if (!strcmp(ftype,"oneshot"))
        DTable[Dc]=new GData(batch,dim,5,param,name);
      GData *gd=(GData *)DTable[Dc];
      gd->next();
      Dc++;
    }
    else if (!strcmp(dtype,"C")) {
      //Data C id cte1 cte2 cte3
      sscanf(line,"Data C %s %d %d %d",name,&sam,&dim,&out);
      if (sam!=-1) {
	//Data::Data(int n,int d,int o,int b,char *name)
	DTable[Dc]=new Data(sam,dim,out,batch,name);
	Dc++;
      }
    }

  }

  //// VAR
  int findvar(char *var) {
    int i,ind;
    for(i=0;i<vnum;i++) 
      if (!strcmp(var,VName[i])) {ind=i;break;}

    if (i==vnum) {
      strcpy(VName[i],var);
      ind=i;
      vnum++;
    }
    return ind;
  }
  float getvar(char *var) {
    int ind=findvar(var);
    return VTable[ind];
  }
  void setvar(char *var,float f) {
    int ind=findvar(var);
    VTable[ind]=f;
  }


  void getnamevar(char *cad) 
  {
    char *pch;

    return;
    // now is deactivated

    pch=strtok(cad,"_");
    pch = strtok (NULL,"_");
    if (pch != NULL) {
      pch = strtok (cad,"_");
      char *p=pch+1;
      int v=getvar(p);
      sprintf(cad,"%s%d",pch,v);
    }
    else {
      return;
    }
  }

  void runevar(char *line) {
    //@evar i data D1 [nrows,ncolsample,ncoltarget]
    char dname[MAX_CHAR];
    char var[MAX_CHAR];
    char cad[MAX_CHAR];
    char op[MAX_CHAR];

    int i;
    int ind;
    
    sscanf(line,"evar %s %s %s %s\n",var,op,dname,cad);

    if (!strcmp(op,"data")) { 
      for(i=0;i<Dc;i++) {
        if (!strcmp(dname,DTable[i]->name)) break;
      }
      Data *data=DTable[i];
      ind=findvar(var);

      //nrows,ncolsample,ncoltarget
      //num, dim, out
      if (!strcmp(cad,"nrows")) 
	VTable[ind]=data->num;
      else if (!strcmp(cad,"ncolsample")) 
	VTable[ind]=data->dim;
      else if (!strcmp(cad,"ncoltarget")) 
	VTable[ind]=data->out;
    }
  }


  void runVar(char *line) {
    char name[MAX_CHAR];
    char dname[MAX_CHAR];
    char var[MAX_CHAR];
    char cad[MAX_CHAR];
    char cad1[MAX_CHAR];
    char cad2[MAX_CHAR];
    char op[MAX_CHAR];
    char func[MAX_CHAR];

    int i;
    int ind,ind1,ind2;
    float fv;

    // var name = name1 op name2
    sscanf(line,"var %s\n",op);
    if (VERBOSE) fprintf(stderr,"#### %s\n",line);

    float r,v1,v2;

    if (!strcmp(op,"print")) {
      sscanf(line,"var print %s\n",cad);    
      ind=findvar(cad);
      printf("%s=%f\n",cad,VTable[ind]);
    }
    else if (!strcmp(op,"initcte")) {
      sscanf(line,"var initcte %s %f\n",cad,&fv);    
      ind=findvar(cad);
      VTable[ind]=fv;
    }
    else if (!strcmp(op,"initelem")) {
      sscanf(line,"var initelem %s %s %s %s\n",var,dname,cad1,cad2);
      ind=findvar(var);
      for(i=0;i<Dc;i++) {
	if (!strcmp(dname,DTable[i]->name)) break;
      }
      Data *data=DTable[i];
      int s,d;
      s=getvar(cad1);
      d=getvar(cad2);
      
      VTable[ind]=data->get(s,d);
    }
    else if (!strcmp(op,"eqelem")) {
      sscanf(line,"var eqelem %s %s %s %s\n",dname,cad1,cad2,var);
      for(i=0;i<Dc;i++) {
	if (!strcmp(dname,DTable[i]->name)) break;
      }
      Data *data=DTable[i];
      int s,d;
      s=getvar(cad1);
      d=getvar(cad2);
   
      data->set(s,d,getvar(var));
    }
    else if (!strcmp(op,"function")) {
      sscanf(line,"var function %s %s %s\n",cad,func,cad1);    
      ind=findvar(cad);
      ind1=findvar(cad1);
      if (!strcmp(func,"exp")) {
	VTable[ind]=exp(VTable[ind1]);
      }
      if (!strcmp(func,"log")) {
	VTable[ind]=log(VTable[ind1]);
      }
      if (!strcmp(func,"sqr")) {
	VTable[ind]=sqrt(VTable[ind1]);
      }
    }
    else if (!strcmp(op,"eqvar")) {
      sscanf(line,"var eqvar %s %s\n",cad,cad1);    
      ind=findvar(cad);
      ind1=findvar(cad1);
      VTable[ind]=VTable[ind1];
    }
    else if (!strcmp(op,"unaryop")) {
      sscanf(line,"var unaryop %s %s %s\n",cad,op,cad1); 
      ind=findvar(cad);
      ind1=findvar(cad1);   
      // Arithmetic
      if (!strcmp(op,"-")) VTable[ind]=-VTable[ind1];
    }
    else if (!strcmp(op,"binaryop")) {
      sscanf(line,"var binaryop %s %s %s %s\n",cad,op,cad1,cad2); 
      ind=findvar(cad);
      ind1=findvar(cad1);   
      ind2=findvar(cad2);   
      // Arithmetic
      if (!strcmp(op,"+")) VTable[ind]=VTable[ind1]+VTable[ind2];
      if (!strcmp(op,"-")) VTable[ind]=VTable[ind1]-VTable[ind2];
      if (!strcmp(op,"/")) VTable[ind]=VTable[ind1]/VTable[ind2];
      if (!strcmp(op,"*")) VTable[ind]=VTable[ind1]*VTable[ind2];
      if (!strcmp(op,"^")) VTable[ind]=pow(VTable[ind1],VTable[ind2]);
      if (!strcmp(op,"%")) {
	int i1=VTable[ind1];
	int i2=VTable[ind2];
	VTable[ind]=i1%i2;
      }
      // Logical
      if (!strcmp(op,">")) {
	if (VTable[ind1]>VTable[ind2]) VTable[ind]=1;
	else VTable[ind]=0;
      }
      if (!strcmp(op,"<")){
        if (VTable[ind1]<VTable[ind2]) VTable[ind]=1;
        else VTable[ind]=0;
      }
      if (!strcmp(op,">=")){
        if (VTable[ind1]>=VTable[ind2]) VTable[ind]=1;
        else VTable[ind]=0;
      }
      if (!strcmp(op,"<=")){
        if (VTable[ind1]<=VTable[ind2]) VTable[ind]=1;
        else VTable[ind]=0;
      }
      if (!strcmp(op,"==")){
        if (VTable[ind1]==VTable[ind2]) VTable[ind]=1;
        else VTable[ind]=0;
      }
      if (!strcmp(op,"!=")){
        if (VTable[ind1]!=VTable[ind2]) VTable[ind]=1;
        else VTable[ind]=0;
      }
      
    }

  }


  void runNetwork(char *line) {
    char name[MAX_CHAR];

    sscanf(line,"Network %s\n",name);
    if (VERBOSE) fprintf(stderr,"#### %s\n",line);
    fprintf(stderr,"\n============= Network %s\n",name);
    NTable[Nc]=new Net(name,batch);
    strcpy(innet,name);
  }


  void rundata(char *line) {
    char dtype[MAX_CHAR],use[MAX_CHAR],name[MAX_CHAR];
    int i;

    //data (tr, ts, va) (F, G, C) id
    sscanf(line,"data %s %s %s",use,dtype,name);
    if (VERBOSE) fprintf(stderr,"#### %s\n",line);
    int enc=0;
    for(i=0;i<Dc;i++) {
      if (!strcmp(name,DTable[i]->name)) {enc=1;break;}
    }
    if (!strcmp(use,"tr")) {
      NTable[Nc]->Dtrain=DTable[i];
    }
    else if (!strcmp(use,"ts")) {
      NTable[Nc]->Dtest=DTable[i];
    }
    else {
      NTable[Nc]->Dval=DTable[i];
    }
  }


  void runlayer(char *line) {
    char lname[MAX_CHAR];
    char lname2[MAX_CHAR];
    char name[MAX_CHAR];
    char net1[MAX_CHAR];
    char layer1[MAX_CHAR];
    char net2[MAX_CHAR];
    char layer2[MAX_CHAR];
    char ltype[MAX_CHAR];
    char cad[MAX_CHAR];
    char cad2[MAX_CHAR];
    char data[MAX_CHAR];
    int nk,kz,kr,kc,cc,cr,rpad,cpad,stride;
    int sizer,sizec;
    int act,nn;
    int i;


    sscanf(line,"layer %s %s ",name,ltype);
    if (VERBOSE) fprintf(stderr,"#### %s\n",line);
    ////////////// FI //////////////
    if (!strcmp(ltype,"FI")) {
      //layer id FI Net Layer Dat
      sscanf(line,"layer %s FI %s %s %s\n",name,net1,layer1,data);
      sprintf(lname,"%s:%s",innet,name);

      if (!strcmp(net1,"NULL")) {// set source data
	if (!strcmp(data,"NULL")) { 
	  if (NTable[Nc]->Dtrain==NULL) {
	    fprintf(stderr,"Error creating Input Layer (%s:%s) without source\n",innet,name);
	    exit(1);
	  }
	  LTable[Lc]=new IFLayer(NTable[Nc]->Dtrain,NULL,batch,lname);
	  NTable[Nc]->addLayer(LTable[Lc]);
	}
	else {
	  int enc=0;
	  for(i=0;i<Dc;i++) {
	    if (!strcmp(data,DTable[i]->name)) {enc=1;break;}
	  }
	  LTable[Lc]=new IFLayer(DTable[i],NULL,batch,lname);
	  NTable[Nc]->addLayer(LTable[Lc]);
	  NTable[Nc]->Dtrain=DTable[i];
	}
      }
      else {// set source layer
	sprintf(lname2,"%s:%s",net1,layer1);
	for(i=0;i<Lc;i++) {
	  if (!strcmp(lname2,LTable[i]->name)) break;
	}
	Layer *l2=LTable[i];
	LTable[Lc]=new IFLayer(NULL,(FLayer *)l2,batch,lname);
	NTable[Nc]->addLayer(LTable[Lc]);

      }
      Lc++;
    }

    ////////////// CI //////////////  
    else if (!strcmp(ltype,"CI")) {
      //layer id CI nz cte nr cte nc cte cr (cte, cte_nr) cc (cte, cte_nc) (NULL, dat) 
      sscanf(line,"layer %s CI nz %d nr %d nc %d cr %d cc %d %s %s %s\n",name,&kz,&kr,&kc,&cr,&cc,net1,layer1,data);
      sprintf(lname,"%s:%s",innet,name);
      if (!strcmp(net1,"NULL")) {// set source data
	if (!strcmp(data,"NULL")) {
	  LTable[Lc]=new ICLayer(NTable[Nc]->Dtrain,NULL,batch,kz,kr,kc,cr,cc,lname);
	  NTable[Nc]->addLayer(LTable[Lc]);
	}
	else {
	  int enc=0;
	  for(i=0;i<Dc;i++) {
	    if (!strcmp(data,DTable[i]->name)) {enc=1;break;}
	  }
	  LTable[Lc]=new ICLayer(DTable[i],NULL,batch,kz,kr,kc,cr,cc,lname);
	  NTable[Nc]->addLayer(LTable[Lc]);
	}
      }
      else {
	sprintf(lname2,"%s:%s",net1,layer1);
	for(i=0;i<Lc;i++) {
	  if (!strcmp(lname2,LTable[i]->name)) break;
	}
	Layer *l2=LTable[i];
	LTable[Lc]=new ICLayer(NULL,l2,batch,kz,kr,kc,cr,cc,lname);
	NTable[Nc]->addLayer(LTable[Lc]);
      }
      Lc++;
    }

    ////////////// C //////////////
    else if (!strcmp(ltype,"C")) {
      //layer id C nk 64 kr 3 kc 3 rpad 1 cpad 1 stride 1
      sscanf(line,"layer %s C nk %d kr %d kc %d rpad %d cpad %d stride %d\n",name,&nk,&kr,&kc,&rpad,&cpad,&stride);
      sprintf(lname,"%s:%s",innet,name);
      if (stride<1) stride=1;
      LTable[Lc]=new CLayer(nk,kr,kc,batch,rpad,cpad,stride,lname);
      NTable[Nc]->addLayer(LTable[Lc]);
      Lc++;
    }

    ////////////// MP //////////////

    else if (!strcmp(ltype,"MP")) {
      //layer id MP sizer 2 sizec 2
      sscanf(line,"layer %s MP sizer %d sizec %d\n",name,&sizer,&sizec);
      sprintf(lname,"%s:%s",innet,name);

      LTable[Lc]=new PLayer(batch,sizer,sizec,lname);
      NTable[Nc]->addLayer(LTable[Lc]);
      Lc++;
    }
    ////////////// CAT //////////////
    else if (!strcmp(ltype,"CA")) {
      // layer id CAT
      sscanf(line,"layer %s CA\n",name);
      sprintf(lname,"%s:%s",innet,name);

      LTable[Lc]=new CatLayer(batch,lname);
      NTable[Nc]->addLayer(LTable[Lc]);
      Lc++;
    }
    ////////////// ADD //////////////
    else if (!strcmp(ltype,"ADD")) {
      // layer id ADD
      sscanf(line,"layer %s ADD\n",name);
      sprintf(lname,"%s:%s",innet,name);

      LTable[Lc]=new AddLayer(batch,lname);
      NTable[Nc]->addLayer(LTable[Lc]);
      Lc++;
    }

    ////////////// R //////////////
    else if (!strcmp(ltype,"R")) {
      //layer id R N1 l2
      sscanf(line,"layer %s R %s %s\n",name,cad,cad2);
      sprintf(R[RLc],"%s:%s",innet,name);
      RLc++;

    }

    ////////////// O //////////////
    else if (!strcmp(ltype,"O")) {
      //layer id R N1 l2
      sscanf(line,"layer %s O %s\n",name,cad);
      
      int op;
      //operador={add, sub, imult, omult, div, sigmoid, tanh, log, relu}
      if (!strcmp(cad,"add")) op=OP_SUM;
      else if (!strcmp(cad,"sub")) op=OP_SUB;
      else if (!strcmp(cad,"imult")) op=OP_IMULT;
      else if (!strcmp(cad,"omult")) op=OP_OMULT;
      else if (!strcmp(cad,"div")) op=OP_DIV;
      else if (!strcmp(cad,"sigmoid")) op=OP_SIGM;
      else if (!strcmp(cad,"tanh")) op=OP_TANH;
      else if (!strcmp(cad,"log")) op=OP_LOG;
      else if (!strcmp(cad,"relu")) op=OP_MEAN; /// !!!!!
      else err("incorrect operand","O Layer");

      sprintf(lname,"%s:%s",innet,name);
      LTable[Lc]=new OLayer(batch,op,lname);
      NTable[Nc]->addLayer(LTable[Lc]);
      Lc++;

    }

    ////////////// FO //////////////
    else if (!strcmp(ltype,"FO")) {

      //layer id FO (#1) (-1, net) (-1, lay) (NULL, dat) 
      //                #1: classification, regression, autoencoder...
      sscanf(line,"layer %s FO %s %s %s %s",name,cad,net1,layer1,data);
      sprintf(lname,"%s:%s",innet,name);
      
      // target data
      if (!strcmp(net1,"NULL")) {
	Data *fod;
	if (!strcmp(data,"NULL")) {fod=NTable[Nc]->Dtrain;}
	else {    
	  int enc=0;
	  for(i=0;i<Dc;i++) {
	    if (!strcmp(data,DTable[i]->name)) {enc=1;break;}
	  }
	  fod=DTable[i];
	}
	if (!strcmp(cad,"classification"))
	  LTable[Lc]=new OFLayer(fod, NULL, batch,0,lname);
	else if (!strcmp(cad,"regression"))
	  LTable[Lc]=new OFLayer(fod, NULL, batch,1,lname);
	else if (!strcmp(cad,"autoencoder"))
	  LTable[Lc]=new OFLayer(fod, NULL, batch,2,lname);
	else if (!strcmp(cad,"max"))
	  LTable[Lc]=new OFLayer(fod, NULL, batch,3,lname);
	else if (!strcmp(cad,"min"))
	  LTable[Lc]=new OFLayer(fod, NULL, batch,4,lname);
	else if (!strcmp(cad,"maxlog"))
	  LTable[Lc]=new OFLayer(fod, NULL, batch,5,lname);
	else if (!strcmp(cad,"minlog"))
	  LTable[Lc]=new OFLayer(fod, NULL, batch,6,lname);
	else err("incorrect loss","FO Layer");
      }
      //target layer
      else { 
	act=0;
	sprintf(lname,"%s:%s",innet,name);
	sprintf(cad2,"%s:%s",net1,layer1);
	if (VERBOSE) fprintf(stderr,"Target %s:%s\n",net1,layer1);
	for(i=0;i<Lc;i++) {
	  if (!strcmp(cad2,LTable[i]->name)) break;
	}
	if (!strcmp(cad,"classification"))
	  LTable[Lc]=new OFLayer(NULL,(FLayer*)LTable[i], batch,0,lname);
	else if (!strcmp(cad,"regression")) 
	  LTable[Lc]=new OFLayer(NULL,(FLayer*)LTable[i], batch,1,lname);
	else if (!strcmp(cad,"autoencoder"))
	  LTable[Lc]=new OFLayer(NULL,(FLayer*)LTable[i], batch,2,lname);
	else if (!strcmp(cad,"max"))
	  LTable[Lc]=new OFLayer(NULL,(FLayer*)LTable[i], batch,3,lname);
	else if (!strcmp(cad,"min"))
	  LTable[Lc]=new OFLayer(NULL,(FLayer*)LTable[i], batch,4,lname);
	else if (!strcmp(cad,"maxlog"))
	  LTable[Lc]=new OFLayer(NULL,(FLayer*)LTable[i], batch,5,lname);
	else if (!strcmp(cad,"minlog"))
	  LTable[Lc]=new OFLayer(NULL,(FLayer*)LTable[i], batch,6,lname);
	else err("incorrect loss","FO Layer");

      }

      NTable[Nc]->addLayer(LTable[Lc]);
      Lc++;
    }
    //F
    else if (!strcmp(ltype,"F")) {
      //layer id F numnodes 128
      sscanf(line,"layer %s F numnodes %d\n",name,&nn);
      sprintf(lname,"%s:%s",innet,name);
      LTable[Lc]=new FLayer(nn,batch,lname);
      NTable[Nc]->addLayer(LTable[Lc]);
      Lc++;
    }
  }

  void runlink(char *line) {
    char lname[MAX_CHAR];
    char name[MAX_CHAR];
    char net1[MAX_CHAR];
    char layer1[MAX_CHAR];
    char net2[MAX_CHAR];
    char layer2[MAX_CHAR];
    char ltype[MAX_CHAR];
    char cad[MAX_CHAR];
    Layer *l1,*l2;
    int kz,kr,kc,cc,cr;
    int sizer,sizec;
    int act,nn;
    int i;


    sscanf(line,"link %s %s %s %s\n",net1,layer1,net2,layer2);
    if (VERBOSE) fprintf(stderr,"#### %s\n",line);
    sprintf(lname,"%s:%s",net2,layer2);

    for(i=0;i<RLc;i++)
      if (!strcmp(R[i],lname)) {
	if (VERBOSE) fprintf(stderr,"%s is a reshape layer\n",lname);
	break;
      }

    if (i<RLc) {// reshape layer special case
      sscanf(line,"link %s %s %s %s\n",net1,layer1,net2,layer2);
      sprintf(lname,"%s:%s",net1,layer1);

      for(i=0;i<Lc;i++) {
	if (!strcmp(lname,LTable[i]->name)) break;
      }

      sprintf(lname,"%s:%s",net2,layer2);
      LTable[Lc]=new FLayer(LTable[i],batch,lname);
      NTable[Nc]->addLayer(LTable[i]);
      NTable[Nc]->addLayer(LTable[Lc]);
      Lc++;
    }
    else {
      sscanf(line,"link %s %s %s %s\n",net1,layer1,net2,layer2);
      sprintf(lname,"%s:%s",net1,layer1);

      for(i=0;i<Lc;i++) {
	if (!strcmp(lname,LTable[i]->name)) break;
      }
      l1=LTable[i];
      NTable[Nc]->addLayer(l1);


      sprintf(lname,"%s:%s",net2,layer2);
      for(i=0;i<Lc;i++) {
	if (!strcmp(lname,LTable[i]->name)) break;
      }
      l2=LTable[i];
      NTable[Nc]->addLayer(l2);
      
      l1->addchild(l2);
    }
  }



  void runshared(char *line) {
    char lname[MAX_CHAR];
    char name[MAX_CHAR];
    char net1[MAX_CHAR];
    char layer1[MAX_CHAR];
    char net2[MAX_CHAR];
    char layer2[MAX_CHAR];
    char ltype[MAX_CHAR];
    Layer *l1,*l2;
    int i;

    sscanf(line,"shared %s %s %s %s\n",net1,layer1,net2,layer2);
    sprintf(lname,"%s:%s",net1,layer1);

    for(i=0;i<Lc;i++) {
      if (!strcmp(lname,LTable[i]->name)) break;
    }
    l1=LTable[i];

    sprintf(lname,"%s:%s",net2,layer2);
    for(i=0;i<Lc;i++) {
	if (!strcmp(lname,LTable[i]->name)) break;
    }
    l2=LTable[i];

    // Shared
    l1->shared(l2);
    
  }

  void runendnet(char *line) {
    int i;
    Net *n=NTable[Nc];

    n->Init(flog);
    n->net2dot();
    n->setthreads(threads);
    fprintf(stderr,"==========================\n\n");
    Nc++;
  }

  void runcommand(char *line) {
    int par;
    float fv;
    Data *d;
    char fname[MAX_CHAR];
    char lname[MAX_CHAR];
    char lname2[MAX_CHAR];
    char name[MAX_CHAR];
    char com[MAX_CHAR];
    char var[MAX_CHAR];
    char net1[MAX_CHAR];
    char layer1[MAX_CHAR];
    char net2[MAX_CHAR];
    char layer2[MAX_CHAR];
    char ltype[MAX_CHAR];
    char cad[MAX_CHAR];
    char cad2[MAX_CHAR];
    char ctype[MAX_CHAR];
    int i,j;

    //command type                                                                                         
    sscanf(line,"command %s ",ctype);
    if (VERBOSE) fprintf(stderr,"#### %s\n",line);
    ////////////////////
    // command layer    
    ///////////////////
    if (!strcmp(ctype,"layer")) {
      sscanf(line,"command layer %s %s %s",com,net1,layer1);

      sprintf(lname,"%s:%s",net1,layer1);
      Layer *l;
      for(i=0;i<Lc;i++)
	if (!strcmp(LTable[i]->name,lname)) break;
      l=LTable[i];
      //printkernels
      if (!strcmp(com,"printkernels")) {
	sscanf(line,"command layer %s %s %s %s",com,net1,layer1,cad);

	FILE *fe=fopen(cad,"wt");
	if (fe==NULL) {
	  fprintf(stderr,"File error %s\n",cad);
	  exit(1);
	}
	l->printkernels(fe);
      }
      //copy
      else  if (!strcmp(com,"copy")) {
	sscanf(line,"command layer %s %s %s %s %s",com,net1,layer1,net2,layer2);

	sprintf(lname2,"%s:%s",net2,layer2);
	Layer *l2;
	for(i=0;i<Lc;i++)
	  if (!strcmp(LTable[i]->name,lname2)) break;
	l2=LTable[i];

	for(i=0;i<Nc;i++)
	  if (!strcmp(NTable[i]->name,net1)) break;
	Net *n1=NTable[i];

	n1->copy(l,l2);
      }
      //change
      else  if (!strcmp(com,"change")) {
	Data *d;
	char dname[MAX_CHAR];
	sscanf(line,"command layer %s %s %s %s %s %s",com,net1,layer1,net2,layer2,dname);

	//set data
	if (!strcmp(net2,"NULL")) {
	  for(i=0;i<Dc;i++)
	    if (!strcmp(DTable[i]->name,dname)) break;
	  d=DTable[i];

	  if (l->out) {((OFLayer *)l)->settarget(d);}
	  else {
	    if (l->type==1) {((IFLayer *)l)->setsource(d);}
	    else if (l->type==2) {((ICLayer *)l)->setsource(d);}
	  }
	}
	//set layer
	else {
	  sprintf(lname2,"%s:%s",net2,layer2);
	  FLayer *l2;
	  for(i=0;i<Lc;i++)
	    if (!strcmp(LTable[i]->name,lname2)) break;
	  l2=(FLayer *)LTable[i];
	  if (l->out) ((OFLayer *)l)->settarget(l2);
	  else ((IFLayer *)l)->setsource(l2);
	}
      }
    }
    /////////////////////
    // command network                  
    /////////////////////                                                                  
    else if (!strcmp(ctype,"network")) {
      sscanf(line,"command network %s %s ",com,net1);
      for(i=0;i<Nc;i++)
	if (!strcmp(NTable[i]->name,net1)) break;

      Net *n1=NTable[i];
      // train
      if (!strcmp(com,"train")) {
	sscanf(line,"command network train %s %s",cad,var);
	par=getvar(var);

	n1->train(par);
      }
      // load
      else if (!strcmp(com,"load")) {
	sscanf(line,"command network load %s %s",cad,cad2);

	FILE *fe=fopen(cad2,"rt");
	if (fe==NULL) {
	  fprintf(stderr,"File error %s\n",cad2);
	  exit(1);
	}
	n1->load(fe);
      }
      // save
      else if (!strcmp(com,"save")) {
	sscanf(line,"command network save %s %s",cad,cad2);

	FILE *fe=fopen(cad2,"wt");
	if (fe==NULL) {
	  fprintf(stderr,"File error %s\n",cad2);
	  exit(1);
	}
	n1->save(fe);
      }
      // testout
      else if (!strcmp(com,"testout")) {
	sscanf(line,"command network testout %s %s",cad,cad2);

	FILE *fe=fopen(cad2,"wt");
	if (fe==NULL) {
	  fprintf(stderr,"File error %s\n",cad2);
	  exit(1);
	}
	n1->testOut(fe);
      }
      //forward
      else if (!strcmp(com,"forward")) {
	n1->doforward();
      }
      else if (!strcmp(com,"counterr")) {
	n1->docounterr();
      }
      // backward
      else if (!strcmp(com,"backward")) {
	n1->dobackward();
      }
      else if (!strcmp(com,"update")) {
	n1->doupdate();
      }
      else if (!strcmp(com,"printerrors")) {
	n1->doprinterrors();
      }
      else if (!strcmp(com,"reseterrors")) {
	n1->doreseterrors();
      }
      else if (!strcmp(com,"resetstats")) {
	n1->doresetstats();
      } 
      else if (!strcmp(com,"trainmode")) {
	n1->trainmode();
      }
      else if (!strcmp(com,"testmode")) {
	n1->testmode();
      }
      // test
      else if (!strcmp(com,"evaluate")) {
	sscanf(line,"command network evaluate %s %s",cad,cad2);
	if (!strcmp(cad2,"NULL")) {
	  if (n1->Dtest!=NULL)
	    n1->evaluate(n1->Dtest);
	}
	else {
	  for(i=0;i<Dc;i++)
	    if (!strcmp(DTable[i]->name,cad2)) break;
	  d=DTable[i];
	  n1->evaluate(d);
	}
      }
    }
    //////////////////////
    // command data       
    /////////////////////
    else if (!strcmp(ctype,"data")) {
      char csini1[MAX_CHAR],csfin1[MAX_CHAR],ccini1[MAX_CHAR],ccfin1[MAX_CHAR],cctype1[MAX_CHAR];
      char csini2[MAX_CHAR],csfin2[MAX_CHAR],ccini2[MAX_CHAR],ccfin2[MAX_CHAR],cctype2[MAX_CHAR];
      char carg[MAX_CHAR];
      float sini1,sfin1,cini1,cfin1,ctype1;
      float sini2,sfin2,cini2,cfin2,ctype2;
      float arg;

      char dname1[MAX_CHAR],dname2[MAX_CHAR];
      Data *d1,*d2;

      
      // Commands wiht one data without ranges
      sscanf(line,"command data %s %s ",com,dname1);
      getnamevar(dname1);

      for(i=0;i<Dc;i++) {
	if (!strcmp(DTable[i]->name,dname1)) break;
      }

      if (i==Dc) d1=NULL;
      else d1=DTable[i];

      if (!strcmp(com,"next")) {//command data next D1 
	d1->next();
      }
      else if (!strcmp(com,"store")) {//command data store D1 filename
	sscanf(line,"command data store %s %s",dname1,fname);
	getnamevar(dname1);

	//d1->SaveBin(fname);
	d1->Save(fname);
      }
      else if (!strcmp(com,"shuffle")) { //command data shuffle D1
	d1->shuffle();
      }
      else if (!strcmp(com,"getstats")) { //command data getstats D1 D2
	sscanf(line,"command data getstats %s %s",dname1,dname2);
	getnamevar(dname1);
	getnamevar(dname2);

	for(i=0;i<Dc;i++)
	  if (!strcmp(DTable[i]->name,dname2)) break;
	d2=DTable[i];
	d1->copystats(d2);
      }
      else {
	// Commands with one data with ranges

	//command data div D2 #0 #0 #0 #0 NONE #1
	sscanf(line,"command data %s %s %s %s %s %s %s %s",com,dname1,csini1,csfin1,ccini1,ccfin1,cctype1,carg);
		
	getnamevar(dname1);
	

	sini1=getvar(csini1);
	sfin1=getvar(csfin1);
	cini1=getvar(ccini1);
	cfin1=getvar(ccfin1);
	arg=getvar(carg);

	ctype1=-1;
	if (!strcmp(cctype1,"SAMPLE")) {cini1=1;cfin1=d1->dim;}
	else if (!strcmp(cctype1,"TARGET")) {cini1=d1->dim+1;cfin1=d1->size;}
	else {
	  if  (!strcmp(cctype1,"REAL")) {ctype1=0;}
	  else if  (!strcmp(cctype1,"BIN")) {ctype1=1;}
	  else if  (!strcmp(cctype1,"INT")) {ctype1=2;}
	}	

	if (!strcmp(com,"mul")) {
	  d1->mul(arg,sini1,sfin1,cini1,cfin1,ctype1);
	}
	else if (!strcmp(com,"div")) {
	  d1->div(arg,sini1,sfin1,cini1,cfin1,ctype1);
	}
	else if (!strcmp(com,"add")) {
	  d1->add(arg,sini1,sfin1,cini1,cfin1,ctype1);
	}
	else if (!strcmp(com,"sub")) {
	  d1->sub(arg,sini1,sfin1,cini1,cfin1,ctype1);
	}
	else if (!strcmp(com,"set")) {
	  d1->set(arg,sini1,sfin1,cini1,cfin1,ctype1);
	}
	else if (!strcmp(com,"zscore")) {
	  d1->zscore(sini1,sfin1,cini1,cfin1,ctype1);
	}
	else if (!strcmp(com,"center")) {
	  d1->center(sini1,sfin1,cini1,cfin1,ctype1);
	}
	else if (!strcmp(com,"maxmin")) {
	  d1->maxmin(sini1,sfin1,cini1,cfin1,ctype1);
	}
	else if (!strcmp(com,"yuv")) {
	  d1->YUV();
	}
      }

      // Commads with two datas
      if (!strcmp(com,"copy")) {
	char source[MAX_CHAR];
	// command data copy DEST #1 #2 #3 #4 NONE SOURCE_TYPE SOURCE #5 #6 #7 #8 NONE
	sscanf(line,"command data copy  %s    %s %s %s %s %s  %s",dname1, csini1,csfin1,ccini1,ccfin1,cctype1,source);
	getnamevar(dname1);

	sini1=getvar(csini1);
	sfin1=getvar(csfin1);
	cini1=getvar(ccini1);
	cfin1=getvar(ccfin1);

	ctype1=-1;
	if (!strcmp(cctype1,"SAMPLE")) {cini1=1;cfin1=d1->dim;}
	else if (!strcmp(cctype1,"TARGET")) {cini1=d1->dim+1;cfin1=d1->size;}
	else {
	  if  (!strcmp(cctype1,"REAL")) {ctype1=0;}
	  else if  (!strcmp(cctype1,"BIN")) {ctype1=1;}
	  else if  (!strcmp(cctype1,"INT")) {ctype1=2;}
	}	

	if (!strcmp(source,"data")) {// source data
	  sscanf(line,"command data copy  %s    %s %s %s %s %s  data   %s",dname1, csini1,csfin1,ccini1,ccfin1,cctype1,dname2);

	  getnamevar(dname1);
	  getnamevar(dname2);

	  // D2 orig
	  for(i=0;i<Dc;i++)
	    if (!strcmp(DTable[i]->name,dname2)) break;
	  d2=DTable[i];

	  ctype2=-1;
	  cini2=-1;cfin2=-1;
	  sini2=-1;sfin2=-1;
	  
	  if (d1!=NULL) {// copy
	    d2->copyto(d1,sini1,sfin1,cini1,cfin1,ctype1,sini2,sfin2,cini2,cfin2,ctype2);
	  }
	  else {//create
	    DTable[Dc]=d2->create(dname1,sini1,sfin1,cini1,cfin1,ctype1);
	    DTable[Dc]->detect();
	    Dc++;
	  }
	}//source data
	else if (!strcmp(source,"rank")) {// source data rank
	  sscanf(line,"command data copy  %s    %s %s %s %s %s  rank  %s %s %s %s %s %s",dname1, csini1,csfin1,ccini1,ccfin1,cctype1,dname2,csini2,csfin2,ccini2,ccfin2,cctype2);
	  
	  getnamevar(dname1);
	  getnamevar(dname2);

	  // D2 orig
	  for(i=0;i<Dc;i++)
	    if (!strcmp(DTable[i]->name,dname2)) break;
	  d2=DTable[i];
	  
	  sini2=getvar(csini2);
	  sfin2=getvar(csfin2);
	  cini2=getvar(ccini2);
	  cfin2=getvar(ccfin2);

	  ctype2=-1;
	  if (!strcmp(cctype2,"SAMPLE")) {cini2=1;cfin2=d2->dim;}
	  else if (!strcmp(cctype2,"TARGET")) {cini2=d2->dim+1;cfin2=d2->size;}
	  else {
	    if  (!strcmp(cctype2,"REAL")) {ctype2=0;}
	    else if  (!strcmp(cctype2,"BIN")) {ctype2=1;}
	    else if  (!strcmp(cctype2,"INT")) {ctype2=2;}
	  }	

	  if (d1!=NULL) {// copy
	    d2->copyto(d1,sini1,sfin1,cini1,cfin1,ctype1,sini2,sfin2,cini2,cfin2,ctype2);
	  }
	  else {//create
	    DTable[Dc]=d2->create(dname1,sini2,sfin2,cini2,cfin2,ctype2);
	    DTable[Dc]->detect();
	    Dc++;
	  }
	}
	else { // source Layer
	  sscanf(line,"command data copy %s %f %f %f %f %f layer %s %s",dname1,&sini1,&sfin1,&cini1,&cfin1,&ctype1,net1,layer1);

	  getnamevar(dname1);
	  fprintf(stderr,"data %s %s:%s\n",d1->name,net1,layer1);

	  sprintf(lname,"%s:%s",net1,layer1);
	  Layer *l;
	  for(i=0;i<Lc;i++)
	    if (!strcmp(LTable[i]->name,lname)) break;
	  l=LTable[i];

	  if (d1!=NULL) {
	    d1->copyL(((FLayer *)l)->N->ptr2,sini1,sfin1,cini1,cfin1,ctype1);
	  }
	}// Layer
      }//copy
    }//data
     /////////////////////////////////////
     // FOR
    /////////////////////////////////////
    else if (!strcmp(ctype,"For")) { 
      int ini=point+1;
      int fin,n;
      char vf[MAX_CHAR];
      char cini[MAX_CHAR];
      char cfin[MAX_CHAR];
      char cstep[MAX_CHAR];
      float fini,ffin,fstep;
      sscanf(line,"command For %s %s %s %s",vf,cini,cstep,cfin);

      fini=getvar(cini);
      ffin=getvar(cfin);
      fstep=getvar(cstep);

      int r=0;
      for(fin=ini;;fin++) {
	strcpy(line,block[fin]);
	sscanf(line,"%s %s ",cad,cad2);
	if (!strcmp(cad2,"For")) r++;
	if (!strcmp(cad2,"EndFor")) {
	  if (r==0) break;
	  else r--;
	}
      }

      IBlock *niblock=new IBlock(this,ini,fin-1);
      //fprintf(stderr,"For loop %f %f %f, %d instructions\n",fini,ffin,fstep,fin-ini+1);
      for(float r=fini;r<=ffin;r+=fstep) {
	setvar(vf,r);
	niblock->run();
	r=getvar(vf);
      }
      point=fin;
    }
    /////////////////////////////////////
    // IF
    /////////////////////////////////////
    else if (!strcmp(ctype,"If")) { 
      int ini=point+1;
      int fin,n;
      char var[MAX_CHAR];
      float vf;

      sscanf(line,"command If %s",vf,var);
      vf=getvar(var);

      // IF
      if (vf==1.0) {
	int r=0,found=0;
	for(fin=ini;;fin++) {
	  strcpy(line,block[fin]);
	  sscanf(line,"%s %s ",cad,cad2);
	  if (!strcmp(cad2,"If")) r++;
	  if (!strcmp(cad2,"EndIf")) {
	    if (r==0) break;
	    else r--;
	  }
	  if (!strcmp(cad2,"Else")) {
	    if (r==0) {found=fin;}
	  }
	}
	IBlock *niblock;
	if (found)
	  niblock=new IBlock(this,ini,found-1);
	else
	  niblock=new IBlock(this,ini,fin-1);
	niblock->run();
	
	point=fin;
      }
      // ELSE
      else {
	int r=0,found=0;
	for(fin=ini;;fin++) {
	  strcpy(line,block[fin]);
	  sscanf(line,"%s %s ",cad,cad2);
	  if (!strcmp(cad2,"If")) r++;
	  if (!strcmp(cad2,"EndIf")) {
	    if (r==0) break;
	    else r--;
	  }
	  if (!strcmp(cad2,"Else")) {
	    if (r==0) {found=1;ini=fin+1;break;}
	  }
	}

	if (found) {
	  int r=0;
	  for(fin=ini;;fin++) {
	    strcpy(line,block[fin]);
	    sscanf(line,"%s %s ",cad,cad2);
	    if (!strcmp(cad2,"If")) r++;
	    if (!strcmp(cad2,"EndIf")) {
	      if (r==0) break;
	      else r--;
	    }
	  }
	}
	IBlock *niblock=new IBlock(this,ini,fin-1);
	niblock->run();
	point=fin;
      }
    }
    /////////////////////////////////////
    // ECHO
    /////////////////////////////////////
    else if (!strcmp(ctype,"echo")) { 
      sscanf(line,"command echo %s",var);
      if (!strcmp(var,"-r")) {
	fprintf(stderr,"\r");
      }
      else if (!strcmp(var,"-n")) {
	fprintf(stderr,"\n");
      }
      else {
	char *pch;
	pch=strchr(line,'\"');
	if (pch==NULL) {
	  sscanf(line,"command echo %s",var);
	  fv=getvar(var);
	  if (fv==round(fv)) {
	    int d=round(fv);
	    fprintf(stderr,"%d ",d);
	  }
	  else
	    fprintf(stderr,"%f ",fv);

	}
	else{
	  pch=strtok(line,"\"");
	  pch = strtok (NULL,"\"");
	  fprintf(stderr,"%s ",pch);
	}
      }
    }

  }//runcommand


  void runamendment(char *line) {
    char arg[MAX_CHAR];
    char var[MAX_CHAR];
    char lname[MAX_CHAR];
    char cad[MAX_CHAR];
    char cad2[MAX_CHAR];
    char atype[MAX_CHAR];
    int i;
    float fv;

    sscanf(line,"amendment %s ",atype);
    if (VERBOSE) fprintf(stderr,"#### %s\n",line);
    if (!strcmp(atype,"network")) {

      sscanf(line,"amendment network %s %s %s\n",cad,arg,var);
      fv=getvar(var);

      Net *net;
      for(i=0;i<Nc;i++)
	if (!strcmp(NTable[i]->name,cad)) break;
      net=NTable[i];

      if (!strcmp(arg,"l2")) net->setl2(fv);
      else if (!strcmp(arg,"l1")) net->setl1(fv);
      else if (!strcmp(arg,"maxn")) net->setmaxn(fv);
      else if (!strcmp(arg,"mu")) net->setmu(fv);
      else if (!strcmp(arg,"mmu")) net->setmmu(fv);
      else if (!strcmp(arg,"drop")) net->setdrop(fv);
      else if (!strcmp(arg,"bn")) net->setbn(fv);
      else if (!strcmp(arg,"act")) net->setact(fv);
      else if (!strcmp(arg,"noiser")) net->setnoiser(fv);
      else if (!strcmp(arg,"noiseb")) net->setnoiseb(fv);
      else if (!strcmp(arg,"noisesd")) net->setnoisesd(fv);
      else if (!strcmp(arg,"lambda")) net->setlambda(fv);
      else if (!strcmp(arg,"flip")) net->setflip(fv);
      else if (!strcmp(arg,"cropmode")) net->setcropmode(fv);
    }
    else if (!strcmp(atype,"layer")) {
      sscanf(line,"amendment layer %s %s %s %s\n",cad,cad2,arg,var);
      fv=getvar(var);

      sprintf(lname,"%s:%s",cad,cad2);

      Layer *l;
      for(i=0;i<Lc;i++)
	if (!strcmp(LTable[i]->name,lname)) break;
      l=LTable[i];
	
      if (!strcmp(arg,"l2")) l->setl2(fv);
      else if (!strcmp(arg,"l1")) l->setl1(fv);
      else if (!strcmp(arg,"maxn")) l->setmaxn(fv);
      else if (!strcmp(arg,"mu")) l->setmu(fv);
      else if (!strcmp(arg,"mmu")) l->setmmu(fv);
      else if (!strcmp(arg,"drop")) l->setdrop(fv);
      else if (!strcmp(arg,"bn")) l->setbn(fv);
      else if (!strcmp(arg,"noiser")) l->setnoiser(fv);
      else if (!strcmp(arg,"noiseb")) l->setnoiseb(fv);
      else if (!strcmp(arg,"noisesd")) l->setnoisesd(fv);
      else if (!strcmp(arg,"act")) l->setact(fv);
      else if (!strcmp(arg,"bn")) l->setbn(fv);
      else if (!strcmp(arg,"lambda")) l->setlambda(fv);
      else if (!strcmp(arg,"flip")) l->setflip(fv);
    }
    else if (!strcmp(atype,"data")) {
      Data *d;
      sscanf(line,"amendment data %s %s %s ",cad,arg,var);
      fv=getvar(var);

      for(i=0;i<Dc;i++)
	if (!strcmp(DTable[i]->name,cad)) break;
      d=DTable[i];

      if (!strcmp(arg,"balance")) d->setbalance(fv);
    }
  }

  ///------@
  void runShell(char *line) 
  {
    line=line+6;
    system(line);
  }
  void runrename(char *line)
  {
    char fname1[100],fname2[100],name[100],var[100],ext[100];
    char com[100];

    sscanf(line,"rename %s %s %s %s",fname1,name,var,ext);

    int i=getvar(var);

    sprintf(fname2,"%s%d%s",name,i,ext);

    sprintf(com,"mv %s %s",fname1,fname2);

    fprintf(stderr,"%s\n",com);
    system(com);
  }

  void run() {
    char line[MAX_CHAR];
    char cad[MAX_CHAR];

    for(point=0;point<sb;point++) {
      strcpy(line,block[point]);
      if (VERBOSE) fprintf(stderr,"%d: %s",point+1,line);
      sscanf(line,"%s ",cad);

      if (!strcmp(cad,"End")) return;
      else if (!strcmp(cad,"Const")) runConst(line);
      else if (!strcmp(cad,"Data")) runData(line);
      else if (!strcmp(cad,"Network")) runNetwork(line);
      else if (!strcmp(cad,"data")) rundata(line);
      else if (!strcmp(cad,"layer")) runlayer(line);
      else if (!strcmp(cad,"link")) runlink(line);
      else if (!strcmp(cad,"EndNetwork")) runendnet(line);
      else if (!strcmp(cad,"var")) runVar(line);
      else if (!strcmp(cad,"exit")) exit(1);
      else if (!strcmp(cad,"command")) runcommand(line);
      else if (!strcmp(cad,"amendment")) runamendment(line);
      ///---- @
      else if (!strcmp(cad,"shell")) runShell(line);      
      else if (!strcmp(cad,"rename")) runrename(line);      
      else if (!strcmp(cad,"evar")) runevar(line);
      else if (!strcmp(cad,"shared")) runshared(line);
    }
  }
};


int main(int argc, char **argv) {
  //Juan-> Fix as you want
  Eigen::initParallel();

  if (argc<2) {
    if (VERBOSE) fprintf(stderr,"use: layers netfile\n");
    exit(1);
  }
  if (argc==2)
    netparser(argv[1]);

  lut_init();

  FILE *fin;
  if (argc==2)
    fin=fopen("netparser.run","rt");
  else
    fin=fopen(argv[2],"rt");

  if (fin==NULL) {
    if (VERBOSE) fprintf(stderr,"Error netparser.run not found!!!\n");
    exit(1);
  }

  //exit(1);

  DTable=(Data **)malloc(MAX_ITEM*sizeof(Data *));
  LTable=(Layer **)malloc(MAX_ITEM*sizeof(Layer *));
  NTable=(Net **)malloc(MAX_ITEM*sizeof(Net *));

  strcpy(logname,"netparser.log");

  int i=0;
  char line[MAX_CHAR];
  while (!feof(fin)) {
    char *read=fgets(line, MAX_CHAR, fin);
    i++;
  }
  fclose(fin);
  IBlock *block=new IBlock(i);

  if (argc==2)
    fin=fopen("netparser.run","rt");
  else
    fin=fopen(argv[2],"rt");

  i=0;
  while (!feof(fin)) {
    char *read=fgets(line, MAX_CHAR, fin);
    block->put(line,i);
    i++;
  }
  block->run();


}
