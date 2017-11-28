#include <string.h>
#include <stdio.h>
#include <cuda_runtime_api.h>
#include <cuda.h>
#include <cublas_v2.h>
#include <curand.h>

#include "../utils.h"
#include "../types.h"
#include "execution.h"
#include "gpu_env.h"
#include "gpu_kernels.h"

#define max_gpu_threads 10000000000

/////////////////CURAND ERROR/////////////////////////


static const char *_curandGetErrorEnum(curandStatus_t error)
{
    switch (error)
    {
        case CURAND_STATUS_ALLOCATION_FAILED:
            return "CURAND_STATUS_ALLOCATION_FAILED";
            break;
        case CURAND_STATUS_INITIALIZATION_FAILED:
            return "CURAND_STATUS_INITIALIZATION_FAILED";
            break;
        case CURAND_STATUS_VERSION_MISMATCH:
            return "CURAND_STATUS_VERSION_MISMATCH";
            break;

        case CURAND_STATUS_TYPE_ERROR:
            return "CURAND_STATUS_TYPE_ERROR";
            break;

        case CURAND_STATUS_OUT_OF_RANGE:
            return "CURAND_STATUS_OUT_OF_RANGE";
            break;

        case CURAND_STATUS_PREEXISTING_FAILURE:
            return "CURAND_STATUS_PREEXISTING_FAILURE";
            break;

        case CURAND_STATUS_NOT_INITIALIZED:
            return "CURAND_STATUS_NOT_INITIALIZED";
            break;

        case CURAND_STATUS_DOUBLE_PRECISION_REQUIRED:
            return "CURAND_STATUS_DOUBLE_PRECISION_REQUIRED";
            break;
        default:
	    fprintf(stderr,"Not all curand errors here\n");
	    exit(-1);
    }

}

/////////////////////////////////////////////////////////////



gpu_env::gpu_env()
{

}
//error function for random numbers
void gpu_env::error_rand()
{
  if(rand_error!=CURAND_STATUS_SUCCESS)
  {
     fprintf(stderr,"Problem in cuda random execution getting: %s\n",	_curandGetErrorEnum(rand_error));
     exit(-1);
  }

}
//error function for check internally
void gpu_env::error_f()
{
  if ( error!=cudaSuccess)
  {
     fprintf(stderr,"\nProblem in cuda execution getting: %s\n",	cudaGetErrorString(error));
     exit(-1);
  }

}

//////////////////////////////////////////
/////////////Memory Transfer//////////////
//////////////////////////////////////////

//JUAN_FIX: change for cuda malloc pitch
//make tensor in GPU and alloc memory
float* gpu_env::makeTensor( int a, int b, int c, int d)
{
  float* devicePointer;
  error=cudaMalloc((void**)&devicePointer,a*b*c*d*sizeof(float));
  error_f();
  return devicePointer;
}
//destroy tensor
void gpu_env::destroyTensor(float* p)
{
  error=cudaFree(p);
  error_f();
}
//transfer scalar array
void gpu_env::set_sc(float* gpu, float sc, tensor_gpu_specs* sp)
{
  if (gpu==NULL)
    {fprintf(stderr,"Correctly allocate tensor in GPU and CPU\n");exit(-1);}

   //use Memset if int value, for float we need a kernel
     //error=cudaMemset(p,sc,size);
   dim3 dimBlock(sp->col);
   dim3 dimGrid(sp->row);
   long int ops=sp->batch*sp->row*sp->col*sp->featureMap;

   tensor_set_value<<<dimBlock,dimGrid>>>(gpu,sc,ops);
   error_f();
   error=cudaDeviceSynchronize();
   error_f();
}
//JUAN_FIX:implement function which stack all the device pointer to dealloc when error happens.
//transfer array to array
void gpu_env::copy_data(float* cpu, float* gpu,tr_type t,size_t size)
{
  if (cpu==NULL || gpu==NULL)
	{fprintf(stderr,"Correctly allocate tensor in GPU and CPU\n");exit(-1);}

  if (t==TOGPU)
    error=cudaMemcpy(gpu,cpu,size,cudaMemcpyHostToDevice);
  else if (t==FROMGPU)
{
    error=cudaMemcpy(cpu,gpu,size,cudaMemcpyDeviceToHost);
}
  else if (t==GPU)
    error=cudaMemcpy(cpu,gpu,size,cudaMemcpyDeviceToDevice);
  else
    {fprintf(stderr,"NOT IMPLEMENTED");exit(-1);} 

  error_f();
  error=cudaDeviceSynchronize();
  error_f();
}

