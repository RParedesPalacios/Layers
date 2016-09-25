#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <iostream>

#include "Eigen/Dense"

#include "layer.h"
#include "net.h"

#include "utils.h"

#define VERBOSE 0


// Eigen

using namespace Eigen;
using namespace std;

////////////////////////////////////
///// FULLY CONNECTED LAYER CLASS
////////////////////////////////////

FLayer::FLayer()
{

}

FLayer::FLayer(int in,int batch,char *name):Layer(batch,name)
{

  din=in;
  type=1;
  act=1;

  if (in<=0) {
    fprintf(stderr,"Error %s with %d neurons\n",name,in);
    exit(1);
  }

  W=new LMatrix[MAX_CONNECT];
  gW=new LMatrix[MAX_CONNECT];
  pgW=new LMatrix[MAX_CONNECT];
  b=new LRVector[MAX_CONNECT];
  gb=new LRVector[MAX_CONNECT];
  pgb=new LRVector[MAX_CONNECT];
  MT=new LMatrix[MAX_CONNECT];
  VT=new LMatrix[MAX_CONNECT];
  MTs=new LMatrix[MAX_CONNECT];
  VTs=new LMatrix[MAX_CONNECT];

  N.resize(batch,in);
  E.resize(batch,in);
  dE.resize(batch,in);
  Delta.resize(batch,in);
  dvec.resize(in);

  //BN

  bn_mean.resize(in);
  bn_var.resize(in);
  bn_gmean.resize(in);
  bn_gvar.resize(in);
  bn_g.resize(in);
  bn_b.resize(in);
  bn_E.resize(batch,in);
  BNE.resize(batch,in);

  gbn_mean.resize(in);
  gbn_var.resize(in);
  gbn_g.resize(in);
  gbn_b.resize(in);
  gbn_E.resize(batch,in);


  fprintf(stderr,"Creating FC layer (%s) with %d neurons\n",name,in);

}

//Reshape Layer
FLayer::FLayer(Layer *In,int batch,char *name):Layer(batch,name)
{
  CLayer *cin;

  if (In->type>1) {
    cin=(CLayer *)In;
    din=cin->outz*cin->outr*cin->outc;
    reshape=1;
    if (din<=0) {
      fprintf(stderr,"Error %s with %d neurons\n",name,din);
      exit(1);
    }
  }
  else {
    fprintf(stderr,"Error building %s with %s, not convolutional\n",name,In->name);
    exit(1);
  }

  type=1;
  // Linear
  act=0;

  W=new LMatrix[MAX_CONNECT];
  gW=new LMatrix[MAX_CONNECT];
  pgW=new LMatrix[MAX_CONNECT];
  b=new LRVector[MAX_CONNECT];
  gb=new LRVector[MAX_CONNECT];
  pgb=new LRVector[MAX_CONNECT];
  MT=new LMatrix[MAX_CONNECT];
  VT=new LMatrix[MAX_CONNECT];
  MTs=new LMatrix[MAX_CONNECT];
  VTs=new LMatrix[MAX_CONNECT];

  N.resize(batch,din);
  E.resize(batch,din);
  dE.resize(batch,din);
  Delta.resize(batch,din);
  dvec.resize(din);

  //BN

  bn_mean.resize(din);
  bn_var.resize(din);
  bn_gmean.resize(din);
  bn_gvar.resize(din);
  bn_g.resize(din);
  bn_b.resize(din);
  bn_E.resize(batch,din);
  BNE.resize(batch,din);

  gbn_mean.resize(din);
  gbn_var.resize(din);
  gbn_g.resize(din);
  gbn_b.resize(din);
  gbn_E.resize(batch,din);

  fprintf(stderr,"Creating Reshape layer (%s) with %d neurons\n",name,din);

  In->addchild(this);

}

