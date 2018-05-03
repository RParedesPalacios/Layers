# Layers source code

## Compile and install

> 
> you need to have **g++** and **make** installed, and the **Flex** library to link the parser (-lfl). In case you want to modify the parser (but this is not requiered for normal installation) you would need Bison  as well.
>


~~~shell
cd src
make clean
make ## will run with default compiling setting, see below
make install
~~~

Compiling on CPU or GPU can be selected with the CORE parameter:

~~~shell
make CORE=0 ## FOR CPU (Default)
make CORE=1 ## FOR GPU, check CudaNN is installed and LD_LIBRARY_PATH set
~~~

On how to install NVIDIA GPU Libraries [here](https://github.com/RParedesPalacios/Layers/blob/master/src/gpu_install.md)

## Target system and CPU optimizations

By default a Linux target is selected with standard optimizations but you can choose other systems and optimizations, see table

| TARGET | OPT  | SYSTEM  | AVX  | SSE  | Debug  |
|---|---|---|---|---|---|
| 1  | 1  | Linux  | YES  | no  | no |
| 1  | 2  | Linux  | no |  YES | no  |
| 1  | 3  | Linux  | no  | no  | no  |
| 1  | 4  | Linux  | no  | no  | Yes |
|  |   |  | | | |
| 2  | 1  | MAC  | YES  | no  | no |
| 2  | 2  | MAC  | no |  YES | no  |
| 2  | 3  | MAC  | no  | no  | no  |
| 2  | 4  | MAC  | no  | no  | YES |

__Default values, CORE=0, TARGET=1, OPT=3__


Example for LINUX using AVX instruction set:

~~~shell
make CORE=0 TARGET=1 OPT=1
~~~

or for MAC:

~~~shell
make CORE=0 TARGET=2 
~~~

or GPU and Linux:

~~~shell
make CORE=1 TARGET=1 
~~~


### Compiling on MAC:

We suggest to install GCC from Homebrew to support openmp:

~~~shell
brew install gcc --without-multilib
~~~

Modify this line in Makefile to the suitable g++ version:

~~~c
CXX= g++-7
~~~

### Install

~~~shell
make install
~~~

will copy the binaries to /usr/local/bin 







