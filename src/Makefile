#############################
# FOR LINUX
############################

## REGULAR
#LIBFLAGS = -lm -lfl
#CXXFLAGS = -fopenmp -I Eigen -O3

## SIMD instructions SSE2 ENABLED
#LIBFLAGS = -lm -lfl 
#CXXFLAGS = -fopenmp -I Eigen -march=native -msse2 -O3

## SIMD instructions AVX ENABLED
LIBFLAGS = -lm -lfl 
CXXFLAGS = -fopenmp -I Eigen -march=native -mavx -O3
## DEBUGING
#LIBFLAGS = -lm -lfl
#CXXFLAGS = -fopenmp -I Eigen -g

############################
# FOR MAC:
############################
#CXXFLAGS = -I . -O3
#LIBFLAGS = -ll

##GPU FLAGS
GPU_CXXFLAGS = 
GPU_LIBFLAGS =
LAYERS = layers


##########################################################################Eige
OBJ =	asin.o alex.o nettable.o utils.o data.o layer.o flayer.o \
	clayer.o player.o catlayer.o net.o tensor.o addlayer.o olayer.o
GPU_OBJ =


all: checkGPU

#---------------------------------- Compile for GPU
checkGPU:
#compile for GPU
ifdef CORE

ifeq ($(CORE),1)
cuda_path := $(LAYERS_CUDA_PATH)

ifeq ($(cuda_path),)
$(error Set enviroment variable LAYERS_CUDA_PATH with directory to cuda)
endif

	CXXFLAGS :=  $(CXXFLAGS) -DfGPU -I $(cuda_path)include/
	GPU_CXXFLAGS := -I $(cuda_path)include/ -L  $(cuda_path)lib64/ -DfGPU
	GPU_OBJ := execution.o cublas_env.o gpu_env.o gpu_kernels.o
        GPU_LIBFLAGS := -lcudart -lcublas -lcurand
	GPU_CXX := $(cuda_path)bin/nvcc
	LAYERS = layers
#ifeq ($(GPU),CUDNN)
#	GPU_LIBFLAGS := $(GPU_LIBFLAGS) -lcudnn
#	CXXFLAGS := $(CXXFLAGS) -DfCUDNN
#endif
endif
else
ifneq ($(MAKECMDGOALS),clean)
$(error Execute make CORE=0 for CPU compiling and make CORE=1 for gpu and cpu compiling)
endif
endif

all: $(GPU_OBJ) $(OBJ) bin2ascii ascii2bin $(LAYERS)
#---------------------------------- Netparser
C_OPT = -pedantic
C_OBJ    = alex.o asin.o 

nettable.o: nettable.c
	gcc -c nettable.c $(C_OPT)

asin.o:	asin.c
	gcc -c asin.c  $(C_OPT)

alex.o: alex.c asin.c
	gcc -c alex.c  $(C_OPT)

asin.c: asin.y
	bison -oasin.c -d asin.y

alex.c: alex.l 
	flex -oalex.c alex.l
#---------------------------------- layers
CXX = g++

utils:	utils.cpp utils.h
	$(CXX) $(CXXFLAGS) -c utils.cpp

tensor: tensor.cpp tensor.h utils.h
	$(CXX) $(CXXFLAGS) -c tensor.cpp

data:	data.cpp data.h utils.h
	$(CXX) $(CXXFLAGS) -c data.cpp

layer:	layer.cpp layer.h utils.h
	$(CXX) $(CXXFLAGS) -c layer.cpp

flayer:	flayer.cpp layer.h utils.h tensor.h
	$(CXX) $(CXXFLAGS) -c flayer.cpp

clayer:	clayer.cpp layer.h utils.h tensor.h
	$(CXX) $(CXXFLAGS) -c clayer.cpp

player:	player.cpp layer.h utils.h 
	$(CXX) $(CXXFLAGS) -c player.cpp

catlayer: catlayer.cpp layer.h utils.h 
	$(CXX) $(CXXFLAGS) -c catlayer.cpp

addlayer: addlayer.cpp layer.h utils.h
	$(CXX) $(CXXFLAGS) -c addlayer.cpp

olayer: olayer.cpp layer.h utils.h
	$(CXX) $(CXXFLAGS) -c olayer.cpp

net:	net.cpp net.h utils.h tensor.h
	$(CXX) $(CXXFLAGS) -c net.cpp

#---------------------------------- gpu code
cublas_env.o: ./gpu/cublas_env.h ./utils.h  ./gpu/execution.h
	$(GPU_CXX) $(GPU_CXXFLAGS) $(GPU_LIBFLAGS) -c ./gpu/cublas_env.cu

gpu_env.o: ./gpu/gpu_env.h ./gpu/gpu_kernels.h ./utils.h ./gpu/execution.h
	$(GPU_CXX) $(GPU_CXXFLAGS) $(GPU_LIBFLAGS) -c ./gpu/gpu_env.cu

gpu_kernels.o:  ./gpu/gpu_kernels.h ./utils.h  
	$(GPU_CXX) $(GPU_CXXFLAGS) $(GPU_LIBFLAGS) -c ./gpu/gpu_kernels.cu

execution.o: ./gpu/gpu_env.h ./utils.h 
	$(GPU_CXX) $(GPU_CXXFLAGS) $(GPU_LIBFLAGS) -c ./gpu/execution.cu

#-------------------------

ascii2bin: ascii2bin.cpp data.o utils.o $(GPU_OBJ) 
	$(CXX) $(CXXFLAGS) $(GPU_CXXFLAGS)  -o ascii2bin ascii2bin.cpp data.o utils.o $(GPU_OBJ) $(GPU_LIBFLAGS)

bin2ascii: bin2ascii.cpp data.o utils.o
	$(CXX) $(CXXFLAGS)  $(GPU_CXXFLAGS) -o bin2ascii bin2ascii.cpp data.o utils.o  $(GPU_OBJ) $(GPU_LIBFLAGS)

$(LAYERS): main.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) $(GPU_CXXFLAGS) -o $(LAYERS) main.cpp $(OBJ) $(GPU_OBJ) $(LIBFLAGS) $(GPU_LIBFLAGS)
clean:
	rm *.o 


###########################################################################




















