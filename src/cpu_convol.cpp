#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <iostream>

#include "Eigen/Dense"
#include "tensor.h"

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

  Tensor *N;
  Tensor *K;
  Tensor *E;

  Tensor *D;
  Tensor *gK;
  Tensor *IN;
  Tensor *ID;
};


pthread_t thr[100];
struct tdata td[100];



void *ConvolFt(void *threadarg)
{
  struct tdata *m;

  m = (struct tdata*) threadarg;

  int i,j,k,z,b,r,im,in,i2,j2,ib;
  int ini,fin;
  
  Tensor *Nt=m->N;
  Tensor *Et=m->E;
  Tensor *Kt=m->K;
  Tensor *B=new Tensor(m->kr,m->kc);
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
    Tensor *I=new Tensor(m->kr*m->kc*m->kz,(fin-ini)*m->outr*m->outc);
    Tensor *K=new Tensor(m->nk, m->kr*m->kc*m->kz);
    Tensor *O=new Tensor(m->nk,(fin-ini)*m->outr*m->outc);

    int size=m->outr*m->outc;
    int kr2=m->kr/2;
    int kc2=m->kc/2;
    int si,sj;
    int inr=m->inr;
    int inc=m->inc;
    int c;

    if (!m->rpad) kr2=0;
    if (!m->cpad) kc2=0;

    for(k=0;k<m->nk;k++) {
      b=0;
      for(z=0;z<m->kz;z++)
	for(i=0;i<m->kr;i++)
	  for(j=0;j<m->kc;j++,b++)
	    K->ptr2(k,b)=Kt->ptr[k]->ptr[z]->ptr2(i,j);
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
		  I->ptr2(im,in+ib)=0.0;
		else
		  I->ptr2(im,in+ib)=Nt->ptr[b]->ptr[z]->ptr2(si,sj);

	  }
	}
    }
    
    // MAKE LOWERING CONVOLUTION
    O->ptr2=K->ptr2*I->ptr2;
    
    // RESHAPE
    ib=0;
    for(b=ini;b<fin;b++,ib+=size) {
      for(k=0;k<m->nk;k++) {
	z=0;
	for(i=0;i<m->outr;i++)
	  for(j=0;j<m->outc;j++,z++) {
	    Et->ptr[b]->ptr[k]->ptr2(i,j)=O->ptr2(k,z+ib);
	  }
      }
     
    }
    
  
    delete I;
    delete K;
    delete O;
    delete B;
  }
}

void ConvolF(Tensor *N, Tensor *K, Tensor *E,int stride, int pad,int threads,int batch)
{
  void *status;
  int rc;
  int i,b;

  int nt=threads;

  setNbThreads(1);
  for( i=0; i < nt; ++i ){
    td[i].id=i;
    td[i].nt=threads;
    td[i].batch=batch;
    td[i].nk=K->a;
    td[i].kr=K->c;
    td[i].kc=K->d;
    td[i].kz=K->b;
    td[i].outr=E->c;
    td[i].outc=E->d;
    td[i].zpad=pad;
    td[i].rpad=pad;
    td[i].cpad=pad;
    td[i].stride=stride;

    td[i].N=N;
    td[i].K=K;
    td[i].E=E;
    td[i].inr=N->c;
    td[i].inc=N->d;
    
    rc = pthread_create(&thr[i], NULL,ConvolFt, (void *)(&td[i]));
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
  setNbThreads(threads);
}


///////////////////
// BACKWARD
///////////////////
void *ConvolBGradt(void *threadarg)
{
  struct tdata *m;

  m = (struct tdata*) threadarg;

  int i,j,k,z,b,i2,j2;
  double sum;
  int ini,fin;

  Tensor *Dt=m->D;
  Tensor *INt=m->IN;
  Tensor *gKt=m->gK;
  Tensor *Kt=m->K;
  int kr2=m->kr/2;
  int kc2=m->kc/2;
  int si,sj;
  int stride=m->stride;
  int inr=m->inr;
  int inc=m->inc;

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
    Tensor *I=new Tensor((zfin-zini)*m->kr*m->kc,m->batch*m->outr*m->outc);
    Tensor *D=new Tensor(m->batch*m->outr*m->outc,(kfin-kini));
    Tensor *Res=new Tensor((zfin-zini)*m->kr*m->kc,(kfin-kini));
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
		if ((si<0)||(si>=inr)||(sj<0)||(sj>=inc)) I->ptr2(q,p)=0.0;
		else I->ptr2(q,p)=INt->ptr[b]->ptr[z]->ptr2(si,sj);
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
	    D->ptr2(p,k-kini)=Dt->ptr[b]->ptr[k]->ptr2(i,j);
    }

    Res->ptr2=I->ptr2*D->ptr2;

    // Reshape to gradient
    
    for(k=kini;k<kfin;k++) {
      p=0;
      for(z=zini;z<zfin;z++) {
	for(i2=0;i2<m->kr;i2++)
	  for(j2=0;j2<m->kc;j2++,p++)
	    gKt->ptr[k]->ptr[z]->ptr2(i2,j2)=Res->ptr2(p,k-kini);
      }
    }

  delete I;
  delete D;
  delete Res;

  }//if
}