//Local Layer
FLayer::FLayer(Layer *In,int lr,int lc,char *name):Layer(0,name)
{
  CLayer *cin;

  if (In->type>1) {
    cin=(CLayer *)In;
    this->lr=lr;
    this->lc=lc;
    din=lr*lc*cin->outz+2;
    fprintf(stderr,"Local reshape %d %d %d %d %d\n",cin->batch, cin->outr, cin->outc,lr,lc);
    batch=cin->batch*((cin->outr-lr)+1)*((cin->outc-lc)+1);
    lm=((cin->outr-lr)+1)*((cin->outc-lc)+1);
    ld=4*lr*lc;
    fprintf(stderr,"Local lm=%d, Local ld=%d\n",lm,ld);
    local=1;
    if (din<=0) {
      fprintf(stderr,"Error %s with %d neurons\n",name,din);
      exit(1);
    }
  }
  else {
    fprintf(stderr,"Error building local FC %s with %s, not convolutional\n",name,In->name);
    exit(1);
  }

  type=1;
  // Linear
  act=0;

  W=new LMatrix[MAX_CONNECT];
  gW=new LMatrix[MAX_CONNECT];
  pgW=new LMatrix[MAX_CONNECT];
  MT=new LMatrix[MAX_CONNECT];
  VT=new LMatrix[MAX_CONNECT];
  MTs=new LMatrix[MAX_CONNECT];
  VTs=new LMatrix[MAX_CONNECT];
  b=new LRVector[MAX_CONNECT];
  gb=new LRVector[MAX_CONNECT];
  pgb=new LRVector[MAX_CONNECT];

  N.resize(batch,din);
  E.resize(batch,din);
  dE.resize(batch,din);
  Delta.resize(batch,din);
  dvec.resize(din);

  fprintf(stderr,"Creating Reshape Local layer (%s) batch %d with %d neurons\n",name,batch,din);

  In->addchild(this);

}

void FLayer::modbatch(int b)
{
  fprintf(stderr,"Layer %s mod batch %d->%d\n",name,batch,b);
  batch=b;

  if (D!=NULL) T.resize(batch,din);
  N.resize(batch,din);
  E.resize(batch,din);
  dE.resize(batch,din);
  Delta.resize(batch,din);

  bn_E.resize(batch,din);
  BNE.resize(batch,din);
  gbn_E.resize(batch,din);
}




void FLayer::addchild(Layer *li)
{

  int enc=0;
  for(int i=0;i<lout;i++)
    if (Lout[i]==li) enc=1;

  if (enc) {
    fprintf(stderr,"%s->%s just connected\n",this->name,li->name);
  }
  else {

    if (li->type==1) {
      FLayer *l=(FLayer *)li;

      Lout[lout]=l;

      W[lout].resize(din,l->din);
      b[lout].resize(l->din);
      gW[lout].resize(din,l->din);

      MT[lout].resize(din,l->din);
      VT[lout].resize(din,l->din);
      MTs[lout].resize(din,l->din);
      VTs[lout].resize(din,l->din);

      pgW[lout].resize(din,l->din);
      pgW[lout].setZero();

      gb[lout].resize(l->din);
      pgb[lout].resize(l->din);
      pgb[lout].setZero();

      lout++;

      fprintf(stderr,"Connecting %s --> %s\n",name,li->name);
      l->addparent(this);
    }
    else {
      fprintf(stderr,"Error: %s->%s Only FC can be connected after FC\n",name,li->name);
      exit(1);
    }
  }

}


void FLayer::addparent(Layer *l)
{
  if ((lin>0)&&((reshape)||(local))) {
    fprintf(stderr,"Error, reshape layer (%s) can only have one parent layer, (%s)\n",name,l->name);
    exit(1);
  }

  if (!local)
    if (l->batch!=batch) {
      modbatch(l->batch);
      lm=l->lm;
      ld=l->ld;
    }

  Lin[lin]=l;
  lin++;

}


void FLayer::initialize()
{
  int i,j;
  int k;
  double s;

  if (!init) {
    for(k=0;k<lout;k++) {
      s=sqrt(2.0/W[k].cols());
      for(j=0;j<W[k].cols();j++)
	for(i=0;i<W[k].rows();i++)
	  W[k](i,j)=s*gauss(0,1);

      for(j=0;j<b[k].cols();j++)
	b[k](j)=0.1;

      MT[k].setZero();
      VT[k].setZero();
      MTs[k].setZero();
      VTs[k].setZero();
      ab1t=1.0;
      ab2t=1.0;
    }

    if ((!local)&&(!reshape))
      for(i=0;i<din;i++) {
	bn_g(i)=1.0;
	bn_b(i)=0.0;
      }

    init=1;
  }

}