/////////////////////////////////////
/////////Neural Networks/////////////
/////////////////////////////////////

//activation functions
void gpu_env::activation(float* E,float* N, int f,tensor_gpu_specs* sp)
{
if (E==NULL || N==NULL)
	{fprintf(stderr,"Fill data in pointer.\n");exit(-1);}
dim3 dimBlock;
dim3 dimGrid;
if (f==ACT_SOF)
{
 dimBlock.x=sp->row;
 dimGrid.x=1;
}
else
{
 dimBlock.x=sp->col;
 dimGrid.x=sp->row;
}
long int ops = sp->col*sp->row;
long int sample_dim=sp->col;

double alfa=1;
float* auxE=NULL;
switch(f)
{
  case ACT_RLU:
	ReLu<<<dimBlock,dimGrid>>>(E,N,ops);
	break;
  case ACT_ELU:
	ELU<<<dimBlock,dimGrid>>>(E,N,alfa,ops);
	break;
  case ACT_SOF:
       {
        ops=sp->row;
        auxE = makeTensor(sp->col,sp->row);
        set_sc(auxE, 0.0, sp);
	Softmax<<<dimBlock,dimGrid>>>(E,N,auxE,sample_dim,ops);
	break;
       }
  case ACT_SIG:
	Sigmoid<<<dimBlock,dimGrid>>>(E,N,ops);
	break;
  case ACT_LIN:
        //N=E;
        error = cudaMemcpy(N,E,sp->batch*sp->featureMap*sp->col*sp->row*sizeof(float),cudaMemcpyDeviceToDevice);
        break;
  default:
	fprintf(stderr,"Activation function not implemented\n");
	exit(-1);
}
error_f();
error=cudaDeviceSynchronize();
error_f();
if (auxE!=NULL)
	destroyTensor(auxE);
}
//derivative of activation functions
void gpu_env::dactivation(float* E, float* N,float* D, int f,tensor_gpu_specs* sp)
{
if (E==NULL || N==NULL || D==NULL)
	{fprintf(stderr,"Fill data in pointer.\n");exit(-1);}
dim3 dimBlock(sp->col);
dim3 dimGrid(sp->row);
long int ops = sp->row*sp->col;
long int sample_dim=sp->col*sp->row;

switch(f)
{
  case ACT_RLU:
	dReLu<<<dimBlock,dimGrid>>>(E,D,ops);
	break;
  case ACT_ELU:
	dELU<<<dimBlock,dimGrid>>>(E,N,D,ops);
	break;
  case ACT_SIG:
	dSigmoid<<<dimBlock,dimGrid>>>(E,D,ops);
	break;
  case ACT_LIN:
       set_sc(D,1.0,sp);      
       break;
  default:
	fprintf(stderr,"Activation function not implemented\n");
	exit(-1);
}
error_f();
error=cudaDeviceSynchronize();
error_f();

}


//loss functions
void gpu_env::compute_loss(float* T, float* N,loss_type t,tensor_gpu_specs* gsp,double* ent, double* cerr)
{
dim3 dimBlock(gsp->row);
dim3 dimGrid(1);
long int ops = gsp->row;

switch(t)
{
  case CE:
       {
       float* max_row=makeTensor(gsp->row);//store it from device but use in gpu
       int* cerr_g;
       error=cudaMalloc((void**)&cerr_g,sizeof(int));
       error_f();
       cudaMemset(cerr_g, 0, sizeof(int));
       error_f();
       MC_loss<<<dimBlock,dimGrid>>>(T,N,max_row,gsp->col,ops,cerr_g);
       error_f();
       cudaDeviceSynchronize(); 

       error_f();
       float* CE_vec;
       error=cudaMalloc((void**)&CE_vec,sizeof(float)*gsp->row*gsp->col);
       error_f();
       CE_loss<<<dimBlock,dimGrid>>>(N,max_row,CE_vec,gsp->col,ops);
       cudaDeviceSynchronize(); 
       error_f();
       float* result_ce;
       error=cudaMalloc((void**)&result_ce,sizeof(float));
       error_f(); 
       reduce_array_sum<<<dimGrid,dimBlock,ops*sizeof(float)>>>(CE_vec,ops, gsp->col,result_ce);
       cudaDeviceSynchronize(); 
       error_f();
       float aux1;
       error=cudaMemcpy(&aux1,result_ce,sizeof(float),cudaMemcpyDeviceToHost);
       error_f();
       *ent=(double)aux1;
       int aux=0;

       error=cudaMemcpy(&aux,cerr_g,sizeof(int),cudaMemcpyDeviceToHost);
       *cerr=(double)aux;
       destroyTensor(max_row);
       break;
       }
  case SSE:
	fprintf(stderr,"GPU COST NOT IMPLEMENTED\n");
	exit(-1);
	break;
  default:
	fprintf(stderr,"GPU COST NOT IMPLEMENTED\n");
	exit(-1);

}

}


