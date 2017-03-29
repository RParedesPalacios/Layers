#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <iostream>
#include <time.h>


#include "net.h"
#include "layer.h"
#include "data.h"
#include "utils.h"

#define VERBOSE 0
#define SHOW_TIME 0

// Comment this line for Mac
#define USETIME 


////////////////////////////////////
///// NET CLASS
////////////////////////////////////

Net::Net(char *name)
{
  layers=0;
  olayers=0;
  strcpy(this->name,name);
  bn=0;
  init=0;
  cropmode=0;
  crops=1;
  decay=0.999;

  Dtrain=NULL;
  Dtest=NULL;
  Dval=NULL;
}

void Net::addLayer(Layer *l)
{
  int i,enc;

  enc=0;
  for(i=0;i<layers;i++)
    if (lvec[i]==l) enc=1;

  if (!enc) {
    fprintf(stderr,"adding layer %s to net %s\n",l->name, name);
    lvec[layers++]=l;
  }

}

void Net::initialize()
{
  int i;
  fprintf(stderr,"Net %s initializing layers\n",name);

  for(i=0;i<layers;i++) 
    lvec[i]->initialize();
}

void Net::net2dot()
{
  int i,j;
  FILE *fs;
  char *pch;
  char *pch2;
  char cad[1000];
  char cad2[1000];
  CLayer *c;
  PLayer *p;
  CatLayer *cat;

  sprintf(cad,"%s.dot",name);
  fs=fopen(cad,"wt");

  fprintf(fs,"digraph %s {\n",name);
  fprintf(fs,"rankdir=TB;\n");

  fprintf(fs,"Data [label=\"%s\",style=filled,fontsize=12,fillcolor=LightBlue,shape=box]\n",Dtrain->name);

  for(i=0;i<layers;i++) {
    strcpy(cad,lvec[i]->name);
    pch = strtok (cad,":");
    pch = strtok (NULL,":");
    if (lvec[i]->type==1) {
      if (lvec[i]->lin==0)
	fprintf(fs,"%s [label=\"%s [%d]\",style=filled,fontsize=12,fillcolor=Gray,shape=box]\n",pch,lvec[i]->name,lvec[i]->din);
      else if (lvec[i]->out)
	fprintf(fs,"%s [label=\"%s [%d]\",style=filled,fontsize=12, fillcolor=LightSalmon,shape=box]\n",pch,lvec[i]->name,lvec[i]->din);
      else
	fprintf(fs,"%s [label=\"%s [%d]\",style=filled,fontsize=12, fillcolor=White,shape=box]\n",pch,lvec[i]->name,lvec[i]->din);

    }
    if (lvec[i]->type==2) {
      c=(CLayer *)lvec[i];
      if (lvec[i]->lin==0)
	fprintf(fs,"%s [label=\"%s [%d@%dx%d]\",style=filled,fontsize=12, fillcolor=gray,shape=box]\n",pch,lvec[i]->name,c->nk,c->outr,c->outc);
      else
	fprintf(fs,"%s [label=\"%s [%d@%dx%d]\",style=filled,fontsize=12, fillcolor=steelblue3,shape=box]\n",pch,lvec[i]->name,c->nk,c->kr,c->kc);
    }
    if (lvec[i]->type==3) {
      p=(PLayer *)lvec[i];
      fprintf(fs,"%s [label=\"%s [%dx%d]\",style=filled,fontsize=12, fillcolor=Crimson,shape=box]\n",pch,lvec[i]->name,p->sizer,p->sizec);
    }
    if (lvec[i]->type==4) {
      cat=(CatLayer *)lvec[i];
      fprintf(fs,"%s [label=\"%s [%d@%dx%d]\",style=filled,fontsize=12, fillcolor=darkkhaki,shape=box]\n",pch,lvec[i]->name,cat->nk,cat->outr,cat->outc);
    }
  }

  for(i=0;i<layers;i++) {
    if (lvec[i]->lin==0) {
      strcpy(cad,lvec[i]->name);
      pch = strtok (cad,":");
      pch = strtok (NULL,":");
      fprintf(fs,"Data->%s\n",pch);
    }
  }


  for(i=0;i<layers;i++) {
    strcpy(cad,lvec[i]->name);
    pch = strtok (cad,":");
    pch = strtok (NULL,":");
    for(j=0;j<lvec[i]->lout;j++) {
      if (isIn(lvec[i]->Lout[j])) {
	strcpy(cad2,lvec[i]->Lout[j]->name);
	pch2 = strtok (cad2,":");
	pch2 = strtok (NULL,":");
	fprintf(fs,"%s->%s\n",pch,pch2);
      }
    }
    if ((lvec[i]->lt)&&(isIn(lvec[i]->target))) {

      strcpy(cad2,lvec[i]->target->name);
      pch2 = strtok (cad2,":");
      pch2 = strtok (NULL,":");
      fprintf(fs,"%s->%s [style=\"dashed\"]\n",pch2,pch);
      fprintf(fs,"{rank = same; %s; %s;}\n",pch2,pch);
    }
    
  }

  for(i=0;i<layers;i++) {
    if (lvec[i]->lin==0) {
      strcpy(cad,lvec[i]->name);
      pch = strtok (cad,":");
      pch = strtok (NULL,":");
      for(j=i+1;j<layers;j++) {
	if (lvec[j]->lin==0) {
	  strcpy(cad2,lvec[j]->name);
	  pch2 = strtok (cad2,":");
	  pch2 = strtok (NULL,":");
	  fprintf(fs,"{rank = same; %s; %s;}\n",pch2,pch);
	}
      
      }
    }
  }
  fprintf(fs,"}\n");
  fclose(fs);

}
void Net::resetLayers()
{
  int i;
  for(i=0;i<layers;i++)
    lvec[i]->reset();
}
void Net::resetstats()
{
  int i;
  for(i=0;i<layers;i++)
    lvec[i]->resetstats();
}

