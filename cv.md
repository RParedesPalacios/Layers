\[fragile\]<span>Constants</span>

-   There are three different constants to define (default values):

    -   threads: number of threads for parallelization (4)

    -   batch size: size of the batch for the network (100)

    -   log: log file where some messages are saved (netparser.log)

-   An example:

const<span> threads=4 batch=10 log=“mnist.log” </span>

\[fragile\]<span>Data</span>

-   Data can be read in ascii or binary. Data format is the following:

samples dim output sample1\_1 ... sample1\_dim out\_1 .. out\_c ...
samplen\_1 ... sample1\_dim out\_1 .. out\_c

-   *samples* is the number of samples (int)

-   *dim* is the dimensionality of the samples (int)

-   *outout* is ths number of output targets, classes in a
    classification problem (int)

-   each row is a sample (float values)

-   when samples are color images the channels appear separated, firts
    R, then G and then B and $dim$ must be $3\times rows\times cols$

\[fragile\]<span>Data</span>

-   An example of data definition:

data <span> D1 \[filename=“../training”, binary\] D2
\[filename=“../test”, binary\] Dval \[filename=“../valid”, ascii\]
</span>

-   D1, D2 and Dval are the name of the data variables

-   Full path to file can be used

\[fragile\]<span>Networks</span>

-   Networks are the main part of a Layer program

-   Networks are composed by three main parts:

    -   Data

    -   Layers

    -   Connections

-   The networks are defined like this:

    network N1 <span> ... </span>

-   where N1 is the name of the network

\[fragile\]<span>Networks - Data</span>

-   The Networks have to defined at least a training data set

-   Test and validation data sets are optional:

    network N1 <span> //data data tr D1 //mandatory data ts D2
    //optional data va Dval //optional ... </span>

-   When test or validation data are provided the error function of the
    net will be also evaluated for that data sets


