#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <math.h>
#include <typeinfo>
#include <iostream>
#include <cstdlib>

#include "tensor.h"
#include "data.h"
#include "utils.h"
#include "Eigen/Dense"

using namespace Eigen;
using namespace std;


extern double gn[LUT];
extern double un[LUT];


Tensor * Tensor::AUX;


//// FOR CPU with Eigen
void Tensor::replace_unset()
{
  if (a==UNSET) a=1;
  if (b==UNSET) b=1;
  if (c==UNSET) c=1;
  if (d==UNSET) d=1;
}
/////

Tensor::Tensor() 
{
  dim=0;
  T=NULL;
}

Tensor::Tensor(int d1)
{
  dim=1;
  a=d1;
  replace_unset();  
  size=a;
  T=NULL;

  // CPU
  ptr1.resize(a);
}

Tensor::Tensor(int d1,int d2)
{
  dim=2;
  T=NULL;

  if ((d1!=UNSET)&&(d2==UNSET)) { // dim=2 but it0s a vector of 1D vectors with different sizes
    a=d1;
    b=d2;
    replace_unset();
    ptr=(Tensor **)malloc(a*sizeof(Tensor *));
    for(int i=0;i<a;i++)
      ptr[i]=new Tensor(b);
    size=a*b; // take care
  }
  else { // Regular Matrix
    a=d1;
    b=d2;
    replace_unset();
    size=a*b;
    //CPU
    ptr2.resize(a,b);
  }
}

Tensor::Tensor(int d1,int d2,int d3)
{
  dim=3;
  T=NULL;

  a=d1;
  b=d2;
  c=d3;
  replace_unset();
  size=a*b*c;


  //CPU
  ptr=(Tensor **)malloc(a*sizeof(Tensor *));
  for(int i=0;i<a;i++)
    ptr[i]=new Tensor(b,c);

}

Tensor::Tensor(int d1,int d2,int d3,int d4)
{
  dim=4;
  T=NULL;

  a=d1;
  b=d2;
  c=d3;
  d=d4;
  replace_unset();
  size=a*b*c*d;

  //CPU
  ptr=(Tensor **)malloc(a*sizeof(Tensor *));
  for(int i=0;i<a;i++)
    ptr[i]=new Tensor(b,c,d);
}


// Only for 4D Tensors
void Tensor::Transpose()
{
  if (dim==4) {
    if (T==NULL) 
      {
	T=new Tensor(b,a,c,d);
      }
  
    for(int i=0;i<a;i++)
      for(int j=0;j<b;j++)
	T->ptr[j]->ptr[i]->ptr2=ptr[i]->ptr[j]->ptr2;
  }
  else {
    fprintf(stderr,"Transpose oly for 4D Tensors\n");
    exit(1);
  }
}
  
/////
void Tensor::resize(int d1) 
{
  if (dim!=1) {
    fprintf(stderr,"Error resize tensor.dim=%d != call resize 1\n",dim);
    exit(1);
  }
  
  
  // CPU
  ptr1.resize(d1);
  a=d1;
  size=d1;
}

void Tensor::resize(int d1,int d2) {
  if (dim!=2) {
    fprintf(stderr,"Error resize tensor.dim=%d != call resize 2\n",dim);
    exit(1);
  }
  
  // CPU
  ptr2.resize(d1,d2);
  a=d1;
  b=d2;
  size=d1*d2;
}


//////////////////////////////////////////////////
// NO EMPLEADAS
/////////////////////////////////////////////////
void Tensor::resize(int d1,int d2,int d3) {
  if (dim!=3) {
    fprintf(stderr,"Error resize tensor.dim=%d != call resize 3\n",dim);
    exit(1);
  }
  // CPU
  for(int i=0;i<a;i++) {
    delete(ptr[i]);
  }
  delete ptr;
  ///////

  a=d1;
  b=d2;
  c=d3;
  size=a*b*c;

  // CPU
  ptr=(Tensor **)malloc(a*sizeof(Tensor *));
  for(int i=0;i<a;i++)
    ptr[i]=new Tensor(b,c);
}

void Tensor::resize(int d1,int d2,int d3,int d4) {
  if (dim!=4) {
    fprintf(stderr,"Error resize tensor.dim=%d != call resize 4\n",dim);
    exit(1);
  }

  // CPU
  for(int i=0;i<a;i++) {
    delete(ptr[i]);
  }
  delete ptr;
  ///////


  a=d1;
  b=d2;
  c=d3;
  d=d4;

  size=a*b*c*d;

  // CPU
  ptr=(Tensor **)malloc(a*sizeof(Tensor *));
  for(int i=0;i<a;i++)
    ptr[i]=new Tensor(b,c,d);
}
//////////////////////////////////////////////////


Tensor::~Tensor() 
{

  // CPU
  if (dim==1) ptr1.resize(0);
  else if (dim==2) ptr2.resize(0,0);
  else if (dim>2) {
    for(int i=0;i<a;i++) {
      delete ptr[i];
    }
    delete ptr;
  }
}


