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
double uniform() {
  return ((rand()%10000)/10000.0);

}

double suniform() {
  return (2*uniform())-1;
}

double gauss(double mean,double sd) {
  double x,u1,u2;

  u1=uniform();
  u2=uniform();

  while (u1==0.0) u1=uniform();
    
  x=sqrt(log(1/u1))*cos(2*PI*u2);

  x*=sd;
  x+=mean;

  return x;
}





double sigm(double x)
{
  if (x<-100) return 0;
  if (x>100) return 1;

  return 1/(1+exp(-x));

}

double dsigm(double x)
{
  double s=sigm(x);
  
  return s*(1-s);

}

void Drop(LMatrix &M,double drop)
{
  for(int i=0;i<M.rows();i++)
    for(int j=0;j<M.cols();j++)
      if (uniform()<drop) M(i,j)=0;
      else M(i,j)=1;
  
}

void ReLu(LMatrix E,LMatrix& N)
{
  
  for(int i=0;i<E.rows();i++)
    for(int j=0;j<E.cols();j++)
      if (E(i,j)<=0) N(i,j)=0;
      else N(i,j)=E(i,j);
  
  
}

void ELU(LMatrix E,LMatrix& N,double alfa)
{
  int i,j;

  for(int i=0;i<E.rows();i++)
    for(int j=0;j<E.cols();j++)
      if (E(i,j)<=0)  N(i,j)=alfa*(exp(E(i,j)-1));
      else N(i,j)=E(i,j);
  
}
void Sigmoid(LMatrix E,LMatrix &N)
{
  int i,j;

  for(int i=0;i<E.rows();i++)
    for(int j=0;j<E.cols();j++)
      N(i,j)=sigm(E(i,j));

}

void Softmax(LMatrix E,LMatrix &N)
{
  int i,j;
  double max,sum;

  for(i=0;i<E.rows();i++) {

    max=E.row(i).maxCoeff();    
    
    for(j=0;j<E.cols();j++)
      E(i,j)=exp(E(i,j)-max);
    
    sum=E.row(i).sum();   
    
    for(j=0;j<E.cols();j++)
      N(i,j)=E(i,j)/sum;
    }
}

void Linear(LMatrix E,LMatrix &N)
{
  N=E;  
}
