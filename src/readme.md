# Layers source code

## Compile and install

> 
> you need to have **g++** and **make** installed, and the **Flex** library to link the parser (-lfl). In case you want to modify the parser (but this is no requiered for normal installation) you would need Bison  as well.
>

### **Since version V.04 the compilation is just straightforward:**

~~~shell
cd src
make clean
make CORE=0 ## FOR CPU
make CORE=1 ## FOR GPU, check CudaNN is installed and LD_LIBRARY_PATH set
~~~

### Compiling on MAC:


* Use the MAC Flags that appear in the Makefile

* You need some alternative to:
 
 clock_gettime and CLOCK_MONOTONIC
 
* See this stackoverflow [post](http://stackoverflow.com/questions/5167269/clock-gettime-alternative-in-mac-os-x) or just **comment the following line in the net.cpp**

~~~c
#define USETIME 
~~~

* In case you use a gcc compiler from Homebrew, unlink it and use the default gcc installed:

~~~c
brew unlink gcc
~~~





