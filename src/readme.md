# Layers source code

## Compile and install

> 
> you need to have **g++** and **make** installed. For the parser you need Flex library to link (-lfl)
>

* Enter in the netparser directory
* Compile the parser


~~~shell
cd netparser
make clean
make
~~~


* Copy the parser to some PAHT directory (e.g. ~/bin)

~~~shell
mkdir ~/bin
export PATH="~/bin:$PATH" >> ~/.bashrc
cp cmc ~/bin
source ~/.bashrc
~~~

* back to layers src and compile layers

~~~shell
cd ..
make clean
make
cp layers ~/bin
~~~

DONE!

### Compiling on MAC:

* You need some alternative to:
 
 clock_gettime and CLOCK_MONOTONIC
 
* See this stackoverflow [post](http://stackoverflow.com/questions/5167269/clock-gettime-alternative-in-mac-os-x) or just comment that lines!
 
* Also in the Makefile use the MAC FLAGS:
 
 CXXFLAGS = -I Eigen -O3 

### Compiling on Windows:

* Try and push it! ...  ¯\\\_(ツ)_/¯ 



## Changelog

### V0.1 - May 30 2016
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





