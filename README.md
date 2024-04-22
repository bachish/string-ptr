# StringPtr
Small single-threaded library for automatic string freeing. Used one-bit counters and "smart" pointers

## Global values: 

* empty_string 
* null_object

## Operations set:

* creating a new pointer initialized by default, string and other pointer
* assignment to pointer other pointer or string
* extracting a string from smart pointer
* printing a smartpointer include counter and value
* string release trace in debug mode, to enable add `-D DEBUG` in  compilation command at `Makefile`

## Test set
* various initialisation methods
* assignment
* simple sorting array of string which represented as smart pointers (don't change ptr counting)  
