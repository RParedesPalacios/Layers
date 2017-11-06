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

#ifdef fGPU
#include "./gpu/execution.h"
// Data structures variables and functions for GPU computation setup
#endif


using namespace Eigen;
using namespace std;

extern double gn[LUT];
extern double un[LUT];


//GLOBAL,EXTERN VARIABLES DIRECTIVES INCLUDES FOR GPU COMPUTATION

extern int useCPU;

void msgerr(const char *s1,const char *s2) {
  fprintf(stderr,"%s\n",s1);
  fprintf(stderr,"%s\n",s2);
  exit(1);
}

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
  lin=NULL;
  T=NULL;
}

//JUAN: implemented
Tensor::Tensor(int d1)
{
  dim=1;
  a=d1;
  replace_unset();  
  size=a;
  T=NULL;

  // CPU
  if(useCPU) 
    ptr1.resize(a);
  #ifdef fGPU
  else
  {
   if (a!=1)
   {	
     gptr=gpu_tensor_op.makeTensor(a);
     gsp.row=1;gsp.col=a;gsp.batch=1;gsp.featureMap=1;	
   }
  }
 #endif
}

//JUAN: implemented
Tensor::Tensor(int d1,int d2)
{
  dim=2;
  T=NULL;

  if ((d1!=UNSET)&&(d2==UNSET)) { // matrix but a vectors of 1D vectors with different sizes

    a=d1;
    b=d2;
    replace_unset();
    ptr=(Tensor **)malloc(a*sizeof(Tensor *));
    for(int i=0;i<a;i++)
      ptr[i]=new Tensor(b);
    size=a*b; // take care
  }
  else { // Matrix
    a=d1;
    b=d2;
    replace_unset();
    size=a*b;
  //CPU
  if(useCPU)
    ptr2.resize(a,b);
 #ifdef fGPU
  else
  {
    if(a!=1 && b!=1) //as we cannot realloc memory on gpu we just alloc only if a!=1 and b!=1. We do allocation on resize methods
    {	
      gptr=gpu_tensor_op.makeTensor(a,b);
      gsp.row=a;gsp.col=b;gsp.batch=1;gsp.featureMap=1;	
    }
  }
 #endif
  }
}
//JUAN:  implemented
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

//Juan: Not implemented for the moment
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

// Cloning                                                                           
Tensor * Tensor::Clone()
{
  Tensor *N;

  if (dim==1) N=new Tensor(a);
  else if (dim==2) N=new Tensor(a,b);
  else if (dim==3) N=new Tensor(a,b,c);
  else N=new Tensor(a,b,c,d);

  N->copy(this);

  return N;
}


/////
// Only for 4D Tensors
//Juan: Not implemented for the moment
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
  if(useCPU)
  {
    ptr1.resize(d1);
    a=d1;
    size=d1;
  }
 #ifdef fGPU
  else
  {
     a=d1;
     size=d1;	
     gptr=gpu_tensor_op.makeTensor(a);
     gsp.row=1;gsp.col=a;gsp.batch=1;gsp.featureMap=1;	
  }
 #endif
}

