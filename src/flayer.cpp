#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <iostream>

#include "layer.h"
#include "net.h"

#include "utils.h"
#include "tensor.h"

#ifdef MKL 
#define EIGEN_USE_MKL_ALL
#endif

#include "Eigen/Dense"


/// Eigen
using namespace Eigen;
using namespace std;


/////////
//Helper funciton
#ifdef fGPU
#include "./gpu/execution.h"
void printDebug(float* p, const char*, int total)
{
float* aux = (float*)malloc(total*sizeof(float));

gpu_tensor_op.copy_data(aux,p,FROMGPU,total*sizeof(float));
float suma=0.0;

for (int i=0;i<total;i++)
{
	printf("%f ",aux[i]);
        suma+=aux[i];
}

printf("\nvalor de la suma:%f \n",suma);
}

#endif
////////

////////////////////////////////////
///// FULLY CONNECTED LAYER CLASS
////////////////////////////////////

FLayer::FLayer()
{

}


void FLayer::mem()
{
  int i;

  W=new Tensor(MAX_CONNECT,UNSET,UNSET);
  gW=new Tensor(MAX_CONNECT,UNSET,UNSET);
  pgW=new Tensor(MAX_CONNECT,UNSET,UNSET);
  b=new Tensor(MAX_CONNECT,UNSET);

  gb=new Tensor(MAX_CONNECT,UNSET);
  pgb=new Tensor(MAX_CONNECT,UNSET);
  
  N=new Tensor(batch,din);
  E=new Tensor(batch,din);
  dE=new Tensor(batch,din);
  Delta=new Tensor(batch,din);
  dvec=new Tensor(din);

  //BN
  bn_mean=new Tensor(din);
  bn_var=new Tensor(din);
  bn_gmean=new Tensor(din);
  bn_gvar=new Tensor(din);
  bn_g=new Tensor(din);
  bn_b=new Tensor(din);
  
  bn_E=new Tensor(batch,din);
  BNE=new Tensor(batch,din);

  bn_g->set(1.0);
  bn_b->set(1.0);

  gbn_mean=new Tensor(din);
  gbn_var=new Tensor(din);
  gbn_g=new Tensor(din);
  gbn_b=new Tensor(din);
  gbn_E=new Tensor(batch,din);
}

FLayer::FLayer(int batch,char *name):Layer(batch,name)
{
  type=1;
  act=1;
}



FLayer::FLayer(int in,int batch,char *name):Layer(batch,name)
{

  din=in;
  type=1;
  act=1;

  if (in<=0) {
    fprintf(stderr,"Error %s with %d neurons\n",name,in);
    exit(1);
  }

  mem();

  fprintf(stderr,"Creating FC layer (%s) with %d neurons\n",name,in);

}

//Reshape Layer
FLayer::FLayer(Layer *In,int batch,char *name):Layer(batch,name)
{
  if (In->type==FLAYER) {

  }
  else if (In->type==OLAYER) {
    OLayer *l=(OLayer *)In;
    din=l->din;
    if (din<=0) {
      fprintf(stderr,"Error %s with %d neurons\n",name,din);
      exit(1);
    }
    reshape=1;
  }
  else {
    CLayer *cin;

    cin=(CLayer *)In;
    din=cin->outz*cin->outr*cin->outc;
    reshape=1;
    if (din<=0) {
      fprintf(stderr,"Error %s with %d neurons\n",name,din);
      exit(1);
    }
  }
  type=1;
  // Linear
  act=0;

  mem();

  fprintf(stderr,"Creating Reshape layer (%s) with %d neurons\n",name,din);

  In->addchild(this);

}