void FLayer::resetmomentum()
{
  int k;

  if (VERBOSE) fprintf(stderr,"layer %s reset momentum\n",name);

  for(k=0;k<lout;k++) {
    pgW[k].setZero();
    pgb[k].setZero();
  }

}

void FLayer::reset()
{
  int k;

  if (VERBOSE) fprintf(stderr,"RESET Layers\n");

  E.setZero();
  N.setZero();
  Delta.setZero();

  for(k=0;k<lout;k++) {
    gW[k].setZero();

    gb[k].setZero();
  }


}
void FLayer::resetstats()
{
  bnc=0;

  bn_gmean.setZero();
  bn_gvar.setZero();

}

//////////////////////
///// FORWARD
//////////////////////

void FLayer::fBN()
{

  if (trmode) {
    bnc++;
    //#pragma omp parallel for
    for(int i=0;i<din;i++) {
      int b;
      double m,var,eps=0.00001;

      m=0;
      for(b=0;b<batch;b++)
	m+=E(b,i);
      m/=batch;
      bn_mean(i)=m;

      var=0;
      for(b=0;b<batch;b++)
	var+=(m-E(b,i))*(m-E(b,i));
      var/=batch;
      bn_var(i)=var;

      for(b=0;b<batch;b++) {
	bn_E(b,i)=(E(b,i)-bn_mean(i))/sqrt(bn_var(i)+eps); //this is \hat{x}
	if (noiser>0.0)
	  if (uniform()<noiser)
	    bn_E(b,i)+=gauss(0.0,noisesd);
	BNE(b,i)=(bn_g(i)*bn_E(b,i))+bn_b(i);
      }
    }
    bn_gmean+=bn_mean;
    bn_gvar+=bn_var;
  }
  else { // testmode
    //#pragma omp parallel for
    for(int i=0;i<din;i++) {
      int b;
      double var,eps=0.00001;

      for(b=0;b<batch;b++){
	bn_E(b,i)=(E(b,i)-bn_gmean(i)/bnc)/sqrt(bn_gvar(i)/bnc+eps);
	BNE(b,i)=(bn_g(i)*bn_E(b,i))+bn_b(i);
      }
    }
  }
}

void FLayer::doActivation()
{
  int i,j;

  if (VERBOSE) {
    if (bn) fprintf(stderr,"BNE(%s) = %f\n",name,BNE.norm());
    else fprintf(stderr,"E(%s) = %f\n",name,E.norm());
  }


  if (!bn)
    if (trmode) {
      if (noiser>0.0) {
	//#pragma omp parallel for
	for(int i=0;i<batch;i++)
	  for(int j=0;j<din;j++)
	    if (uniform()<noiser)
	      E(i,j)+=gauss(0.0,noisesd);

      }
    }


  if (bn) {
    if (act==0) N=BNE;
    if (act==1) ReLu(BNE,N);
    if (act==2) Sigmoid(BNE,N);
    if (act==3) ELU(BNE,N,1.0);
    if (act==10) Softmax(BNE,N);
    if (act==11) N=BNE;
  }
  else {
    if (act==0) N=E;
    if (act==1) ReLu(E,N);
    if (act==2) Sigmoid(E,N);
    if (act==3) ELU(E,N,1.0);
    if (act==10) Softmax(E,N);
    if (act==11) N=E;
  }


  // For output

  if (VERBOSE) {
    fprintf(stderr,"N(%s,%d) = %f\n",name,act,N.norm());
    if (N.norm()==0) getchar();
  }


  // drop-out on trmode for input and hidden
  if (drop>0.0) {
    if (trmode) {
      dvec.setZero();
      for(i=0;i<din;i++)
	if (uniform()>drop) dvec(i)=1;

      if (VERBOSE) fprintf(stderr,"Drop N %s(%d)\n",name,act);
      for(j=0;j<din;j++)
	if (dvec(j)==0)
	  for(i=0;i<batch;i++) N(i,j)=0.0;
    }
    else {
      N*=(1.0-drop);
    }

  }

  if (VERBOSE) fprintf(stderr,"N(%s) = %f\n",name,N.norm());

}