Tensor* Tensor::toLin()
{
  Tensor *n=new Tensor(size);
  
  // CPU
  if (dim==1) {
    n->ptr1=ptr1;
  }
  else if (dim==2) {    
#pragma omp parallel for
    for(int i=0;i<a;i++) {
      int p=i*b;
      for(int j=0;j<b;j++,p++)
	n->ptr1(p)=ptr2(i,j);
    }
  }
  else if (dim==3) {
#pragma omp parallel for
    for(int i=0;i<a;i++) {
      int p=i*b*c;
      for(int j=0;j<b;j++)
	for(int k=0;k<c;k++,p++)
	  n->ptr1(p)=ptr[i]->ptr2(j,k);
    }
  }
  else if (dim==4) {
#pragma omp parallel for
    for(int i=0;i<a;i++) {
      int p=i*b*c*d;
      for(int j=0;j<b;j++)
	for(int k=0;k<c;k++)
	  for(int l=0;l<d;l++,p++) 
	    n->ptr1(p)=ptr[i]->ptr[j]->ptr2(k,l);
    }
  }
  return n;
}

void Tensor::fromLin(Tensor *T)
{
  if (size!=T->size) {

    fprintf(stderr,"Error sizes fromLin %d!=%d\n",size,T->size);
    exit(1);
  }

  // CPU
  if (dim==1) {
    ptr1=T->ptr1;
  }
  else if (dim==2) {
    #pragma omp parallel for
    for(int i=0;i<a;i++) {
      int p=i*b;
      for(int j=0;j<b;j++,p++)
      {
	ptr2(i,j)=T->ptr1(p);  
      }
    }
  }
  else if (dim==3) {
   #pragma omp parallel for
    for(int i=0;i<a;i++) {
      int p=i*b*c;
      for(int j=0;j<b;j++)
	for(int k=0;k<c;k++,p++)
	  ptr[i]->ptr2(j,k)=T->ptr1(p);
    }
  }
  else if (dim==4) {
#pragma omp parallel for
    for(int i=0;i<a;i++) {
    int p=i*b*c*d;
      for(int j=0;j<b;j++)
	for(int k=0;k<c;k++)
	  for(int l=0;l<d;l++,p++)
	    ptr[i]->ptr[j]->ptr2(k,l)=T->ptr1(p);
    }
  }
}

int Tensor::equal(Tensor *T)
{
  if (size!=T->size) return 0;

  Tensor *n1=toLin();
  Tensor *n2=T->toLin();

  for(int i=0;i<size;i++) 
    if (n1->ptr1(i)!=n2->ptr1(i)) return 0;
  
  delete n1;
  delete n2;

  return 1;

}


Tensor * Tensor::subTensor(int ind)
{
  return ptr[ind];
}

Tensor * Tensor::subTensor(int a,int b)
{
  return ptr[a]->ptr[b];
}

void Tensor::copy(Tensor *T)  //copy, reshape etc...
{
  
  if (size!=T->size) {
    fprintf(stderr,"size mismatch copying tensors %d!=%d\n",size,T->size);
    exit(1);
  }

  /// CPU
  if (dim==T->dim) {
    if (T->dim==1) 
      ptr1=T->ptr1;
    if (T->dim==2)
      ptr2=T->ptr2;
    if (T->dim>2) {
      for(int i=0;i<a;i++)
	ptr[i]->copy(T->ptr[i]);
    }
  }
  else {
    if (VERBOSE) fprintf(stderr,"COPY dim! %d %d, %d %d\n",dim,T->dim,size,T->size);
    if (T->dim!=1) {
      Tensor *n=T->toLin();
      fromLin(n);
      delete n;
    }
    else {
      fromLin(T);
    }
  }
  ////////
}

void Tensor::copyfromData(Data *D)
{
  
  if (dim==2) {
    #pragma omp parallel for
    for(int i=0;i<a;i++) 
      for(int j=0;j<b;j++)
	ptr2(i,j)=D->M(D->getpos(i),j);
  }
  else if (dim==4) {
    #pragma omp parallel for
    for(int i=0;i<a;i++) {
      int p=0;
      for(int j=0;j<b;j++)
	for(int k=0;k<c;k++)
	  for(int l=0;l<d;l++,p++)
	    ptr[i]->ptr[j]->ptr2(k,l)=D->M(D->getpos(i),p);
    }
  }  

}

void Tensor::set(LType val)
{
  
  if (dim==1) {
#pragma omp parallel for
    for(int i=0;i<a;i++) ptr1(i)=val;
  }
  else if (dim==2) {
    #pragma omp parallel for
    for(int i=0;i<a;i++) 
      for(int j=0;j<b;j++) ptr2(i,j)=val;
  }
  else 
    for(int i=0;i<a;i++)
      ptr[i]->set(val);
}


void Tensor::set(int a,LType val)
{
  if (dim!=1) {
    fprintf(stderr,"Error set with 1 param for dim=%d\n",dim);
  }
  //CPU
  ptr1(a)=val;
}
void Tensor::set(int a,int b,LType val)
{
  if (dim!=2) {
    fprintf(stderr,"Error set with 2 params for dim=%d\n",dim);
  }
  //CPU
  ptr2(a,b)=val;
}