void FLayer::addchild(Layer *li)
{

  int enc=0,i,j;

  for(i=0;i<lout;i++)
    if (Lout[i]==li) enc=1;

  if (enc) {
    fprintf(stderr,"%s->%s just connected\n",this->name,li->name);
  }
  else {

    if (li->type==1) {
      FLayer *l=(FLayer *)li;

      Lout[lout]=l;

      W->subTensor(lout)->resize(din,l->din);
      b->subTensor(lout)->resize(l->din);
      
      // initialice here!
      double s=sqrt(2.0/din);
      W->subTensor(lout)->set_rand_gauss(0,s);
      b->subTensor(lout)->set(0.1);

      gW->subTensor(lout)->resize(din,l->din);
      gW->subTensor(lout)->set(0.0);

      pgW->subTensor(lout)->resize(din,l->din);
      pgW->subTensor(lout)->set(0.0);
      
      gb->subTensor(lout)->resize(l->din);
      gb->subTensor(lout)->set(0.0);

      pgb->subTensor(lout)->resize(l->din);
      pgb->subTensor(lout)->set(0.0);

      lout++;

      fprintf(stderr,"Connecting %s --> %s\n",name,li->name);
      l->addparent(this);
    }
    else if (li->type==OLAYER) {
      OLayer *l=(OLayer *)li;

      Lout[lout]=l;

      fprintf(stderr,"Connecting %s --> %s\n",name,li->name);
      l->addparent(this);
      lout++;
    }
    else{
      fprintf(stderr,"Error: %s->%s Only FC or O can be connected after FC\n",name,li->name);
      exit(1);
    }
  }

}


void FLayer::addparent(Layer *l)
{
  if ((lin>0)&&(reshape)) {
    fprintf(stderr,"Error, reshape layer (%s) can only have one parent layer, (%s)\n",name,l->name);
    exit(1);
  }

  Lin[lin]=l;
  lin++;

}


void FLayer::initialize()
{
  //nothing here
}

void FLayer::resetmomentum()
{
  int k;

  if (VERBOSE) fprintf(stderr,"layer %s reset momentum\n",name);

  for(k=0;k<lout;k++) {
    pgW->subTensor(k)->set(0.0);
    pgb->subTensor(k)->set(0.0);
  }

}

void FLayer::reset()
{
  int i,k;

  if (VERBOSE) fprintf(stderr,"RESET Layer %s\n",name);


  E->set(0.0);
  N->set(0.0);
  Delta->set(0.0);
  
  for(k=0;k<lout;k++) {
    gW->subTensor(k)->set(0.0);
    gb->subTensor(k)->set(0.0);
  }
}

void FLayer::resetstats()
{
  bnc=0;

  bn_gmean->set(0.0);
  bn_gvar->set(0.0);

}


//////////////////////
///// FORWARD
//////////////////////
void FLayer::fBN()
{
  int i,j;


  //CPU
  if (trmode) {
    bnc++;

    Tensor::forwardBN_training(batch,
			       E,
			       bn_mean,
			       bn_var,
			       bn_E,
			       bn_g,
			       bn_b,
			       BNE,
			       bn_gmean,
			       bn_gvar,
			       bnc,
			       noiser,
			       noisesd);
  }
  else { // testmode
    Tensor::forwardBN_inference(batch,E,bn_mean,bn_var,bn_E,bn_g,bn_b,BNE,bnc);
  }
}

