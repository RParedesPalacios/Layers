![Layers](./figs/layers.jpg)


* A Neural Network toolkit.


* Layers is written in C++. 


* Layers uses [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page), [OpenMP](http://openmp.org/wp/) and ad-hoc [multi-threading](https://computing.llnl.gov/tutorials/pthreads/)

* Some features:
	* Flexible.
	* Easy to use. 
	* Layers provides a prototype and script language in order to ease the networks definition and experimentation. 
	* Optimized for CPU (not GPU).
	* Mainly for academic use. Layers is used in the following subjects:
		* Neural Networks
		* Computer Vision

* Check the last changes [Chagelog](https://github.com/RParedesPalacios/Layers/blob/master/src/readme.md#changelog)
* Read the [Tutorial](https://github.com/RParedesPalacios/Layers/tree/master/Tutorial)

## Usage

Layers only requires one argument, a net file:

> **layers file.net**

see some examples of net files in the [examples](https://github.com/RParedesPalacios/Layers/tree/master/examples) section
	
## Authors

* Layers core is written by [**Roberto Paredes**](http://users.dsic.upv.es/~rparedes/)
* The parser is written by [**Jose Miguel Benedí**](http://users.dsic.upv.es/~jbenedi/)

## Contributors

* [**Juan Maroñas**](https://github.com/jmaronas) is porting Layers to **GPU** and suggesting new functionalities 
* Python [**templating**](https://github.com/RParedesPalacios/Layers/tree/master/templating) to create easily the .net files by [**Mayte Gimenez**](https://github.com/maigimenez)
* Some improvements for compiling in Mac and linking Eigen by [**Jordi Mansanet**](https://github.com/jormansa)


## Install and compiling

[Installation instructions](https://github.com/RParedesPalacios/Layers/blob/master/src/readme.md)



## Changelog

### V0.4 - September 2016

Thanks to [**Jose Miguel Benedí**](http://users.dsic.upv.es/~jbenedi/) now we have a full integration of the parser inside Layers. 


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