void Tensor::set(int a,int b,int c,LType val)
{
  if (dim!=3) {
    fprintf(stderr,"Error set with 3 params for dim=%d\n",dim);
  }
  //CPU
  ptr[a]->ptr2(b,c)=val;
}
void Tensor::set(int a,int b,int c,int d,LType val)
{
  if (dim!=4) {
    fprintf(stderr,"Error set with 4 params for dim=%d\n",dim);
  }

  //CPU
  ptr[a]->ptr[b]->ptr2(c,d)=val;
}

void Tensor::inc(int a,LType val)
{
  if (dim!=1) {
    fprintf(stderr,"Error set with 1 param for dim=%d\n",dim);
  }
  //CPU
  ptr1(a)+=val;
}
void Tensor::inc(int a,int b,LType val)
{
  if (dim!=2) {
    fprintf(stderr,"Error set with 2 params for dim=%d\n",dim);
  }
  //CPU
  ptr2(a,b)+=val;
}
void Tensor::inc(int a,int b,int c,LType val)
{
  if (dim!=3) {
    fprintf(stderr,"Error set with 3 params for dim=%d\n",dim);
  }
  //CPU
  ptr[a]->ptr2(b,c)+=val;
}
void Tensor::inc(int a,int b,int c,int d,LType val)
{
  if (dim!=4) {
    fprintf(stderr,"Error set with 4 params for dim=%d\n",dim);
  }

  //CPU
  #pragma omp parallel for
  for(int i=0;i<a;i++)
    ptr[a]->ptr[b]->ptr2(c,d)+=val;
}

void Tensor::set_rand_binary(LType val)
{
  Tensor *n=new Tensor(size);
  int s=rand()%LUT;
  //CPU
  for(int i=0;i<n->ptr1.size();i++) {
    int c=(s*i)%LUT;
    if (un[(c++)%LUT]>val) n->ptr1(i)=1;
    else n->ptr1(i)=0;
  }
  ////
  fromLin(n);
  delete n;
}

void Tensor::set_rand_signed_uniform(LType val)
{
  Tensor *n=new Tensor(size);

  //CPU
  for(int i=0;i<n->ptr1.size();i++) 
      n->ptr1(i)=val*suniform();
  ////

  fromLin(n);
  delete n;
}


void Tensor::set_rand_uniform(LType val)
{
  int i,j,k,l;

  Tensor *n=new Tensor(size);

  //CPU
  for(int i=0;i<n->ptr1.size();i++) 
    n->ptr1(i)=val*uniform();
  /////
  
  fromLin(n);
  delete n;
  
}
void Tensor::set_rand_gauss(LType m,LType sd)
{
  Tensor *n=new Tensor(size);

  //CPU
  for(int i=0;i<n->ptr1.size();i++) 
      n->ptr1(i)=gauss(m,sd);
  //////
  fromLin(n);
  delete n;
}

void Tensor::add_noise_gauss(LType noiser,LType mean,LType noisesd)
{
  Tensor *n=toLin();
  int s=rand();
  //CPU
  if (noiser==1) {
    if (mean==0.0) {
#pragma omp parallel for
      for(int i=0;i<n->ptr1.size();i++) {
	int c=(i*s)%LUT;
	n->ptr1(i)+=noisesd*gn[(c++)%LUT];
      }
    }
    else {
#pragma omp parallel for
      for(int i=0;i<n->ptr1.size();i++) {
	int c=(i*s)%LUT;
	n->ptr1(i)+=mean+noisesd*gn[(c++)%LUT];
      }
    }
  }
  else {
#pragma omp parallel for
    for(int i=0;i<n->ptr1.size();i++) {
      int c=(i*s)%LUT;
      if (un[(c++)%LUT]<noiser) 
	n->ptr1(i)+=mean+noisesd*gn[(c++)%LUT];
    }
  }
  //////                                                                                                    
  fromLin(n);

  delete n;
}

/////
LType Tensor::get(int a)
{
  if (dim!=1) {
    fprintf(stderr,"Error get with 1 param for dim=%d\n",dim);
  }
  //CPU
  return ptr1(a);
}
LType Tensor::get(int a,int b)
{
  if (dim!=2) {
    fprintf(stderr,"Error get with 2 params for dim=%d\n",dim);
  }
  //CPU
  return ptr2(a,b);
}
LType Tensor::get(int a,int b,int c)
{
  if (dim!=3) {
    fprintf(stderr,"Error get with 3 params for dim=%d\n",dim);
  }
  //CPU
  return ptr[a]->ptr2(b,c);
}
LType Tensor::get(int a,int b,int c,int d)
{
  if (dim!=4) {
    fprintf(stderr,"Error get with 4 params for dim=%d\n",dim);
  }
  //CPU
  return ptr[a]->ptr[b]->ptr2(c,d);
}


void Tensor::save(FILE *fs)
{
  if (dim==1) 
    for(int i=0;i<a;i++) 
      fprintf(fs,"%f ",ptr1(i));
  else if (dim==2) 
    for(int i=0;i<a;i++) 
      for(int j=0;j<b;j++)
	fprintf(fs,"%f ",ptr2(i,j));
  else
    for(int i=0;i<a;i++) 
      ptr[i]->save(fs);
  
}