void FLayer::forward()
{
  int k,i,j,z,r,c;
  FLayer *l;
  CLayer *cin;

  if (reshape) {
    cin=(CLayer *)Lin[0];
    for(k=0;k<batch;k++) {
      j=0;
      for(z=0;z<cin->outz;z++)
	for(r=0;r<cin->outr;r++)
	  for(c=0;c<cin->outc;c++,j++)
	    E(k,j)=cin->N[k][z](r,c);
    }
    if (VERBOSE) fprintf(stderr,"from CNN (%s) E(%s) = %f\n",cin->name,name,E.norm());
  }
  else if (local) {
    cin=(CLayer *)Lin[0];
    int b=0,r2,c2;

    for(k=0;k<cin->batch;k++) {
      for(r=0;r<(cin->outr-lr)+1;r++)
	for(c=0;c<(cin->outc-lc)+1;c++,b++) {
	  j=0;
	  for(r2=0;r2<lr;r2++)
	    for(c2=0;c2<lc;c2++)
	      for(z=0;z<cin->outz;z++,j++)
		E(b,j)=cin->N[k][z](r+r2,c+c2);
	  E(b,j)=(double)r/(double)cin->outr;
	  E(b,j+1)=(double)c/(double)cin->outc;
	}
    }

    if (VERBOSE) fprintf(stderr,"from CNN Local (%s) E(%s) = %f\n",cin->name,name,E.norm());
  }
  else if (bn) fBN();

  doActivation();

  setNbThreads(threads);
  for(i=0;i<lout;i++) {
    if (rnet->isIn(Lout[i])) {
      if (Lout[i]->type==1) {
	l=(FLayer *)Lout[i];
	l->E+=N*W[i];
	l->E.rowwise()+=b[i];
      }
    }
  }
  setNbThreads(1);
}

void FLayer::save(FILE *fe)
{
  int k,i,j;

  save_param(fe);

  for(k=0;k<lout;k++) {
    for(i=0;i<din;i++)
      for(j=0;j<Lout[k]->din;j++)
	fprintf(fe,"%f ",W[k](i,j));
    for(j=0;j<Lout[k]->din;j++)
      fprintf(fe,"%f ",b[k](j));
    fprintf(fe,"\n");
  }

}

void FLayer::printkernels(FILE *fe)
{
  int k,i,j;

  for(k=0;k<lout;k++) {
    for(i=0;i<din;i++)
      for(j=0;j<Lout[k]->din;j++)
	fprintf(fe,"%f ",W[k](i,j));
    fprintf(fe,"\n");
  }

  fclose(fe);
}

void FLayer::load(FILE *fe)
{
  int k,i,j;
  double fv;
  int fsd;

  load_param(fe);

  for(k=0;k<lout;k++) {
    for(i=0;i<din;i++)
      for(j=0;j<Lout[k]->din;j++) {
	fsd=fscanf(fe,"%lf ",&fv);
	W[k](i,j)=fv;
      }
    for(j=0;j<Lout[k]->din;j++) {
      fsd=fscanf(fe,"%lf ",&fv);
      b[k](j)=fv;
    }
    fsd=fscanf(fe,"\n");
  }

}


