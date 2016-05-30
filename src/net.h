#include "data.h"

#define MAX_LAYERS 100
#define MAX_DATA 100

class Layer;

class Net {
 public:
  
  Layer *lvec[MAX_LAYERS];
  Data *Dtrain;
  Data *Dtest;
  Data *Dval;
  FILE *flog;

  Layer *out[MAX_LAYERS];
  Layer *in[MAX_LAYERS];
  float err[MAX_LAYERS];
  

  Layer *fts[MAX_LAYERS];
  Layer *bts[MAX_LAYERS];
  
  char name[100];
  
  int layers,olayers,ilayers;
  int bn;
  int init;
  int trit;
  int trepoch;
  
  float mu;

  float ftime;
  float btime;

  Net(char *name);

  void addLayer(Layer *l);

  void getbatch();
  void getbatch(Data *Dt);
  void next();
  void gcheck();
  void gcheckF();
  void initialize();
  void preparebatch(int code);
  void resetLayers();
  void resetstats();
  void build_fts();
  void build_bts();
  void forward();
  void backward();
  void applygrads();

  void net2dot();
  void trainmode();
  void testmode();  

  void setvalues();
  void train(int epochs);
  void trainbatch(int b);
  void testOut();
  void printOut(Data *Dt,FILE *fs);
  void preparetrainbatch();
  void calcerr(Data *Dt);
  void printerrors(Data *Dt);
  void printerrors(Data *Dt,int num);
  
  void reseterrors();
  void Init(char *logname);

  void setmu(float m);
  void setmmu(float m);
  void setshift(int f);
  void setflip(int f);
  void setbrightness(float f);
  void setcontrast(float f);
  void decmu(float decay);  
  void setact(int a);
  void setbn(int a);
  void setmaxn(float m);
  void setl2(float m);
  void setdrop(float m);
  void setopt(int l);
  void setthreads(int l);
  void setnoiser(float n);
  void setnoisesd(float n);

  int isIn(Layer *l);
};

class MLP : public Net {
 public:

  MLP(Data *D,int batch,int h,int hv[]);
  
};