void Tensor::load(FILE *fs)
{
  float fv;

  if (dim==1) 
    for(int i=0;i<a;i++) {
      fscanf(fs,"%f ",&fv);
      ptr1(i)=fv;
    }
  else if (dim==2) 
    for(int i=0;i<a;i++) 
      for(int j=0;j<b;j++) {
	fprintf(fs,"%f ",&fv);
	ptr2(i,j)=fv;
      }
  else
    for(int i=0;i<a;i++) 
      ptr[i]->save(fs);

}

LType Tensor::norm()
{
  LType n=0.0;

  if (dim==1) 
    for(int i=0;i<a;i++) n+=ptr1(i);
  else if (dim==2) {
    for(int i=0;i<a;i++) 
      for(int j=0;j<b;j++) n+=ptr2(i,j);
  }
  else {
    for(int i=0;i<a;i++) 
      n+=ptr[i]->norm();
  }

  return n;
}

LType Tensor::sum()
{
  if (dim==1) return ptr1.sum();
  else if (dim==2) return ptr2.sum();
  else {
    LType sum=0;
    for(int i=0;i<a;i++)
      sum+=ptr[i]->sum();

    return sum;
  }
}

////// TODO: 
// col_sum: devolver void y dejar resultado en algún sitio
LType Tensor::col_sum(int ind)
{
  return ptr2.col(ind).sum();
}

LType Tensor::row_sum(int ind)
{
  return ptr2.row(ind).sum();
}

LType Tensor::col_max(int ind,int *imax)
{
  return ptr2.col(ind).maxCoeff(imax);
}

LType Tensor::row_max(int ind,int *imax)
{
  return ptr2.row(ind).maxCoeff(imax);
}


void Tensor::inc_2Drowwise(Tensor *T)
{
  if ((dim!=2)||(T->dim!=1)) {
    fprintf(stderr,"inc_2Drowise is for 2D Tensor + 1D Tensor\n");
    exit(1);
  }
    
  //CPU
  ptr2.rowwise()+=T->ptr1;

}



/// STATIC FUNCS
///////////////////////////////////////
//// MULT C=(a*A)*(b*B)
//// Dimensions must fit
////
////      ONLY FOR >=2D TENSORS
////
//// tA,tB {0,1} to transpose A and B
//// inc {0,1} 
////           0: set the result in C
////           1: increment the result in C
///////////////////////////////////////
Tensor *Tensor::mult(Tensor *A, int tA, Tensor *B, int tB, Tensor *C, int inc)
{
  int aux=0;

  if (VERBOSE) {
    fprintf(stderr,"Tensor::mult %d %d %d %d %d\n",A->dim,B->dim,tA,tB,inc);
  }

  if (C==NULL) {
    if (VERBOSE) {fprintf(stderr,"NULL dest creating tmp\n");}
    if (AUX!=NULL) delete AUX;
    AUX=C=new Tensor();
  }
  
  if (A->dim==2) {
    if ((tA==0)&&(tB==0)&&(inc==0)) C->ptr2=A->ptr2*B->ptr2;
    if ((tA==0)&&(tB==0)&&(inc==1)) C->ptr2+=A->ptr2*B->ptr2;
    if ((tA==0)&&(tB==1)&&(inc==0)) C->ptr2=A->ptr2*B->ptr2.transpose();
    if ((tA==0)&&(tB==1)&&(inc==1)) C->ptr2+=A->ptr2*B->ptr2.transpose();

    if ((tA==1)&&(tB==0)&&(inc==0)) C->ptr2=A->ptr2.transpose()*B->ptr2;
    if ((tA==1)&&(tB==0)&&(inc==1)) C->ptr2+=A->ptr2.transpose()*B->ptr2;
    if ((tA==1)&&(tB==1)&&(inc==0)) C->ptr2=A->ptr2.transpose()*B->ptr2.transpose();
    if ((tA==1)&&(tB==1)&&(inc==1)) C->ptr2+=A->ptr2.transpose()*B->ptr2.transpose();
    C->dim=2;
  }
  else if (A->dim>2) {
    for(int i=0;i<A->a;i++) 
      Tensor::mult(A->subTensor(i),tA,B->subTensor(i),tB,C->subTensor(i),inc);
  }

  return C;
}


///////////////////////////////////////////////
//// B=sc*A
////
//// ANY D
////
//// inc {0,1} 
////           0: set the result in B
////           1: increment the result in B
///////////////////////////////////////////////
Tensor * Tensor::sc_mult(Tensor *A, LType sc, Tensor *B, int inc)
{
  if (A->dim==1) {
    if (inc) B->ptr1+=sc*A->ptr1;
    else B->ptr1=sc*A->ptr1;
  }
  else if (A->dim==2) {
    if (inc) B->ptr2+=sc*A->ptr2;
    else B->ptr2=sc*A->ptr2;
  }
  else {
    for(int i=0;i<A->a;i++)
      Tensor::sc_mult(A->ptr[i],sc,B->ptr[i],inc);
  }

  return B;
}

