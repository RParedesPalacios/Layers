#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <iostream>

#include "Eigen/Dense"
#include "tensor.h"

#define useMT 1

#define USEOMP

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



void ConvolF(Tensor *N, Tensor *K, Tensor *E,int stride, int rpad,int cpad,int threads,int batch)
{
  

  // LOWERING  N,K,E
  Tensor *I=new Tensor(K->b*K->c*K->d,E->a*E->c*E->d);
  Tensor *Kn=new Tensor(K->a, K->b*K->c*K->d);
  Tensor *O=new Tensor(K->a,E->a*E->c*E->d);

  int size=E->c*E->d;
  int kr2=K->c/2;
  int kc2=K->d/2;
  int si,sj;
  int inr=N->c;
  int inc=N->d;
  int c;
  int i,j,k,m,z,i2,j2,b,ib,im,in;
    
  if (!rpad) kr2=0;
  if (!cpad) kc2=0;

#ifdef USEOMP
#pragma omp parallel for
#endif
  for(int k=0;k<K->a;++k) {
    for(int z=0;z<K->b;++z) {
      int b=z*(K->c*K->d);
      for(int i=0;i<K->c;++i)
	for(int j=0;j<K->d;++j,++b)
	  Kn->ptr2(k,b)=K->ptr[k]->ptr[z]->ptr2(i,j);
    }
  }

#ifdef USEOMP
#pragma omp parallel for
#endif
  for(int z=0;z<K->b;++z) {
    for(int b=0;b<N->a;++b) {
      for(int i=0;i<E->c;++i) {
	int in=i*E->d;
	int ib=b*size;
	for(int j=0;j<E->d;++j,in++) {
	  int im=z*(K->c*K->d);
	  //for(int z=0;z<K->b;++z) {
	  int si=(i*stride)-kr2;
	  int sj=(j*stride)-kc2;
	  for(int i2=0;i2<K->c;++i2,++si)
	    for(int j2=0,sj=(j*stride)-kc2;j2<K->d;++j2,im++,++sj)
	      if ((si<0)||(sj<0)||(si>=inr)||(sj>=inc))
		I->ptr2(im,in+ib)=0.0;
	      else
		I->ptr2(im,in+ib)=N->ptr[b]->ptr[z]->ptr2(si,sj);

	}
      }
    }
  }

  
  // MAKE LOWERING CONVOLUTION
  O->ptr2=Kn->ptr2*I->ptr2;

  // RESHAPE
#ifdef USEOMP
#pragma omp parallel for
#endif
  for(int k=0;k<E->b;++k) {
    for(int b=0;b<E->a;++b) {
      int ib=b*size;
      int z=0;
      for(int i=0;i<E->c;++i)
	for(int j=0;j<E->d;++j,++z) {
	  E->ptr[b]->ptr[k]->ptr2(i,j)=O->ptr2(k,z+ib);
	}
    }
  }
    
  
  delete I;
  delete Kn;
  delete O;

  
}


