#include <cuda.h>
#include <cuda_runtime_api.h>
#include <string.h>
#include <cublas_v2.h>
#include <stdio.h>

//
#include "../utils.h"
#include "execution.h"
#include "cublas_env.h"

//global variables for all program
extern bool isYes;
extern cublasHandle_t p_cublas;
extern cublasStatus_t status;
extern gpu_specs gpuI;
////

static const char *_cudaGetErrorEnum(cublasStatus_t error)
{
    switch (error)
    {
        case CUBLAS_STATUS_SUCCESS:
            return "CUBLAS_STATUS_SUCCESS";

        case CUBLAS_STATUS_NOT_INITIALIZED:
            return "CUBLAS_STATUS_NOT_INITIALIZED";

        case CUBLAS_STATUS_ALLOC_FAILED:
            return "CUBLAS_STATUS_ALLOC_FAILED";

        case CUBLAS_STATUS_INVALID_VALUE:
            return "CUBLAS_STATUS_INVALID_VALUE";

        case CUBLAS_STATUS_ARCH_MISMATCH:
            return "CUBLAS_STATUS_ARCH_MISMATCH";

        case CUBLAS_STATUS_MAPPING_ERROR:
            return "CUBLAS_STATUS_MAPPING_ERROR";

        case CUBLAS_STATUS_EXECUTION_FAILED:
            return "CUBLAS_STATUS_EXECUTION_FAILED";

        case CUBLAS_STATUS_INTERNAL_ERROR:
            return "CUBLAS_STATUS_INTERNAL_ERROR";
    }

    return "<unknown>";
}
cublas_env::cublas_env()
{
alfa=1;
}
//Private:
//Check for cuBlas initialization
void cublas_env::check()
{
if (!isYes)
	{fprintf(stderr,"Cublas Enviroment not created\n");exit(1);}
}

//Check for cuBlas execution
void cublas_env::error()
{
if ( status!=  CUBLAS_STATUS_SUCCESS)
{
   fprintf(stderr,"Problem in cuBlas execution getting: %s\n",_cudaGetErrorEnum(status));
   exit(1);

}
}

//Destroy handle
/*void cublas_env::destroyHandle()
{
check();
status = cublasDestroy(p_cublas);
error();
isYes=0;
}

//Create handle
void cublas_env::createHandle()
{
status = cublasCreate(&p_cublas);

error();

isYes=1;
}*/

//Set atomic mode operation or not
void cublas_env::setAtomicMode(bool flag)
{
check();
if (flag)
	status = cublasSetAtomicsMode(p_cublas, CUBLAS_ATOMICS_ALLOWED);
else
	status = cublasSetAtomicsMode(p_cublas, CUBLAS_ATOMICS_NOT_ALLOWED);

error();
}

//ALGEBRA OPERATOR

//Matrix to Matrix Operator

//Product
void cublas_env::matrixProduct(float* A, float* B, float* C,tensor_gpu_specs* sA, tensor_gpu_specs* sB, tensor_gpu_specs* sC,int acc,int tA, int tB)
{
//Cublas is inspired in blas. blas is fortran library an thus it uses column major order. Layers is written in c-style. However 
//it can be easily performed: C=A*B; A*B=(B'*A')'; C'=(B'*A'). So we need only to perform B*A as cublas implicitly transpose B and A and we read C in row major order
//so implicitly do transposition
beta=(float)acc;
cublasOperation_t trA = CUBLAS_OP_N;
cublasOperation_t trB = CUBLAS_OP_N;
ldA=sA->col;
ldB=sB->col;
ldC=sB->col;
m=sB->col;
n=sA->row;
k=sB->row;

if (tA==1)
{
	trA = CUBLAS_OP_T;
	n=sA->col; 
}
if (tB==1)
{
	trB = CUBLAS_OP_T;
   	m=sB->row;
	k=sB->col;
        ldC=sB->row;//leading dimension is only affected when transposing B (C=B*A). We have to take columns of the output C which is normally col, however because of trasposition the output col will be row.
}

status = cublasSgemm(p_cublas,trB,trA,m,n,k,&alfa,B,ldB,A,ldA,&beta,C,ldC);

error();

}

