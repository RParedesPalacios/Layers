# Layers source code

## Compile and install

> 
> you need to have **g++** and **make** installed, and the **Flex** library to link the parser (-lfl). In case you want to modify the parser (but this is no requiered for normal installation) you would need Bison  as well.
>


~~~shell
cd src
make clean
make CORE=0 ## FOR CPU
make CORE=1 ## FOR GPU, check CudaNN is installed and LD_LIBRARY_PATH set
~~~

By default a Linux target is selected with standard optimizations but you can choose other systems and optimizations, see table

| TARGET | OPT  | SYSTEM  | AVX  | SSE  | Debug  |
|---|---|---|---|---|---|
| 1  | 1  | Linux  | YES  | NO  | NO |
| 1  | 2  | Linux  | NO |  YES | NO  |
| 1  | 3  | Linux  | NO  | NO  | NO  |
| 1  | 4  | Linux  | NO  | NO  | Yes |
|  |   |  | | | |
| 2  | 1  | MAC  | YES  | NO  | NO |
| 2  | 2  | MAC  | NO |  YES | NO  |
| 2  | 3  | MAC  | NO  | NO  | NO  |
| 2  | 4  | MAC  | NO  | NO  | Yes |

__Default values, TARGET=1, OPT=3__


Example for LINUX using AVX instruction set:

~~~shell
make CORE=0 TARGET=1 OPT=1
~~~

or for MAC:

~~~shell
make CORE=0 TARGET=2 
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





