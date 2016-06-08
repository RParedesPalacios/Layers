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
///// BASE LAYER CLASS
////////////////////////////////////

Layer::Layer()
{
 
}

Layer::Layer(int batch,char *name)
{

  strcpy(this->name,name);
  this->batch=batch;
  
  din=0;
  lin=0;
  lout=0;
  mu=0.0001;
  mmu=0.9;
  drop=0.0;
  l2=l1=maxn=0.0;
  trmode=1;
  type=0;
  act=1;
  noiser=noisesd=0;
  dev_done=0;
  reshape=0;
  local=0;
  bn=0;
  init=0;
  shift=flip=0;
  brightness=contrast=0;

  D=NULL;

  Lin=(Layer **)malloc(MAX_CONNECT*sizeof(Layer *));
  Lout=(Layer **)malloc(MAX_CONNECT*sizeof(Layer *));

  
}

void Layer::setbrightness(float f){ if (VERBOSE) fprintf(stderr,"Layer %s setting brightness %f\n",name,f);brightness=f;}

void Layer::setcontrast(float f){ if (VERBOSE) fprintf(stderr,"Layer %s setting contrast %f\n",name,f);contrast=f;}

void Layer::setflip(int f){ if (VERBOSE) fprintf(stderr,"Layer %s setting flip %d\n",name,f);flip=f;}
void Layer::setshift(int f){ if (VERBOSE) fprintf(stderr,"Layer %s setting shift %d\n",name,f);shift=f;}
void Layer::setmu(float m){if (VERBOSE) fprintf(stderr,"Layer %s setting mu %f\n",name,m);mu=m;resetmomentum();}
void Layer::setmmu(float m){ if (VERBOSE) fprintf(stderr,"Layer %s setting mmu %f\n",name,m);mmu=m;}
void Layer::setdrop(float m){ if (VERBOSE) fprintf(stderr,"Layer %s setting drop %f\n",name,m);drop=m;}
void Layer::setl2(float m){ if (VERBOSE) fprintf(stderr,"Layer %s setting l2 %f\n",name,m);l2=m;}
void Layer::setl1(float m){ if (VERBOSE) fprintf(stderr,"Layer %s setting l1 %f\n",name,m);l1=m;}
void Layer::setmaxn(float m){ if (VERBOSE) fprintf(stderr,"Layer %s setting maxn %f\n",name,m);maxn=m;}
void Layer::trainmode(){trmode=1;}
void Layer::testmode(){trmode=0;}
void Layer::setact(int i){ if (VERBOSE) fprintf(stderr,"Layer %s setact to %d\n",name,i);act=i;} 
void Layer::setbn(int i){ if (VERBOSE) fprintf(stderr,"Layer %s setting BN %d\n",name,i);bn=i;} 
void Layer::setnoiser(float m){ if (VERBOSE) fprintf(stderr,"Layer %s setting noiser %f\n",name,m);noiser=m;}
void Layer::setnoisesd(float m){ if (VERBOSE) fprintf(stderr,"Layer %s setting noisesd %f\n",name,m);noisesd=m;}
void Layer::setthreads(int t){threads=t;}
void Layer::setopt(int t){opt=t;}

void Layer::save_param(FILE *fe)
{
  int i;

  fprintf(fe,"%s\n",name);
  fprintf(fe,"%d\n",din);
  fprintf(fe,"%d\n",lin);
  fprintf(fe,"%d\n",lout);

  fprintf(fe,"%d\n",act);
  fprintf(fe,"%d\n",bn);
  fprintf(fe,"%d\n",shift);
  fprintf(fe,"%d\n",flip);

  fprintf(fe,"%f\n",mu);
  fprintf(fe,"%f\n",mmu);
  fprintf(fe,"%f\n",drop);
  fprintf(fe,"%f\n",l2);
  fprintf(fe,"%f\n",l1);
  fprintf(fe,"%f\n",maxn);
  fprintf(fe,"%f\n",brightness);
  fprintf(fe,"%f\n",contrast);
  
  // FOR FUTURE PARAMS
  for(i=0;i<10;i++)
    fprintf(fe,"-1\n");
  
}
void Layer::load_param(FILE *fe)
{
  char lname[100];
  int ldin,llin,llout;
  int fsd,i;

  
  fsd=fscanf(fe,"%s\n",lname);
  if (strcmp(name,lname)) {
    fprintf(stderr,"Error loading layer  %s (name) %s -- %s\n",name,name,lname);
    exit(1);
  }
  fsd=fscanf(fe,"%d\n",&ldin);
  if (ldin!=din) {
    fprintf(stderr,"Error loading layer  %s (din) %d -- %d\n",name,din,ldin);
    exit(1);
  }

  fsd=fscanf(fe,"%d\n",&llin);
  if (llin!=lin) {
    fprintf(stderr,"Error loading layer  %s (lin) %d -- %d\n",name,lin,llin);
    exit(1);
  }
  fsd=fscanf(fe,"%d\n",&llout);
  if (llout!=lout) {
    fprintf(stderr,"Error loading layer  %s (lout) %d -- %d\n",name,lout,llout);
    exit(1);
  }

  fsd=fscanf(fe,"%d\n",&act);
  fsd=fscanf(fe,"%d\n",&bn);
  fsd=fscanf(fe,"%d\n",&shift);
  fsd=fscanf(fe,"%d\n",&flip);

  fsd=fscanf(fe,"%f\n",&mu);
  fsd=fscanf(fe,"%f\n",&mmu);
  fsd=fscanf(fe,"%f\n",&drop);
  fsd=fscanf(fe,"%f\n",&l2);
  fsd=fscanf(fe,"%f\n",&l1);
  fsd=fscanf(fe,"%f\n",&maxn);
  fsd=fscanf(fe,"%f\n",&brightness);
  fsd=fscanf(fe,"%f\n",&contrast);

  // FOR FUTURE PARAMS
  for(i=0;i<10;i++)
    fsd=fscanf(fe,"-1\n");
  

}
