# Layers source code

## Compile and install

> 
> you need to have **g++** and **make** installed, and the **Flex** library to link the parser (-lfl). In case you want to modify the parser (but this is no requiered for normal installation) you would need Bison  as well.
>

### **Since version V.04 the compilation is just straightforward:**

~~~shell
cd src
make clean
make
~~~


DONE!

### Compiling on MAC:

* You need some alternative to:
 
 clock_gettime and CLOCK_MONOTONIC
 
* See this stackoverflow [post](http://stackoverflow.com/questions/5167269/clock-gettime-alternative-in-mac-os-x) or just comment the following line in the net.cpp:

~~~c
#define USETIME 
~~~

* Use the MAC Flags that appear in the Makefile


### Compiling on Windows:

* Try and push it! ...  ¯\\\_(ツ)_/¯ 



## Changelog

### V0.4 - September 2016

Thanks to [**Jose Miguel Benedí**](http://users.dsic.upv.es/~jbenedi/) now we have a full integration of the parser inside Layers


### V0.3 - June 2016

* New functions for data:
	* center
	* div
* New parameters for data:
	* balance
* Added a types.h to change from float to double precision
* Other improvements

* Note: **Parser must be compiled**

### V0.2 - June 2016

* New functions available:
	* Network save and load are now available. 
	* Write the output of test data is also available
	* Write out the weights of a particular layer

* Check the new functions in [Scripts-functions](https://github.com/RParedesPalacios/Layers/tree/master/Tutorial#scripts-functions) in the tutorial

* Note: **Parser must be compiled**


### V0.1.1 - June 2016

* Important memory problem solved.


### V0.1 - May 2016
 * Initial commit of source code
 
 * Things to do:
 	* Full integration of the parser
 	* Robust implementation 
 	* Clean code
 	* Improve reusability of some parts
 	* ...

 * Major things to do (we are in the way!):
 	* Recurrent Neural networks
 	* GPU support





