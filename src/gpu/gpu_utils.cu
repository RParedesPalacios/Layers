#include "gpu_utils.h"
#include <cublas_v2.h>
#include <string.h>
#include <stdio.h>
#include <curand.h>

 
bool useCPU=0;

//For controlling cublas routines
bool isYes=0; //for controlling cublas activation

//For controlling tensor operations over GPU
cublasHandle_t p_cublas;
cublasStatus_t status;
gpu_specs gpuI;
gpu_env gpu_tensor_op;


//for controlling random generator
long int gpu_seed=10;
curandGenerator_t random_generator;
curandStatus_t rand_error;


 
void cublasInit()
{

  status=cublasCreate(&p_cublas);
  if ( status!=  CUBLAS_STATUS_SUCCESS)
  {
     fprintf(stderr,"Problem in cuBlas execution getting: NOT IMPLEMENTED \n");
     exit(1);

  }

  isYes=1;

/*  status=cublasSetPointerMode(p_cublas,CUBLAS_POINTER_MODE_DEVICE);
  if ( status!=  CUBLAS_STATUS_SUCCESS)
  {
     fprintf(stderr,"Problem in cuBlas execution getting: NOT IMPLEMENTED \n");
     exit(1);

  }*/

}

void curandInit()
{

  rand_error=curandCreateGenerator(&random_generator,CURAND_RNG_PSEUDO_MRG32K3A);
  if (rand_error != CURAND_STATUS_SUCCESS)
	{fprintf(stderr,"Error creating random numbers on gpu\n");exit(-1);}

   rand_error=curandSetPseudoRandomGeneratorSeed(random_generator,gpu_seed); 
    if (rand_error != CURAND_STATUS_SUCCESS)
	{fprintf(stderr,"Error seeting the seed for program\n");exit(-1);}

}





















