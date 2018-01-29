/*Merge Sort File*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>

#define SIZE 1010228
#define PATH "../data/T10I4D100K.txt"

void run_omp(int a[], int size, int temp[], int threads);
void merge(int a[], int size, int temp[]);
void mergesort_serial(int a[], int size, int temp[]);
void mergesort_parallel(int a[], int size, int temp[], int threads);
int main(int argc, char* argv[]);




void run_omp(int a[], int size, int temp[], int threads) {
  printf("Entered run_omp\n");
    // Enable nested parallelism, if available
  omp_set_nested(1);
    // Parallel mergesort
  mergesort_parallel(a, size, temp, threads);
  printf("Exit run_omp\n");
}

void merge(int a[], int size, int temp[]) {
  printf("Entered merge\n");
  int i1 = 0;
  int i2 = size/2;
  int tempi = 0;
  while (i1 < size/2 && i2 < size) {
    if (a[i1] < a[i2]) {
      temp[tempi] = a[i1];
      i1++;
    } else {
      temp[tempi] = a[i2];
      i2++;
    }
    tempi++;
  }
  while (i1 < size/2) {
    temp[tempi] = a[i1];
    i1++;
    tempi++;
  }
  while (i2 < size) {
    temp[tempi] = a[i2];
    i2++;
    tempi++;
  }
    // Copy sorted temp array into main array, a
  memcpy(a, temp, size*sizeof(int));
}

void mergesort_serial(int a[], int size, int temp[]) {
  printf("Entered mergesort_serial\n");
  mergesort_serial(a, size/2, temp);
  mergesort_serial(a + size/2, size - size/2, temp);
    // The above call will not work properly in an OpenMP program
    // Merge the two sorted subarrays into a temp array
  merge(a, size, temp);
}


void mergesort_parallel(int a[], int size, int temp[], int threads) {
  printf("Entered mergesort_parallel\n");
  if ( threads == 1) {
    //printf("Thread %d begins serial merge sort\n", omp_get_thread_num());
    mergesort_serial(a, size, temp);
  } else if (threads > 1) {
          #pragma omp parallel sections num_threads(2)
          {
            // printf("Thread %d begins recursive section\n", omp_get_thread_num());
            #pragma omp section
            { //printf("Thread %d begins recursive call\n", omp_get_thread_num());

            mergesort_parallel(a, size/2, temp, threads/2);}
            #pragma omp section
            { //printf("Thread %d begins recursive call\n", omp_get_thread_num());
            mergesort_parallel(a + size/2, size - size/2, temp + size/2, threads - threads/2);}

            // The above use of temp + size/2 is an essential change from the serial version  
          }
        // Thread allocation is implementation dependent
        // Some threads can execute multiple sections while others are idle 
        // Merge the two sorted sub-arrays through temp
          merge(a, size, temp); 
        } else {
         printf("Error: %d threads\n", threads); 
         return;
       }
}

int main(int argc, char* argv[]) {
    puts("-OpenMP Recursive Mergesort-\t");
    // Check arguments
    if ( argc != 2 ) /* argc must be 3 for proper execution! */
      {
        printf( "Usage: %s array-size number-of-threads\n", argv[0]);
        return 1;
      }
    // Get arguments
    int size = SIZE; // Array size 
    int threads = atoi(argv[1]); // Requested number of threads
    // Check nested parallelism availability
    omp_set_nested(1);
    if (omp_get_nested() !=1 )
    {
      puts("Warning: Nested parallelism desired but unavailable");
    } 
    // Check processors and threads
    int processors = omp_get_num_procs(); // Available processors
    printf("Array size = %d\nProcesses = %d\nProcessors = %d\n", size, threads, processors);
    if (threads > processors) 
    {
      printf( "Warning: %d threads requested, will run_omp on %d processors available\n", threads, processors);
      omp_set_num_threads(threads);
    }
    int max_threads = omp_get_max_threads(); // Max available threads
    if (threads > max_threads) // Requested threads are more than max available
    {
      printf( "Error: Cannot use %d threads, only %d threads available\n", threads, max_threads);
      return 1;
    }
    // Array allocation
    int* a    = malloc(sizeof(int)*size);
    int* temp = malloc(sizeof(int)*size);
    if (a == NULL || temp == NULL) 
    {
      printf( "Error: Could not allocate array of size %d\n", size);
      return 1;
    }
    printf("Memory Allocated\n");

    int count = 0;

    for (int i=0; i<size; i++){
      a[i] = 0;
    }

    printf("a[] initialized with zeroes\n");

    //Read and intialize array from file
    FILE *file;
    file = fopen(PATH,"r");

    if(!file){
      perror("Error opening file");
      return -1;
    }
    printf("File opened\n");
    printf("Starting to read from file\n");
    while (!feof(file) && (count < size)){
      fscanf(file, "%d", &a[count++]);
    }
    fclose(file);
    printf("File read\n");

    printf("Size: %d\n", count);
    /*for(int i = 0; i < count; i++)
    {
      printf("a[%d] = %d\n", i, a[i]);
    }
    printf("Ended printing array\n");

    */
    /*
    // Random array initialization
    int i;
    srand(time(NULL));
    for(i=0; i<size; i++) {
      a[i] = rand() % size;
    }
    */

    // Sort
    double start = omp_get_wtime();
    printf("Start time %lf\n", start);
    run_omp(a, size, temp, threads);
    double end = omp_get_wtime( );
    printf("Start = %.2f\nEnd = %.2f\nElapsed = %.2f\n", start, end, end - start);
    // Result check
    for(int i=1; i<size; i++) {
      if (!(a[i-1] <= a[i])) {
        printf("Implementtion error: a[%d]=%d > a[%d]=%d\n", i-1, a[i-1], i, a[i]);
        return 1;
      }
    }
    puts("-Success-");
    double wtick = omp_get_wtick( );
    printf("Wtick = %.8f\n1/Wtick = %.8f\n",wtick, 1.0 / wtick);
    return 0;
  }