void Net::trainmode()
{
  int i;
  for(i=0;i<layers;i++)
    lvec[i]->trainmode();
}
void Net::testmode()
{
  int i;
  for(i=0;i<layers;i++)
    lvec[i]->testmode();
}

void Net::preparebatch(int code)
{
  int i;

  Dtrain->preparebatch(code);

}


void Net::getbatch(Data *Dt)
{
  int i;

  for(i=0;i<layers;i++)
    if (lvec[i]->lin==0)
      lvec[i]->getbatch(Dt);

}

void Net::getbatch(Data *Dt,int s)
{
  int i;

  for(i=0;i<layers;i++)
    if (lvec[i]->lin==0)
      lvec[i]->getbatch(Dt,s);

}


void Net::applygrads()
{
  int i;
  for(i=0;i<layers;i++)
    lvec[i]->applygrads();

}

void Net::setcropmode(int f)
{
  int i;

  fprintf(stderr,"Net %s set cropmode to %d\n",name,f);
  cropmode=f;
}

void Net::setshift(int f)
{
  int i;

  fprintf(stderr,"Net %s set input shift to %d\n",name,f);
  for(i=0;i<layers;i++)
    if (lvec[i]->lin==0)
      lvec[i]->setshift(f);
}
void Net::setbrightness(double f)
{
  int i;

  fprintf(stderr,"Net %s set input brightness to %f\n",name,f);
  for(i=0;i<layers;i++)
    if (lvec[i]->lin==0)
      lvec[i]->setbrightness(f);
}

void Net::setcontrast(double f)
{
  int i;

  fprintf(stderr,"Net %s set input contrast to %f\n",name,f);
  for(i=0;i<layers;i++)
    if (lvec[i]->lin==0)
      lvec[i]->setcontrast(f);
}

void Net::setflip(int f)
{
  int i;

  fprintf(stderr,"Net %s set input flip to %d\n",name,f);
  for(i=0;i<layers;i++)
    if (lvec[i]->lin==0)
      lvec[i]->setflip(f);
}


void Net::setmu(double m)
{
  int i;

  mu=m;
  fprintf(stderr,"Net %s set learning rate to %f\n",name,m);
  for(i=0;i<layers;i++)
    lvec[i]->setmu(m);
}