///////////////////////////////////////////////
//// C=A*.B  (element wise product)
////
//// ANY D
////
//// tA,tB {0,1} to transpose A and B
//// inc {0,1} 
////           0: set the result in C
////           1: increment the result in C
///////////////////////////////////////////////
Tensor * Tensor::el_mult(Tensor *A, int tA, Tensor *B, int tB, Tensor *C, int inc)
{
  if (C==NULL) {
    if (AUX!=NULL) delete AUX;
    AUX=C=new Tensor();
  }

  if (A->dim==1) {
    if ((tA==0)&&(tB==0)&&(inc==0)) C->ptr1=A->ptr1.cwiseProduct(B->ptr1);
    if ((tA==0)&&(tB==0)&&(inc==1)) C->ptr1+=A->ptr1.cwiseProduct(B->ptr1);
    if ((tA==0)&&(tB==1)&&(inc==0)) C->ptr1=A->ptr1.cwiseProduct(B->ptr1.transpose());
    if ((tA==0)&&(tB==1)&&(inc==1)) C->ptr1+=A->ptr1.cwiseProduct(B->ptr1.transpose());

    if ((tA==1)&&(tB==0)&&(inc==0)) C->ptr1=A->ptr1.transpose().cwiseProduct(B->ptr1);
    if ((tA==1)&&(tB==0)&&(inc==1)) C->ptr1+=A->ptr1.transpose().cwiseProduct(B->ptr1);
    if ((tA==1)&&(tB==1)&&(inc==0)) C->ptr1=A->ptr1.transpose().cwiseProduct(B->ptr1.transpose());
    if ((tA==1)&&(tB==1)&&(inc==1)) C->ptr1+=A->ptr1.transpose().cwiseProduct(B->ptr1.transpose());
  }
  else if (A->dim==2) {
    if ((tA==0)&&(tB==0)&&(inc==0)) C->ptr2=A->ptr2.cwiseProduct(B->ptr2);
    if ((tA==0)&&(tB==0)&&(inc==1)) C->ptr2+=A->ptr2.cwiseProduct(B->ptr2);
    if ((tA==0)&&(tB==1)&&(inc==0)) C->ptr2=A->ptr2.cwiseProduct(B->ptr2.transpose());
    if ((tA==0)&&(tB==1)&&(inc==1)) C->ptr2+=A->ptr2.cwiseProduct(B->ptr2.transpose());

    if ((tA==1)&&(tB==0)&&(inc==0)) C->ptr2=A->ptr2.transpose().cwiseProduct(B->ptr2);
    if ((tA==1)&&(tB==0)&&(inc==1)) C->ptr2+=A->ptr2.transpose().cwiseProduct(B->ptr2);
    if ((tA==1)&&(tB==1)&&(inc==0)) C->ptr2=A->ptr2.transpose().cwiseProduct(B->ptr2.transpose());
    if ((tA==1)&&(tB==1)&&(inc==1)) C->ptr2+=A->ptr2.transpose().cwiseProduct(B->ptr2.transpose());
  }
  else {
    for(int i=0;i<A->a;i++)
      Tensor::el_mult(A->ptr[i],tA,B->ptr[i],tB,C->ptr[i],inc);
  }
  return C;
}

///////////////////////////////////////////////
//// C=A*B  (outter product of vectors)
////
//// 2D normally batchxvectors
//// inc --> C+=A*B
///////////////////////////////////////////////
Tensor * Tensor::out_mult(Tensor *A, Tensor *B, Tensor *C, int inc)
{
  if (C==NULL) {
    if (AUX!=NULL) delete AUX;
    AUX=C=new Tensor();
  }
  
  for(int i=0;i<A->a;i++) {
    LMatrix Res=A->ptr2.row(i).transpose()*B->ptr2.row(i);
    Map<RowVectorXf> v(Res.data(), Res.size());
    C->ptr2.row(i)=v;
  }
  
  return C;
}


 ///////////////////////////////////////////////                                                          
 //// C=A+B 
 ////                                                                                                     
 //// ANY D                                                                                               
 ////                  
 //// sca,scb escalars                                                                                   
 //// tA,tB {0,1} to transpose A and B                                                                    
 //// inc {0,1}                                                                                           
 ////           0: set the result in C                                                                   
 ////           1: increment the result in C                                                               
 ///////////////////////////////////////////////           
 Tensor * Tensor::sum(LType sca,Tensor *A, int tA, LType scb,Tensor *B, int tB, Tensor *C, int inc)