void Tensor::resize(int d1,int d2) {
  if (dim!=2) {
    fprintf(stderr,"Error resize tensor.dim=%d != call resize 2\n",dim);
    exit(1);
  }
  // CPU
  if(useCPU)
  {
    ptr2.resize(d1,d2);
    a=d1;
    b=d2;
    size=d1*d2;
  }
  #ifdef fGPU
  else
  {
   a=d1;
   b=d2;	
   size=a*b;
   gptr=gpu_tensor_op.makeTensor(a,b);
   gsp.row=a;gsp.col=b;gsp.batch=1;gsp.featureMap=1;	 
  }
 #endif

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
    fprintf(stderr,"Error resize tensor.dim=%d != call resize 4sssssssss\n",dim);
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

//JUAN: Implemented
Tensor::~Tensor() 
{

  // CPU
  if(useCPU)
  {
    if (dim==1) ptr1.resize(0);
    else if (dim==2) ptr2.resize(0,0);
    else if (dim>2) {
      for(int i=0;i<a;i++) {
        delete ptr[i];
      }
    delete ptr;
    }
  }
  #ifdef fGPU
  else
  {
    gpu_tensor_op.destroyTensor(this->gptr);
  }
  #endif
}

//Juan: GPU not use this
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

//Juan: GPU not use this
void Tensor::fromLin(Tensor *T)
{
  // CPU
  if(useCPU)
  {
  if (dim==1) {
    ptr1=T->ptr1;
  }
  else if (dim==2) {
#pragma omp parallel for
    for(int i=0;i<a;i++) {
      int p=i*b;
      for(int j=0;j<b;j++,p++)
	ptr2(i,j)=T->ptr1(p);
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
   #ifdef fGPU
  else
	{fprintf(stderr,"Not implemented from LIn\n");exit(-1);}
  #endif

}
//Juan: Implemented
int Tensor::equal(Tensor *T)
{
  if (size!=T->size) return 0;

  if(useCPU)
  {
    Tensor *n1=toLin();
    Tensor *n2=T->toLin();

    for(int i=0;i<size;i++) 
      if (n1->ptr1(i)!=n2->ptr1(i)) return 0;
  
    delete n1;
    delete n2;
  }
  #ifdef fGPU
  else
    return gpu_tensor_op.tensor_equal(T->gptr,gptr,&gsp);
  #endif

  return 1;

}

//Juan: Implemented. Subtensor is for tensor 3D. Tensor 3D keep tensor array. Each element of array is tensor 2D which has GPU support
Tensor * Tensor::subTensor(int ind)
{
    return ptr[ind];
}

//Juan: Not implemented
Tensor * Tensor::subTensor(int a,int b)
{
  if(useCPU)
     return ptr[a]->ptr[b];
  #ifdef fGPU
  else
  {
  fprintf(stderr,"Not implementet subtensor 2D\n");exit(-1);
  }

  #endif
}

void Tensor::copy(Tensor *T)  //copy, reshape etc...
{
  
  if (size!=T->size) {
    fprintf(stderr,"size mismatch copying tensors %d!=%d\n",size,T->size);
    exit(1);
  }

  /// CPU
  if (useCPU)
  {
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
      if (VERBOSE) fprintf(stderr,"COPY dim!\n");
    Tensor *n=T->toLin();
    fromLin(n);
    delete n;
    }
  }
  #ifdef fGPU
  else
  {
  fprintf(stderr,"Imlementear copy\n");exit(-1);
  }
  #endif
  
  ////////
}

//Juan: Not implemented
void Tensor::copylabels(Data *D)
{
  if (dim!=2) msgerr("copylabels","Labels only copy to 2D Tensors");

  if(useCPU) {
#pragma omp parallel for
    for(int i=0;i<a;i++)
      for(int j=0;j<b;j++)
	ptr2(i,j)=D->M(D->getpos(i),j+D->dim);
    
  }
#ifdef fGPU
  else
    {
      float* data_aux;
      float* batch_aux= new float[b];
      size_t counter=0;
      data_aux = (float*)malloc(a*b*sizeof(float));
      
      for (int i=0;i<a;i++)
	{
	  for(int j=0;j<b;j++)
	    batch_aux[j]=D->M(D->getpos(i),j+D->dim);
	  memcpy((void*)data_aux+counter,batch_aux,b*sizeof(float));
	  counter+=b*sizeof(float);
	}
	
      gpu_tensor_op.copy_data(data_aux,gptr,TOGPU,a*b*sizeof(float));
      free(data_aux);
      delete batch_aux;
    }
#endif
}
void Tensor::copyfromData(Data *D)
{
 if(useCPU)
 {
   //a_batch 
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
 #ifdef fGPU
 else
 {
  float* data_aux;
  float* batch_aux= new float[b];
    if (dim==2)
    { 
      size_t counter=0;
      data_aux = (float*)malloc(a*b*sizeof(float));
  

      for (int i=0;i<a;i++)
      {
        for(int j=0;j<b;j++)
        	batch_aux[j]=D->M(D->getpos(i),j);
        memcpy((void*)data_aux+counter,batch_aux,b*sizeof(float));
        counter+=b*sizeof(float);
      }

      }
    gpu_tensor_op.copy_data(data_aux,gptr,TOGPU,a*b*sizeof(float));
    free(data_aux);
    delete batch_aux;
  }
 #endif
}
//
void Tensor::copyStatistics(Data *D,int tipe)
{
  if (dim!=1) msgerr("copyStatistics","Statistics only copy to 1D tensor");

#ifdef fGPU
      float* data_aux;
      float* batch_aux= new float[a];
      size_t counter=0;
      data_aux = (float*)malloc(a*sizeof(float));
      if (tipe==1)//std
      {
	  for(int j=0;j<a;j++)
	    batch_aux[j]=D->fsd[j+D->dim],j+D->dim;
          
	  memcpy((void*)data_aux+counter,batch_aux,a*sizeof(float));
	  counter+=a*sizeof(float);
      }
      else if (tipe==2)	//mean
      {
	  for(int j=0;j<a;j++)
	    batch_aux[j]=D->fmu[j+D->dim],j+D->dim;
          
	  memcpy((void*)data_aux+counter,batch_aux,a*sizeof(float));
	  counter+=a*sizeof(float);
      }

      gpu_tensor_op.copy_data(data_aux,gptr,TOGPU,a*sizeof(float));
      free(data_aux);
      delete batch_aux;
#endif
}



//Juan:: Implemented
void Tensor::set(LType val)
{
 if(useCPU)
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
 #ifdef fGPU
 else
   if (dim==1 || dim==2)
   {
       gpu_tensor_op.set_sc(gptr,val,&gsp);
   }
   else
   {
      //#pragma omp parallel for
      for(int i=0;i<a;i++)
      {
         printf("%d of %d",i,a);
         ptr[i]->set(val); 
      }
   }
 #endif 
}

//Juan: implemented
void Tensor::set(int a,LType val)
{
  if(useCPU)
  {
    if (dim!=1) {
      fprintf(stderr,"Error set with 1 param for dim=%d\n",dim);
    }
    //CPU
    ptr1(a)=val;
  }
  #ifdef fGPU
  else
  {
  gpu_tensor_op.copy_data(&val,&(gptr[a]),TOGPU,sizeof(float));
  }
  #endif
  
}


//Juan: implemented
void Tensor::inc(int a,LType val)
{
  if(useCPU)
  {
    if (dim!=1) {
      fprintf(stderr,"Error set with 1 param for dim=%d\n",dim);
    }
    //CPU
    ptr1(a)+=val;
  }
  #ifdef fGPU
  else
  {

  }
  #endif
  
}
//Juan: implemented
void Tensor::set(int a,int b,LType val)
{
  if (useCPU)
  {
    if (dim!=2) {
      fprintf(stderr,"Error set with 2 params for dim=%d\n",dim);
    }
    //CPU
    ptr2(a,b)=val;
  }
   #ifdef fGPU
  else
  {
   gpu_tensor_op.copy_data(&val,&(gptr[a*this->b+b]),TOGPU,sizeof(float));
  }
  #endif
  
 
}

//Juan: implemented
void Tensor::inc(int a,int b,LType val)
{
  if (useCPU)
  {
    if (dim!=2) {
      fprintf(stderr,"Error set with 2 params for dim=%d\n",dim);
    }
    //CPU
    ptr2(a,b)+=val;
  }
   #ifdef fGPU
  else
  {
 
  }
  #endif
  
 
}

//Juan: Not implemented
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



/////////////RANDOM FOR THE MOMENTO NO IMPLEMNTED WE NEED TO STUDY CURAND API//////////////////////////
//Juan: Implemented
void Tensor::set_rand_binary(LType val)
{
  if(useCPU)
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
  #ifdef fGPU
  else
  {
   gpu_tensor_op.random_number_host_binary(gptr,&gsp,val);
  }
  #endif
  
}

void Tensor::set_rand_signed_uniform(LType val)
{
  if(useCPU)
  {
  Tensor *n=new Tensor(size);

  //CPU
  for(int i=0;i<n->ptr1.size();i++) 
      n->ptr1(i)=val*suniform();
  ////

  fromLin(n);
  delete n;
  }
}


void Tensor::set_rand_uniform(LType val)
{
  if(useCPU)
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
}
//Juan: Implemented
void Tensor::set_rand_gauss(LType m,LType sd)
{
  if(useCPU)
  {
  Tensor *n=new Tensor(size);

  //CPU
  for(int i=0;i<n->ptr1.size();i++) 
      n->ptr1(i)=gauss(m,sd);
  //////

  fromLin(n);
  delete n;
  }
  #ifdef fGPU
  else
  {
    gpu_tensor_op.random_number_host_gaussian(gptr,&gsp,m,sd);

  }
  #endif

}

//Juan: Implemented
void Tensor::add_noise_gauss(LType noiser,LType mean,LType noisesd)
{
  if(useCPU)
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
#ifdef fGPU
  else
  {
   float* gptr_aux=gpu_tensor_op.makeTensor(gsp.row,gsp.col,gsp.batch,gsp.featureMap);
   gpu_tensor_op.random_number_host_gaussian(gptr_aux,&gsp,mean,noisesd);
   gpu_tensor_op.add_noise(gptr,gptr_aux,noiser,&gsp);
   gpu_tensor_op.destroyTensor(gptr_aux); 
  }
  #endif

}

/////
///////////////////////////////////////////////////////////////////////////
//Juan: Not implemented
LType Tensor::get(int a)
{
  if (dim!=1) {
    fprintf(stderr,"Error get with 1 param for dim=%d\n",dim);
  }
  if(useCPU)
  //CPU
  return ptr1(a);
  #ifdef fGPU
  else
  {
     float aux1;
     gpu_tensor_op.copy_data(&aux1, &(gptr[a]),FROMGPU,sizeof(float));
     return aux1;

  }
  #endif


}
//Juan: implemented
LType Tensor::get(int a,int b)
{
  if (dim!=2) {
    fprintf(stderr,"Error get with 2 params for dim=%d\n",dim);
  }
  //CPU
  if(useCPU)
  {
  return ptr2(a,b);
  }
  #ifdef fGPU
  else
  {
     float aux1;
     gpu_tensor_op.copy_data(&aux1, &(gptr[a*this->b+b]),FROMGPU,sizeof(float));
     return aux1;
  }
  #endif
}

//Juan: Not implemented
LType Tensor::get(int a,int b,int c)
{
  if (dim!=3) {
    fprintf(stderr,"Error get with 3 params for dim=%d\n",dim);
  }
  //CPU
  if(useCPU)
  return ptr[a]->ptr2(b,c);
 #ifdef fGPU
  else
  {
  fprintf(stderr,"get 3D\n");exit(-1);
  }
  #endif


}
//Juan: Not implemented
LType Tensor::get(int a,int b,int c,int d)
{
  if (dim!=4) {
    fprintf(stderr,"Error get with 4 params for dim=%d\n",dim);
  }
  //CPU
  if(useCPU)
  return ptr[a]->ptr[b]->ptr2(c,d);
 #ifdef fGPU
  else
  {
  fprintf(stderr,"get 4D\n");exit(-1);
  }
  #endif


}

//Juan: Not implemented
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
//Juan: Not implemented
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

//Juan: Not implemented
void Tensor::mul(LType val)
{
  if(useCPU)
    {
      if (dim==1)
#pragma omp parallel for
	for(int i=0;i<a;i++) ptr1(i)*=val;
      else if (dim==2)
#pragma omp parallel for
	for(int i=0;i<a;i++)
	  for(int j=0;j<b;j++)
	    ptr2(i,j)*=val;
      else 
	for(int i=0;i<a;i++)
	  ptr[i]->mul(val);
    }
#ifdef fGPU
  else
    {
      fprintf(stderr,"tensor absolute value\n");exit(-1);
    }
#endif



}

void Tensor::div(LType val)
{
  if(useCPU)
    {
      if (dim==1)
	  #pragma omp parallel for
	for(int i=0;i<a;i++) ptr1(i)/=val;
      else if (dim==2)
  #pragma omp parallel for
	for(int i=0;i<a;i++)
	  for(int j=0;j<b;j++)
	    ptr2(i,j)/=val;
      else 
	for(int i=0;i<a;i++)
	  ptr[i]->div(val);
    }
#ifdef fGPU
  else
    {
      fprintf(stderr,"tensor absolute value\n");exit(-1);
    }
#endif



}

void Tensor::add(LType val)
{
  if(useCPU)
    {
      if (dim==1)
	  #pragma omp parallel for
	for(int i=0;i<a;i++) ptr1(i)+=val;
      else if (dim==2)
	  #pragma omp parallel for
	for(int i=0;i<a;i++)
	  for(int j=0;i<b;i++)
	    ptr2(i,j)+=val;
      else 
	for(int i=0;i<a;i++)
	  ptr[i]->add(val);
    }
#ifdef fGPU
  else
    {
      fprintf(stderr,"tensor absolute value\n");exit(-1);
    }
#endif
}


void Tensor::abs()
{
  if(useCPU)
    {
      if (dim==1)
	  #pragma omp parallel for
	for(int i=0;i<a;i++) ptr1(i)=fabs(ptr1(i));
      else if (dim==2)
	  #pragma omp parallel for
	for(int i=0;i<a;i++)
	  for(int j=0;i<b;i++)
	    ptr2(i,j)=fabs(ptr2(i,j));
      else 
	for(int i=0;i<a;i++)
	  ptr[i]->abs();
    }
#ifdef fGPU
  else
    {
      fprintf(stderr,"tensor absolute value\n");exit(-1);
    }
#endif


}

void Tensor::sqr()
{
  if(useCPU)
    {
      if (dim==1)
	  #pragma omp parallel for
	for(int i=0;i<a;i++) ptr1(i)=sqrt(ptr1(i));
      else if (dim==2)
	  #pragma omp parallel for
	for(int i=0;i<a;i++)
	  for(int j=0;i<b;i++)
	    ptr2(i,j)=sqrt(ptr2(i,j));
      else 
	for(int i=0;i<a;i++)
	  ptr[i]->sqr();
    }
#ifdef fGPU
  else
    {
      fprintf(stderr,"tensor sqrt\n");exit(-1);
    }
#endif


}

LType Tensor::norm() {
  return sum();
}
LType Tensor::sum()
{
  if(useCPU)
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
  #ifdef fGPU
  else
  {
    LType sum=0;
    gpu_tensor_op.reduce_operator(gptr,&gsp,&sum);
    return sum;
  }
  #endif


}

//Juan: Not implemented
LType Tensor::col_max(int ind,int *imax)
{
  if(useCPU)
 	 return ptr2.col(ind).maxCoeff(imax);
 #ifdef fGPU
  else
  {
  fprintf(stderr,"Imlementear col max 2D\n");exit(-1);
  }
  #endif

}

//Juan:  implemented
//JUAN_FIX: returned aux value for max_pooling
LType Tensor::row_max(int ind,int *imax)
{
if (useCPU)
  return ptr2.row(ind).maxCoeff(imax);
 #ifdef fGPU
  else
  {
  *imax = gpu_tensor_op.row_max(gptr,&(gsp),ind);
  float aux;
  gpu_tensor_op.copy_data(&aux,&gptr[*imax],FROMGPU,sizeof(float));
   
  //printf("====gpu routine %d \n",*imax);
  return aux;
  }
  #endif


}


//Juan:  implemented
void Tensor::inc_2Drowwise(Tensor *T)
{

  if ((dim!=2)||(T->dim!=1)) {
    fprintf(stderr,"inc_2Drowise is for 2D Tensor + 1D Tensor\n");
    exit(1);
  }
  if (useCPU)    
  //CPU
  ptr2.rowwise()+=T->ptr1;
  #ifdef fGPU
  else
  {
    gpu_tensor_op.mat_elwise_vec(NULL,gptr,T->gptr,&gsp,0,1);
  }
  #endif


}



/// STATIC FUNCS
void Tensor::loss_sse(Tensor *T,Tensor *N,Data *D,int offset,double &mae,double &mse)
{

  if (T->dim!=2) msgerr("loss_sse","error T dim!=2");
  if (N->dim!=2) msgerr("loss_sse","error N dim!=2");

  // Lo mismo para CPU o GPU está refactorizado para que sea genérico
  // ATENCION JUAN tienes que implementar el sum() y el abs()
  if (D==NULL) {
    Tensor *Res=new Tensor(T->a,T->b);

    Tensor::sum(1,T,0,-1,N,0,Res,0); // T-N
    Tensor::el_mult(Res,0,Res,0,Res,0); //(T-N)*(T-N)
    mse+=Res->sum()/T->b;

    Tensor::sum(1,T,0,-1,N,0,Res,0); // T-N
    if(useCPU)
    {
      Res->abs();
      mae+=Res->sum()/T->b;
    }
    #ifdef fGPU
    else
    {
      float aux=0;
      gpu_tensor_op.sum_abs(Res->gptr,&(Res->gsp),&aux);
      mae+=aux/T->b;
    }
    #endif

    Res->abs();
    mae+=Res->sum()/T->b;
    delete Res;
  }
  else { //D!=NULL hay que deshacer normalización
    if (useCPU) {
      for(int i=0;i<N->a;i++)
	for(int j=0;j<N->b;j++) {
	  float Tn,Nn;
	  Tn=(T->ptr2(i,j)*D->fsd[j+offset])+D->fmu[j+offset];
	  Nn=(N->ptr2(i,j)*D->fsd[j+offset])+D->fmu[j+offset];
	  
	  mse+=(Tn-Nn)*(Tn-Nn)/T->b;
	  mae+=fabs(Tn-Nn)/T->b;
	}
    }
#ifdef fGPU
    else {
     //desnormalizar
     Tensor* Nn=new Tensor(N->a,N->b);
     Tensor* Tn=new Tensor(T->a,T->b);     
     Tensor *Res=new Tensor(T->a,T->b);
     Tensor* mu = new Tensor(T->b);
     Tensor* std = new Tensor(T->b);    

 
     std->copyStatistics(D,1);//copy std
     mu->copyStatistics(D,2);//copy mean
     
//     mu->set(0.0);
//     std->set(1.0);

     printDebug(std->gptr,"",std->gsp.row,std->gsp.col);
     printDebug(mu->gptr,"",mu->gsp.row,mu->gsp.col);
     getchar();
     gpu_tensor_op.mat_elwise_vec(Nn->gptr,N->gptr,std->gptr,&(N->gsp),1,0);//product by std     
     gpu_tensor_op.mat_elwise_vec(Tn->gptr,T->gptr,std->gptr,&(N->gsp),1,0);     
    
     gpu_tensor_op.mat_elwise_vec(Nn->gptr,N->gptr,mu->gptr,&(N->gsp),0,0);//add mean     
     gpu_tensor_op.mat_elwise_vec(Tn->gptr,T->gptr,mu->gptr,&(N->gsp),0,0);     

     Tensor::sum(1,T,0,-1,N,0,Res,0); // T-N
     
     Tensor::el_mult(Res,0,Res,0,Res,0); //(T-N)*(T-N)

     mse+=Res->sum()/T->b*-1;
     Tensor::sum(1,T,0,-1,N,0,Res,0); // T-N
     float aux=0;
     gpu_tensor_op.sum_abs(Res->gptr,&(Res->gsp),&aux);
     mae+=aux/T->b;

     delete Res;
     delete Tn;
     delete Nn; 
     delete mu;
     delete std;
    }
#endif
  }

}


void Tensor::loss_cross_entropy(Tensor *T,Tensor *N,double &cerr,double &ent)
{
  
  if (T->dim!=2) msgerr("loss_cross_entropy","error T dim!=2");
  if (N->dim!=2) msgerr("loss_cross_entropy","error N dim!=2");
  
  if (useCPU) {
    int i,j,rindex,nindex;
    for(i=0;i<T->a;i++) {
      T->row_max(i,&rindex);
      N->row_max(i,&nindex);
      if (rindex!=nindex) cerr++;
      for(j=0;j<T->b;j++) {
	if (j==rindex) {if (N->ptr2(i,j)!=0.0) ent-=log(N->ptr2(i,j));}
	else if (N->ptr2(i,j)!=1.0) ent-=log(1-N->ptr2(i,j));
      }
    }
  }
#ifdef fGPU
  else {
   int op=0;
    if (op)
    {
       int i,j,rindex,nindex;
    for(i=0;i<T->a;i++) {
      T->row_max(i,&rindex);
      N->row_max(i,&nindex);
      if (rindex!=nindex) cerr++;
      for(j=0;j<T->b;j++) {
	if (j==rindex) {if (N->get(i,j)!=0.0) ent-=log(N->get(i,j));}
	else if (N->get(i,j)!=1.0) ent-=log(1-N->get(i,j));
      }
    }
    }
    else
     {
	double aux_ent;
        double aux_cerr;
	gpu_tensor_op.compute_loss(T->gptr,N->gptr,CE,&(T->gsp),&aux_ent,&aux_cerr);
        ent+=aux_ent;
        cerr+=aux_cerr;

      }
    }
#endif
}
  

///////////////////////////////////////
//// MULT C=(a*A)*(b*B)
//// Dimensions must fit
////
////      ONLY FOR 2D TENSORS
////
//// tA,tB {0,1} to transpose A and B
//// inc {0,1} 
////           0: set the result in C
////           1: increment the result in C
///////////////////////////////////////
//Juan: Implemented
Tensor *Tensor::mult(Tensor *A, int tA, Tensor *B, int tB, Tensor *C, int inc)
{
  int aux=0;

  if (VERBOSE) {
    fprintf(stderr,"Tensor::mult %d %d %d %d %d\n",A->dim,B->dim,tA,tB,inc);
  }
  if (useCPU)
  {
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
  }
  #ifdef fGPU
  else
  {
      gpu_tensor_op.matMul(A->gptr,B->gptr,C->gptr,&(A->gsp),&(B->gsp),&(C->gsp),inc,tA,tB);
  } 
  #endif

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
//Juan: Implemented
Tensor * Tensor::sc_mult(Tensor *A, LType sc, Tensor *B, int inc)
{
  if (useCPU)
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
  }
  #ifdef fGPU
  else
  {
    gpu_tensor_op.scMat(B->gptr,A->gptr,&(A->gsp),sc,1,inc);
  }

  #endif

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
//Juan:Implemented
Tensor * Tensor::el_mult(Tensor *A, int tA, Tensor *B, int tB, Tensor *C, int inc)
{
  if(useCPU)
  {

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
  }
  #ifdef fGPU
  else{
      gpu_tensor_op.mat_elwise_mat(A->gptr,B->gptr,C->gptr,&(A->gsp),&(B->gsp),&(C->gsp),1,inc,tA,tB);
  }                                       
  #endif
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
  if(useCPU)
  {
  for(int i=0;i<A->a;i++) {
    LMatrix Res=A->ptr2.row(i).transpose()*B->ptr2.row(i);
    Map<RowVectorXf> v(Res.data(), Res.size());
    C->ptr2.row(i)=v;
  }
  }
  #ifdef fGPU
  else{
      gpu_tensor_op.matMul(A->gptr,B->gptr,C->gptr,&(A->gsp),&(B->gsp),&(C->gsp),inc,0,0);
  }
  #endif

  

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
 //Juan: Implemented
 Tensor * Tensor::sum(LType sca,Tensor *A, int tA, LType scb,Tensor *B, int tB, Tensor *C, int inc)
{

   if(useCPU)
   {
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
  }
  #ifdef fGPU
  else{
    gpu_tensor_op.mat_elwise_mat(A->gptr,B->gptr,C->gptr,&(A->gsp),&(B->gsp),&(C->gsp),0,inc,tA,tB,sca,scb);
  }
#endif
  return C;
}


void Tensor::sumcol(Tensor *A,Tensor *B)
{
  int j;
  
  if (useCPU) {
    for(j=0;j<A->a;j++)
      A->set(j,B->ptr2.col(j).sum());
  }
  #ifdef fGPU
  else{
    float* sum;
    float b;
    sum=gpu_tensor_op.col_sum(B->gptr,&(B->gsp));
    
    gpu_tensor_op.copy_data(A->gptr,sum,GPU,A->a*sizeof(float));
    
    gpu_tensor_op.destroyTensor(sum);

  }
  #endif
}



 ///////////////////////////////////////////////                                                          
 //// C+=A 
 ////                                                                                                     
 //// ANY D                                                                                               
 ///////////////////////////////////////////////           
 //Juan Implemented
 Tensor * Tensor::inc(Tensor *A, Tensor *C)
{
  if(useCPU)
  {
    if (A->dim==1) C->ptr1+=A->ptr1;
    else  if (A->dim==2) C->ptr2+=A->ptr2;
    else {
      for(int i=0;i<A->a;i++)
        Tensor::inc(A->ptr[i],C->ptr[i]);
    }
  }
  #ifdef fGPU
  else
  {
       gpu_tensor_op.mat_elwise_mat(A->gptr,C->gptr,C->gptr,&(A->gsp),&(C->gsp),&(C->gsp),0,0,0,0);
  }
  #endif 

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
//Juan:Implemented
Tensor * Tensor::sc_sum(Tensor *A, LType sc,Tensor *B,int inc) 
{
  if (useCPU)
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
  }
  #ifdef fGPU
  else{
    gpu_tensor_op.scMat(B->gptr,A->gptr,&(A->gsp),sc,0,inc);
  }

  #endif

  return B;
}
 


//Juan:Implemented
void Tensor::activation(Tensor *E,Tensor *N,int act)
{ 

  //CPU
  if(useCPU)
  {
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
  #ifdef fGPU
  else
  {
    gpu_tensor_op.activation(E->gptr,N->gptr,act,&(E->gsp));
  }

  #endif
}


void Tensor::print(const char *cad="")
{
  fprintf(stderr,"%s\n",cad);
  if (dim==1) {
    for(int i=0;i<a;i++)
      fprintf(stderr,"%1.3f ",ptr1(i));
    fprintf(stderr,"\n");
  }
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


//Juan: implemented
void Tensor::dactivation(Tensor *E,Tensor *N, Tensor *D, int act) 
{
  if(useCPU)
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
  }
  #ifdef fGPU
  else
     gpu_tensor_op.dactivation(E->gptr,N->gptr,D->gptr,act,&(E->gsp));
  #endif
  //D->print();
}

//For apply dropout
//Juan: implemented
void Tensor::maskZeros(Tensor *mask,Tensor *A)
{
  if(useCPU)
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
  #ifdef fGPU
  else
  {
  gpu_tensor_op.mat_elwise_vec(NULL,A->gptr,mask->gptr,&(A->gsp),1,1);
  }
  #endif
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



// REDUCED FUNCTIONS 2D <--> 1D                                                      
void Tensor::reduceTosum(Tensor *A, Tensor *B,int row)
{
  if (A->dim!=2) msgerr("reduceTosum","error A dim!=2\n");
  if (B->dim!=1) msgerr("reduceTosum","error B dim!=1\n");

  if (useCPU) {
    if (row) {
      #pragma omp parallel for
      for(int i=0;i<A->b;i++) {
        B->ptr1(i)=0;
        for(int j=0;j<A->a;j++)
          B->ptr1(i)+=A->ptr2(j,i);
      }
    }
    else {
      #pragma omp parallel for
      for(int i=0;i<A->a;i++) {
        B->ptr1(i)=0;
        for(int j=0;j<A->b;j++)
          B->ptr1(i)+=A->ptr2(i,j);
      }
    }
  }
#ifdef fGPU
  else
    {

    }
#endif
}
void Tensor::reduceTomean(Tensor *A, Tensor *B,int row)
{
  if (A->dim!=2) msgerr("reduceTomean","error A dim!=2\n");
  if (B->dim!=1) msgerr("reduceTomean","error B dim!=1\n");

  if (row) {
    Tensor::reduceTosum(A,B,row);
    B->div(A->a);
  }
  else {
    Tensor::reduceTosum(A,B,row);
    B->div(A->b);
  }
}

void Tensor::reduceTovariance(Tensor *A, Tensor *B,int row)
{
  if (A->dim!=2) msgerr("reduceTovariance","error A dim!=2\n");
  if (B->dim!=1) msgerr("reduceTovariance","error B dim!=1\n");

  Tensor *M;

  if (row)
    M=new Tensor(A->b);
  else
    M=new Tensor(A->a);

  Tensor *AM=new Tensor(A->a,A->b);

  Tensor::reduceTomean(A,M,row);

  Tensor::reduced_sum(1,A,-1,M,AM,0,row);
  Tensor::el_mult(AM,0,AM,0,AM,0);

  Tensor::reduceTomean(AM,B,row);

  delete M;
  delete AM;
}

void Tensor::reduced_sum(float scA, Tensor *A,float scB,Tensor *B,Tensor *C,int inc,\
			 int row)
{
  if (A->dim!=2) msgerr("reduced_sum","error A dim!=2\n");
  if (B->dim!=1) msgerr("reduced_sum","error B dim!=1\n");
  if (C->dim!=2) msgerr("reduced_sum","error C dim!=2\n");

  if (useCPU) {
    if (row)
      #pragma omp parallel for
      for(int i=0;i<A->a;i++)
        for(int j=0;j<A->b;j++)
          if (inc) C->ptr2(i,j)+=(scA*A->ptr2(i,j))+(scB*B->ptr1(j));
          else  C->ptr2(i,j)=(scA*A->ptr2(i,j))+(scB*B->ptr1(j));
    else
      #pragma omp parallel for
      for(int i=0;i<A->a;i++)
        for(int j=0;j<A->b;j++)
          if (inc) C->ptr2(i,j)+=(scA*A->ptr2(i,j))+(scB*B->ptr1(i));
          else  C->ptr2(i,j)=(scA*A->ptr2(i,j))+(scB*B->ptr1(i));
  }
  #ifdef fGPU
  else
    {

    }
#endif

}
void Tensor::reduced_div(Tensor *A,Tensor *B,Tensor *C,int inc,int row)
{
  if (A->dim!=2) msgerr("reduced_div","error A dim!=2\n");
  if (B->dim!=1) msgerr("reduced_div","error B dim!=1\n");
  if (C->dim!=2) msgerr("reduced_div","error C dim!=2\n");

  if (useCPU) {
    if (row)
      #pragma omp parallel for
      for(int i=0;i<A->a;i++)
        for(int j=0;j<A->b;j++)
          if (inc) C->ptr2(i,j)+=A->ptr2(i,j)/B->ptr1(j);
          else C->ptr2(i,j)=A->ptr2(i,j)/B->ptr1(j);
    else
      #pragma omp parallel for
      for(int i=0;i<A->a;i++)
        for(int j=0;j<A->b;j++)
          if (inc) C->ptr2(i,j)+=A->ptr2(i,j)/B->ptr1(i);
          else C->ptr2(i,j)=A->ptr2(i,j)/B->ptr1(i);

  }
#ifdef fGPU
  else
    {

    }
#endif

}

void Tensor::reduced_mult(Tensor *A,Tensor *B,Tensor *C,int inc,int row)
{
  if (A->dim!=2) msgerr("reduced_mult","error A dim!=2\n");
  if (B->dim!=1) msgerr("reduced_mult","error B dim!=1\n");
  if (C->dim!=2) msgerr("reduced_mult","error C dim!=2\n");

  if (useCPU) {
    if (row)
      #pragma omp parallel for
      for(int i=0;i<A->a;i++)
        for(int j=0;j<A->b;j++)
          if (inc) C->ptr2(i,j)+=A->ptr2(i,j)*B->ptr1(j);
          else C->ptr2(i,j)=A->ptr2(i,j)*B->ptr1(j);
    else
      #pragma omp parallel for
      for(int i=0;i<A->a;i++)
        for(int j=0;j<A->b;j++)
          if (inc) C->ptr2(i,j)+=A->ptr2(i,j)*B->ptr1(i);
          else C->ptr2(i,j)=A->ptr2(i,j)*B->ptr1(i);

  }
#ifdef fGPU
  else
    {

    }
#endif

}