/////////////////////////////////////////
///////////////gpu parsing///////////////
////////////////////////////////////////
void gpu_env::gpu_info(int selected_gpu)
{

int nDevices;
cudaGetDeviceCount(&nDevices);

if (selected_gpu>nDevices)
 {
  fprintf(stderr,"Error. GPU %d not available. Number of available GPU is %d. Further information running nvidia-smi\n",selected_gpu,nDevices);
  exit(-1);	
 }

fprintf(stderr,"Selecting GPU device %d\n",selected_gpu);
cudaSetDevice(selected_gpu);

cudaDeviceProp prop;
cudaGetDeviceProperties(&prop,selected_gpu);

fprintf(stderr,"Layers is running on GPU %s\n",prop.name);

gpuI.warpSize=prop.warpSize;
gpuI.maxThreadPerBlock=prop.maxThreadsPerBlock;

}


///////////////////////////////////////////
///////////////Linear Albegra//////////////
///////////////////////////////////////////

//MATRIX TO MATRIX OPERATIONS

//matrix operator
//Perform matrix produc c=a*b
//float pointer are matrix
//tensor_gpu_spcs matrix specifications
//tA and tB are for transposing matrix
// acc{0,1}->whether to accumulate result in C (1) or set (0)
void gpu_env::matMul(float* a,float* b,float* c, tensor_gpu_specs* sA,tensor_gpu_specs* sB, tensor_gpu_specs* sC, int acc, int tA, int tB)
{
//for the moment only available cublas for operation
	cublas.matrixProduct(a,b,c,sA,sB,sC,acc,tA,tB);
	error=cudaDeviceSynchronize();
	error_f();

}

//SCALAR VECTOR OPERATOR
void gpu_env::scVec(float* vec_o,float* vec_i, tensor_gpu_specs* sA, float sc ,int op,int acc)
{
//gpuI has info about GPU for kernel dimensions

if (op==0)
{
	dim3 dimBlock(sA->row);//maybe move this to declaration
	dim3 dimGrid(sA->col);
	long int ops = sA->row*sA->col;
	//add -> no blas operation (we could use same as product buth we should fill B in gpu and that is shit. Home made kernel)
	sc_add_mat<<<dimBlock,dimGrid>>>(vec_o,vec_i,sc,ops,acc);//could be same as matrix scalar operator because we treat as float*

	error_f();
	error=cudaDeviceSynchronize();
	error_f();
}
else if (op==1)
{
	//prod -> use same as matrix + matrix just matrix B is 0
        if (vec_o==NULL || vec_i==NULL)
		{printf("Error\n");exit(-1);} 
	error=cudaMemcpy(vec_o,vec_i,sA->row*sA->col*sizeof(float),cudaMemcpyDeviceToDevice);	
        error_f();
	cublas.sc_prod_vec(vec_o,vec_i,sc,sA,acc);
	error=cudaDeviceSynchronize();
	error_f();
}
else
	{fprintf(stderr,"Not implemented\n");exit(-1);}

}


//MATRIX SCALAR OPERATORS