{
   if (C==NULL) {
    if (AUX!=NULL) delete AUX;
    if (A->dim<3) AUX=C=new Tensor();
    else {
      if (A->dim==3) C=new Tensor(A->a,A->b,A->c);
      if (A->dim==4) C=new Tensor(A->a,A->b,A->c,A->d);
    }
  }

  if (A->dim==1) {
    if ((tA==0)&&(tB==0)&&(inc==0)) C->ptr1=(sca*A->ptr1)+(scb*B->ptr1);
    if ((tA==0)&&(tB==0)&&(inc==1)) C->ptr1+=(sca*A->ptr1)+(scb*B->ptr1);
    if ((tA==0)&&(tB==1)&&(inc==0)) C->ptr1=(sca*A->ptr1)+(scb*B->ptr1.transpose());
    if ((tA==0)&&(tB==1)&&(inc==1)) C->ptr1+=(sca*A->ptr1)+(scb*B->ptr1.transpose());

    if ((tA==1)&&(tB==0)&&(inc==0)) C->ptr1=(sca*A->ptr1.transpose())+(scb*B->ptr1);
    if ((tA==1)&&(tB==0)&&(inc==1)) C->ptr1+=(sca*A->ptr1.transpose())+(scb*B->ptr1);
    if ((tA==1)&&(tB==1)&&(inc==0)) C->ptr1=(sca*A->ptr1.transpose())+(scb*B->ptr1.transpose());
    if ((tA==1)&&(tB==1)&&(inc==1)) C->ptr1+=(sca*A->ptr1.transpose())+(scb*B->ptr1.transpose());
  }
  else  if (A->dim==2) {
    if ((tA==0)&&(tB==0)&&(inc==0)) C->ptr2=(sca*A->ptr2)+(scb*B->ptr2);
    if ((tA==0)&&(tB==0)&&(inc==1)) C->ptr2+=(sca*A->ptr2)+(scb*B->ptr2);
    if ((tA==0)&&(tB==1)&&(inc==0)) C->ptr2=(sca*A->ptr2)+(scb*B->ptr2.transpose());
    if ((tA==0)&&(tB==1)&&(inc==1)) C->ptr2+=(sca*A->ptr2)+(scb*B->ptr2.transpose());

    if ((tA==1)&&(tB==0)&&(inc==0)) C->ptr2=(sca*A->ptr2.transpose())+(scb*B->ptr2);
    if ((tA==1)&&(tB==0)&&(inc==1)) C->ptr2+=(sca*A->ptr2.transpose())+(scb*B->ptr2);
    if ((tA==1)&&(tB==1)&&(inc==0)) C->ptr2=(sca*A->ptr2.transpose())+(scb*B->ptr2.transpose());
    if ((tA==1)&&(tB==1)&&(inc==1)) C->ptr2+=(sca*A->ptr2.transpose())+(scb*B->ptr2.transpose());
  }
  else {
    for(int i=0;i<A->a;i++)
      Tensor::sum(sca,A->ptr[i], tA, scb,B->ptr[i],tB, C->ptr[i],inc);

  }

  return C;
}

 ///////////////////////////////////////////////                                                          
 //// C+=A 
 ////                                                                                                     
 //// ANY D                                                                                               
 ///////////////////////////////////////////////           
 Tensor * Tensor::inc(Tensor *A, Tensor *C)
{
  if (C==NULL) {
    if (AUX!=NULL) delete AUX;
    if (A->dim<3) AUX=C=new Tensor();
    else {
      if (A->dim==3) AUX=C=new Tensor(A->a,A->b,A->c);
      if (A->dim==4) AUX=C=new Tensor(A->a,A->b,A->c,A->d);
    }
  }

  if (A->dim==1) C->ptr1+=A->ptr1;
  else  if (A->dim==2) C->ptr2+=A->ptr2;
  else {
    for(int i=0;i<A->a;i++)
      Tensor::inc(A->ptr[i],C->ptr[i]);
  }

  return C;
}


///////////////////////////////////////////////
//// B=sc+A (element wise sum of sc)
////
//// ANY D
////
//// inc {0,1} 
////           0: set the result in B
////           1: increment the result in B
///////////////////////////////////////////////
Tensor * Tensor::sc_sum(Tensor *A, LType sc,Tensor *B,int inc) 
{
  if (A->dim==1) {
    for (int i=0;i<B->a;i++)
      if (inc)
	B->ptr1(i)+=sc+A->ptr2(i);
      else
	B->ptr1(i)=sc+A->ptr2(i);
  }
  else if (A->dim==2) {
    for (int i=0;i<B->a;i++)
      for(int j=0;j<B->b;j++)
	if (inc) B->ptr2(i,j)+=sc+A->ptr2(i,j);
	else B->ptr2(i,j)=sc+A->ptr2(i,j);
  }
  else {
    for(int i=0;i<A->a;i++)
      Tensor::sc_sum(A->ptr[i], sc, B->ptr[i],inc);
  }

  return B;
}
 



void Tensor::activation(Tensor *E,Tensor *N,int act)
{ 

  //CPU
  if (E->dim==2) {
    if (act==ACT_LIN) N->ptr2=E->ptr2;
    else if (act==ACT_RLU) ReLu(E->ptr2,N->ptr2);
    else if (act==ACT_SIG) Sigmoid(E->ptr2,N->ptr2);
    else if (act==ACT_ELU) ELU(E->ptr2,N->ptr2,1.0);
    else if (act==ACT_SOF) Softmax(E->ptr2,N->ptr2);
    else {
      fprintf(stderr,"Wrong activation function\n");
      exit(1);
    }
  }
  /////
  if (E->dim>2) {
    for(int i=0;i<E->a;i++) 
      Tensor::activation(E->ptr[i],N->ptr[i],act);
  }
}

