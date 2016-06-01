CXX = g++

# FOR LINUX
CXXFLAGS = -fopenmp -I Eigen -lpthread -lm  -O3 

# FOR MAC:
#CXXFLAGS = -I Eigen -O3 


all: utils.o data.o layer.o flayer.o clayer.o player.o net.o layers ascii2bin

utils: utils.cpp utils.h
	$(CXX) $(CXXFLAGS) -c utils.cpp

data: data.cpp data.h
	$(CXX) $(CXXFLAGS) -c data.cpp

layer: layer.cpp layer.h 
	$(CXX) $(CXXFLAGS) -c layer.cpp

flayer: flayer.cpp layer.h 
	$(CXX) $(CXXFLAGS) -c flayer.cpp

clayer: clayer.cpp layer.h 
	$(CXX) $(CXXFLAGS) -c clayer.cpp

player: player.cpp layer.h 
	$(CXX) $(CXXFLAGS) -c player.cpp

catlayer: catlayer.cpp layer.h 
	$(CXX) $(CXXFLAGS) -c catlayer.cpp

net: net.cpp net.h
	$(CXX) $(CXXFLAGS) -c net.cpp

ascii2bin: ascii2bin.cpp data.o
	$(CXX) $(CXXFLAGS) -o ascii2bin ascii2bin.cpp data.o

layers: main.cpp  utils.o data.o layer.o flayer.o clayer.o player.o net.o catlayer.o
	$(CXX) $(CXXFLAGS) -o layers main.cpp utils.o data.o layer.o flayer.o clayer.o player.o net.o catlayer.o
clean: 
	rm *.o 

