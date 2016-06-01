#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <iostream>

#include "Dense"
#include "layer.h"
#include "utils.h"

#define VERBOSE 0

using namespace Eigen;
using namespace std;

////////////////////////////////////
///// CONVOLUTIONAL LAYER CLASS
////////////////////////////////////
struct tdata{
  int id;
  int nt;
  int batch;
  int nk;
  int kr;
  int kc;
  int kz;
  int outr;
  int outc;
  int zpad;
  int rpad;
  int cpad;
  int stride;
  int inr;
  int inc;
  int bn;

  MatrixXf **N;
  MatrixXf **K;
  VectorXf bias;
  MatrixXf **E;

  MatrixXf **D;
  MatrixXf **gK;
  VectorXf gbias;
  MatrixXf **IN;
  MatrixXf **ID;
};


pthread_t thr[1000];
struct tdata td[1000];

CLayer::CLayer()
{
  type=2;
}

CLayer::CLayer(int batch,char *name):Layer(batch,name)
{
  type=2;
  threads=4;
  rpad=cpad=zpad=0;
  stride=1;
}


CLayer::CLayer(int nk,int kr, int kc,int batch,int rp,int cp,int stride,char *name):Layer(batch,name)
{
  
  this->nk=nk;
  outz=nk;
  this->kr=kr;
  this->kc=kc;
  this->batch=batch;
  this->stride=stride;
  act=1;
  type=2;
  threads=4;
  
  rpad=rp;
  cpad=cp;

  if ((rpad)||(cpad)) zpad=1;

  if (stride<=0) {
    fprintf(stderr,"Error stride value %d\n",stride);
    exit(1);
  }

  fprintf(stderr,"Creating Conv layer (%s) with %d@%dx%d kernels pad=%dx%d stride=%d\n",name,nk,kr,kc,rpad,cpad,stride);
}

void CLayer::setzpad(int t)
{
  zpad=t;
}