//////////////////////////////////////////
///// BACKWARD
//////////////////////////////////////////
void FLayer::bBN()
{
  //#pragma omp parallel for
  for(int i=0;i<din;i++) {
    int b;
    double m,var,eps=0.00001;
    double sqvar,var32;

    m=batch;

    //1 Gamma
    gbn_g(i)=0.0;
    for(b=0;b<batch;b++)
      gbn_g(i)+=Delta(b,i)*bn_E(b,i);

    //2 Beta
    gbn_b(i)=0.0;
    for(b=0;b<batch;b++)
      gbn_b(i)+=Delta(b,i);


    //3 bnE
    for(b=0;b<batch;b++)
      gbn_E(b,i)=Delta(b,i)*bn_g(i);


    //4 Var
    sqvar=sqrt(bn_var(i)+eps);
    var32=(bn_var(i)+eps)*sqvar;

    gbn_var(i)=0;
    for(b=0;b<batch;b++)
      gbn_var(i)+=-0.5*gbn_E(b,i)*(E(b,i)-bn_mean(i))/var32;


    //5 Mean
    gbn_mean(i)=0;
    for(b=0;b<batch;b++) {
      gbn_mean(i)+=-gbn_E(b,i)/sqvar;
      //gbn_mean(i)+=-2*gbn_var(i)*(E(b,i)-bn_mean(i))/m;
    }

    //6 x
    for(b=0;b<batch;b++) {
      Delta(b,i)=gbn_E(b,i)/sqvar;
      Delta(b,i)+=gbn_var(i)*2*(E(b,i)-bn_mean(i))/m;
      Delta(b,i)+=gbn_mean(i)/m;
    }



  }


}


void FLayer::dactivation()
{

  if (bn) {
    if (act==0) {
      for(int i=0;i<batch;i++)
	for(int j=0;j<din;j++)
	  dE(i,j)=1;
    }
    else if (act==1) {
      for(int i=0;i<batch;i++)
	for(int j=0;j<din;j++)
	  if (BNE(i,j)<=0) dE(i,j)=0;
	  else dE(i,j)=1;
    }
    else if (act==2)  {
      for(int i=0;i<batch;i++)
	for(int j=0;j<din;j++)
	  dE(i,j)=dsigm(BNE(i,j));
    }
    else if (act==3)  {
      for(int i=0;i<batch;i++)
	for(int j=0;j<din;j++)
	  if (BNE(i,j)<=0) dE(i,j)=N(i,j)+1;
	  else dE(i,j)=1;
    }
    else {
      fprintf(stderr,"Error dactivation (%s)\n",name);
      exit(1);
    }
  }
  else {
    if (act==0) {
      for(int i=0;i<batch;i++)
	for(int j=0;j<din;j++)
	  dE(i,j)=1;
    }
    else if (act==1) {
      for(int i=0;i<batch;i++)
	for(int j=0;j<din;j++)
	  if (E(i,j)<=0) dE(i,j)=0;
	  else dE(i,j)=1;
    }
    else if (act==2)  {
      for(int i=0;i<batch;i++)
	for(int j=0;j<din;j++)
	  dE(i,j)=dsigm(E(i,j));
    }
    else if (act==3)  {
      for(int i=0;i<batch;i++)
	for(int j=0;j<din;j++)
	  if (E(i,j)<=0) dE(i,j)=N(i,j)+1;
	  else dE(i,j)=1;
    }
    else {
      fprintf(stderr,"Error dactivation (%s)\n",name);
      exit(1);
    }

  }


}


