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
  int cropmode;
  int crops;

  double mu;
  double decay;

  double ftime;
  double btime;

  Net(char *name);

  void addLayer(Layer *l);

  void getbatch();
  void getbatch(Data *Dt);
  void getbatch(Data *Dt,int s);
  void next();
  void initialize();
  void preparebatch(int code);
  void evaluate(Data *dt);

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
  void copy(Layer *ld,Layer *ls);
  void setvalues();
  void train(int epochs);
  void trainbatch(int b,int e);
  void testOut(FILE *fs);
  void fillData(Data *D,Layer *l1,Layer *l2);
  void printOut(Data *Dt,FILE *fs,int n);
  void preparetrainbatch();
  void calcerr(Data *Dt);
  void calcerr(Data *Dt,int s);
  void printerrors(Data *Dt);
  void printerrors(Data *Dt,int num);
  
  void reseterrors();
  void Init(FILE *flog);

  void setcropmode(int f);
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