void Net::setvalues()
{
  int i;

  //mu
  //fprintf(stderr,"Net %s re-set learning rate to %f\r",name,mu);
  for(i=0;i<layers;i++)
    lvec[i]->setmu(mu);
}

void Net::setact(int a)
{
  int i;
  fprintf(stderr,"Net %s set activation type to %d\n",name,a);
  for(i=0;i<layers;i++)
    if ((lvec[i]->lin>0)&&(!lvec[i]->out)&&(!lvec[i]->reshape))
      lvec[i]->setact(a);
}
void Net::setbn(int a)
{
  int i;
  bn=a;
  fprintf(stderr,"Net %s set BN to %d\n",name,a);
  for(i=0;i<layers;i++)
    if ((lvec[i]->lin>0)&&(!lvec[i]->reshape))
      lvec[i]->setbn(a);
}

void Net::setdecay(double f)
{
  fprintf(stderr,"Net %s set decay lr to %f\n",name,f);
  decay=f;
}

void Net::decmu(double decay)
{
  int i;
  for(i=0;i<layers;i++)
    lvec[i]->setmu(lvec[i]->mu*decay);
}
void Net::setmmu(double m)
{
  int i;
  fprintf(stderr,"Net %s set momentum rate to %f\n",name,m);
  for(i=0;i<layers;i++)
    lvec[i]->setmmu(m);
}
void Net::setl2(double m)
{
  int i;
  fprintf(stderr,"Net %s set l2 regularization to %f\n",name,m);
  for(i=0;i<layers;i++)
    lvec[i]->setl2(m);
}
void Net::setl1(double m)
{
  int i;
  fprintf(stderr,"Net %s set l2 regularization to %f\n",name,m);
  for(i=0;i<layers;i++)
    lvec[i]->setl1(m);
}
void Net::setoptim(int l)
{
  int i;

  fprintf(stderr,"Net %s set optimization method to %d\n",name,l);
  for(i=0;i<layers;i++)
    lvec[i]->setoptim(l);
}

void Net::setmaxn(double m)
{
  int i;
  fprintf(stderr,"Net %s set maxnorm rate to %f\n",name,m);
  for(i=0;i<layers;i++)
    lvec[i]->setmaxn(m);

}
void Net::setnoiser(double n)
{
  int i;
  fprintf(stderr,"Net %s set noise rate to %f\n",name,n);
  for(i=0;i<layers;i++)
    lvec[i]->setnoiser(n);

}
void Net::setnoiseb(double n)
{
  int i;
  fprintf(stderr,"Net %s set binary noise rate to %f\n",name,n);
  for(i=0;i<layers;i++)
    lvec[i]->setnoiseb(n);

}
void Net::setnoisesd(double n)
{
  int i;
  fprintf(stderr,"Net %s set noise sd to %f\n",name,n);
  for(i=0;i<layers;i++)
    lvec[i]->setnoisesd(n);

}
void Net::setlambda(double m)
{
  int i;
  fprintf(stderr,"Net %s set l2 regularization to %f\n",name,m);
  for(i=0;i<layers;i++)
    lvec[i]->setlambda(m);
}
void Net::setdrop(double m)
{
  int i;
  fprintf(stderr,"Net %s set dropout rate to %f\n",name,m);
  for(i=0;i<layers;i++)
    if (!lvec[i]->out)
      lvec[i]->setdrop(m);
}
void Net::setthreads(int l)
{
  int i;
  fprintf(stderr,"Net %s set threads to %d\n",name,l);
  for(i=0;i<layers;i++)
    lvec[i]->setthreads(l);
}

void Net::setadvf(double n)
{
  int i;
  fprintf(stderr,"Net %s set adversarial factor to %f\n",name,n);
  for(i=0;i<layers;i++)
    lvec[i]->setadvf(n);

}

void Net::setadv(int l)
{
  int i;
  fprintf(stderr,"Net %s set adversarial mode to %d\n",name,l);

  for(i=0;i<layers;i++)
    lvec[i]->setadv(l);

}

void Net::setaddelta(int l)
{
  int i;
  for(i=0;i<layers;i++)
    if (lvec[i]->adv) lvec[i]->adelta=l;

}


