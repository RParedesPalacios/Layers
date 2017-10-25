#include "execution.h"
#include <curand.h> 
#include <cublas_v2.h>
#include <string.h>
#include <stdio.h>

//For controlling tensor operations over GPU
cublasHandle_t p_cublas;//for cublas routines execution
cublasStatus_t status;//cublas error
bool isYes=0;//for cublas execution

gpu_env gpu_tensor_op;//gpu class routines

//for controlling random generator
curandGenerator_t random_generator; //for random routines
curandStatus_t rand_error;// random error

gpu_specs gpuI;
long int gpu_seed=1;

//initialice cublas handle
void cublasInit()
{

  status=cublasCreate(&p_cublas);
  if ( status!=  CUBLAS_STATUS_SUCCESS)
  {
     fprintf(stderr,"Problem in cuBlas execution getting: NOT IMPLEMENTED \n");
     exit(1);

  }

  isYes=1;

status = cublasSetAtomicsMode(p_cublas,CUBLAS_ATOMICS_NOT_ALLOWED);
  if ( status!=  CUBLAS_STATUS_SUCCESS)
  {
     fprintf(stderr,"Problem in cuBlas execution getting: NOT IMPLEMENTED \n");
     exit(1);

  }


/*  status=cublasSetPointerMode(p_cublas,CUBLAS_POINTER_MODE_DEVICE);
  if ( status!=  CUBLAS_STATUS_SUCCESS)
  {
     fprintf(stderr,"Problem in cuBlas execution getting: NOT IMPLEMENTED \n");
     exit(1);

  }*/

}

//initialize curand handle and set seed
void curandInit()
{

  rand_error=curandCreateGenerator(&random_generator,CURAND_RNG_PSEUDO_MRG32K3A);
  if (rand_error != CURAND_STATUS_SUCCESS)
	{fprintf(stderr,"Error creating random numbers on gpu\n");exit(-1);}

   rand_error=curandSetPseudoRandomGeneratorSeed(random_generator,gpu_seed); 
    if (rand_error != CURAND_STATUS_SUCCESS)
	{fprintf(stderr,"Error seeting the seed for program\n");exit(-1);}

}