void FLayer::backward()
{
  int i,j,k,ind,b,c,r,z;
  double sum;
  FLayer *l;
  CLayer *cnn;
  CatLayer *cat;
  PLayer *mp;


  if (drop>0.0) {
      if (VERBOSE) fprintf(stderr,"Drop Delta %s(%d)\n",name,act);
      for(j=0;j<din;j++)
	if (dvec(j)==0)
	  for(i=0;i<batch;i++) Delta(i,j)=0.0;
  }


  if (reshape) {
    cnn=(CLayer *)Lin[0];
    for(b=0;b<batch;b++) {
      j=0;
      for(z=0;z<cnn->outz;z++)
	for(r=0;r<cnn->outr;r++)
	  for(c=0;c<cnn->outc;c++,j++) {
	    cnn->De[b][z](r,c)+=Delta(b,j);
	  }
    }
    if (VERBOSE) {
      fprintf(stderr,"%s Delta norm %f\n",name,Delta.norm());
    }
  }
  else if (local) {
    cnn=(CLayer *)Lin[0];
    int b=0,r2,c2;
    for(k=0;k<cnn->batch;k++) {
      for(r=0;r<(cnn->outr-lr)+1;r++)
	for(c=0;c<(cnn->outc-lc)+1;c++,b++) {
	  j=0;
	  for(r2=0;r2<lr;r2++)
	    for(c2=0;c2<lc;c2++)
	      for(z=0;z<cnn->outz;z++,j++)
		cnn->De[k][z](r+r2,c+c2)+=Delta(b,j);
	}
    }
    if (VERBOSE) {
      fprintf(stderr,"%s Delta Local norm %f\n",name,Delta.norm());
    }

  }
  else { //!reshape

    if (VERBOSE) {
      sum=Delta.norm();
      fprintf(stderr,"%s Delta norm %f\n",name,sum);
    }


    // Delta*DerivAct
    if (!out) { // To prevent for output layers
      dactivation();
      for(int b=0;b<batch;b++)
	for(int j=0;j<din;j++)
	  Delta(b,j)*=dE(b,j);
    }


    if (bn) bBN();

    setNbThreads(threads);
    for(i=0;i<lin;i++) {
      if (rnet->isIn(Lin[i])) {
	if (Lin[i]->type==1) { // Fully connected
	  l=(FLayer *)Lin[i];

	  ind=-1;
	  for(k=0;k<l->lout;k++)
	    if ((Layer *)l->Lout[k]==(Layer *)this) ind=k;
	  if (ind==-1) {fprintf(stderr,"Error no connection!!\n"); exit(1);}

	  // Compute grads
	  if (VERBOSE) {
	    fprintf(stderr,"%f %f -->\n",l->N.norm(),Delta.norm());
	  }
	  //noalias
	  l->gW[ind]+=l->N.transpose()*Delta;

	  if (VERBOSE) {
	    fprintf(stderr,"gW %s = %f\n",l->name,l->gW[ind].norm());
	  }

	  for(j=0;j<l->gb[ind].cols();j++)
	    l->gb[ind](j)+=Delta.col(j).sum();

	  // back-propagate Delta
	  //noalias
	  l->Delta+=(Delta*l->W[ind].transpose());
	}
      }
    }
    setNbThreads(1);
  }
}



void FLayer::applygrads()
{
  int k,i,j;
  double inc;
  double sum=0;


  for(k=0;k<lout;k++) {

    // WEIGHTS
    if (optim==1) {//MOMENTUM
      pgW[k]=(mu/batch)*gW[k]+mmu*pgW[k];
      W[k]+=pgW[k];

    }
    else if (optim==2) { //ADAM
      ab1t*=ab1;
      ab2t*=ab2;
      for(i=0;i<W[k].rows();i++)
	for(j=0;j<W[k].cols();j++) {
	  MT[k](i,j)=(ab1*MT[k](i,j))+(1-ab1)*gW[k](i,j);
	  VT[k](i,j)=(ab2*VT[k](i,j))+(1-ab2)*(gW[k](i,j)*gW[k](i,j));
	  MTs[k](i,j)=MT[k](i,j)/(1-ab1t);
	  VTs[k](i,j)=VT[k](i,j)/(1-ab2t);
	}
      for(i=0;i<W[k].rows();i++)
	for(j=0;j<W[k].cols();j++)
	  W[k](i,j)+=(mu/batch)*MTs[k](i,j)/(sqrt(VTs[k](i,j))+aeps);
    }

    // REGULARIZATION
    if (l2!=0.0)
      W[k]-=l2*W[k];

    if (maxn>0.0)
      for(i=0;i<W[k].cols();i++) {
	if (W[k].col(i).norm()>maxn) {
	  W[k].col(i)=(maxn/W[k].col(i).norm())*W[k].col(i);
	}
      }

    if (l1!=0.0) {
      for(i=0;i<W[k].rows();i++)
	for(j=0;j<W[k].cols();j++)
	  if (W[k](i,j)<0.0) W[k](i,j)+=l1;
	  else W[k](i,j)-=l1;
    }

    // BIAS
    pgb[k]=(mu/batch)*gb[k]+mmu*pgb[k];
    b[k]+=pgb[k];

    gW[k].setZero();
    gb[k].setZero();

  }


  // BATCH NORM g,b
  if (bn) {
    for(i=0;i<din;i++) {
      bn_g(i)+=(mu/batch)*gbn_g(i);
      bn_b(i)+=(mu/batch)*gbn_b(i);
    }
  }

}



