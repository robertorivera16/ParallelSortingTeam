/*Merge Sort File*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>


void mergesort_serial(int a[], int size, int temp[]) {
       
    mergesort_serial(a, size/2, temp);
    mergesort_serial(a + size/2+1, size - size/2, temp);
    // The above call will not work properly in an OpenMP program
    // Merge the two sorted subarrays into a temp array
    merge(a, size, temp);
}

int main(int argc, char *argv[]) {
  
 
}