int Net::isIn(Layer *l)
{
  int i;

  for(i=0;i<layers;i++)
    if (lvec[i]==l) return 1;

  return 0;
}


void Net::Init(FILE *f)
{
  int i;

  if (!init) {

    fprintf(stderr,"**** Initializing Net %s\n",name);
    flog=f;

    olayers=0;
    for(i=0;i<layers;i++) {
      if (lvec[i]->out) {
	out[olayers++]=lvec[i];
      }
      lvec[i]->rnet=this;
    }

    build_fts();
    build_bts();
    initialize();

    init=1;
  }


}

  //Forward Topologic sort
void Net::build_fts()
{
  int gin[MAX_LAYERS];
  int ind;
  int it,i,j,k;

  for(i=0;i<layers;i++) {
    gin[i]=0;
    for(j=0;j<lvec[i]->lin;j++)
      if (isIn(lvec[i]->Lin[j]))
	gin[i]++;
  }

  ind=0;
  fprintf(stderr,"Net %s building FTS\n",name);
  for(it=0;it<layers;it++) {

    for(i=0;i<layers;i++) {
      if (gin[i]==0) {
	fts[ind++]=lvec[i];
	fprintf(stderr,"%s,",lvec[i]->name);
	gin[i]=-1;
	for(j=0;j<lvec[i]->lout;j++) {
	  if (isIn(lvec[i]->Lout[j])) {
	    for(k=0;k<layers;k++) {
	      if ((Layer *)lvec[i]->Lout[j]==(Layer *)lvec[k]) gin[k]--;
	    }
	  }
	}
      }

    }

  }
  fprintf(stderr,"\n");

  if (ind!=layers) {fprintf(stderr,"Error fts\n");exit(1);}



}

void Net::forward()
{
  int i;
  struct timespec t0, t1,ft0,ft1;
  double e;

#ifdef USETIME

  if (SHOW_TIME) {
    fprintf(stderr,"===== FORWARD ======\n");
  }
  clock_gettime(CLOCK_MONOTONIC, &ft0);

  for(i=0;i<layers;i++) {
    if (SHOW_TIME) {
      fprintf(stderr,"\t %s Ftime=",fts[i]->name);
      clock_gettime(CLOCK_MONOTONIC, &t0);
    }
    fts[i]->rnet=this;
    fts[i]->forward();
    if (SHOW_TIME) {
      clock_gettime(CLOCK_MONOTONIC, &t1);
      e = (t1.tv_sec - t0.tv_sec);
      e += (t1.tv_nsec - t0.tv_nsec) / 1000000000.0;
      fprintf(stderr,"%g\n",e);
    }
  }

  clock_gettime(CLOCK_MONOTONIC, &ft1);
  e = (ft1.tv_sec - ft0.tv_sec);
  e += (ft1.tv_nsec - ft0.tv_nsec) / 1000000000.0;
  ftime+=e;

  if (SHOW_TIME) {
    fprintf(stderr,"Total Forward=%g acum=%g\n",e,ftime);
    fprintf(stderr,"===================\n\n");
  }
#else
  for(i=0;i<layers;i++) {
    fts[i]->rnet=this;
    fts[i]->forward();
  }

#endif

}

void Net::save(FILE *fe)
{
  int i;

  fprintf(stderr,"Saving Network %s\n",name);

  for(i=0;i<layers;i++) {
    fts[i]->save(fe);
  }
  fclose(fe);
}

void Net::load(FILE *fe)
{
  int i;
  
  fprintf(stderr,"Loading Network %s\n",name);
  
  for(i=0;i<layers;i++) {
    fts[i]->load(fe);
  }
  fclose(fe);
  
}


