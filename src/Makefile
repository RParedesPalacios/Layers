###########################################################################Eige
OBJ =	asin.o alex.o nettable.o utils.o tensor.o data.o layer.o flayer.o \
	clayer.o player.o catlayer.o addlayer.o olayer.o net.o

all:	$(OBJ) ascii2bin bin2ascii layers
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
	flex -o alex.c alex.l
#---------------------------------- layers
CXX = g++
MKLROOT=/opt/intel/mkl

############################
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

# FOR INTEL MKL
# you need to install the libmkl libs 
#LIBFLAGS =  -Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_lp64.a ${MKLROOT}/lib/intel64/libmkl_gnu_thread.a ${MKLROOT}/lib/intel64/libmkl_core.a -Wl,--end-group -lm -ldl -lfl
#CXXFLAGS = -m64 -I${MKLROOT}/include -fopenmp -mavx -I Eigen -O3  


## DEBUGING
#LIBFLAGS = -lm -lfl
#CXXFLAGS = -fopenmp -I Eigen -g



############################
# FOR MAC:
############################
CXXFLAGS = -I . -O3
LIBFLAGS = -ll

utils:	utils.cpp utils.h
	$(CXX) $(CXXFLAGS) -c utils.cpp

tensor:	tensor.cpp tensor.h utils.h
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

net:	net.cpp net.h utils.h
	$(CXX) $(CXXFLAGS) -c net.cpp

ascii2bin: ascii2bin.cpp data.o utils.o
	$(CXX) $(CXXFLAGS) -o ascii2bin ascii2bin.cpp data.o utils.o

bin2ascii: bin2ascii.cpp data.o utils.o
	$(CXX) $(CXXFLAGS) -o bin2ascii bin2ascii.cpp data.o utils.o

layers:	main.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) -o layers main.cpp $(OBJ) $(LIBFLAGS)
clean:
	rm *.o *~
###########################################################################
