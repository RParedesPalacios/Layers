# Layers source code

## Compile and install

> 
> you need to have **g++** and **make** installed
>


~~~shell
cd src
make clean
make ## will run with default compiling setting, see below
make install
~~~
~~~

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
|  |   |  | | | |
| 3  | 1  | POWER7  | --  | --  | no |
| 3  | 2  | POEWR8  | -- |  -- | no  |
| 3  | 3  | POWER9  | --  | --  | no  |
| 3  | 4  | POWER  | --  | --  | YES |


__Default values, TARGET=1, OPT=3__


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

### IBM POWER

On IBM POWER, VSX and Altivec instruction sets are activated. Running on POWER requieres 
to use the OMP\_NUM\_THREADS directive:

~~~shell
OMP_NUM_THREADS=8 layers file.net
~~~

Also is recommended to reduce smt:

~~~shell
sudo ppc64_cpu --smt=1
~~~

Or deactivate it:

~~~shell
sudo ppc64_cpu --smt=off
~~~

Select cores:

~~~shell
sudo ppc64_cpu --cores-on=16
~~~

### Install

~~~shell
make install
~~~

will copy the binaries to /usr/local/bin 