void Net::copy(Layer *ld,Layer *ls)
{


  if ((ld->type==1)&&(ls->type==1))
    {
      fprintf(stderr,"Copy %s --> %s\n",ls->name,ld->name);

      FLayer *fd,*fs;

      fd=(FLayer*)ld;
      fs=(FLayer*)ls;

      fd->W[0]=fs->W[0];
      fd->b=fs->b;
      
      for(int j=0;j<fd->din;j++) {
	fd->bn_g(j)=fs->bn_g(j);
	fd->bn_b(j)=fs->bn_b(j);
	fd->bn_gmean(j)=fs->bn_gmean(j);
	fd->bn_gvar(j)=fs->bn_gvar(j);
      }
      fd->bnc=fs->bnc;
    }
}

//Backward topologic sort
void Net::build_bts()
{
  int gout[MAX_LAYERS];
  int ind;
  int it,i,j,k;

  for(i=0;i<layers;i++) {
    gout[i]=0;
    for(j=0;j<lvec[i]->lout;j++)
      if (isIn(lvec[i]->Lout[j]))
	gout[i]++;
  }

  ind=0;
  fprintf(stderr,"Net %s building BTS\n",name);
  for(it=0;it<layers;it++) {

    for(i=0;i<layers;i++) {
      if (gout[i]==0) {
	fprintf(stderr,"%s,",lvec[i]->name);
	bts[ind++]=lvec[i];
	gout[i]=-1;

	for(j=0;j<lvec[i]->lin;j++)
	  if (isIn(lvec[i]->Lin[j]))
	    for(k=0;k<layers;k++) {
	      if ((Layer *)lvec[i]->Lin[j]==(Layer *)lvec[k]) gout[k]--;
	    }
      }
    }

  }
  fprintf(stderr,"\n");
  if (ind!=layers) {fprintf(stderr,"Error bts\n");exit(1);}
}

void Net::backward()
{
  struct timespec t0, t1,ft0,ft1;
  double e;

  int i;

#ifdef USETIME

  if (SHOW_TIME) {
    fprintf(stderr,"===== BACKWARD ======\n");
  }
  clock_gettime(CLOCK_MONOTONIC, &ft0);
  for(i=0;i<layers;i++) {
    if (SHOW_TIME) {
      fprintf(stderr,"\t%s Btime=",bts[i]->name);
      clock_gettime(CLOCK_MONOTONIC, &t0);
    }
    bts[i]->rnet=this;
    bts[i]->backward();
    if (SHOW_TIME) {
      clock_gettime(CLOCK_MONOTONIC, &t1);
      e = (t1.tv_sec - t0.tv_sec);
      e += (t1.tv_nsec - t0.tv_nsec) / 1000000000.0;
      fprintf(stderr,"%g\n",e);
    }
  }


  clock_gettime(CLOCK_MONOTONIC, &ft1);
  e = (ft1.tv_sec - ft0.tv_sec);
  e += (ft1.tv_nsec - ft0.tv_nsec) / 1000000000.0;
  btime+=e;

  if (SHOW_TIME) {
    fprintf(stderr,"Total Backward=%g acum=%g\n",e,btime);
    fprintf(stderr,"===================\n\n");
    getchar();
  }
#else
  for(i=0;i<layers;i++) {
    bts[i]->rnet=this;
    bts[i]->backward();
  }
#endif

}




void Net::reseterrors()
{
  int i;
  OFLayer *o;
  
  for(i=0;i<olayers;i++) {
    o=(OFLayer *)out[i];
    o->mse=0.0;
    o->rmse=0.0;
    o->mae=0.0;
    o->cerr=0.0;
    o->ent=0.0;
  }
}


void Net::printerrors(Data *Dt)
{
  printerrors(Dt,Dt->num);
}

