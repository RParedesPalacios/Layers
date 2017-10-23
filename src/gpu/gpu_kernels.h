#ifndef GPUKERN
#define GPUKERN

///////////////NEURAL NETWORKS/////////////////
__global__ void ReLu(float* E,float* N, long int total_ops );
__global__ void ELU(float* E,float* N,float alfa, long int total_ops );
__global__ void Sigmoid(float* E,float* N, long int total_ops );
__global__ void Softmax(float* E,float* N,float* auxE ,long int sample_dim, long int n_vals);
__global__ void dReLu(float* E,float* D, long int total_ops);
__global__ void dSigmoid(float* E,float* D, long int total_ops);
__global__ void dELU(float *E,float* N,float* D, long int total_ops);
///////////////////////////////////////////////////
////////////////LINEAR ALGEBRA/////////////////////
///////////////////////////////////////////////////
__global__ void sc_add_mat(float* mat_o, float* mat_i, float sc, long int total_ops, int acc);


///////////////////////////////////////////
//////////ELEMENT WISE OPERATOR////////////
///////////////////////////////////////////

__global__ void mat_ewprod_mat(float* mat_o,float* mat_i1, float* mat_i2,int acc ,long int total_ops);
__global__ void kern_tensor_equal(float* A, float* B, long int ops);
__global__ void mat_ewcol_vec(float* mat, float* vec,long int ops, long int cols,int op);


////////////////////////////////////////////
////////////MEMORY MANAGMENT////////////////
////////////////////////////////////////////
__global__ void tensor_set_value(float* A, float value, long int total_ops);

////////////////////////////////////////////
////////////SELF OPERATOR///////////////////
////////////////////////////////////////////
__global__ void kernel_col_sum(float* A,float* O,int rows, int cols ,long int ops);

///////////RANDOM/////////////////////////
__global__ void drop_mask(float* rand_vec,float p,long int ops);
__global__ void add_noise_with_mask(float* nn_vector,float* rand_vec,float* mask,float noiser,long int ops);


#endif