//Elwise sum
void cublas_env::mat_ewsum_mat(float* A, float* B, float* C,tensor_gpu_specs* sA,tensor_gpu_specs* sB, int tA, int tB,float sca,float scb)
{

cublasOperation_t trA = CUBLAS_OP_N;
cublasOperation_t trB = CUBLAS_OP_N;

m=sA->col;
n=sB->row;
ldA=sA->col;
ldB=sB->col;
ldC=sA->col;

if (tA==1)
{
	trA = CUBLAS_OP_T;
	m=sA->row;
	ldC=sA->row;
}
if (tB==1)
{
	trB = CUBLAS_OP_T;
	n=sB->col;
	
}

alfa=sca;
beta=scb;
status = cublasSgeam(p_cublas,trA,trB, m,n,&alfa,A,ldA,&beta,B,ldB,C,ldC);
error();

}


//Matrix to scalar operator: either sum or product sc*A or sc+A->only product, sum is not contemplated
void cublas_env::sc_prod_mat(float* mat_o, float* mat_i,float sc,tensor_gpu_specs* sC,int acc)
{
//inc=0 means overlap over C
//inc=1 means increments over C

beta=(float)acc;
m=sC->col;
n=sC->row;
ldA=sC->col;
ldB=sC->col;
ldC=sC->col;


status = cublasSgeam(p_cublas, CUBLAS_OP_N,CUBLAS_OP_N, m,n,&sc,mat_i,ldA,&beta,mat_o,ldB,mat_o,ldC);

error();

}

//Scalar to vector operator
void cublas_env::sc_prod_vec(float* vec_o, float* vec_i,float sc,tensor_gpu_specs* sC,int acc)
{
//inc=0 means overlap over C
//inc=1 means increments over C
cudaError_t error_cuda;
if (acc==0)
        {
	error_cuda=cudaMemcpy(vec_o,vec_i,sC->row*sC->col*sizeof(float),cudaMemcpyDeviceToDevice);	
	if(error_cuda!=cudaSuccess)
   		{fprintf(stderr,"Error memory transfer %s\n",cudaGetErrorString(error_cuda));exit(-1);}
	status=cublasSscal(p_cublas, sC->row*sC->col, &sc, vec_o, 1);

         }

if (acc==1)
    {
    fprintf(stderr,"Not chequed cublas scalar vector product\n");
    exit(-1);
    status=cublasSaxpy(p_cublas, sC->row*sC->col , &sc, vec_i, sizeof(float), vec_o, sizeof(float));

    }


error();
}

//vector to vector operator
void cublas_env::vec_sum_vec(float* vec_o, float* vec_i1,float* vec_i2,tensor_gpu_specs* sC,int acc,float sca, float scb)
{
//acc=0 means overlap over C
//acc=1 means increments over C

//first as cublas routine overwrite result we need to save input
cudaError_t error_cuda;

if (acc==0)
        {
	//vec_o=vec_i2*scb;
	sc_prod_vec(vec_o,vec_i2,scb,sC,0);
        error_cuda=cudaDeviceSynchronize();
	if(error_cuda!=cudaSuccess)
   		{fprintf(stderr,"Error sync%s\n",cudaGetErrorString(error_cuda));exit(-1);}

        //vec_o=sca*vec_i1+vec_o=sca*vec_i1+scb*vec_i2
        status=cublasSaxpy(p_cublas, sC->row*sC->col , &sca, vec_i1, 1, vec_o, 1);
	error();
        }

if (acc==1)
        {
	//vec_o+=vec_i2*scb;
	sc_prod_vec(vec_o,vec_i2,scb,sC,1);
        error_cuda=cudaDeviceSynchronize();
	if(error_cuda!=cudaSuccess)
   		{fprintf(stderr,"Error sync%s\n",cudaGetErrorString(error_cuda));exit(-1);}

	//vec_o+=vec_i1*sca;
	sc_prod_vec(vec_o,vec_i1,sca,sC,1);
        
        }


}


//Matrix transposition
void cublas_env::mat_transp(float* output, float* input, tensor_gpu_specs* sInp)
{
//cannot perform in place tranposition an thus we need an output array 
beta=0.0;
alfa=1.0;
n=sInp->col;
m=sInp->row;
ldA=n;
ldB=sInp->row;
ldC=sInp->row;
status = cublasSgeam(p_cublas, CUBLAS_OP_T,CUBLAS_OP_N, m,n,&alfa,input,ldA,&beta,output,ldB,output,ldC);
error();

}



