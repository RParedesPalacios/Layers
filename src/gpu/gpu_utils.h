#ifndef GPUUTILS
#define GPUUTILS
#include<stdint.h>
#include <cublas_v2.h>
#include <curand.h>
/*
typedef enum
{
ACT_RLU,
ACT_SIG,
ACT_SOF,
ACT_ELU
}act_func;
*/

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
FROMGPU
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


void cublasInit();
void curandInit();

extern bool isYes;
extern cublasHandle_t p_cublas;
extern gpu_specs gpuI;
extern bool useCPU;
extern curandStatus_t rand_error;
extern curandGenerator_t random_generator;
extern long int gpu_seed;

#include "gpu_env.h"
extern gpu_env gpu_tensor_op;
#endif
