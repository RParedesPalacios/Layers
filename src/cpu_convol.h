#include "tensor.h"

void ConvolF(Tensor *N, Tensor *K, Tensor *E,int stride, int pad,int threads,int batch);

void ConvolBGrad(Tensor *N, Tensor *gK, Tensor *D,int stride, int pad,int threads,int batch);

void ConvolBDelta(Tensor *ID, Tensor *K, Tensor *D,int stride, int pad,int threads,int batch);
