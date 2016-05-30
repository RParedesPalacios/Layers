#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <math.h>
#include <typeinfo>
#include <iostream>
#include <cstdlib>
#include <pthread.h>

#include "utils.h"

#include "Dense"

#define PI 3.1415926


using namespace Eigen;
using namespace std;
float uniform() {
  return ((rand()%10000)/10000.0);

}

float suniform() {
  return (2*uniform())-1;
}

float gauss(float mean,float sd) {
  float x,u1,u2;

  u1=uniform();
  u2=uniform();

  while (u1==0.0) u1=uniform();
    
  x=sqrt(log(1/u1))*cos(2*PI*u2);

  x*=sd;
  x+=mean;

  return x;
}





float sigm(float x)
{
  if (x<-10) return 0;
  if (x>10) return 1;

  return 1/(1+exp(-x));

}

float dsigm(float x)
{
  float s=sigm(x);
  
  return s*(1-s);

}

void Drop(MatrixXf &M,float drop)
{
  for(int i=0;i<M.rows();i++)
    for(int j=0;j<M.cols();j++)
      if (uniform()<drop) M(i,j)=0;
      else M(i,j)=1;
  
}

void ReLu(MatrixXf E,MatrixXf& N)
{
  
  for(int i=0;i<E.rows();i++)
    for(int j=0;j<E.cols();j++)
      if (E(i,j)<=0) N(i,j)=0;
      else N(i,j)=E(i,j);
  
  
}

void ELU(MatrixXf E,MatrixXf& N,float alfa)
{
  int i,j;

  for(int i=0;i<E.rows();i++)
    for(int j=0;j<E.cols();j++)
      if (E(i,j)<=0)  N(i,j)=alfa*(exp(E(i,j)-1));
      else N(i,j)=E(i,j);
  
}
void Sigmoid(MatrixXf E,MatrixXf &N)
{
  int i,j;

  for(int i=0;i<E.rows();i++)
    for(int j=0;j<E.cols();j++)
      N(i,j)=sigm(E(i,j));

}

void Softmax(MatrixXf E,MatrixXf &N)
{
  int i,j;
  float max,sum;

  for(i=0;i<E.rows();i++) {

    max=E.row(i).maxCoeff();    
    
    for(j=0;j<E.cols();j++)
      E(i,j)=exp(E(i,j)-max);
    
    sum=E.row(i).sum();   
    
    for(j=0;j<E.cols();j++)
      N(i,j)=E(i,j)/sum;
    }
}

void Linear(MatrixXf E,MatrixXf &N)
{
  N=E;  
}
