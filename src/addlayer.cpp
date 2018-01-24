#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <iostream>

#include "layer.h"
#include "utils.h"


////////////////////////////////////
///// ADD LAYER CLASS
////////////////////////////////////
AddLayer::AddLayer()
{
  type=ADDLAYER;
  act=1;
}

AddLayer::AddLayer(int batch,char *name):CLayer(batch,name)
{
  this->batch=batch;
  type=ADDLAYER;
  act=1;


  fprintf(stderr,"Creating AddLayer (%s)\n",name);
}

void AddLayer::addchild(Layer *l)
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
    else if (l->type==4) {
      Lout[lout++]=l;
      fprintf(stderr,"Connecting %s --> %s Cat\n",name,l->name);
      l->addparent(this);
    }    
    else if (l->type==5) {
      Lout[lout++]=l;
      fprintf(stderr,"Connecting %s --> %s Add\n",name,l->name);
      l->addparent(this);
    }
    else {
      fprintf(stderr,"Error: %s add layer can not have child layer %s\n",name,l->name);
      exit(1);
    }
  }
}

void AddLayer::shared(Layer *li){}

void AddLayer::addparent(Layer *l)
{
  int i,j;

  int enc=0;

  for(int i=0;i<lin;i++)
    if (Lin[i]==l) enc=1;

  if (!enc) {

    if (l->type>1) {
      CLayer *c=(CLayer *)l;
      Lin[lin++]=l;

      if (add==0) {
	add++;
	outr=c->outr;
	outc=c->outc;
	outz=c->outz;
	nk=outz;
      }
      else {
	if ((outr!=c->outr)||(outc!=c->outc)) {
	  fprintf(stderr,"Error: (%s) can not add different sizes\n",name);
	  exit(-1);
	}
      
	if (c->outz>nk) nk=c->outz;
      }

      N=new Tensor(batch,nk,outr,outc);
      E=new Tensor(batch,nk,outr,outc);
      Delta=new Tensor(batch,nk,outr,outc);
    }
    else {
      fprintf(stderr,"Error: (%s) add layer only after cnn-like layers\n",name);
      exit(-1);
    }

   fprintf(stderr,"Creating AddLayer (%s) output %d@%dx%d\n",name,outz,outr,outc);
  }
}




void AddLayer::forward()
{
  int i,j,b;
  int ini;
  CLayer *c;
  PLayer *p;

  for(i=0;i<lin;i++) {
    c=(CLayer *)Lin[i];
    Tensor::inc(c->N,E);
  }

  Tensor::activation(E,N,act);

}

void AddLayer::save(FILE *fe)
{
  save_param(fe);
}

void AddLayer::load(FILE *fe)
{
  load_param(fe);
}


void AddLayer::backward()
{
  int i,j,b,k,r,c;
  int ini;
  CLayer *cin;

  Tensor::dactivation(E,N,Delta,act);

  for(i=0;i<lin;i++) {
    cin=(CLayer *)Lin[i]; 
    cin->Delta->copy(Delta);
  }
}


void AddLayer::initialize(){ }
void AddLayer::applygrads(){ }
void AddLayer::reset()
{
  int i,j;
  
  Delta->set(0.0);
  E->set(0.0);
}
void AddLayer::resetmomentum(){}
