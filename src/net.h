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
  double err[MAX_LAYERS];
  

  Layer *fts[MAX_LAYERS];
  Layer *bts[MAX_LAYERS];
  
  char name[100];
  
  int layers,olayers,ilayers;
  int bn;
  int init;

  double mu;
  double decay;

  double ftime;
  double btime;

  Net(char *name);

  void addLayer(Layer *l);

  void getbatch();
  void getbatch(Data *Dt);
  void next();
  void gcheck();
  void gcheckF();
  void initialize();
  void preparebatch(int code);
  void evaluate();

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
  void testOut(FILE *fs);
  void printOut(Data *Dt,FILE *fs,int n);
  void preparetrainbatch();
  void calcerr(Data *Dt);
  void printerrors(Data *Dt);
  void printerrors(Data *Dt,int num);
  
  void reseterrors();
  void Init(char *logname);

  void setmu(double m);
  void setmmu(double m);
  void setshift(int f);
  void setflip(int f);
  void setbrightness(double f);
  void setcontrast(double f);
  void decmu(double decay);  
  void setact(int a);
  void setbn(int a);
  void setmaxn(double m);
  void setl2(double m);
  void setl1(double m);
  void setdrop(double m);
  void setoptim(int l);
  void setthreads(int l);
  void setnoiser(double n);
  void setnoisesd(double n);
  void setnoiseb(double n);
  void setdecay(double f);
  void setlambda(double f);
  void setadv(int i);
  void setadvf(double m);
  void setaddelta(int i);

  int isIn(Layer *l);

  void save(FILE *fe);
  void load(FILE *fe);

};

class MLP : public Net {
 public:

  MLP(Data *D,int batch,int h,int hv[]);
  
};
