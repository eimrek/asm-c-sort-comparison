# Assembly and C sorting algorithm comparison 

This repository contains assembly and C implementations of quick and insertion sort algorithms. Timing is compared. Here's the output on a linux machine:

~~~
$ ./main.exe 
Length of array: 10000000 
Running qsort(); time taken: 1326 ms 
Running cQuickSort(); time taken: 460 ms 
Running asmQuickSort(); time taken: 443 ms 
Length of array2: 100000 
Running cInsertionSort(); time taken: 1387 ms 
Running asmInsertionSort(); time taken: 1050 ms
~~~

NB: the implementations are most likely not optimal!

Run instructions on a Ubuntu machine:

* Install `gcc` and `nasm`: `sudo apt install build-essential gcc-multilib nasm`
* `make all`
