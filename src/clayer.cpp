#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <iostream>

#include "layer.h"
#include "types.h"
#include "utils.h"
#include "tensor.h"

#ifdef MKL 
#define EIGEN_USE_MKL_ALL
#endif

#include "Eigen/Dense"


using namespace Eigen;
using namespace std;

extern double gn[LUT];
extern double un[LUT];

////////////////////////////////////
///// CONVOLUTIONAL LAYER CLASS
////////////////////////////////////

CLayer::CLayer()
{
  type=CLAYER;
}

CLayer::CLayer(int batch,char *name):Layer(batch,name)
{
  type=CLAYER;
  rpad=cpad=zpad=0;
  stride=1;
}


CLayer::CLayer(int nk,int kr, int kc,int batch,int rp,int cp,int stride,char *name):Layer(batch,name)
{

  type=CLAYER;
  this->nk=nk;
  outz=nk;
  this->kr=kr;
  this->kc=kc;
  this->batch=batch;
  this->stride=stride;
  act=1;
  type=CLAYER;

  rpad=rp;
  cpad=cp;

  if ((rpad)||(cpad)) zpad=1;

  if (stride<=0) {
    fprintf(stderr,"Error stride value %d\n",stride);
    exit(1);
  }

  fprintf(stderr,"Creating Conv layer (%s) with %d@%dx%d kernels pad=%dx%d stride=%d\n",name,nk,kr,kc,rpad,cpad,stride);
}

void CLayer::addchild(Layer *l)
{
  int enc=0;

  for(int i=0;i<lout;i++)
    if (Lout[i]==l) enc=1;

  if (!enc) {
    if (l->type==FLAYER) {
      Lout[lout++]=l;
      fprintf(stderr,"Connecting %s --> %s FC\n",name,l->name);
      l->addparent(this);
    }
    else if (l->type==CLAYER) {
      Lout[lout++]=l;
      fprintf(stderr,"Connecting %s --> %s Conv\n",name,l->name);
      l->addparent(this);
    }
    else if (l->type==PLAYER) {
      Lout[lout++]=l;
      fprintf(stderr,"Connecting %s --> %s MP\n",name,l->name);
      l->addparent(this);
    }
    else if (l->type==CATLAYER) {
      Lout[lout++]=l;
      fprintf(stderr,"Connecting %s --> %s Cat\n",name,l->name);
      l->addparent(this);
    }
    else if (l->type==ADDLAYER) {
      Lout[lout++]=l;
      fprintf(stderr,"Connecting %s --> %s Add\n",name,l->name);
      l->addparent(this);
    }
    else {
      fprintf(stderr,"Error: %s conv layer can not have child layer %s\n",name,l->name);
      exit(1);
    }
  }
}

void CLayer::shared(Layer *li)
{


}


void CLayer::addparent(Layer *l)
{
  int i,j;
  CLayer *c;
  PLayer *p;
  CatLayer *cat;


  if (lin>0) {
    if (Lin[0]!=l) {
      fprintf(stderr,"Error: %s conv layer can only have one parent layer\n",name);
      exit(1);
    }
    else {
      fprintf(stderr,"Layers just connected\n");
      return;
    }
  }
 
  if (l->type!=FLAYER) {
    Lin[lin++]=l;

    c=(CLayer *)l;

    kz=c->outz;
    outr=((c->outr-kr)/stride)+1;
    outc=((c->outc-kc)/stride)+1;

    if (rpad) outr=(c->outr/stride);
    if (cpad) outc=(c->outc/stride);
  
    fprintf(stderr,"Creating Convol (%d@%dx%d) output %d@%dx%d\n",nk,kr,kc,outz,outr,outc);

    din=outr*outc*outz;
    if ((outr<=0)||(outc<=0)||(outz<=0)||(nk<=0)||(kr<=0)||(kc<=0)) exit(1);

    //// DIMS are ok
    K=new Tensor(nk,kz,kr,kc);
    gK=new Tensor(nk,kz,kr,kc);
    pgK=new Tensor(nk,kz,kr,kc);

    E=new Tensor(batch,nk,outr,outc);
    N=new Tensor(batch,nk,outr,outc);
    Delta=new Tensor(batch,nk,outr,outc);
    
    Dvec=new Tensor(batch,nk,outr,outc);
    dE=new Tensor(batch,nk,outr,outc);

    bias=new Tensor(nk);
    gbias=new Tensor(nk);

    // FOR BN
    BNE=new Tensor(batch,nk,outr,outc);
    bn_E=new Tensor(batch,nk,outr,outc);
    gbn_E=new Tensor(batch,nk,outr,outc);

    bn_mean=new Tensor(nk);
    bn_var=new Tensor(nk);

    bn_gmean=new Tensor(nk);
    bn_gvar=new Tensor(nk);

    bn_g=new Tensor(nk);
    bn_b=new Tensor(nk);

    gbn_mean=new Tensor(nk);
    gbn_var=new Tensor(nk);
    gbn_g=new Tensor(nk);
    gbn_b=new Tensor(nk);
  }
  else {
    fprintf(stderr,"Error: %s can not be parent of convol layer %s\n",l->name,name);
    exit(1);
  }

  if ((outc<=0)||(outr<=0)) {
    fprintf(stderr,"Error output values %dx%d\n",outr,outc);
    exit(1);
  }

}