void FLayer::forward()
{
  int k,i,j,z,r,c;
  FLayer *l;
  CLayer *cin;

  if (reshape) {
    
    if (Lin[0]->type==OLAYER) {
      OLayer *l;
      l=(OLayer *)Lin[0];
      N->copy(l->N);
      if (VERBOSE) fprintf(stderr,"from OP(%s) = %f\n",l->name,N->norm());

    }
    else {
      cin=(CLayer *)Lin[0];
      N->copy(cin->N);
    
      if (VERBOSE) fprintf(stderr,"from CNN (%s) = %f\n",cin->name,N->norm());

    }
  }
  else{ // !reshape
    /////////////////////////////
    // PREACTIVATION
    /////////////////////////////
  
    if (bn) {
      fBN();
    }  
    else {
      // Gaussian Noise
      if ((trmode)&&(noiser>0.0)) {
	E->add_noise_gauss(noiser,0.0,noisesd);
      }
    }
  
    if (VERBOSE) fprintf(stderr,"E(%s) = %f\n",name,E->norm());
  
    ////////////////////////////
    // ACTIVATION
    ////////////////////////////
  
    if (bn) 
      Tensor::activation(BNE,N,act);
    else 
      Tensor::activation(E,N,act);
  /*
    printf("==========VALORES EN FORWARD\n") ;
    printf("====== ACTIVATION\n");
    printf("%d \n",act); 
    printf("======E\n");
    printDebug(E->gptr,"E",20);
    printf("======N\n");
    printDebug(N->gptr,"N",20);
    printf("======W\n");
    if(act!=ACT_SOF)
    {
    printDebug(W->subTensor(0)->gptr,"N",20);
    printf("======B\n");
    printDebug(b->subTensor(0)->gptr,"N",10);}
    getchar();*/
    ////////////////////////////
    // POST-ACTIVATION
    ////////////////////////////
    if (drop>0.0) {
      if (trmode) {
	dvec->set_rand_binary(drop);
	Tensor::maskZeros(dvec,N);
      }
      else 
	Tensor::sc_mult(N,1.0-drop,N,0);
    }
  
    if (VERBOSE) fprintf(stderr,"N(%s,%d) = %f\n",name,act,N->norm());
  }

  //////////////////////////////
  // FORWARD TO CHILD LAYERS
  //////////////////////////////
  for(i=0;i<lout;i++) {
    if (rnet->isIn(Lout[i])) {
      if (Lout[i]->type==FLAYER) {
	if (VERBOSE) fprintf(stderr,"Forward %s-->%s\n",name,Lout[i]->name);
	l=(FLayer *)Lout[i];
	
	if (VERBOSE) fprintf(stderr,"Forward %s W norm %f\n",name,W->subTensor(i)->norm());

	Tensor::mult(N,0,W->subTensor(i),0,l->E,1);
	
	//bias
	l->E->inc_2Drowwise(b->subTensor(i));
      }
    }
  }
}


void FLayer::save(FILE *fe)
{
  int k,i,j;

  save_param(fe);

  for(k=0;k<lout;k++) {
    for(i=0;i<din;i++)
      for(j=0;j<Lout[k]->din;j++)
	fprintf(fe,"%f ",W->get(k,i,j));
    
    for(j=0;j<Lout[k]->din;j++)
      fprintf(fe,"%f ",b->get(k,j));
    
    fprintf(fe,"\n");
  }
  
  if (bn) {
    for(j=0;j<din;j++)
      fprintf(fe,"%f %f %f %f ",bn_g->get(j),bn_b->get(j),bn_gmean->get(j),bn_gvar->get(j));
    
    fprintf(fe,"%d\n",bnc);
  }
  
}

void FLayer::load(FILE *fe)
{
  int k,i,j;
  double fv;
  int fsd;

  fprintf(stderr,"Loading layer %s...",name);

  load_param(fe);

  for(k=0;k<lout;k++) {
    for(i=0;i<din;i++)
      for(j=0;j<Lout[k]->din;j++) {
	fsd=fscanf(fe,"%lf ",&fv);
	W->set(k,i,j,fv);
      }
    
      for(j=0;j<Lout[k]->din;j++) {
	fsd=fscanf(fe,"%lf ",&fv);
	b->set(k,j,fv);
      }
    fsd=fscanf(fe,"\n");
  }

  if (bn) {
    for(j=0;j<din;j++) {
      fsd=fscanf(fe,"%lf ",&fv);
      bn_g->set(j,fv);
      fsd=fscanf(fe,"%lf ",&fv);
      bn_b->set(j,fv);
      fsd=fscanf(fe,"%lf ",&fv);
      bn_gmean->set(j,fv);
      fsd=fscanf(fe,"%lf ",&fv);
      bn_gvar->set(j,fv);
    }
    fsd=fscanf(fe,"%d\n",&bnc);
  }
  fprintf(stderr,"ok\n");
}