//Scalar product/sum Matrix
//op{0,1}-> 0 is add and 1 is product
//acc{0,1}-> accumulate (1) or set (0)
void gpu_env::scMat(float* mat_o,float* mat_i, tensor_gpu_specs* sA, float sc ,int op,int acc)
{
//gpuI has info about GPU for kernel dimensions

if (op==0)
{
	dim3 dimBlock(sA->row);//maybe move this to declaration
	dim3 dimGrid(sA->col);
	long int ops = sA->row*sA->col;
	//add -> no blas operation (we could use same as product buth we should fill B in gpu and that is shit. Home made kernel)
	sc_add_mat<<<dimBlock,dimGrid>>>(mat_o,mat_i,sc,ops,acc);

	error_f();
	error=cudaDeviceSynchronize();
	error_f();
}
else if (op==1)
{
	//prod -> use same as matrix + matrix just matrix B is 0
	
	cublas.sc_prod_mat(mat_o,mat_i,sc,sA,acc);
	error=cudaDeviceSynchronize();
	error_f();
}
else
	{fprintf(stderr,"Not implemented\n");exit(-1);}

}

///////////////////////////////////////////
///////////ELEMENT WISE OPERATOR///////////
///////////////////////////////////////////
//(sum or product)
// op{0,1,2}->0 is add and 1 is product 2 is sqrt
//Division can be performed by multiplying by inverse and subtraction can be done as a sum using scb and sca correctly (with -)
// acc{0,1}->whether to accumulate result in C (1) or set (0)
//tA and tB are for transposing matrix
//sca and scb only available when sum is done. Not contemplate for el wise product as it is the same as making the product and then scalar dot product. We do not save memory performing this operation in the same operation as in the sum(where we first make a new float* with the result of scalar dot matrix and then sum)
void gpu_env::mat_elwise_mat(float* A, float* B, float* C,tensor_gpu_specs* sA,tensor_gpu_specs* sB,tensor_gpu_specs* sC,int op, int acc, int trA, int trB,float sca, float scb)
{
 
  if (op==0)
  {
	//transpose is done in cublas routine. We have cublas routine for this
	if (acc==0)
	{//not accumulateA
	  cublas.mat_ewsum_mat(A,B,C,sA,sB,trA,trB,sca,scb);	
	}
	else if (acc==1)
	{//accumulate

	 float* aux=makeTensor(sA->row,sA->col,1,1);
         set_sc(aux,0.0, sA);
         cublas.mat_ewsum_mat(A,B,aux,sA,sB,trA,trB,sca,scb);
	 cublas.mat_ewsum_mat(C,aux,C,sC,sC,0,0);
         destroyTensor(aux);
	}
  }
  else if(op==1) 
  {
	float* tA;
	float* tB;

	if (trA==1)
	{
	   //transpose A
	   tA=makeTensor(sA->row,sA->col,1,1);
           set_sc(tA,0.0, sA);
   	   cublas.mat_transp(tA,A,sA);
       	   error=cudaDeviceSynchronize();
	   error_f();

        }
	if (trB==1)
	{
	   //transpose B
	   tB=makeTensor(sB->row,sB->col,1,1);
           set_sc(tB,0.0, sB);
   	   cublas.mat_transp(tB,B,sB);
       	   error=cudaDeviceSynchronize();
	   error_f();

        }
	dim3 dimBlock(sA->col);//maybe move this to declaration
	dim3 dimGrid(sA->row);
	long int ops = sA->row*sA->col;
        

	if (trA==1 && trB==1)
        {
           mat_ewprod_mat<<<dimBlock,dimGrid>>>(C,tA,tB,acc,ops);
        }
	if (trA==1 && trB==0)
        {
          mat_ewprod_mat<<<dimBlock,dimGrid>>>(C,tA,B,acc,ops);
        }
	if (trA==0 && trB==1){mat_ewprod_mat<<<dimBlock,dimGrid>>>(C,A,tB,acc,ops);}
	if (trA==0 && trB==0){

            mat_ewprod_mat<<<dimBlock,dimGrid>>>(C,A,B,acc,ops);

         }

	error_f();
	error=cudaDeviceSynchronize();
	error_f();
	if (trA)
		destroyTensor(tA);
	if (trB)
		destroyTensor(tB);
	error_f(); 

  }
  else
      {fprintf(stderr,"Not implemented\n");exit(-1);}
}

//compare to tensor element by element
int gpu_env::tensor_equal(float* A, float* B,tensor_gpu_specs* sA)
{
  dim3 dimBlock(sA->col);//maybe move this to declaration
  dim3 dimGrid(sA->row);
  long int ops = sA->row*sA->col;

  kern_tensor_equal<<<dimBlock,dimGrid>>>(A,B,ops);
  error=cudaDeviceSynchronize();
  if (error==cudaErrorLaunchFailure)
	return 0;
  else if(error!=cudaSuccess)
	{fprintf(stderr,"Error launching gpu kernel: %s",cudaGetErrorString(error));
	exit(-1);}
  else
	return 1;

}

