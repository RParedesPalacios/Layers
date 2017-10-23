//Developer: Juan Maroñas Molano 
//This file implements kernel cuda for Layers

#include <cuda.h>
#include <cuda_runtime_api.h>
#include <curand_kernel.h>
#include "gpu_kernels.h"

////////////////////////////////////////////
///////////NEURAL NETWORKS//////////////////
////////////////////////////////////////////

//ACTIVATION FUNCTIONS
//FORWARD

//Rectifier Linear Units
__global__ void ReLu(float* E, float* N, long int n_vals)
{
  int thread_id_x = threadIdx.x + blockIdx.x*blockDim.x;
if (thread_id_x < n_vals)
  N[thread_id_x]=fmaxf(0.0,E[thread_id_x]);
}

//Exponential Linear Unit
//JUAN_FIX: make eficient without warping divergence
__global__ void ELU(float* E,float* N, float alfa ,long int n_vals)
{

  int thread_id_x = threadIdx.x + blockIdx.x*blockDim.x;
  float a=0;
  if (thread_id_x < n_vals)
  {
	a=E[thread_id_x]; 
	if (a<0) //Warping divergence
		N[thread_id_x]=alfa*(expf(a)-1);
  }
}

//Sigmoid 
__global__ void Sigmoid(float* E,float* N ,long int n_vals)
{
  int thread_id_x = threadIdx.x + blockIdx.x*blockDim.x;
  if (thread_id_x < n_vals)
     N[thread_id_x] = 1/(1+expf(-1*E[thread_id_x]));
}

//Softmax->implemented for not saturating
__global__ void Softmax(float* E,float* N,float* auxE ,long int sample_dim, long int n_vals)
{
//This way of programing allow no warp syncronization as we only need kernel optimization.
//Maybe use thrust library but could be tricky. Should study if it fit well with this problem. Think is not, we would need one thrust vector per row.
//On the other hand possibly implement reduction as in http://www.cuvilib.com/Reduction.pdf. Will need to call another function. This could be complecated also as we need to see which thread id implements softmax and which one computes maximum. For now simple approximation.
    float C_value=0;
    int thread_id_x = threadIdx.x + blockIdx.x*blockDim.x;
    float maxCoef = E[thread_id_x*sample_dim];
    float actualCoef = 0;
    if (thread_id_x<n_vals)
    {
	    ///REALLY HIGH PROBABILITY OF BRANCH DIVERGENCE. 
            //Description: All of the threads that lie under one condition execute first (stalling the others) and then next. Assuming one clock cycle per operation we would need double time to execute one warp.
	    //Warping divergence: study reduction options for getting the maximum
	    #pragma omp parallel for
	    for (int cA = 1; cA < sample_dim; cA++)
		if (E[thread_id_x*sample_dim+cA] > maxCoef)
			 maxCoef=E[thread_id_x*sample_dim+cA];

	    //No warping divergence as all threads execute the same
	    #pragma omp parallel for
	    for (int cA = 0; cA < sample_dim; cA++)
		{
			actualCoef=expf(E[thread_id_x*sample_dim+cA]-maxCoef);
			auxE[thread_id_x*sample_dim+cA]=actualCoef;
                        C_value+=actualCoef;
		}
            #pragma omp parallel for
	    for (int cA=0; cA < sample_dim; cA++)
	       N[thread_id_x*sample_dim+cA]=auxE[thread_id_x*sample_dim+cA]/C_value;
    }
	
}
//BACKWARD (derivatives)

__global__ void dReLu(float *E,float* D, long int total_ops)
{

  int thread_id_x = threadIdx.x +blockIdx.x*blockDim.x;
  if (thread_id_x<total_ops)
  {
        D[thread_id_x]=(float) E[thread_id_x] > 0;

  }
}

__global__ void dSigmoid(float *E,float* D, long int total_ops)
{
 
  int thread_id_x = threadIdx.x + blockIdx.x * blockDim.x;
  if (thread_id_x < total_ops)
  {
     float val = 1/(1+expf(-1*E[thread_id_x])); 
     D[thread_id_x] = val*(1-val);
  }

}