void *ConvolBDeltat(void *threadarg)
{
  struct tdata *m;

  m = (struct tdata*) threadarg;

  int i,j,k,z,b,r,c,s,im,in,i2,j2,ib;
  int ini,fin;
  Tensor *Dt=m->D;
  Tensor *IDt=m->ID;
  Tensor *Kt=m->K;

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
    //Matrix <Ltype,Dynamic,Dynamic,RowMajor> Del;
    //Del.resize(bfin-bini,m->nk);
    Tensor *Del=new Tensor(bfin-bini,m->nk);


    //Matrix <Ltype,Dynamic,Dynamic,RowMajor> Kr;
    //Kr.resize(m->nk,m->kr*m->kc);
    Tensor *Kr=new Tensor(m->kz,m->nk,m->kr*m->kc);
    Tensor *Res=new Tensor(bfin-bini,m->kr*m->kc);

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
	  Kr->ptr[z]->ptr2(k,i2)=Kt->ptr[k]->ptr[z]->ptr2(r,c);
	}
    }

    if (m->zpad) {


      for(i=0;i<m->outr;i++) {
	for(j=0;j<m->outc;j++) {

	  for(b=bini;b<bfin;b++)
	    for(k=0;k<m->nk;k++)
	      Del->ptr2(b-bini,k)=Dt->ptr[b]->ptr[k]->ptr2(i,j);

	  for(z=zini;z<zfin;z++) {
	    Res->ptr2=Del->ptr2*Kr->ptr[z]->ptr2;

	    for(b=bini;b<bfin;b++) {
	      for(i2=0,r=0,c=0;i2<m->kc*m->kr;i2++,c++) {
		if (c==m->kc) {c=0;r++;}
		si=(i*stride+r)-kr2;
		sj=(j*stride+c)-kc2;
		if ((si<0)||(sj<0)||(si>=inr)||(sj>=inc)) { }
		else IDt->ptr[b]->ptr[z]->ptr2(si,sj)+=Res->ptr2(b-bini,i2);
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
	      Del->ptr2(b-bini,k)=Dt->ptr[b]->ptr[k]->ptr2(i,j);

	  for(z=zini;z<zfin;z++) {

	    Res->ptr2=Del->ptr2*Kr->ptr[z]->ptr2;

	    for(b=bini;b<bfin;b++) {
	      for(i2=0,r=0,c=0;i2<m->kc*m->kr;i2++,c++) {
		if (c==m->kc) {c=0;r++;}
		IDt->ptr[b]->ptr[z]->ptr2(i*stride+r,j*stride+c)+=Res->ptr2(b-bini,i2);

	      }
	    }

	  }//z

	}//j
      }//i
    }
    delete Kr;
  }

}


void ConvolBGrad(Tensor *N, Tensor *gK, Tensor *D,int stride, int pad,int threads,int batch)
{

  void *status;
  int rc;
  int nt=2;
  int i,j,r,c;
  double sum;


  setNbThreads(threads/2);
  

  for( i=0; i < nt; ++i ){

    td[i].id=(i%nt);

    td[i].nt=nt;
    td[i].batch=batch;
    td[i].nk=gK->a;
    td[i].kr=gK->c;
    td[i].kc=gK->d;
    td[i].kz=gK->b;
    td[i].outr=D->c;
    td[i].outc=D->d;
    td[i].zpad=pad;
    td[i].rpad=pad;
    td[i].cpad=pad;
    td[i].stride=stride;

    td[i].D=D;
    td[i].gK=gK;
    td[i].K=NULL;
    td[i].inr=N->c;
    td[i].inc=N->d;

    td[i].IN=N;
    td[i].ID=NULL;

    rc = pthread_create(&thr[i], NULL,ConvolBGradt, (void *)(&td[i]));
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

  setNbThreads(threads);
}


void ConvolBDelta(Tensor *D, Tensor *K, Tensor *ID,int stride, int pad,int threads,int batch)
{

  void *status;
  int rc;
  int nt=threads;
  int i,j,r,c;
  double sum;


  setNbThreads(1);

  for( i=0; i < nt; ++i ){

    td[i].id=(i%nt);

    td[i].nt=nt;
    td[i].batch=batch;
    td[i].nk=K->a;
    td[i].kr=K->c;
    td[i].kc=K->d;
    td[i].kz=K->b;
    td[i].outr=D->c;
    td[i].outc=D->d;
    td[i].zpad=pad;
    td[i].rpad=pad;
    td[i].cpad=pad;
    td[i].stride=stride;

    td[i].D=D;
    td[i].gK=NULL;
    td[i].K=K;
    td[i].inr=ID->c;
    td[i].inc=ID->d;

    td[i].IN=NULL;
    td[i].ID=ID;

    rc = pthread_create(&thr[i], NULL,ConvolBDeltat, (void *)(&td[i]));
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

  setNbThreads(threads);
}

