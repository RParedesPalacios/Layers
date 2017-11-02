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

#define PRINT 0
/// Eigen
using namespace Eigen;
using namespace std;


/////////
//Helper funciton
#ifdef fGPU
#include "./gpu/execution.h"
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
  bn_b->set(0.0);

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
      double s=sqrt(2.0/l->din);
      //W->subTensor(lout)->set_rand_gauss(0,s);
      for (int i=0;i< W->subTensor(lout)->a;i++)
        for (int j=0;j< W->subTensor(lout)->b;j++)
            W->subTensor(lout)->set(i,j,gauss(0,s));//set_rand_gauss(0,s);
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

  /*
  int i,j;
  float eps=0.0001;
  
  if (trmode) {
    Tensor::reduceTomean(E,bn_mean,1);  
    Tensor::reduceTovariance(E,bn_var,1);

    Tensor::inc(bn_mean,bn_gmean);
    Tensor::inc(bn_var,bn_gvar);
    bnc++;
    
    bn_var->add(eps); 
    bn_var->sqr();  
    
    Tensor::reduced_sum(1,E,-1,bn_mean,bn_E,0,1);
    Tensor::reduced_div(bn_E,bn_var,bn_E,0,1);

    if ((trmode)&&(noiser>0.0)) {
      bn_E->add_noise_gauss(noiser,0.0,noisesd);
    }

    Tensor::reduced_mult(bn_E,bn_g,BNE,0,1);
    Tensor::reduced_sum(1,BNE,1,bn_b,BNE,0,1);
  }
  else { // testmode
    Tensor::reduced_sum(1,E,-1.0/bnc,bn_gmean,bn_E,0,1);
    bn_var->copy(bn_gvar);
    bn_var->div(bnc);
    bn_var->add(eps); 
    bn_var->sqr();  

    Tensor::reduced_div(bn_E,bn_var,bn_E,0,1);
    
    Tensor::reduced_mult(bn_E,bn_g,BNE,0,1);
    Tensor::reduced_sum(1,BNE,1,bn_b,BNE,0,1);
  }
*/
}
extern bool useCPU;
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
      if (VERBOSE) fprintf(stderr,"from OP(%s) = %f\n",l->name,N->sum());

    }
    else {
      cin=(CLayer *)Lin[0];
      N->copy(cin->N);
    
      if (VERBOSE) fprintf(stderr,"from CNN (%s) = %f\n",cin->name,N->sum());

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
  
    if (VERBOSE) fprintf(stderr,"E(%s) = %f\n",name,E->sum());
  
    ////////////////////////////
    // ACTIVATION
    ////////////////////////////
  
    if (bn) 
      Tensor::activation(BNE,N,act);
    else 
      Tensor::activation(E,N,act);

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
  
    if (VERBOSE) fprintf(stderr,"N(%s,%d) = %f\n",name,act,N->sum());
  }

