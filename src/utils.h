#ifndef _UTILS_
#define _UTILS_

#include "Dense"


using namespace Eigen;
using namespace std;

void ReLu(MatrixXf E,MatrixXf &N);
void Sigmoid(MatrixXf E,MatrixXf &N);
void ELU(MatrixXf E,MatrixXf& N,float alfa);
void Softmax(MatrixXf E,MatrixXf &N);
void Linear(MatrixXf E,MatrixXf &N);
void Drop(MatrixXf &M,float drop);


float dsigm(float x);
float sigm(float x);
float uniform();
float suniform();
float gauss(float mean,float sd);


#endif