void FLayer::printkernels(FILE *fe)
{
  int k,i,j;

  for(k=0;k<lout;k++) {
    for(i=0;i<din;i++)
      for(j=0;j<Lout[k]->din;j++)
	fprintf(fe,"%f ",W->get(k,i,j));
    fprintf(fe,"\n");
  }

  fclose(fe);
}


//////////////////////////////////////////
///// BACKWARD
//////////////////////////////////////////
void FLayer::bBN()
{
  Tensor::backwardBN(batch,
			E,
			bn_E,
			bn_g,
			bn_mean,
			bn_var,
			Delta,
			gbn_g,
			gbn_b,
			gbn_E,
			gbn_mean,
			gbn_var
			 );

}


void FLayer::backward()
{
/*
    printf("==========VALORES EN BACKWARD\n");
    printf("====== ACTIVATION\n");
    printf("%d \n",act); */


  int i,j,k,ind;

  if (drop>0.0) Tensor::maskZeros(dvec,Delta);

  
  if (reshape) {
    if (VERBOSE) {
      fprintf(stderr,"%s Delta norm %f\n",name,Delta->norm());
    }
    
    if (Lin[0]->type==OLAYER) {
      OLayer *l=(OLayer *)Lin[0];
      l->Delta->copy(Delta);      
    }
    else {
      CLayer *cnn;
      cnn=(CLayer *)Lin[0];
      cnn->Delta->copy(Delta);
    }
  }
  else { //!reshape
    FLayer *l;

    if (VERBOSE) fprintf(stderr,"%s Delta norm %f\n",name,Delta->norm());

    // Delta*DerivAct

//    printf("======delta antes de activacion\n");
//    printDebug(Delta->gptr,"gW",20);

    //printf("===========BACKWARD NORMAL LAYER %d\n",act);
   // printf("===== pre activation\n");
   // printf("==E \n");
   // printDebug(E->gptr,"",10);
   // printf("==N \n");
   // printDebug(N->gptr,"",10);
   // getchar();

 
    if (act!=ACT_SOF) { // To prevent for output layers with softmax
      if (bn) 
	Tensor::dactivation(BNE,N,dE,act);
      else 
	Tensor::dactivation(E,N,dE,act);

    //printf("===== Deactivatcion \n");
   // printf("==E \n");
   // printDebug(E->gptr,"",10);
   // printf("==N \n");
   // printDebug(N->gptr,"",10);
   // printf("==dE \n");
   // printDebug(dE->gptr,"",10);
   // getchar();

    //printf("===== Delta pre\n");
    //printf("==Delta \n");
    //printDebug(Delta->gptr,"",10);

    Tensor::el_mult(Delta,0,dE,0,Delta,0);

    //printf("===== Delta pos apply dE\n");
    //printf("==Delta*dE \n");
    //printDebug(Delta->gptr,"",10);


    }
//printf("======delta despues de activacion\n");
//    printDebug(Delta->gptr,"gW",20);



    if (bn) bBN();

    for(i=0;i<lin;i++) {
      if (rnet->isIn(Lin[i])) {
	if (Lin[i]->type==FLAYER) { // Fully connected
	  l=(FLayer *)Lin[i];

	  ind=-1;
	  for(k=0;k<l->lout;k++)
	    if ((Layer *)l->Lout[k]==(Layer *)this) ind=k;
	  if (ind==-1) {fprintf(stderr,"Error no connection!!\n"); exit(1);}

	  // Compute grads
	  if (VERBOSE) fprintf(stderr,"%f %f -->\n",l->N->norm(),Delta->norm());
  
  //  printf("======delta antes de backpropaegar\n");
  //  printDebug(Delta->gptr,"gW",20);

	  Tensor::mult(l->N,1,Delta,0,l->gW->subTensor(ind),0);

	  if (!l->bn)
	    for(j=0;j<l->gb->subTensor(ind)->a;j++)
	      l->gb->subTensor(ind)->set(j,Delta->col_sum(j));

	  // back-propagate Delta
	  Tensor::mult(Delta,0,l->W->subTensor(ind),1,l->Delta,1);
   
    //printf("======gW\n");
   // printDebug(l->gW->subTensor(ind)->gptr,"gW",20);
   // getchar();

	}
      }
    }
  }
}



