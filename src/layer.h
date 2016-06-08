#include "data.h"
#include "Dense"

#define MAX_CONNECT 100

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
  float mu;
  float mmu;
  float l2;
  float l1;
  float maxn;
  float drop;
  float noiser;
  float noisesd;
  int trmode;
  int dev_done;
  int threads;
  int opt;
  int reshape;
  int local;
  int lr,lc,lm,ld;
  int bn;
  int init;

  int shift,flip;
  float brightness,contrast;

  Data *D;
  Layer **Lin;
  Layer **Lout;
  Net *rnet;

  Layer();
  Layer(int b,char *name);

  void setflip(int f);
  void setshift(int f);
  void setbrightness(float f);
  void setcontrast(float f);

  void setmu(float m);
  void setmmu(float m);
  void setdrop(float m);
  void setl2(float m);
  void setl1(float m);
  void setmaxn(float m);
  void trainmode();
  void testmode();
  void setact(int i);  
  void setbn(int a);
  void setnoiser(float n);
  void setnoisesd(float n);
  void setthreads(int t);
  void setopt(int i);  

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

};


class FLayer : public Layer {
 public:
  
  FLayer();
  FLayer(int in,int batch,char *name);
  FLayer(Layer *In,int batch,char *name);
  FLayer(Layer *In,int lr,int lc,char *name);

  MatrixXf *W;
  MatrixXf *gW;
  MatrixXf *pgW;
  RowVectorXf *b;
  RowVectorXf *gb;
  RowVectorXf *pgb;
  RowVectorXf dvec;
  
  MatrixXf N;
  MatrixXf E;
  MatrixXf T;
  MatrixXf dE;
  MatrixXf Delta;

  //BN
  VectorXf bn_mean;
  VectorXf bn_var;
  VectorXf bn_gmean;
  VectorXf bn_gvar;
  VectorXf bn_g;
  VectorXf bn_b;
  MatrixXf bn_E;
  MatrixXf BNE;
  int bnc;

  VectorXf gbn_mean;
  VectorXf gbn_var;
  VectorXf gbn_g;
  VectorXf gbn_b;
  MatrixXf gbn_E;
  
  void modbatch(int b);
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

  void doActivation();
  void dactivation();

  void save(FILE *fe);
  void load(FILE *fe);

  void printkernels(FILE *fe);

};
  
class IFLayer : public FLayer {
 public:

  IFLayer(Data *D,int b,char *name);
  
  void getbatch(Data *Dt);
  void backward();
  void addparent(Layer *l);

};


class OFLayer : public FLayer {
 public:

  int ae;
  float landa;

  float rmse,mse,mae,cerr,ent;

  OFLayer(Data *D,int b,int act,int ae,char *name);
  OFLayer(Data *D,int b,int act,char *name);

  void forward();
  void backward();
  void modbatch(int b);
  void addchild(Layer *l);
  float get_err(Data *Dt);
};

////////////////////
class CLayer : public Layer {
 public:

  int nk,kr,kc,kz;
  int outz,outr,outc;
  int stride;
  int zpad;
  int rpad,cpad;
  
  MatrixXf **K;
  MatrixXf **gK;
  MatrixXf **pgK;
  VectorXf bias;
  VectorXf gbias;

  MatrixXf **E;  
  MatrixXf **BNE;
  MatrixXf **N;
  MatrixXf *Dvec;
  MatrixXf **padN;
  MatrixXf **De;
  
  // FOR BN
  VectorXf bn_mean;
  VectorXf bn_gmean;
  VectorXf bn_var;
  VectorXf bn_gvar;
  VectorXf bn_g;
  VectorXf bn_b;
  MatrixXf **bn_E;
  int bnc;

  VectorXf gbn_mean;
  VectorXf gbn_var;
  VectorXf gbn_g;
  VectorXf gbn_b;
  MatrixXf **gbn_E;

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
  void doActivation();
  void ConvolB();
  void MaxPoolB();
  void printkernels(FILE *fe);

  void save(FILE *fe);
  void load(FILE *fe);

  
};

class ICLayer : public CLayer {
 public:

  int imr,imc;
  
  ICLayer(Data *D,int batch,int z,int r,int c,char *name);
  ICLayer(Data *D,int batch,int z,int r,int c,int ir,int ic,char *name);
 
  void getbatch(Data *Dt);
  void addparent(Layer *l);

  void forward();
  void backward();
  void initialize();
  void applygrads();
  void reset();
  void save(FILE *fe);
  void load(FILE *fe);

  void doflip(MatrixXf& I);
  void doshift(MatrixXf& I,int sx,int sy);
  void donoise(MatrixXf& I,float ratio, float sd);
  float calc_brightness(MatrixXf I,float factor);
  void dobrightness(MatrixXf& I,float factor); 
  void docontrast(MatrixXf& I,float factor); 
  void SaveImage(MatrixXf R,MatrixXf G,MatrixXf B,char *name);

 
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


