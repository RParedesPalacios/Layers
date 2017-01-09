#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <string.h>

#include "layer.h"
#include "data.h"
#include "net.h"
#include "utils.h" 

extern "C" int netparser (char *nfich) ;

#define MAX_ITEM 1000
#define MAX_CHAR 1000
#define GPU 0

int seed;
int gpu;

int main(int argc, char **argv) {
  int batch=100;
  int threads=4;
  char cad[MAX_CHAR];
  char cad2[MAX_CHAR];
  char cad3[MAX_CHAR];
  char logname[MAX_CHAR];

  Eigen::initParallel();

 
  if (argc<2) {
    fprintf(stderr,"use: layers netfile\n");
    exit(1);
  }

  // Call new parser
  if (argc==2) 
    netparser(argv[1]);

  lut_init();

  FILE *fe,*fin;
  FILE *flog;
  int i,j;
  char name[MAX_CHAR];
  char fname[MAX_CHAR];
  char ftype[MAX_CHAR];
  char line[MAX_CHAR];
  char com[MAX_CHAR];
  size_t nb=MAX_CHAR;

  // DATA
  Data **DTable;
  int Dc=0;
  DTable=(Data **)malloc(MAX_ITEM*sizeof(Data *));
  
  // Layer
  Layer **LTable;
  int Lc=0;
  LTable=(Layer **)malloc(MAX_ITEM*sizeof(Layer *));
      
  // RLayer
  char RLTable[MAX_ITEM][MAX_CHAR];
  int RLc=0;

  // Network
  Net **NTable;
  int Nc=-1;
  NTable=(Net **)malloc(MAX_ITEM*sizeof(Net *));
  
  
  char ltype[MAX_CHAR];
  char ldata[MAX_CHAR];
  char innet[MAX_CHAR];  
  char lname[MAX_CHAR];
  
  int nk,kr,kc,kz,size,sizer,sizec,np,rpad,cpad,stride,cc,cr;
  int act,ae,nn,val;
  char crit[MAX_CHAR];
  char arg[MAX_CHAR];
  float fv;
  int iv;
  Layer *l1,*l2;
  char net1[MAX_CHAR],net2[MAX_CHAR],layer1[MAX_CHAR],layer2[MAX_CHAR];
  ////////


  // Read netparser.run
  if (argc==2) 
    fin=fopen("netparser.run","rt");
  else 
    fin=fopen(argv[2],"rt");

  if (fin==NULL) {
    fprintf(stderr,"Error netparser.run not found!!!\n");
    exit(1);
  }

  while (!feof(fin)) {

    char *read=fgets(line, MAX_CHAR, fin);

    fprintf(stderr,"-->%s",line);

    sscanf(line,"%s ",cad);
    if (!strcmp(cad,"END")) exit(1);

    ///////////////////////////
    // Const
    ///////////////////////////
    if (!strcmp(cad,"Const")) {
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
      if (!strcmp(cad,"seeds")) {
	sscanf(line,"Const %s %d\n",cad,&seed);
	fprintf(stderr,"setting random seed to %d\n",seed);      
	srand(seed);
      }
      if (!strcmp(cad,"GPU")) {
	sscanf(line,"Const %s %d\n",cad,&gpu);
	fprintf(stderr,"setting gpu devices to %d\n",gpu);      
	
      }

    }
    ///////////////////////////
    // Data
    ///////////////////////////
    else if (!strcmp(cad,"Data")) {
      //Data D4 2 creadata N0 k0 N0 k4 filename ./lola.tr
      sscanf(line,"Data %s %d %s\n",name,&iv,cad);
      if (!strcmp(cad,"creadata")) {
	sscanf(line,"Data %s 2 creadata %s %s %s %s filename %s\n",name,net1,layer1,net2,layer2,fname);
	
	for(i=0;i<Nc;i++)
	  if (!strcmp(NTable[i]->name,net1)) break;
	Net *n=NTable[i];
	
	sprintf(cad,"%s:%s",net1,layer1);
	for(i=0;i<Lc;i++) {
	  if (!strcmp(cad,LTable[i]->name)) break;
	}
	Layer *l1=LTable[i];

	sprintf(cad,"%s:%s",net1,layer2);
	for(i=0;i<Lc;i++) {
	  if (!strcmp(cad,LTable[i]->name)) break;
	}
	Layer *l2=LTable[i];

	//if (l1->lin==0) l1->din=n->Dtrain->dim;

	fprintf(stderr,"New data %s from %s,%d->%s,%d\n",name,l1->name,l1->din,l2->name,l2->din);

	DTable[Dc]=new Data(20*n->Dtrain->num,l1->din,l2->din,batch,name);

	n->fillData(DTable[Dc],l1,l2);

	DTable[Dc]->SaveBin(fname);
      }
      else {
	sscanf(line,"Data %s 2 filename %s filetype %s\n",name,fname,ftype);
	if (!strcmp(ftype,"ascii")) 
	  DTable[Dc]=new Data(fname, batch,name);
	else 
	  DTable[Dc]=new Data(1,fname, batch,name);
      }
      Dc++;
    }
    ///////////////////////////
    // Network
    ///////////////////////////
    else if (!strcmp(cad,"Network")) {
      Nc++;
      sscanf(line,"Network %s\n",name);
      fprintf(stderr,"Creating network %s\n",name);
      NTable[Nc]=new Net(name);
      strcpy(innet,name);
    }
    ///////////////////////////
    // Net Data
    ///////////////////////////
    else if (!strcmp(cad,"data")) {
      sscanf(line,"data %s %s",cad,cad2);
      int enc=0;
      for(i=0;i<Dc;i++) {
	if (!strcmp(cad2,DTable[i]->name)) {enc=1;break;}
      }
      
      if (!strcmp(cad,"tr")) 
	NTable[Nc]->Dtrain=DTable[i];
      else if (!strcmp(cad,"ts")) 
	NTable[Nc]->Dtest=DTable[i];
      else NTable[Nc]->Dval=DTable[i];
    }
    ///////////////////////////
    // Net Layer
    ///////////////////////////
    else if (!strcmp(cad,"layer")) {
      
      sscanf(line,"layer %s ",name);
      sprintf(lname,"%s:%s",innet,name);

      sscanf(line,"layer %s %s ",name,ltype);
      ////////////// CI //////////////
      if (!strcmp(ltype,"CI")) {
	sscanf(line,"layer %s CI 5 nz %d nr %d nc %d cr %d cc %d\n",name,&kz,&kr,&kc,&cr,&cc);
	  
	sprintf(lname,"%s:%s",innet,name);
	LTable[Lc]=new ICLayer(NTable[Nc]->Dtrain,batch,kz,kr,kc,cr,cc,lname);
	NTable[Nc]->addLayer(LTable[Lc]);
	if ((kr!=cr)||(kc!=cc)) {
	  NTable[Nc]->crops=((kr-cr)+1)*((kc-cc)+1);
	  fprintf(stderr,"Input with %d crops\n",NTable[Nc]->crops);
	}

	Lc++;
      }
      ////////////// FI //////////////
      else if (!strcmp(ltype,"FI")) {
	sscanf(line,"layer %s FI 0\n",name);
	sprintf(lname,"%s:%s",innet,name);
	  
	LTable[Lc]=new IFLayer(NTable[Nc]->Dtrain,batch,lname);
	NTable[Nc]->addLayer(LTable[Lc]);
	Lc++;
      
      }
      ////////////// C //////////////
      else if (!strcmp(ltype,"C")) {
	sscanf(line,"layer %s %s 6 nk %d kr %d kc %d rpad %d cpad %d stride %d\n",name,ltype,&nk,&kr,&kc,&rpad,&cpad,&stride);
	sprintf(lname,"%s:%s",innet,name);
	if (stride<1) stride=1;
	LTable[Lc]=new CLayer(nk,kr,kc,batch,rpad,cpad,stride,lname);
	NTable[Nc]->addLayer(LTable[Lc]);
	Lc++;
      }
      
      ////////////// MP //////////////
      else if (!strcmp(ltype,"MP")) {
	sscanf(line,"layer %s MP 2 sizer %d sizec %d\n",name,&sizer,&sizec);
	sprintf(lname,"%s:%s",innet,name);
	    
	LTable[Lc]=new PLayer(batch,sizer,sizec,lname);
	NTable[Nc]->addLayer(LTable[Lc]);
	Lc++;
      }
      ////////////// CAT //////////////
      else if (!strcmp(ltype,"CA")) {
	sscanf(line,"layer %s CA 0\n",name);
	sprintf(lname,"%s:%s",innet,name);
	    
	LTable[Lc]=new CatLayer(batch,lname);
	NTable[Nc]->addLayer(LTable[Lc]);
	Lc++;
      }
      
      ////////////// R //////////////
      else if (!strcmp(ltype,"R")) { 
	//layer f0 R 2 prevlayer N1 p1 local 1
	int val;
	sscanf(line,"layer %s R 2 prevlayer %s %s %s %d\n",name,cad,cad2,cad3,&val);

	sprintf(lname,"%s:%s",cad,cad2);

	for(i=0;i<Lc;i++) {
	  if (!strcmp(lname,LTable[i]->name)) break;
	}
	sprintf(lname,"%s:%s",innet,name);

	LTable[Lc]=new FLayer(LTable[i],batch,lname);
	NTable[Nc]->addLayer(LTable[i]);
	NTable[Nc]->addLayer(LTable[Lc]);
	Lc++;
      }
      ////////////// FO //////////////
      else if (!strcmp(ltype,"FO")) {
	sscanf(line,"layer %s FO %d criterion %s %s %d\n",name,&val,crit,cad,&ae);
	sprintf(lname,"%s:%s",innet,name);

	if (!strcmp(crit,"classification")) {
	  act=10;
	  LTable[Lc]=new OFLayer(NTable[Nc]->Dtrain,batch,act,lname);
	}
	else {
	  act=0;
	  if (strcmp(cad,"autoencoder")) {
	    if (val==2) {
	      sscanf(line,"layer %s FO 2 criterion regression %s %s\n",name,net1,layer1);
	      sprintf(cad,"%s:%s",net1,layer1);
	      fprintf(stderr,"Target %s.%s\n",net1,layer1);
	      for(i=0;i<Lc;i++) {
		if (!strcmp(cad,LTable[i]->name)) break;
	      }
	      LTable[Lc]=new OFLayer((FLayer*)LTable[i],batch,lname);
	    }
	    else {
	      LTable[Lc]=new OFLayer(NTable[Nc]->Dtrain,batch,act,lname);
	    }
	  }
	  else {
	    if (ae) 
	      LTable[Lc]=new OFLayer(NTable[Nc]->Dtrain,batch,act,ae,lname);
	    else 
	      LTable[Lc]=new OFLayer(NTable[Nc]->Dtrain,batch,act,lname);
	  }	
	}
	NTable[Nc]->addLayer(LTable[Lc]);
	Lc++;
            
      }
      //F
      else if (!strcmp(ltype,"F")) {
	sscanf(line,"layer %s F 1 numnodes %d\n",name,&nn);
	sprintf(lname,"%s:%s",innet,name);

	LTable[Lc]=new FLayer(nn,batch,lname);
	NTable[Nc]->addLayer(LTable[Lc]);
	Lc++;
      } 
    }
 
    ///////////////////////////
    // Net Link
    ///////////////////////////
    else if (!strcmp(cad,"link")) {
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
    else if (!strcmp(cad,"END_Network")) {
      NTable[Nc]->Init(flog);
      NTable[Nc]->net2dot();
      NTable[Nc]->setthreads(threads);
    }

    ///////////////////////////
    // Command
    ///////////////////////////
    else if (!strcmp(cad,"command")) {
      int par,par2;
      Data *d;
   
      //command Nd ld copy Ns ls
      sscanf(line,"command %s %s %s ",cad,cad2,com);
      if (!strcmp(com,"copy")) {
	sscanf(line,"command %s %s copy %s %s\n",net1,layer1,net2,layer2);

        for(i=0;i<Nc;i++)
          if (!strcmp(NTable[i]->name,net1)) break;
        Net *n1=NTable[i];

        for(i=0;i<Nc;i++)
          if (!strcmp(NTable[i]->name,net2)) break;
        Net *n2=NTable[i];

        sprintf(cad,"%s:%s",net1,layer1);
        for(i=0;i<Lc;i++) {
          if (!strcmp(cad,LTable[i]->name)) break;
        }
        Layer *l1=LTable[i];

        sprintf(cad,"%s:%s",net2,layer2);
        for(i=0;i<Lc;i++) {
          if (!strcmp(cad,LTable[i]->name)) break;
        }
        Layer *l2=LTable[i];
	
	n1->copy(l1,l2);

      }

      sscanf(line,"command %s %s %d ",cad,com,&par);
      if (!strcmp(com,"zscore")) {
	for(i=0;i<Dc;i++) 
	  if (!strcmp(DTable[i]->name,cad)) break;
	d=DTable[i];
	if (par==0) {
	  d->zscore();
	}
	else{
	  sscanf(line,"command %s zscore %d %s",cad,&par,cad2);

	  for(i=0;i<Dc;i++) 
	    if (!strcmp(DTable[i]->name,cad)) break;
	  d=DTable[i];

	  for(i=0;i<Dc;i++)
	    if (!strcmp(DTable[i]->name,cad2)) break;

	  d->zscore(DTable[i]);
	}
      }
      if (!strcmp(com,"center")) {
	for(i=0;i<Dc;i++) 
	  if (!strcmp(DTable[i]->name,cad)) break;
	d=DTable[i];
	if (par==0) {
	  d->center();
	  
	}
	else{
	  sscanf(line,"command %s center %d %s",cad,&par,cad2);

	  for(i=0;i<Dc;i++) 
	    if (!strcmp(DTable[i]->name,cad)) break;
	  d=DTable[i];

	  for(i=0;i<Dc;i++)
	    if (!strcmp(DTable[i]->name,cad2)) break;
	  
	  d->center(DTable[i]);
	}
      }
      if (!strcmp(com,"store")) {
        sscanf(line,"command %s %s 1 %s ",cad,com,cad2);
        for(i=0;i<Dc;i++)
          if (!strcmp(DTable[i]->name,cad)) break;
        d=DTable[i];

        d->SaveBin(cad2);
      }

      if (!strcmp(com,"div")) {
	sscanf(line,"command %s %s 1 %f ",cad,com,&fv);
	for(i=0;i<Dc;i++) 
	  if (!strcmp(DTable[i]->name,cad)) break;
	d=DTable[i];
	
	d->div(fv);
      }
      if (!strcmp(com,"mul")) {
	sscanf(line,"command %s %s 1 %f ",cad,com,&fv);
	for(i=0;i<Dc;i++) 
	  if (!strcmp(DTable[i]->name,cad)) break;
	d=DTable[i];
	
	d->mul(fv);
      }
      if (!strcmp(com,"add")) {
	sscanf(line,"command %s %s 1 %f ",cad,com,&fv);
	for(i=0;i<Dc;i++) 
	  if (!strcmp(DTable[i]->name,cad)) break;
	d=DTable[i];
	
	d->add(fv);
      }
      if (!strcmp(com,"sub")) {
	sscanf(line,"command %s %s 1 %f ",cad,com,&fv);
	for(i=0;i<Dc;i++) 
	  if (!strcmp(DTable[i]->name,cad)) break;
	d=DTable[i];
	
	d->sub(fv);
      }
      if (!strcmp(com,"maxmin")) {
        for(i=0;i<Dc;i++)
          if (!strcmp(DTable[i]->name,cad)) break;
        d=DTable[i];
        d->maxmin();
      }

      //command D1 yuv 0
      if (!strcmp(com,"yuv")) {
	for(i=0;i<Dc;i++) 
	  if (!strcmp(DTable[i]->name,cad)) break;
	d=DTable[i];
	d->YUV();
      }
      else if (!strcmp(com,"train")) {
	if (!strcmp(cad,"list")) {
	  int nets;
	  int lepoch,lbatch,liter;
	  Net **Nlist=(Net **)malloc(MAX_ITEM*sizeof(Net *));

	  sscanf(line,"command list train numiter %d numnet %d",&liter,&nets);

	  fprintf(stderr,"Training %d nets %d iter\n",nets,liter);
	  for(i=0;i<nets;i++) {
	    char *read=fgets(line, MAX_CHAR, fin);
	    fprintf(stderr,"-->%s",line);

	    sscanf(line,"command %s train %d nepoch %d numbatch %d ",cad,&par,&lepoch,&lbatch);
	    for(j=0;j<Nc;j++) 
	      if (!strcmp(NTable[j]->name,cad)) break;
	    Nlist[i]=NTable[j];
	    	   
	    fprintf(stderr,"%s\n",Nlist[i]->name);
	  }

	  char *read=fgets(line, MAX_CHAR, fin);
	  fprintf(stderr,"-->%s",line);
	  lut_init();
	  
	  for (int it=0;it<liter;it++) {

	    for(i=0;i<nets;i++) 
	      Nlist[i]->Dtrain->preparebatch(1);
	    	    
	    for(j=0;j<lepoch;j++) {
	      for(i=0;i<nets;i++) 
		Nlist[i]->trainbatch(lbatch,j);
	    }
	    
	    fprintf(stderr,"\n");
	    for(i=0;i<nets;i++) {
	      if (Nlist[i]->Dval!=NULL) Nlist[i]->evaluate(Nlist[i]->Dval);
	      if (Nlist[i]->Dtest!=NULL) Nlist[i]->evaluate(Nlist[i]->Dtest);
	    }
	    fprintf(stderr,"\n");
	  }

	}
	else{
	  sscanf(line,"command %s train 1 nepoch %d",cad,&par);
	  for(i=0;i<Nc;i++) 
	    if (!strcmp(NTable[i]->name,cad)) break;
	 
	  NTable[i]->train(par);

	}
      }
      else if (!strcmp(com,"save")) {
	sscanf(line,"command %s save 1 %s",cad,cad2);
	for(i=0;i<Nc;i++) 
	  if (!strcmp(NTable[i]->name,cad)) break;
	FILE *fe=fopen(cad2,"wt");
	NTable[i]->save(fe);
      }
      else if (!strcmp(com,"load")) {
	sscanf(line,"command %s load 1 %s",cad,cad2);
	for(i=0;i<Nc;i++) 
	  if (!strcmp(NTable[i]->name,cad)) break;
	FILE *fe=fopen(cad2,"rt");
	NTable[i]->load(fe);
      }
      else if (!strcmp(com,"testout")) {
	sscanf(line,"command %s testout 1 %s",cad,cad2);
	for(i=0;i<Nc;i++) 
	  if (!strcmp(NTable[i]->name,cad)) break;
	FILE *fe=fopen(cad2,"wt");
	NTable[i]->testOut(fe);
      }
      else if (!strcmp(com,"evaluate")) {
	sscanf(line,"command %s evaluate 1 %s",cad,cad2);
	for(i=0;i<Nc;i++) 
	  if (!strcmp(NTable[i]->name,cad)) break;

	for(j=0;j<Dc;j++) 
	  if (!strcmp(DTable[j]->name,cad2)) break;
	NTable[i]->evaluate(DTable[j]);
      }
      // script over a particular layer
      else {
	sscanf(line,"command %s %s %s ",cad,cad2,com);
	if (!strcmp(com,"printkernels")) {
	  sscanf(line,"command %s %s printkernels 1 %s",cad,cad2,cad3);
	  sprintf(lname,"%s:%s",cad,cad2);

	  Layer *l;
	  for(i=0;i<Lc;i++)
	    if (!strcmp(LTable[i]->name,lname)) break;
	  l=LTable[i];
	  
	  fprintf(stderr,"printkernels %s\n",l->name);

	  FILE *fe=fopen(cad3,"wt");
	  l->printkernels(fe);
	}
      }
    }
    ///////////////////////////                                                
    // Amendment
    ///////////////////////////
    else if (!strcmp(cad,"amendment")) {
      sscanf(line,"amendment %s %s ",cad,cad2);
      if (!strcmp(cad2,"balance")) {
	Data *d;
	int par;
	sscanf(line,"amendment %s %s %d ",cad,cad2,&par);
	for(i=0;i<Dc;i++) 
	  if (!strcmp(DTable[i]->name,cad)) break;
	d=DTable[i];
	d->setbalance(par);	
      }
      else if (!strcmp(cad2,"*")) {
	sscanf(line,"amendment %s * %s %f\n",cad,arg,&fv);
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
	else if (!strcmp(arg,"adv")) net->setadv(fv);
	else if (!strcmp(arg,"advf")) net->setadvf(fv);
	else if (!strcmp(arg,"cropmode")) net->setcropmode(fv);
      }
      else {
	
	sscanf(line,"amendment %s %s %s %f\n",cad,cad2,arg,&fv);
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
	else if (!strcmp(arg,"adv")) l->setadv(fv);
	else if (!strcmp(arg,"advf")) l->setadvf(fv);

      }

      
    }
   
  }



}
