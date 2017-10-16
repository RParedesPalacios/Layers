#ifndef _TENSOR_
#define _TENSOR_

#include "types.h"
#include "data.h"
#include "Eigen/Dense"

#define unset -1

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

  static Tensor *AUX;

  Tensor **ptr;
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
  
  void Transpose();

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

  void set(LType val);  
  void set(int a,LType val);
  void set(int a,int b,LType val);
  void set(int a,int b,int c,LType val);
  void set(int a,int b,int c,int d,LType val);

  LType get(int a);
  LType get(int a,int b);
  LType get(int a,int b,int c);
  LType get(int a,int b,int c,int d);

  void inc(LType val);  
  void inc(int a,LType val);
  void inc(int a,int b,LType val);
  void inc(int a,int b,int c,LType val);
  void inc(int a,int b,int c,int d,LType val);

  void inc_2Drowwise(Tensor *T);


  void set_rand_gauss(LType m,LType sd);
  void set_rand_signed_uniform(LType val);
  void set_rand_uniform(LType val);
  void set_rand_binary(LType val);
  void add_noise_gauss(LType noiser,LType m,LType noisesd);

  LType norm();
  LType sum();
  int equal(Tensor *T);
  LType col_sum(int ind);
  LType row_sum(int ind);
  LType col_max(int ind,int *imax);
  LType row_max(int ind,int *imax);
  void info();
  void print();
  void save(FILE *fs);
  void load(FILE *fs);

  // STATIC METHODS
  static void dactivation(Tensor *E, Tensor *N, Tensor *D, int act);
  static void activation(Tensor *E, Tensor *N,int act);
  static void maskZeros(Tensor *mask,Tensor *A);

  static Tensor * mult(Tensor *A, int tA, Tensor *B, int tB, Tensor *C, int inc);
  static Tensor * el_mult(Tensor *A, int tA, Tensor *B, int tB, Tensor *C, int inc);
  static Tensor * out_mult(Tensor *A, Tensor *B, Tensor *C, int inc);
  static Tensor * sc_mult(Tensor *A, LType sc, Tensor *B, int inc);
  static Tensor * sum(LType sca,Tensor *A, int tA, LType scb,Tensor *B, int tB, Tensor *C, int inc);
  static Tensor * inc(Tensor *A, Tensor *C);
  static Tensor * sc_sum(Tensor *A, LType sc, Tensor *B, int inc);
  


  static void Convol2D(Tensor *A,Tensor *K,Tensor *B,int inc,int stride,int pad);
  static void Convol2DT(Tensor *A,Tensor *K,Tensor *B,int inc,int stride,int pad);
  static void Convol3D(Tensor *A,Tensor *K,Tensor *B,int stride,int pad);
  static void Convol(Tensor *A,Tensor *K,int tK,Tensor *B,int tB,int stride, int pad);



  static void ConvolT(Tensor *A,Tensor *K,Tensor *B,int stride, int pad);






  static void forwardBN_training(int batch,
				 Tensor *E,
				 Tensor *bn_mean,
				 Tensor *bn_var,
				 Tensor *bn_E,
				 Tensor *bn_g,
				 Tensor *bn_b,
				 Tensor *BNE,
				 Tensor *bn_gmean,
				 Tensor *bn_gvar,
				 int bnc,
				 int noiser,
				 LType noisesd);

  static void forwardBN_inference(int batch,Tensor *E,Tensor *bn_mean,Tensor *bn_var,Tensor *bn_E,Tensor *bn_g,Tensor *bn_b,Tensor *BNE,int bnc); 

  static void backwardBN(int batch,
			Tensor *E,
			Tensor *bn_E,
			Tensor *bn_g,
			Tensor *bn_mean,
			Tensor *bn_var,
			Tensor *Delta,
			Tensor *gbn_g,
			Tensor *gbn_b,
			Tensor *gbn_E,
			Tensor *gbn_mean,
			Tensor *gbn_var
			 );


};


#endif