void CLayer::addchild(Layer *l)
{
  int enc=0;
  
  for(int i=0;i<lout;i++)
    if (Lout[i]==l) enc=1;
  
  if (!enc) {
    if (l->type==1) {
      Lout[lout++]=l;
      fprintf(stderr,"Connecting %s --> %s FC\n",name,l->name);
      l->addparent(this);
    }
    else if (l->type==2) {
      Lout[lout++]=l;
      fprintf(stderr,"Connecting %s --> %s Conv\n",name,l->name);
      l->addparent(this);
    }
    else if (l->type==3) {
      Lout[lout++]=l;
      fprintf(stderr,"Connecting %s --> %s MP\n",name,l->name);
      l->addparent(this);
    }
    else if (l->type==4) {
      Lout[lout++]=l;
      fprintf(stderr,"Connecting %s --> %s Cat\n",name,l->name);
      l->addparent(this);
    }
    else {
      fprintf(stderr,"Error: %s conv layer can not have child layer %s\n",name,l->name);
      exit(1);
    }
  }
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

  if (l->type>1) {
    Lin[lin++]=l;

    c=(CLayer *)l;
    kz=c->outz;
    
    if (!zpad) {
      outr=((c->outr-kr)/stride)+1;
      outc=((c->outc-kc)/stride)+1;
    }
    else {
      outr=((c->outr-kr)/stride)+1;
      outc=((c->outc-kc)/stride)+1;

      if (rpad) outr=(c->outr/stride);
      if (cpad) outc=(c->outc/stride);
    }

    fprintf(stderr,"Creating Convol (%d@%dx%d) output %d@%dx%d\n",nk,kr,kc,outz,outr,outc);
    
    if ((outr<=0)||(outc<=0)||(outz<=0)||(nk<=0)||(kr<=0)||(kc<=0)) exit(1);

    K=(MatrixXf **)malloc(nk*sizeof(MatrixXf *));
    for(i=0;i<nk;i++) 
      K[i]=new MatrixXf[kz];
     
    for(i=0;i<nk;i++)
      for(j=0;j<kz;j++)
	K[i][j].resize(kr,kc);

    bias.resize(nk);
    gbias.resize(nk);
     
    gK=(MatrixXf **)malloc(nk*sizeof(MatrixXf *));
    for(i=0;i<nk;i++) 
      gK[i]=new MatrixXf[kz];

  
    for(i=0;i<nk;i++)
      for(j=0;j<kz;j++)
	gK[i][j].resize(kr,kc);

    pgK=(MatrixXf **)malloc(nk*sizeof(MatrixXf *));
    for(i=0;i<nk;i++) 
      pgK[i]=new MatrixXf[kz];

  
    for(i=0;i<nk;i++)
      for(j=0;j<kz;j++) {
	pgK[i][j].resize(kr,kc);
	pgK[i][j].setZero();
      }	
    

    E=(MatrixXf **)malloc(batch*sizeof(MatrixXf *));
    for(i=0;i<batch;i++) {
      E[i]=new MatrixXf[nk];
    }
  
    for(i=0;i<batch;i++)
      for(j=0;j<nk;j++) {
	E[i][j].resize(outr,outc);
      }
   

    N=(MatrixXf **)malloc(batch*sizeof(MatrixXf *));
    for(i=0;i<batch;i++) {
      N[i]=new MatrixXf[nk];
    }

    for(i=0;i<batch;i++)
      for(j=0;j<nk;j++)
	N[i][j].resize(outr,outc);

    
    De=(MatrixXf **)malloc(batch*sizeof(MatrixXf *));
    for(i=0;i<batch;i++) {
      De[i]=new MatrixXf[nk];
    }
  
    for(i=0;i<batch;i++)
      for(j=0;j<nk;j++)
	De[i][j].resize(outr,outc);


    Dvec=new MatrixXf[nk];
    for(j=0;j<nk;j++)
      Dvec[j].resize(outr,outc);


    // FOR BN
    bn_mean.resize(nk);
    bn_var.resize(nk);
    bn_gmean.resize(nk);
    bn_gvar.resize(nk);
    bn_g.resize(nk);
    bn_b.resize(nk);
    
    gbn_mean.resize(nk);
    gbn_var.resize(nk);
    gbn_g.resize(nk);
    gbn_b.resize(nk);

    BNE=(MatrixXf **)malloc(batch*sizeof(MatrixXf *));
    for(i=0;i<batch;i++) {
      BNE[i]=new MatrixXf[nk];
    }
  
    for(i=0;i<batch;i++)
      for(j=0;j<nk;j++)
	BNE[i][j].resize(outr,outc);
  
    bn_E=(MatrixXf **)malloc(batch*sizeof(MatrixXf *));
    for(i=0;i<batch;i++) {
      bn_E[i]=new MatrixXf[nk];
    }
  
    for(i=0;i<batch;i++)
      for(j=0;j<nk;j++)
	bn_E[i][j].resize(outr,outc);
  

    gbn_E=(MatrixXf **)malloc(batch*sizeof(MatrixXf *));
    for(i=0;i<batch;i++) {
      gbn_E[i]=new MatrixXf[nk];
    }
  
    for(i=0;i<batch;i++)
      for(j=0;j<nk;j++)
	gbn_E[i][j].resize(outr,outc);
    


    
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

void *Convolt(void *threadarg)
{
  struct tdata *m;

  m = (struct tdata*) threadarg;

  int i,j,k,z,b,r,im,in,i2,j2,ib;
  float sum=0.0;
  int ini,fin;

  MatrixXf **Nt=m->N;
  MatrixXf **Et=m->E;
  MatrixXf **Kt=m->K;
  VectorXf bt=m->bias;
  MatrixXf B(m->kr,m->kc);
  int stride=m->stride;

  if (m->nt<m->batch) {
    ini=(m->id*(m->batch/m->nt));
    fin=ini+(m->batch/m->nt);
    if (m->id==(m->nt-1)) fin=m->batch;
  }
  else {
    ini=m->id;
    fin=ini+1;
  }

  if ((m->nt<m->batch)||(m->id<m->batch)) { 
    // LOWERING
    MatrixXf I(m->kr*m->kc*m->kz,(fin-ini)*m->outr*m->outc);
    
    Matrix<float, Dynamic,Dynamic, RowMajor> K;
    K.resize(m->nk, m->kr*m->kc*m->kz);

    //MatrixXf K(m->nk, m->kr*m->kc*m->kz);  

    MatrixXf O(m->nk,(fin-ini)*m->outr*m->outc);
	  
    int size=m->outr*m->outc;
    int kr2=m->kr/2;
    int kc2=m->kc/2;
    int si,sj;
    int inr=m->inr;
    int inc=m->inc;
    int bn=m->bn;

    if (!m->rpad) kr2=0;
    if (!m->cpad) kc2=0;
    
    for(k=0;k<m->nk;k++) {
      b=0;
      for(z=0;z<m->kz;z++) 
	for(i=0;i<m->kr;i++) 
	  for(j=0;j<m->kc;j++,b++) 
	    K(k,b)=Kt[k][z](i,j);
    }
    

    ib=0;
    for(b=ini;b<fin;b++,ib+=size) {
      in=0;      
      for(i=0;i<m->outr;i++) 
	for(j=0;j<m->outc;j++,in++) {
	  im=0;
	  for(z=0;z<m->kz;z++) {
	    si=(i*stride)-kr2;
	    sj=(j*stride)-kc2;
	    for(i2=0;i2<m->kr;i2++,si++) 
	      for(j2=0,sj=(j*stride)-kc2;j2<m->kc;j2++,im++,sj++) 
		if ((si<0)||(sj<0)||(si>=inr)||(sj>=inc))
		  I(im,in+ib)=0.0;
		else 
		  I(im,in+ib)=Nt[b][z](si,sj);

	  }
	}
    }


    O=K*I;

    ib=0;
    for(b=ini;b<fin;b++,ib+=size) {
      for(k=0;k<m->nk;k++) {
	z=0;
	for(i=0;i<m->outr;i++) 
	  for(j=0;j<m->outc;j++,z++) {
	    Et[b][k](i,j)=O(k,z+ib);
	    if (!bn) Et[b][k](i,j)+=bt(k);
	  }
      }
    }
    

  }

}



void CLayer::Convol()
{
  
  void *status;
  int rc;
  int nt=threads;
  int i,b;
  float sum=0.0;
  CLayer *cin;
  PLayer *pin;
  CatLayer *cat;
  
  ///////////////////
  cin=(CLayer *)Lin[0];
    
  if (VERBOSE) {
    for(b=0;b<batch;b++) 
      for(i=0;i<cin->outz;i++) 
	sum+=cin->N[b][i].norm();
    
    fprintf(stderr,"(%s) Parent N(%s %dx%d) = %f\n",name,cin->name,batch,cin->outz,sum);
  }
  

  for( i=0; i < nt; ++i ){
    td[i].id=i;
    td[i].nt=nt;
    td[i].batch=batch;
    td[i].nk=nk;
    td[i].kr=kr;
    td[i].kc=kc;
    td[i].kz=kz;
    td[i].outr=outr;
    td[i].outc=outc;
    td[i].zpad=zpad;
    td[i].rpad=rpad;
    td[i].cpad=cpad;
    td[i].stride=stride;

    td[i].N=cin->N;
    td[i].bias=bias;
    td[i].K=K;
    td[i].E=E;
    td[i].inr=cin->outr;
    td[i].inc=cin->outc;
    td[i].bn=bn;
    

    rc = pthread_create(&thr[i], NULL,Convolt, (void *)(&td[i]));
    if (rc){
      fprintf(stderr,"Error:unable to create thread %d",rc);
      exit(-1);
    }
  }


  for( i=0; i < nt; ++i ){
    rc = pthread_join(thr[i], &status);
    if (rc){
      cout << "Error:unable to join," << rc << endl;
      exit(-1);
    }
  }

 
}

void CLayer::doActivation()
{
  
  if (bn) {
#pragma omp parallel for
    for(int i=0;i<batch;i++)
      for(int k=0;k<nk;k++) {
	if (act==0) N[i][k]=BNE[i][k];
	if (act==1) ReLu(BNE[i][k],N[i][k]);
	if (act==2) Sigmoid(BNE[i][k],N[i][k]);
	if (act==3) ELU(BNE[i][k],N[i][k],1.0);
      }
  }
  else {
#pragma omp parallel for
    for(int i=0;i<batch;i++)
      for(int k=0;k<nk;k++) {
	if (act==0) N[i][k]=E[i][k];
	if (act==1) ReLu(E[i][k],N[i][k]);
	if (act==2) Sigmoid(E[i][k],N[i][k]);
	if (act==3) ELU(E[i][k],N[i][k],1.0);
      }
  }
}




void CLayer::fBN()
{

  if (trmode) {
    bnc++;
#pragma omp parallel for
    for(int i=0;i<nk;i++) {
      int j,k,r,c,b;
      float m,var,eps=0.0001;
      m=0;
      for(b=0;b<batch;b++)
	for(r=0;r<outr;r++)
	  for(c=0;c<outc;c++) 
	    m+=E[b][i](r,c);
      m/=(batch*outr*outc);
      bn_mean(i)=m;
    
      var=0;
      for(b=0;b<batch;b++)
	for(r=0;r<outr;r++)
	  for(c=0;c<outc;c++) 
	    var+=(m-E[b][i](r,c))*(m-E[b][i](r,c));
      var/=((batch*outr*outc)-1);
      bn_var(i)=var;
    	
      for(b=0;b<batch;b++)
	for(r=0;r<outr;r++)
	  for(c=0;c<outc;c++) {
	    bn_E[b][i](r,c)=(E[b][i](r,c)-bn_mean(i))/sqrt(bn_var(i)+eps);
	    BNE[b][i](r,c)=(bn_g(i)*bn_E[b][i](r,c))+bn_b(i);
	  }

    }
    bn_gmean+=bn_mean;
    bn_gvar+=bn_var;  
  }
  else {
#pragma omp parallel for
    for(int i=0;i<nk;i++) {
      int j,k,r,c,b;
      float m,var,eps=0.0001;
      for(b=0;b<batch;b++)
	for(r=0;r<outr;r++)
	  for(c=0;c<outc;c++) {
	    bn_E[b][i](r,c)=(E[b][i](r,c)-(bn_gmean(i))/bnc)/sqrt((bn_gvar(i)/bnc)+eps);
	    BNE[b][i](r,c)=(bn_g(i)*bn_E[b][i](r,c))+bn_b(i);
	  }
    }
  }
    
}


void CLayer::forward()
{
  int i,j,k,b,r,c;
  float sum=0;

  if (lout>0) {
   
    Convol();

    if (VERBOSE) {
      for(i=0;i<batch;i++)
	for(k=0;k<nk;k++) 
	  sum+=E[i][k].norm();
      fprintf(stderr,"Preact E(%s %dx%d)=%f\n",name,batch,nk,sum);
    }
    
    //BN
    if (bn) fBN();

    if ((VERBOSE)&&(bn)) {
      sum=0.0;
      for(i=0;i<batch;i++)
	for(k=0;k<nk;k++) 
	  sum+=BNE[i][k].norm();
      fprintf(stderr,"BNE(%s)=%f\n",name,sum);
    }

    //Activation
    doActivation();

    // drop-out
    if (drop>0.0) {
      if (trmode) {
	for(int j=0;j<nk;j++) 
	  for(int r=0;r<outr;r++)
	    for(int c=0;c<outc;c++)
	      if (uniform()<drop) {
		Dvec[j](r,c)=0.0;
		for(int i=0;i<batch;i++) 
		  N[i][j](r,c)=0.0;
	      }
	      else Dvec[j](r,c)=1.0;
      }
      else { //testmode
	for(int i=0;i<batch;i++) 
	  for(int j=0;j<nk;j++) 
	    for(int r=0;r<outr;r++)
	      for(int c=0;c<outc;c++)
		N[i][j](r,c)*=(1.0-drop);
      }
    }

    if (VERBOSE) {
      sum=0.0;
      for(i=0;i<batch;i++)
	for(k=0;k<nk;k++) 
	  sum+=N[i][k].norm();
      fprintf(stderr,"N(%s %dx%d)=%f\n",name,batch,nk,sum);
    }
  }
}

///////////////////
// BACKWARD
///////////////////
void *ConvolB1t(void *threadarg)
{
  struct tdata *m;
  
  m = (struct tdata*) threadarg;

  int i,j,k,z,b,i2,j2;
  float sum;
  int ini,fin;

  MatrixXf **Dt=m->D;
  MatrixXf **INt=m->IN;
  MatrixXf **gKt=m->gK;
  VectorXf gbt=m->gbias;
  MatrixXf **Kt=m->K;
  int kr2=m->kr/2;
  int kc2=m->kc/2;
  int si,sj;
  int stride=m->stride;
  int inr=m->inr;
  int inc=m->inc;
  int bn=m->bn;

  if (!m->rpad) kr2=0;
  if (!m->cpad) kc2=0;
    
  // Compute Grad
  int kini,kfin,zini,zfin;
  
  kini=zini=0;
  kfin=m->nk;
  zfin=m->kz;
    

  if (m->nk>m->kz) {
    if (m->nt<m->nk) {
      kini=(m->id*(m->nk/m->nt));
      kfin=kini+(m->nk/m->nt);
      if (m->id==(m->nt-1)) kfin=m->nk;
    }
    else {
      kini=m->id;
      kfin=kini+1;
    }
  }
  else {
    if (m->nt<m->kz) {
      zini=(m->id*(m->kz/m->nt));
      zfin=zini+(m->kz/m->nt);
      if (m->id==(m->nt-1)) zfin=m->kz;
    }
    else {
      zini=m->id;
      zfin=zini+1;
    }

  }

  if ( ((m->nk>m->kz)&&((m->nt<m->nk)||(m->id<m->nk))) || ((m->nk<=m->kz)&&((m->nt<m->kz)||(m->id<m->kz))) ) {
    
    // LOWERING
    Matrix <float,Dynamic,Dynamic,RowMajor> I;
    I.resize((zfin-zini)*m->kr*m->kc,m->batch*m->outr*m->outc);

    //MatrixXf I((zfin-zini)*m->kr*m->kc,m->batch*m->outr*m->outc);
    MatrixXf D(m->batch*m->outr*m->outc,(kfin-kini));
    MatrixXf Res((zfin-zini)*m->kr*m->kc,(kfin-kini));
    int p,q;

    // Prepare I
    q=0;
    for(z=zini;z<zfin;z++) {	
      for(i=0;i<m->kr;i++)
	for(j=0;j<m->kc;j++,q++) {
	  p=0;
	  for(b=0;b<m->batch;b++) {
	    for(i2=0;i2<m->outr;i2++)
	      for(j2=0;j2<m->outc;j2++,p++) {
		si=((i2*stride)-kr2)+i;
		sj=((j2*stride)-kc2)+j;
		if ((si<0)||(si>=inr)||(sj<0)||(sj>=inc)) I(q,p)=0.0;
		else I(q,p)=INt[b][z](si,sj);
	      }
	  }
	}
    }

    //Prepare Delta
    for(k=kini;k<kfin;k++) {
      p=0;
      for(b=0;b<m->batch;b++)
	for(i=0;i<m->outr;i++)
	  for(j=0;j<m->outc;j++,p++)
	    D(p,k-kini)=Dt[b][k](i,j);
    }

    Res=I*D;
    
    // Reshape to gradient
    for(k=kini;k<kfin;k++) {
      p=0;
      for(z=zini;z<zfin;z++) {	
	for(i2=0;i2<m->kr;i2++)
	  for(j2=0;j2<m->kc;j2++,p++) 
	    gKt[k][z](i2,j2)=Res(p,k-kini);
      }
    }
    

  }//if

  //Bias
  if (!bn) {
    if (m->nt<m->nk) {
      kini=(m->id*(m->nk/m->nt));
      kfin=kini+(m->nk/m->nt);
      if (m->id==(m->nt-1)) kfin=m->nk;
    }
    else {
      kini=m->id;
      kfin=kini+1;
    }
 
    if ((m->nt<m->nk)||(m->id<m->nk)) {
      for(k=kini;k<kfin;k++) 
	for(b=0;b<m->batch;b++) {
	  for(i2=0;i2<m->outr;i2++)
	    for(j2=0;j2<m->outc;j2++)
	      gbt(k)+=Dt[b][k](i2,j2);
	}
    }
  }
}


void *ConvolB2t(void *threadarg)
{
  struct tdata *m;
  
  m = (struct tdata*) threadarg;
  
  int i,j,k,z,b,r,c,s,im,in,i2,j2,ib;
  int ini,fin;
  MatrixXf **Dt=m->D;
  MatrixXf **IDt=m->ID;
  MatrixXf **Kt=m->K;
  
  int bini,bfin,zini,zfin;

  // BackProp Deltas 
  bini=zini=0;
  bfin=m->batch;
  zfin=m->kz;
    
  if (m->batch>m->kz) {
    if (m->nt<m->batch) {
      bini=(m->id*(m->batch/m->nt));
      bfin=bini+(m->batch/m->nt);
      if (m->id==(m->nt-1)) bfin=m->batch;
    }
    else {
      bini=m->id;
      bfin=bini+1;
    }
  }
  else {
    if (m->nt<m->kz) {
      zini=(m->id*(m->kz/m->nt));
      zfin=zini+(m->kz/m->nt);
      if (m->id==(m->nt-1)) zfin=m->kz;
    }
    else {
      zini=m->id;
      zfin=zini+1;
    }

  }
 
  if ( ((m->batch>m->kz)&&((m->nt<m->batch)||(m->id<m->batch))) || ((m->batch<=m->kz)&&((m->nt<m->kz)||(m->id<m->kz))) ) {
    // LOWERING
    //Matrix <float,Dynamic,Dynamic,RowMajor> Del;
    //Del.resize(bfin-bini,m->nk);
    MatrixXf Del(bfin-bini,m->nk);


    //Matrix <float,Dynamic,Dynamic,RowMajor> Kr;
    //Kr.resize(m->nk,m->kr*m->kc);
    MatrixXf *Kr;
    Kr=new MatrixXf[m->kz];
    for(i=0;i<m->kz;i++)
      Kr[i].resize(m->nk,m->kr*m->kc);

    MatrixXf Res(bfin-bini,m->kr*m->kc);

    int si,sj;
    int kr2=m->kr/2;
    int kc2=m->kc/2;
    int stride=m->stride;
    int inr=m->inr;
    int inc=m->inc;

    if (!m->rpad) kr2=0;
    if (!m->cpad) kc2=0;

    for(z=zini;z<zfin;z++) {
      for(k=0;k<m->nk;k++)
	for(i2=0,r=0,c=0;i2<m->kc*m->kr;i2++,c++) {
	  if (c==m->kc) {c=0;r++;}
	  Kr[z](k,i2)=Kt[k][z](r,c);
	}
    }
    
    if (m->zpad) {


      for(i=0;i<m->outr;i++) {
	for(j=0;j<m->outc;j++) {

	  for(b=bini;b<bfin;b++) 
	    for(k=0;k<m->nk;k++)
	      Del(b-bini,k)=Dt[b][k](i,j);

	  for(z=zini;z<zfin;z++) {
	    Res=Del*Kr[z];
	
	    for(b=bini;b<bfin;b++) {
	      for(i2=0,r=0,c=0;i2<m->kc*m->kr;i2++,c++) {
		if (c==m->kc) {c=0;r++;}
		si=(i*stride+r)-kr2;
		sj=(j*stride+c)-kc2;
		if ((si<0)||(sj<0)||(si>=inr)||(sj>=inc)) { }
		else IDt[b][z](si,sj)+=Res(b-bini,i2);
	      }
	    }

	  }//z

	}//j
      }//i
    }
    else {
      for(i=0;i<m->outr;i++) {
	for(j=0;j<m->outc;j++) {

	  for(b=bini;b<bfin;b++) 
	    for(k=0;k<m->nk;k++)
	      Del(b-bini,k)=Dt[b][k](i,j);

	  for(z=zini;z<zfin;z++) {

	    Res=Del*Kr[z];
	
	    for(b=bini;b<bfin;b++) {
	      for(i2=0,r=0,c=0;i2<m->kc*m->kr;i2++,c++) {
		if (c==m->kc) {c=0;r++;}
		IDt[b][z](i*stride+r,j*stride+c)+=Res(b-bini,i2);
		
	      }
	    }

	  }//z

	}//j
      }//i
    }
  }
  
}


void CLayer::ConvolB()
{
  
  void *status;
  int rc;
  int nt=threads;
  int i,j,r,c;
  float sum;

  CLayer *cin;

  cin=(CLayer *)Lin[0];

  if (drop>0.0) 
    //#pragma omp parallel for
    for(int j=0;j<nk;j++) 
      for(int r=0;r<outr;r++)
	for(int c=0;c<outc;c++)
	  if (Dvec[j](r,c)==0.0) 
	    for(int i=0;i<batch;i++) 
	      De[i][j](r,c)=0.0;

  
  if (act==0){
    //Delta as it is
  }    
  else if (act==1) { //ReLu Deriv
#pragma omp parallel for
    for(int b=0;b<batch;b++) 
      for(int k=0;k<nk;k++) 
	for(int r=0;r<outr;r++)
	  for(int c=0;c<outc;c++)
	    if (bn) {
	      if (BNE[b][k](r,c)<=0) De[b][k](r,c)=0.0;
	    }
	    else
	      if (E[b][k](r,c)<=0) De[b][k](r,c)=0.0;
		
	    
  }
  else if (act==2) { //Sigmoid Deriv
#pragma omp parallel for
    for(int b=0;b<batch;b++) 
      for(int k=0;k<nk;k++) 
	for(int r=0;r<outr;r++)
	  for(int c=0;c<outc;c++)
	    if (bn) De[b][k](r,c)*=dsigm(BNE[b][k](r,c));
	    else De[b][k](r,c)*=dsigm(E[b][k](r,c));
  }
  else if (act==3) { //ELU
#pragma omp parallel for
    for(int b=0;b<batch;b++) 
      for(int k=0;k<nk;k++) 
	for(int r=0;r<outr;r++)
	  for(int c=0;c<outc;c++)
	    if (bn) {
	      if (BNE[b][k](r,c)<=0) De[b][k](r,c)*=(N[b][k](r,c)+1);
	    }
	    else if (E[b][k](r,c)<=0) De[b][k](r,c)*=(N[b][k](r,c)+1);
  }
  
  

  if (bn) bBN();


  if (VERBOSE) {
    sum=0;
    for(int b=0;b<batch;b++) 
      for(int k=0;k<nk;k++) 
	sum+=De[b][k].norm();
    fprintf(stderr,"DeN(%s) %f\n",name,sum);
  }

 
  if (VERBOSE) {
    sum=0;
    for(int k=0;k<nk;k++) 
      for(int z=0;z<kz;z++) 
	sum+=K[k][z].norm();
    fprintf(stderr,"KernelN %f\n",sum);
  }

  if (nt<2) nt=2;

  for( i=0; i < nt; ++i ){

    td[i].id=(i%(nt/2));

    td[i].nt=nt/2;
    td[i].batch=batch;
    td[i].nk=nk;
    td[i].kr=kr;
    td[i].kc=kc;
    td[i].kz=kz;
    td[i].outr=outr;
    td[i].outc=outc;
    td[i].zpad=zpad;
    td[i].rpad=rpad;
    td[i].cpad=cpad;
    td[i].stride=stride;

    td[i].D=De;
    td[i].gK=gK;
    td[i].gbias=gbias;
    td[i].K=K;
    td[i].inr=cin->outr;
    td[i].inc=cin->outc;
    td[i].bn=bn;
    
    td[i].IN=cin->N;
    td[i].ID=cin->De;
    
    if (i<nt/2) {
      rc = pthread_create(&thr[i], NULL,ConvolB1t, (void *)(&td[i]));
      if (rc){
	fprintf(stderr,"Error:unable to create thread %d",rc);
	exit(-1);
      }
    }
    else {
      rc = pthread_create(&thr[i], NULL,ConvolB2t, (void *)(&td[i]));
      if (rc){
	fprintf(stderr,"Error:unable to create thread %d",rc);
	exit(-1);
      }
    }
    
  }

  
  for( i=0; i < nt; ++i ){
    rc = pthread_join(thr[i], &status);
    if (rc){
      cout << "Error:unable to join," << rc << endl;
      exit(-1);
    }
  }

  
  if (VERBOSE) {
    float sum=0.0;
    for(int i=0;i<nk;i++) 
      for(int j=0;j<kz;j++) 
	sum+=(gK[i][j].norm());
    
    fprintf(stderr,"grads (%s) %f\n",name,sum);
  }
  
}


void CLayer::bBN()
{
#pragma omp parallel for
  for(int i=0;i<nk;i++) {
    int j,k,r,c,b;
    float m,var,eps=0.0001;
    
    m=batch*outr*outc;
    //1 Gamma
    gbn_g(i)=0.0;
    for(b=0;b<batch;b++)
      for(r=0;r<outr;r++)
	for(c=0;c<outc;c++) 
	  gbn_g(i)+=De[b][i](r,c)*bn_E[b][i](r,c);
  
    //2 Beta

    gbn_b(i)=0.0;
    for(b=0;b<batch;b++)
      for(r=0;r<outr;r++)
	for(c=0;c<outc;c++) 
	  gbn_b(i)+=De[b][i](r,c);
  

    //3 bnE

    for(b=0;b<batch;b++)
      for(r=0;r<outr;r++)
	for(c=0;c<outc;c++) 
	  gbn_E[b][i](r,c)=De[b][i](r,c)*bn_g(i);
  
	  
    //4 Var

    gbn_var(i)=0;
    for(b=0;b<batch;b++)
      for(r=0;r<outr;r++)
	for(c=0;c<outc;c++) 
	  gbn_var(i)+=-0.5*gbn_E[b][i](r,c)*(E[b][i](r,c)-bn_mean(i))/((bn_var(i)+eps)*sqrt(bn_var(i)+eps));
    
  
    //5 Mean

    gbn_mean(i)=0;
    for(b=0;b<batch;b++)
      for(r=0;r<outr;r++)
	for(c=0;c<outc;c++) {
	  gbn_mean(i)+=-gbn_E[b][i](r,c)/sqrt(bn_var(i)+eps);
	  gbn_mean(i)+=-2*gbn_var(i)*(E[b][i](r,c)-bn_mean(i))/m;
	  
	}
  
    //6 x

    for(b=0;b<batch;b++)
      for(r=0;r<outr;r++)
	for(c=0;c<outc;c++) {
	  De[b][i](r,c)=gbn_E[b][i](r,c)/(sqrt(bn_var(i)+eps));
	  De[b][i](r,c)+=gbn_var(i)*2*(E[b][i](r,c)-bn_mean(i))/m;
	  De[b][i](r,c)+=gbn_mean(i)/m;
	}
  }
	  
  
}


void CLayer::backward()
{

  if (lin>0) {
    ConvolB();
  }
}


void CLayer::initialize()
{
  int i,j,r,c;
  float s=sqrt(2.0/(kr*kc*kz));

  if (!init) {
    for(i=0;i<nk;i++) {
      bias(i)=0.1;

      for(j=0;j<kz;j++) {
	for(r=0;r<kr;r++)
	  for(c=0;c<kc;c++)
	    K[i][j](r,c)=s*gauss(0,1);
      }
    }

    for(i=0;i<nk;i++) {
      bn_g(i)=1.0;      
      bn_b(i)=0.0;
    }
    init=1;
  }
}

  void CLayer::applygrads()
  {
    float sum=0.0;

#pragma omp parallel for
    for(int i=0;i<nk;i++) {
      bias(i)+=(mu/batch)*gbias(i);

      for(int j=0;j<kz;j++) {
	pgK[i][j]=(mu/batch)*gK[i][j]+mmu*pgK[i][j];
	K[i][j]+=pgK[i][j];
	if (l2!=0.0) 
	  K[i][j]-=l2*K[i][j];
	sum+=(gK[i][j].norm());
      }
      if (sum!=sum) {
	fprintf(stderr,"Nan values!!\n");
	exit(1);
      }
      if (bn) {
	bn_g(i)+=(mu/batch)*gbn_g(i);
	bn_b(i)+=(mu/batch)*gbn_b(i);
      }
  
    }
    if (VERBOSE) {
      fprintf(stderr,"%s IncK %f\n",name,sum/(nk*kz));
    }
  
    if (VERBOSE) fprintf(stderr,"grads (%s) %f\n",name,sum);
  }
	  
  void CLayer::resetmomentum()
  {
    int k,z;

    if (VERBOSE)  fprintf(stderr,"layer %s reset momentum\n",name);
    for(k=0;k<nk;k++) 
      for(z=0;z<kz;z++) 
	pgK[k][z].setZero();

  }

  void CLayer::reset()
  {
    int i,j,k,z;

    for(i=0;i<batch;i++)
      for(j=0;j<nk;j++)
	De[i][j].setZero();

    gbias.setZero();
    for(k=0;k<nk;k++) 
      for(z=0;z<kz;z++) 
	gK[k][z].setZero();

  }
  void CLayer::resetstats()
  {

    bnc=0;

    bn_gmean.setZero();
    bn_gvar.setZero();

  }

void CLayer::savekernels(int v)
{
  int i,j,r,c;
  FILE *fs;
  char name[100];
  float min,max,fv;
  int g;


  if ((kz==1)||(kz==3)) {

    fprintf(stderr,"Saving kernels...\n");
    min=max=K[0][0](0,0);

    for(i=0;i<nk;i++)
      for(j=0;j<kz;j++) 
	for(r=0;r<kr;r++)
	  for(c=0;c<kc;c++){
	    if (K[i][j](r,c)>max) max=K[i][j](r,c);
	    if (K[i][j](r,c)<min) min=K[i][j](r,c);
	  }

      
    if (kz==3) {
      sprintf(name,"kernel_%d.ppm",v);
      fs=fopen(name,"wt");
      fprintf(fs,"P3\n%d %d\n255\n",((kc+1)*nk),kr);
    }
    else {
      sprintf(name,"kernel_%d.pgm",v);
      fs=fopen(name,"wt");
      fprintf(fs,"P2\n%d %d\n255\n",(kc+1)*nk,kr);
    }
    

    for(r=0;r<kr;r++) {
      for(i=0;i<nk;i++) {
	for(c=0;c<kc;c++) {
	  for(j=0;j<kz;j++) {
	    fv=(K[i][j](r,c)-min)/(max-min);
	    fv*=255.0;
	    g=fv;
	    fprintf(fs,"%d ",g);
	  }
	}
	for(j=0;j<kz;j++)
	  fprintf(fs,"255 ");
      }
      fprintf(fs,"\n");
    }

    fprintf(fs,"\n");
    fclose(fs);
      
  }
  else {
    fprintf(stderr,"Not saving kernels...\n");
  }
}

  ///////////////////////////////////////////
  /// Input Convol Layer
  ///////////////////////////////////////////
ICLayer::ICLayer(Data *D,int batch,int z,int ir,int ic,int cr,int cc,char *name):CLayer(batch,name)
{
  int i,j;

  this->batch=batch;
  this->D=D;
  act=1;
  shift=0;
  flip=0;
  brightness=0.0;
  contrast=0.0;

  ////////////////////////////////////////////

  if ((z*ir*ic)!=D->dim) {
    fprintf(stderr,"Error Conv Data for Reshape %d!=%d\n",z*ir*ic,D->dim);
    exit(1);
  }

  imr=ir;
  imc=ic;

  outr=cr;
  outc=cc;
  nk=z;
  outz=z;
  
  if ((imr<outr)||(imc<outc)){
    fprintf(stderr,"Error input lower than out (%dx%d)<(%dx%d)\n",imr,imc,outr,outc);
    exit(1);
  }

  fprintf(stderr,"Creating Convol input %d@%dx%d from %d@%dx%d batch %d\n",outz,outr,outc,outz,imr,imc,batch);


  N=(MatrixXf **)malloc(batch*sizeof(MatrixXf *));
  if (N==NULL) {
    fprintf(stderr,"Error Mem\n");
    exit(1);
  }

  for(i=0;i<batch;i++) {
    N[i]=new MatrixXf[nk];
    
    if (N[i]==NULL) {
      fprintf(stderr,"Error Mem i\n");
      exit(1);
    }
  }

  for(i=0;i<batch;i++) 
    for(j=0;j<nk;j++) 
      (N[i][j]).resize(outr,outc);

  
  De=(MatrixXf **)malloc(batch*sizeof(MatrixXf *));
  if (N==NULL) {
    fprintf(stderr,"Error Mem\n");
    exit(1);
  }

  for(i=0;i<batch;i++) {
    De[i]=new MatrixXf[nk];
    
    if (De[i]==NULL) {
      fprintf(stderr,"Error Mem i\n");
      exit(1);
    }
  }

  for(i=0;i<batch;i++) 
    for(j=0;j<nk;j++) 
      (De[i][j]).resize(outr,outc);

  
  Dvec=new MatrixXf[nk];
  for(j=0;j<nk;j++)
    Dvec[j].resize(outr,outc);

  fprintf(stderr,"Creating Convol output %d@%dx%d\n",outz,outr,outc);
}

  // RANDOM FLIP
void ICLayer::doflip(MatrixXf& I)
{
  int i,j,r,c;
  MatrixXf T=I;

  r=I.rows();
  c=I.cols();

  for(i=0;i<r;i++)
    for(j=0;j<c;j++)
      I(i,j)=T(i,(c-1)-j);  
}


  // RANDOM SHIFT
void ICLayer::doshift(MatrixXf& I,int sx,int sy)
{
  int i,j,r,c;
  MatrixXf T=I;

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
void ICLayer::donoise(MatrixXf& I,float ratio, float sd)
{
  int i,j,r,c;

  r=I.rows();
  c=I.cols();

  for(i=0;i<r;i++)
    for(j=0;j<c;j++)
      if (uniform()<ratio)
	I(i,j)+=gauss(0.0,sd);
  
}

  // RANDOM BRIGHTNESS
float ICLayer::calc_brightness(MatrixXf I,float factor) 
{
  int i,j,r,c;
  float br;

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

void ICLayer::dobrightness(MatrixXf& I,float b) 
{
  int i,j,r,c;

  r=I.rows();
  c=I.cols();

  for(i=0;i<r;i++)
    for(j=0;j<c;j++)
      I(i,j)+=b;

}


  // RANDOM CONTRAST
void ICLayer::docontrast(MatrixXf& I,float factor) 
{
  int i,j,r,c;
  int sc;
  float smin;
  float s,u;

  r=I.rows();
  c=I.cols();
  
  smin=1.0/factor;
  u=uniform();

  s=smin+(u*(factor-smin));

  for(i=0;i<r;i++)
    for(j=0;j<c;j++)
      I(i,j)+=I(i,j)*s;

}

void ICLayer::SaveImage(MatrixXf R,MatrixXf G,MatrixXf B,char *name)
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

void ICLayer::getbatch(Data *Dt)
{
  int b,i,j,k,p,pk;
  int sx,sy;
  int cr,cc; //crop

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

    for(k=0;k<nk;k++) {
      pk=k*(imc*imr);
      for(i=0;i<outr;i++) {
	p=pk+((cr+i)*imc)+cc;
	for(j=0;j<outc;j++,p++) {
	  N[b][k](i,j)=Dt->M((Dt->gethead()+b)%Dt->num,p);
	}
      }
    }

    //SaveImage(N[b][0],N[b][1],N[b][2],"orig.ppm");
    
    if (trmode) {
      //FLIP
      if ((flip)&&(rand()%2==0)) 
	for(k=0;k<nk;k++) 
	  doflip(N[b][k]);
    


      //SHIFT
      if (shift!=0) {
	sx=rand()%((shift*2)+1);
	sy=rand()%((shift*2)+1);
	sx-=shift;
	sy-=shift;

	for(k=0;k<nk;k++) 
	  doshift(N[b][k],sx,sy);
      }


      //BRIGHTNESS
      if (brightness!=0.0) {
	float br=calc_brightness(N[b][0],brightness);
	for(k=0;k<nk;k++) 
	  dobrightness(N[b][k],br);
     
      }
      //CONTRAST
      if (contrast!=0.0) {
	for(k=0;k<nk;k++) 
	  docontrast(N[b][k],contrast);
      }

      // NOISE
      if (noiser!=0.0)
	for(k=0;k<nk;k++) 
	  donoise(N[b][k],noiser,noisesd);
    }//trmode
  }//b
}


  //void ICLayer::addchild(Layer *l);
void ICLayer::addparent(Layer *l)
{
  fprintf(stderr,"Error: ICLayer(%s) can not have parent layer\n",name);
  exit(1);
}
void ICLayer::forward() {

}

void ICLayer::backward() {

}
void ICLayer::initialize() {

}
void ICLayer::applygrads() {

}
void ICLayer::reset() {

}