////////////////////////////////////////////////////////////////
/// INPUT FULLY CONNECTED LAYER
////////////////////////////////////////////////////////////////
IFLayer::IFLayer(Data *D,int b,char *name):FLayer(D->dim,b,name)
{
  this->D=D;
  // Linear
  act=0;

  fprintf(stderr,"Creating Input FC layer (%s) with %d neurons\n",name,din);

}

void IFLayer::getbatch(Data *Dt)
{
  int i,j,c;
  double fv;

  for(i=0;i<batch;i++)
    for(j=0;j<din;j++)
      E(i,j)=Dt->M(Dt->getpos(i),j);


  //Noise for binary input
  if (trmode) {
    if (noiseb>0.0)
      for(int i=0;i<batch;i++)
	for(int j=0;j<din;j++)
	  if (uniform()<noiseb)
	    if (E(i,j)) E(i,j)=0.0;
	    else E(i,j)=1.0;
  }

}

void IFLayer::addparent(Layer *l) {
  fprintf(stderr,"Error: Input FC Layer (%s) can not have parent layer\n",name);
  exit(1);

}
//void IFLayer::forward();
void IFLayer::backward() {
  return;
}

//void IFLayer::initialize();
//void IFLayer::applygrads();
//void IFLayer::reset();



////////////////////////////////////////////////////////////////
/// OUTPUT FULLY CONNECTED LAYER
////////////////////////////////////////////////////////////////

OFLayer::OFLayer(Data *D,int b,int act,char *name):FLayer(D->out,b,name)
{
  this->ae=0;
  T.resize(batch,din);
  this->D=D;
  this->act=act;
  out=1;
  if (act==10)
    fprintf(stderr,"Creating Onput FC layer CLASS (%s) with %d neurons\n",name,din);
  else
    fprintf(stderr,"Creating Onput FC layer REG (%s) with %d neurons\n",name,din);
}
OFLayer::OFLayer(Data *D,int b,int act,int ae,char *name):FLayer(D->dim,b,name)
{
  this->ae=ae;
  T.resize(batch,din);
  this->D=D;
  out=1;
  this->act=act;
  if (act==10){
    fprintf(stderr,"Autoencoder %s can not have softmax activation\n",name);
    exit(1);
  }
  else {
    fprintf(stderr,"Creating Onput FC layer REG (%s) with %d neurons\n",name,din);
  }
}

void OFLayer::modbatch(int b)
{
  fprintf(stderr,"Output Layer %s mod batch %d->%d\n",name,batch,b);
  batch=b;

  T.resize(batch,din);
}


/*void OFLayer::forward()
{
  int i;

  if (bn) fBN();
  doActivation();
}
*/