void FLayer::applygrads()
{
  int k,i,j;


  for(k=0;k<lout;k++) {

    // WEIGHTS
   // printf("=============APPLY GRADS");
   // printf("=============mu %f %f\n",mu,batch);

   // printf("=========W antes\n");
    //printDebug(W->subTensor(k)->gptr,"adsfad",10);

   // printf("=========gW antes del momentum\n");
   // printDebug(gW->subTensor(k)->gptr,"adsfad",10);


    Tensor::sum((mu/batch),gW->subTensor(k),0,mmu,pgW->subTensor(k),0,pgW->subTensor(k),0);

 //   printf("=========gW despues del momentum\n");
 //   printDebug(gW->subTensor(k)->gptr,"adsfad",10);


    Tensor::inc(pgW->subTensor(k),W->subTensor(k));
/*
    printf("=========W despues\n");
    printDebug(W->subTensor(k)->gptr,"adsfad",10);
    getchar();
*/
    if (VERBOSE) fprintf(stderr,"W (%s) norm = %f\n",name,W->subTensor(k)->norm());


    // BIAS
/*
    printf("=========Bias antes\n");
    printDebug(b->subTensor(k)->gptr,"adsfad",10);
    printf("=========gb antes del momentum\n");
    printDebug(gb->subTensor(k)->gptr,"adsfad",10);
    printf("=========pgb antes del momentum\n");
    printDebug(pgb->subTensor(k)->gptr,"adsfad",10);
*/
    Tensor::sum((mu/batch),gb->subTensor(k),0,mmu,pgb->subTensor(k),0,pgb->subTensor(k),0);
/*
    printf("=========pgb despuest del momentum\n");
    printDebug(pgb->subTensor(k)->gptr,"adsfad",10);
*/
    Tensor::inc(pgb->subTensor(k),b->subTensor(k));
/*
    printf("=========b despuest del incremento de gradiente\n");
    printDebug(b->subTensor(k)->gptr,"adsfad",10);
*/



    // REGULARIZATION    
    if (l2!=0.0)
      Tensor::sc_mult(W->subTensor(k),(1-l2),W->subTensor(k),0);
    //W[k]-=l2*W[k];

    /*
    if (maxn>0.0)
      for(i=0;i<W[k].cols();i++) {
	if (W[k].col(i)->norm()>maxn) {
	  W[k].col(i)=(maxn/W[k].col(i)->norm())*W[k].col(i);
	}
      }

    if (l1!=0.0) {
      for(i=0;i<W[k].rows();i++)
	for(j=0;j<W[k].cols();j++)
	  if (W[k](i,j)<0.0) W[k](i,j)+=l1;
	  else W[k](i,j)-=l1;
    }
    */

    gW->subTensor(k)->set(0.0);
    gb->subTensor(k)->set(0.0);
    //gW[k].setZero();
    //gb[k].setZero();
  /*
    printf("==========APPLY GRAD\n");
    printf("====== ACTIVATION\n");
    printf("%d \n",act); 
    printf("======E\n");
    printDebug(E->gptr,"E",20);
    printf("======N\n");
    printDebug(N->gptr,"N",20);
    printf("======W\n");
    if(act!=ACT_SOF)
    {
    printDebug(W->subTensor(0)->gptr,"N",10);
    printf("======B\n");
    printDebug(b->subTensor(0)->gptr,"N",10);}
    getchar();
*/
  }

  // BATCH NORM g,b
  if (bn) {
    Tensor::sc_mult(gbn_g,(mu/batch),bn_g,1);
    
    /*
      for(i=0;i<din;i++) {
      bn_g(i)+=(mu/batch)*gbn_g(i);
      bn_b(i)+=(mu/batch)*gbn_b(i);
    }
    */
  }

}



