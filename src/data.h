#ifndef _CDATA_
#define _CDATA_

#include "utils.h"

#ifdef MKL 
#define EIGEN_USE_MKL_ALL
#endif
#include "Eigen/Dense"


using namespace Eigen;
using namespace std;

class Data {
 public:
  int num,dim,out,size;
  int batch,head;
  int gen;
  char name[1000];
  char fname[1000];
  int balance;
  int init_balance;
  int **bci;
  int *bcc;
  int *idx;
  ArrayXXd M;
  //ArrayXXd T;

  //stats
  int cp;
  int *fbin,*freal,*fint;
  float *fmu;
  float *fsd;
  float *fmax;
  float *fmin;

 
  
  Data();
  Data(int n,int d,int o,int b,char *name);

  // Files
  Data(char *fname,int batch,char *name);
  Data(int bin,char *fname,int batch,char *name);

  void Mem();
  void copystats(Data *D);
  int isBin(int f);
  int isReal(int f);
  void detect();

  void zscore(int sini,int sfin,int dini,int dfin,int type);
  void center(int sini,int sfin,int dini,int dfin,int type);
  void maxmin(int sini,int sfin,int dini,int dfin,int type);
  void YUV();

  void div(double val,int sini,int sfin,int dini,int dfin,int type);
  void add(double val,int sini,int sfin,int dini,int dfin,int type);
  void sub(double val,int sini,int sfin,int dini,int dfin,int type);
  void mul(double val,int sini,int sfin,int dini,int dfin,int type);
  void set(double val,int sini,int sfin,int dini,int dfin,int type);
  double get(int s,int d);
  void set(int s,int d,double val);

  void shuffle();
  void preparebatch(int code);
  void next();
  int getpos(int p);
  void setbalance(int b);
  void fillData(Data *D,int p);
  void Save(char *fname);
  void SaveBin(char *fname);
  void limits(int &sini,int &sfin,int &dini,int &dfin);
  Data* create(char *newn,int sini,int sdfin,int dini,int dfin,int type);
  void copyto(Data *D,int Dsini,int Dsfin,int Ddini,int Ddfin,int Dtype,int sini,int sfin,int dini,int dfin,int type);
  void copyL(LMatrix N,int sini,int sfin,int dini,int dfin,int type);

  void cat(Data *D);
  void paste(Data *D);
};

class GData : public Data {
 public:
  int type;
  int param;

  GData();
  GData(int n,int d,int t,int p,char *name);

  void next();
  
};

#endif