double OFLayer::get_err(Data *Dt)
{
  int i,j,k,p;
  int rindex;
  int nindex;
  double err;


  if (lm) {
    p=0;
    if (ae)
      for(i=0;i<batch/lm;i++)
	for(k=0;k<lm;k++,p++)
	  for(j=0;j<din;j++)
	    T(p,j)=Dt->M(Dt->getpos(i),j);
    else
      for(i=0;i<batch/lm;i++)
	for(k=0;k<lm;k++,p++)
	  for(j=0;j<din;j++)
	    T(p,j)=Dt->T(Dt->getpos(i),j);

  }
  else {
    if (ae)
      for(i=0;i<batch;i++)
	for(j=0;j<din;j++)
	  T(i,j)=Dt->M(Dt->getpos(i),j);
    else
      for(i=0;i<batch;i++)
	for(j=0;j<din;j++)
	  T(i,j)=Dt->T(Dt->getpos(i),j);
  }

  if (lm) {
    int b=batch/lm;
    LMatrix T2;
    LMatrix N2;

    T2.resize(b,din);
    N2.resize(b,din);

    for(i=0;i<b;i++)
      for(j=0;j<din;j++) {
	N2(i,j)=0.0;
	T2(i,j)=0.0;
	for(k=i*lm;k<(i+1)*lm;k++) {
	  T2(i,j)+=T(k,j);
	  N2(i,j)+=N(k,j);
	}
	T2(i,j)/=lm;
	N2(i,j)/=lm;
      }

    if (act==10) {
      for(i=0;i<b;i++) {
	T2.row(i).maxCoeff(&rindex);
	N2.row(i).maxCoeff(&nindex);
	if (rindex!=nindex) cerr++;
	for(j=0;j<din;j++) {
	  if (j==rindex) {if (N2(i,j)!=0.0) ent+=log(N2(i,j));}
	  else if (N2(i,j)!=1.0) ent+=log(1-N2(i,j));
	}
      }
    }
    else{
      for(i=0;i<b;i++)
	mse+=((T2.row(i)-N2.row(i)).squaredNorm())/din;

      for(i=0;i<b;i++)
	rmse+=sqrt(((T2.row(i)-N2.row(i)).squaredNorm())/din);

      for(i=0;i<b;i++)
	for(j=0;j<din;j++)
	  mae+=fabs(T2(i,j)-N2(i,j))/din;
    }
  }
  else {
    if (act==10) {
      for(i=0;i<batch;i++) {
	T.row(i).maxCoeff(&rindex);
	N.row(i).maxCoeff(&nindex);
	if (rindex!=nindex) cerr++;
	for(j=0;j<din;j++) {
	  if (j==rindex) {if (N(i,j)!=0.0) ent+=log(N(i,j));}
	  else if (N(i,j)!=1.0) ent+=log(1-N(i,j));
	}
      }
    }
    else{
      for(i=0;i<batch;i++)
	for(j=0;j<din;j++)
	  mse+=(T(i,j)-N(i,j))*(T(i,j)-N(i,j))/din;

      for(i=0;i<batch;i++)
	rmse+=sqrt(((T.row(i)-N.row(i)).squaredNorm())/din);

      for(i=0;i<batch;i++)
	for(j=0;j<din;j++)
	  mae+=fabs(T(i,j)-N(i,j))/din;
    }
  }

  return 0.0;

}

void OFLayer::backward()
{
  int i,j,k,p;
  double sum;

  if (!lm) {
    if (ae)
      for(i=0;i<batch;i++)
	for(j=0;j<din;j++)
	  T(i,j)=D->M(D->getpos(i),j);
    else
      for(i=0;i<batch;i++)
	for(j=0;j<din;j++)
	  T(i,j)=D->T(D->getpos(i),j);

  }
  else {
    p=0;
    if (ae)
      for(i=0;i<batch/lm;i++)
	for(k=0;k<lm;k++,p++)
	  for(j=0;j<din;j++)
	    T(p,j)=D->M(D->getpos(i),j);
    else
      for(i=0;i<batch/lm;i++)
	for(k=0;k<lm;k++,p++)
	  for(j=0;j<din;j++)
	    T(p,j)=D->T(D->getpos(i),j);
  }

  if (act==10) {// Softmax, CrossEnt
    if (lout>0) {
      for(i=0;i<batch;i++)
	for(j=0;j<din;j++)
	  Delta(i,j)*=(N(i,j)-(N(i,j)*N(i,j))); //deriv softmax w.r.t pre-activation: y_i-(y_i)^2
    }
    Delta+=(T-N)*lambda;
  }

  if (act==11) {// Linear, MSE
    //if (lout>0) Delta*=1; //deriv linear w.r.t pre-activation: 1
    Delta+=2*(T-N)*lambda;
  }

  FLayer::backward();

}


  //  virtual void addparent(Layer *l);
  //  virtual void forward();
  //  virtual void backward();
  //  virtual void initialize();
  //  virtual void applygrads();
  //  virtual void reset();