////////////////////////////////////////////////////////////////
/// INPUT FULLY CONNECTED LAYER
////////////////////////////////////////////////////////////////
IFLayer::IFLayer(Data *D,FLayer *L,int b,char *name):FLayer(b,name)
{
  int i,j;

  if (D!=NULL) {
    din=D->dim;
    this->D=D;
  }
  else {
    din=L->din;
    this->L=L;
  }
  

  mem();
  act=0;

  fprintf(stderr,"Creating Input FC layer (%s) with %d neurons\n",name,din);

}

void IFLayer::setsource(Data *Dt)  
{
  // Check if generative data is used
  if (Dt->gen) {
    if (Dt->dim==0) {
      Dt->dim=Dt->out;
      Dt->out=0;
    }
  }

  if (din!=Dt->dim) {
    fprintf(stderr,"setsource data error, different dimensions %d %d in %s\n",din,Dt->dim,name);
    exit(1);
  }

  D=Dt;
  L=NULL;
  
}

void IFLayer::setsource(FLayer *Lt)  
{
  if (din!=Lt->din) {
    fprintf(stderr,"setsource layer error, different dimensions %d %d in %s\n",din,Lt->din,name);
    exit(1);
  }

  D=NULL;
  L=Lt;
}
 
void IFLayer::next()
{
  if (D!=NULL) {
    if (D->gen) {
      GData *gd=(GData *)D;
      gd->next();
    }
    else D->next();
  }
}

void IFLayer::getbatch()
{
  int i,j;
  double fv;

  if ((D==NULL)&&(L==NULL)) {
    fprintf(stderr,"Input layer %s has not source\n",name);
    exit(1);
  }

  if (D!=NULL) 
    E->copyfromData(D);
  else 
    E->copy(((FLayer*)L)->N);
  

  //Noise for binary input
  if (trmode) {
    if (noiseb>0.0)
      for(int i=0;i<batch;i++)
	for(int j=0;j<din;j++)
	  if (uniform()<noiseb)
	    if (E->get(i,j)) E->set(i,j,0.0);
	    else E->set(i,j,1.0);
  }
}

void IFLayer::addparent(Layer *l) {
  fprintf(stderr,"Error: Input FC Layer (%s) can not have parent layer\n",name);
  exit(1);
  
}
 

//void IFLayer::forward();


void IFLayer::backward() {
  int b,i;

  if (L!=NULL) {
    // pass Delta to parent (FC) Layer
    if (VERBOSE) fprintf(stderr,"%s Delta norm %f\n",name,Delta->norm());
    
    ((FLayer *)L)->Delta->copy(Delta);
  }

}

//void IFLayer::initialize();
//void IFLayer::applygrads();
//void IFLayer::reset();



////////////////////////////////////////////////////////////////
/// OUTPUT FULLY CONNECTED LAYER
////////////////////////////////////////////////////////////////
OFLayer::OFLayer(Data *Dt,FLayer *Lt,int b,int o,char *name):FLayer(b,name)
{
  // opt 0: classification
  // opt 1: regression
  // opt 2: autoencoder
  // opt 3: max
  // opt 4: min
  // opt 5: max log
  // opt 6: min log
  // ...

  D=Dt;
  L=Lt;
  opt=o;

  if (L!=NULL) {
    din=Lt->din;
    L=Lt;
  }
  else if (opt==2) { //autoencoder
    if (Dt->gen) {
      if (Dt->dim==0) {
	Dt->dim=Dt->out;
	Dt->out=0;
      }
    }
    din=Dt->dim;
    D=Dt;
  }
  else { //normal
    if (Dt->gen) {
      if (Dt->out==0) {
	Dt->out=Dt->dim;
	Dt->dim=0;
      }
    }
    din=Dt->out;
    D=Dt;
  }
  out=1;

  mem();

  T=new Tensor(batch,din);

  // act
  if (opt==0) act=10; //softmax
  else act=0; //linear;

  if (D==NULL)
    fprintf(stderr,"Creating Output FC layer %s with %d neurons opt %d target %s\n",name,din,opt,L->name);
  else    
    fprintf(stderr,"Creating Output FC layer %s with %d neurons opt %d data %s\n",name,din,opt,D->name);
}