//////////////PRINT OUTPU FROM SOFTMAX
        if (PRINT)
        {
        if (act==ACT_SOF)
        {
        if(useCPU)
        {
           FILE *f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_cpu_N.txt","w");
           if (f==NULL)
		exit(-1);

	for (int j=0;j<N->a;j++)
        {
          for (int q=0;q<N->b;q++)
              fprintf(f," %f ",N->ptr2(j,q));
         fprintf(f,"\n");
        }
        fclose(f);

        f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_cpu_T.txt","w");
        if (f==NULL)
		exit(-1);

	for (int j=0;j<T->a;j++)
        {
          for (int q=0;q<T->b;q++)
              fprintf(f," %f ",T->ptr2(j,q));
         fprintf(f,"\n");
        }
        fclose(f);
        }
        else
        {
          
           FILE *f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_gpu_N.txt","w");
           if (f==NULL)
		exit(-1);

	for (int j=0;j<N->a;j++)
        {
          for (int q=0;q<N->b;q++)
              fprintf(f," %f ",N->get(j,q));
         fprintf(f,"\n");
        }
        fclose(f);

        f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_gpu_T.txt","w");
        if (f==NULL)
		exit(-1);

	for (int j=0;j<T->a;j++)
        {
          for (int q=0;q<T->b;q++)
              fprintf(f," %f ",T->get(j,q));
         fprintf(f,"\n");
        }
        fclose(f);


        }
        printf("Get char en forward\n");
        getchar();
        }
        }
 /////////////////////////////////////

  //////////////////////////////
  // FORWARD TO CHILD LAYERS
  //////////////////////////////
  for(i=0;i<lout;i++) {
    if (rnet->isIn(Lout[i])) {
      if (Lout[i]->type==FLAYER) {
	if (VERBOSE) fprintf(stderr,"Forward %s-->%s\n",name,Lout[i]->name);
	l=(FLayer *)Lout[i];
	
	if (VERBOSE) fprintf(stderr,"Forward %s W norm %f\n",name,W->subTensor(i)->sum());

	Tensor::mult(N,0,W->subTensor(i),0,l->E,1);
	
	//bias
	if (!bn) l->E->inc_2Drowwise(b->subTensor(i));
 /*printf("EL BIAS\n");
  if (useCPU)
  {
   printf("Entra\n");
   for (int j=0;j<(b->subTensor(i)->a);j++)
	printf(" %f ",b->subTensor(i)->ptr1(j));
   printf("\n");
  }
  else
   printDebug(b->subTensor(0)->gptr,"" ,b->subTensor(i)->gsp.row,b->subTensor(i)->gsp.col);
 
  printf("FIN\n"); 
  getchar();
  printf("EL PESO\n");
  if (useCPU)
  {
   printf("Entra\n");
   for (int j=0;j<1;j++)
        for (int q=0;q<(W->subTensor(i)->b);q++)
	printf(" %f ",W->subTensor(i)->ptr2(j,q));
   printf("\n");
  }
  else
   printDebug(W->subTensor(i)->gptr,"" ,1,W->subTensor(i)->gsp.col);
   getchar();
*/

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
  /*
 
  Tensor *A=new Tensor(Delta->a,Delta->b);
  Tensor *Tvar32=new Tensor(bn_var->a);
  Tensor *Tsqvar=new Tensor(bn_var->a);
  float eps=0.0001;
  
  //1 Gamma
  Tensor::el_mult(Delta,0,bn_E,0,A,0);
  Tensor::reduceTosum(A,gbn_g,1);

  //2 Beta  
  Tensor::reduceTosum(Delta,gbn_b,1);
  
  //3 bnE
  Tensor::reduced_mult(Delta,bn_g,gbn_E,0,1);
  
  //4 Var 
  Tsqvar->copy(bn_var);
  Tsqvar->add(eps);
  Tsqvar->sqr();
  Tvar32->copy(bn_var);
  Tvar32->add(eps);

  Tensor::el_mult(Tvar32,0,Tsqvar,0,Tvar32,0);
  Tensor::reduced_sum(-0.5,E,0.5,bn_mean,A,0,1);
  Tensor::reduced_div(A,Tvar32,A,0,1);
  Tensor::el_mult(A,0,gbn_E,0,A,0);
  Tensor::reduceTosum(A,gbn_var,1);

  //5 Mean
  Tensor::reduced_div(gbn_E,Tsqvar,A,0,1);
  A->mul(-1);
  Tensor::reduceTosum(A,gbn_mean,1);

  //6 Delta
  Tensor::reduced_div(gbn_E,Tsqvar,Delta,0,1);
  Tensor::reduced_sum(2.0/batch,E,-2.0/batch,bn_mean,A,0,1);
  Tensor::reduced_mult(A,gbn_var,A,0,1);
  Tensor::reduced_sum(1,A,1.0/batch,gbn_mean,Delta,1,1);

    
  delete A;
  delete Tvar32;
  delete Tsqvar;
  */
}


void FLayer::backward()
{
  int i,j,k,ind;

  if (drop>0.0) Tensor::maskZeros(dvec,Delta);

  
  if (reshape) {
    if (VERBOSE) {
      fprintf(stderr,"%s Delta norm %f\n",name,Delta->sum());
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

    if (VERBOSE) fprintf(stderr,"%s Delta norm %f\n",name,Delta->sum());

    if (act!=ACT_SOF) { // To prevent for output layers with softmax
      if (bn) 
	Tensor::dactivation(BNE,N,dE,act);
      else 
	Tensor::dactivation(E,N,dE,act);
        if(PRINT)
        {
        if(useCPU)
        {
           FILE *f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_cpu_Delta_preact.txt","w");
           if (f==NULL)
		exit(-1);

	for (int j=0;j<Delta->a;j++)
        {
          for (int q=0;q<Delta->b;q++)
              fprintf(f," %f ",Delta->ptr2(j,q));
         fprintf(f,"\n");
        }
        fclose(f);
        }
        else
        {
           FILE *f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_gpu_Delta_preact.txt","w");
           if (f==NULL)
		exit(-1);

	for (int j=0;j<Delta->a;j++)
        {
         printf("%d\n",j);
          for (int q=0;q<Delta->b;q++)
              fprintf(f," %f ",Delta->get(j,q));
         fprintf(f,"\n");
        }
        fclose(f);

        }
        if(useCPU)
        {
           FILE *f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_cpu_dE.txt","w");
           if (f==NULL)
		exit(-1);

	for (int j=0;j<dE->a;j++)
        {
          for (int q=0;q<dE->b;q++)
              fprintf(f," %f ",dE->ptr2(j,q));
         fprintf(f,"\n");
        }
        fclose(f);
        }
        else
        {
           FILE *f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_gpu_dE.txt","w");
           if (f==NULL)
		exit(-1);

	for (int j=0;j<dE->a;j++)
        {
         printf("%d\n",j);
          for (int q=0;q<dE->b;q++)
              fprintf(f," %f ",dE->get(j,q));
         fprintf(f,"\n");
        }
        fclose(f);

        }
        }
    Tensor::el_mult(Delta,0,dE,0,Delta,0);
        if (PRINT)
        {
        if(useCPU)
        {
           FILE *f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_cpu_Delta.txt","w");
           if (f==NULL)
		exit(-1);

	for (int j=0;j<Delta->a;j++)
        {
          for (int q=0;q<Delta->b;q++)
              fprintf(f," %f ",Delta->ptr2(j,q));
         fprintf(f,"\n");
        }
        fclose(f);
        }
        else
        {
           FILE *f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_gpu_Delta.txt","w");
           if (f==NULL)
		exit(-1);

	for (int j=0;j<Delta->a;j++)
        {
         printf("%d\n",j);
          for (int q=0;q<Delta->b;q++)
              fprintf(f," %f ",Delta->get(j,q));
         fprintf(f,"\n");
        }
        fclose(f);

        }
        }

    }

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
	  if (VERBOSE) fprintf(stderr,"%f %f -->\n",l->N->sum(),Delta->sum());
//////////////////PRINTING
        if (PRINT)
        {
        if(useCPU)
        {
           FILE *f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_cpu_gW.txt","w");
           if (f==NULL)
		exit(-1);

	for (int j=0;j<l->gW->subTensor(ind)->a;j++)
        {
          for (int q=0;q<l->gW->subTensor(ind)->b;q++)
              fprintf(f," %f ",l->gW->subTensor(ind)->ptr2(j,q));
         fprintf(f,"\n");
        }
        fclose(f);
        }
        else
        {
           FILE *f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_gpu_gW.txt","w");
           if (f==NULL)
		exit(-1);

	for (int j=0;j<l->gW->subTensor(ind)->a;j++)
        {
          for (int q=0;q<l->gW->subTensor(ind)->b;q++)
              fprintf(f," %f ",l->gW->subTensor(ind)->get(j,q));
         fprintf(f,"\n");
        }
        fclose(f);

        }
        

//////////////////////

///////////////////////////

        if(useCPU)
        {
           FILE *f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_cpu_N_backward.txt","w");
           if (f==NULL)
		exit(-1);

	for (int j=0;j<l->N->a;j++)
        {
          for (int q=0;q<l->N->b;q++)
              fprintf(f," %f ",l->N->ptr2(j,q));
         fprintf(f,"\n");
        }
        fclose(f);
        }
        else
        {
        FILE *f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_gpu_N_backward.txt","w");
        if (f==NULL)
		exit(-1);

	for (int j=0;j<l->N->a;j++)
        {
          for (int q=0;q<l->N->b;q++)
              fprintf(f," %f ",l->N->get(j,q));
         fprintf(f,"\n");
        }
        fclose(f);
        }
        }
///////////////////////////


	  Tensor::mult(l->N,1,Delta,0,l->gW->subTensor(ind),0);

//////////////////////
        if (PRINT)
        {
        if(useCPU)
        {
           FILE *f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_cpu_gw.txt","w");
           if (f==NULL)
		exit(-1);

	for (int j=0;j<l->gW->subTensor(ind)->a;j++)
        {
          for (int q=0;q<l->gW->subTensor(ind)->b;q++)
              fprintf(f," %f ",l->gW->subTensor(ind)->ptr2(j,q));
         fprintf(f,"\n");
        }
        fclose(f);
        }
        else
        {
           FILE *f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_gpu_gw.txt","w");
           if (f==NULL)
		exit(-1);

	for (int j=0;j<l->gW->subTensor(ind)->a;j++)
        {
          for (int q=0;q<l->gW->subTensor(ind)->b;q++)
              fprintf(f," %f ",l->gW->subTensor(ind)->get(j,q));
         fprintf(f,"\n");
        }
        fclose(f);

        }
        }

///////////////////
	  if (!l->bn) Tensor::sumcol(l->gb->subTensor(ind),Delta);

/////////////////////////
        if (PRINT)
        {
        if(useCPU)
        {
           FILE *f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_cpu_gb.txt","w");
           if (f==NULL)
		exit(-1);

	for (int q=0;q<l->gb->subTensor(ind)->a;q++)
              fprintf(f," %f ",l->gb->subTensor(ind)->ptr1(q));

         fprintf(f,"\n");
        fclose(f);
        }
        else
        {
           FILE *f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_gpu_gb.txt","w");

           if (f==NULL)
		exit(-1);

	for (int q=0;q<l->gb->subTensor(ind)->a;q++)
              fprintf(f," %f ",l->gb->subTensor(ind)->get(q));

         fprintf(f,"\n");
        fclose(f);

        }
        }


////////////////////////////



	  // back-propagate Delta
	  Tensor::mult(Delta,0,l->W->subTensor(ind),1,l->Delta,1);
 //////////////////////
        if (PRINT)
        {
        if(useCPU)
        {
           FILE *f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_cpu_delta_prop.txt","w");
           if (f==NULL)
		exit(-1);

	for (int j=0;j<l->Delta->a;j++)
        {
          for (int q=0;q<l->Delta->b;q++)
              fprintf(f," %f ",l->Delta->ptr2(j,q));
         fprintf(f,"\n");
        }
        fclose(f);
        }
        else
        {
           FILE *f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_gpu_delta_prop.txt","w");
           if (f==NULL)
		exit(-1);

	for (int j=0;j<l->Delta->a;j++)
        {
         printf("%d\n",j);
          for (int q=0;q<l->Delta->b;q++)
              fprintf(f," %f ",l->Delta->get(j,q));
         fprintf(f,"\n");
        }
        fclose(f);

        }
        }
///////////////////
  
	}
      }
    }
  }
//printf("get char en backward\n");
//getchar();
}