//elwise operator matrix vector
//op=0 is sum and 1 is prod
void gpu_env::mat_elwise_vec(float* mat_o,float* mat, float* vec, tensor_gpu_specs* sA,int op,int acc,float sca, float scb, int rdim)
{
//op 0 is sum
//op 1 is multiplication
//op 2 is division
if (rdim==1)
{
  dim3 dimBlock(sA->col);
  dim3 dimGrid(sA->row);
  long int ops = sA->row*sA->col;

  mat_ewcol_vec<<<dimBlock,dimGrid>>>(mat_o,mat,vec,ops,sA->col,op,acc,sca, scb);
}
else
{
  dim3 dimBlock(sA->col);
  dim3 dimGrid(sA->row);
  long int ops = sA->row*sA->col;

  mat_ewrow_vec<<<dimBlock,dimGrid>>>(mat_o,mat,vec,ops,sA->row,op,acc,sca, scb);
}

  error_f();
  error=cudaDeviceSynchronize();
  error_f();
}

//elwise operator vector vector

void gpu_env::vec_elwise_vec(float* A, float* B, float* C,tensor_gpu_specs* sA,int op, int acc,float sca, float scb)
{
 //trasposition is not contemplated. This is real programming not grandfather programming. 
  if (op==0)//sum
  {
    cublas.vec_sum_vec(C,B,A,sA,acc,sca,scb);
    error=cudaDeviceSynchronize();
    error_f();
 
  }
  else if(op==1) //product
  {
	
      {fprintf(stderr,"Not implemented\n");exit(-1);}
  }
  else
      {fprintf(stderr,"Not implemented\n");exit(-1);}
}
///////////////////////////////////////////////
/////////////////INPLACE OPERATOR//////////////
///////////////////////////////////////////////
void gpu_env::mat_inplace_mat(float* o, float* i,tensor_gpu_specs* si,int op, int acc)
{
  dim3 dimBlock(si->row);
  dim3 dimGrid(si->col);
  if (op==0)//sqrt
  {
    
  tensor_sqrt<<<dimGrid,dimBlock>>>(o,i, acc,si->col*si->row);
  }
  else
  {fprintf(stderr,"Not implemented mat_inplace_mat\n");exit(-1);}    
}


///////////////////////////////////////////////
///////////////REDUCTION OPERATOR//////////////
///////////////////////////////////////////////
//This operators should be programed manually using reduction
//techniques. For the moment we can use wonderfull thurst library
//or cuBlas. For performance self-programmed or cuBlas is better.
//We use cannonical float* whenever we can (always looking for avoiding
//warping divergence )
void gpu_env::sum_abs(float* p,tensor_gpu_specs* gsp,float* acc)
{
cublasStatus_t error_cb=cublasSasum(p_cublas,gsp->row*gsp->col,p,1,acc);
if (error_cb!=CUBLAS_STATUS_SUCCESS)
	fprintf(stderr,"Error calling sum_abs with cublasSasum routine\n");

}

void gpu_env::reduce_operator(float* p,tensor_gpu_specs* gsp,float* acc)
{
  float* sum_aux;
  error = cudaMalloc((void**)&sum_aux,sizeof(float));
  error_f();
  dim3 dimGrid(1);
  dim3 dimBlock(gsp->row);
  long int ops = gsp->row;
  reduce_array_sum<<<dimGrid,dimBlock,ops*sizeof(float)>>>(p,ops, gsp->col,sum_aux);
  cudaDeviceSynchronize();
  error_f();
  copy_data(acc,sum_aux,FROMGPU,sizeof(float));
 

}

void gpu_env::row_sum(float* A, tensor_gpu_specs* sA,float* B)
{
  dim3 dimBlock(sA->col);
  dim3 dimGrid(1);
  long int ops = sA->row;

  tensor_set_value<<<dimBlock,dimGrid>>>(B,0.0,sA->row);
  error_f();
  error=cudaDeviceSynchronize();
  error_f();

  kernel_row_sum<<<dimBlock,dimGrid>>>(A,B,(int)sA->row,(int)sA->col,ops);

  error_f();
  error=cudaDeviceSynchronize();
  error_f();
}


