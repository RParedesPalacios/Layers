//#define MKL 

#ifdef MKL 
#define EIGEN_USE_MKL_ALL
#endif

#include "Eigen/Dense"

using namespace Eigen;

//#define USE_DOUBLE

#ifdef USE_DOUBLE
typedef MatrixXd LMatrix;
typedef RowVectorXd LRVector;
typedef VectorXd LVector;
typedef double Ltype;
#else
typedef MatrixXf LMatrix;
typedef RowVectorXf LRVector;
typedef VectorXf LVector;
typedef float LType;
#endif

#define FLAYER 1
#define CLAYER 2
#define ICLAYER 21
#define PLAYER 3
#define CATLAYER 4
#define ADDLAYER 5
#define OLAYER 6

#define ACT_LIN 0
#define ACT_RLU 1
#define ACT_SIG 2
#define ACT_ELU 3
#define ACT_SOF 10

#define UNSET -1

//OPERATORS

// Binary
#define OP_SUM 1
#define OP_SUB 2
#define OP_IMULT 3
#define OP_OMULT 4
#define OP_DIV 5
/// Unary
#define OP_SIGM 21
#define OP_TANH 22
#define OP_LOG 23
#define OP_RELU 24
