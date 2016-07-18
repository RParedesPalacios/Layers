#include "Eigen/Dense"

using namespace Eigen;

#define USE_DOUBLE

#ifdef USE_DOUBLE
typedef MatrixXd LMatrix;
typedef RowVectorXd LRVector;
typedef VectorXd LVector;
typedef double Ltype;
#else
typedef MatrixXf LMatrix;
typedef RowVectorXf LRVector;
typedef VectorXf LVector;
typedef float Ltype;
#endif