void OFLayer::settarget(Data *Dt)
{
  // Check if generative data is used
  if (Dt->gen) {
    if (Dt->out==0) {
      Dt->out=Dt->dim;
      Dt->dim=0;
    }
  }

  int dsize;

  if (opt==2) dsize=Dt->dim; //autoencoder
  else dsize=Dt->out;

  if (din!=dsize) {
    fprintf(stderr,"settarget error, different dimensions %d %d in %s\n",din,dsize,name);
    exit(1);
  }
  
  D=Dt;
  L=NULL;
}
void OFLayer::settarget(FLayer *Lt)
{

  if (din!=Lt->din) {
    fprintf(stderr,"settarget error, different dimensions %d %d in %s\n",din,Lt->din,name);
    exit(1);
  }
  
  L=Lt;
  D=NULL;
}

double OFLayer::get_err(int n)
{
  int i,j,k,p;
  int rindex;
  int nindex;
  double err;

  // opt 0: classification
  // opt 1: regression
  // opt 2: autoencoder
  // opt 3: max
  // opt 4: min
  // opt 5: max log
  // opt 6: min log
  // ...

  if ((D==NULL)&&(L==NULL)) {
    fprintf(stderr,"Output layer %s has not targets\n",name);
    exit(1);
  }

  if (L!=NULL) 
    T->copy(((FLayer *)L)->N);
  else {
    if (opt<2) 
      for(i=0;i<n;i++) 
        for(j=0;j<din;j++) 
          T->set(i,j,D->M(D->getpos(i),j+D->dim));
    else if (opt==2) // autoencoder
      for(i=0;i<n;i++)
	for(j=0;j<din;j++) 
	  T->set(i,j,D->M(D->getpos(i),j));
	
  }
  //////////////////////
  if (opt==0) {
//    printf("==========VALORES EN GET ERROR\n");
/*
    printf("====== ACTIVATION\n");
    printf("%d \n",act); 
    printf("======E\n");
    printDebug(E->gptr,"E",20);
    printf("======N\n");
    printDebug(N->gptr,"N",20);
    if(act!=ACT_SOF)
    {
    printDebug(W->subTensor(0)->gptr,"N",20);
    printf("======B\n");
    printDebug(b->subTensor(0)->gptr,"N",20);}

printf("========N %d\n",n);
getchar();
    printf("======T total con todo\n");
    printDebug(T->gptr,"T total con todo",20);
    printf("======N Total con todo\n");
    printDebug(N->gptr,"N total con todo",20);
*/
    for(i=0;i<n;i++) {
  /*  
    printf("======T\n");
    printDebug(T->gptr+i*T->gsp.col,"T",10);
*/
    T->row_max(i,&rindex);
/*
    printf("======N\n");
    printDebug(N->gptr+i*T->gsp.col,"N",10);
*/
    N->row_max(i,&nindex);
/*
    printf("======Tindex %d  ",rindex);
    printf("=====Nindex %d\n",nindex);
    getchar();
*/
      if (rindex!=nindex) cerr++;
      for(j=0;j<din;j++) {
	if (j==rindex) {if (N->get(i,j)!=0.0) ent-=log(N->get(i,j));}
	else if (N->get(i,j)!=1.0) ent-=log(1-N->get(i,j));
      }
    }

    //getchar();
  }
  else if (opt<3) {
    for(i=0;i<n;i++)
      for(j=0;j<din;j++) {
        float Tn,Nn;
        if (D!=NULL) {
          if (opt==1) {
            Tn=(T->get(i,j)*D->fsd[j+D->dim])+D->fmu[j+D->dim];
            Nn=(N->get(i,j)*D->fsd[j+D->dim])+D->fmu[j+D->dim];
          }
          else {//opt=2
            Tn=(T->get(i,j)*D->fsd[j])+D->fmu[j];
            Nn=(N->get(i,j)*D->fsd[j])+D->fmu[j];
          }
        }
        else {
          Tn=T->get(i,j);
          Nn=N->get(i,j);
        }
        mse+=(Tn-Nn)*(Tn-Nn)/din;
        mae+=fabs(Tn-Nn)/din;
      }
  }
  else if (opt<5) {
    // max min                                                                            
    for(i=0;i<n;i++)
      for(j=0;j<din;j++) loss+=N->get(i,j)/din;

  }
  else {
    //maxlog minlog                                                                       
    for(i=0;i<n;i++)
      for(j=0;j<din;j++) loss+=log(N->get(i,j))/din;
  }
  return 0.0;
  
}