///////////////////
// BACKWARD
///////////////////
void ConvolBGrad(Tensor *N, Tensor *gK, Tensor *D,int stride, int rpad,int cpad,int threads,int batch)
{

    int kr2=gK->c/2;
    int kc2=gK->d/2;
    int inr=N->c;
    int inc=N->d;

    if (!rpad) kr2=0;
    if (!cpad) kc2=0;
    
    // LOWERING N,gK,D
    Tensor *I=new Tensor(gK->b*gK->c*gK->d,D->a*D->c*D->d);
    Tensor *Dn=new Tensor(D->a*D->c*D->d,gK->a);
    Tensor *Res=new Tensor(D->a*D->c*D->d,gK->a);

    // Prepare I

#ifdef USEOMP
#pragma omp parallel for
#endif
    for(int z=0;z<gK->b;++z) {
      int q=z*(gK->c*gK->d);
      for(int i=0;i<gK->c;++i)
	for(int j=0;j<gK->d;++j,q++) {
	  int p=0;
	  for(int b=0;b<D->a;++b) {
	    for(int i2=0;i2<D->c;++i2)
	      for(int j2=0;j2<D->d;++j2,p++) {
		int si=((i2*stride)-kr2)+i;
		int sj=((j2*stride)-kc2)+j;
		if ((si<0)||(si>=inr)||(sj<0)||(sj>=inc)) I->ptr2(q,p)=0.0;
		else I->ptr2(q,p)=N->ptr[b]->ptr[z]->ptr2(si,sj);
	      }
	  }
	}
    }
    
    //Prepare Delta
#ifdef USEOMP
#pragma omp parallel for
#endif
    for(int k=0;k<gK->a;++k) {
      int p=0;
      for(int b=0;b<D->a;++b)
	for(int i=0;i<D->c;++i)
	  for(int j=0;j<D->d;++j,p++)
	    Dn->ptr2(p,k)=D->ptr[b]->ptr[k]->ptr2(i,j);
    }

    Res->ptr2=I->ptr2*Dn->ptr2;

    // Reshape to gradient
#ifdef USEOMP
#pragma omp parallel for
#endif
    for(int k=0;k<gK->a;++k) {
      int p=0;
      for(int z=0;z<gK->b;++z) {
	for(int i2=0;i2<gK->c;++i2)
	  for(int j2=0;j2<gK->d;++j2,p++)
	    gK->ptr[k]->ptr[z]->ptr2(i2,j2)=Res->ptr2(p,k);
      }
    }

    delete I;
    delete Dn;
    delete Res;
 
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

    for(z=zini;z<zfin;++z) {
      for(k=0;k<m->nk;++k)
	for(i2=0,r=0,c=0;i2<m->kc*m->kr;++i2,c++) {
	  if (c==m->kc) {c=0;r++;}
	  Kr->ptr[z]->ptr2(k,i2)=Kt->ptr[k]->ptr[z]->ptr2(r,c);
	}
    }

    if (m->rpad||m->cpad) {


      for(i=0;i<m->outr;++i) {
	for(j=0;j<m->outc;++j) {

	  for(b=bini;b<bfin;++b)
	    for(k=0;k<m->nk;++k)
	      Del->ptr2(b-bini,k)=Dt->ptr[b]->ptr[k]->ptr2(i,j);

	  for(z=zini;z<zfin;++z) {
	    Res->ptr2=Del->ptr2*Kr->ptr[z]->ptr2;

	    for(b=bini;b<bfin;++b) {
	      for(i2=0,r=0,c=0;i2<m->kc*m->kr;++i2,c++) {
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
      for(i=0;i<m->outr;++i) {
	for(j=0;j<m->outc;++j) {

	  for(b=bini;b<bfin;++b)
	    for(k=0;k<m->nk;++k)
	      Del->ptr2(b-bini,k)=Dt->ptr[b]->ptr[k]->ptr2(i,j);

	  for(z=zini;z<zfin;++z) {

	    Res->ptr2=Del->ptr2*Kr->ptr[z]->ptr2;

	    for(b=bini;b<bfin;++b) {
	      for(i2=0,r=0,c=0;i2<m->kc*m->kr;++i2,c++) {
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

void ConvolBDelta(Tensor *D, Tensor *K, Tensor *ID,int stride, int rpad,int cpad,int threads,int batch)
{
  if (useMT) {
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
      td[i].rpad=rpad;
      td[i].cpad=cpad;
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
  else {
    // LOWERING D K ID

    Tensor *Del=new Tensor(D->a,K->a);
    Tensor *Kr=new Tensor(K->b,K->a,K->c*K->d);
    Tensor *Res=new Tensor(K->a,K->c*K->d);

    int si,sj;
    int kr2=K->c/2;
    int kc2=K->d/2;
    int inr=ID->c;
    int inc=ID->d;
    
    if (!rpad) kr2=0;
    if (!cpad) kc2=0;

    for(int z=0;z<K->b;++z) {
      for(int k=0;k<K->a;++k)
	for(int i2=0,r=0,c=0;i2<K->c*K->d;++i2,c++) {
	  if (c==K->d) {c=0;r++;}
	  Kr->ptr[z]->ptr2(k,i2)=K->ptr[k]->ptr[z]->ptr2(r,c);
	}
    }
    
    for(int i=0;i<D->c;++i) {
      for(int j=0;j<D->d;++j) {

	for(int b=0;b<D->a;++b)
	  for(int k=0;k<K->a;++k)
	    Del->ptr2(b,k)=D->ptr[b]->ptr[k]->ptr2(i,j);

	for(int z=0;z<K->b;++z) {
	  Res->ptr2=Del->ptr2*Kr->ptr[z]->ptr2;

	  for(int b=0;b<D->a;++b) {
	    for(int i2=0,r=0,c=0;i2<K->c*K->d;++i2,c++) {
	      if (c==K->d) {c=0;r++;}
	      si=(i*stride+r)-kr2;
	      sj=(j*stride+c)-kc2;
	      if ((si<0)||(sj<0)||(si>=inr)||(sj>=inc)) { }
	      else ID->ptr[b]->ptr[z]->ptr2(si,sj)+=Res->ptr2(b,i2);
	    }
	  }

	}//z

      }//j
    }//i

    delete Del;
    delete Kr;
    delete Res;
  }

}