void gpu_env::col_sum(float* A, tensor_gpu_specs* sA,float* B)
{
  dim3 dimBlock(sA->col);
  dim3 dimGrid(1);
  long int ops = sA->col;

  tensor_set_value<<<dimBlock,dimGrid>>>(B,0.0,sA->col);
  error_f();
  error=cudaDeviceSynchronize();
  error_f();

  kernel_col_sum<<<dimBlock,dimGrid>>>(A,B,(int)sA->row,(int)sA->col,ops);
 
  error_f();
  error=cudaDeviceSynchronize();
  error_f();
  
}

int gpu_env::row_max(float* A, tensor_gpu_specs* sA,int ind)
{
//ind is the row index;
//use thrurst for this in future or cubla. As we copy to thurst we only copy the row we operate.
  if (ind > sA->row)
	{fprintf(stderr,"Error. Row not available\n");exit(-1);}
  cublasStatus_t error_cb;
 // printf ("===Indice pasado %d",ind);
  float *Aaux=A+ind*sA->col;
  int result;
  error_cb = cublasIsamax(p_cublas,sA->col,Aaux,1,&result);
  if (error_cb!=CUBLAS_STATUS_SUCCESS)
	{fprintf(stderr,"Error in cublas execution\n");exit(-1);}

//printf("====columns routine %d \n",sA->col);
//printf("====cublas routine %d \n",result);
   cudaDeviceSynchronize();
   error_f();
   return result;
} 

//////////////////////////////////////////////
///////////////RANDOM GENERATOR///////////////
//////////////////////////////////////////////
/*use host api -> when we need to save generated values. Easier to implement but poor performance:
	-on one side we store values on GPU so waste memory
        -on other side we cannot use generated values online->we loose time accesing memory for reading stored buffers

*/
void gpu_env::random_number_host_binary(float* rand_vec,tensor_gpu_specs* sp,float p)
{

  if(rand_vec==NULL)
     {fprintf(stderr,"Error. Allocate gpu Rand vector\n");exit(-1);}

  rand_error=curandGenerateUniform(random_generator,rand_vec,sp->row*sp->col*sp->batch*sp->featureMap);
  error_rand();
  error=cudaDeviceSynchronize();
  error_f();

  dim3 dimBlock(sp->col);
  dim3 dimGrid(sp->row);
  long int ops = sp->col*sp->row;


  drop_mask<<<dimBlock,dimGrid>>>(rand_vec,p,ops);
  error_f(); 
  error=cudaDeviceSynchronize();
  error_f();

}


void gpu_env::random_number_host_gaussian(float* rand_vec,tensor_gpu_specs* sp,float mean,float std)
{

 rand_error=curandGenerateNormal (random_generator, rand_vec, sp->row*sp->col*sp->batch*sp->featureMap,   mean,   std );

  error_rand();
  error=cudaDeviceSynchronize();
  error_f();

}

void gpu_env::add_noise(float* vec, float* rand_vec, float noiser, tensor_gpu_specs* sp)
{
  float* mask = makeTensor(sp->row,sp->col);
  rand_error=curandGenerateUniform(random_generator,mask,sp->row*sp->col*sp->batch*sp->featureMap);
  error_rand();
  error=cudaDeviceSynchronize();
  error_f();
  dim3 dimBlock(sp->col);
  dim3 dimGrid(sp->row);
  long int ops = sp->col*sp->row;

  add_noise_with_mask<<<dimBlock,dimGrid>>>(vec,rand_vec,mask,noiser,ops);
  error_f(); 
  error=cudaDeviceSynchronize();
  error_f();
  destroyTensor(mask);


}

/*
void gpu_env::random_number_device_binary(float* rand_vec,tensor_gpu_specs* sp,float p)
{
  if(rand_vec==NULL)
     {fprintf(stderr,"Error. Allocate gpu Rand vector\n");exit(-1);}

  //for avoid to kernel launch(one for generating and one for rounding we do in one. However we take care of actual state)
  rand_error=curandGenerateUniform(random_generator,rand_vec,sp->row*sp->col*sp->batch*sp->featureMap);
  error_rand();
  error=cudaDeviceSynchronize();
  error_f();
  

}
*/



