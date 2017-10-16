#ifndef _UTILS_
#define _UTILS_

#include "types.h"

#ifdef MKL 
#define EIGEN_USE_MKL_ALL
#endif
#include "Eigen/Dense"

#define VERBOSE 0

#define LUT 100000

using namespace Eigen;
using namespace std;

void lut_init();
void NoiseG(LMatrix &E,double noiser,double noisesd);
void ReLu(LMatrix E,LMatrix &N);
void Sigmoid(LMatrix E,LMatrix &N);
void ELU(LMatrix E,LMatrix& N,double alfa);
void Softmax(LMatrix E,LMatrix &N);
void Linear(LMatrix E,LMatrix &N);
void Drop(LMatrix &M,double drop);


double dsigm(double x);
double sigm(double x);
double uniform();
double suniform();
double gauss(double mean,double sd);
double gaussgen();


#endif