///////////////////
// FORWARD
///////////////////
void CLayer::fBN()
{
  int i;
  float eps=0.000001;

  if (trmode) {
    Tensor::reduceTomean(E,bn_mean,1);  
    Tensor::reduceTovariance(E,bn_var,1);

    Tensor::inc(bn_mean,bn_gmean);
    Tensor::inc(bn_var,bn_gvar);
    bnc++;

    Tensor *sd=bn_var->Clone();

    sd->add(eps); 
    sd->sqr();  

    Tensor::reduced_sum(1,E,-1,bn_mean,bn_E,0,1);
    Tensor::reduced_div(bn_E,sd,bn_E,0,1);


    if (noiser>0.0) {
      bn_E->add_noise_gauss(noiser,0.0,noisesd);
    }

    Tensor::reduced_mult(bn_E,bn_g,BNE,0,1);
    Tensor::reduced_sum(1,BNE,1,bn_b,BNE,0,1);

    delete sd;
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
}



void CLayer::forward()
{
  int i,j,k,b,r,c;
  double sum=0;
  
  if (lout>0) {
    CLayer *cin;
    cin=(CLayer *)Lin[0];

    // CONVOL
    Tensor::ConvolForward(cin->N,K,0,E,0,stride,zpad,threads);

    
    if (!bn)
      Tensor::reduced_sum(1,E,1,bias,E,0,1);

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


    ////////////////////////////
    // POST-ACTIVATION
    ////////////////////////////
    if (drop>0.0) {
      if (trmode) {
	Dvec->set_rand_binary(drop);
	Tensor::maskZeros(Dvec,N);
      }
      else 
	Tensor::sc_mult(N,1.0-drop,N,0);
    }

    if (VERBOSE) fprintf(stderr,"N(%s,%d) = %f\n",name,act,N->norm());
  }
  
}




///////////////////
// BACKWARD
///////////////////
void CLayer::bBN()
{
  
  Tensor *A=new Tensor(Delta->a,Delta->b,Delta->c,Delta->d);
  Tensor *Tvar32=bn_var->Clone();
  Tensor *Tsqvar=bn_var->Clone();
  float eps=0.0001;
  

  //1 Gamma
  Tensor::el_mult(Delta,0,bn_E,0,A,0);
  Tensor::reduceTosum(A,gbn_g,1);
  
  //2 Beta  
  Tensor::reduceTosum(Delta,gbn_b,1);
  
  //3 bnE
  Tensor::reduced_mult(Delta,bn_g,gbn_E,0,1);
  
  //4 Var 
  Tsqvar->add(eps);
  Tsqvar->sqr();
  
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
  int m=batch*outr*outc;
  Tensor::reduced_div(gbn_E,Tsqvar,Delta,0,1);
  Tensor::reduced_sum(2.0/m,E,-2.0/m,bn_mean,A,0,1);
  Tensor::reduced_mult(A,gbn_var,A,0,1);
  Tensor::reduced_sum(1,A,1.0/m,gbn_mean,Delta,1,1);

    
  delete A;
  delete Tvar32;
  delete Tsqvar;

}


void CLayer::backward()
{

  int i,j,b,r,c;
  double sum;
  CLayer *cin;


  cin=(CLayer *)Lin[0];

  if (VERBOSE) fprintf(stderr,"DeltaN(%s) %f\n",name,Delta->norm());

  if (drop)
    Tensor::maskZeros(Dvec,Delta);


  if (bn) 
    Tensor::dactivation(BNE,N,dE,act);
  else 
    Tensor::dactivation(E,N,dE,act);
  
  Tensor::el_mult(Delta,0,dE,0,Delta,0);
  

  if (bn) bBN();
  

  if (VERBOSE) fprintf(stderr,"DeltaN(%s) %f\n",name,Delta->norm());
  if (VERBOSE) fprintf(stderr,"KernelN %f\n",K->norm());

  
  ///// COMPUTE GRADIENT
  if (VERBOSE) fprintf(stderr,"--> cinN=%f Delta=%f gK=%f\n",cin->N->norm(),Delta->norm(),gK->norm());

  Tensor::ConvolGrad(cin->N,gK,0,Delta,1,stride,zpad,threads);

  if (!bn) 
    Tensor::reduceTosum(Delta,gbias,1);

  if (VERBOSE) fprintf(stderr,"grads (%s) %f\n",name,gK->norm());

  ///// PROPAGATE DELTA
  if (cin->lin>0) 
    Tensor::ConvolBackward(Delta,K,1,cin->Delta,0,stride,zpad,threads);
}



void CLayer::initialize()
{
  int i,j,r,c;
  double s=sqrt(2.0/(kr*kc*kz));

  if (!init) {
    bias->set(0.1);
    K->set_rand_gauss(0,s);
    bn_g->set(1);
    bn_b->set(0.0);
    init=1;
  }
}

void CLayer::applygrads()
{
  double sum=0.0;
  int i;
  
  // WEIGHTS
  Tensor::sum(mu/batch,gK,0,mmu,pgK,0,pgK,0);
  Tensor::inc(pgK,K);

  // REGULARIZATION    
  if (l2!=0.0)
    Tensor::RegL2(K,l2);
  if (l1!=0.0)
    Tensor::RegL1(K,l1);

  // BIAS
  if (!bn) Tensor::sc_mult(gbias,mu/batch,bias,1);
  else {
    Tensor::sc_mult(gbn_g,mu/batch,bn_g,1);
    Tensor::sc_mult(gbn_b,mu/batch,bn_b,1);
  }

  if (VERBOSE) fprintf(stderr,"grads (%s) %f\n",name,gK->norm());
}

void CLayer::resetmomentum()
{
  if (VERBOSE)  fprintf(stderr,"layer %s reset momentum\n",name);
  
  if (type==CLAYER)
    pgK->set(0.0);

}

void CLayer::reset()
{
  if (lin>0) {
    if (VERBOSE) fprintf(stderr,"%s RESET\n",name);
    Delta->set(0.0);
    gK->set(0.0);
    gbias->set(0.0);
  }
	  
}
void CLayer::resetstats()
{
  if (type==CLAYER) {
    bnc=0;
    bn_gmean->set(0.0);
    bn_gvar->set(0.0);
    fprintf(stderr,"%s reset stats\n",name);
  }

}

void CLayer::printkernels( FILE *fe)
{
  int i,j,r,c;


  for(i=0;i<nk;i++) {
    for(j=0;j<kz;j++) {
      for(r=0;r<kr;r++) {
	for(c=0;c<kc;c++)
	  fprintf(fe,"%f ",K->get(i,j,r,c));
      }
    }
    fprintf(fe,"\n");
  }
  fclose(fe);
}



void CLayer::save(FILE *fe)
{
  int i,j,r,c;

  save_param(fe);

  K->save(fe,1);
  if (!bn) bias->save(fe,1);
  else {
    bn_g->save(fe,1);
    bn_b->save(fe,1);
    bn_gmean->save(fe,1);
    bn_gvar->save(fe,1);
    fprintf(fe,"%d\n",bnc);
  }

}

void CLayer::load(FILE *fe)
{

  int i,j,r,c;
  LType fv;
  int fsd;

  fprintf(stderr,"Loading layer %s...",name);
  load_param(fe);

  K->load(fe);
  
  if (!bn) {
    bias->load(fe);
  }
  else {
    bn_g->load(fe);
    bn_b->load(fe);
    bn_gmean->load(fe);
    bn_gvar->load(fe);
    fsd=fscanf(fe,"%d\n",&bnc);
  }

  fprintf(stderr,"ok\n");

}


///////////////////////////////////////////
/// Input Convol Layer
///////////////////////////////////////////
ICLayer::ICLayer(Data *Dt,Layer *Lt,int batch,int z,int ir,int ic,int cr,int cc,char *name):CLayer(batch,name)
{
  int i,j;
  type=ICLAYER;

  this->batch=batch;
  D=Dt;
  L=Lt;

  act=1;
  shift=0;
  flip=0;
  brightness=0.0;
  contrast=0.0;

  ////////////////////////////////////////////
  if (D!=NULL) {
    if ((z*ir*ic)!=D->dim) {
      fprintf(stderr,"Error Conv Data for Reshape %d!=%d\n",z*ir*ic,D->dim);
      exit(1);
    }
  }
  else {
    if ((z*ir*ic)!=L->din) {
      fprintf(stderr,"Error Conv Layer for Reshape %d!=%d\n",z*ir*ic,D->dim);
      exit(1);
    }
  }

  imr=ir;
  imc=ic;

  outr=cr;
  outc=cc;
  nk=z;
  outz=z;

  din=outr*outc*outz;

  if ((imr<outr)||(imc<outc)){
    fprintf(stderr,"Error input lower than out (%dx%d)<(%dx%d)\n",imr,imc,outr,outc);
    exit(1);
  }


  fprintf(stderr,"Creating Convol input %d@%dx%d from %d@%dx%d batch %d\n",outz,outr,outc,outz,imr,imc,batch);



  N=new Tensor(batch,nk,outr,outc);
  Delta=new Tensor(batch,nk,outr,outc);
  Dvec=new Tensor(batch,nk,outr,outc);

  fprintf(stderr,"Creating Convol output %d@%dx%d\n",outz,outr,outc);
}

void ICLayer::setsource(Data *newd)
{
  D=newd;
  L=NULL;
}
void ICLayer::setsource(FLayer *newl)
{
  L=newl;
  D=NULL;
}


// RANDOM FLIP
void ICLayer::doflip(LMatrix& I)
{
  int i,j,r,c;
  LMatrix T=I;

  r=I.rows();
  c=I.cols();

  for(i=0;i<r;i++)
    for(j=0;j<c;j++)
      I(i,j)=T(i,(c-1)-j);
}


// RANDOM SHIFT
void ICLayer::doshift(LMatrix& I,int sx,int sy)
{
  int i,j,r,c;
  LMatrix T=I;

  r=I.rows();
  c=I.cols();

  I.setZero();

  for(i=0;i<r;i++)
    if ((i+sy>=0)&&(i+sy<r))
      for(j=0;j<c;j++)
	if ((j+sx>=0)&&(j+sx<c))
	  I(i+sy,j+sx)=T(i,j);

}


// RANDOM NOISE
void ICLayer::donoise(LMatrix& I,double ratio, double sd)
{
  int i,j,r,c;

  r=I.rows();
  c=I.cols();

  for(i=0;i<r;i++)
    for(j=0;j<c;j++)
      if (uniform()<ratio)
	I(i,j)+=gauss(0.0,sd);

}

void ICLayer::donoiseb(LMatrix& I,double ratio)
{
  int i,j,r,c;

  r=I.rows();
  c=I.cols();

  for(i=0;i<r;i++)
    for(j=0;j<c;j++)
      if (uniform()<ratio)
	if (I(i,j)) I(i,j)=0.0;
	else I(i,j)=1.0;

}

// RANDOM BRIGHTNESS
double ICLayer::calc_brightness(LMatrix I,double factor)
{
  int i,j,r,c;
  double br;

  r=I.rows();
  c=I.cols();

  br=0.0;
  for(i=0;i<r;i++)
    for(j=0;j<c;j++)
      br+=I(i,j);
  br/=(r*c);

  br*=suniform()*factor;

  return br;
}

void ICLayer::dobrightness(LMatrix& I,double b)
{
  int i,j,r,c;

  r=I.rows();
  c=I.cols();

  for(i=0;i<r;i++)
    for(j=0;j<c;j++)
      I(i,j)+=b;

}


// RANDOM CONTRAST
void ICLayer::docontrast(LMatrix& I,double factor)
{
  int i,j,r,c;
  int sc;
  double smin;
  double s,u;

  r=I.rows();
  c=I.cols();

  smin=1.0/factor;
  u=uniform();

  s=smin+(u*(factor-smin));

  for(i=0;i<r;i++)
    for(j=0;j<c;j++)
      I(i,j)+=I(i,j)*s;

}

void ICLayer::SaveImage(LMatrix R,LMatrix G,LMatrix B,char *name)
{
  FILE *fs;
  int r,c,i,j;

  fs=fopen(name,"wt");


  r=R.rows();
  c=R.cols();

  fprintf(fs,"P3\n%d %d\n255\n",c,r);

  for(i=0;i<r;i++) {
    for(j=0;j<c;j++) {
      int ir,ig,ib;
      ir=255*R(i,j);if (ir>255) {ir=255;}if (ir<0) {ir=0;}
      ig=255*G(i,j);if (ig>255) {ig=255;}if (ig<0) {ig=0;}
      ib=255*B(i,j);if (ib>255) {ib=255;}if (ib<0) {ib=0;}
      fprintf(fs,"%d %d %d ",ir,ig,ib);
    }
    fprintf(fs,"\n");
  }
  fclose(fs);
  fprintf(stderr,"Image saved\n");

  getchar();
}

void ICLayer::next()
{
  if (D!=NULL) {
    if (D->gen) {
      GData *gd=(GData *)D;
      gd->next();
    }
    else D->next();
  }
}


void ICLayer::getbatch()
{
  int b,i,j,k,p,pk;
  int sx,sy;
  int cr,cc; //crop

  
  if ((D==NULL)&&(L==NULL)) {
    fprintf(stderr,"CInput layer %s has not source\n",name);
    exit(1);
  }

  if (D!=NULL) {
    if ((imr!=outr)||(imc!=outc)) {
      LMatrix IM;
      IM.resize(batch,nk*outr*outc);
      for(b=0;b<batch;b++) {

	if (trmode) {
	  cr=cc=0;
	  if (imr!=outr) {
	    cr=rand()%((imr-outr)+1);
	  }
	  if (imc!=outc) {
	    cc=rand()%((imc-outc)+1);
	  }
	}
	else {
	  cr=(imr-outr)/2;
	  cc=(imc-outc)/2;
	}
      
            
	int p2=0;
	for(k=0;k<nk;k++) {
	  pk=k*(imc*imr);
	  for(i=0;i<outr;i++) {
	    p=pk+((cr+i)*imc)+cc;
	    for(j=0;j<outc;j++,p++,p2++) {
	      IM(b,p2)=D->M(D->getpos(b),p);
	    }
	  }
	}
      }//batch
      N->copyfromEigen(IM);
    }
    else {
      N->copyfromData(D);
    }
  
    if (trmode) {    
      for(b=0;b<batch;b++) {
	//FLIP
	if ((flip)&&(rand()%2==0))
	  for(k=0;k<nk;k++)
	    doflip(N->subTensor(b,k)->ptr2);

	//SHIFT
	if (shift!=0) {
	  sx=rand()%((shift*2)+1);
	  sy=rand()%((shift*2)+1);
	  sx-=shift;
	  sy-=shift;

	  for(k=0;k<nk;k++)
	    doshift(N->subTensor(b,k)->ptr2,sx,sy);
	}
	//BRIGHTNESS
	if (brightness!=0.0) {
	  double br=calc_brightness(N->subTensor(b,0)->ptr2,brightness);
	  for(k=0;k<nk;k++)
	    dobrightness(N->subTensor(b,k)->ptr2,br);

	}
	//CONTRAST
	if (contrast!=0.0) {
	  for(k=0;k<nk;k++)
	    docontrast(N->subTensor(b,k)->ptr2,contrast);
	}
	// NOISE
	if (noiser!=0.0)
	  for(k=0;k<nk;k++)
	    donoise(N->subTensor(b,k)->ptr2,noiser,noisesd);

	if (noiseb!=0.0)
	  for(k=0;k<nk;k++)
	    donoiseb(N->subTensor(b,k)->ptr2,noiseb);
    
      }
    }
  }//D!=NULL
  else
    N->copy(((FLayer *)L)->N);

  if (VERBOSE) fprintf(stderr,"(%s) N norm %f\n",name,N->norm());
}


void ICLayer::addparent(Layer *l)
{
  fprintf(stderr,"Error: ICLayer(%s) can not have parent layer\n",name);
  exit(1);
}

void ICLayer::save(FILE *fe)
{
  save_param(fe);
}

void ICLayer::load(FILE *fe)
{
  load_param(fe);
}

void ICLayer::forward() 
{
  
}

void ICLayer::backward() {
  int b,i,j,k,p;

  if (L!=NULL) {
    // pass Delta to parent (FC) Layer
    ((FLayer *)L)->Delta->copy(Delta);
    L->backward();
  }
}

void ICLayer::initialize() {}
void ICLayer::applygrads() {}
void ICLayer::reset() {}
void ICLayer::resetmomentum() {}