void OFLayer::backward()
{

//  printf("===========================\n");
//  printf("===========================\n");
//  printf("=========INIT BACKWARD\n");

  int i,j,k,p;
  double sum;
  
  
  if (L!=NULL) {
    T->copy(((FLayer *)L)->N);
  }
  else {
    if (opt==2)
      for(i=0;i<batch;i++)
	for(j=0;j<din;j++)
	  T->set(i,j,D->M(D->getpos(i),j));
    else
      for(i=0;i<batch;i++)
	for(j=0;j<din;j++)
	  T->set(i,j,D->M(D->getpos(i),j+D->dim));
  }

  if (opt==0) {// Softmax, CrossEnt
    if (lout>0) {
      for(i=0;i<batch;i++)
	for(j=0;j<din;j++) {
	  LType val=N->get(i,j);
	  Delta->set(i,j,Delta->get(i,j)*(val-(val*val))); //deriv softmax w.r.t pre-activation: y_i-(y_i)^2
	}
    }
/*
    printf("======= DELTA EN SOFTMAX\n");
    printDebug(Delta->gptr,"aa",10);
    printf("======= T EN SOFTMAX\n");
    printDebug(T->gptr,"aa",10);
    printf("======= N EN SOFTMAX\n");
    printDebug(N->gptr,"aa",10);
    printf("Lambda vale %f",lambda);
*/
 //   printf("===========DELTA oflayer backward\n");
    Tensor::sum(lambda,T,0,-lambda,N,0,Delta,1);
 /*   printf("==delta \n");
    printDebug(Delta->gptr,"",10);
    printf("==T \n");
    printDebug(T->gptr,"",10);
    printf("==N \n");
    printDebug(N->gptr,"",10);
 getchar();*/
/*
    printf("======= DELTA APLICADO EN SOFTMAX\n");
    printDebug(Delta->gptr,"aa",10);
    getchar();*/

    //Delta+=(T-N)*lambda;
  }
  else if (opt<3) {
    Tensor::sum(2*lambda,T,0,-2*lambda,N,0,Delta,1);
    //Delta+=2*(T-N)*lambda;
  }
  else if (opt<5) {
    // max min
    for(i=0;i<batch;i++)
      for(j=0;j<din;j++)
	if (opt==3) Delta->set(i,j,-1.0);
	else Delta->set(i,j,1.0);
  }
  else {
    // maxlog minlog
    if (opt==5)  
      for(i=0;i<batch;i++)
	for(j=0;j<din;j++)
	  if (opt==5) Delta->set(i,j,-1/N->get(i,j));
	  else  Delta->set(i,j,1/N->get(i,j));
  }

  if (VERBOSE) fprintf(stderr,"OFLayer %s Delta norm %f\n",name,Delta->norm());
/*
    printf("==========VALORES EN BACKWARD\n");
    printf("====== ACTIVATION\n");
    printf("%d \n",act); 
    printf("======E\n");
    printDebug(E->gptr,"E",20);
    printf("======N\n");
    printDebug(N->gptr,"N",20);
    printf("======W\n");
    if(act!=ACT_SOF)
    {
    printDebug(W->subTensor(0)->gptr,"N",20);
    printf("======B\n");
    printDebug(b->subTensor(0)->gptr,"N",20);}
    getchar();
*/
  FLayer::backward();

}

//  virtual void addparent(Layer *l);
//  virtual void forward();
//  virtual void backward();
//  virtual void initialize();
//  virtual void applygrads();
//  virtual void reset();
