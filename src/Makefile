###########################################################################
OBJ =	nettable.o asin.o alex.o utils.o data.o layer.o flayer.o \
	clayer.o player.o catlayer.o net.o

all:	$(OBJ) ascii2bin layers
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

# FOR LINUX
LIBFLAGS = -lpthread -lm -lfl
CXXFLAGS = -fopenmp -I Eigen -O3

# FOR MAC:
#CXXFLAGS = -I . -O3

utils:	utils.cpp utils.h
	$(CXX) $(CXXFLAGS) -c utils.cpp

data:	data.cpp data.h
	$(CXX) $(CXXFLAGS) -c data.cpp

layer:	layer.cpp layer.h
	$(CXX) $(CXXFLAGS) -c layer.cpp

flayer:	flayer.cpp layer.h
	$(CXX) $(CXXFLAGS) -c flayer.cpp

clayer:	clayer.cpp layer.h
	$(CXX) $(CXXFLAGS) -c clayer.cpp

player:	player.cpp layer.h
	$(CXX) $(CXXFLAGS) -c player.cpp

catlayer: catlayer.cpp layer.h
	$(CXX) $(CXXFLAGS) -c catlayer.cpp

net:	net.cpp net.h
	$(CXX) $(CXXFLAGS) -c net.cpp

ascii2bin: ascii2bin.cpp data.o
	$(CXX) $(CXXFLAGS) -o ascii2bin ascii2bin.cpp data.o

layers:	main.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) -o layers main.cpp $(OBJ) $(LIBFLAGS)
clean:
	rm *.o
	rm -f alex.c asin.c asin.h
###########################################################################