void Tensor::info()
{
  fprintf(stderr,"Tensor %dD ",dim);
  if (dim==1) fprintf(stderr,"%d\n",a);
  if (dim==2) fprintf(stderr,"%dx%d\n",a,b);
  if (dim==3) fprintf(stderr,"%dx%dx%d\n",a,b,c);
  if (dim==4) fprintf(stderr,"%dx%dx%dx%d\n",a,b,c,d);

}
void Tensor::print()
{
  if (dim==2) {
    for(int i=0;i<a;i++) {
      for(int j=0;j<b;j++)
	fprintf(stderr,"%1.3f ",ptr2(i,j));
      fprintf(stderr,"\n");
    }
  }
  else if (dim==3) {
    for(int i=0;i<a;i++) {
      fprintf(stderr,"==== 3(%d) ====\n",i);
      ptr[i]->print();
    }
  }
  else if (dim==4) {
    for(int i=0;i<a;i++) {
      fprintf(stderr,"==== 4(%d) ====\n",i);
      ptr[i]->print();
    }
  }
}
void Tensor::dactivation(Tensor *E,Tensor *N, Tensor *D, int act) 
{
  //E->print();
  if (E->dim==2) {
  for(int i=0;i<E->a;i++)
    for(int j=0;j<E->b;j++)
      if (act==ACT_LIN) 
	D->ptr2(i,j)=1;
      else if (act==ACT_RLU) {
	if (E->ptr2(i,j)<=0) D->ptr2(i,j)=0;
	else D->ptr2(i,j)=1.0;
      }
      else if (act==ACT_SIG)  {
	D->ptr2(i,j)=dsigm(E->ptr2(i,j));
      }
      else if (act==ACT_ELU)  {
	if (E->ptr2(i,j)<=0) D->ptr2(i,j)=N->ptr2(i,j)+1;
      }
  }
  else if (E->dim>2) {
    for(int i=0;i<E->a;i++)
      Tensor::dactivation(E->ptr[i],N->ptr[i],D->ptr[i],act);
  }
  //D->print();
}


void Tensor::maskZeros(Tensor *mask,Tensor *A)
{
  if (A->dim==1) 
      A->ptr1=mask->ptr1.cwiseProduct(A->ptr1);
  if (A->dim==2)  
      A->ptr2=A->ptr2.array().rowwise()*mask->ptr1.array();
  else {
    for(int i=0;i<A->a;i++)
      Tensor::maskZeros(mask->ptr[i],A->ptr[i]);
  }
}





//////////// HASTA AQUI GPU ////////////////////////




///////////////////////////////////////////////
//// Convolution of 2D Tensors:
//// 
//// A is a 2D tensor, normally an image
//// K is a 2D tensor, normally a filter
//// B is a 2D tensor, normally an image
///////////////////////////////////////////////
void Tensor::Convol2D(Tensor *A,Tensor *K,Tensor *B,int inc,int stride,int pad)
{
  for(int i=0;i<B->a;i++) {
      int ar=(i*stride)-pad;
      for(int j=0;j<B->b;j++) {
	int ac=(j*stride)-pad;
	LType sum=0;
	for(int r=0;r<K->a;r++)
	  for(int c=0;c<K->b;c++)
	    if ((ar+r>=0)&&(ar+r<A->a)&&(ac+c>=0)&&(ac+c<A->b))
	      sum+=K->ptr2(r,c)*A->ptr2(ar+r,ac+c);

	if (inc) 
	  B->ptr2(i,j)+=sum;
	else
	  B->ptr2(i,j)=sum;
      }
    }

}


///////////////////////////////////////////////
//// Convolution of 2D Transpose Tensors:
//// 
//// A is a 2D tensor, normally an image
//// K is a 2D tensor, normally a filter
//// B is a 2D tensor, normally and image
///////////////////////////////////////////////
void Tensor::Convol2DT(Tensor *A,Tensor *K,Tensor *B,int inc,int stride,int pad)
{
  if (inc) {
    for(int i=0;i<K->a;i++)
      for(int j=0;j<K->b;j++) {
	LType sc=K->ptr2(i,j);
	for(int r=0;r<A->a;r++)
	  for(int c=0;c<A->b;c++)
	    B->ptr2(r+i,c+j)+=sc*A->ptr2(r,c);
      }
  }
  else {
    for(int i=0;i<K->a;i++)
      for(int j=0;j<K->b;j++) {
	LType sc=K->ptr2(i,j);
	for(int r=0;r<A->a;r++)
	  for(int c=0;c<A->b;c++)
	    B->ptr2(r+i,c+j)=sc*A->ptr2(r,c);
      }
  }
}

///////////////////////////////////////////////
//// Convolution of 3D Tensors:
//// 
//// A is a 3D tensor, normally depth x image
//// K is a 3D tensor, normally depth x filter
//// B is a 2D tensor, normally and image
///////////////////////////////////////////////
void Tensor::Convol3D(Tensor *A,Tensor *K,Tensor *B,int stride,int pad)
{
  for(int i=0;i<A->a; i++)
    Tensor::Convol2D(A->subTensor(i),K->subTensor(i),B,1,stride,pad);
}