__global__ void dELU(float *E,float* N,float* D, long int total_ops)
{
int thread_id_x = threadIdx.x + blockIdx.x*blockDim.x;

  if (thread_id_x < total_ops)
  {
    bool val = E[thread_id_x] <= 0;
    D[thread_id_x]=val*N[thread_id_x]+1;
  }

}

////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////

///////////////////////////////////////////
//////////////LINEAR ALGEBRA///////////////
///////////////////////////////////////////

//SCALAR MATRIX OPERATOR
//add scalar to matrix and store
__global__ void sc_add_mat(float* mat_o,float* mat_i, float sc, long int total_ops, int acc)
{
  //this function does not have memory races-> maybe optimized using shared memory
  int thread_id_x = threadIdx.x + blockIdx.x * blockDim.x;
  
  if (thread_id_x < total_ops)
  {
	if (acc == 0)//not warping divergence as all the threads will have acc set to same value
		mat_o[thread_id_x]=mat_i[thread_id_x]+sc;
	else if(acc==1)
		mat_o[thread_id_x]+=(mat_i[thread_id_x]+sc);
   }
}
////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////

///////////////////////////////////////////
//////////ELEMENT WISE OPERATOR////////////
///////////////////////////////////////////


//MATRIX MATRIX OPERATOR
//el wise product

__global__ void mat_ewprod_mat(float* mat_o,float* mat_i1, float* mat_i2,int acc ,long int total_ops)
{
  int thread_id_x = threadIdx.x + blockIdx.x * blockDim.x;
  if (thread_id_x < total_ops)
  {
      
	if (acc==0)//Accumulate the value
        {
		mat_o[thread_id_x]=mat_i1[thread_id_x]*mat_i2[thread_id_x];
        }
	else if(acc==1)
        {
		mat_o[thread_id_x]=mat_o[thread_id_x]+mat_i1[thread_id_x]*mat_i2[thread_id_x];
        }
   

  }
}
//tensor equal
__global__ void kern_tensor_equal(float* A, float* B, long int ops)
{
  int thread_id_x = threadIdx.x + blockIdx.x * blockDim.x;

  if(thread_id_x < ops)
	if(A[thread_id_x]!=B[thread_id_x])
		asm("trap;");

}

//MATRIX VECTOR OPERATOR
__global__ void mat_ewcol_vec(float* mat, float* vec, long int ops, long int cols, int op)
{

  int thread_id_x = threadIdx.x+blockIdx.x*blockDim.x;
 
  if (thread_id_x < ops)
   if (op==0)
     mat[thread_id_x]+=vec[thread_id_x%cols];
   else
     mat[thread_id_x]*=vec[thread_id_x%cols];

}

////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////


////////////////////////////////////////////
////////////MEMORY MANAGMENT////////////////
////////////////////////////////////////////
__global__ void tensor_set_value(float* A, float value, long int total_ops)
{
int thread_id_x = threadIdx.x +blockIdx.x*blockDim.x;

if (thread_id_x < total_ops)
	A[thread_id_x]=value;

}

////////////////////////////////////////////
////////////SELF OPERATOR///////////////////
////////////////////////////////////////////
//JUAN_FIX: implement with reduction operators
__global__ void kernel_col_sum(float* I, float* O, int rows,int cols ,long int ops)
{

int thread_id_x = threadIdx.x +blockIdx.x*blockDim.x;
int i=0;
if (thread_id_x < ops)
   #pragma omp parallel for
   for(i=0;i<rows;i++)
   	O[thread_id_x]+=I[thread_id_x+cols*i];
   
}

//////////////////////////////////////////////
///////////////RANDOM GENERATOR///////////////
//////////////////////////////////////////////
//Do this using device api
__global__ void drop_mask(float* rand_vec,float p,long int ops)
{
   int thread_id_x = threadIdx.x+blockIdx.x*blockDim.x;
   if (thread_id_x<ops)
     rand_vec[thread_id_x]=rand_vec[thread_id_x]>p;

}

__global__ void add_noise_with_mask(float* nn_vector,float* rand_vec,float* mask,float noiser,long int ops)
{

   int thread_id_x = threadIdx.x+blockIdx.x*blockDim.x;
   if (thread_id_x<ops)
     nn_vector[thread_id_x]+=(mask[thread_id_x]>noiser)*rand_vec[thread_id_x];

}