void Net::printerrors(Data *Dt,int num)
{
  int i;
  OFLayer *o;

  for(i=0;i<olayers;i++) {
    o=(OFLayer *)out[i];
    if ((!o->lt)||(isIn(o->target))){
      if (o->act==10) {
	fprintf(stderr,"%s Errors (%s) %1.0f of %d  %2.2f%%  CrossEnt=%f\n",Dt->fname,o->name,o->cerr,num,(100.0*o->cerr)/num,o->ent/(num*Dt->out));
	fprintf(flog,"%s Errors (%s) %1.0f of %d  %2.2f%%  CrossEnt=%f\n",Dt->fname,o->name,o->cerr,num,(100.0*o->cerr)/num,o->ent/(num*Dt->out));
      }
      else
	if (o->ae) {
	  fprintf(stderr,"%s AE (%s) MSE=%f  MAE=%f\n",Dt->fname,o->name,o->mse/num,o->mae/num);
	  fprintf(flog,"%s AE (%s) MSE=%f  MAE=%f\n",Dt->fname,o->name,o->mse/num,o->mae/num);
	}
	else {
	  fprintf(stderr,"%s RMSE(%s)=%f  MAE=%f\n",Dt->fname,o->name,o->rmse/num,o->mae/num);
	  fprintf(flog,"%s RMSE(%s)=%f  MAE=%f\n",Dt->fname,o->name,o->rmse/num,o->mae/num);
	}
    }
  }
  fflush(flog);
}




void Net::calcerr(Data *Dt)
{
  int i;
  OFLayer *o;

  for(i=0;i<olayers;i++) {
    o=(OFLayer *)out[i];
    o->get_err(Dt,Dt->batch);
  }
}

void Net::calcerr(Data *Dt,int s)
{
  int i;
  OFLayer *o;

  for(i=0;i<olayers;i++) {
    o=(OFLayer *)out[i];
    o->get_err(Dt,s);
  }
}


void Net::printOut(Data *Dt,FILE *fs,int n)
{
  int i,j,b;
  OFLayer *o;

  for(b=0;b<n;b++) {
    for(i=0;i<olayers;i++) {
      o=(OFLayer *)out[i];
      for(j=0;j<o->din;j++)
	fprintf(fs,"%f ",o->N(b,j));
      for(j=0;j<o->din;j++)
	fprintf(fs,"%f ",o->T(b,j));

    }
    fprintf(fs,"\n");
  }
}




/////////////////////////////////
// TRAINING NETS
/////////////////////////////////
void Net::train(int epochs)
{
  int i,d;
  int epoch;
  int adv=0;

  fprintf(stderr,"Training net %s %d epochs\n",name,epochs);


  for(i=0;i<layers;i++) 
    if (lvec[i]->adv) adv=1;

  if (adv) {
    fprintf(stderr,"Adversarial training\n");
    for(i=0;i<layers;i++) {
      if (lvec[i]->adv) fprintf(stderr,"%s layer has adversarial noise type %d with factor %f\n",lvec[i]->name,lvec[i]->adv,lvec[i]->advf);
    }
  }

  for(epoch=1;epoch<=epochs;epoch++) {
    lut_init();

    reseterrors();
    fprintf(stderr,"Epoch %d:\n",epoch);

    Dtrain->preparebatch(1);
    ftime=0;
    btime=0;
    trainmode();
    if (bn) resetstats();
    for(i=0;i<Dtrain->num/Dtrain->batch;i++) {
      fprintf(stderr,"%d of %d batches\r",i+1,Dtrain->num/Dtrain->batch);
      /////Layer %s setting noiser %f\n",name,
      resetLayers();
      /////
      getbatch(Dtrain);
      /////
      forward();
      /////
      backward();
      /////
      if (!adv) {
	calcerr(Dtrain);
	applygrads();
      }
      else {
	setaddelta(1);
	/////
	resetLayers();
	/////
	getbatch(Dtrain);
	/////
	forward();
	/////
	calcerr(Dtrain);
	/////
	backward();
	/////
	applygrads();
	/////
	setaddelta(0);
      }
     
      /////
      Dtrain->next();
      if (VERBOSE) getchar();

    }

    fprintf(stderr,"---------------------------------------\n");
    fprintf(stderr,"Forward %g secs\n",ftime);
    fprintf(stderr,"Forward %g secs/batch\n",ftime/(Dtrain->num/Dtrain->batch));

    fprintf(stderr,"Backward %g secs\n",btime);
    fprintf(stderr,"Backward %g secs/batch\n",btime/(Dtrain->num/Dtrain->batch));
    fprintf(stderr,"Total= %g secs\n",ftime+btime);
    fprintf(stderr,"Total= %g secs/batch\n",(ftime+btime)/(Dtrain->num/Dtrain->batch));
    fprintf(stderr,"---------------------------------------\n");

    printerrors(Dtrain);

    // VAL
    if (Dval!=NULL)  evaluate(Dval);

    //TEST
    if (Dtest!=NULL) evaluate(Dtest);

    decmu(decay);
  }

  //fclose(flog);
}