void FLayer::applygrads()
{
  int k,i,j;


  for(k=0;k<lout;k++) {
/*
   printf("EL MOMENTUM DEL PESO\n");
  if (useCPU)
  {
   printf("Entra\n");
   for (int j=0;j<1;j++)
      for (int q=0;q<(pgW->subTensor(k)->b);q++)
	printf(" %f ",pgW->subTensor(k)->ptr2(j,q));
   printf("\n");
  }
  else
   printDebug(pgW->subTensor(k)->gptr,"" ,1,pgW->subTensor(k)->gsp.col);
 
  printf("FIN\n"); 
  getchar();

   printf("EL GRADIENTE DEL PESO\n");
  if (useCPU)
  {
   printf("Entra\n");
   for (int j=0;j<1;j++)
      for (int q=0;q<(gW->subTensor(k)->b);q++)
	printf(" %f ",gW->subTensor(k)->ptr2(j,q));
   printf("\n");
  }
  else
   printDebug(gW->subTensor(k)->gptr,"" ,1,gW->subTensor(k)->gsp.col);
 
  printf("FIN\n"); 
  getchar();
*/

    Tensor::sum((mu/batch),gW->subTensor(k),0,mmu,pgW->subTensor(k),0,pgW->subTensor(k),0);
    Tensor::inc(pgW->subTensor(k),W->subTensor(k));

    if (VERBOSE) fprintf(stderr,"W (%s) norm = %f\n",name,W->subTensor(k)->sum());
/*
   printf("EL MOMENTUM DEL PESO\n");
  if (useCPU)
  {
   printf("Entra\n");
   for (int j=0;j<1;j++)
      for (int q=0;q<(pgW->subTensor(k)->b);q++)
	printf(" %f ",pgW->subTensor(k)->ptr2(j,q));
   printf("\n");
  }
  else
   printDebug(pgW->subTensor(k)->gptr,"" ,1,pgW->subTensor(k)->gsp.col);
 
  printf("FIN\n"); 
  getchar();
*/


    // BIAS
    Tensor::sum((mu/batch),gb->subTensor(k),0,mmu,pgb->subTensor(k),0,pgb->subTensor(k),0);
    Tensor::inc(pgb->subTensor(k),b->subTensor(k));
/*
   printf("EL MOMENTUM DEL PESO\n");
  if (useCPU)
  {
   printf("Entra\n");
   for (int j=0;j<1;j++)
      for (int q=0;q<(pgW->subTensor(k)->b);q++)
	printf(" %f ",pgW->subTensor(k)->ptr2(j,q));
   printf("\n");
  }
  else
   printDebug(pgW->subTensor(k)->gptr,"" ,1,pgW->subTensor(k)->gsp.col);
 
  printf("FIN\n"); 
  getchar();
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
  }

  // BATCH NORM g,b
  if (bn) {
    Tensor::sc_mult(gbn_g,(mu/batch),bn_g,1);
    Tensor::sc_mult(gbn_b,(mu/batch),bn_b,1);
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
    if (VERBOSE) fprintf(stderr,"%s Delta norm %f\n",name,Delta->sum());
    
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

  // opt 0: classification
  // opt 1: regression
  // opt 2: autoencoder
  // opt 3: max
  // opt 4: min
  // opt 5: max log
  // opt 6: min log

  if ((D==NULL)&&(L==NULL)) {
    fprintf(stderr,"Output layer %s has not targets\n",name);
    exit(1);
  }

  if (L!=NULL) 
    T->copy(((FLayer *)L)->N);
  else {
    if (opt<2) // cross_entropy or sum_squared_errors
      T->copylabels(D);
    else if (opt==2) // autoencoder
      T->copyfromData(D);
  }


  if (opt==0) Tensor::loss_cross_entropy(T,N,cerr,ent);
  else if (opt==1) Tensor::loss_sse(T,N,D,0,mae,mse);
  else if (opt==2) Tensor::loss_sse(T,N,D,D->dim,mae,mse);

  
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

  int i,j,k,p;
  double sum;
  

  if (L!=NULL) {
    T->copy(((FLayer *)L)->N);
  }
  else {
    if (opt<2) // cross_entropy or sum_squared_errors                                                               
      T->copylabels(D);
    else if (opt==2) // autoencoder                                                                                 
      T->copyfromData(D);
  }

  if (opt==0) {// Softmax, CrossEnt
    if (lout>0) {
      for(i=0;i<batch;i++)
	for(j=0;j<din;j++) {
	  LType val=N->get(i,j);
	  Delta->set(i,j,Delta->get(i,j)*(val-(val*val))); 
	}
    }
    Tensor::sum(lambda,T,0,-lambda,N,0,Delta,1);
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

  if (VERBOSE) fprintf(stderr,"OFLayer %s Delta norm %f\n",name,Delta->sum());
FILE *f;
  if (PRINT)
  {
   if (useCPU)
 {
 
   f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_cpu_T.txt","w");
        if (f==NULL)
		exit(-1);

	for (int j=0;j<T->a;j++)
        {
          for (int q=0;q<T->b;q++)
              fprintf(f," %f ",T->ptr2(j,q));
         fprintf(f,"\n");
        }
        fclose(f);

   f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_cpu_Delta_output.txt","w");
        if (f==NULL)
		exit(-1);

	for (int j=0;j<T->a;j++)
        {
          for (int q=0;q<T->b;q++)
              fprintf(f," %f ",Delta->ptr2(j,q));
         fprintf(f,"\n");
        }
        fclose(f);

 }
 else
 {
   f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_gpu_T.txt","w");
        if (f==NULL)
		exit(-1);

	for (int j=0;j<T->a;j++)
        {
          for (int q=0;q<T->b;q++)
              fprintf(f," %f ",T->get(j,q));
         fprintf(f,"\n");
        }
        fclose(f);



   f = fopen("/home/jmaronasm/Layers_update_final/Layers/file_gpu_Delta_output.txt","w");
        if (f==NULL)
		exit(-1);

	for (int j=0;j<T->a;j++)
        {
          for (int q=0;q<T->b;q++)
              fprintf(f," %f ",Delta->get(j,q));
         fprintf(f,"\n");
        }
        fclose(f);

  }
  }
 //printf("Getchar backward oflayer\n");
 //getchar();
  FLayer::backward();

}

//  virtual void addparent(Layer *l);
//  virtual void forward();
//  virtual void backward();
//  virtual void initialize();
//  virtual void applygrads();
//  virtual void reset();
