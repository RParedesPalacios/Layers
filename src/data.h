#ifndef _CDATA_
#define _CDATA_


#include "Eigen/Dense"

using namespace Eigen;
using namespace std;

class Data {
 public:
  int num,dim,out;
  int batch,head;
  char name[1000];
  char fname[1000];
  int balance;
  int init_balance;
  int **bci;
  int *bcc;

  int *idx;
  ArrayXXd M;
  ArrayXXd T;
  ArrayXXd inmu;
  ArrayXXd insd;

  Data();
  Data(int n,int d,int o,int b,char *name);

  // Files
  Data(char *fname,int batch,char *name);
  Data(int bin,char *fname,int batch,char *name);


  void zscore();
  void zscore(Data *D);
  void center();
  void center(Data *D);
  void YUV();
  void div(double val);
  void add(double val);
  void sub(double val);
  void mul(double val);
  void maxmin();
  void shuffle();
  void preparebatch(int code);
  void next();
  int gethead();
  int getpos(int p);
  void setbalance(int b);
  void fillData(Data *D,int p);
  void Save(char *fname);
  void SaveBin(char *fname);

};

#endif