void Net::evaluate(Data *Dt)
{
  int i;

  //////////////////////////////
  testmode();
  Dt->preparebatch(0);
  reseterrors();

  for(i=0;i<Dt->num/Dt->batch;i++) {
    fprintf(stderr,"%d of %d batches\r",i+1,Dt->num/Dt->batch);
    resetLayers();
    getbatch(Dt);
    forward();
    calcerr(Dt);
    Dt->next();
  }
  if (Dt->num%Dt->batch) {
    fprintf(stderr,"...\n");
    resetLayers();
    getbatch(Dt);
    forward();
    calcerr(Dt,Dt->num%Dt->batch);    
  }
  printerrors(Dt);

  
}
void Net::testOut(FILE *fs)
{
  int i,j;

  if (Dtest!=NULL) {
    fprintf(stderr,"writting test output\n");
    testmode();
    Dtest->preparebatch(0);
    for(i=0;i<Dtest->num/Dtest->batch;i++) {
      fprintf(stderr,"%d of %d batches\r",i+1,Dtest->num/Dtest->batch);
      resetLayers();
      getbatch(Dtest);
      forward();
      calcerr(Dtest); // to update Targets needed in printOut
      printOut(Dtest,fs,Dtest->batch);
      Dtest->next();
    }
    // last batch
    if (Dtest->num%Dtest->batch) {
      fprintf(stderr,"...\n");
      resetLayers();
      getbatch(Dtest);
      forward();
      calcerr(Dtest,Dtest->num%Dtest->batch);    
      printOut(Dtest,fs,Dtest->num%Dtest->batch);
    }
  }

  fclose(fs);

}


void Net::fillData(Data *D,Layer *l1,Layer *l2)
{
  int i,it,k;


  fprintf(stderr,"Forward to Data %s,%d -> %s,%d\n",l1->name,l1->din,l2->name,l2->din);

  testmode();
  Dtrain->preparebatch(0);
  for(i=0;i<Dtrain->num/Dtrain->batch;i++) {
    fprintf(stderr,"%d of %d batches\r",i+1,Dtrain->num/Dtrain->batch);
    resetLayers();
    getbatch(Dtrain);
    forward();
    l1->fillData(D,i);
    l2->fillTarget(D,i);
    Dtrain->next();
  }
  // last samples not complete batch
  if (Dtrain->num%Dtrain->batch) {
    resetLayers();
    getbatch(Dtrain);
    forward();
    l1->fillData(D,i);
    l2->fillTarget(D,i);
    Dtrain->next();
  }
  fprintf(stderr,"\n");
}


///////////////////////////////////////////
// FOR TRAINIG SEVERAL NETS FROM MAIN
///////////////////////////////////////////
void Net::trainbatch(int b,int epoch)
{
  int i,d;
  int adv=0,bn;

  fprintf(stderr,"Epoch %d: training %s %d batches\r",epoch+1,name,b);

  //setvalues();

  for(i=0;i<layers;i++) 
    if (lvec[i]->adv) adv=1;

  for(i=0;i<layers;i++) 
    if (lvec[i]->bn) bn=1;

  trainmode();
  if (bn) resetstats();
  for(i=0;i<b;i++) {
    /////Layer %s setting noiser %f\n",name,
    resetLayers();
    /////
    getbatch(Dtrain);
    /////
    forward();
    /////
    backward();
    /////
    if (!adv) {
      calcerr(Dtrain);
      /////
      applygrads();
    }
    else {
      setaddelta(1);
      /////
      resetLayers();
      /////
      getbatch(Dtrain);
      /////
      forward();
      /////
      calcerr(Dtrain);
      /////
      backward();
      /////
      applygrads();
      /////
      setaddelta(0);
    }
     
    /////
    Dtrain->next();
    if (VERBOSE) getchar();

  }
  
  decmu(decay);
}




