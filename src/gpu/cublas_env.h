#ifndef _GCUBLASCLASS_
#define _GCUBLASCLASS_

#include <cublas_v2.h> 

#include "../utils.h"
#include  "execution.h"


class cublas_env
{
private:
//bool isYes;
void check();
void error();
float beta;
float alfa;
int m,n,k,ldA,ldB,ldC;
public:

//static cublasHandle_t p_cublas;
//static cublasStatus_t status;

cublas_env();
//void createHandle();
//void destroyHandle();
void setAtomicMode(bool flag);
void matrixProduct(float* A, float* B, float* C,tensor_gpu_specs* sA, tensor_gpu_specs* sB, tensor_gpu_specs* sC,int acc, int tA, int tB);
void mat_ewsum_mat(float* A, float* B, float* C,tensor_gpu_specs* sA,tensor_gpu_specs* sB, int tA, int tB,float sca=1.0,float scb=1.0);
void sc_prod_mat(float* mat_o, float* mat_i,float sc,tensor_gpu_specs* sC,int acc);
void mat_transp(float* output, float* input, tensor_gpu_specs* sInp);

void sc_prod_vec(float* vec_o, float* vec_i,float sc,tensor_gpu_specs* sC,int acc);


void vec_sum_vec(float* vec_o, float* vec_i1,float* vec_i2,tensor_gpu_specs* sC,int acc,float sca, float scb);
};
#endif
