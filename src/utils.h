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

#ifdef fGPU
#include<stdint.h>
typedef enum
{
CE,
SSE
}loss_type;

void printDebug(float* p, const char*, int row,int col); 

typedef enum
{
BIN,
GAUSS,
SUNI,
UUNI
}rand_type;

typedef enum
{
TOGPU,
FROMGPU,
GPU,
CPU
}tr_type;

typedef struct
{
int batch;//only for convolutional
int featureMap;//only for convolutional
int row;
int col;
}tensor_gpu_specs;

typedef struct
{
uint8_t warpSize;
uint8_t maxThreadPerBlock;
uint8_t multiCores;
uint8_t totalGlobMem;
uint8_t sharedMemPerBlock;
uint8_t totalConstMem;
uint8_t clockRate;
}gpu_specs;

//variables

#endif
#endif
