#ifndef _UTILS_
#define _UTILS_

#define LUT 100000

#include "Eigen/Dense"
#include "types.h"


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
