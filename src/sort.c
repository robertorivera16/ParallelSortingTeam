
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/* ==========================================================================
 * COMPARATORS
 * ========================================================================== */

/* A comparator function pointer type that we can pass to sort functions. */
typedef int (*IntComparator)(int a, int b);

/* Function: AscendingOrder(int a, int b)
 * Usage: int *sortedArray = BubbleSort( array, len, AscendingOrder );
 * -----------------------------------------------------------------------------
 * A comparator function that causes an array's values to be sorted in ascending 
 * order. Returns a positive value if a > b, 0 if a == b, and a negative value 
 * if a < b.
 */
int AscendingOrder(int a, int b) {
  return a - b;
}

/* Function: DescendingOrder(int a, int b)
 * Usage: int *sortedArray = BubbleSort( array, len, DescendingOrder );
 * -----------------------------------------------------------------------------
 * A comparator function that causes an array's values to be sorted in 
 * descending order. Returns a negative value if a > b, 0 if a == b, and a 
 * positive value if a < b.
 */
int DescendingOrder(int a, int b) {
  return b - a;
}

/* Function: RandomOrder(int a, int b)
 * Usage: int *sortedArray = BubbleSort( array, len, RandomOrder );
 * -----------------------------------------------------------------------------
 * A comparator function that causes an array's values to be shuffled in 
 * random order.
 */
int RandomOrder(int a, int b) {
  #define MAX 4
  return (rand() % MAX) - (MAX/2);
}


/* ==========================================================================
 * HELPER FUNCTIONS
 * ========================================================================== */

/* Function: PrintArray(int *array, int len)
 * Usage: PrintArray( array, len );
 * -----------------------------------------------------------------------------
 * Prints the provided array to the console. The len parameter should equal the 
 * number of elements in the array.
 */
void PrintArray(int *array, int len) {
  for ( int i = 0; i < len; ++i ) {
    printf( "%d ", array[i] );
  }
  printf("\n");
}

/* Function: DuplicateArray( int *array, int len )
 * Usage: int *dupArray = DuplicateArray( array, len );
 * -----------------------------------------------------------------------------
 * Returns a deep copy of the provided array, where len is the number of 
 * elements in the array. The copy is allocated on the heap; it should be freed 
 * by the caller after use.
 */
int *DuplicateArray(int *array, int len) {
  int *result = malloc( len * sizeof(int) );
  memcpy( result, array, len * sizeof(int) );
  return result;
}

/* Function: SwapElements(int *a, int *b)
 * Usage: SwapElements( &array[0], &array[1] );
 * -----------------------------------------------------------------------------
 * A helper function that swaps two integers in memory.
 */
void SwapElements(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}


/* ==========================================================================
 * SORTING ALGORITHMS
 * ========================================================================== */

typedef int* (*SortFunction)(int *array, int len, IntComparator cmp);


int *BubbleSort(int *array, int len, IntComparator cmp) {
  
  int *result = DuplicateArray( array, len );
  
  for ( int i = len - 1; i > 0; --i ) {
    for ( int j = 0; j < i; ++j ) {
      if ( cmp( result[j], result[j+1] ) > 0 ) {
        SwapElements( &result[j], &result[j+1] );
      }
    }
  }
  
  return result;
}


int *SelectionSort(int *array, int len, IntComparator cmp) {
  
  int *result = DuplicateArray( array, len );
  
  for ( int i = 0; i < len; ++i ) {
    int minIndex = i;
    
    for ( int j = i + 1; j < len; ++j ) {
      if ( cmp( result[j], result[minIndex] ) < 0 ) {
        minIndex = j;
      }
    }
    
    SwapElements( &result[i], &result[minIndex] );
  }
  
  return result;
}


int *InsertionSort(int *array, int len, IntComparator cmp) {
  int *result = DuplicateArray( array, len );
  
  for ( int i = 1; i < len; ++i ) {
    int valueToInsert = result[i];
    int holePos = i;
    
    while ( holePos > 0 && valueToInsert < result[holePos - 1]) {
      SwapElements( &result[holePos], &result[holePos - 1] );
      holePos -= 1;
    }
    
    result[holePos] = valueToInsert;
  }
  
  return result;
}


/* ==========================================================================
 * MAIN PROGRAM
 * ========================================================================== */

int *GetShuffledArray(int len) {
  int *array = malloc( len * sizeof(int) );
  
  for (int i = 0; i < len; ++i) {
    array[i] = i;
  }
  
  return SelectionSort( array, len, RandomOrder );
}

/* Function: DoSort(int *array, int len, char *algorithmName,
 *                  SortFunction sortFunc, IntComparator cmp)
 * Usage: DoSort( array, len, "BubbleSort", BubbleSort, AscendingOrder );
 * -----------------------------------------------------------------------------
 * A wrapper function that runs the specified sorting algorithm on the provided 
 * array, printing both the original unsorted array and the final sorted array.
 */
void DoSort(int *array, int len, char *algorithmName,
            SortFunction sortFunc, IntComparator cmp) {
  printf("\n---------------------------------------------------------------\n");
  printf("%s\n", algorithmName);
  printf("---------------------------------------------------------------\n");
  
  printf("Before: ");
  PrintArray( array, len );
  
  int *sortedArray = sortFunc( array, len, cmp );
  
  printf("After:  ");
  PrintArray( sortedArray, len );
  
  free( sortedArray );
}

int main(int argc, char *argv[]) {
  
  /* Seeds the random number generator in case the RandomOrder comparator is 
   * needed.
   */
  srand ( time( NULL ) );
  
  /* Create a shufled array of N elements. */
  int len = atoi(argv[1]);
  int *array = GetShuffledArray( len );
  
  DoSort( array, len, "BubbleSort",     BubbleSort,    AscendingOrder );
  DoSort( array, len, "Selection Sort", SelectionSort, AscendingOrder );
  DoSort( array, len, "Insertion Sort", InsertionSort, AscendingOrder );
  
  free( array );
  
  return 0;
}