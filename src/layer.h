#include "data.h"
#include "Eigen/Dense"
#include "types.h"

#define MAX_CONNECT 100
#define GLUT 100000

using namespace Eigen;
using namespace std;

class Net;

class Layer {
 public:
  char name[1000];
  int type;

  int din;
  int lin;
  int lout;
  int batch;
  int act;
  double mu;
  double mmu;
  double l2;
  double l1;
  double maxn;
  double drop;
  double noiser;
  double noiseb;
  double noisesd;
  double *gn;
  double *un;

  int optim;
  int trmode;
  int dev_done;
  int threads;
  int opt;
  int reshape;

  int nobias;
  int bn;
  int init;
  int out;
  double lambda;
  int adv,adelta;
  double advf;
  

  int shift,flip;
  double brightness,contrast;

  int lt;

  Data *D;
  Layer *target;
  Layer **Lin;
  Layer **Lout;
  Net *rnet;

  Layer();
  Layer(int b,char *name);

  void setflip(int f);
  void setshift(int f);
  void setbrightness(double f);
  void setcontrast(double f);

  void setmu(double m);
  void setmmu(double m);
  void setdrop(double m);
  void setl2(double m);
  void setl1(double m);
  void setmaxn(double m);
  void trainmode();
  void testmode();
  void setact(int i);
  void setbn(int a);
  void setnoiser(double n);
  void setnoisesd(double n);
  void setnoiseb(double n);
  void setlambda(double l);
  void setthreads(int t);
  void setoptim(int i);
  void setadv(int i);
  void setadvf(double m);

  void save_param(FILE *fe);
  void load_param(FILE *fe);


  virtual void save(FILE *fe){}
  virtual void load(FILE *fe){}
  virtual void printkernels(FILE *fe){}
  virtual void addchild(Layer *l){}
  virtual void addparent(Layer *l){}
  virtual void forward(){}
  virtual void backward(){}
  virtual void initialize(){}
  virtual void applygrads(){}
  virtual void reset(){}
  virtual void resetmomentum(){}
  virtual void resetstats(){}
  virtual void getbatch(Data *Dt){}
  virtual void getbatch(Data *Dt,int s){}
  virtual void fillData(Data *D,int p) {}
  virtual void fillTarget(Data *D,int p){}

};


class FLayer : public Layer {
 public:

  FLayer();
  FLayer(int in,int batch,char *name);
  FLayer(Layer *In,int batch,char *name);

  LMatrix *W;
  LMatrix *gW;
  LMatrix *pgW;

  LRVector *b;
  LRVector *gb;
  LRVector *pgb;
  LRVector dvec;

  LMatrix N;
  LMatrix E;
  LMatrix T;
  LMatrix dE;
  LMatrix Delta;

  //BN
  LVector bn_mean;
  LVector bn_var;
  LVector bn_gmean;
  LVector bn_gvar;
  LVector bn_g;
  LVector bn_b;
  LMatrix bn_E;
  LMatrix BNE;
  int bnc;

  LVector gbn_mean;
  LVector gbn_var;
  LVector gbn_g;
  LVector gbn_b;
  LMatrix gbn_E;

  void mem();
  void addchild(Layer *l);
  void addparent(Layer *l);
  void forward();
  void fBN();
  void backward();
  void bBN();
  void initialize();
  void applygrads();
  void reset();
  void resetstats();
  void resetmomentum();

  void dactivation();

  void save(FILE *fe);
  void load(FILE *fe);

  void printkernels(FILE *fe);
  void fillData(Data *D,int p);
  void fillTarget(Data *D,int p);

};

class IFLayer : public FLayer {
 public:

  IFLayer(Data *D,int b,char *name);

  void getbatch(Data *Dt);
  void getbatch(Data *Dt,int s);
  void backward();
  void addparent(Layer *l);

};


class OFLayer : public FLayer {
 public:

  int ae;
  double landa;
  
  double rmse,mse,mae,cerr,ent;

  OFLayer(Data *D,int b,int act,int ae,char *name);
  OFLayer(Data *D,int b,int act,char *name);
  OFLayer(FLayer *t,int b,char *name);

  void backward();
  void modbatch(int b);
  double get_err(Data *Dt);
  double get_err(Data *Dt,int s,int cs);
};

////////////////////
class CLayer : public Layer {
 public:

  int nk,kr,kc,kz;
  int outz,outr,outc;
  int stride;
  int zpad;
  int rpad,cpad;

  LMatrix **K;
  LMatrix **gK;
  LMatrix **pgK;
  LVector bias;
  LVector gbias;

  LMatrix **E;
  LMatrix **BNE;
  LMatrix **N;
  LMatrix *Dvec;
  LMatrix **padN;
  LMatrix **De;

  // FOR BN
  LVector bn_mean;
  LVector bn_gmean;
  LVector bn_var;
  LVector bn_gvar;
  LVector bn_g;
  LVector bn_b;
  LMatrix **bn_E;
  int bnc;

  LVector gbn_mean;
  LVector gbn_var;
  LVector gbn_g;
  LVector gbn_b;
  LMatrix **gbn_E;

  CLayer();
  CLayer(int batch,char *name);
  CLayer(int nk,int kr, int kc,int batch,int rpad,int cpad,int stride,char *name);



  void addchild(Layer *l);
  void addparent(Layer *l);
  void forward();
  void backward();
  void initialize();
  void applygrads();
  void reset();
  void resetstats();
  void resetmomentum();
  void setzpad(int t);


  void fBN();
  void bBN();

  void Convol();
  void ConvolOMP();
  void MaxPool();
  void ConvolB();
  void MaxPoolB();
  void printkernels(FILE *fe);
  void fillData(Data *D,int p);
  void fillTarget(Data *D,int p);

  void save(FILE *fe);
  void load(FILE *fe);


};

class ICLayer : public CLayer {
 public:

  int imr,imc;

  ICLayer(Data *D,int batch,int z,int r,int c,char *name);
  ICLayer(Data *D,int batch,int z,int r,int c,int ir,int ic,char *name);

  void getbatch(Data *Dt);
  void getbatch(Data *Dt,int s);
  void addparent(Layer *l);

  void forward();
  void backward();
  void initialize();
  void applygrads();
  void reset();
  void save(FILE *fe);
  void load(FILE *fe);

  void doflip(LMatrix& I);
  void doshift(LMatrix& I,int sx,int sy);
  void donoise(LMatrix& I,double ratio, double sd);
  void donoiseb(LMatrix& I,double ratio);
  double calc_brightness(LMatrix I,double factor);
  void dobrightness(LMatrix& I,double factor);
  void docontrast(LMatrix& I,double factor);
  void SaveImage(LMatrix R,LMatrix G,LMatrix B,char *name);


};




class PLayer : public CLayer {
 public:

  int sizer;
  int sizec;

  MatrixXi **maxR;
  MatrixXi **maxC;


  void addchild(Layer *l);
  void addparent(Layer *l);
  void forward();
  void backward();
  void initialize();
  void applygrads();
  void reset();



  void MaxPoolB();
  void MaxPool();

  void save(FILE *fe);
  void load(FILE *fe);

  PLayer();
  PLayer(int batch,int sizer,int sizec,char *name);
};



class CatLayer : public CLayer {
 public:
  int cat,catvec[100];

  void addchild(Layer *l);
  void addparent(Layer *l);
  void forward();
  void backward();
  void initialize();
  void applygrads();
  void reset();

  void save(FILE *fe);
  void load(FILE *fe);

  CatLayer();
  CatLayer(int batch,char *name);
};
