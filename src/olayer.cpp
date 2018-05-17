#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <iostream>


#include "layer.h"
#include "utils.h"

////////////////////////////////////
///// OPERATOR LAYER CLASS
////////////////////////////////////
OLayer::OLayer()
{
  type=OLAYER;
}

OLayer::OLayer(int batch,int op,char *name):Layer(batch,name)
{
  this->batch=batch;
  type=OLAYER;
  this->op=op;

  fprintf(stderr,"Creating Operator Layer layer (%s) op %d\n",name,op);
}

void OLayer::addchild(Layer *l)
{
  int enc=0;

  if (l->type!=OLAYER) 
    if (N->size!=l->N->size) {
      fprintf(stderr,"Error connecting with operator %s with %s %d!=%d\n",name,l->name,N->size,l->N->size);
  }

  Lout[lout++]=l;
  fprintf(stderr,"Connecting %s --> %s\n",name,l->name);
  l->addparent(this);

}
void OLayer::shared(Layer *li){}

void OLayer::addparent(Layer *l)
{
  int i,j;
  
  if ((op>=OP_MEAN)&&(lin>0)) {
    fprintf(stderr,"Unary operator only accepts 1 parent layer\n");
    exit(1);
  }

  if ((op<OP_MEAN)&&(lin>1)) {
    fprintf(stderr,"Bimary operator only accepts 2 parent layer\n");
    exit(1);
  }

  if (l->N->dim!=2) {
    fprintf(stderr,"Operators only over 2D Tensors\n");
    exit(1);
  }

  Lin[lin++]=l;
  

  if (lin==1) {
    din=Lin[0]->N->size/batch;

    if (op==OP_OMULT) din*=din;

    N=new Tensor(batch,din);
    Delta=new Tensor(batch,din);
    dE=new Tensor(batch,din);
  }
  else { // in case of binary op check sizes
    int s1,s2;
    
    s1=Lin[0]->N->size;
    s2=Lin[1]->N->size;
    
    if (s1!=s2) {
      if (op!=OP_OMULT){
	fprintf(stderr,"operand sizes don't match %d!=%d\n",s1,s2);
	exit(1);
      }
      else {
	s1/=batch;
	s2/=batch;
	din=s1*s2;
	N=new Tensor(batch,s1*s2);
	Delta=new Tensor(batch,s1*s2);
      }
    }
  }
}

void OLayer::forward()
{
  if (op<=5) {
    Tensor *t1=Lin[0]->N;
    Tensor *t2=Lin[1]->N;

    if (op==OP_SUM) Tensor::sum(1.0,t1,0,1.0,t2,0,N,0);
    if (op==OP_SUB) Tensor::sum(1.0,t1,0,-1.0,t2,0,N,0);
    if (op==OP_IMULT) Tensor::el_mult(t1,0,t2,0,N,0);
    if (op==OP_OMULT) Tensor::out_mult(t1,t2,N,0);
    if (op==OP_DIV) {}
  }
  else if (op<=10) {
    Tensor *t1=Lin[0]->N;
    if (op==OP_MEAN) {
      Tensor *n=new Tensor(t1->b);
      Tensor::reduceTomean(t1,n,1);
      Tensor::augment(n,N,1);
      delete n;
    }
  }
  else {
    Tensor *t1=Lin[0]->N;
    if (op==OP_SIGM) Tensor::activation(t1,N,ACT_SIG);
    if (op==OP_RELU) Tensor::activation(t1,N,ACT_RLU);
    if (op==OP_TANH) {}
    if (op==OP_LOG) {}
  }

  if (VERBOSE) fprintf(stderr,"N(%s) = %f\n",name,N->norm());
}

void OLayer::backward()
{
  int i,b;
  
  if (VERBOSE) fprintf(stderr,"%s Delta norm %f\n",name,Delta->sum());

  if (op<=5) {
    Tensor *t1=Lin[0]->Delta;
    Tensor *t2=Lin[1]->Delta;

    Tensor *n1=Lin[0]->N;
    Tensor *n2=Lin[1]->N;

    if (op==OP_SUM) {
      Tensor::inc(Delta,t1);
      Tensor::inc(Delta,t2);
    }
    if (op==OP_SUB) {
      Tensor::inc(Delta,t1);
      Tensor::sc_mult(Delta,-1.0, t2,1);
    }
    if (op==OP_IMULT) {
      Tensor::el_mult(Delta,0,n2,0,t1,1);
      Tensor::el_mult(Delta,0,n1,0,t2,1);
    }
    if (op==OP_OMULT) {
      int s1=Lin[0]->din;
      int s2=Lin[1]->din;

      
      Tensor *n=new Tensor(batch,s1,s2);
      n->copy(Delta);

      Tensor *m1=new Tensor(batch,1,s1);
      m1->copy(Lin[0]->N);

      Tensor *m2=new Tensor(batch,1,s2);
      m2->copy(Lin[1]->N);

      Tensor::mult(m1,0,n,0,m2,0);
      Tensor::mult(m2,0,n,1,m1,0);

      delete n;
      delete m1;
      delete m2;
    }
  }
  else if (op<=10) {
    Tensor *t1=Lin[0]->Delta;
    if (op==OP_MEAN) {
      Tensor::sc_mult(Delta, 1.0/t1->a, t1,1);
    }
  }
  else {
    Tensor *t1=Lin[0]->Delta;
    Tensor *n1=Lin[0]->N;

    if (op==OP_SIGM) {
      Tensor::dactivation(n1,N,dE,ACT_SIG);
      Tensor::el_mult(Delta,0,dE,0,t1,1);
    }
    if (op==OP_RELU) {
      Tensor::dactivation(n1,N,dE,ACT_RLU);
      Tensor::el_mult(Delta,0,dE,0,t1,1);
    }
    if (op==OP_TANH) {}
    if (op==OP_LOG) {}
  }

}



void OLayer::save(FILE *fe)
{
  save_param(fe);

}

void OLayer::load(FILE *fe)
{
  int fsd;

  load_param(fe);
}


void OLayer::initialize(){ }
void OLayer::applygrads(){ }
void OLayer::reset()
{
  N->set(0.0);
  Delta->set(0.0);
}

