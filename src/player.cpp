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
///// POOLING LAYER CLASS
////////////////////////////////////
PLayer::PLayer()
{
  type=3;

}

PLayer::PLayer(int batch,int sizer,int sizec,char *name):CLayer(batch,name)
{
  this->batch=batch;
  this->sizer=sizer;
  this->sizec=sizec;
  type=3;

  fprintf(stderr,"Creating MaxPool layer (%s) with %dx%d size\n",name,sizer,sizec);
}

void PLayer::addchild(Layer *l)
{
  int enc=0;
  
  for(int i=0;i<lout;i++)
    if (Lout[i]==l) enc=1;
  
  if (!enc) {

    if (l->type==1) {
      Lout[lout++]=l;
      fprintf(stderr,"Connecting %s --> %s Reshape Layer\n",name,l->name);
      l->addparent(this);
    }
    else if (l->type==2) {
      Lout[lout++]=l;
      fprintf(stderr,"Connecting %s --> %s Conv\n",name,l->name);
      l->addparent(this);
    }
    else if (l->type==3) {
      fprintf(stderr,"Error: %s mp layer can not have child mp layer %s\n",name,l->name);
      exit(1);
    }
    else if (l->type==4) {
      Lout[lout++]=l;
      fprintf(stderr,"Connecting %s --> %s Cat\n",name,l->name);
      l->addparent(this);
    }
    else {
      fprintf(stderr,"Error: %s mp layer can not have child layer %s\n",name,l->name);
      exit(1);
    }
  }
}

void PLayer::addparent(Layer *l)
{
  int i,j;

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

  
  if ((l->type==2)||(l->type==3)||(l->type==4)) {
    CLayer *c=(CLayer *)l;
    Lin[lin++]=l;
    
    nk=outz=c->outz;
    outr=(c->outr/sizer);
    outc=(c->outc/sizec);
    
    maxR=(MatrixXi **)malloc(batch*sizeof(MatrixXi *));
    for(i=0;i<batch;i++) {
      maxR[i]=new MatrixXi[nk];
    }
    
    for(i=0;i<batch;i++)
      for(j=0;j<nk;j++)
	maxR[i][j].resize(outr,outc);
    
    maxC=(MatrixXi **)malloc(batch*sizeof(MatrixXi *));
    for(i=0;i<batch;i++) {
      maxC[i]=new MatrixXi[nk];
    }
    
    for(i=0;i<batch;i++)
      for(j=0;j<nk;j++)
	maxC[i][j].resize(outr,outc);
    
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
    
    fprintf(stderr,"Creating MaxPool (%dx%d) output %d@%dx%d\n",sizer,sizec,outz,outr,outc);
  }
  else {
    fprintf(stderr,"Error: MaxPool layer (%s) can only appear after Conv, Cat or MPool layers\n",name);
    exit(1);
  }
}
  
void PLayer::MaxPool()
{
  
 
  CLayer *c=(CLayer *)Lin[0];
  float sum=0.0;

  if (VERBOSE) {
    for(int b=0;b<batch;b++) 
      for(int i=0;i<c->outz;i++)
	sum+=c->N[b][i].norm();
    fprintf(stderr,"%s Parent N(%s) = %f\n",name,c->name,sum);
  }


#pragma omp parallel for
  for(int b=0;b<batch;b++) {
    MatrixXf::Index x,y;
    int i,j,k,z,r;
    int mr,mc;
    for(k=0;k<nk;k++) {
      for(i=0;i<outr;i++) {
	for(j=0;j<outc;j++) {
	  N[b][k](i,j)=((c->N[b][k]).block((i*sizer),(j*sizec),sizer,sizec)).maxCoeff(&x,&y);

	  maxR[b][k](i,j)=x;
	  maxC[b][k](i,j)=y;
	  maxR[b][k](i,j)+=(i*sizer);
	  maxC[b][k](i,j)+=(j*sizec);
	}
      }
    }
  }
}


void PLayer::forward()
{
  int i,b;
  float sum=0.0;

  MaxPool();
    
  if (VERBOSE) {
    for(b=0;b<batch;b++) 
      for(i=0;i<outz;i++)
	sum+=N[b][i].norm();
    fprintf(stderr,"N(%s) = %f\n",name,sum);
  }
}



void PLayer::save(FILE *fe)
{
  save_param(fe);

  fprintf(fe,"%d %d\n",sizer,sizec);
  
}

void PLayer::load(FILE *fe)
{
  int fsd;

  load_param(fe);

  fsd=fscanf(fe,"%d %d\n",&sizer,&sizec);
  
}



void PLayer::MaxPoolB()
{
  CLayer *c=(CLayer *)Lin[0];
  float sum=0;

  #pragma omp parallel for
  for(int b=0;b<batch;b++) {
    int i,j,k,z,r;
    for(k=0;k<nk;k++) {
      for(i=0;i<outr;i++) 
	for(j=0;j<outc;j++) 
	  c->De[b][k](maxR[b][k](i,j),maxC[b][k](i,j))=De[b][k](i,j);
      if (VERBOSE) sum+=De[b][k].norm();
    }
  }

  if (VERBOSE) fprintf(stderr,"DeMP=%f\n ",sum);

  if (VERBOSE) {
    sum=0;
    int b,k;
    for(b=0;b<batch;b++)
      for(k=0;k<nk;k++) {
	sum+=c->De[b][k].norm();
       
      }
    fprintf(stderr,"DeMPIn=%f\n ",sum);
  }
}

void PLayer::backward()
{
  
  MaxPoolB();

}


void PLayer::initialize(){ }
void PLayer::applygrads(){ }
void PLayer::reset()
{ 
  int i,j;

  for(i=0;i<batch;i++)
    for(j=0;j<nk;j++)
      De[i][j].setZero();

}
