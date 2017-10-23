#ifndef _GGPU_ENV_
#define _GGPU_ENV_
#include "../utils.h"
#include "cublas_env.h"

class gpu_env
{
private:
void error_f();
void error_rand();
cudaError_t error;
cublas_env cublas;

public:
gpu_env();
void gpu_info(int selected_gpu);

//memory managment
float* makeTensor(int a, int b=1,int c=1, int d=1);
void destroyTensor(float* p);
void copy_data(float* cpu, float* gpu, tr_type t, size_t size);
void set_sc(float* gpu, float sc, tensor_gpu_specs* sp);//set scalar;

//neural networks
void activation(float* E,float* N, int f,tensor_gpu_specs* sp);
void dactivation(float* E,float* N,float* D, int f, tensor_gpu_specs* sp);

//linear algebra
void matMul(float* a,float* b,float* c, tensor_gpu_specs* sA,tensor_gpu_specs* sB, tensor_gpu_specs* sC, int acc, int tA, int tB);
void scMat(float* mat_o,float* mat_i, tensor_gpu_specs* sA, float sc ,int op,int acc);
void scVec(float* vec_o,float* vec_i, tensor_gpu_specs* sA, float sc ,int op,int acc);

//elwise operator
void mat_elwise_mat(float* A, float* B, float* C,tensor_gpu_specs* sA,tensor_gpu_specs* sB,tensor_gpu_specs* sC,int op, int acc, int tA, int tB,float sca=1.0, float scb=1.0);
int tensor_equal(float* A, float* B, tensor_gpu_specs* sA);
void mat_elwise_vec(float* mat, float* vec, tensor_gpu_specs* sA,int op);
void vec_elwise_vec(float* A, float* B, float* C,tensor_gpu_specs* sA,int op, int acc,float sca=1.0, float scb=1.0);

//self operator
float* col_sum(float* A, tensor_gpu_specs* sA);
int row_max(float* A, tensor_gpu_specs* sA,int ind );

//random number

void add_noise(float* vec, float* rand_vec,float noiser, tensor_gpu_specs* sp);
void random_number_host_gaussian(float* rand_vec,tensor_gpu_specs* sp,float mean,float std);
void random_number_host_binary(float* rand_vec,tensor_gpu_specs* sp,float p);

};

#endif














