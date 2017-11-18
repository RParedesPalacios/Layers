#ifndef _TENSOR_
#define _TENSOR_

#include "types.h"
#include "data.h"
#include "Eigen/Dense"

#define unset -1

//FOR GPU COMPUTATION
#ifdef fGPU
 #include "utils.h"
#endif


using namespace Eigen;
using namespace std;

typedef LMatrix **Tensor4D;
typedef LMatrix *Tensor3D;
typedef LMatrix Tensor2D;
typedef LVector Tensor1D;





class Tensor {
  public:
  // CPU
  LRVector ptr1;
  LMatrix ptr2;
  ////

  // GPU
  #ifdef fGPU
    float* gptr;	
    tensor_gpu_specs gsp;
  #endif
  ///

  static Tensor *AUX;

  Tensor **ptr;
  Tensor *lin;
  Tensor *T;

  int dim;
  int size;
  int a,b,c,d;
  
  

  Tensor();
  ~Tensor();


  Tensor(int a);
  Tensor(int a,int b);
  Tensor(int a,int b,int c);
  Tensor(int a,int b,int c,int d);

  Tensor *Clone();  
  void Transpose();
  void UnTranspose();

  void replace_unset();
  void resize(int a);
  void resize(int a,int b);
  void resize(int a,int b,int c);
  void resize(int a,int b,int c,int d);

  Tensor *subTensor(int a);
  Tensor *subTensor(int a,int b);

  Tensor* toLin();
  void fromLin(Tensor *);
    
  void copy(Tensor *T);
  void copyfromData(Data *D);
  void copylabels(Data *D);
  void copyStatistics(Data *D,int tipe);

  
  void set(LType val);  
  void set(int a,LType val);
  void inc(int a,LType val);
  void set(int a,int b,LType val);
  void inc(int a,int b,LType val);
  void set(int a,int b,int c,LType val);
  void set(int a,int b,int c,int d,LType val);

  LType get(int a);
  LType get(int a,int b);
  LType get(int a,int b,int c);
  LType get(int a,int b,int c,int d);

  // stats
  LType sum();
  LType norm();
  LType col_max(int ind,int *imax);
  LType row_max(int ind,int *imax);
  int equal(Tensor *T);
  
  // math element wise
  void mul(LType val);
  void div(LType val);
  void add(LType val);
  void abs();
  void sqr();

  // noise
  void set_rand_gauss(LType m,LType sd);
  void set_rand_signed_uniform(LType val);
  void set_rand_uniform(LType val);
  void set_rand_binary(LType val);
  void add_noise_gauss(LType noiser,LType m,LType noisesd);
  
  // I/O
  
  void print(const char *cad);
  void save(FILE *fs,int nl);
  void load(FILE *fs);



  
  void inc_2Drowwise(Tensor *T);


  // STATIC METHODS
  static void loss_cross_entropy(Tensor *T,Tensor *N,double &cerr,double &ent);
  static void loss_sse(Tensor *T,Tensor *N,Data *D,int offset,double &mae,double &mse);

  static void dactivation(Tensor *E, Tensor *N, Tensor *D, int act);
  static void activation(Tensor *E, Tensor *N,int act);
  static void maskZeros(Tensor *mask,Tensor *A);

  static Tensor * mult(Tensor *A, int tA, Tensor *B, int tB, Tensor *C, int inc);
  static Tensor * el_mult(Tensor *A, int tA, Tensor *B, int tB, Tensor *C, int inc);
  static Tensor * sc_mult(Tensor *A, LType sc, Tensor *B, int inc);
  static Tensor * sum(LType sca,Tensor *A, int tA, LType scb,Tensor *B, int tB, Tensor *C, int inc);
  static Tensor * inc(Tensor *A, Tensor *C);
  static Tensor * sc_sum(Tensor *A, LType sc, Tensor *B, int inc);
  static Tensor * out_mult(Tensor *A, Tensor *B, Tensor *C, int inc);
  static void sumcol(Tensor *A,Tensor *B);

  static void Convol2D(Tensor *A,Tensor *K,Tensor *B,int inc,int stride,int pad);
  static void Convol2DT(Tensor *A,Tensor *K,Tensor *B,int inc,int stride,int pad);
  static void Convol3D(Tensor *A,Tensor *K,Tensor *B,int stride,int pad);
  static void Convol(Tensor *A,Tensor *K,int tK,Tensor *B,int tB,int stride, int pad);
  static void ConvolT(Tensor *A,Tensor *K,Tensor *B,int stride, int pad);
  
  static void cpu_convol(Tensor *A,Tensor *K,Tensor *B,int stride,int pad);
  static void cpu_convolT(Tensor *A,Tensor *K,Tensor *B,int stride,int pad);

  // REDUCTIONS
  static void reduceTomean(Tensor *A, Tensor *B,int rowcol);
  static void reduceTosum(Tensor *A, Tensor *B,int rowcol);
  static void reduceTovariance(Tensor *A, Tensor *B,int rowcol);
  static void reduced_sum(float scA, Tensor *A,float scB,Tensor *B,Tensor *C,int inc\
			  ,int row);
  static void reduced_div(Tensor *A,Tensor *B,Tensor *C,int inc,int row);
  static void reduced_mult(Tensor *A,Tensor *B,Tensor *C,int inc,int row);




};


#endif