///////////////////////////////////////////////
//// Convolution of 4D Tensors:
//// 
//// A is a 4D tensor, normally:
////    batch x depth x images (rows x cols)
//// K is a 4D tensor, normally:
////    numfilters x depth x filterimage (rows x cols)
//// B is a 4D tensor, normally:
////     batch x depth_out x images (rows x cols) 
////     where depth_out=K numfilters
///////////////////////////////////////////////
void Tensor::Convol(Tensor *A,Tensor *K,int tK,Tensor *B,int tr,int stride, int pad)
{

  B->set(0.0);
  if (!tK) {
    if (!tr) {
  #pragma omp parallel for
      for(int i=0;i<B->a;i++)
	for(int j=0;j<B->b;j++)
	  Tensor::Convol3D(A->subTensor(i),K->subTensor(j),B->subTensor(i,j),stride,pad);
    }
    else {
      A->Transpose(); 
      K->Transpose(); 
  #pragma omp parallel for
      for(int i=0;i<B->a;i++) 
	for(int j=0;j<B->b;j++) 
	  Tensor::Convol3D(A->T->subTensor(j),K->T->subTensor(i),B->subTensor(i,j),stride,pad);
    }
  }
  else {
#pragma omp parallel for
    for(int i=0;i<A->a;i++)//batch
      for(int j=0;j<A->b;j++)//nk
	for(int k=0;k<B->b;k++)//depth
	  Tensor::Convol2DT(A->subTensor(i,j),K->subTensor(j,k),B->subTensor(i,k),1,stride,pad);
  }
}




// FOR BN

void Tensor::forwardBN_training(int batch,Tensor *E,Tensor *bn_mean,Tensor *bn_var,Tensor *bn_E,Tensor *bn_g,Tensor *bn_b,Tensor *BNE,Tensor *bn_gmean,Tensor *bn_gvar,int bnc,int noiser,LType noisesd) 
{
  
  //CPU
#pragma omp parallel for
  for(int i=0;i<E->b;i++) {
    int b;
    double m,var,eps=0.00001;
    int cn=(i*bnc%LUT);
    m=0;
    for(b=0;b<batch;b++)
      m+=E->ptr2(b,i);
    m/=batch;
    bn_mean->ptr1(i)=m;

    var=0;
    for(b=0;b<batch;b++)
      var+=(m-E->ptr2(b,i))*(m-E->ptr2(b,i));
    var/=batch;
    bn_var->ptr1(i)=var;

    for(b=0;b<batch;b++) {
      bn_E->ptr2(b,i)=(E->ptr2(b,i)-bn_mean->ptr1(i))/sqrt(bn_var->ptr1(i)+eps); //this is \hat{x}
      if (noiser>0.0) {
	if (noiser>=un[(cn++)%LUT])
	  bn_E->ptr2(b,i)+=noisesd*gn[(cn++)%LUT];
      }
      BNE->ptr2(b,i)=(bn_g->ptr1(i)*bn_E->ptr2(b,i))+bn_b->ptr1(i);
    }
  }
  bn_gmean->ptr1+=bn_mean->ptr1;
  bn_gvar->ptr1+=bn_var->ptr1;
}

void Tensor::forwardBN_inference(int batch,Tensor *E,Tensor *bn_gmean,Tensor *bn_gvar,Tensor *bn_E,Tensor *bn_g,Tensor *bn_b,Tensor *BNE,int bnc) 
{
  //CPU
  for(int i=0;i<E->b;i++) {
    int b;
    double var,eps=0.00001;

    for(b=0;b<batch;b++){
      bn_E->ptr2(b,i)=(E->ptr2(b,i)-bn_gmean->ptr1(i)/bnc)/sqrt(bn_gvar->ptr1(i)/bnc+eps);
      BNE->ptr2(b,i)=(bn_g->ptr1(i)*bn_E->ptr2(b,i))+bn_b->ptr1(i);
    }
  }
}

void Tensor::backwardBN(int batch,
			Tensor *E,
			Tensor *bn_E,
			Tensor *bn_g,
			Tensor *bn_mean,
			Tensor *bn_var,
			Tensor *Delta,
			Tensor *gbn_g,
			Tensor *gbn_b,
			Tensor *gbn_E,
			Tensor *gbn_mean,
			Tensor *gbn_var
			)
{
  int i;
#pragma omp parallel for
  for(int i=0;i<bn_E->b;i++) {
    int b;
    double m,var,eps=0.00001;
    double sqvar,var32;

    m=batch;

    //1 Gamma
    gbn_g->set(i,0.0);
    for(b=0;b<batch;b++)
      gbn_g->set(i,Delta->get(b,i)*bn_E->get(b,i));

    //2 Beta
    gbn_b->set(i,0.0);
    for(b=0;b<batch;b++)
      gbn_b->inc(i,Delta->get(b,i));


    //3 bnE
    for(b=0;b<batch;b++)
      gbn_E->set(b,i,Delta->get(b,i)*bn_g->get(i));


    //4 Var
    sqvar=sqrt(bn_var->get(i)+eps);
    var32=(bn_var->get(i)+eps)*sqvar;

    gbn_var->set(i,0);
    for(b=0;b<batch;b++)
      gbn_var->inc(i,-0.5*gbn_E->get(b,i)*(E->get(b,i)-bn_mean->get(i))/var32);


    //5 Mean
    gbn_mean->set(i,0);
    for(b=0;b<batch;b++) {
      gbn_mean->inc(i,-gbn_E->get(b,i)/sqvar);
      //gbn_mean(i)+=-2*gbn_var(i)*(E(b,i)-bn_mean(i))/m;
    }

    //6 x
    for(b=0;b<batch;b++) {
      Delta->set(b,i,gbn_E->get(b,i)/sqvar);
      Delta->inc(b,i,gbn_var->get(i)*2*(E->get(b,i)-bn_mean->get(i))/m);
      Delta->inc(b,i,gbn_mean->get(i)/m);
    }
  }

}

