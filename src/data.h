#ifndef _CDATA_
#define _CDATA_


#include "Dense"

using namespace Eigen;
using namespace std;

class Data {
 public:
  int num,dim,out;
  int batch,head;
  char name[1000];
  char fname[1000];

  ArrayXXf M;
  ArrayXXf T;
  ArrayXXf inmu;
  ArrayXXf insd;

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
  void div(float val);
  void shuffle();
  void preparebatch(int code);
  void next();
  int gethead();

  void Save(char *fname);
  void SaveBin(char *fname);

};

#endif
