#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <iostream>

#include "Eigen/Dense"
#include "layer.h"
#include "utils.h"

#define VERBOSE 0

using namespace Eigen;
using namespace std;

////////////////////////////////////
///// POOLING LAYER CLASS
////////////////////////////////////
CatLayer::CatLayer()
{
  type=4;
  cat=0;

}

CatLayer::CatLayer(int batch,char *name):CLayer(batch,name)
{
  this->batch=batch;
  type=4;
  cat=0;

  N=(LMatrix **)malloc(batch*sizeof(LMatrix *));
  De=(LMatrix **)malloc(batch*sizeof(LMatrix *));

  fprintf(stderr,"Creating CatLayer (%s)\n",name);
}

void CatLayer::addchild(Layer *l)
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
      fprintf(stderr,"Connecting %s --> %s Pool\n",name,l->name);
      l->addparent(this);
    }
    else {
      fprintf(stderr,"Error: %s cat layer can not have child layer %s\n",name,l->name);
      exit(1);
    }
  }
}

void CatLayer::addparent(Layer *l)
{
  int i,j;

  int enc=0;

  for(int i=0;i<lin;i++)
    if (Lin[i]==l) enc=1;

  if (!enc) {

    if (l->type>1) {
      CLayer *c=(CLayer *)l;
      Lin[lin++]=l;

      if (cat==0) {
	outr=c->outr;
	outc=c->outc;
	catvec[cat]=c->outz;
	outz+=c->outz;
	cat++;
      }
      else {
	if ((outr!=c->outr)||(outc!=c->outc)) {
	  fprintf(stderr,"Error: (%s) can not cat different sizes\n",name);
	  exit(-1);
	}
	catvec[cat]=catvec[cat-1]+c->outz;
	outz+=c->outz;
	cat++;
      }
    }
    else {
      fprintf(stderr,"Error: (%s) cat layer only after cnn or maxpool\n",name);
      exit(-1);
    }

    nk=outz;
    for(i=0;i<batch;i++)
      N[i]=new LMatrix[nk];

    for(i=0;i<batch;i++)
      for(j=0;j<nk;j++)
	N[i][j].resize(outr,outc);

    for(i=0;i<batch;i++) {
      De[i]=new LMatrix[nk];
    }

    for(i=0;i<batch;i++)
      for(j=0;j<nk;j++)
	De[i][j].resize(outr,outc);

    fprintf(stderr,"Creating CatLayer (%s) output %d@%dx%d\n",name,outz,outr,outc);
  }
}




void CatLayer::forward()
{
  int i,j,b;
  int ini;
  CLayer *c;
  PLayer *p;

  for(i=0;i<lin;i++) {
    if (i==0) ini=0;
    else ini=catvec[i-1];

    for(j=ini;j<catvec[i];j++) {
	c=(CLayer *)Lin[i];
	for(b=0;b<batch;b++)
	  N[b][j]=c->N[b][j-ini];
      }
  }
}

void CatLayer::save(FILE *fe)
{
  save_param(fe);
}

void CatLayer::load(FILE *fe)
{
  load_param(fe);
}


void CatLayer::backward()
{
  int i,j,b;
  int ini;
  CLayer *c;
  PLayer *p;

  for(i=0;i<lin;i++) {
    if (i==0) ini=0;
    else ini=catvec[i-1];


    for(j=ini;j<catvec[i];j++){
	c=(CLayer *)Lin[i];
	for(b=0;b<batch;b++)
	  c->De[b][j-ini]=De[b][j];
    }
  }

}


void CatLayer::initialize(){ }
void CatLayer::applygrads(){ }
void CatLayer::reset()
{
  int i,j;

  for(i=0;i<batch;i++)
    for(j=0;j<nk;j++)
      De[i][j].setZero();

}
