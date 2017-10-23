#ifndef _GGPU_EXECUTION_
#define _GGPU_EXECUTION_
#include <curand.h> 
#include <cublas_v2.h>
#include "../utils.h"
#include "gpu_env.h"


//For controlling tensor operations over GPU
extern cublasHandle_t p_cublas;//for cublas routines execution
extern cublasStatus_t status;//cublas error
extern bool isYes;//for cublas execution

extern gpu_env gpu_tensor_op;//gpu class routines


extern gpu_specs gpuI; //for GPU parameters

//for controlling random generator
extern curandGenerator_t random_generator; //for random routines
extern curandStatus_t rand_error;// random error

//initialice cublas handle
void cublasInit();
//initialize curand handle and set seed
void curandInit();

#endif


